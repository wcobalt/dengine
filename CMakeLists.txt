cmake_minimum_required(VERSION 3.12)
project(Dengine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH lib)

add_executable(App
        src/App/main.cpp
        )

add_library(Dengine
        src/Components/Component.cpp
        src/Components/Transform/TransformComponent.cpp
        src/Components/Component.h
        src/Components/Transform/TransformComponent.h

        src/Dengine.cpp
        src/Dengine.h
        src/DObject.h
        src/DObject.cpp
        src/Scene.cpp
        src/Scene.h
        src/ScenesManager.cpp
        src/ScenesManager.h
        src/GameObject.cpp
        src/GameObject.h
        src/Platform/PlatformSet.h
        src/Coreutils/ID.h
        src/Coreutils/Messages/MessageType.h
        src/SceneBehavior.h
        src/SceneBehavior.cpp
        src/SceneBehavior.h

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
        src/Events/EventsState.cpp
        src/Events/EventsState.h

        src/Exceptions/IllegalStateException.h
        src/Exceptions/ImageException.h
        src/Exceptions/IOException.h
        src/Exceptions/IllegalArgumentException.h
        src/Exceptions/DengineException.h
        src/Exceptions/ComponentException.h
        src/Exceptions/SceneException.h
        src/Exceptions/GameObjectException.h

        src/Math/Vector3.h
        src/Math/vectors.h
        src/Math/Geometry.cpp
        src/Math/Vector2.h
        src/Math/Vector.h
        src/Math/Geometry.h
        src/Math/Number.h
        src/Math/Quaternion.h
        src/Math/Euler.h
        src/Math/Euler.cpp

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

        src/Filter/Filter.cpp
        src/Filter/Filter.h
        src/Initializer.h
        src/Components/Transform/TransformFilters.cpp
        src/Components/Transform/TransformFilters.h
        src/Components/Transform/TransformToolkit.cpp
        src/Components/Transform/TransformToolkit.h
        src/Exceptions/LayerException.h
        src/Layer.cpp
        src/Layer.h
        src/Coreutils/Messages/Message.cpp src/Coreutils/Messages/Message.h src/Coreutils/Messages/DirectChildrenChangeMessage.cpp src/Coreutils/Messages/DirectChildrenChangeMessage.h src/Coreutils/Messages/ParentChangeMessage.cpp src/Coreutils/Messages/ParentChangeMessage.h src/ComponentsManager.cpp src/ComponentsManager.h)


find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

include_directories(lib/png)
find_library(LIB_PNG png)

find_package (Threads)

target_link_libraries(App Dengine ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${LIB_PNG})