//
// Created by wcobalt on 2/1/20.
//

#ifndef DENGINE_DISTANCEFILTER_H
#define DENGINE_DISTANCEFILTER_H

#include "../../Filter/CustomFilter.h"
#include "../../Filter/TraversalMethods/BfsTraversal.h"
#include "../../Math/vectors.h"

namespace dengine {
    class DistanceFilter : public CustomFilter {
    private:
        float maximalDistance, minimalDistance;
        vec3f origin;

    public:
        enum class Distance {
            MINIMAL, MAXIMAL
        };

        void init(vec3f origin, float distance, Distance type, action_type action,
                  std::unique_ptr<TraversalMethod> traversalMethod = std::make_unique<BfsTraversal>());

        void init(vec3f origin, float minimalDistance, float maximalDistance, CustomFilter::action_type action,
                  std::unique_ptr<TraversalMethod> traversalMethod = std::make_unique<BfsTraversal>());

        float getMinimalDistance() const;

        float getMaximalDistance() const;

        const vec3f& getOrigin() const;
    };
}

#endif //DENGINE_DISTANCEFILTER_H
