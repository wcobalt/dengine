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

namespace dengine {
    class ScenesManager : public DObject {
    private:
        mutable std::vector<std::unique_ptr<Scene>> scenes;

        Scene* currentScene = nullptr;

        ID currentId = IDUtils::NO_ID;

        ID takeNextSceneId();
    public:
        using const_iterator = decltype(scenes)::const_iterator;
        using iterator = decltype(scenes)::iterator;
    private:
        iterator findSceneByAlias(const std::string& alias) const;

        iterator findSceneById(ID id) const;

        void removeScene(const_iterator iterator);

        void loadScene(const_iterator iterator);

        void unloadCurrentScene();
    public:
        enum class EventType {
            UPDATE, GAME_END
        };

        void handleExternalEvent(EventType eventType);

        //depends on how to reset behaviours when scene reloading - nohow just call onSceneLoad()
        Scene & addScene(std::unique_ptr<SceneBehavior> sceneBehavior);

        Scene & addScene(std::unique_ptr<SceneBehavior> sceneBehavior, const std::string &alias);

        void removeScene(ID id);

        void removeScene(const std::string& alias);

        void loadScene(ID id);

        void loadScene(const std::string& alias);

        void restartScene();

        void loadNextScene();

        void loadPreviousScene();

        void loadFirstScene();

        Scene & getCurrentScene() const;

        bool isAnySceneLoaded() const;

        Scene & getScene(ID id) const;

        Scene & getScene(const std::string &alias) const;

        iterator begin();

        iterator end();

        const_iterator begin() const;

        const_iterator end() const;

        const_iterator cbegin() const;

        const_iterator cend() const;
    };
}

#endif //DENGINE_SCENESMANAGER_H
