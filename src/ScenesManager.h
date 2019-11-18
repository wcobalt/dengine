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
        class SceneEntry {
        private:
            ID id;
            std::string alias;
            std::shared_ptr<Scene> scene;
        public:
            SceneEntry(ID id, const std::string& alias, std::shared_ptr<Scene> scene);

            ID getId();

            std::string getAlias();

            std::shared_ptr<Scene> getScene();
        };

        std::vector<std::shared_ptr<SceneEntry>> scenes;

        std::shared_ptr<SceneEntry> currentScene;

        ID currentId;

        ID takeNextSceneId();

        using scene_iterator = decltype(scenes)::iterator;

        scene_iterator findSceneByAlias(const std::string& alias) const;

        scene_iterator findSceneById(ID id) const;

        void removeScene(scene_iterator iterator);

        void loadScene(scene_iterator iterator);
    public:
        ScenesManager();

        void sendMessage(ScenesManagerMessage message);

        ID addScene(SceneBehavior &sceneBehavior);

        ID addScene(SceneBehavior &sceneBehavior, const std::string &alias);

        void removeScene(ID id);

        void removeScene(const std::string& alias);

        void loadScene(ID id);

        void loadScene(const std::string& alias);

        void restartScene();

        void loadNextScene();

        void loadPreviousScene();

        void loadFirstScene();

        ID getCurrentSceneID() const;

        std::string getCurrentSceneAlias() const;

        Scene& getCurrentScene() const;

        bool isCurrentSceneExist() const;

        Scene& getScene(ID id) const;

        Scene& getScene(const std::string& alias) const;

        ID getIdByAlias(const std::string &alias) const;

        std::string getAliasById(ID id) const;
    };
}

#endif //DENGINE_SCENESMANAGER_H
