//
// Created by wcobalt on 19.09.18.
//

#include "../ID.h"

#ifndef DENGINE_COMPONENT_H
#define DENGINE_COMPONENT_H


class Component {
private:
    ID *id;
public:
    Component(ID *id);
    ID *getID();
    virtual void gameStart() = 0;
    virtual void update() = 0;
    virtual void gameEnd() = 0;
    virtual void create() = 0;
    virtual void destroy() = 0;
};


#endif //DENGINE_COMPONENT_H
