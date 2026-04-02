#########################
# Appstream

add_subdirectory(appstream)

#########################
# Generator-specific components

install(FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/copyright"
  DESTINATION "${CMAKE_INSTALL_DOCDIR}${WZ_OUTPUT_NAME_SUFFIX}"
  COMPONENT DebianInfo
)

#########################

if(NOT DEFINED WZ_DIST_LICENSE OR NOT EXISTS "${WZ_DIST_LICENSE}")
	message(FATAL_ERROR "This file should be included in the project's root CMakeLists.txt, after WZ_DIST_LICENSE is defined.")
endif()

set(CPACK_PACKAGE_NAME			"Warzone 2100")
set(CPACK_PACKAGE_VENDOR		"${WZ_DISTRIBUTOR}")
set(CPACK_RESOURCE_FILE_LICENSE "${WZ_DIST_LICENSE}")
set(CPACK_PACKAGE_CHECKSUM		SHA256)
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Description.txt")
set(CPACK_PACKAGE_HOMEPAGE_URL  https://warzone2100.retropaganda.info)

#########################
# Default components that are added to package

set(CPACK_COMPONENTS_ALL Core Data Docs Info Languages)
if(UNIX AND NOT APPLE)
	list(APPEND CPACK_COMPONENTS_ALL Manpages)
endif()
set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)

#########################
# Default component info

set(CPACK_COMPONENT_CORE_DISPLAY_NAME "Application")
set(CPACK_COMPONENT_CORE_REQUIRED ON)
set(CPACK_COMPONENT_CORE_DESCRIPTION "Application")
set(CPACK_COMPONENT_CORE_GROUP "CoreGroup")
set(CPACK_COMPONENT_CORE_DEPENDS Data Docs Info)

set(CPACK_COMPONENT_DEBUGSYMBOLS_DISPLAY_NAME "Debug Symbols")
set(CPACK_COMPONENT_DEBUGSYMBOLS_REQUIRED ON)
set(CPACK_COMPONENT_DEBUGSYMBOLS_DESCRIPTION "Debug Symbols")
set(CPACK_COMPONENT_DEBUGSYMBOLS_GROUP "CoreGroup")
set(CPACK_COMPONENT_DEBUGSYMBOLS_HIDDEN ON)

set(CPACK_COMPONENT_ADDITIONALDEBUGSYMBOLS_DISPLAY_NAME "Additional Debug Symbols")
set(CPACK_COMPONENT_ADDITIONALDEBUGSYMBOLS_REQUIRED ON)
set(CPACK_COMPONENT_ADDITIONALDEBUGSYMBOLS_DESCRIPTION "Additional Debug Symbols")
set(CPACK_COMPONENT_ADDITIONALDEBUGSYMBOLS_GROUP "CoreGroup")
set(CPACK_COMPONENT_ADDITIONALDEBUGSYMBOLS_HIDDEN ON)

set(CPACK_COMPONENT_DATA_DISPLAY_NAME "Data Files")
set(CPACK_COMPONENT_DATA_REQUIRED ON)
set(CPACK_COMPONENT_DATA_DESCRIPTION "Data Files")
set(CPACK_COMPONENT_DATA_GROUP "CoreGroup")

set(CPACK_COMPONENT_DOCS_DISPLAY_NAME "Documentation")
set(CPACK_COMPONENT_DOCS_REQUIRED ON)
set(CPACK_COMPONENT_DOCS_DESCRIPTION "Documentation")
set(CPACK_COMPONENT_DOCS_GROUP "CoreGroup")

set(CPACK_COMPONENT_INFO_DISPLAY_NAME "Info")
set(CPACK_COMPONENT_INFO_REQUIRED ON)
set(CPACK_COMPONENT_INFO_DESCRIPTION "Info Files")
set(CPACK_COMPONENT_INFO_GROUP "CoreGroup")

set(CPACK_COMPONENT_PORTABLECONFIG_DISPLAY_NAME "Portable Configuration")
set(CPACK_COMPONENT_PORTABLECONFIG_DESCRIPTION "Portable Configuration")
set(CPACK_COMPONENT_PORTABLECONFIG_GROUP "CoreGroup")
set(CPACK_COMPONENT_PORTABLECONFIG_HIDDEN ON)

set(CPACK_COMPONENT_MANPAGES_GROUP "CoreGroup")

set(CPACK_COMPONENT_GROUP_COREGROUP_DISPLAY_NAME "Core files")
set(CPACK_COMPONENT_GROUP_COREGROUP_REQUIRED ON)
set(CPACK_COMPONENT_GROUP_COREGROUP_DESCRIPTION "The core files required to run Warzone 2100.")

