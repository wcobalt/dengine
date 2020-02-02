//
// Created by wcobalt on 2/1/20.
//

#ifndef DENGINE_RECTANGLEFILTER_H
#define DENGINE_RECTANGLEFILTER_H

#include "../../Filter/CustomFilter.h"
#include "../../Math/vectors.h"
#include "../../Filter/TraversalMethods/BfsTraversal.h"

namespace dengine {
    class RectangleFilter : public CustomFilter {
    private:
        vec3f from, to;
    public:
        void init(float x1, float y1, float x2, float y2, CustomFilter::action_type action,
                        std::unique_ptr<TraversalMethod> traversalMethod = std::make_unique<BfsTraversal>());

        void init(vec2f point1, vec2f point2, CustomFilter::action_type action,
                        std::unique_ptr<TraversalMethod> traversalMethod = std::make_unique<BfsTraversal>());

        void init(float x1, float y1, float z1, float x2, float y2, float z2, CustomFilter::action_type action,
                        std::unique_ptr<TraversalMethod> traversalMethod = std::make_unique<BfsTraversal>());

        void init(vec3f point1, vec3f point2, CustomFilter::action_type action,
                        std::unique_ptr<TraversalMethod> traversalMethod = std::make_unique<BfsTraversal>());

        const vec3f& getFromPoint() const;

        const vec3f& getToPoint() const;
    };
}

#endif //DENGINE_RECTANGLEFILTER_H
