# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = "/Users/pablodeputter/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.8194.17/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/pablodeputter/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.8194.17/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pablodeputter/Documents/GitHub/engine_computer_graphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/engine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/engine.dir/flags.make

CMakeFiles/engine.dir/src/easy_image.cc.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/src/easy_image.cc.o: ../src/easy_image.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/engine.dir/src/easy_image.cc.o"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/src/easy_image.cc.o -c /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/easy_image.cc

CMakeFiles/engine.dir/src/easy_image.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/src/easy_image.cc.i"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/easy_image.cc > CMakeFiles/engine.dir/src/easy_image.cc.i

CMakeFiles/engine.dir/src/easy_image.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/src/easy_image.cc.s"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/easy_image.cc -o CMakeFiles/engine.dir/src/easy_image.cc.s

CMakeFiles/engine.dir/src/engine.cc.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/src/engine.cc.o: ../src/engine.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/engine.dir/src/engine.cc.o"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/src/engine.cc.o -c /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/engine.cc

CMakeFiles/engine.dir/src/engine.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/src/engine.cc.i"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/engine.cc > CMakeFiles/engine.dir/src/engine.cc.i

CMakeFiles/engine.dir/src/engine.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/src/engine.cc.s"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/engine.cc -o CMakeFiles/engine.dir/src/engine.cc.s

CMakeFiles/engine.dir/src/ini_configuration.cc.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/src/ini_configuration.cc.o: ../src/ini_configuration.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/engine.dir/src/ini_configuration.cc.o"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/src/ini_configuration.cc.o -c /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/ini_configuration.cc

CMakeFiles/engine.dir/src/ini_configuration.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/src/ini_configuration.cc.i"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/ini_configuration.cc > CMakeFiles/engine.dir/src/ini_configuration.cc.i

CMakeFiles/engine.dir/src/ini_configuration.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/src/ini_configuration.cc.s"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/ini_configuration.cc -o CMakeFiles/engine.dir/src/ini_configuration.cc.s

CMakeFiles/engine.dir/src/Line2D.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/src/Line2D.cpp.o: ../src/Line2D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/engine.dir/src/Line2D.cpp.o"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/src/Line2D.cpp.o -c /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Line2D.cpp

CMakeFiles/engine.dir/src/Line2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/src/Line2D.cpp.i"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Line2D.cpp > CMakeFiles/engine.dir/src/Line2D.cpp.i

CMakeFiles/engine.dir/src/Line2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/src/Line2D.cpp.s"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Line2D.cpp -o CMakeFiles/engine.dir/src/Line2D.cpp.s

CMakeFiles/engine.dir/src/Color.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/src/Color.cpp.o: ../src/Color.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/engine.dir/src/Color.cpp.o"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/src/Color.cpp.o -c /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Color.cpp

CMakeFiles/engine.dir/src/Color.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/src/Color.cpp.i"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Color.cpp > CMakeFiles/engine.dir/src/Color.cpp.i

CMakeFiles/engine.dir/src/Color.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/src/Color.cpp.s"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Color.cpp -o CMakeFiles/engine.dir/src/Color.cpp.s

CMakeFiles/engine.dir/src/l_parser.cc.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/src/l_parser.cc.o: ../src/l_parser.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/engine.dir/src/l_parser.cc.o"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/src/l_parser.cc.o -c /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/l_parser.cc

CMakeFiles/engine.dir/src/l_parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/src/l_parser.cc.i"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/l_parser.cc > CMakeFiles/engine.dir/src/l_parser.cc.i

CMakeFiles/engine.dir/src/l_parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/src/l_parser.cc.s"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/l_parser.cc -o CMakeFiles/engine.dir/src/l_parser.cc.s

CMakeFiles/engine.dir/src/Point2D.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/src/Point2D.cpp.o: ../src/Point2D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/engine.dir/src/Point2D.cpp.o"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/src/Point2D.cpp.o -c /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Point2D.cpp

CMakeFiles/engine.dir/src/Point2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/src/Point2D.cpp.i"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Point2D.cpp > CMakeFiles/engine.dir/src/Point2D.cpp.i

