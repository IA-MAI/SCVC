cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES CXX C)

# Set the C++ and C standards
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 14)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find OpenMP libraries
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# Windows specific flags
if (MSVC)
    add_compile_definitions(_ENABLE_EXTENDED_ALIGNED_STORAGE)
    add_compile_definitions(/bigobj)
endif()

# Define headers and sources
set(${PROJECT_NAME}_HEADERS
    src/algo/point_cloud_registration.h
    src/algo/registration/registration_helpers.hpp
    src/algo/registration/registration_SCVC.h
    src/algo/registration/registration_stdafx.h
    src/algo/ICP_Princeton/KDtree.h
    src/algo/ICP_Princeton/ICP.h
    src/algo/ICP_Princeton/TriMesh.h
    src/algo/ICP_Princeton/TriMesh_algo.h
)

set(${PROJECT_NAME}_SOURCES
    src/algo/point_cloud_registration.cpp
    src/algo/registration/registration_helpers.cpp
    src/algo/registration/registration_SCVC.cpp
    
    src/algo/ICP_Princeton/KDtree.cpp
    src/algo/ICP_Princeton/ICP.cpp
    src/algo/ICP_Princeton/TriMesh_bounding.cpp
    src/algo/ICP_Princeton/TriMesh_connectivity.cpp
    src/algo/ICP_Princeton/TriMesh_curvature.cpp
    src/algo/ICP_Princeton/TriMesh_grid.cpp
    src/algo/ICP_Princeton/TriMesh_io.cpp
    src/algo/ICP_Princeton/TriMesh_normal.cpp
    src/algo/ICP_Princeton/TriMesh_pointareas.cpp
    src/algo/ICP_Princeton/TriMesh_stats.cpp
    src/algo/ICP_Princeton/TriMesh_tstrips.cpp
    src/algo/ICP_Princeton/remove.cpp
    src/algo/ICP_Princeton/reorder_verts.cpp
    src/main.cpp
)

# Set the root directory for easier include paths
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
include_directories(${PROJECT_ROOT_DIR})

# Include each algorithm directory
include_directories(${PROJECT_ROOT_DIR}/src/algo)
include_directories(${PROJECT_ROOT_DIR}/src/algo/ICP_Princeton)
include_directories(${PROJECT_ROOT_DIR}/src/algo/registration)

# Third-party configurations
set(3DMODEL_THIRD_PARTY ${PROJECT_ROOT_DIR}/scvcLibs)
add_subdirectory(${3DMODEL_THIRD_PARTY})
mark_as_advanced(FORCE BUILD_SHARED_LIBS)
mark_as_advanced(FORCE BUILD_TESTING)

# Add an executable
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${3DMODEL_THIRD_PARTY})

# Setup Eigen include directory
set(EIGEN_SOURCE_DIR ${3DMODEL_THIRD_PARTY}/eigen-3.4.0)
target_include_directories(${PROJECT_NAME} PRIVATE ${EIGEN_SOURCE_DIR})
