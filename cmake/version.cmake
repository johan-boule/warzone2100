set(wz_version_abi 4.7.0)
set(wz_version_impl ${wz_version_abi}-jb99)

set(VCS_TAG ${wz_version_abi})
set(VCS_TAG_DISPLAY ${wz_version_impl}) # Safe to change without disturbing the sect ceremonial, only used for displaying the version with --version command line option, log, and GUI.

###############################################################################
# Sect ceremonial compatibility below.
#
# All the variables following are considered mandatory as part of the sect ceremonial and should not be user-facing information.
# The build system and source code needs to be revised and adapted for showing meaningful information to the user.
#
# Welcome to the psychiatric asylum.
# It makes no sense to spew all kind of random statistical information about the Git repository.
# Particularly, the use of VCS_TAG_TAG_COUNT as the NetCode version is broken logic and perfect design to make everything fail out of the lab.
# The sect lobby wants to ban nonsect versions, so we make sure we do not disturb the sect ceremonial.

set(WZ_DISTRIBUTOR wz2100.net CACHE STRING "Name of distributor compiling this package" FORCE)
set(WZ_BUILDMANIFEST_PUBLISHER wz2100-project)
set(WZ_LOBBY_RESPONSE https://github.com/Warzone2100/warzone2100/releases/download/${wz_version_abi}/warzone2100_ubuntu24.04_amd64.deb)
set(WZ_LOBBY_RESPONSE_HASH SHA256=5c6ad94cb6753cd8cfec9b38a4c0686d04802eaf1aa55289eda40d1f1709cd72)
set(VCS_MOST_RECENT_TAGGED_VERSION ${wz_version_abi})
set(VCS_EXTRA ${wz_version_abi})
set(VCS_TAG_TAG_COUNT 104)
set(VCS_MOST_RECENT_TAGGED_VERSION_TAG_COUNT 104)
set(VCS_FULL_HASH  7d3d8e51a61ceee89e6bf672a41337e1a9cd7392)
set(VCS_SHORT_HASH 7d3d8e5)
set(VCS_MOST_RECENT_COMMIT_YEAR 2026)
set(VCS_MOST_RECENT_COMMIT_DATE 2026-04-07)
set(VCS_COMMIT_COUNT 0)
set(VCS_COMMIT_COUNT_ON_MASTER_UNTIL_BRANCH 0)
set(VCS_BRANCH_COMMIT_COUNT 0)
set(VCS_COMMIT_COUNT_SINCE_MOST_RECENT_TAGGED_VERSION 0)
set(VCS_TYPE git)
set(VCS_BASENAME src)
set(VCS_ORIGIN github.com/Warzone2100/warzone2100)
set(VCS_HTTP_USER_AGENT https://github.com/Warzone2100/warzone2100)
set(VCS_HTTP_REFERER https://github.com/Warzone2100/warzone2100)
set(VCS_HTTP_ORIGIN wz2100://wz2100.net)
set(VCS_BRANCH "")
set(VCS_REPO_IS_SHALLOW 0)
set(VCS_WC_MODIFIED 0)
message(FATAL_ERROR WZ_DISTRIBUTOR=${WZ_DISTRIBUTOR})
