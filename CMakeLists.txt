cmake_minimum_required(VERSION 2.8)
project(SSVUtilsJson)

set(SSVUTILSJSON_BUILD_SHARED_LIB FALSE CACHE BOOL "Build shared libraries.")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type." FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" CACHE STRING "" FORCE)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extlibs/SSVUtils/cmake/Modules/;${CMAKE_MODULE_PATH}")

find_package(JsonCpp REQUIRED)
if(JSONCPP_FOUND)
	include_directories(${JSONCPP_INCLUDE_DIR})
	message("\nJsonCpp found and included\n")
else()
	set(JSONCPP_ROOT "" CACHE PATH "JsonCpp top-level directory")
	message("\n-> JsonCpp directory not found. Set SSVUTILS_ROOT to SSVUtils' top-level path (containing both \"include\" and \"lib\" directories).")
endif()

find_package(SSVUtils REQUIRED)
if(SSVUTILS_FOUND)
	include_directories(${SSVUTILS_INCLUDE_DIR})
	message("\nSSVUtils found and included\n")
else()
	set(SSVUTILS_ROOT "" CACHE PATH "SSVUtils top-level directory")
	message("\n-> SSVUtils directory not found. Set SSVUTILS_ROOT to SSVUtils' top-level path (containing both \"include\" and \"lib\" directories).")
endif()

if(SSVUTILSJSON_BUILD_SHARED_LIB)
	set(LIB_TYPE SHARED)
else()
	set(LIB_TYPE STATIC)
endif()

set(SRC_DIR "src")
set(INC_DIR "include")

set(
	SOURCES
	${INC_DIR}/${PROJECT_NAME}/Utils/UtilsJson.h
	${SRC_DIR}/${PROJECT_NAME}/Utils/UtilsJson.cpp
)

include_directories(${INC_DIR})

add_library(${PROJECT_NAME} ${LIB_TYPE} ${SOURCES})
target_link_libraries(SSVUtilsJson ${JSONCPP_LIBRARY})
target_link_libraries(SSVUtilsJson ${SSVUTILS_LIBRARY})

if(SSVUTILSJSON_BUILD_SHARED_LIB)
	set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)
else()
	set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -s-d)
	set_target_properties(${PROJECT_NAME} PROPERTIES RELEASE_POSTFIX -s)
endif()

if(WIN32)
	install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
else()
	install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION lib
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
endif()

install(DIRECTORY ${INC_DIR}
	DESTINATION .)
