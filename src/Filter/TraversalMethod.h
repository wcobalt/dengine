//
// Created by wcobalt on 1/23/20.
//

#ifndef DENGINE_TRAVERSALMETHOD_H
#define DENGINE_TRAVERSALMETHOD_H

namespace dengine {
    class GameObject;
    class Filter;
}

namespace dengine {
    class TraversalMethod {
    public:
        virtual void run(GameObject &gameObject) = 0;

        virtual void stop() = 0;

        virtual bool isStopped() const = 0;

        virtual const Filter& getFilter() const = 0;
    };
}

#endif //DENGINE_TRAVERSALMETHOD_H