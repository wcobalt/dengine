cmake_minimum_required(VERSION 3.12)
project(Dengine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dengine main.cpp WindowAccessors/WindowAccessorX.cpp WindowAccessors/WindowAccessorX.h WindowAccessor.cpp WindowAccessor.h Events/EventsManager.cpp Events/EventsManager.h Events/EventsHandler.cpp Events/EventsHandler.h Events/MouseEventsHandler.cpp Events/MouseEventsHandler.h Events/MouseEventsAdapter.cpp Events/MouseEventsAdapter.h Events/WindowEventsHandler.cpp Events/WindowEventsHandler.h Events/WindowEventsAdapter.cpp Events/WindowEventsAdapter.h Events/KeyEventsHandler.cpp Events/KeyEventsHandler.h Events/KeyEventsAdapter.cpp Events/KeyEventsAdapter.h Events/KeyEventInfo.cpp Events/KeyEventInfo.h Events/EventInfo.cpp Events/EventInfo.h Events/WindowEventInfo.cpp Events/WindowEventInfo.h Events/MouseEventInfo.cpp Events/MouseEventInfo.h Events/MouseButtonEventInfo.cpp Events/MouseButtonEventInfo.h Events/MouseScrollEventInfo.cpp Events/MouseScrollEventInfo.h)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

target_link_libraries(Dengine ${X11_LIBRARIES} ${OPENGL_LIBRARIES})