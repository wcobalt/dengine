//
// Created by wcobalt on 1/23/20.
//

#include "ComponentMessages.h"

using namespace dengine;

//InstanceCreateMessage
InstanceCreateMessage::InstanceCreateMessage() : InstanceCreateMessage(std::chrono::system_clock::now()) {}

InstanceCreateMessage::InstanceCreateMessage(const ComponentMessage::time_type &sendingTime)
        : ComponentMessage(ComponentMessage::Type::INSTANCE_CREATE, sendingTime) {}

void InstanceCreateMessage::handle(Component &component) const {
    component.onInstanceCreate(*this);
}

//InstanceDestroyMessage
InstanceDestroyMessage::InstanceDestroyMessage() : InstanceDestroyMessage(std::chrono::system_clock::now()) {}

InstanceDestroyMessage::InstanceDestroyMessage(const ComponentMessage::time_type &sendingTime)
        : ComponentMessage(ComponentMessage::Type::INSTANCE_DESTROY, sendingTime) {}

void InstanceDestroyMessage::handle(Component &component) const {
    component.onInstanceDestroy(*this);
}

//ComponentLoadMessage
ComponentLoadMessage::ComponentLoadMessage() : ComponentLoadMessage(std::chrono::system_clock::now()) {}

ComponentLoadMessage::ComponentLoadMessage(const ComponentMessage::time_type &sendingTime)
        : ComponentMessage(ComponentMessage::Type::COMPONENT_LOAD, sendingTime) {}

void ComponentLoadMessage::handle(Component &component) const {
    component.onComponentLoad(*this);
}

//ComponentUnloadMessage
ComponentUnloadMessage::ComponentUnloadMessage() : ComponentUnloadMessage(std::chrono::system_clock::now()) {}

ComponentUnloadMessage::ComponentUnloadMessage(const ComponentMessage::time_type &sendingTime)
        : ComponentMessage(ComponentMessage::Type::COMPONENT_UNLOAD, sendingTime) {}

void ComponentUnloadMessage::handle(Component &component) const {
    component.onComponentUnload(*this);
}

//UpdateMessage
UpdateMessage::UpdateMessage() : UpdateMessage(std::chrono::system_clock::now()) {}

UpdateMessage::UpdateMessage(const ComponentMessage::time_type &sendingTime)
        : ComponentMessage(ComponentMessage::Type::UPDATE, sendingTime) {}

void UpdateMessage::handle(Component &component) const {
    component.onUpdate(*this);
}

//SceneUnloadMessage
SceneUnloadMessage::SceneUnloadMessage() : SceneUnloadMessage(std::chrono::system_clock::now()) {}

SceneUnloadMessage::SceneUnloadMessage(const ComponentMessage::time_type &sendingTime)
        : ComponentMessage(ComponentMessage::Type::SCENE_UNLOAD, sendingTime) {}

void SceneUnloadMessage::handle(Component &component) const {
    component.onSceneUnload(*this);
}

//GameEndMessage
GameEndMessage::GameEndMessage() : GameEndMessage(std::chrono::system_clock::now()) {}

GameEndMessage::GameEndMessage(const ComponentMessage::time_type &sendingTime)
        : ComponentMessage(ComponentMessage::Type::GAME_END, sendingTime) {}

void GameEndMessage::handle(Component &component) const {
    component.onGameEnd(*this);
}