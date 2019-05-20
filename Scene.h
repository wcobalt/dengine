//
// Created by wcobalt on 19.09.18.
//

#include <string>
#include <map>
#include <memory>

#ifndef DENGINE_SCENE_H
#define DENGINE_SCENE_H

#include "DObject.h"
#include "GameObject.h"
#include "DengineAccessor.h"

namespace dengine {
    class Scene : public DObject {
    public:
        const float ROOT_GAME_OBJECT_X = 0;
        const float ROOT_GAME_OBJECT_Y = 0;
        const float ROOT_GAME_OBJECT_Z = 0;
    private:
        std::shared_ptr<dengine::GameObject> root;

        void deleteInstance(std::shared_ptr<dengine::GameObject> instance, bool isSceneUnloading);
    protected:
        virtual void sceneLoad(dengine::DengineAccessor dengineAccessor);
        virtual void sceneUnload(dengine::DengineAccessor dengineAccessor);
    public:
        Scene();

        void placeInstance(std::shared_ptr<dengine::GameObject> instance);

        void placeInstance(std::shared_ptr<dengine::GameObject> instance, float x, float y);
        void placeInstance(std::shared_ptr<dengine::GameObject> instance, float x, float y, float z);

        void destroyInstance(std::shared_ptr<dengine::GameObject> instance);

        void update(dengine::DengineAccessor dengineAccessor);

        void create(dengine::DengineAccessor dengineAccessor);

        void destroy(dengine::DengineAccessor dengineAccessor);

        template <class T>
        std::vector<std::shared_ptr<GameObject>> getInstances() const;

        std::shared_ptr<dengine::GameObject> getRoot() const;
    };
}

#endif //DENGINE_SCENE_H
