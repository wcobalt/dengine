//
// Created by wcobalt on 2/23/19.
//

#include <memory>

#ifndef DENGINE_TRANSFORMCOMPONENT_H
#define DENGINE_TRANSFORMCOMPONENT_H

namespace dengine {
    class GameObject;
}

#include "Component.h"
#include "../Math/vectors.h"
#include "../Math/Quaternion.h"

namespace dengine {
    class TransformComponent : public virtual Component {
    public:
        vec3f position;
        Quaternion<float> rotation;
        vec3f scale;

        TransformComponent(std::shared_ptr<GameObject> gameObject);

        TransformComponent(std::shared_ptr<GameObject> gameObject, const vec3f& position);

        TransformComponent(std::shared_ptr<GameObject> gameObject, float x, float y, float z);

        TransformComponent(std::shared_ptr<GameObject> gameObject, const vec3f& position,
                const Quaternion<float>& rotation, const vec3f& scale);

        //layer - class

        //tag - string???

        //isActive

        /*
         * class filters {
         *      public:
         *      void filter2d(vec2, vec2, std::func(void(GO));
         * }
         * */
/*        void filter2d(float x0, float y0, float x1, float y1, FilterAction& filterAction);

        void filter2d(vec2f point0, vec2f point1, FilterAction& filterAction);

        void filter3d(float x0, float y0, float z0, float x1, float y1, float z1, FilterAction& filterAction);

        void filter3d(vec3f point0, vec3f point1, FilterAction& filterAction);*/

        //@todo what's about calculation distance to a transformComponent rather than a gameObject?
        double getDistanceTo(std::shared_ptr<GameObject> instance) const;

        double getDistanceTo(const vec3f& position) const;

        template<typename T>
        std::shared_ptr<GameObject> getNearestInstance() const;
    };
}

#endif //DENGINE_TRANSFORMCOMPONENT_H