CMakeFiles/engine.dir/src/Point2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/src/Point2D.cpp.s"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Point2D.cpp -o CMakeFiles/engine.dir/src/Point2D.cpp.s

CMakeFiles/engine.dir/src/Face.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/src/Face.cpp.o: ../src/Face.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/engine.dir/src/Face.cpp.o"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/src/Face.cpp.o -c /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Face.cpp

CMakeFiles/engine.dir/src/Face.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/src/Face.cpp.i"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Face.cpp > CMakeFiles/engine.dir/src/Face.cpp.i

CMakeFiles/engine.dir/src/Face.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/src/Face.cpp.s"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Face.cpp -o CMakeFiles/engine.dir/src/Face.cpp.s

CMakeFiles/engine.dir/src/Figure.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/src/Figure.cpp.o: ../src/Figure.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/engine.dir/src/Figure.cpp.o"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/src/Figure.cpp.o -c /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Figure.cpp

CMakeFiles/engine.dir/src/Figure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/src/Figure.cpp.i"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Figure.cpp > CMakeFiles/engine.dir/src/Figure.cpp.i

CMakeFiles/engine.dir/src/Figure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/src/Figure.cpp.s"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/Figure.cpp -o CMakeFiles/engine.dir/src/Figure.cpp.s

CMakeFiles/engine.dir/src/vector3d.cc.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/src/vector3d.cc.o: ../src/vector3d.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/engine.dir/src/vector3d.cc.o"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/src/vector3d.cc.o -c /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/vector3d.cc

CMakeFiles/engine.dir/src/vector3d.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/src/vector3d.cc.i"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/vector3d.cc > CMakeFiles/engine.dir/src/vector3d.cc.i

CMakeFiles/engine.dir/src/vector3d.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/src/vector3d.cc.s"
	/Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/src/vector3d.cc -o CMakeFiles/engine.dir/src/vector3d.cc.s

# Object files for target engine
engine_OBJECTS = \
"CMakeFiles/engine.dir/src/easy_image.cc.o" \
"CMakeFiles/engine.dir/src/engine.cc.o" \
"CMakeFiles/engine.dir/src/ini_configuration.cc.o" \
"CMakeFiles/engine.dir/src/Line2D.cpp.o" \
"CMakeFiles/engine.dir/src/Color.cpp.o" \
"CMakeFiles/engine.dir/src/l_parser.cc.o" \
"CMakeFiles/engine.dir/src/Point2D.cpp.o" \
"CMakeFiles/engine.dir/src/Face.cpp.o" \
"CMakeFiles/engine.dir/src/Figure.cpp.o" \
"CMakeFiles/engine.dir/src/vector3d.cc.o"

# External object files for target engine
engine_EXTERNAL_OBJECTS =

engine: CMakeFiles/engine.dir/src/easy_image.cc.o
engine: CMakeFiles/engine.dir/src/engine.cc.o
engine: CMakeFiles/engine.dir/src/ini_configuration.cc.o
engine: CMakeFiles/engine.dir/src/Line2D.cpp.o
engine: CMakeFiles/engine.dir/src/Color.cpp.o
engine: CMakeFiles/engine.dir/src/l_parser.cc.o
engine: CMakeFiles/engine.dir/src/Point2D.cpp.o
engine: CMakeFiles/engine.dir/src/Face.cpp.o
engine: CMakeFiles/engine.dir/src/Figure.cpp.o
engine: CMakeFiles/engine.dir/src/vector3d.cc.o
engine: CMakeFiles/engine.dir/build.make
engine: CMakeFiles/engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/engine.dir/build: engine

.PHONY : CMakeFiles/engine.dir/build

CMakeFiles/engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/engine.dir/clean

CMakeFiles/engine.dir/depend:
	cd /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pablodeputter/Documents/GitHub/engine_computer_graphics /Users/pablodeputter/Documents/GitHub/engine_computer_graphics /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug /Users/pablodeputter/Documents/GitHub/engine_computer_graphics/cmake-build-debug/CMakeFiles/engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/engine.dir/depend

