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
    class Layer;
}

#include "DObject.h"
#include "Coreutils/ID.h"
#include "SceneBehavior.h"
#include "Coreutils/Messages/ComponentMessage.h"
#include "GameObject.h"

namespace dengine {
    class Scene : public DObject, public std::enable_shared_from_this<Scene> {
    private:
        std::unique_ptr<GameObject> root;

        SceneBehavior& sceneBehavior;

        ID currentId, id;
        std::string alias;

        std::vector<std::shared_ptr<Layer>> baseLayers;

        void handle(GameObject::EventType messageType);

        void freeScene();

        using const_layer_iterator = decltype(baseLayers)::const_iterator;

        const_layer_iterator findLayer(const std::string& layerName) const;
    public:
        enum class EventType {
            UPDATE, SCENE_UNLOAD, SCENE_LOAD, GAME_END
        };

        static const unsigned BASE_NUMBERED_LAYERS_COUNT = 8;
        static const char BASE_NUMBERED_LAYER_PREFIX[];
        static const unsigned DEFAULT_BASE_NUMBERED_LAYER = 0;

        Scene(ID id, SceneBehavior &sceneBehavior);

        Scene(ID id, SceneBehavior &sceneBehavior, const std::string &alias);

        void handleExternalEvent(EventType eventType);

        ID takeNextId();

        std::shared_ptr<Layer> getBaseLayerByName(const std::string& layerName) const;

        std::shared_ptr<Layer> getBaseNumberedLayer(unsigned number) const;

        std::shared_ptr<Layer> getDefaultBaseNumberedLayer() const;

        GameObject & getRoot() const;

        const std::string& getAlias() const;

        ID getId() const;
    };
}

#endif //DENGINE_SCENE_H
