# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pit/CLionProjectsassembler90

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pit/CLionProjectsassembler90/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CLionProjectsassembler90.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CLionProjectsassembler90.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CLionProjectsassembler90.dir/flags.make

CMakeFiles/CLionProjectsassembler90.dir/main.c.o: CMakeFiles/CLionProjectsassembler90.dir/flags.make
CMakeFiles/CLionProjectsassembler90.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pit/CLionProjectsassembler90/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CLionProjectsassembler90.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CLionProjectsassembler90.dir/main.c.o -c /Users/pit/CLionProjectsassembler90/main.c

CMakeFiles/CLionProjectsassembler90.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CLionProjectsassembler90.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pit/CLionProjectsassembler90/main.c > CMakeFiles/CLionProjectsassembler90.dir/main.c.i

CMakeFiles/CLionProjectsassembler90.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CLionProjectsassembler90.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pit/CLionProjectsassembler90/main.c -o CMakeFiles/CLionProjectsassembler90.dir/main.c.s

# Object files for target CLionProjectsassembler90
CLionProjectsassembler90_OBJECTS = \
"CMakeFiles/CLionProjectsassembler90.dir/main.c.o"

# External object files for target CLionProjectsassembler90
CLionProjectsassembler90_EXTERNAL_OBJECTS =

CLionProjectsassembler90: CMakeFiles/CLionProjectsassembler90.dir/main.c.o
CLionProjectsassembler90: CMakeFiles/CLionProjectsassembler90.dir/build.make
CLionProjectsassembler90: CMakeFiles/CLionProjectsassembler90.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pit/CLionProjectsassembler90/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable CLionProjectsassembler90"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CLionProjectsassembler90.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CLionProjectsassembler90.dir/build: CLionProjectsassembler90

.PHONY : CMakeFiles/CLionProjectsassembler90.dir/build

CMakeFiles/CLionProjectsassembler90.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CLionProjectsassembler90.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CLionProjectsassembler90.dir/clean

CMakeFiles/CLionProjectsassembler90.dir/depend:
	cd /Users/pit/CLionProjectsassembler90/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pit/CLionProjectsassembler90 /Users/pit/CLionProjectsassembler90 /Users/pit/CLionProjectsassembler90/cmake-build-debug /Users/pit/CLionProjectsassembler90/cmake-build-debug /Users/pit/CLionProjectsassembler90/cmake-build-debug/CMakeFiles/CLionProjectsassembler90.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CLionProjectsassembler90.dir/depend

