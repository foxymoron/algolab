# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/jait/dev/algolab/week6/almostantenna/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jait/dev/algolab/week6/almostantenna/src

# Include any dependencies generated for this target.
include CMakeFiles/almostantenna.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/almostantenna.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/almostantenna.dir/flags.make

CMakeFiles/almostantenna.dir/almostantenna.cpp.o: CMakeFiles/almostantenna.dir/flags.make
CMakeFiles/almostantenna.dir/almostantenna.cpp.o: almostantenna.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jait/dev/algolab/week6/almostantenna/src/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/almostantenna.dir/almostantenna.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/almostantenna.dir/almostantenna.cpp.o -c /home/jait/dev/algolab/week6/almostantenna/src/almostantenna.cpp

CMakeFiles/almostantenna.dir/almostantenna.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/almostantenna.dir/almostantenna.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jait/dev/algolab/week6/almostantenna/src/almostantenna.cpp > CMakeFiles/almostantenna.dir/almostantenna.cpp.i

CMakeFiles/almostantenna.dir/almostantenna.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/almostantenna.dir/almostantenna.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jait/dev/algolab/week6/almostantenna/src/almostantenna.cpp -o CMakeFiles/almostantenna.dir/almostantenna.cpp.s

CMakeFiles/almostantenna.dir/almostantenna.cpp.o.requires:
.PHONY : CMakeFiles/almostantenna.dir/almostantenna.cpp.o.requires

CMakeFiles/almostantenna.dir/almostantenna.cpp.o.provides: CMakeFiles/almostantenna.dir/almostantenna.cpp.o.requires
	$(MAKE) -f CMakeFiles/almostantenna.dir/build.make CMakeFiles/almostantenna.dir/almostantenna.cpp.o.provides.build
.PHONY : CMakeFiles/almostantenna.dir/almostantenna.cpp.o.provides

CMakeFiles/almostantenna.dir/almostantenna.cpp.o.provides.build: CMakeFiles/almostantenna.dir/almostantenna.cpp.o

# Object files for target almostantenna
almostantenna_OBJECTS = \
"CMakeFiles/almostantenna.dir/almostantenna.cpp.o"

# External object files for target almostantenna
almostantenna_EXTERNAL_OBJECTS =

almostantenna: CMakeFiles/almostantenna.dir/almostantenna.cpp.o
almostantenna: CMakeFiles/almostantenna.dir/build.make
almostantenna: /usr/lib64/libmpfr.so
almostantenna: /usr/lib64/libgmp.so
almostantenna: /usr/lib/libCGAL_Core.so
almostantenna: /usr/lib/libCGAL.so
almostantenna: /usr/lib64/libboost_thread.so
almostantenna: /usr/lib64/libboost_system.so
almostantenna: /usr/lib/libCGAL_Core.so
almostantenna: /usr/lib/libCGAL.so
almostantenna: /usr/lib64/libboost_thread.so
almostantenna: /usr/lib64/libboost_system.so
almostantenna: CMakeFiles/almostantenna.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable almostantenna"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/almostantenna.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/almostantenna.dir/build: almostantenna
.PHONY : CMakeFiles/almostantenna.dir/build

CMakeFiles/almostantenna.dir/requires: CMakeFiles/almostantenna.dir/almostantenna.cpp.o.requires
.PHONY : CMakeFiles/almostantenna.dir/requires

CMakeFiles/almostantenna.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/almostantenna.dir/cmake_clean.cmake
.PHONY : CMakeFiles/almostantenna.dir/clean

CMakeFiles/almostantenna.dir/depend:
	cd /home/jait/dev/algolab/week6/almostantenna/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jait/dev/algolab/week6/almostantenna/src /home/jait/dev/algolab/week6/almostantenna/src /home/jait/dev/algolab/week6/almostantenna/src /home/jait/dev/algolab/week6/almostantenna/src /home/jait/dev/algolab/week6/almostantenna/src/CMakeFiles/almostantenna.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/almostantenna.dir/depend
