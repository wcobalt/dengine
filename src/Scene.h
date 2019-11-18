//
// Created by wcobalt on 19.09.18.
//

#include <string>
#include <map>
#include <memory>
#include <vector>

#ifndef DENGINE_SCENE_H
#define DENGINE_SCENE_H

namespace dengine {
    class GameObject;
}

#include "DObject.h"
#include "Coreutils/ID.h"
#include "Coreutils/Messages.h"
#include "SceneBehavior.h"

namespace dengine {
    class Scene : public DObject {
    private:
        std::shared_ptr<GameObject> root;

        SceneBehavior& sceneBehavior;

        ID currentId;
    public:
        Scene(SceneBehavior& sceneBehavior);

        void sendMessage(SceneMessage message);

/*        template<typename T>
        std::vector<std::shared_ptr<GameObject>> getInstances() const; //@todo to filter or something*/

        ID takeNextId();

        std::shared_ptr<GameObject> getRoot() const;
    };
}

#endif //DENGINE_SCENE_H
