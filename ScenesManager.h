//
// Created by wcobalt on 3/30/19.
//

#include <map>
#include <memory>

#ifndef DENGINE_SCENESMANAGER_H
#define DENGINE_SCENESMANAGER_H

#include "Coreutils/ID.h"
#include "Scene.h"

namespace dengine {
    using std::shared_ptr;
    using std::map;

    class ScenesManager {
    public:
        static const ID NOT_EXIST_SCENE = 0;
    private:
        map<ID, Entry<String, Scene>> scenesIds;
        map<String, Entry<ID, Scene>> scenesAliases;

        Entry<ID, Scene> currentScene;

        ID nextSceneId;

        void setCurrentScene(Entry<ID, Scene> scene);
        ID getUniqueSceneId();
    public:
        ScenesManager();

        void update();

        ID addScene(shared_ptr<Scene> scene);
        ID addScene(shared_ptr<Scene> scene, String alias);

        void removeScene(ID id);
        void removeScene(String alias);

        void loadScene(ID id);
        void loadScene(String alias);

        ID getCurrentSceneID() const;

        shared_ptr<Scene> getCurrentScene() const;

        shared_ptr<Scene> getScene(ID id) const;
        shared_ptr<Scene> getScene(String alias) const;

        ID getIDByAlias(String alias) const;
        String getAliasByID(ID id) const;
    };
}

#endif //DENGINE_SCENESMANAGER_H
