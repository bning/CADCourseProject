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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bo/Documents/CAD/CADCourseProject/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bo/Documents/CAD/CADCourseProject/bin

# Include any dependencies generated for this target.
include trans/CMakeFiles/trans.dir/depend.make

# Include the progress variables for this target.
include trans/CMakeFiles/trans.dir/progress.make

# Include the compile flags for this target's objects.
include trans/CMakeFiles/trans.dir/flags.make

trans/CMakeFiles/trans.dir/Image2TriMesh.o: trans/CMakeFiles/trans.dir/flags.make
trans/CMakeFiles/trans.dir/Image2TriMesh.o: /home/bo/Documents/CAD/CADCourseProject/src/trans/Image2TriMesh.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bo/Documents/CAD/CADCourseProject/bin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object trans/CMakeFiles/trans.dir/Image2TriMesh.o"
	cd /home/bo/Documents/CAD/CADCourseProject/bin/trans && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/trans.dir/Image2TriMesh.o -c /home/bo/Documents/CAD/CADCourseProject/src/trans/Image2TriMesh.cpp

trans/CMakeFiles/trans.dir/Image2TriMesh.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/trans.dir/Image2TriMesh.i"
	cd /home/bo/Documents/CAD/CADCourseProject/bin/trans && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bo/Documents/CAD/CADCourseProject/src/trans/Image2TriMesh.cpp > CMakeFiles/trans.dir/Image2TriMesh.i

trans/CMakeFiles/trans.dir/Image2TriMesh.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/trans.dir/Image2TriMesh.s"
	cd /home/bo/Documents/CAD/CADCourseProject/bin/trans && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bo/Documents/CAD/CADCourseProject/src/trans/Image2TriMesh.cpp -o CMakeFiles/trans.dir/Image2TriMesh.s

trans/CMakeFiles/trans.dir/Image2TriMesh.o.requires:
.PHONY : trans/CMakeFiles/trans.dir/Image2TriMesh.o.requires

trans/CMakeFiles/trans.dir/Image2TriMesh.o.provides: trans/CMakeFiles/trans.dir/Image2TriMesh.o.requires
	$(MAKE) -f trans/CMakeFiles/trans.dir/build.make trans/CMakeFiles/trans.dir/Image2TriMesh.o.provides.build
.PHONY : trans/CMakeFiles/trans.dir/Image2TriMesh.o.provides

trans/CMakeFiles/trans.dir/Image2TriMesh.o.provides.build: trans/CMakeFiles/trans.dir/Image2TriMesh.o

# Object files for target trans
trans_OBJECTS = \
"CMakeFiles/trans.dir/Image2TriMesh.o"

# External object files for target trans
trans_EXTERNAL_OBJECTS =

trans/libtrans.a: trans/CMakeFiles/trans.dir/Image2TriMesh.o
trans/libtrans.a: trans/CMakeFiles/trans.dir/build.make
trans/libtrans.a: trans/CMakeFiles/trans.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libtrans.a"
	cd /home/bo/Documents/CAD/CADCourseProject/bin/trans && $(CMAKE_COMMAND) -P CMakeFiles/trans.dir/cmake_clean_target.cmake
	cd /home/bo/Documents/CAD/CADCourseProject/bin/trans && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/trans.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
trans/CMakeFiles/trans.dir/build: trans/libtrans.a
.PHONY : trans/CMakeFiles/trans.dir/build

trans/CMakeFiles/trans.dir/requires: trans/CMakeFiles/trans.dir/Image2TriMesh.o.requires
.PHONY : trans/CMakeFiles/trans.dir/requires

trans/CMakeFiles/trans.dir/clean:
	cd /home/bo/Documents/CAD/CADCourseProject/bin/trans && $(CMAKE_COMMAND) -P CMakeFiles/trans.dir/cmake_clean.cmake
.PHONY : trans/CMakeFiles/trans.dir/clean

trans/CMakeFiles/trans.dir/depend:
	cd /home/bo/Documents/CAD/CADCourseProject/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bo/Documents/CAD/CADCourseProject/src /home/bo/Documents/CAD/CADCourseProject/src/trans /home/bo/Documents/CAD/CADCourseProject/bin /home/bo/Documents/CAD/CADCourseProject/bin/trans /home/bo/Documents/CAD/CADCourseProject/bin/trans/CMakeFiles/trans.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : trans/CMakeFiles/trans.dir/depend

