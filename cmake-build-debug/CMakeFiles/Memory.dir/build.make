# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/adri/Downloads/clion-2019.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/adri/Downloads/clion-2019.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adri/Dropbox/Projects/CPP/DruidEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adri/Dropbox/Projects/CPP/DruidEngine/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Memory.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Memory.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Memory.dir/flags.make

CMakeFiles/Memory.dir/code/source/Memory/Allocator.cpp.o: CMakeFiles/Memory.dir/flags.make
CMakeFiles/Memory.dir/code/source/Memory/Allocator.cpp.o: ../code/source/Memory/Allocator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adri/Dropbox/Projects/CPP/DruidEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Memory.dir/code/source/Memory/Allocator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Memory.dir/code/source/Memory/Allocator.cpp.o -c /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/Allocator.cpp

CMakeFiles/Memory.dir/code/source/Memory/Allocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memory.dir/code/source/Memory/Allocator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/Allocator.cpp > CMakeFiles/Memory.dir/code/source/Memory/Allocator.cpp.i

CMakeFiles/Memory.dir/code/source/Memory/Allocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memory.dir/code/source/Memory/Allocator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/Allocator.cpp -o CMakeFiles/Memory.dir/code/source/Memory/Allocator.cpp.s

CMakeFiles/Memory.dir/code/source/Memory/FreeListAllocator.cpp.o: CMakeFiles/Memory.dir/flags.make
CMakeFiles/Memory.dir/code/source/Memory/FreeListAllocator.cpp.o: ../code/source/Memory/FreeListAllocator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adri/Dropbox/Projects/CPP/DruidEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Memory.dir/code/source/Memory/FreeListAllocator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Memory.dir/code/source/Memory/FreeListAllocator.cpp.o -c /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/FreeListAllocator.cpp

CMakeFiles/Memory.dir/code/source/Memory/FreeListAllocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memory.dir/code/source/Memory/FreeListAllocator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/FreeListAllocator.cpp > CMakeFiles/Memory.dir/code/source/Memory/FreeListAllocator.cpp.i

CMakeFiles/Memory.dir/code/source/Memory/FreeListAllocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memory.dir/code/source/Memory/FreeListAllocator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/FreeListAllocator.cpp -o CMakeFiles/Memory.dir/code/source/Memory/FreeListAllocator.cpp.s

CMakeFiles/Memory.dir/code/source/Memory/LinearAllocator.cpp.o: CMakeFiles/Memory.dir/flags.make
CMakeFiles/Memory.dir/code/source/Memory/LinearAllocator.cpp.o: ../code/source/Memory/LinearAllocator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adri/Dropbox/Projects/CPP/DruidEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Memory.dir/code/source/Memory/LinearAllocator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Memory.dir/code/source/Memory/LinearAllocator.cpp.o -c /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/LinearAllocator.cpp

CMakeFiles/Memory.dir/code/source/Memory/LinearAllocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memory.dir/code/source/Memory/LinearAllocator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/LinearAllocator.cpp > CMakeFiles/Memory.dir/code/source/Memory/LinearAllocator.cpp.i

CMakeFiles/Memory.dir/code/source/Memory/LinearAllocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memory.dir/code/source/Memory/LinearAllocator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/LinearAllocator.cpp -o CMakeFiles/Memory.dir/code/source/Memory/LinearAllocator.cpp.s

CMakeFiles/Memory.dir/code/source/Memory/Memory.cpp.o: CMakeFiles/Memory.dir/flags.make
CMakeFiles/Memory.dir/code/source/Memory/Memory.cpp.o: ../code/source/Memory/Memory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adri/Dropbox/Projects/CPP/DruidEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Memory.dir/code/source/Memory/Memory.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Memory.dir/code/source/Memory/Memory.cpp.o -c /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/Memory.cpp

