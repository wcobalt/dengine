//
// Created by wcobalt on 3/30/19.
//

#include <memory>
#include <string>
#include <vector>

#ifndef DENGINE_SCENESMANAGER_H
#define DENGINE_SCENESMANAGER_H

namespace dengine {
    class Scene;
    class WindowState;
    class KeyboardState;
    class MouseState;
    class SceneBehavior;
}

#include "Coreutils/ID.h"
#include "DObject.h"
#include "Coreutils/Messages.h"

namespace dengine {
    class ScenesManager : public DObject {
    private:
        std::vector<std::shared_ptr<Scene>> scenes;

        std::shared_ptr<Scene> currentScene;

        ID currentId;

        ID takeNextSceneId();
    public:
        using const_iterator = decltype(scenes)::const_iterator;

        using iterator = decltype(scenes)::iterator;
    private:
        const_iterator findSceneByAlias(const std::string& alias) const;

        const_iterator findSceneById(ID id) const;

        void removeScene(const_iterator iterator);

        void loadScene(const_iterator iterator);

        void unloadCurrentScene();
    public:
        ScenesManager();

        void sendMessage(ScenesManagerMessage message);

        ID addScene(std::shared_ptr<SceneBehavior> sceneBehavior);

        ID addScene(std::shared_ptr<SceneBehavior> sceneBehavior, const std::string &alias);

        void removeScene(ID id);

        void removeScene(const std::string& alias);

        void loadScene(ID id);

        void loadScene(const std::string& alias);

        void restartScene();

        void loadNextScene();

        void loadPreviousScene();

        void loadFirstScene();

        std::shared_ptr<Scene> getCurrentScene() const;

        bool isCurrentSceneExist() const;

        std::shared_ptr<Scene> getScene(ID id) const;

        std::shared_ptr<Scene> getScene(const std::string &alias) const;

        iterator begin();

        iterator end();

        const_iterator begin() const;

        const_iterator end() const;

        const_iterator cbegin() const;

        const_iterator cend() const;
    };
}

#endif //DENGINE_SCENESMANAGER_H
