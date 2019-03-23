//
// Created by wcobalt on 19.09.18.
//
#include <string>

#ifndef DENGINE_COMPONENT_H
#define DENGINE_COMPONENT_H

namespace dengine::components {
    class Component {
    private:
        const std::string &id;
        bool mIsOnly;
        bool mIsEnabled;
    public:
        Component(const std::string &id);

        virtual void sceneLoad() = 0;

        virtual void sceneUnload() = 0;

        virtual void componentLoad() = 0;

        virtual void componentUnload() = 0;

        virtual void update() = 0;

        virtual void create() = 0;

        virtual void destroy() = 0;

        virtual void draw() = 0;//????
        void setOnly(bool isOnly);

        bool isOnly() const;

        void setEnabled(bool isEnabled);

        bool isEnabled() const;

        const std::string &getID() const;
        //@todo is compoennt neccessary required option? (in GameObject?)
    };
}

#endif //DENGINE_COMPONENT_H
