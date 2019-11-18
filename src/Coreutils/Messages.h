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
        UPDATE, UNLOAD, LOAD, GAME_END
    };

    enum class GameObjectMessage {
        UPDATE, CREATE, DESTROY, SCENE_UNLOAD, GAME_END
    };
}

#endif //DENGINE_DENGINEMESSAGE_H
