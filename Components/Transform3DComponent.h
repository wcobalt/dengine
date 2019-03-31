//
// Created by wcobalt on 2/23/19.
//

#include <memory>

#ifndef DENGINE_TRANSFORM3DCOMPONENT_H
#define DENGINE_TRANSFORM3DCOMPONENT_H

#include "DefaultComponent.h"
#include "../GameObject.h"
#include "../Dengine.h"
#include "../Geometry/vectors.h"

namespace dengine::components {
    using namespace dengine::geometry;
    using namespace dengine;
    using std::shared_ptr;

    class Transform3DComponent : public DefaultComponent {
    private:
        vec3f position;
        vec3f rotation;
        vec3f scale;
    public:
        Transform3DComponent();
        Transform3DComponent(vec3f position);
        Transform3DComponent(float x, float y, float z);
        Transform3DComponent(vec3f position, vec3f rotation, vec3f scale);

        virtual void componentUnload();

        virtual void update();

        virtual void instanceCreate();

        virtual void instanceDestroy();

        void setPosition(float x, float y, float z);
        void setPosition(vec3f vec);
        void setRotation(float x, float y, float z);
        void setRotation(vec3f vec);
        void setScale(float x, float y, float z);
        void setScale(vec3f vec);

        vec3f getPosition() const;
        vec3f getRotation() const;
        vec3f getScale() const;

        double getDistanceTo(shared_ptr<GameObject> instance) const;
        double getDistanceTo(vec3f position) const;

        template <class T>
        shared_ptr<GameObject> getNearestInstance() const;
    };
}

#endif //DENGINE_TRANSFORM3DCOMPONENT_H
