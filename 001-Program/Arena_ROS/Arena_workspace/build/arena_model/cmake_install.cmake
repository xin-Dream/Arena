# Install script for directory: /home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/src/arena_model

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/build/arena_model/catkin_generated/installspace/arena_model.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/arena_model/cmake" TYPE FILE FILES
    "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/build/arena_model/catkin_generated/installspace/arena_modelConfig.cmake"
    "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/build/arena_model/catkin_generated/installspace/arena_modelConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/arena_model" TYPE FILE FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/src/arena_model/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/arena_model/config" TYPE DIRECTORY FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/src/arena_model/config/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/arena_model/launch" TYPE DIRECTORY FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/src/arena_model/launch/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/arena_model/meshes" TYPE DIRECTORY FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/src/arena_model/meshes/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/arena_model/urdf" TYPE DIRECTORY FILES "/home/dream/001-data/001-Arena/Arena/001-Program/Arena_ROS/Arena_workspace/src/arena_model/urdf/")
endif()

