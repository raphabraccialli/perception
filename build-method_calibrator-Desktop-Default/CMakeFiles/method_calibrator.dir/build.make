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
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/livia/nao/workspace/perception/method_calibrator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/livia/nao/workspace/perception/build-method_calibrator-Desktop-Default

# Include any dependencies generated for this target.
include CMakeFiles/method_calibrator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/method_calibrator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/method_calibrator.dir/flags.make

CMakeFiles/method_calibrator.dir/main.cpp.o: CMakeFiles/method_calibrator.dir/flags.make
CMakeFiles/method_calibrator.dir/main.cpp.o: /home/livia/nao/workspace/perception/method_calibrator/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/livia/nao/workspace/perception/build-method_calibrator-Desktop-Default/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/method_calibrator.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/method_calibrator.dir/main.cpp.o -c /home/livia/nao/workspace/perception/method_calibrator/main.cpp

CMakeFiles/method_calibrator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/method_calibrator.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/livia/nao/workspace/perception/method_calibrator/main.cpp > CMakeFiles/method_calibrator.dir/main.cpp.i

CMakeFiles/method_calibrator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/method_calibrator.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/livia/nao/workspace/perception/method_calibrator/main.cpp -o CMakeFiles/method_calibrator.dir/main.cpp.s

CMakeFiles/method_calibrator.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/method_calibrator.dir/main.cpp.o.requires

CMakeFiles/method_calibrator.dir/main.cpp.o.provides: CMakeFiles/method_calibrator.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/method_calibrator.dir/build.make CMakeFiles/method_calibrator.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/method_calibrator.dir/main.cpp.o.provides

CMakeFiles/method_calibrator.dir/main.cpp.o.provides.build: CMakeFiles/method_calibrator.dir/main.cpp.o

CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o: CMakeFiles/method_calibrator.dir/flags.make
CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o: /home/livia/nao/workspace/perception/method_calibrator/quaternaryMask.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/livia/nao/workspace/perception/build-method_calibrator-Desktop-Default/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o -c /home/livia/nao/workspace/perception/method_calibrator/quaternaryMask.cpp

CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/livia/nao/workspace/perception/method_calibrator/quaternaryMask.cpp > CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.i

CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/livia/nao/workspace/perception/method_calibrator/quaternaryMask.cpp -o CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.s

CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o.requires:
.PHONY : CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o.requires

CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o.provides: CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o.requires
	$(MAKE) -f CMakeFiles/method_calibrator.dir/build.make CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o.provides.build
.PHONY : CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o.provides

CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o.provides.build: CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o

CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o: CMakeFiles/method_calibrator.dir/flags.make
CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o: /home/livia/nao/workspace/perception/method_calibrator/houghCirclesContrast.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/livia/nao/workspace/perception/build-method_calibrator-Desktop-Default/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o -c /home/livia/nao/workspace/perception/method_calibrator/houghCirclesContrast.cpp

CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/livia/nao/workspace/perception/method_calibrator/houghCirclesContrast.cpp > CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.i

CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/livia/nao/workspace/perception/method_calibrator/houghCirclesContrast.cpp -o CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.s

CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o.requires:
.PHONY : CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o.requires

CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o.provides: CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o.requires
	$(MAKE) -f CMakeFiles/method_calibrator.dir/build.make CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o.provides.build
.PHONY : CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o.provides

CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o.provides.build: CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o

# Object files for target method_calibrator
method_calibrator_OBJECTS = \
"CMakeFiles/method_calibrator.dir/main.cpp.o" \
"CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o" \
"CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o"

# External object files for target method_calibrator
method_calibrator_EXTERNAL_OBJECTS =

method_calibrator: CMakeFiles/method_calibrator.dir/main.cpp.o
method_calibrator: CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o
method_calibrator: CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o
method_calibrator: CMakeFiles/method_calibrator.dir/build.make
method_calibrator: /usr/local/lib/libopencv_videostab.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_video.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_ts.a
method_calibrator: /usr/local/lib/libopencv_superres.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_stitching.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_photo.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_ocl.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_objdetect.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_nonfree.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_ml.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_legacy.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_imgproc.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_highgui.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_gpu.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_flann.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_features2d.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_core.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_contrib.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_calib3d.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_nonfree.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_ocl.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_gpu.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_photo.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_objdetect.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_legacy.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_video.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_ml.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_calib3d.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_features2d.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_highgui.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_imgproc.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_flann.so.2.4.9
method_calibrator: /usr/local/lib/libopencv_core.so.2.4.9
method_calibrator: CMakeFiles/method_calibrator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable method_calibrator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/method_calibrator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/method_calibrator.dir/build: method_calibrator
.PHONY : CMakeFiles/method_calibrator.dir/build

CMakeFiles/method_calibrator.dir/requires: CMakeFiles/method_calibrator.dir/main.cpp.o.requires
CMakeFiles/method_calibrator.dir/requires: CMakeFiles/method_calibrator.dir/quaternaryMask.cpp.o.requires
CMakeFiles/method_calibrator.dir/requires: CMakeFiles/method_calibrator.dir/houghCirclesContrast.cpp.o.requires
.PHONY : CMakeFiles/method_calibrator.dir/requires

CMakeFiles/method_calibrator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/method_calibrator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/method_calibrator.dir/clean

CMakeFiles/method_calibrator.dir/depend:
	cd /home/livia/nao/workspace/perception/build-method_calibrator-Desktop-Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/livia/nao/workspace/perception/method_calibrator /home/livia/nao/workspace/perception/method_calibrator /home/livia/nao/workspace/perception/build-method_calibrator-Desktop-Default /home/livia/nao/workspace/perception/build-method_calibrator-Desktop-Default /home/livia/nao/workspace/perception/build-method_calibrator-Desktop-Default/CMakeFiles/method_calibrator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/method_calibrator.dir/depend

