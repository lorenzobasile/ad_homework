# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lorenzo/Desktop/ad_homework/dijkstra

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lorenzo/Desktop/ad_homework/dijkstra

# Include any dependencies generated for this target.
include CMakeFiles/dijkstra.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dijkstra.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dijkstra.dir/flags.make

CMakeFiles/dijkstra.dir/main.c.o: CMakeFiles/dijkstra.dir/flags.make
CMakeFiles/dijkstra.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lorenzo/Desktop/ad_homework/dijkstra/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/dijkstra.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dijkstra.dir/main.c.o   -c /home/lorenzo/Desktop/ad_homework/dijkstra/main.c

CMakeFiles/dijkstra.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dijkstra.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lorenzo/Desktop/ad_homework/dijkstra/main.c > CMakeFiles/dijkstra.dir/main.c.i

CMakeFiles/dijkstra.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dijkstra.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lorenzo/Desktop/ad_homework/dijkstra/main.c -o CMakeFiles/dijkstra.dir/main.c.s

CMakeFiles/dijkstra.dir/main.c.o.requires:

.PHONY : CMakeFiles/dijkstra.dir/main.c.o.requires

CMakeFiles/dijkstra.dir/main.c.o.provides: CMakeFiles/dijkstra.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/dijkstra.dir/build.make CMakeFiles/dijkstra.dir/main.c.o.provides.build
.PHONY : CMakeFiles/dijkstra.dir/main.c.o.provides

CMakeFiles/dijkstra.dir/main.c.o.provides.build: CMakeFiles/dijkstra.dir/main.c.o


CMakeFiles/dijkstra.dir/dijkstra.c.o: CMakeFiles/dijkstra.dir/flags.make
CMakeFiles/dijkstra.dir/dijkstra.c.o: dijkstra.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lorenzo/Desktop/ad_homework/dijkstra/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/dijkstra.dir/dijkstra.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dijkstra.dir/dijkstra.c.o   -c /home/lorenzo/Desktop/ad_homework/dijkstra/dijkstra.c

CMakeFiles/dijkstra.dir/dijkstra.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dijkstra.dir/dijkstra.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lorenzo/Desktop/ad_homework/dijkstra/dijkstra.c > CMakeFiles/dijkstra.dir/dijkstra.c.i

CMakeFiles/dijkstra.dir/dijkstra.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dijkstra.dir/dijkstra.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lorenzo/Desktop/ad_homework/dijkstra/dijkstra.c -o CMakeFiles/dijkstra.dir/dijkstra.c.s

CMakeFiles/dijkstra.dir/dijkstra.c.o.requires:

.PHONY : CMakeFiles/dijkstra.dir/dijkstra.c.o.requires

CMakeFiles/dijkstra.dir/dijkstra.c.o.provides: CMakeFiles/dijkstra.dir/dijkstra.c.o.requires
	$(MAKE) -f CMakeFiles/dijkstra.dir/build.make CMakeFiles/dijkstra.dir/dijkstra.c.o.provides.build
.PHONY : CMakeFiles/dijkstra.dir/dijkstra.c.o.provides

CMakeFiles/dijkstra.dir/dijkstra.c.o.provides.build: CMakeFiles/dijkstra.dir/dijkstra.c.o


CMakeFiles/dijkstra.dir/graph.c.o: CMakeFiles/dijkstra.dir/flags.make
CMakeFiles/dijkstra.dir/graph.c.o: graph.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lorenzo/Desktop/ad_homework/dijkstra/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/dijkstra.dir/graph.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dijkstra.dir/graph.c.o   -c /home/lorenzo/Desktop/ad_homework/dijkstra/graph.c

CMakeFiles/dijkstra.dir/graph.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dijkstra.dir/graph.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lorenzo/Desktop/ad_homework/dijkstra/graph.c > CMakeFiles/dijkstra.dir/graph.c.i

CMakeFiles/dijkstra.dir/graph.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dijkstra.dir/graph.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lorenzo/Desktop/ad_homework/dijkstra/graph.c -o CMakeFiles/dijkstra.dir/graph.c.s

CMakeFiles/dijkstra.dir/graph.c.o.requires:

.PHONY : CMakeFiles/dijkstra.dir/graph.c.o.requires

CMakeFiles/dijkstra.dir/graph.c.o.provides: CMakeFiles/dijkstra.dir/graph.c.o.requires
	$(MAKE) -f CMakeFiles/dijkstra.dir/build.make CMakeFiles/dijkstra.dir/graph.c.o.provides.build
.PHONY : CMakeFiles/dijkstra.dir/graph.c.o.provides

CMakeFiles/dijkstra.dir/graph.c.o.provides.build: CMakeFiles/dijkstra.dir/graph.c.o


# Object files for target dijkstra
dijkstra_OBJECTS = \
"CMakeFiles/dijkstra.dir/main.c.o" \
"CMakeFiles/dijkstra.dir/dijkstra.c.o" \
"CMakeFiles/dijkstra.dir/graph.c.o"

# External object files for target dijkstra
dijkstra_EXTERNAL_OBJECTS =

dijkstra: CMakeFiles/dijkstra.dir/main.c.o
dijkstra: CMakeFiles/dijkstra.dir/dijkstra.c.o
dijkstra: CMakeFiles/dijkstra.dir/graph.c.o
dijkstra: CMakeFiles/dijkstra.dir/build.make
dijkstra: /home/lorenzo/Desktop/ad_homework/heapv2/libbinheap.so
dijkstra: CMakeFiles/dijkstra.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lorenzo/Desktop/ad_homework/dijkstra/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable dijkstra"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dijkstra.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dijkstra.dir/build: dijkstra

.PHONY : CMakeFiles/dijkstra.dir/build

CMakeFiles/dijkstra.dir/requires: CMakeFiles/dijkstra.dir/main.c.o.requires
CMakeFiles/dijkstra.dir/requires: CMakeFiles/dijkstra.dir/dijkstra.c.o.requires
CMakeFiles/dijkstra.dir/requires: CMakeFiles/dijkstra.dir/graph.c.o.requires

.PHONY : CMakeFiles/dijkstra.dir/requires

CMakeFiles/dijkstra.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dijkstra.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dijkstra.dir/clean

CMakeFiles/dijkstra.dir/depend:
	cd /home/lorenzo/Desktop/ad_homework/dijkstra && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lorenzo/Desktop/ad_homework/dijkstra /home/lorenzo/Desktop/ad_homework/dijkstra /home/lorenzo/Desktop/ad_homework/dijkstra /home/lorenzo/Desktop/ad_homework/dijkstra /home/lorenzo/Desktop/ad_homework/dijkstra/CMakeFiles/dijkstra.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dijkstra.dir/depend
