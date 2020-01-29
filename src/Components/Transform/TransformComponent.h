//
// Created by wcobalt on 2/23/19.
//

#include <memory>
#include <unordered_map>
#include <set>

#ifndef DENGINE_TRANSFORMCOMPONENT_H
#define DENGINE_TRANSFORMCOMPONENT_H

namespace dengine {
    class GameObject;
    class Space;
}

#include "../Component.h"
#include "../../Math/vectors.h"
#include "../../Math/Quaternion.h"

namespace dengine {
    class TransformComponent final : public virtual Component {
    public:
        class SpacesManager : public DObject {
        private:
            std::set<Space*> spaces;
        public:
            class Spaces : public DObject {
            private:
                using spaces_type = std::set<Space*>;

                spaces_type & spaces;
            public:
                Spaces(spaces_type& spaces);

                using iterator = spaces_type::iterator;
                using const_iterator = spaces_type::const_iterator;

                iterator begin();

                iterator end();

                const_iterator begin() const;

                const_iterator end() const;

                const_iterator cbegin() const;

                const_iterator cend() const;
            };
        public:
            SpacesManager& operator=(SpacesManager& spacesManager) = delete;

            void addSpace(Space& space);

            void removeSpace(Space& space);

            Spaces buildSpaces() const;
        };
    private:
        bool mIsActive;

        vec3f position;
        Quaternion<float> rotation;
        vec3f scale;

        SpacesManager spacesManager;
    public:
        TransformComponent(GameObject &gameObject);

        TransformComponent(GameObject &gameObject, const vec3f& position);

        TransformComponent(GameObject &gameObject, float x, float y, float z);

        TransformComponent(GameObject &gameObject, const vec3f& position,
                           const Quaternion<float>& rotation, const vec3f& scale);

        void setPosition(const vec3f& position);

        void setPosition(float x, float y, float z);

        void moveFor(const vec3f& position);

        void moveFor(float x, float y, float z);

        void setRelativePosition(const vec3f& position);

        void setRelativePosition(float x, float y, float z);

        vec3f getRelativePosition() const;

        void setRotation(const Quaternion<float>& rotation);

        void setScale(const vec3f& scale);

        void setScale(float x, float y, float z);

        vec3f getPosition() const;

        Quaternion<float> getRotation() const;

        vec3f getScale() const;

        Quaternion<float> up() const;

        Quaternion<float> front() const;

        Quaternion<float> left() const;

        void onAdditionToSpace(Space& space);//add to spacesmanager

        void onRemovalFromSpace(Space& space);//remove from spacesmanager

        void addToSpace(Space& space);//just delegation

        void removeFromSpace(Space& space);//just delegation

        bool isInSpace(Space& space) const;//just delegation


        //inactive objects ignore incoming events, but can still be used other ways
        void setActive(bool isActive);

        SpacesManager::Spaces getSpaces() const {
            return std::move(spacesManager.buildSpaces());//RVO?
        }

        bool isActive() const {
            return mIsActive;
        }
    };
}

#endif //DENGINE_TRANSFORMCOMPONENT_H
