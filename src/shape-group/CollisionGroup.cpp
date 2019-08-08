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
#include <memory>
#include "CollisionGroup.hpp"

#include "shape/Spaceship.hpp"
#include "shape/Bunker.hpp"
#include "shape/RoundMissile.hpp"
#include "shape/Fuel.hpp"
#include "shape/Rectangle.hpp"
#include "shape/Circle.hpp"

using CollisionGroup = gvt::CollisionGroup;
using Event = gvt::Event;
using Shape = gvt::Shape;

template<typename T> using shared_ptr = std::shared_ptr<T>;

gvt::CollisionListener::CollisionListener(CollisionGroup &group):
	mGroup{group} {
}

void gvt::CollisionListener::handle(Event *e) {
	auto shapeEvent = dynamic_cast<ShapeEvent *>(e);

	if (shapeEvent) {
        switch (shapeEvent->type) {
        	case ShapeEvent::Type::moved:
			case ShapeEvent::Type::rotated:
                mGroup.updateCollisions();
        	default:
        		break;
        }
	}
}


gvt::CollisionVisitor::CollisionVisitor(CollisionGroup &group):
	mGroup{group} {
}

void gvt::CollisionVisitor::visitMissile(gvt::RoundMissile &missile) {
	missile.destroyed(true);
}

void gvt::CollisionVisitor::visitBunker(gvt::Bunker &bunker) {
    // Bunkers are indestructible
}

void gvt::CollisionVisitor::visitSpaceship(gvt::Spaceship &spaceship) {
	spaceship.destroyed(true);
}

void gvt::CollisionVisitor::visitFuel(gvt::Fuel &fuel) {
	fuel.destroyed(true);
}


void gvt::CollisionGroup::updateCollisions() {
	for (auto first: mShapes) {
        for (auto second: mShapes) {
        	if (*first != *second && first->clashes(*second)) {
        		first->accept(mVisitor);
				second->accept(mVisitor);
        	}
        }
	}
}
