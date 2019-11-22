//
// Created by wcobalt on 11/21/19.
//

#ifndef DENGINE_TRANSFORMFILTERS_H
#define DENGINE_TRANSFORMFILTERS_H

#include "../../Math/vectors.h"

namespace dengine {
    class TransformFilters {
    public:
        void filter2d(float x0, float y0, float x1, float y1, FilterAction& filterAction);

        void filter2d(vec2f point0, vec2f point1, FilterAction& filterAction);

        void filter3d(float x0, float y0, float z0, float x1, float y1, float z1, FilterAction& filterAction);

        void filter3d(vec3f point0, vec3f point1, FilterAction& filterAction);

        void filterByMaximalDistance(double maximalDistance, filterAction);

        void filterByMinimalDistance(double minimalDistamce, filterAction);
    };
}

#endif //DENGINE_TRANSFORMFILTERS_H
