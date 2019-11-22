//
// Created by wcobalt on 2/23/19.
//

#include <memory>
#include <unordered_map>

#ifndef DENGINE_TRANSFORMCOMPONENT_H
#define DENGINE_TRANSFORMCOMPONENT_H

namespace dengine {
    class GameObject;
    class Layer;
}

#include "../Component.h"
#include "../../Math/vectors.h"
#include "../../Math/Quaternion.h"

namespace dengine {
    class TransformComponent : public virtual Component {
    private:
        bool mIsActive;
        std::string tagName; //@todo i don't know is it worth to exclude tag in a separate class
        std::unordered_map<std::shared_ptr<Layer>, bool> layers;

        using const_layers_iterator = decltype(layers)::const_iterator;

        const_layers_iterator findLayer(std::shared_ptr<Layer> layer) const;

        vec3f position;
        Quaternion<float> rotation;
        vec3f scale;
    public:
        TransformComponent(std::shared_ptr<GameObject> gameObject);

        TransformComponent(std::shared_ptr<GameObject> gameObject, const vec3f& position);

        TransformComponent(std::shared_ptr<GameObject> gameObject, float x, float y, float z);

        TransformComponent(std::shared_ptr<GameObject> gameObject, const vec3f& position,
                const Quaternion<float>& rotation, const vec3f& scale);

        void setPosition(const vec3f& position);

        void setPosition(float x, float y, float z);

        void setRotation(const Quaternion<float>& rotation);

        void setScale(const vec3f& scale);

        void setScale(float x, float y, float z);

        vec3f getPosition() const;

        Quaternion<float> getRotation() const;

        vec3f getScale() const;

        Quaternion<float> up() const;

        Quaternion<float> forward() const;

        Quaternion<float> left() const;

        void addToLayer(std::shared_ptr<Layer> layer);

        bool isOnLayer(std::shared_ptr<Layer> layer) const;

        std::vector<std::shared_ptr<Layer>> getAllLayers() const {
            std::vector<std::shared_ptr<Layer>> result;

            for (auto& pair : layers)
                result.emplace_back(pair.first);

            return result;
        }

        void setTagName(const std::string& tagName);

        const std::string& getTagName() const {
            return tagName;
        }

        void setActive(bool isActive);

        bool isActive() const {
            return mIsActive;
        }
    };
}

#endif //DENGINE_TRANSFORMCOMPONENT_H
