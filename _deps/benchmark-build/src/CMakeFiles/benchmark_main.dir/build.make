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
include _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/flags.make

_deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/benchmark_main.cc.o: _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/flags.make
_deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/benchmark_main.cc.o: _deps/benchmark-src/src/benchmark_main.cc
_deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/benchmark_main.cc.o: _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/particle/Documents/DS2_Final_Project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/benchmark_main.cc.o"
	cd /home/particle/Documents/DS2_Final_Project/_deps/benchmark-build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/benchmark_main.cc.o -MF CMakeFiles/benchmark_main.dir/benchmark_main.cc.o.d -o CMakeFiles/benchmark_main.dir/benchmark_main.cc.o -c /home/particle/Documents/DS2_Final_Project/_deps/benchmark-src/src/benchmark_main.cc

_deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/benchmark_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark_main.dir/benchmark_main.cc.i"
	cd /home/particle/Documents/DS2_Final_Project/_deps/benchmark-build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/particle/Documents/DS2_Final_Project/_deps/benchmark-src/src/benchmark_main.cc > CMakeFiles/benchmark_main.dir/benchmark_main.cc.i

_deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/benchmark_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark_main.dir/benchmark_main.cc.s"
	cd /home/particle/Documents/DS2_Final_Project/_deps/benchmark-build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/particle/Documents/DS2_Final_Project/_deps/benchmark-src/src/benchmark_main.cc -o CMakeFiles/benchmark_main.dir/benchmark_main.cc.s

# Object files for target benchmark_main
benchmark_main_OBJECTS = \
"CMakeFiles/benchmark_main.dir/benchmark_main.cc.o"

# External object files for target benchmark_main
benchmark_main_EXTERNAL_OBJECTS =

lib/libbenchmark_main.a: _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/benchmark_main.cc.o
lib/libbenchmark_main.a: _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/build.make
lib/libbenchmark_main.a: _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/particle/Documents/DS2_Final_Project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../lib/libbenchmark_main.a"
	cd /home/particle/Documents/DS2_Final_Project/_deps/benchmark-build/src && $(CMAKE_COMMAND) -P CMakeFiles/benchmark_main.dir/cmake_clean_target.cmake
	cd /home/particle/Documents/DS2_Final_Project/_deps/benchmark-build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/benchmark_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/build: lib/libbenchmark_main.a
.PHONY : _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/build

_deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/clean:
	cd /home/particle/Documents/DS2_Final_Project/_deps/benchmark-build/src && $(CMAKE_COMMAND) -P CMakeFiles/benchmark_main.dir/cmake_clean.cmake
.PHONY : _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/clean

_deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/depend:
	cd /home/particle/Documents/DS2_Final_Project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/particle/Documents/DS2_Final_Project/mujoco /home/particle/Documents/DS2_Final_Project/_deps/benchmark-src/src /home/particle/Documents/DS2_Final_Project /home/particle/Documents/DS2_Final_Project/_deps/benchmark-build/src /home/particle/Documents/DS2_Final_Project/_deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/benchmark-build/src/CMakeFiles/benchmark_main.dir/depend

