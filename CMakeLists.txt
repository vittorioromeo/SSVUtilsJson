cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type.")
project(SSVUtilsJson)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -W -pedantic" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-fno-omit-frame-pointer -g3 -gdwarf-2 -O0" CACHE STRING "" FORCE)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/;${CMAKE_MODULE_PATH}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extlibs/SSVJsonCpp/cmake/modules/;${CMAKE_MODULE_PATH}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extlibs/SSVUtils/cmake/modules/;${CMAKE_MODULE_PATH}")

find_package(SSVJsonCpp REQUIRED)
find_package(SSVUtils REQUIRED)

set(INC_DIR "include")

file(GLOB SRC_LIST
	"${INC_DIR}/${PROJECT_NAME}/*.h"
	"${INC_DIR}/${PROJECT_NAME}/LinkedValue/*.h"
	"${INC_DIR}/${PROJECT_NAME}/Utils/*.h"
	"${INC_DIR}/${PROJECT_NAME}/Utils/Internal/*.h"
)

add_library(HEADER_ONLY_TARGET STATIC ${SRC_LIST})
set_target_properties(HEADER_ONLY_TARGET PROPERTIES LINKER_LANGUAGE CXX)

install(DIRECTORY ${INC_DIR} DESTINATION .)
