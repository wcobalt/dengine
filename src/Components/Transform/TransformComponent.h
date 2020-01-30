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
        class SpacesContainer : public DObject {
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
            SpacesContainer& operator=(SpacesContainer& spacesManager) = delete;

            void addSpace(Space& space);

            void removeSpace(Space& space);

            Spaces buildSpaces() const;
        };
    private:
        bool mIsActive;

        vec3f position;
        Quat rotation;
        vec3f scale;

        SpacesContainer spacesManager;
    public:
        TransformComponent(GameObject &gameObject);

        TransformComponent(GameObject &gameObject, const vec3f& position);

        TransformComponent(GameObject &gameObject, float x, float y, float z);

        TransformComponent(GameObject &gameObject, const vec3f& position,
                           const Quat& rotation, const vec3f& scale);

        //absolute, doesnt move children
        void setPosition(const vec3f& position);

        void setPosition(float x, float y, float z);

        //relative to current position, doesnt move children
        void changePositionFor(const vec3f& delta);

        void changePositionFor(float x, float y, float z);

        //absolute, moves children
        void moveTo(const vec3f& position);

        void moveTo(float x, float y, float z);

        //relative to current position, moves children
        void moveFor(const vec3f& delta);

        void moveFor(float x, float y, float z);

        //relative to parent, doesnt move children
        void setRelativePosition(const vec3f& position);

        void setRelativePosition(float x, float y, float z);

        //relative to parent, moves children
        void moveToRelative(const vec3f& position);

        void moveToRelative(float x, float y, float z);

        vec3f getRelativePosition() const;

        vec3f getPosition() const;

        void setRotation(const Quat& rotation);

        void setScale(const vec3f& scale);

        void setScale(float x, float y, float z);

        Quat getRotation() const;

        vec3f getScale() const;

        Quat up() const;

        Quat front() const;

        Quat left() const;

        void onAdditionToSpace(Space& space);//add to SpacesContainer

        void onRemovalFromSpace(Space& space);//remove from SpacesContainer

        void addToSpace(Space& space);//just delegation

        void removeFromSpace(Space& space);//just delegation

        bool isInSpace(Space& space) const;//just delegation

        //inactive objects ignore incoming events, but can still be used other ways
        void setActive(bool isActive);

        SpacesContainer::Spaces getSpaces() const {
            return spacesManager.buildSpaces();
        }

        bool isActive() const {
            return mIsActive;
        }
    };
}

#endif //DENGINE_TRANSFORMCOMPONENT_H
