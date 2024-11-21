cmake_minimum_required(VERSION 3.22)

project(cs2kz)

include("shared.cmake")

set(KZ_SRC "./src" CACHE STRING "KZ source directory")

include_directories(
	${KZ_SRC}
	${KZ_SRC}/protobuf
	./vendor/funchook/include
)

if(WIN32)
	file(GLOB KZ_LIBS
		"./vendor/funchook/lib/*.lib"
	)
else()
	file(GLOB KZ_LIBS
		"./vendor/funchook/lib/*.a"
	)
endif()

file(GLOB_RECURSE PROTOBUF_SOURCES "${KZ_SRC}/protobuf/*.pb.cc" "${KZ_SRC}/protobuf/*.pb.h")

file(GLOB_RECURSE KZ_SOURCES 
				"${SDK_ROOT}/entity2/entityidentity.cpp"
				"${SDK_ROOT}/entity2/entitysystem.cpp"
				"${SDK_ROOT}/entity2/entitykeyvalues.cpp"
				"${SDK_ROOT}/tier1/generichash.cpp"
				"${SDK_ROOT}/tier1/keyvalues3.cpp"
				"${KZ_SRC}/*.cpp"
				"${KZ_SRC}/*.h")

if(WIN32)
	list(FILTER KZ_SOURCES EXCLUDE REGEX "plat_linux.cpp")
else()
	list(FILTER KZ_SOURCES EXCLUDE REGEX "plat_win.cpp")
endif()

set(KZExcludedDir "${KZ_SRC}/kz/mode" "${KZ_SRC}/kz/style")
foreach(Dir ${KZExcludedDir})
	list(FILTER KZ_SOURCES EXCLUDE REGEX ${Dir})
endforeach()

list(APPEND KZ_SOURCES 
				"${KZ_SRC}/kz/mode/kz_mode_manager.cpp"
				"${KZ_SRC}/kz/mode/kz_mode_vnl.cpp"
				"${KZ_SRC}/kz/style/kz_style_manager.cpp"
)

add_library(${PROJECT_NAME} SHARED ${SDK_CONVAR} ${SDK_MEMOVERRIDE} ${PROTOBUF_SOURCES} ${KZ_SOURCES})

if(WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE psapi.lib)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${KZ_LIBS})

#target_precompile_headers(${PROJECT_NAME} PRIVATE ${PCH})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

set(OUT_DIR "" CACHE PATH "KZ binary directory for post-build file copy")

if (NOT "${OUT_DIR}" STREQUAL "")
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
			$<TARGET_FILE:${PROJECT_NAME}>
			${OUT_DIR}
	)
endif()


set(MODE_CKZ "${PROJECT_NAME}-mode-ckz")
file(GLOB_RECURSE MODE_CKZ_SOURCES 
				"${SDK_ROOT}/entity2/entityidentity.cpp"
				"${SDK_ROOT}/entity2/entitysystem.cpp"
				"${KZ_SRC}/utils/schema.cpp" "${KZ_SRC}/utils/schema.h"
				"${KZ_SRC}/utils/gameconfig.cpp" "${KZ_SRC}/utils/gameconfig.h"
				"${KZ_SRC}/kz/mode/kz_mode_ckz.cpp" "${KZ_SRC}/kz/mode/kz_mode_ckz.h"
)
if(WIN32)
	list(APPEND MODE_CKZ_SOURCES "${KZ_SRC}/utils/plat_win.cpp")
else()
	list(APPEND MODE_CKZ_SOURCES "${KZ_SRC}/utils/plat_linux.cpp")
endif()
add_library(${MODE_CKZ} SHARED ${SDK_CONVAR} ${SDK_MEMOVERRIDE} ${PROTOBUF_SOURCES} ${MODE_CKZ_SOURCES})


set(STYLE_AUTOBHOP "${PROJECT_NAME}-style-autobhop")
file(GLOB_RECURSE STYLE_AUTOBHOP_SOURCES 
				"${SDK_ROOT}/entity2/entityidentity.cpp"
				"${SDK_ROOT}/entity2/entitysystem.cpp"
				"${KZ_SRC}/utils/schema.cpp" "${KZ_SRC}/utils/schema.h"
				"${KZ_SRC}/utils/gameconfig.cpp" "${KZ_SRC}/utils/gameconfig.h"
				"${KZ_SRC}/kz/style/kz_style_autobhop.cpp" "${KZ_SRC}/kz/style/kz_style_autobhop.h"
)
if(WIN32)
	list(APPEND STYLE_AUTOBHOP_SOURCES "${KZ_SRC}/utils/plat_win.cpp")
else()
	list(APPEND STYLE_AUTOBHOP_SOURCES "${KZ_SRC}/utils/plat_linux.cpp")
endif()
add_library(${STYLE_AUTOBHOP} SHARED ${SDK_CONVAR} ${SDK_MEMOVERRIDE} ${PROTOBUF_SOURCES} ${STYLE_AUTOBHOP_SOURCES})
