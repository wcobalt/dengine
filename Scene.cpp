//
// Created by wcobalt on 19.09.18.
//

#include "Scene.h"
#include "Components/Component.h"
#include "Components/TransformComponent.h"

Scene::Scene(const std::string& id):id(id) {
    currentID = BASE_ID;
}

Scene::Scene(const std::string& id, unsigned int width, unsigned int height):Scene(id) {
    this->width = width;
    this->height = height;
}

void Scene::placeInstance(GameObject& instance) {
    instances.push_back(instance);
}

void Scene::placeInstance(GameObject& instance, float x, float y) {
    TransformComponent* transform =
            static_cast<TransformComponent*>(instance.getComponentsByID("transform")[0]);

    std::vector<Component&> tr = instance.getComponentsByID("hui");

    std::vector<Component&>& t = instance.getAllComponents();

    for (int i = 0; i < t.size(); i++) t[i]->create();

    transform.setPosition(x, y);

    placeInstance(instance);
}

unsigned int Scene::getUniqueGameObjectID() {
    //I'm not sure that it's the best method for getting id of new instance
    return currentID++;
}

const std::string& Scene::getID() const {
    return id;
}