CMakeFiles/Memory.dir/code/source/Memory/Memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memory.dir/code/source/Memory/Memory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/Memory.cpp > CMakeFiles/Memory.dir/code/source/Memory/Memory.cpp.i

CMakeFiles/Memory.dir/code/source/Memory/Memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memory.dir/code/source/Memory/Memory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/Memory.cpp -o CMakeFiles/Memory.dir/code/source/Memory/Memory.cpp.s

CMakeFiles/Memory.dir/code/source/Memory/PoolAllocator.cpp.o: CMakeFiles/Memory.dir/flags.make
CMakeFiles/Memory.dir/code/source/Memory/PoolAllocator.cpp.o: ../code/source/Memory/PoolAllocator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adri/Dropbox/Projects/CPP/DruidEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Memory.dir/code/source/Memory/PoolAllocator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Memory.dir/code/source/Memory/PoolAllocator.cpp.o -c /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/PoolAllocator.cpp

CMakeFiles/Memory.dir/code/source/Memory/PoolAllocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memory.dir/code/source/Memory/PoolAllocator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/PoolAllocator.cpp > CMakeFiles/Memory.dir/code/source/Memory/PoolAllocator.cpp.i

CMakeFiles/Memory.dir/code/source/Memory/PoolAllocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memory.dir/code/source/Memory/PoolAllocator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/PoolAllocator.cpp -o CMakeFiles/Memory.dir/code/source/Memory/PoolAllocator.cpp.s

CMakeFiles/Memory.dir/code/source/Memory/StackAllocator.cpp.o: CMakeFiles/Memory.dir/flags.make
CMakeFiles/Memory.dir/code/source/Memory/StackAllocator.cpp.o: ../code/source/Memory/StackAllocator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adri/Dropbox/Projects/CPP/DruidEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Memory.dir/code/source/Memory/StackAllocator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Memory.dir/code/source/Memory/StackAllocator.cpp.o -c /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/StackAllocator.cpp

CMakeFiles/Memory.dir/code/source/Memory/StackAllocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Memory.dir/code/source/Memory/StackAllocator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/StackAllocator.cpp > CMakeFiles/Memory.dir/code/source/Memory/StackAllocator.cpp.i

CMakeFiles/Memory.dir/code/source/Memory/StackAllocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Memory.dir/code/source/Memory/StackAllocator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adri/Dropbox/Projects/CPP/DruidEngine/code/source/Memory/StackAllocator.cpp -o CMakeFiles/Memory.dir/code/source/Memory/StackAllocator.cpp.s

Memory: CMakeFiles/Memory.dir/code/source/Memory/Allocator.cpp.o
Memory: CMakeFiles/Memory.dir/code/source/Memory/FreeListAllocator.cpp.o
Memory: CMakeFiles/Memory.dir/code/source/Memory/LinearAllocator.cpp.o
Memory: CMakeFiles/Memory.dir/code/source/Memory/Memory.cpp.o
Memory: CMakeFiles/Memory.dir/code/source/Memory/PoolAllocator.cpp.o
Memory: CMakeFiles/Memory.dir/code/source/Memory/StackAllocator.cpp.o
Memory: CMakeFiles/Memory.dir/build.make

.PHONY : Memory

# Rule to build all files generated by this target.
CMakeFiles/Memory.dir/build: Memory

.PHONY : CMakeFiles/Memory.dir/build

CMakeFiles/Memory.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Memory.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Memory.dir/clean

CMakeFiles/Memory.dir/depend:
	cd /home/adri/Dropbox/Projects/CPP/DruidEngine/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adri/Dropbox/Projects/CPP/DruidEngine /home/adri/Dropbox/Projects/CPP/DruidEngine /home/adri/Dropbox/Projects/CPP/DruidEngine/cmake-build-debug /home/adri/Dropbox/Projects/CPP/DruidEngine/cmake-build-debug /home/adri/Dropbox/Projects/CPP/DruidEngine/cmake-build-debug/CMakeFiles/Memory.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Memory.dir/depend

