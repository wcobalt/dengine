cmake_minimum_required(VERSION 3.12)
project(Dengine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH lib)

add_executable(App
        src/App/main.cpp
        )

add_library(Dengine
        src/Components/BaseComponent.cpp
        src/Components/TransformComponent.cpp
        src/Components/BaseComponent.h
        src/Components/TransformComponent.h
        src/Components/Component.h

        src/DengineAccessor.cpp
        src/DengineAccessor.h
        src/Dengine.cpp
        src/Dengine.h
        src/DObject.h
        src/Scene.cpp
        src/Scene.h
        src/ScenesManager.cpp
        src/ScenesManager.h
        src/GameObject.cpp
        src/GameObject.h
        src/Platform/PlatformSet.h
        src/Coreutils/ID.h

        src/Events/Window/DefaultWindowStateBuilder.h
        src/Events/Window/DefaultWindowStateBuilder.cpp
        src/Events/Window/DefaultWindowState.h
        src/Events/Window/DefaultWindowState.cpp
        src/Events/Window/WindowStateBuilder.h
        src/Events/Window/WindowState.h
        src/Events/Keyboard/KeyBySymbolComparator.h
        src/Events/Keyboard/KeyboardStateBuilder.h
        src/Events/Keyboard/KeyBySymbolComparator.cpp
        src/Events/Keyboard/DefaultKeyboardState.cpp
        src/Events/Keyboard/DefaultKeyboardState.h
        src/Events/Keyboard/DKey.h
        src/Events/Keyboard/Keyboard.cpp
        src/Events/Keyboard/KeyByDKeyCodeComparator.cpp
        src/Events/Keyboard/Keyboard.h
        src/Events/Keyboard/DefaultKeyboardStateBuilder.cpp
        src/Events/Keyboard/KeyByDKeyCodeComparator.h
        src/Events/Keyboard/DKey.cpp
        src/Events/Keyboard/KeyboardState.h
        src/Events/Keyboard/Key.h
        src/Events/Keyboard/KeyComparator.h
        src/Events/Keyboard/DefaultKeyboardStateBuilder.h
        src/Events/Mouse/DefaultMouseStateBuilder.h
        src/Events/Mouse/MouseState.h
        src/Events/Mouse/Mouse.h
        src/Events/Mouse/DefaultMouseStateBuilder.cpp
        src/Events/Mouse/MouseStateBuilder.h
        src/Events/Mouse/DefaultMouseState.h
        src/Events/Mouse/DefaultMouseState.cpp

        src/Exceptions/IllegalStateException.h
        src/Exceptions/ImageException.h
        src/Exceptions/IOException.h
        src/Exceptions/IllegalArgumentException.h
        src/Exceptions/DengineException.h
        src/Exceptions/ComponentException.h
        src/Exceptions/SceneException.h

        src/Math/Vector3.h
        src/Math/vectors.h
        src/Math/Geometry.cpp
        src/Math/Vector2.h
        src/Math/Vector.h
        src/Math/Geometry.h

        src/Graphics/ImageIO.h
        src/Graphics/PNG/PngLoader.h
        src/Graphics/PNG/Exceptions/PngException.h
        src/Graphics/PNG/PngLoader.cpp
        src/Graphics/ImageBuilder.h
        src/Graphics/DefaultImageBuilder.h
        src/Graphics/ImageLoader.h
        src/Graphics/Image.h
        src/Graphics/DefaultImageIO.h
        src/Graphics/DefaultImage.h
        src/Graphics/DefaultImage.cpp
        src/Graphics/DefaultImageBuilder.cpp
        src/Graphics/DefaultImageIO.cpp

        src/Platform/Window/X/Exceptions/XException.h
        src/Platform/Window/X/Util/XDefaultKeyboardConverter.h
        src/Platform/Window/X/Util/XDefaultKeyboardConverter.cpp
        src/Platform/Window/X/Util/XKeyboardConverter.h
        src/Platform/Window/X/WindowManagerX.cpp
        src/Platform/Window/X/WindowManagerX.h
        src/Platform/Window/WindowManager.h

        src/Platform/Input/GamepadManager.cpp
        src/Platform/Input/GamepadManager.h

        src/Platform/Network/NetworkManager.cpp
        src/Platform/Network/NetworkManager.h

        src/Platform/Audio/AudioManager.h
        src/Platform/Audio/AudioManager.cpp
        src/DObject.cpp src/Math/Number.h src/Math/Quaternion.h src/Math/Euler.h src/Math/Euler.cpp)


find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

include_directories(lib/png)
find_library(LIB_PNG png)

find_package (Threads)

target_link_libraries(App Dengine ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${LIB_PNG})