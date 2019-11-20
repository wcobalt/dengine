//
// Created by wcobalt on 11/18/19.
//

#ifndef DENGINE_DENGINEMESSAGE_H
#define DENGINE_DENGINEMESSAGE_H

namespace dengine {
    enum class ScenesManagerMessage {
        UPDATE, GAME_END
    };

    enum class SceneMessage {
        UPDATE, SCENE_UNLOAD, SCENE_LOAD, GAME_END
    };

    enum class GameObjectMessage {
        UPDATE, INSTANCE_CREATE, INSTANCE_DESTROY, SCENE_UNLOAD, GAME_END
    };

    enum class ComponentMessage {
        INSTANCE_CREATE, INSTANCE_DESTROY, COMPONENT_LOAD, COMPONENT_UNLOAD, UPDATE, SCENE_UNLOAD, GAME_END
    };
}

#endif //DENGINE_DENGINEMESSAGE_H
