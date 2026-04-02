cmake_minimum_required(VERSION 3.16...3.31)

# Automatically generate a Flatpak manifest from the template file
#
# Required input defines:
# - TEMPLATE_FILE: the full filename + path for the input info.retropaganda.warzone2100.yaml.in template file
# - OUTPUT_FILE: the full filename + path for the output info.retropaganda..warzone2100.yaml file
# - PROJECT_ROOT: the path the project root (${PROJECT_SOURCE_DIR})
#
# And also, these input defines:
# - WZ_OUTPUT_NAME_SUFFIX: The desired suffix to apply to the app id in the manifest (should match the main build)
#
# If cross-compiling, specify:
# - WZ_CROSS_COMPILE_TARGET_ARCH: <aarch64, etc>
#

if(NOT DEFINED TEMPLATE_FILE OR "${TEMPLATE_FILE}" STREQUAL "")
	message( FATAL_ERROR "Missing required input define: TEMPLATE_FILE" )
endif()
if(NOT DEFINED OUTPUT_FILE OR "${OUTPUT_FILE}" STREQUAL "")
	message( FATAL_ERROR "Missing required input define: OUTPUT_FILE" )
endif()
if(NOT DEFINED PROJECT_ROOT OR "${PROJECT_ROOT}" STREQUAL "")
	message( FATAL_ERROR "Missing required input define: PROJECT_ROOT" )
endif()

if(NOT DEFINED WZ_OUTPUT_NAME_SUFFIX)
	message( FATAL_ERROR "Missing expected input define: WZ_OUTPUT_NAME_SUFFIX" )
endif()
if (DEFINED WZ_CROSS_COMPILE_TARGET_ARCH)
	message( FATAL_ERROR "WZ_CROSS_COMPILE_TARGET_ARCH detected - not currently supported by this script" )
endif()

##################################
# WZ module source (the current dir into which the Github repo is checked-out)
# Assumes the generated config will be placed in .ci/flatpak/

set(WZ_MAIN_MODULE_SOURCE "\n\
      - type: dir\n\
        path: ../../\n\
")

##################################
# Handle prebuilt-texture-packages

include("${PROJECT_ROOT}/data/WZPrebuiltPackages.cmake")

##################################
# Debug output

execute_process(COMMAND ${CMAKE_COMMAND} -E echo "++TEMPLATE_FILE: ${TEMPLATE_FILE}")
execute_process(COMMAND ${CMAKE_COMMAND} -E echo "++OUTPUT_FILE: ${OUTPUT_FILE}")

execute_process(COMMAND ${CMAKE_COMMAND} -E echo "++WZ_OUTPUT_NAME_SUFFIX: ${WZ_OUTPUT_NAME_SUFFIX}")

##################################
# Output configured file based on the template

if(NOT EXISTS "${TEMPLATE_FILE}")
	message( FATAL_ERROR "Input TEMPLATE_FILE does not exist: \"${TEMPLATE_FILE}\"" )
endif()
configure_file("${TEMPLATE_FILE}" "${OUTPUT_FILE}" @ONLY)

