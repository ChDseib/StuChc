# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\app\intellij\CLion 2023.3\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "D:\app\intellij\CLion 2023.3\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\project\gitcc\StuChc\StuChc\StuChc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\project\gitcc\StuChc\StuChc\StuChc\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/StuChc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/StuChc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/StuChc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StuChc.dir/flags.make

CMakeFiles/StuChc.dir/main.cpp.obj: CMakeFiles/StuChc.dir/flags.make
CMakeFiles/StuChc.dir/main.cpp.obj: D:/project/gitcc/StuChc/StuChc/StuChc/main.cpp
CMakeFiles/StuChc.dir/main.cpp.obj: CMakeFiles/StuChc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\project\gitcc\StuChc\StuChc\StuChc\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/StuChc.dir/main.cpp.obj"
	D:\app\mingw\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/StuChc.dir/main.cpp.obj -MF CMakeFiles\StuChc.dir\main.cpp.obj.d -o CMakeFiles\StuChc.dir\main.cpp.obj -c D:\project\gitcc\StuChc\StuChc\StuChc\main.cpp

CMakeFiles/StuChc.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/StuChc.dir/main.cpp.i"
	D:\app\mingw\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\project\gitcc\StuChc\StuChc\StuChc\main.cpp > CMakeFiles\StuChc.dir\main.cpp.i

CMakeFiles/StuChc.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/StuChc.dir/main.cpp.s"
	D:\app\mingw\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\project\gitcc\StuChc\StuChc\StuChc\main.cpp -o CMakeFiles\StuChc.dir\main.cpp.s

# Object files for target StuChc
StuChc_OBJECTS = \
"CMakeFiles/StuChc.dir/main.cpp.obj"

# External object files for target StuChc
StuChc_EXTERNAL_OBJECTS =

StuChc.exe: CMakeFiles/StuChc.dir/main.cpp.obj
StuChc.exe: CMakeFiles/StuChc.dir/build.make
StuChc.exe: CMakeFiles/StuChc.dir/linkLibs.rsp
StuChc.exe: CMakeFiles/StuChc.dir/objects1.rsp
StuChc.exe: CMakeFiles/StuChc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\project\gitcc\StuChc\StuChc\StuChc\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable StuChc.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\StuChc.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StuChc.dir/build: StuChc.exe
.PHONY : CMakeFiles/StuChc.dir/build

CMakeFiles/StuChc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\StuChc.dir\cmake_clean.cmake
.PHONY : CMakeFiles/StuChc.dir/clean

CMakeFiles/StuChc.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\project\gitcc\StuChc\StuChc\StuChc D:\project\gitcc\StuChc\StuChc\StuChc D:\project\gitcc\StuChc\StuChc\StuChc\cmake-build-debug D:\project\gitcc\StuChc\StuChc\StuChc\cmake-build-debug D:\project\gitcc\StuChc\StuChc\StuChc\cmake-build-debug\CMakeFiles\StuChc.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/StuChc.dir/depend

