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
CMAKE_SOURCE_DIR = /home/jait/dev/algolab/week8/diets/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jait/dev/algolab/week8/diets/src

# Include any dependencies generated for this target.
include CMakeFiles/diets.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/diets.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/diets.dir/flags.make

CMakeFiles/diets.dir/diets.cpp.o: CMakeFiles/diets.dir/flags.make
CMakeFiles/diets.dir/diets.cpp.o: diets.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jait/dev/algolab/week8/diets/src/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/diets.dir/diets.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/diets.dir/diets.cpp.o -c /home/jait/dev/algolab/week8/diets/src/diets.cpp

CMakeFiles/diets.dir/diets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/diets.dir/diets.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jait/dev/algolab/week8/diets/src/diets.cpp > CMakeFiles/diets.dir/diets.cpp.i

CMakeFiles/diets.dir/diets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/diets.dir/diets.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jait/dev/algolab/week8/diets/src/diets.cpp -o CMakeFiles/diets.dir/diets.cpp.s

CMakeFiles/diets.dir/diets.cpp.o.requires:
.PHONY : CMakeFiles/diets.dir/diets.cpp.o.requires

CMakeFiles/diets.dir/diets.cpp.o.provides: CMakeFiles/diets.dir/diets.cpp.o.requires
	$(MAKE) -f CMakeFiles/diets.dir/build.make CMakeFiles/diets.dir/diets.cpp.o.provides.build
.PHONY : CMakeFiles/diets.dir/diets.cpp.o.provides

CMakeFiles/diets.dir/diets.cpp.o.provides.build: CMakeFiles/diets.dir/diets.cpp.o

# Object files for target diets
diets_OBJECTS = \
"CMakeFiles/diets.dir/diets.cpp.o"

# External object files for target diets
diets_EXTERNAL_OBJECTS =

diets: CMakeFiles/diets.dir/diets.cpp.o
diets: CMakeFiles/diets.dir/build.make
diets: /usr/lib64/libmpfr.so
diets: /usr/lib64/libgmp.so
diets: /usr/lib/libCGAL_Core.so
diets: /usr/lib/libCGAL.so
diets: /usr/lib64/libboost_thread.so
diets: /usr/lib64/libboost_system.so
diets: /usr/lib/libCGAL_Core.so
diets: /usr/lib/libCGAL.so
diets: /usr/lib64/libboost_thread.so
diets: /usr/lib64/libboost_system.so
diets: CMakeFiles/diets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable diets"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/diets.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/diets.dir/build: diets
.PHONY : CMakeFiles/diets.dir/build

CMakeFiles/diets.dir/requires: CMakeFiles/diets.dir/diets.cpp.o.requires
.PHONY : CMakeFiles/diets.dir/requires

CMakeFiles/diets.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/diets.dir/cmake_clean.cmake
.PHONY : CMakeFiles/diets.dir/clean

CMakeFiles/diets.dir/depend:
	cd /home/jait/dev/algolab/week8/diets/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jait/dev/algolab/week8/diets/src /home/jait/dev/algolab/week8/diets/src /home/jait/dev/algolab/week8/diets/src /home/jait/dev/algolab/week8/diets/src /home/jait/dev/algolab/week8/diets/src/CMakeFiles/diets.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/diets.dir/depend

