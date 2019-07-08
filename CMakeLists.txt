cmake_minimum_required(VERSION 3.12)
project(Dengine)

set(CMAKE_CXX_STANDARD 17)

add_executable(App src/App/main.cpp)

add_library(Dengine
        src/Platform/Window/X/Exceptions/CouldNotOpenXDisplayException.cpp
        src/Platform/Window/X/Exceptions/CouldNotOpenXDisplayException.h
        src/Platform/Window/X/Exceptions/NoSuitableXVisualInfoException.cpp
        src/Platform/Window/X/Exceptions/NoSuitableXVisualInfoException.h
        src/Platform/Window/X/WindowManagerX.cpp
        src/Platform/Window/X/WindowManagerX.h
        src/Platform/Window/WindowManager.h

        src/Events/Keyboard/KeyboardState.h
        src/Events/Mouse/MouseState.h
        src/Events/Keyboard/KeyCode.cpp
        src/Events/Window/WindowState.h
        src/Events/Mouse/DefaultMouseState.cpp
        src/Events/Mouse/DefaultMouseState.h
        src/Events/Window/DefaultWindowState.cpp
        src/Events/Window/DefaultWindowState.h
        src/Events/Keyboard/DefaultKeyboardState.cpp
        src/Events/Keyboard/DefaultKeyboardState.h
        src/Events/Keyboard/KeyCode.h
        src/Events/Keyboard/Key.h
        src/Events/Keyboard/DKey.cpp
        src/Events/Keyboard/DKey.h
        src/Events/Keyboard/KeyByDKeyCodeComparator.cpp
        src/Events/Keyboard/KeyByDKeyCodeComparator.h
        src/Events/Keyboard/KeyBySymbolComparator.cpp
        src/Events/Keyboard/KeyBySymbolComparator.h

        src/Platform/Window/WindowManager.cpp src/Platform/Window/X/Exceptions/UnableToCreateGLXContextException.cpp src/Platform/Window/X/Exceptions/UnableToCreateGLXContextException.h src/Platform/Window/X/Exceptions/UnableToAttachGLXContextToWindow.cpp src/Platform/Window/X/Exceptions/UnableToAttachGLXContextToWindow.h src/Platform/Window/X/Exceptions/TraySpecificationIsNotSupportedException.cpp src/Platform/Window/X/Exceptions/TraySpecificationIsNotSupportedException.h src/Events/Keyboard/KeyComparator.h src/Events/Mouse/MouseStateBuilder.h src/Events/Mouse/Mouse.h src/Events/Mouse/DefaultMouseStateBuilder.cpp src/Events/Mouse/DefaultMouseStateBuilder.h)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

find_package (Threads)

target_link_libraries(App Dengine ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
