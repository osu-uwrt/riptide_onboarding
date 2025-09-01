cmake_minimum_required(VERSION 3.8)
project(riptide_turtle)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_srvs REQUIRED)

#install python programs
file(GLOB python_programs RELATIVE ${PROJECT_SOURCE_DIR} src/py/*.py)
install(PROGRAMS ${python_programs}
  DESTINATION lib/${PROJECT_NAME})

# Build c++ executables
add_executable(turtle_node src/cpp/turtle_node.cpp)
add_executable(turtle_kill_switch src/cpp/turtle_kill_switch.cpp)

set (cpp_deps
  rclcpp
  geometry_msgs
  std_msgs
  std_srvs
)

ament_target_dependencies(turtle_node ${cpp_deps})
ament_target_dependencies(turtle_kill_switch ${cpp_deps})

#Install c++ executables
install(TARGETS turtle_node turtle_kill_switch
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
