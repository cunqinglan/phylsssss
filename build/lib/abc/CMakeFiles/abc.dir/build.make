# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /home/panhongxiang/common/centos/bin/cmake

# The command to remove a file.
RM = /home/panhongxiang/common/centos/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/panhongxiang/phyLS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/panhongxiang/phyLS/build

# Include any dependencies generated for this target.
include lib/abc/CMakeFiles/abc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/abc/CMakeFiles/abc.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/abc/CMakeFiles/abc.dir/progress.make

# Include the compile flags for this target's objects.
include lib/abc/CMakeFiles/abc.dir/flags.make

lib/abc/CMakeFiles/abc.dir/src/base/main/main.c.o: lib/abc/CMakeFiles/abc.dir/flags.make
lib/abc/CMakeFiles/abc.dir/src/base/main/main.c.o: /home/panhongxiang/phyLS/lib/abc/src/base/main/main.c
lib/abc/CMakeFiles/abc.dir/src/base/main/main.c.o: lib/abc/CMakeFiles/abc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/panhongxiang/phyLS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/abc/CMakeFiles/abc.dir/src/base/main/main.c.o"
	cd /home/panhongxiang/phyLS/build/lib/abc && /opt/rh/devtoolset-8/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/abc/CMakeFiles/abc.dir/src/base/main/main.c.o -MF CMakeFiles/abc.dir/src/base/main/main.c.o.d -o CMakeFiles/abc.dir/src/base/main/main.c.o -c /home/panhongxiang/phyLS/lib/abc/src/base/main/main.c

lib/abc/CMakeFiles/abc.dir/src/base/main/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/abc.dir/src/base/main/main.c.i"
	cd /home/panhongxiang/phyLS/build/lib/abc && /opt/rh/devtoolset-8/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/panhongxiang/phyLS/lib/abc/src/base/main/main.c > CMakeFiles/abc.dir/src/base/main/main.c.i

lib/abc/CMakeFiles/abc.dir/src/base/main/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/abc.dir/src/base/main/main.c.s"
	cd /home/panhongxiang/phyLS/build/lib/abc && /opt/rh/devtoolset-8/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/panhongxiang/phyLS/lib/abc/src/base/main/main.c -o CMakeFiles/abc.dir/src/base/main/main.c.s

# Object files for target abc
abc_OBJECTS = \
"CMakeFiles/abc.dir/src/base/main/main.c.o"

# External object files for target abc
abc_EXTERNAL_OBJECTS =

lib/abc/abc: lib/abc/CMakeFiles/abc.dir/src/base/main/main.c.o
lib/abc/abc: lib/abc/CMakeFiles/abc.dir/build.make
lib/abc/abc: lib/abc/libabc.a
lib/abc/abc: lib/abc/CMakeFiles/abc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/panhongxiang/phyLS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable abc"
	cd /home/panhongxiang/phyLS/build/lib/abc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/abc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/abc/CMakeFiles/abc.dir/build: lib/abc/abc
.PHONY : lib/abc/CMakeFiles/abc.dir/build

lib/abc/CMakeFiles/abc.dir/clean:
	cd /home/panhongxiang/phyLS/build/lib/abc && $(CMAKE_COMMAND) -P CMakeFiles/abc.dir/cmake_clean.cmake
.PHONY : lib/abc/CMakeFiles/abc.dir/clean

lib/abc/CMakeFiles/abc.dir/depend:
	cd /home/panhongxiang/phyLS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/panhongxiang/phyLS /home/panhongxiang/phyLS/lib/abc /home/panhongxiang/phyLS/build /home/panhongxiang/phyLS/build/lib/abc /home/panhongxiang/phyLS/build/lib/abc/CMakeFiles/abc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/abc/CMakeFiles/abc.dir/depend

