# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/wcobalt/Files/InstalledPrograms/clion-2018.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/wcobalt/Files/InstalledPrograms/clion-2018.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wcobalt/Files/Dengine/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wcobalt/Files/Dengine/src/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/App.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/App.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/App.dir/flags.make

CMakeFiles/App.dir/App/main.cpp.o: CMakeFiles/App.dir/flags.make
CMakeFiles/App.dir/App/main.cpp.o: ../App/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wcobalt/Files/Dengine/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/App.dir/App/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/App.dir/App/main.cpp.o -c /home/wcobalt/Files/Dengine/src/App/main.cpp

CMakeFiles/App.dir/App/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/App.dir/App/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wcobalt/Files/Dengine/src/App/main.cpp > CMakeFiles/App.dir/App/main.cpp.i

CMakeFiles/App.dir/App/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/App.dir/App/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wcobalt/Files/Dengine/src/App/main.cpp -o CMakeFiles/App.dir/App/main.cpp.s

# Object files for target App
App_OBJECTS = \
"CMakeFiles/App.dir/App/main.cpp.o"

# External object files for target App
App_EXTERNAL_OBJECTS =

App: CMakeFiles/App.dir/App/main.cpp.o
App: CMakeFiles/App.dir/build.make
App: libDengine.a
App: /usr/lib/x86_64-linux-gnu/libX11.so
App: /usr/lib/x86_64-linux-gnu/libXext.so
App: /usr/lib/x86_64-linux-gnu/libOpenGL.so
App: /usr/lib/x86_64-linux-gnu/libGLX.so
App: CMakeFiles/App.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wcobalt/Files/Dengine/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable App"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/App.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/App.dir/build: App

.PHONY : CMakeFiles/App.dir/build

CMakeFiles/App.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/App.dir/cmake_clean.cmake
.PHONY : CMakeFiles/App.dir/clean

CMakeFiles/App.dir/depend:
	cd /home/wcobalt/Files/Dengine/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wcobalt/Files/Dengine/src /home/wcobalt/Files/Dengine/src /home/wcobalt/Files/Dengine/src/cmake-build-debug /home/wcobalt/Files/Dengine/src/cmake-build-debug /home/wcobalt/Files/Dengine/src/cmake-build-debug/CMakeFiles/App.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/App.dir/depend

