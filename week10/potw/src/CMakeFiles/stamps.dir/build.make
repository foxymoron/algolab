# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /nas/jdixit/algolab/week10/potw/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /nas/jdixit/algolab/week10/potw/src

# Include any dependencies generated for this target.
include CMakeFiles/stamps.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/stamps.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stamps.dir/flags.make

CMakeFiles/stamps.dir/stamps.cpp.o: CMakeFiles/stamps.dir/flags.make
CMakeFiles/stamps.dir/stamps.cpp.o: stamps.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /nas/jdixit/algolab/week10/potw/src/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/stamps.dir/stamps.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/stamps.dir/stamps.cpp.o -c /nas/jdixit/algolab/week10/potw/src/stamps.cpp

CMakeFiles/stamps.dir/stamps.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stamps.dir/stamps.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /nas/jdixit/algolab/week10/potw/src/stamps.cpp > CMakeFiles/stamps.dir/stamps.cpp.i

CMakeFiles/stamps.dir/stamps.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stamps.dir/stamps.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /nas/jdixit/algolab/week10/potw/src/stamps.cpp -o CMakeFiles/stamps.dir/stamps.cpp.s

CMakeFiles/stamps.dir/stamps.cpp.o.requires:
.PHONY : CMakeFiles/stamps.dir/stamps.cpp.o.requires

CMakeFiles/stamps.dir/stamps.cpp.o.provides: CMakeFiles/stamps.dir/stamps.cpp.o.requires
	$(MAKE) -f CMakeFiles/stamps.dir/build.make CMakeFiles/stamps.dir/stamps.cpp.o.provides.build
.PHONY : CMakeFiles/stamps.dir/stamps.cpp.o.provides

CMakeFiles/stamps.dir/stamps.cpp.o.provides.build: CMakeFiles/stamps.dir/stamps.cpp.o

# Object files for target stamps
stamps_OBJECTS = \
"CMakeFiles/stamps.dir/stamps.cpp.o"

# External object files for target stamps
stamps_EXTERNAL_OBJECTS =

stamps: CMakeFiles/stamps.dir/stamps.cpp.o
stamps: CMakeFiles/stamps.dir/build.make
stamps: /usr/lib64/libmpfr.so
stamps: /usr/lib64/libgmp.so
stamps: /usr/lib64/libCGAL_Core.so
stamps: /usr/lib64/libCGAL.so
stamps: /usr/lib64/libboost_thread-mt.so
stamps: /usr/lib64/libboost_system-mt.so
stamps: /usr/lib64/libCGAL_Core.so
stamps: /usr/lib64/libCGAL.so
stamps: /usr/lib64/libboost_thread-mt.so
stamps: /usr/lib64/libboost_system-mt.so
stamps: CMakeFiles/stamps.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable stamps"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stamps.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stamps.dir/build: stamps
.PHONY : CMakeFiles/stamps.dir/build

CMakeFiles/stamps.dir/requires: CMakeFiles/stamps.dir/stamps.cpp.o.requires
.PHONY : CMakeFiles/stamps.dir/requires

CMakeFiles/stamps.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stamps.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stamps.dir/clean

CMakeFiles/stamps.dir/depend:
	cd /nas/jdixit/algolab/week10/potw/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /nas/jdixit/algolab/week10/potw/src /nas/jdixit/algolab/week10/potw/src /nas/jdixit/algolab/week10/potw/src /nas/jdixit/algolab/week10/potw/src /nas/jdixit/algolab/week10/potw/src/CMakeFiles/stamps.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stamps.dir/depend

