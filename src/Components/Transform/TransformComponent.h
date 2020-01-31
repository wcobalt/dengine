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
    class TransformToolkit;
}

#include "../Component.h"
#include "../../Math/vectors.h"
#include "../../Math/Quaternion.h"

namespace dengine {
    class TransformComponent final : public virtual Component {
    public:
        class SpacesContainer : public DObject {
        private:
            mutable std::set<Space*> spaces;
        public:
            class Spaces : public DObject {
            private:
                using spaces_type = std::set<Space*>;

                spaces_type & spaces;
            public:
                explicit Spaces(spaces_type& spaces);

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
            void addSpace(Space& space);

            void removeSpace(Space& space);

            Spaces buildSpaces() const;
        };
    private:
        bool mIsActive;

        vec3f position;
        Quat rotation;
        vec3f scale;

        std::unique_ptr<SpacesContainer> spacesContainer;
        std::unique_ptr<TransformToolkit> transformToolkit;
    public:
        explicit TransformComponent(GameObject &gameObject);

        TransformComponent(GameObject &gameObject, vec3f position);

        TransformComponent(GameObject &gameObject, float x, float y, float z);

        TransformComponent(GameObject &gameObject, vec3f position,
                           Quat rotation, vec3f scale);

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

        const vec3f & getPosition() const;

        void setRotation(const Quat& rotation);

        void setScale(const vec3f& scale);

        void setScale(float x, float y, float z);

        const Quat & getRotation() const;

        const vec3f & getScale() const;

        vec3f up() const;

        vec3f front() const;

        vec3f left() const;

        void onAdditionToSpace(Space& space);//add to SpacesContainer

        void onRemovalFromSpace(Space& space);//remove from SpacesContainer

        //inactive objects ignore incoming events, but can still be used other ways
        void setActive(bool isActive);

        TransformComponent::SpacesContainer::Spaces getSpaces() const;

        TransformToolkit & getTransformToolkit() const;

        bool isActive() const;
    };
}

#endif //DENGINE_TRANSFORMCOMPONENT_H
