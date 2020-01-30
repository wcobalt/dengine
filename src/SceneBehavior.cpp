//
// Created by wcobalt on 11/17/19.
//
#include <memory>
#include "GameObject.h"
#include "Scene.h"
#include "SceneBehavior.h"
#include "Coreutils/Messages/ComponentMessage.h"
#include "Initializer.h"

using namespace dengine;

namespace dengine {
    class CustomInitializer : public Initializer {
    public:
        void initialize(GameObject &gameObject) override {

        }
    };
}

void SceneBehavior::onSceneLoad(Scene &scene) {
    CustomInitializer& initializer();

    GameObject& go = GameObject::instantiate(initializer); //creates empty go and then initializes it trough passed initializer

    //or

    GameObject::instantiate(go); //clones existing go
}

void SceneBehavior::onSceneUnload(Scene &scene) {}

void SceneBehavior::onGameEnd(Scene &scene) {} 