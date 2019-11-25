//
// Created by wcobalt on 11/18/19.
//

#ifndef DENGINE_DENGINEMESSAGETYPE_H
#define DENGINE_DENGINEMESSAGETYPE_H

namespace dengine {
    enum class ScenesManagerMessageType {
        UPDATE, GAME_END
    };

    enum class SceneMessageType {
        UPDATE, SCENE_UNLOAD, SCENE_LOAD, GAME_END
    };

    enum class GameObjectMessageType {
        UPDATE, INSTANCE_CREATE_PRE, INSTANCE_CREATE_POST, INSTANCE_DESTROY, SCENE_UNLOAD, GAME_END, INSTANCE_MOVE
    };

    enum class ComponentMessageType {
        INSTANCE_CREATE, INSTANCE_DESTROY, COMPONENT_LOAD, COMPONENT_UNLOAD, UPDATE, SCENE_UNLOAD, GAME_END,
        DIRECT_CHILDREN_CHANGE, PARENT_CHANGE, INSTANCE_MOVE
    };
}

#endif //DENGINE_DENGINEMESSAGETYPE_H
