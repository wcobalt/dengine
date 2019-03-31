//
// Created by wcobalt on 19.09.18.
//

#include <queue>
#include <vector>

#include "Scene.h"
#include "Components/Component.h"
#include "Components/Transform3DComponent.h"

using namespace dengine;
using namespace dengine::components;

using std::queue;
using std::vector;

Scene::Scene() {
    shared_ptr<Transform3DComponent> transform = std::make_shared<Transform3DComponent>(
            new Transform3DComponent(ROOT_GAME_OBJECT_X, ROOT_GAME_OBJECT_Y, ROOT_GAME_OBJECT_Z));

    root = std::make_shared<GameObject>(new GameObject(transform));
}

void Scene::sceneLoad() {}

void Scene::sceneUnload() {}

void Scene::placeInstance(shared_ptr<GameObject> instance) {
    root->addChild(instance);
}

void Scene::placeInstance(shared_ptr<GameObject> instance, float x, float y) {
    auto transform3d = instance->getComponent<Transform3DComponent>();

    placeInstance(instance, x, y, transform3d->getPosition().z);
}

void Scene::placeInstance(shared_ptr<GameObject> instance, float x, float y, float z) {
    auto transform3d = instance->getComponent<Transform3DComponent>();

    transform3d->setPosition(x, y, z);

    placeInstance(instance);
}

void Scene::destroyInstance(shared_ptr<GameObject> instance) {
    //@todo check memory safety
    instance->removeAllChildren();

    instance->getParent()->removeChild(instance);
}

void Scene::clean() {
    queue<shared_ptr<GameObject>> q;

    q.push(root);

    while (!q.empty()) {
        shared_ptr<GameObject> currentInstance = q.front();

        q.pop();

        vector<shared_ptr<GameObject>> children = currentInstance->getChildren();

        for (const auto& instance : children)
            q.push(instance);

        destroyInstance(currentInstance);
    }
}

template <class T>
vector<shared_ptr<GameObject>> Scene::getInstances() const {
    queue<shared_ptr<GameObject>> q;
    vector<shared_ptr<GameObject>> result;

    q.push(root);

    while (!q.empty()) {
        shared_ptr<GameObject> currentInstance = q.front();

        q.pop();

        vector<shared_ptr<GameObject>> children = currentInstance->getChildren();

        for (const auto& instance : children)
            q.push(instance);

        if (currentInstance != root &&
            std::dynamic_pointer_cast<T>(currentInstance)) {

            result.push_back(currentInstance);
        }
    }

    return result;
}

shared_ptr<GameObject> Scene::getRoot() const {
    return root;
}

void Scene::update() {
    //
}