cmake_minimum_required(VERSION 3.12)
project(Dengine)

set(CMAKE_CXX_STANDARD 17)

add_executable(App App/main.cpp)

add_library(Dengine
        Platform/Window/X/Exceptions/CouldNotOpenXDisplayException.cpp
        Platform/Window/X/Exceptions/CouldNotOpenXDisplayException.h
        Platform/Window/X/Exceptions/NoSuitableXVisualInfoException.cpp
        Platform/Window/X/Exceptions/NoSuitableXVisualInfoException.h
        Platform/Window/X/WindowManagerX.cpp
        Platform/Window/X/WindowManagerX.h
        Platform/Window/WindowManager.h

        Events/Keyboard/KeyboardState.h
        Events/Mouse/MouseState.h
        Events/Keyboard/KeyCode.cpp
        Events/Mouse/Mouse.h
        Events/Window/WindowState.h


        Platform/Window/WindowManager.cpp Platform/Window/X/Exceptions/UnableToCreateGLXContextException.cpp Platform/Window/X/Exceptions/UnableToCreateGLXContextException.h Platform/Window/X/Exceptions/UnableToAttachGLXContextToWindow.cpp Platform/Window/X/Exceptions/UnableToAttachGLXContextToWindow.h Platform/Window/X/Exceptions/TraySpecificationIsNotSupportedException.cpp Platform/Window/X/Exceptions/TraySpecificationIsNotSupportedException.h)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

find_package (Threads)

target_link_libraries(App Dengine ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
