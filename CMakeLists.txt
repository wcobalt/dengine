cmake_minimum_required(VERSION 3.12)
project(Dengine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH lib)

add_executable(App src/App/main.cpp src/Exceptions/InvalidArgumentException.cpp src/Exceptions/InvalidArgumentException.h src/Exceptions/InvalidStateException.cpp src/Exceptions/InvalidStateException.h src/Graphics/PNG/DefaultPngLoader.cpp src/Graphics/PNG/DefaultPngLoader.h src/Graphics/PNG/Exceptions/PngException.cpp src/Graphics/PNG/Exceptions/PngException.h)

#[[add_library(Dengine
        src/Platform/Window/X/WindowManagerX.cpp
        src/Platform/Window/X/WindowManagerX.h
        src/Platform/Window/WindowManager.h

        src/Events/Keyboard/KeyboardState.h
        src/Events/Mouse/MouseState.h
        src/Events/Keyboard/Keyboard.cpp
        src/Events/Window/WindowState.h
        src/Events/Mouse/DefaultMouseState.cpp
        src/Events/Mouse/DefaultMouseState.h
        src/Events/Window/DefaultWindowState.cpp
        src/Events/Window/DefaultWindowState.h
        src/Events/Keyboard/DefaultKeyboardState.cpp
        src/Events/Keyboard/DefaultKeyboardState.h
        src/Events/Keyboard/Keyboard.h
        src/Events/Keyboard/Key.h
        src/Events/Keyboard/DKey.cpp
        src/Events/Keyboard/DKey.h
        src/Events/Keyboard/KeyByDKeyCodeComparator.cpp
        src/Events/Keyboard/KeyByDKeyCodeComparator.h
        src/Events/Keyboard/KeyBySymbolComparator.cpp
        src/Events/Keyboard/KeyBySymbolComparator.h

        src/Platform/Window/WindowManager.cpp src/Events/Keyboard/KeyComparator.h src/Events/Mouse/MouseStateBuilder.h src/Events/Mouse/Mouse.h src/Events/Mouse/DefaultMouseStateBuilder.cpp src/Events/Mouse/DefaultMouseStateBuilder.h src/Events/Window/WindowStateBuilder.h src/Events/Window/DefaultWindowStateBuilder.cpp src/Events/Window/DefaultWindowStateBuilder.h
        src/Events/Keyboard/KeyboardStateBuilder.h
        src/Events/Keyboard/DefaultKeyboardStateBuilder.h
        src/Events/Keyboard/DefaultKeyboardStateBuilder.cpp
        src/Platform/Window/X/Util/XKeyboardConverter.h
        src/Platform/Window/X/Exceptions/XException.cpp
        src/Platform/Window/X/Exceptions/XException.h
        src/Platform/Window/X/Util/XKeyboardConverter.h
        src/Platform/Window/X/Util/XDefaultKeyboardConverter.h
        src/Platform/Window/X/Util/XDefaultKeyboardConverter.cpp
        src/Exceptions/DengineException.h
        src/Exceptions/DengineException.cpp
        src/Exceptions/IOException.cpp src/Exceptions/IOException.h)]]

add_library(PNG src/Graphics/PNG/PngLoader.h
            src/Graphics/Image.h src/Graphics/Pixel.h src/Graphics/DefaultPixel.cpp        src/Exceptions/DengineException.h
        src/Exceptions/DengineException.cpp src/Graphics/DefaultPixel.h src/Graphics/DefaultImage.cpp src/Graphics/DefaultImage.h src/Graphics/ImageBuilder.h src/Graphics/DefaultImageBuilder.cpp src/Graphics/DefaultImageBuilder.h)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

include_directories(lib/png)
find_library(LIB_PNG png)

find_package (Threads)

target_link_libraries(App PNG #[[${X11_LIBRARIES} ${OPENGL_LIBRARIES}]] ${CMAKE_THREAD_LIBS_INIT} ${LIB_PNG})