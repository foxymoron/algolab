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
CMAKE_SOURCE_DIR = /home/jait/dev/algolab/week8/potw/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jait/dev/algolab/week8/potw/src

# Include any dependencies generated for this target.
include CMakeFiles/collisions.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/collisions.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/collisions.dir/flags.make

CMakeFiles/collisions.dir/collisions.cpp.o: CMakeFiles/collisions.dir/flags.make
CMakeFiles/collisions.dir/collisions.cpp.o: collisions.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jait/dev/algolab/week8/potw/src/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/collisions.dir/collisions.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/collisions.dir/collisions.cpp.o -c /home/jait/dev/algolab/week8/potw/src/collisions.cpp

CMakeFiles/collisions.dir/collisions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/collisions.dir/collisions.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jait/dev/algolab/week8/potw/src/collisions.cpp > CMakeFiles/collisions.dir/collisions.cpp.i

CMakeFiles/collisions.dir/collisions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/collisions.dir/collisions.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jait/dev/algolab/week8/potw/src/collisions.cpp -o CMakeFiles/collisions.dir/collisions.cpp.s

CMakeFiles/collisions.dir/collisions.cpp.o.requires:
.PHONY : CMakeFiles/collisions.dir/collisions.cpp.o.requires

CMakeFiles/collisions.dir/collisions.cpp.o.provides: CMakeFiles/collisions.dir/collisions.cpp.o.requires
	$(MAKE) -f CMakeFiles/collisions.dir/build.make CMakeFiles/collisions.dir/collisions.cpp.o.provides.build
.PHONY : CMakeFiles/collisions.dir/collisions.cpp.o.provides

CMakeFiles/collisions.dir/collisions.cpp.o.provides.build: CMakeFiles/collisions.dir/collisions.cpp.o

# Object files for target collisions
collisions_OBJECTS = \
"CMakeFiles/collisions.dir/collisions.cpp.o"

# External object files for target collisions
collisions_EXTERNAL_OBJECTS =

collisions: CMakeFiles/collisions.dir/collisions.cpp.o
collisions: CMakeFiles/collisions.dir/build.make
collisions: /usr/lib64/libmpfr.so
collisions: /usr/lib64/libgmp.so
collisions: /usr/lib/libCGAL_Core.so
collisions: /usr/lib/libCGAL.so
collisions: /usr/lib64/libboost_thread.so
collisions: /usr/lib64/libboost_system.so
collisions: /usr/lib/libCGAL_Core.so
collisions: /usr/lib/libCGAL.so
collisions: /usr/lib64/libboost_thread.so
collisions: /usr/lib64/libboost_system.so
collisions: CMakeFiles/collisions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable collisions"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/collisions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/collisions.dir/build: collisions
.PHONY : CMakeFiles/collisions.dir/build

CMakeFiles/collisions.dir/requires: CMakeFiles/collisions.dir/collisions.cpp.o.requires
.PHONY : CMakeFiles/collisions.dir/requires

CMakeFiles/collisions.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/collisions.dir/cmake_clean.cmake
.PHONY : CMakeFiles/collisions.dir/clean

CMakeFiles/collisions.dir/depend:
	cd /home/jait/dev/algolab/week8/potw/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jait/dev/algolab/week8/potw/src /home/jait/dev/algolab/week8/potw/src /home/jait/dev/algolab/week8/potw/src /home/jait/dev/algolab/week8/potw/src /home/jait/dev/algolab/week8/potw/src/CMakeFiles/collisions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/collisions.dir/depend

