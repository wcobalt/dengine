//
// Created by wcobalt on 19.09.18.
//

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <functional>

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

        std::shared_ptr<SceneBehavior> sceneBehavior;

        ID currentId, id;
        std::string alias;

        void handle(std::function<void (std::shared_ptr<GameObject>)> handler);
    public:
        Scene(ID id, std::shared_ptr<SceneBehavior> sceneBehavior);

        Scene(ID id, std::shared_ptr<SceneBehavior> sceneBehavior, const std::string &alias);

        void sendMessage(SceneMessage message);

        ID takeNextId();

        std::shared_ptr<GameObject> getRoot() const;

        const std::string& getAlias() const;

        ID getId() const;
    };
}

#endif //DENGINE_SCENE_H
