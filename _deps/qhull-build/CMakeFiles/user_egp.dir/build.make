# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/particle/Documents/DS2_Final_Project/mujoco

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/particle/Documents/DS2_Final_Project

# Include any dependencies generated for this target.
include _deps/qhull-build/CMakeFiles/user_egp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/qhull-build/CMakeFiles/user_egp.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/qhull-build/CMakeFiles/user_egp.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/qhull-build/CMakeFiles/user_egp.dir/flags.make

_deps/qhull-build/CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.o: _deps/qhull-build/CMakeFiles/user_egp.dir/flags.make
_deps/qhull-build/CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.o: _deps/qhull-src/src/user_eg/user_eg.c
_deps/qhull-build/CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.o: _deps/qhull-build/CMakeFiles/user_egp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/particle/Documents/DS2_Final_Project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object _deps/qhull-build/CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.o"
	cd /home/particle/Documents/DS2_Final_Project/_deps/qhull-build && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT _deps/qhull-build/CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.o -MF CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.o.d -o CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.o -c /home/particle/Documents/DS2_Final_Project/_deps/qhull-src/src/user_eg/user_eg.c

_deps/qhull-build/CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.i"
	cd /home/particle/Documents/DS2_Final_Project/_deps/qhull-build && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/particle/Documents/DS2_Final_Project/_deps/qhull-src/src/user_eg/user_eg.c > CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.i

_deps/qhull-build/CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.s"
	cd /home/particle/Documents/DS2_Final_Project/_deps/qhull-build && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/particle/Documents/DS2_Final_Project/_deps/qhull-src/src/user_eg/user_eg.c -o CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.s

# Object files for target user_egp
user_egp_OBJECTS = \
"CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.o"

# External object files for target user_egp
user_egp_EXTERNAL_OBJECTS =

bin/user_egp: _deps/qhull-build/CMakeFiles/user_egp.dir/src/user_eg/user_eg.c.o
bin/user_egp: _deps/qhull-build/CMakeFiles/user_egp.dir/build.make
bin/user_egp: lib/libqhull_p.so.8.1-alpha1
bin/user_egp: _deps/qhull-build/CMakeFiles/user_egp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/particle/Documents/DS2_Final_Project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../bin/user_egp"
	cd /home/particle/Documents/DS2_Final_Project/_deps/qhull-build && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/user_egp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/qhull-build/CMakeFiles/user_egp.dir/build: bin/user_egp
.PHONY : _deps/qhull-build/CMakeFiles/user_egp.dir/build

_deps/qhull-build/CMakeFiles/user_egp.dir/clean:
	cd /home/particle/Documents/DS2_Final_Project/_deps/qhull-build && $(CMAKE_COMMAND) -P CMakeFiles/user_egp.dir/cmake_clean.cmake
.PHONY : _deps/qhull-build/CMakeFiles/user_egp.dir/clean

_deps/qhull-build/CMakeFiles/user_egp.dir/depend:
	cd /home/particle/Documents/DS2_Final_Project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/particle/Documents/DS2_Final_Project/mujoco /home/particle/Documents/DS2_Final_Project/_deps/qhull-src /home/particle/Documents/DS2_Final_Project /home/particle/Documents/DS2_Final_Project/_deps/qhull-build /home/particle/Documents/DS2_Final_Project/_deps/qhull-build/CMakeFiles/user_egp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/qhull-build/CMakeFiles/user_egp.dir/depend

