//
// Created by wcobalt on 2/2/20.
//

#ifndef DENGINE_SPACEFILTER_H
#define DENGINE_SPACEFILTER_H

#include "../../Filter/CustomFilter.h"

namespace dengine {
    class Space;
}

//only for use in FilterSet. If you want to obtain objects of particular Space, use begin() end() methods of it.
namespace dengine {
    class SpaceFilter : public CustomFilter {
    private:
        const Space& space;
    public:
        explicit SpaceFilter(const Space & space);

        void init(CustomFilter::action_type action, std::unique_ptr<TraversalMethod> traversalMethod);

        const Space& getSpace() const;
    };
}

#endif //DENGINE_SPACEFILTER_H
