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
CMAKE_COMMAND = /home/wx/Desktop/clion-2020.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/wx/Desktop/clion-2020.3.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wx/CLionProjects/myHttpServer_

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wx/CLionProjects/myHttpServer_/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/common.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/common.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/common.dir/flags.make

CMakeFiles/common.dir/Epoll.cpp.o: CMakeFiles/common.dir/flags.make
CMakeFiles/common.dir/Epoll.cpp.o: ../Epoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wx/CLionProjects/myHttpServer_/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/common.dir/Epoll.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/common.dir/Epoll.cpp.o -c /home/wx/CLionProjects/myHttpServer_/Epoll.cpp

CMakeFiles/common.dir/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/Epoll.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wx/CLionProjects/myHttpServer_/Epoll.cpp > CMakeFiles/common.dir/Epoll.cpp.i

CMakeFiles/common.dir/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/Epoll.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wx/CLionProjects/myHttpServer_/Epoll.cpp -o CMakeFiles/common.dir/Epoll.cpp.s

CMakeFiles/common.dir/ThreadPool.cpp.o: CMakeFiles/common.dir/flags.make
CMakeFiles/common.dir/ThreadPool.cpp.o: ../ThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wx/CLionProjects/myHttpServer_/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/common.dir/ThreadPool.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/common.dir/ThreadPool.cpp.o -c /home/wx/CLionProjects/myHttpServer_/ThreadPool.cpp

CMakeFiles/common.dir/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/ThreadPool.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wx/CLionProjects/myHttpServer_/ThreadPool.cpp > CMakeFiles/common.dir/ThreadPool.cpp.i

CMakeFiles/common.dir/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/ThreadPool.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wx/CLionProjects/myHttpServer_/ThreadPool.cpp -o CMakeFiles/common.dir/ThreadPool.cpp.s

CMakeFiles/common.dir/main.cpp.o: CMakeFiles/common.dir/flags.make
CMakeFiles/common.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wx/CLionProjects/myHttpServer_/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/common.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/common.dir/main.cpp.o -c /home/wx/CLionProjects/myHttpServer_/main.cpp

CMakeFiles/common.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wx/CLionProjects/myHttpServer_/main.cpp > CMakeFiles/common.dir/main.cpp.i

CMakeFiles/common.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wx/CLionProjects/myHttpServer_/main.cpp -o CMakeFiles/common.dir/main.cpp.s

CMakeFiles/common.dir/requestData.cpp.o: CMakeFiles/common.dir/flags.make
CMakeFiles/common.dir/requestData.cpp.o: ../requestData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wx/CLionProjects/myHttpServer_/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/common.dir/requestData.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/common.dir/requestData.cpp.o -c /home/wx/CLionProjects/myHttpServer_/requestData.cpp

CMakeFiles/common.dir/requestData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/requestData.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wx/CLionProjects/myHttpServer_/requestData.cpp > CMakeFiles/common.dir/requestData.cpp.i

CMakeFiles/common.dir/requestData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/requestData.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wx/CLionProjects/myHttpServer_/requestData.cpp -o CMakeFiles/common.dir/requestData.cpp.s

CMakeFiles/common.dir/util.cpp.o: CMakeFiles/common.dir/flags.make
CMakeFiles/common.dir/util.cpp.o: ../util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wx/CLionProjects/myHttpServer_/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/common.dir/util.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/common.dir/util.cpp.o -c /home/wx/CLionProjects/myHttpServer_/util.cpp

CMakeFiles/common.dir/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/util.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wx/CLionProjects/myHttpServer_/util.cpp > CMakeFiles/common.dir/util.cpp.i

CMakeFiles/common.dir/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/util.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wx/CLionProjects/myHttpServer_/util.cpp -o CMakeFiles/common.dir/util.cpp.s

# Object files for target common
common_OBJECTS = \
"CMakeFiles/common.dir/Epoll.cpp.o" \
"CMakeFiles/common.dir/ThreadPool.cpp.o" \
"CMakeFiles/common.dir/main.cpp.o" \
"CMakeFiles/common.dir/requestData.cpp.o" \
"CMakeFiles/common.dir/util.cpp.o"

# External object files for target common
common_EXTERNAL_OBJECTS =

libcommon.a: CMakeFiles/common.dir/Epoll.cpp.o
libcommon.a: CMakeFiles/common.dir/ThreadPool.cpp.o
libcommon.a: CMakeFiles/common.dir/main.cpp.o
libcommon.a: CMakeFiles/common.dir/requestData.cpp.o
libcommon.a: CMakeFiles/common.dir/util.cpp.o
libcommon.a: CMakeFiles/common.dir/build.make
libcommon.a: CMakeFiles/common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wx/CLionProjects/myHttpServer_/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libcommon.a"
	$(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/common.dir/build: libcommon.a

.PHONY : CMakeFiles/common.dir/build

CMakeFiles/common.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean.cmake
.PHONY : CMakeFiles/common.dir/clean

CMakeFiles/common.dir/depend:
	cd /home/wx/CLionProjects/myHttpServer_/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wx/CLionProjects/myHttpServer_ /home/wx/CLionProjects/myHttpServer_ /home/wx/CLionProjects/myHttpServer_/cmake-build-debug /home/wx/CLionProjects/myHttpServer_/cmake-build-debug /home/wx/CLionProjects/myHttpServer_/cmake-build-debug/CMakeFiles/common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/common.dir/depend

