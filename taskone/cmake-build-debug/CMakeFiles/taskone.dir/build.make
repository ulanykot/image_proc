# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\imageproc\taskone

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\imageproc\taskone\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/taskone.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/taskone.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/taskone.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/taskone.dir/flags.make

CMakeFiles/taskone.dir/main.cpp.obj: CMakeFiles/taskone.dir/flags.make
CMakeFiles/taskone.dir/main.cpp.obj: CMakeFiles/taskone.dir/includes_CXX.rsp
CMakeFiles/taskone.dir/main.cpp.obj: C:/imageproc/taskone/main.cpp
CMakeFiles/taskone.dir/main.cpp.obj: CMakeFiles/taskone.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\imageproc\taskone\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/taskone.dir/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/taskone.dir/main.cpp.obj -MF CMakeFiles\taskone.dir\main.cpp.obj.d -o CMakeFiles\taskone.dir\main.cpp.obj -c C:\imageproc\taskone\main.cpp

CMakeFiles/taskone.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/taskone.dir/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\imageproc\taskone\main.cpp > CMakeFiles\taskone.dir\main.cpp.i

CMakeFiles/taskone.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/taskone.dir/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\imageproc\taskone\main.cpp -o CMakeFiles\taskone.dir\main.cpp.s

# Object files for target taskone
taskone_OBJECTS = \
"CMakeFiles/taskone.dir/main.cpp.obj"

# External object files for target taskone
taskone_EXTERNAL_OBJECTS =

taskone.exe: CMakeFiles/taskone.dir/main.cpp.obj
taskone.exe: CMakeFiles/taskone.dir/build.make
taskone.exe: CMakeFiles/taskone.dir/linkLibs.rsp
taskone.exe: CMakeFiles/taskone.dir/objects1.rsp
taskone.exe: CMakeFiles/taskone.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\imageproc\taskone\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable taskone.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\taskone.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/taskone.dir/build: taskone.exe
.PHONY : CMakeFiles/taskone.dir/build

CMakeFiles/taskone.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\taskone.dir\cmake_clean.cmake
.PHONY : CMakeFiles/taskone.dir/clean

CMakeFiles/taskone.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\imageproc\taskone C:\imageproc\taskone C:\imageproc\taskone\cmake-build-debug C:\imageproc\taskone\cmake-build-debug C:\imageproc\taskone\cmake-build-debug\CMakeFiles\taskone.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/taskone.dir/depend

