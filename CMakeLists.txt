cmake_minimum_required(VERSION 3.12)
project(Dengine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dengine main.cpp WindowAccessors/WindowAccessorX.cpp WindowAccessors/WindowAccessorX.h WindowAccessors/WindowAccessor.cpp WindowAccessors/WindowAccessor.h Dengine.cpp Dengine.h WindowAccessors/WindowManager.cpp WindowAccessors/WindowManager.h Scene.cpp Scene.h GameObject.cpp GameObject.h Components/Component.cpp Components/Component.h Events/EventsData.cpp Events/EventsData.h Events/MousePosition.cpp Events/MousePosition.h Components/Transform3DComponent.cpp Components/Transform3DComponent.h Coreutils/Entry.cpp Coreutils/Entry.h Exceptions/DengineException.cpp Exceptions/DengineException.h Exceptions/NoCurrentSceneException.cpp Exceptions/NoCurrentSceneException.h Exceptions/NoSuitableSceneException.cpp Exceptions/NoSuitableSceneException.h Exceptions/CurrentSceneRemovingException.cpp Exceptions/CurrentSceneRemovingException.h Geometry/vector3.cpp Geometry/vector3.h Geometry/vector2.cpp Geometry/vector2.h Geometry/dimension3.cpp Geometry/dimension3.h Geometry/dimension2.cpp Geometry/dimension2.h Geometry/dimensions.h Utils/String.cpp Utils/String.h)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

find_package (Threads)

target_link_libraries(Dengine ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})