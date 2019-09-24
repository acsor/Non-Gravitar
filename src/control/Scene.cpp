// MIT License
//
// Copyright (c) 2018 Oscar B. et al.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include "Scene.hpp"
#include "Game.hpp"
#include "shape-group/CollisionGroup.hpp"
#include "shape/MountainChain.hpp"
#include "shape/Planet.hpp"

using type_index = std::type_index;


namespace gvt {
	TypeVertex::TypeVertex (std::type_index type):
			Vertex(type.hash_code(), std::make_shared<type_index>(type)) {
	}

	bool TypeVertex::operator== (TypeVertex const &other) const {
		return  mId == other.mId &&
				mValue->hash_code() == other.mValue->hash_code();
	}


	Scene::Scene(Vectord size, shared_ptr<CollisionGroup> shapes):
			mSize{size}, mShapes{std::move(shapes)} {
		mGame = Game::getInstance();
		mShapesView.reset(new ShapeGroupView(mShapes));

		initializeDestroyGraph();

		mCollisionCbk = mShapes->collisionDispatcher().addCallback(
			[this] (PairCollisionEvent e) -> void { onCollision(e); }
		);
		mFuelCbk = mGame->spaceship()->fuelDispatcher().addCallback(
			[this] (FuelEvent e) -> void { onFuelChanged(e); }
		);
		mDestroyCbk = mShapes->removalDispatcher().addCallback(
			[this] (ShapeRemovalEvent e) -> void { onShapeRemoved(e); }
		);
	}

	Scene::~Scene() {
		mShapes->removalDispatcher().removeCallback(mDestroyCbk);
		mGame->spaceship()->fuelDispatcher().removeCallback(mFuelCbk);
		mShapes->collisionDispatcher().removeCallback(mCollisionCbk);
	}

	void Scene::initializeDestroyGraph() {
		// Edges to ba later added to the graph. Each (u, v) edge says that,
		// if a shape of type u clashes with a shape of type v, then this last
		// one is destroyed.
		std::vector<std::pair<type_index, type_index>> destroyPair = {
			{typeid(Bunker), typeid(Spaceship)},
			{typeid(RoundMissile), typeid(Spaceship)},
			{typeid(MountainChain), typeid(Spaceship)},

			{typeid(TractorBeam), typeid(RoundMissile)},
			{typeid(TractorBeam), typeid(Fuel)},

			{typeid(Spaceship), typeid(Bunker)},
			{typeid(RoundMissile), typeid(Bunker)},

			{typeid(Spaceship), typeid(RoundMissile)},
			{typeid(Bunker), typeid(RoundMissile)},
			{typeid(MountainChain), typeid(RoundMissile)},
			{typeid(Planet), typeid(RoundMissile)},
		};

		mDestroyGraph.insertVertex(TypeVertex(typeid(Bunker)));
		mDestroyGraph.insertVertex(TypeVertex(typeid(Fuel)));
		mDestroyGraph.insertVertex(TypeVertex(typeid(MountainChain)));
		mDestroyGraph.insertVertex(TypeVertex(typeid(Planet)));
		mDestroyGraph.insertVertex(TypeVertex(typeid(RoundMissile)));
		mDestroyGraph.insertVertex(TypeVertex(typeid(Spaceship)));
		mDestroyGraph.insertVertex(TypeVertex(typeid(TractorBeam)));

		for (auto const &pair: destroyPair)
			mDestroyGraph.insertEdge(
					TypeVertex(pair.first), TypeVertex(pair.second)
			);
	}

	void Scene::onCollision (PairCollisionEvent e) {
		auto first = TypeVertex(typeid(*e.first));
		auto second = TypeVertex(typeid(*e.second));

		if (mDestroyGraph.containsEdge(first, second))
			e.second->destroyed(true);
		if (mDestroyGraph.containsEdge(second, first))
			e.first->destroyed(true);
	}

	void Scene::onFuelChanged (FuelEvent e) {
		if (e.newAmount <= 0) {
			mGame->gameInfo()->resetSpaceships();
			mGame->spaceship()->destroyed(true);
		}
	}

	void Scene::onShapeRemoved (ShapeRemovalEvent e) {
		if (e.shape->destroyed()) {
			if (std::dynamic_pointer_cast<Bunker>(e.shape)) {
				mGame->gameInfo()->upgradeScore(BUNKER_SCORE);
			} else if (auto s = std::dynamic_pointer_cast<Spaceship>(e.shape)) {
				onSpaceshipDestroyed(s);
			} else if (auto f = std::dynamic_pointer_cast<Fuel>(e.shape)) {
				mGame->spaceship()->rechargeFuel(*f);
			}
		}
	}

	void Scene::onSpaceshipDestroyed (shared_ptr<Spaceship> ship) {
		auto info = mGame->gameInfo();

		if (info->spaceships() > 0)
			mGame->gameInfo()->decrementSpaceships();
	}

	void Scene::onUpdateGame (double seconds) {
		// Remove outlived shapes
		mShapes->removeIf(
			[] (shared_ptr<Shape> const &s) -> bool { return s->destroyed (); }
		);
		auto shapesCopy = std::vector<shared_ptr<Shape>>(
				mShapes->begin(), mShapes->end()
		);

		// TODO Is there another more performing way of safely iterating
		//  through the list without making a copy of it?
		for (auto &s: shapesCopy) {
			s->velocity(s->velocity() + seconds * s->acceleration());
			s->position(s->position() + seconds * s->velocity());
		}
	}

	void Scene::onExitBoundaries(shared_ptr<Spaceship> ship) {
		auto const angle = ship->velocity().angle();
		auto const speed = ship->speed();
		auto const pos = ship->position();

		if (pos.x < 0 || pos.x > mSize.x - ship->width()) {
			ship->velocity(speed * Vectord(M_PI - angle));
		} else if (pos.y < 0 || pos.y > mSize.y - ship->height()) {
			ship->velocity(speed * Vectord(-angle));
		}
	}

	void Scene::draw (sf::RenderTarget &t, sf::RenderStates s) const {
		t.draw(*mShapesView, s);
	}
}
