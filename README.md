# ros2-tutorials

A compilation of basic ros2 concepts and templates

## Tutorial 01 - Creating a ROS2 workspace

The first step is creating a ROS2 workspace.
The general file structure of a ROS2 workspace is as follows, illustrated by the structure of this tutorial workspace:

```text
ros2_tutorials
│   README.md
│   build # Created after building with colcon build
│   install # Created after building with colcon build
│   log # Created after building with colcon build
└───src # Includes all packages that need to be built
│   └───package_1 # ROS2 package which includes all scripts
│       │   folders
│       │   files
│       │   CMakeLists.txt # Commands to build the package
│       │   package.xml # Contains dependencies and metadata
│       │   ...
│   └───package2
│       │   folders
│       │   files
│       │   CMakeLists.txt # Commands to build the package
│       │   package.xml # Contains dependencies and metadata
│       │   ...
│   └───...
```

To create a workspace, you need to create the following folders:

```text
mkdir -p ~/<workspace_name>/src
cd ~/<workspace_name>/src
```

## Tutorial 02 - Creating a ROS2 Package

After you created a workspace, you can create as many packages as necessary in the src folder.

The following command creates a package that supports C++ scripts:

```text
ros2 pkg create --build-type ament_cmake <package_name>
```

For Python, use the following command:

```text
ros2 pkg create --build-type ament_python <package_name>
```

If you want to use both C++ and Python, clone the package_template package that can be found in the src folder.

In this tutorial, we will use the package_template package.
The structure of the package is as follows:

```text
package
└───include # Header files for C++ scripts
└───package_template # Libraries and modules for Python
│       │   __init__.py
└───scripts # Python scripts
└───src # Source code file for C++ scripts
│   CMakeLists.txt # Commands to build the package
│   package.xml # Contains dependencies and metadata
```

The files **CMakeLists.txt** and **package.xml** contain information on how to build the package and what dependencies are required.

The **CMakeLists.txt** file includes the following code:

```text
cmake_minimum_required(VERSION 3.5)
project(package_template)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)

# Include Cpp "include" directory
include_directories(include)

# Create Cpp executable
add_executable(cpp_executable src/cpp_node.cpp)
ament_target_dependencies(cpp_executable rclcpp)

# Install include directory
install(
  DIRECTORY include/
  DESTINATION include
)

# Install Cpp executables
install(TARGETS
  cpp_executable
  <cpp_executable_name1>
  <cpp_executable_name2>
  DESTINATION lib/${PROJECT_NAME}
)

# Install directories
install(DIRECTORY
  <folder_name1>
  <folder_name2>
  DESTINATION share/${PROJECT_NAME}
)

# Install Python modules
ament_python_install_package(${PROJECT_NAME})

# Install Python executables
install(PROGRAMS
  scripts/py_node.py
  scripts/<py_node_name1>.py
  scripts/<py_node_name2>.py
  DESTINATION lib/${PROJECT_NAME}
)
ament_package()
```

For extending a package, you may add folders, scripts, and dependencies to the already existing package.
For each folder, add its name to the directories of the directory install command.
For each C++ executable, add its name to the targets of the cpp executable install command
For each Python script, add its name to the programs of the python executable install command.

For C++ and Python nodes, each script requires that the dependencies are added to the CMakeLists.txt and package.xml.
For each required package, add the following line to the CMakeLists.txt:

```text
find_package(<package_name1> REQUIRED)
find_package(<package_name2> REQUIRED)
```

For C++ executables, the dependencies have to be added for each executable as follows:

```text
add_executable(<cpp_executable_name> src/<cpp_executable_name>.cpp)
ament_target_dependencies(<cpp_executable_name> <package_name1> <package_name2>)
```

In addition, we need to modify the **package.xml** file.
It includes the following code:

```text
<?xml version="1.0"?>
<?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypens="http://www.w3.org/2001/XMLSchema"?>
<package format="3">
  <name>package_template</name>
  <version>1.0.0</version>
  <description>Basic ROS2 package for C++ and Python</description>
  <maintainer email="harun.teper@tu-dortmund.de">Harun Teper</maintainer>
  <license>TODO</license>

  <buildtool_depend>ament_cmake</buildtool_depend>
  <buildtool_depend>ament_cmake_python</buildtool_depend>

  <depend>rclcpp</depend>
  <depend>rclpy</depend>

  <test_depend>ament_lint_auto</test_depend>
  <test_depend>ament_lint_common</test_depend>
  
  <export>
    <build_type>ament_cmake</build_type>
  </export>
</package>
```

For the package_template, we include both C++ and Python with the following lines:

```text
  <buildtool_depend>ament_cmake</buildtool_depend>
  <buildtool_depend>ament_cmake_python</buildtool_depend>
```

For each dependency, the **package.xml** file needs to include the following lines:

```text
  <depend><package_name1></depend>
  <depend><package_name2></depend>
```

For more information about the package.xml structure, visit https://ros.org/reps/rep-0149.html.