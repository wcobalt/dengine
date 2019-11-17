//
// Created by wcobalt on 3/30/19.
//

#include <map>
#include <memory>
#include <string>

#ifndef DENGINE_SCENESMANAGER_H
#define DENGINE_SCENESMANAGER_H

namespace dengine {
    class Scene;
    class DengineAccessor;
    class WindowState;
    class KeyboardState;
    class MouseState;
}

#include "Coreutils/ID.h"
#include "DObject.h"

namespace dengine {
    class ScenesManager : public DObject {
    public:
        static const ID NOT_EXIST_SCENE = 0;
    private:
        std::map<ID, std::pair<std::string, std::shared_ptr<dengine::Scene>>> scenesIds;
        std::map<std::string, std::pair<ID, std::shared_ptr<dengine::Scene>>> scenesAliases;

        std::pair<ID, std::shared_ptr<dengine::Scene>> currentScene;

        ID nextSceneId;

        void setCurrentScene(std::pair<ID, std::shared_ptr<dengine::Scene>> scene);

        ID getUniqueSceneId();
    public:
        ScenesManager();

        void update(std::shared_ptr<WindowState> windowState, std::shared_ptr<KeyboardState> keyboardState,
                            std::shared_ptr<MouseState> mouseState);

        ID addScene(std::shared_ptr<dengine::Scene> scene);
        ID addScene(std::shared_ptr<dengine::Scene> scene, const std::string& alias);

        void removeScene(ID id);
        void removeScene(const std::string& alias);

        void loadScene(ID id);
        void loadScene(const std::string& alias);

        ID getCurrentSceneID() const;

        std::shared_ptr<dengine::Scene> getCurrentScene() const;

        std::shared_ptr<dengine::Scene> getScene(ID id) const;
        std::shared_ptr<dengine::Scene> getScene(const std::string& alias) const;

        ID getIDByAlias(const std::string& alias) const;
        std::string getAliasByID(ID id) const;
    };
}

#endif //DENGINE_SCENESMANAGER_H
