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
CMAKE_COMMAND = /home/esh/Qt/Tools/CMake/bin/cmake

# The command to remove a file.
RM = /home/esh/Qt/Tools/CMake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/esh/Рабочий стол/git_info_test/writer"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/esh/Рабочий стол/git_info_test/build-writer-Desktop-Debug"

# Include any dependencies generated for this target.
include CMakeFiles/writer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/writer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/writer.dir/flags.make

CMakeFiles/writer.dir/writer.cpp.o: CMakeFiles/writer.dir/flags.make
CMakeFiles/writer.dir/writer.cpp.o: /home/esh/Рабочий\ стол/git_info_test/writer/writer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/esh/Рабочий стол/git_info_test/build-writer-Desktop-Debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/writer.dir/writer.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/writer.dir/writer.cpp.o -c "/home/esh/Рабочий стол/git_info_test/writer/writer.cpp"

CMakeFiles/writer.dir/writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/writer.dir/writer.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/esh/Рабочий стол/git_info_test/writer/writer.cpp" > CMakeFiles/writer.dir/writer.cpp.i

CMakeFiles/writer.dir/writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/writer.dir/writer.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/esh/Рабочий стол/git_info_test/writer/writer.cpp" -o CMakeFiles/writer.dir/writer.cpp.s

CMakeFiles/writer.dir/sharedbuf.cpp.o: CMakeFiles/writer.dir/flags.make
CMakeFiles/writer.dir/sharedbuf.cpp.o: /home/esh/Рабочий\ стол/git_info_test/writer/sharedbuf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/esh/Рабочий стол/git_info_test/build-writer-Desktop-Debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/writer.dir/sharedbuf.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/writer.dir/sharedbuf.cpp.o -c "/home/esh/Рабочий стол/git_info_test/writer/sharedbuf.cpp"

CMakeFiles/writer.dir/sharedbuf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/writer.dir/sharedbuf.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/esh/Рабочий стол/git_info_test/writer/sharedbuf.cpp" > CMakeFiles/writer.dir/sharedbuf.cpp.i

CMakeFiles/writer.dir/sharedbuf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/writer.dir/sharedbuf.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/esh/Рабочий стол/git_info_test/writer/sharedbuf.cpp" -o CMakeFiles/writer.dir/sharedbuf.cpp.s

# Object files for target writer
writer_OBJECTS = \
"CMakeFiles/writer.dir/writer.cpp.o" \
"CMakeFiles/writer.dir/sharedbuf.cpp.o"

# External object files for target writer
writer_EXTERNAL_OBJECTS =

writer: CMakeFiles/writer.dir/writer.cpp.o
writer: CMakeFiles/writer.dir/sharedbuf.cpp.o
writer: CMakeFiles/writer.dir/build.make
writer: CMakeFiles/writer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/esh/Рабочий стол/git_info_test/build-writer-Desktop-Debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable writer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/writer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/writer.dir/build: writer

.PHONY : CMakeFiles/writer.dir/build

CMakeFiles/writer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/writer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/writer.dir/clean

CMakeFiles/writer.dir/depend:
	cd "/home/esh/Рабочий стол/git_info_test/build-writer-Desktop-Debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/esh/Рабочий стол/git_info_test/writer" "/home/esh/Рабочий стол/git_info_test/writer" "/home/esh/Рабочий стол/git_info_test/build-writer-Desktop-Debug" "/home/esh/Рабочий стол/git_info_test/build-writer-Desktop-Debug" "/home/esh/Рабочий стол/git_info_test/build-writer-Desktop-Debug/CMakeFiles/writer.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/writer.dir/depend

