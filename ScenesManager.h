//
// Created by wcobalt on 3/30/19.
//

#include <map>
#include <memory>
#include <string>

#ifndef DENGINE_SCENESMANAGER_H
#define DENGINE_SCENESMANAGER_H

#include "Coreutils/ID.h"
#include "Scene.h"
#include "DObject.h"
#include "DengineAccessor.h"

namespace dengine {
    class Scene;
    class DengineAccessor;

    class ScenesManager : public DObject {
    public:
        static const coreutils::ID NOT_EXIST_SCENE = 0;
    private:
        std::map<coreutils::ID, std::pair<std::string, std::shared_ptr<dengine::Scene>>> scenesIds;
        std::map<std::string, std::pair<coreutils::ID, std::shared_ptr<dengine::Scene>>> scenesAliases;

        std::pair<coreutils::ID, std::shared_ptr<dengine::Scene>> currentScene;

        coreutils::ID nextSceneId;

        void setCurrentScene(std::pair<coreutils::ID, std::shared_ptr<dengine::Scene>> scene);
        coreutils::ID getUniqueSceneId();
    public:
        ScenesManager();

        void update(dengine::DengineAccessor dengineAccessor);

        coreutils::ID addScene(std::shared_ptr<dengine::Scene> scene);
        coreutils::ID addScene(std::shared_ptr<dengine::Scene> scene, const std::string& alias);

        void removeScene(coreutils::ID id);
        void removeScene(const std::string& alias);

        void loadScene(coreutils::ID id);
        void loadScene(const std::string& alias);

        coreutils::ID getCurrentSceneID() const;

        std::shared_ptr<dengine::Scene> getCurrentScene() const;

        std::shared_ptr<dengine::Scene> getScene(coreutils::ID id) const;
        std::shared_ptr<dengine::Scene> getScene(const std::string& alias) const;

        coreutils::ID getIDByAlias(const std::string& alias) const;
        const std::string& getAliasByID(coreutils::ID id) const;
    };
}

#endif //DENGINE_SCENESMANAGER_H
