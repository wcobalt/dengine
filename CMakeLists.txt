cmake_minimum_required(VERSION 3.12)
project(Dengine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH lib)

add_executable(App
        src/App/main.cpp
        src/Filter/TraversalMethods/BfsTraversal.cpp src/Filter/TraversalMethods/BfsTraversal.h src/Filter/TraversalMethods/BaseTraversal.cpp src/Filter/TraversalMethods/BaseTraversal.h src/Filter/TraversalMethods/DfsTraversal.cpp src/Filter/TraversalMethods/DfsTraversal.h src/Platform/XPlatformBuilder.cpp src/Platform/XPlatformBuilder.h src/Platform/Platform.cpp src/Platform/PlatformBuilder.h)

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
        src/Platform/Platform.h
        src/Coreutils/ID.h
        src/SceneBehavior.h
        src/SceneBehavior.cpp
        src/SceneBehavior.h

        src/Events/Window/DefaultWindowStateBuilder.h
        src/Events/Window/DefaultWindowStateBuilder.cpp
        src/Events/Window/DefaultWindowState.h
        src/Events/Window/DefaultWindowState.cpp
        src/Events/Window/WindowStateBuilder.h
        src/Events/Window/WindowState.h
        src/Events/Keyboard/KeyboardStateBuilder.h
        src/Events/Keyboard/DefaultKeyboardState.cpp
        src/Events/Keyboard/DefaultKeyboardState.h
        src/Events/Keyboard/DKey.h
        src/Events/Keyboard/Keyboard.cpp
        src/Events/Keyboard/Keyboard.h
        src/Events/Keyboard/DefaultKeyboardStateBuilder.cpp
        src/Events/Keyboard/DKey.cpp
        src/Events/Keyboard/KeyboardState.h
        src/Events/Keyboard/Key.h
        src/Events/Keyboard/DefaultKeyboardStateBuilder.h
        src/Events/Mouse/DefaultMouseStateBuilder.h
        src/Events/Mouse/MouseState.h
        src/Events/Mouse/Mouse.h
        src/Events/Mouse/DefaultMouseStateBuilder.cpp
        src/Events/Mouse/MouseStateBuilder.h
        src/Events/Mouse/DefaultMouseState.h
        src/Events/Mouse/DefaultMouseState.cpp
        src/Events/Events.cpp
        src/Events/Events.h

        src/Exceptions/IllegalStateException.h
        src/Exceptions/ImageException.h
        src/Exceptions/IOException.h
        src/Exceptions/IllegalArgumentException.h
        src/Exceptions/DengineException.h
        src/Exceptions/ComponentException.h
        src/Exceptions/SceneException.h
        src/Exceptions/GameObjectException.h
        src/Exceptions/SpaceException.h
        src/Exceptions/PlatformBuildException.h

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

        src/Filter/CustomFilter.cpp
        src/Filter/Filter.h
        src/Initializer.h
        src/Components/Transform/TransformFilters.cpp
        src/Components/Transform/TransformFilters.h
        src/Components/Transform/TransformToolkit.cpp
        src/Components/Transform/TransformToolkit.h
        src/Coreutils/Messages/ComponentMessage.cpp src/Coreutils/Messages/ComponentMessage.h src/Coreutils/Messages/DirectChildrenChangeMessage.cpp src/Coreutils/Messages/DirectChildrenChangeMessage.h src/Coreutils/Messages/ParentChangeMessage.cpp src/Coreutils/Messages/ParentChangeMessage.h src/ComponentsManager.cpp src/ComponentsManager.h src/Coreutils/Messages/ComponentMessages.cpp src/Coreutils/Messages/ComponentMessages.h src/Filter/CustomFilter.h src/Filter/TraversalMethod.h src/Space.cpp src/Space.h src/SpacesManager.cpp src/SpacesManager.h)


find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

include_directories(lib/png)
find_library(LIB_PNG png)

find_package (Threads)

target_link_libraries(App Dengine ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${LIB_PNG})