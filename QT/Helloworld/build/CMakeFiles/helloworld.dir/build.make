# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /home/xyb/cmake-3.16.0-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/xyb/cmake-3.16.0-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build

# Include any dependencies generated for this target.
include CMakeFiles/helloworld.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/helloworld.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/helloworld.dir/flags.make

../Helloworld_zh_CN.ts: ../
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating ../Helloworld_zh_CN.ts"
	/home/xyb/Qt5.14.2/5.14.2/gcc_64/bin/lupdate @/home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build/CMakeFiles/Helloworld_zh_CN.ts_lst_file -ts /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/Helloworld_zh_CN.ts

CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o: CMakeFiles/helloworld.dir/flags.make
CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o: helloworld_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o -c /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build/helloworld_autogen/mocs_compilation.cpp

CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build/helloworld_autogen/mocs_compilation.cpp > CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.i

CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build/helloworld_autogen/mocs_compilation.cpp -o CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.s

CMakeFiles/helloworld.dir/main.cpp.o: CMakeFiles/helloworld.dir/flags.make
CMakeFiles/helloworld.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/helloworld.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/helloworld.dir/main.cpp.o -c /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/main.cpp

CMakeFiles/helloworld.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/main.cpp > CMakeFiles/helloworld.dir/main.cpp.i

CMakeFiles/helloworld.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/main.cpp -o CMakeFiles/helloworld.dir/main.cpp.s

CMakeFiles/helloworld.dir/mainwindow.cpp.o: CMakeFiles/helloworld.dir/flags.make
CMakeFiles/helloworld.dir/mainwindow.cpp.o: ../mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/helloworld.dir/mainwindow.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/helloworld.dir/mainwindow.cpp.o -c /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/mainwindow.cpp

CMakeFiles/helloworld.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/mainwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/mainwindow.cpp > CMakeFiles/helloworld.dir/mainwindow.cpp.i

CMakeFiles/helloworld.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/mainwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/mainwindow.cpp -o CMakeFiles/helloworld.dir/mainwindow.cpp.s

# Object files for target helloworld
helloworld_OBJECTS = \
"CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/helloworld.dir/main.cpp.o" \
"CMakeFiles/helloworld.dir/mainwindow.cpp.o"

# External object files for target helloworld
helloworld_EXTERNAL_OBJECTS =

helloworld: CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o
helloworld: CMakeFiles/helloworld.dir/main.cpp.o
helloworld: CMakeFiles/helloworld.dir/mainwindow.cpp.o
helloworld: CMakeFiles/helloworld.dir/build.make
helloworld: /home/xyb/Qt5.14.2/5.14.2/gcc_64/lib/libQt5Widgets.so.5.14.2
helloworld: /home/xyb/Qt5.14.2/5.14.2/gcc_64/lib/libQt5Gui.so.5.14.2
helloworld: /home/xyb/Qt5.14.2/5.14.2/gcc_64/lib/libQt5Core.so.5.14.2
helloworld: CMakeFiles/helloworld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable helloworld"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/helloworld.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/helloworld.dir/build: helloworld

.PHONY : CMakeFiles/helloworld.dir/build

CMakeFiles/helloworld.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/helloworld.dir/cmake_clean.cmake
.PHONY : CMakeFiles/helloworld.dir/clean

CMakeFiles/helloworld.dir/depend: ../Helloworld_zh_CN.ts
	cd /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build /home/xyb/CPPOUT/CPP_dairly_demo/QT/Helloworld/build/CMakeFiles/helloworld.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/helloworld.dir/depend

