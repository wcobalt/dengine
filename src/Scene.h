//
// Created by wcobalt on 19.09.18.
//

#include <string>
#include <map>
#include <memory>
#include <unordered_map>
#include <functional>

#ifndef DENGINE_SCENE_H
#define DENGINE_SCENE_H

namespace dengine {
    class Space;
    class SceneBehavior;
    class SpacesManager;
}

#include "DObject.h"
#include "Coreutils/ID.h"
#include "GameObject.h"

namespace dengine {
    class Scene : public DObject {
    private:
        std::unique_ptr<GameObject> root;
        std::unique_ptr<SceneBehavior> sceneBehavior;

        const ID INIT_ID = IDUtils::NO_ID;

        ID currentId = INIT_ID, id;
        std::string alias;

        void handle(GameObject::EventType messageType);

        void freeScene();

        void initializeSpaces();
    public:
        enum class StandardSpace {
            GLOBAL
        };
    private:
        std::unique_ptr<SpacesManager> spacesManager;

        mutable std::unordered_map<StandardSpace, Space*> standardSpaces;
    public:
        enum class EventType {
            UPDATE, SCENE_UNLOAD, SCENE_LOAD, GAME_END
        };

        Scene(ID id, std::unique_ptr<SceneBehavior> sceneBehavior);

        Scene(ID id, std::unique_ptr<SceneBehavior> sceneBehavior, std::string alias);

        void handleExternalEvent(EventType eventType);

        ID takeNextId();

        GameObject & getRoot() const;

        const std::string& getAlias() const;

        ID getId() const;

        //tell me if this violates SRP
        Space& getSpace(StandardSpace standardSpace) const;

        SpacesManager& getSpacesManager() const;

        SceneBehavior& getBehavior() const;
    };
}

#endif //DENGINE_SCENE_H
