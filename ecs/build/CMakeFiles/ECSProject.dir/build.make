# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/solype/delivery/current_days/rtype/ecs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/solype/delivery/current_days/rtype/ecs/build

# Include any dependencies generated for this target.
include CMakeFiles/ECSProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ECSProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ECSProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ECSProject.dir/flags.make

CMakeFiles/ECSProject.dir/src/Entity.cpp.o: CMakeFiles/ECSProject.dir/flags.make
CMakeFiles/ECSProject.dir/src/Entity.cpp.o: /home/solype/delivery/current_days/rtype/ecs/src/Entity.cpp
CMakeFiles/ECSProject.dir/src/Entity.cpp.o: CMakeFiles/ECSProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/solype/delivery/current_days/rtype/ecs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ECSProject.dir/src/Entity.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ECSProject.dir/src/Entity.cpp.o -MF CMakeFiles/ECSProject.dir/src/Entity.cpp.o.d -o CMakeFiles/ECSProject.dir/src/Entity.cpp.o -c /home/solype/delivery/current_days/rtype/ecs/src/Entity.cpp

CMakeFiles/ECSProject.dir/src/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ECSProject.dir/src/Entity.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/solype/delivery/current_days/rtype/ecs/src/Entity.cpp > CMakeFiles/ECSProject.dir/src/Entity.cpp.i

CMakeFiles/ECSProject.dir/src/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ECSProject.dir/src/Entity.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/solype/delivery/current_days/rtype/ecs/src/Entity.cpp -o CMakeFiles/ECSProject.dir/src/Entity.cpp.s

CMakeFiles/ECSProject.dir/main.cpp.o: CMakeFiles/ECSProject.dir/flags.make
CMakeFiles/ECSProject.dir/main.cpp.o: /home/solype/delivery/current_days/rtype/ecs/main.cpp
CMakeFiles/ECSProject.dir/main.cpp.o: CMakeFiles/ECSProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/solype/delivery/current_days/rtype/ecs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ECSProject.dir/main.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ECSProject.dir/main.cpp.o -MF CMakeFiles/ECSProject.dir/main.cpp.o.d -o CMakeFiles/ECSProject.dir/main.cpp.o -c /home/solype/delivery/current_days/rtype/ecs/main.cpp

CMakeFiles/ECSProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ECSProject.dir/main.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/solype/delivery/current_days/rtype/ecs/main.cpp > CMakeFiles/ECSProject.dir/main.cpp.i

CMakeFiles/ECSProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ECSProject.dir/main.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/solype/delivery/current_days/rtype/ecs/main.cpp -o CMakeFiles/ECSProject.dir/main.cpp.s

# Object files for target ECSProject
ECSProject_OBJECTS = \
"CMakeFiles/ECSProject.dir/src/Entity.cpp.o" \
"CMakeFiles/ECSProject.dir/main.cpp.o"

# External object files for target ECSProject
ECSProject_EXTERNAL_OBJECTS =

ECSProject: CMakeFiles/ECSProject.dir/src/Entity.cpp.o
ECSProject: CMakeFiles/ECSProject.dir/main.cpp.o
ECSProject: CMakeFiles/ECSProject.dir/build.make
ECSProject: CMakeFiles/ECSProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/solype/delivery/current_days/rtype/ecs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ECSProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ECSProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ECSProject.dir/build: ECSProject
.PHONY : CMakeFiles/ECSProject.dir/build

CMakeFiles/ECSProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ECSProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ECSProject.dir/clean

CMakeFiles/ECSProject.dir/depend:
	cd /home/solype/delivery/current_days/rtype/ecs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/solype/delivery/current_days/rtype/ecs /home/solype/delivery/current_days/rtype/ecs /home/solype/delivery/current_days/rtype/ecs/build /home/solype/delivery/current_days/rtype/ecs/build /home/solype/delivery/current_days/rtype/ecs/build/CMakeFiles/ECSProject.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ECSProject.dir/depend

