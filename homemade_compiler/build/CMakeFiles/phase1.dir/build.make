# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/nic/original-projects/compiler/parser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nic/original-projects/compiler/parser/build

# Include any dependencies generated for this target.
include CMakeFiles/phase1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/phase1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/phase1.dir/flags.make

CMakeFiles/phase1.dir/phase1.cpp.o: CMakeFiles/phase1.dir/flags.make
CMakeFiles/phase1.dir/phase1.cpp.o: ../phase1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nic/original-projects/compiler/parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/phase1.dir/phase1.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/phase1.dir/phase1.cpp.o -c /home/nic/original-projects/compiler/parser/phase1.cpp

CMakeFiles/phase1.dir/phase1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phase1.dir/phase1.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nic/original-projects/compiler/parser/phase1.cpp > CMakeFiles/phase1.dir/phase1.cpp.i

CMakeFiles/phase1.dir/phase1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phase1.dir/phase1.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nic/original-projects/compiler/parser/phase1.cpp -o CMakeFiles/phase1.dir/phase1.cpp.s

CMakeFiles/phase1.dir/phase1.cpp.o.requires:

.PHONY : CMakeFiles/phase1.dir/phase1.cpp.o.requires

CMakeFiles/phase1.dir/phase1.cpp.o.provides: CMakeFiles/phase1.dir/phase1.cpp.o.requires
	$(MAKE) -f CMakeFiles/phase1.dir/build.make CMakeFiles/phase1.dir/phase1.cpp.o.provides.build
.PHONY : CMakeFiles/phase1.dir/phase1.cpp.o.provides

CMakeFiles/phase1.dir/phase1.cpp.o.provides.build: CMakeFiles/phase1.dir/phase1.cpp.o


CMakeFiles/phase1.dir/ParseTable.cpp.o: CMakeFiles/phase1.dir/flags.make
CMakeFiles/phase1.dir/ParseTable.cpp.o: ../ParseTable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nic/original-projects/compiler/parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/phase1.dir/ParseTable.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/phase1.dir/ParseTable.cpp.o -c /home/nic/original-projects/compiler/parser/ParseTable.cpp

CMakeFiles/phase1.dir/ParseTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phase1.dir/ParseTable.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nic/original-projects/compiler/parser/ParseTable.cpp > CMakeFiles/phase1.dir/ParseTable.cpp.i

CMakeFiles/phase1.dir/ParseTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phase1.dir/ParseTable.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nic/original-projects/compiler/parser/ParseTable.cpp -o CMakeFiles/phase1.dir/ParseTable.cpp.s

CMakeFiles/phase1.dir/ParseTable.cpp.o.requires:

.PHONY : CMakeFiles/phase1.dir/ParseTable.cpp.o.requires

CMakeFiles/phase1.dir/ParseTable.cpp.o.provides: CMakeFiles/phase1.dir/ParseTable.cpp.o.requires
	$(MAKE) -f CMakeFiles/phase1.dir/build.make CMakeFiles/phase1.dir/ParseTable.cpp.o.provides.build
.PHONY : CMakeFiles/phase1.dir/ParseTable.cpp.o.provides

CMakeFiles/phase1.dir/ParseTable.cpp.o.provides.build: CMakeFiles/phase1.dir/ParseTable.cpp.o


CMakeFiles/phase1.dir/Parser.cpp.o: CMakeFiles/phase1.dir/flags.make
CMakeFiles/phase1.dir/Parser.cpp.o: ../Parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nic/original-projects/compiler/parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/phase1.dir/Parser.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/phase1.dir/Parser.cpp.o -c /home/nic/original-projects/compiler/parser/Parser.cpp

CMakeFiles/phase1.dir/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phase1.dir/Parser.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nic/original-projects/compiler/parser/Parser.cpp > CMakeFiles/phase1.dir/Parser.cpp.i

CMakeFiles/phase1.dir/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phase1.dir/Parser.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nic/original-projects/compiler/parser/Parser.cpp -o CMakeFiles/phase1.dir/Parser.cpp.s

CMakeFiles/phase1.dir/Parser.cpp.o.requires:

.PHONY : CMakeFiles/phase1.dir/Parser.cpp.o.requires

CMakeFiles/phase1.dir/Parser.cpp.o.provides: CMakeFiles/phase1.dir/Parser.cpp.o.requires
	$(MAKE) -f CMakeFiles/phase1.dir/build.make CMakeFiles/phase1.dir/Parser.cpp.o.provides.build
.PHONY : CMakeFiles/phase1.dir/Parser.cpp.o.provides

CMakeFiles/phase1.dir/Parser.cpp.o.provides.build: CMakeFiles/phase1.dir/Parser.cpp.o


# Object files for target phase1
phase1_OBJECTS = \
"CMakeFiles/phase1.dir/phase1.cpp.o" \
"CMakeFiles/phase1.dir/ParseTable.cpp.o" \
"CMakeFiles/phase1.dir/Parser.cpp.o"

# External object files for target phase1
phase1_EXTERNAL_OBJECTS =

phase1: CMakeFiles/phase1.dir/phase1.cpp.o
phase1: CMakeFiles/phase1.dir/ParseTable.cpp.o
phase1: CMakeFiles/phase1.dir/Parser.cpp.o
phase1: CMakeFiles/phase1.dir/build.make
phase1: CMakeFiles/phase1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nic/original-projects/compiler/parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable phase1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/phase1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/phase1.dir/build: phase1

.PHONY : CMakeFiles/phase1.dir/build

CMakeFiles/phase1.dir/requires: CMakeFiles/phase1.dir/phase1.cpp.o.requires
CMakeFiles/phase1.dir/requires: CMakeFiles/phase1.dir/ParseTable.cpp.o.requires
CMakeFiles/phase1.dir/requires: CMakeFiles/phase1.dir/Parser.cpp.o.requires

.PHONY : CMakeFiles/phase1.dir/requires

CMakeFiles/phase1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/phase1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/phase1.dir/clean

CMakeFiles/phase1.dir/depend:
	cd /home/nic/original-projects/compiler/parser/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nic/original-projects/compiler/parser /home/nic/original-projects/compiler/parser /home/nic/original-projects/compiler/parser/build /home/nic/original-projects/compiler/parser/build /home/nic/original-projects/compiler/parser/build/CMakeFiles/phase1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/phase1.dir/depend

