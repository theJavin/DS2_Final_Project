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
CMAKE_SOURCE_DIR = /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild

# Utility rule file for glm_lib-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/glm_lib-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/glm_lib-populate.dir/progress.make

CMakeFiles/glm_lib-populate: CMakeFiles/glm_lib-populate-complete

CMakeFiles/glm_lib-populate-complete: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-install
CMakeFiles/glm_lib-populate-complete: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-mkdir
CMakeFiles/glm_lib-populate-complete: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-download
CMakeFiles/glm_lib-populate-complete: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-update
CMakeFiles/glm_lib-populate-complete: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-patch
CMakeFiles/glm_lib-populate-complete: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-configure
CMakeFiles/glm_lib-populate-complete: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-build
CMakeFiles/glm_lib-populate-complete: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-install
CMakeFiles/glm_lib-populate-complete: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'glm_lib-populate'"
	/usr/bin/cmake -E make_directory /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/CMakeFiles
	/usr/bin/cmake -E touch /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/CMakeFiles/glm_lib-populate-complete
	/usr/bin/cmake -E touch /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-done

glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-update:
.PHONY : glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-update

glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-build: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'glm_lib-populate'"
	cd /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-build && /usr/bin/cmake -E echo_append
	cd /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-build && /usr/bin/cmake -E touch /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-build

glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-configure: glm_lib-populate-prefix/tmp/glm_lib-populate-cfgcmd.txt
glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-configure: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'glm_lib-populate'"
	cd /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-build && /usr/bin/cmake -E echo_append
	cd /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-build && /usr/bin/cmake -E touch /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-configure

glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-download: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-gitinfo.txt
glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-download: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'glm_lib-populate'"
	cd /home/particle/Documents/DS2_Final_Project/_deps && /usr/bin/cmake -P /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/tmp/glm_lib-populate-gitclone.cmake
	cd /home/particle/Documents/DS2_Final_Project/_deps && /usr/bin/cmake -E touch /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-download

glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-install: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'glm_lib-populate'"
	cd /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-build && /usr/bin/cmake -E echo_append
	cd /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-build && /usr/bin/cmake -E touch /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-install

glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'glm_lib-populate'"
	/usr/bin/cmake -E make_directory /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-src
	/usr/bin/cmake -E make_directory /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-build
	/usr/bin/cmake -E make_directory /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix
	/usr/bin/cmake -E make_directory /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/tmp
	/usr/bin/cmake -E make_directory /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/src/glm_lib-populate-stamp
	/usr/bin/cmake -E make_directory /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/src
	/usr/bin/cmake -E make_directory /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/src/glm_lib-populate-stamp
	/usr/bin/cmake -E touch /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-mkdir

glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-patch: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'glm_lib-populate'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-patch

glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-update:
.PHONY : glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-update

glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-test: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'glm_lib-populate'"
	cd /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-build && /usr/bin/cmake -E echo_append
	cd /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-build && /usr/bin/cmake -E touch /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-test

glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-update: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'glm_lib-populate'"
	cd /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-src && /usr/bin/cmake -P /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/glm_lib-populate-prefix/tmp/glm_lib-populate-gitupdate.cmake

glm_lib-populate: CMakeFiles/glm_lib-populate
glm_lib-populate: CMakeFiles/glm_lib-populate-complete
glm_lib-populate: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-build
glm_lib-populate: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-configure
glm_lib-populate: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-download
glm_lib-populate: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-install
glm_lib-populate: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-mkdir
glm_lib-populate: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-patch
glm_lib-populate: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-test
glm_lib-populate: glm_lib-populate-prefix/src/glm_lib-populate-stamp/glm_lib-populate-update
glm_lib-populate: CMakeFiles/glm_lib-populate.dir/build.make
.PHONY : glm_lib-populate

# Rule to build all files generated by this target.
CMakeFiles/glm_lib-populate.dir/build: glm_lib-populate
.PHONY : CMakeFiles/glm_lib-populate.dir/build

CMakeFiles/glm_lib-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glm_lib-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glm_lib-populate.dir/clean

CMakeFiles/glm_lib-populate.dir/depend:
	cd /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild /home/particle/Documents/DS2_Final_Project/_deps/glm_lib-subbuild/CMakeFiles/glm_lib-populate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glm_lib-populate.dir/depend
