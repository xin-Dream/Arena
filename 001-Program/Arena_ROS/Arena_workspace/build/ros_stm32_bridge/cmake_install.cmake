# Install script for directory: /home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/src/ros_stm32_bridge

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_stm32_bridge/msg" TYPE FILE FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/src/ros_stm32_bridge/msg/stm32_motor.msg")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_stm32_bridge/cmake" TYPE FILE FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/build/ros_stm32_bridge/catkin_generated/installspace/ros_stm32_bridge-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/devel/include/ros_stm32_bridge")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/devel/share/roseus/ros/ros_stm32_bridge")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/devel/share/common-lisp/ros/ros_stm32_bridge")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/devel/share/gennodejs/ros/ros_stm32_bridge")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/devel/lib/python2.7/dist-packages/ros_stm32_bridge")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/devel/lib/python2.7/dist-packages/ros_stm32_bridge")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/build/ros_stm32_bridge/catkin_generated/installspace/ros_stm32_bridge.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_stm32_bridge/cmake" TYPE FILE FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/build/ros_stm32_bridge/catkin_generated/installspace/ros_stm32_bridge-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_stm32_bridge/cmake" TYPE FILE FILES
    "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/build/ros_stm32_bridge/catkin_generated/installspace/ros_stm32_bridgeConfig.cmake"
    "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/build/ros_stm32_bridge/catkin_generated/installspace/ros_stm32_bridgeConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_stm32_bridge" TYPE FILE FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/src/ros_stm32_bridge/package.xml")
endif()

