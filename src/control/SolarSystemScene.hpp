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
#ifndef NON_GRAVITAR_SOLAR_SYSTEM_SCENE_HPP
#define NON_GRAVITAR_SOLAR_SYSTEM_SCENE_HPP

#include <typeindex>
#include "shape-group/SolarSystem.hpp"
#include "Scene.hpp"


namespace gvt {
	class SceneChangeEvent;
	class SolarSystemSceneBuilder;

	/**
	 * A @c SolarSystemScene features a solar system, giving the possibility
	 * to enter planets which the spaceship runs into.
	 */
	class SolarSystemScene: public Scene {
		public:
			using factory = std::function<shared_ptr<SolarSystemScene>(void)>;
		private:
			shared_ptr<SolarSystem> mSystem;
			factory mFactory;
			shared_ptr<Callback<SceneChangeEvent>> mSceneCbk;

			void onCollision (PairCollisionEvent e) override;
			void onShapeDestroyed (shared_ptr<Shape> shape) override;
			void onSceneChanged (SceneChangeEvent e);
		public:
			SolarSystemScene(
				Vectord size, shared_ptr<SolarSystem> &system,
				factory nextSceneFactory
			);
			~SolarSystemScene() override;

			inline bool hasNextScene() const override;
			shared_ptr<Scene> nextScene() override;

			shared_ptr<SolarSystem> solarSystem() const;
	};
}


namespace gvt {
	bool SolarSystemScene::hasNextScene() const {
		return std::distance(
				mSystem->planetsBegin(), mSystem->planetsEnd()
		) == 0;
	}
}


#endif