cmake_minimum_required (VERSION 3.10)

project(ac)

set(TARGET_NAME "ac")

# AC_BUILD_TYPE can be set to one of the three following values
#     STATIC
#     SHARED
#     MODULE
add_library (${TARGET_NAME} ${AC_BUILD_TYPE}
	ac.cxx 
	ac.h
	ac_fast.cxx
	ac_fast.hpp
	ac_slow.cxx
	ac_slow.hpp
	ac_util.hpp
)

if (AC_BUILD_TYPE STREQUAL "SHARED" OR 
	AC_BUILD_TYPE STREQUAL "MODULE")
	target_compile_definitions(${TARGET_NAME} PUBLIC "AC_BUILD_TYPE_SHARED")
	target_compile_definitions(${TARGET_NAME} PRIVATE "AC_BUILDING_LIB")
endif()

target_compile_features(${TARGET_NAME} PRIVATE "cxx_std_11")
set_target_properties(${TARGET_NAME} PROPERTIES PUBLIC_HEADER ac.h)

install(TARGETS ${TARGET_NAME} PUBLIC_HEADER)
