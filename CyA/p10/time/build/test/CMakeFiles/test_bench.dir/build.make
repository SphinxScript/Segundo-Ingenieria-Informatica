# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/build

# Include any dependencies generated for this target.
include test/CMakeFiles/test_bench.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/test_bench.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_bench.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_bench.dir/flags.make

test/CMakeFiles/test_bench.dir/src/test_bench.cpp.o: test/CMakeFiles/test_bench.dir/flags.make
test/CMakeFiles/test_bench.dir/src/test_bench.cpp.o: /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/test/src/test_bench.cpp
test/CMakeFiles/test_bench.dir/src/test_bench.cpp.o: test/CMakeFiles/test_bench.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test_bench.dir/src/test_bench.cpp.o"
	cd /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/test_bench.dir/src/test_bench.cpp.o -MF CMakeFiles/test_bench.dir/src/test_bench.cpp.o.d -o CMakeFiles/test_bench.dir/src/test_bench.cpp.o -c /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/test/src/test_bench.cpp

test/CMakeFiles/test_bench.dir/src/test_bench.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_bench.dir/src/test_bench.cpp.i"
	cd /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/test/src/test_bench.cpp > CMakeFiles/test_bench.dir/src/test_bench.cpp.i

test/CMakeFiles/test_bench.dir/src/test_bench.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_bench.dir/src/test_bench.cpp.s"
	cd /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/test/src/test_bench.cpp -o CMakeFiles/test_bench.dir/src/test_bench.cpp.s

# Object files for target test_bench
test_bench_OBJECTS = \
"CMakeFiles/test_bench.dir/src/test_bench.cpp.o"

# External object files for target test_bench
test_bench_EXTERNAL_OBJECTS =

test/libtest_bench.so: test/CMakeFiles/test_bench.dir/src/test_bench.cpp.o
test/libtest_bench.so: test/CMakeFiles/test_bench.dir/build.make
test/libtest_bench.so: sorting/libsorting_library.so
test/libtest_bench.so: test/CMakeFiles/test_bench.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libtest_bench.so"
	cd /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_bench.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_bench.dir/build: test/libtest_bench.so
.PHONY : test/CMakeFiles/test_bench.dir/build

test/CMakeFiles/test_bench.dir/clean:
	cd /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/build/test && $(CMAKE_COMMAND) -P CMakeFiles/test_bench.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_bench.dir/clean

test/CMakeFiles/test_bench.dir/depend:
	cd /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/test /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/build /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/build/test /home/usuario/ULL/Segundo-Ingenieria-Informatica/CyA/p10/time/build/test/CMakeFiles/test_bench.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/test_bench.dir/depend
