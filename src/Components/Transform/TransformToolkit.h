//
// Created by wcobalt on 11/21/19.
//

#ifndef DENGINE_TRANSFORMTOOLKIT_H
#define DENGINE_TRANSFORMTOOLKIT_H

namespace dengine {
    class TransformToolkit {
    public:
        //@todo what's about calculation distance to a transformComponent rather than a gameObject?
        double getDistanceTo(std::shared_ptr<GameObject> instance) const;

        double getDistanceTo(const vec3f& position) const;

        template<typename T>
        std::shared_ptr<GameObject> getNearestInstance() const;
    };
}

#endif //DENGINE_TRANSFORMTOOLKIT_H
