cmake_minimum_required(VERSION 3.12)
project(Dengine)

set(CMAKE_CXX_STANDARD 17)

add_executable(App App/main.cpp Utils/Compression/Huffman/HuffmanDecoder.h Utils/Compression/Huffman/DefaultHuffmanDecoder.cpp Utils/Compression/Huffman/DefaultHuffmanDecoder.h Utils/Compression/Deflate/DeflateDecoder.h Utils/Compression/Deflate/DefaultDeflateDecoder.cpp Utils/Compression/Deflate/DefaultDeflateDecoder.h Exceptions/InvalidArgumentException.cpp Exceptions/InvalidArgumentException.h Exceptions/InvalidStateException.cpp Exceptions/InvalidStateException.h Utils/Compression/Deflate/Exceptions/DeflateException.cpp Utils/Compression/Deflate/Exceptions/DeflateException.h Utils/Streams/InputBitStream.h Utils/Streams/DefaultInputBitStream.cpp Utils/Streams/DefaultInputBitStream.h)

#[[add_library(Dengine
        Platform/Window/X/WindowManagerX.cpp
        Platform/Window/X/WindowManagerX.h
        Platform/Window/WindowManager.h

        Events/Keyboard/KeyboardState.h
        Events/Mouse/MouseState.h
        Events/Keyboard/Keyboard.cpp
        Events/Window/WindowState.h
        Events/Mouse/DefaultMouseState.cpp
        Events/Mouse/DefaultMouseState.h
        Events/Window/DefaultWindowState.cpp
        Events/Window/DefaultWindowState.h
        Events/Keyboard/DefaultKeyboardState.cpp
        Events/Keyboard/DefaultKeyboardState.h
        Events/Keyboard/Keyboard.h
        Events/Keyboard/Key.h
        Events/Keyboard/DKey.cpp
        Events/Keyboard/DKey.h
        Events/Keyboard/KeyByDKeyCodeComparator.cpp
        Events/Keyboard/KeyByDKeyCodeComparator.h
        Events/Keyboard/KeyBySymbolComparator.cpp
        Events/Keyboard/KeyBySymbolComparator.h

        Platform/Window/WindowManager.cpp Events/Keyboard/KeyComparator.h Events/Mouse/MouseStateBuilder.h Events/Mouse/Mouse.h Events/Mouse/DefaultMouseStateBuilder.cpp Events/Mouse/DefaultMouseStateBuilder.h Events/Window/WindowStateBuilder.h Events/Window/DefaultWindowStateBuilder.cpp Events/Window/DefaultWindowStateBuilder.h
        Events/Keyboard/KeyboardStateBuilder.h
        Events/Keyboard/DefaultKeyboardStateBuilder.h
        Events/Keyboard/DefaultKeyboardStateBuilder.cpp
        Platform/Window/X/Util/XKeyboardConverter.h
        Platform/Window/X/Exceptions/XException.cpp
        Platform/Window/X/Exceptions/XException.h
        Platform/Window/X/Util/XKeyboardConverter.h
        Platform/Window/X/Util/XDefaultKeyboardConverter.h
        Platform/Window/X/Util/XDefaultKeyboardConverter.cpp
        Exceptions/DengineException.h
        Exceptions/DengineException.cpp
        Exceptions/IOException.cpp Exceptions/IOException.h)]]

add_library(PNG Graphics/PNG/PNG.h
            Graphics/Image.h Graphics/Pixel.h Graphics/DefaultPixel.cpp        Exceptions/DengineException.h
        Exceptions/DengineException.cpp Graphics/DefaultPixel.h Graphics/DefaultImage.cpp Graphics/DefaultImage.h)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

find_package (Threads)

target_link_libraries(App PNG #[[${X11_LIBRARIES} ${OPENGL_LIBRARIES}]] ${CMAKE_THREAD_LIBS_INIT})