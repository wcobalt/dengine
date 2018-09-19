cmake_minimum_required(VERSION 3.12)
project(Dengine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dengine main.cpp WindowAccessors/WindowAccessorX.cpp WindowAccessors/WindowAccessorX.h WindowAccessors/WindowAccessor.cpp WindowAccessors/WindowAccessor.h Events/EventsManager.cpp Events/EventsManager.h Events/EventsHandlers/EventsHandler.cpp Events/EventsHandlers/EventsHandler.h Events/EventsHandlers/MouseEventsHandler.cpp Events/EventsHandlers/MouseEventsHandler.h Events/EventsAdapters/MouseEventsAdapter.cpp Events/EventsAdapters/MouseEventsAdapter.h Events/EventsHandlers/WindowEventsHandler.cpp Events/EventsHandlers/WindowEventsHandler.h Events/EventsAdapters/WindowEventsAdapter.cpp Events/EventsAdapters/WindowEventsAdapter.h Events/EventsHandlers/KeyEventsHandler.cpp Events/EventsHandlers/KeyEventsHandler.h Events/EventsAdapters/KeyEventsAdapter.cpp Events/EventsAdapters/KeyEventsAdapter.h Events/EventsInfo/KeyEventInfo.cpp Events/EventsInfo/KeyEventInfo.h Events/EventsInfo/EventInfo.cpp Events/EventsInfo/EventInfo.h Events/EventsInfo/WindowEventInfo.cpp Events/EventsInfo/WindowEventInfo.h Events/EventsInfo/MouseEventInfo.cpp Events/EventsInfo/MouseEventInfo.h Events/EventsInfo/MouseButtonEventInfo.cpp Events/EventsInfo/MouseButtonEventInfo.h Events/EventsInfo/MouseScrollEventInfo.cpp Events/EventsInfo/MouseScrollEventInfo.h Dengine.cpp Dengine.h WindowAccessors/WindowManager.cpp WindowAccessors/WindowManager.h Scene.cpp Scene.h GameObject.cpp GameObject.h Components/Component.cpp Components/Component.h Events/EventsData.cpp Events/EventsData.h)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

find_package (Threads)

target_link_libraries(Dengine ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})