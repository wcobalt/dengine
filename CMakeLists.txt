cmake_minimum_required(VERSION 3.12)
project(Dengine)

set(CMAKE_CXX_STANDARD 17)

add_executable(App App/main.cpp)

add_library(Dengine
        Window/WindowManagerX.cpp
        Window/WindowManagerX.h
        Window/WindowManager.h

        Dengine.cpp
        Dengine.h
        Scene.cpp
        Scene.h
        GameObject.cpp
        GameObject.h
        ScenesManager.cpp
        ScenesManager.h
        DObject.h
        DengineAccessor.cpp
        DengineAccessor.h

        Components/Component.h
        Components/TransformComponent.cpp
        Components/TransformComponent.h
        Components/DefaultComponent.cpp
        Components/DefaultComponent.h

        Events/Keyboard/KeyboardState.h
        Events/Mouse/MouseState.h
        Events/Keyboard/Keyboard.h
        Events/Keyboard/Keyboard.cpp
        Events/Mouse/Mouse.h
        Events/Window/WindowState.h
        Events/Mouse/DefaultMouseState.cpp
        Events/Mouse/DefaultMouseState.h
        Events/Window/DefaultWindowState.cpp
        Events/Window/DefaultWindowState.h
        Events/Keyboard/DefaultKeyboardState.cpp
        Events/Keyboard/DefaultKeyboardState.h

        Exceptions/DengineException.h
        Exceptions/NoCurrentSceneException.cpp
        Exceptions/NoCurrentSceneException.h
        Exceptions/NoSuitableSceneException.cpp
        Exceptions/NoSuitableSceneException.h
        Exceptions/CurrentSceneRemovingException.cpp
        Exceptions/CurrentSceneRemovingException.h
        Exceptions/DengineIsNotInitializedException.cpp
        Exceptions/DengineIsNotInitializedException.h
        Exceptions/ComponentIsNotBoundException.cpp
        Exceptions/ComponentIsNotBoundException.h
        Exceptions/NoSuitableComponentException.cpp
        Exceptions/NoSuitableComponentException.h
        Exceptions/TransformComponentRemovingException.cpp
        Exceptions/TransformComponentRemovingException.h
        Exceptions/ComponentAlreadyAddedException.cpp
        Exceptions/ComponentAlreadyAddedException.h
        Exceptions/NoCastToComponentException.cpp
        Exceptions/NoCastToComponentException.h
        Exceptions/LessThanVectorException.h
        Exceptions/LessThanVectorException.cpp

        Geometry/Vector3.cpp
        Geometry/Vector3.h
        Geometry/Vector2.cpp
        Geometry/Vector2.h
        Geometry/Geometry.cpp
        Geometry/Geometry.h
        Geometry/Vector.h

        Coreutils/ID.h)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

find_package (Threads)

target_link_libraries(App Dengine ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