#########################

if(NOT DEFINED CPACK_MODULE_PATH)
	set(CPACK_MODULE_PATH)
endif()

if(NOT DEFINED CPACK_PACKAGE_FILE_NAME)
	# Default of "warzone2100"
	set(CPACK_PACKAGE_FILE_NAME "warzone2100")
endif()

if(NOT DEFINED CPACK_SOURCE_PACKAGE_FILE_NAME)
	# Default of "warzone2100"
	set(CPACK_SOURCE_PACKAGE_FILE_NAME "warzone2100")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
	# macOS builds

	# Only install the "Core" component (the application), as the macOS app bundle contains all of the data & supporting files & languages
	set(CPACK_COMPONENTS_ALL Core)
	unset(CPACK_COMPONENT_CORE_DEPENDS)
	set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)

	# Default package generators on macOS
	set(CPACK_GENERATOR "ZIP")

	# Support Archive generator
	set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY FALSE)

	# Support DragNDrop generator
	set(CPACK_DMG_BACKGROUND_IMAGE "${CMAKE_CURRENT_SOURCE_DIR}/dmg/WZDMGBackground.tiff")
	set(CPACK_DMG_DS_STORE_SETUP_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/dmg/WZDMGSetup.scpt")
	set(CPACK_DMG_VOLUME_NAME "Warzone 2100")

elseif(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
	# Emscripten builds

	# Only install the "Core" component, as it installs all of the data & supporting files & languages
	set(CPACK_COMPONENTS_ALL Core)
	unset(CPACK_COMPONENT_CORE_DEPENDS)
	set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)

	# Default package generator for Emscripten (archive)
	set(CPACK_GENERATOR "ZIP")
	set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY FALSE)

endif()

#####################
# Archive settings

# Always use component install for archives
# See: https://stackoverflow.com/a/55601955
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)

#####################
# RPM Settings

set(CPACK_RPM_PACKAGE_SUMMARY   "Innovative 3D real-time strategy")
set(CPACK_RPM_PACKAGE_GROUP     "Amusements/Games")
set(CPACK_RPM_PACKAGE_LICENSE   "GPLv2+ and CC-BY-SA")
set(CPACK_RPM_PACKAGE_URL       "https://warzone2100.retropaganda.info")

#####################
# DEB Settings

set(CPACK_DEBIAN_PACKAGE_NAME "warzone2100")
set(CPACK_DEBIAN_PACKAGE_SECTION  "games")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://warzone2100.retropaganda.info")

set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Innovative 3D real-time strategy\n In Warzone 2100 you command the forces of “The Project” in a battle to rebuild the world after mankind has been nearly destroyed by nuclear missiles.\n .\n The game offers campaign, tutorial, multi-player and single-player skirmish modes. An extensive tech tree with over 400 different technologies, combined with the unit design system, allows for a wide variety of possible units and tactics. Play versus AI bots in local skirmishes (or as added teammates / enemies in multiplayer), and practice your skills with endless replayability.\n .\n Warzone 2100 was originally created by Pumpkin Studios and published by Eidos Interactive, and was open-sourced in 2004. It has been developed, maintained, and improved by the community ever since, under the banner of the “Warzone 2100 Project”.\n .\n This package does not include the campaign video sequences - please see the Warzone 2100 website for details on how to download and install them.")

# Add dynamically-loaded dependencies for SDL3 (since some DEB packages have it built from source)

set(wz_deb_sdl3_depends "libdecor-0-0, libdrm2, libgbm1, libwayland-client0, libwayland-cursor0, libwayland-egl1, libx11-6, libxcursor1, libxext6, libxfixes3, libxi6, libxkbcommon0, libxrandr2, libxss1, liburing2, xdg-utils")
set(wz_deb_sdl3_recommends "libdbus-1-3, libegl1, libgl1 | libopengl0, libgles2, libvulkan1")

set(CPACK_DEBIAN_PACKAGE_DEPENDS "${wz_deb_sdl3_depends}")
set(CPACK_DEBIAN_CORE_PACKAGE_DEPENDS "${wz_deb_sdl3_depends}")

set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "${wz_deb_sdl3_recommends}")

######################
# Configure Installer Version-info at Package Build-Time

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CPackConfigVersion.cmake.in
			   ${CMAKE_BINARY_DIR}/CPackConfigVersion.cmake
			   @ONLY)
set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_BINARY_DIR}/CPackConfigVersion.cmake)

include(CPack)
