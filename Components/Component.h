//
// Created by wcobalt on 19.09.18.
//

#ifndef DENGINE_COMPONENT_H
#define DENGINE_COMPONENT_H


class Component {
public:
    virtual void gameStart() = 0;
    virtual void update() = 0;
    virtual void gameEnd() = 0;
    virtual void create() = 0;
    virtual void destroy() = 0;
};


#endif //DENGINE_COMPONENT_H
