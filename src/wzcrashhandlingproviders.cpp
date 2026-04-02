/*
	This file is part of Warzone 2100.
	Copyright (C) 2021  Warzone 2100 Project

	Warzone 2100 is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	Warzone 2100 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Warzone 2100; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <nlohmann/json.hpp> // Must come before WZ includes

#include "wzcrashhandlingproviders.h"

#include "lib/framework/wzglobal.h" // required for config.h
#include "lib/framework/frame.h"
#include "lib/framework/wzapp.h"
#include "lib/framework/wzstring.h"
#include "lib/framework/physfs_ext.h"
#include "lib/framework/string_ext.h"

#include "version.h"
#include "urlhelpers.h"
#include "activity.h"
#include "modding.h"

#include <chrono>
#include <thread>

/* Crash-handling providers */

const size_t tagKeyMaxLength = 32;
const size_t tagValueMaxLength = 200;

bool initCrashHandlingProvider(const std::string& platformPrefDir, const std::string& defaultLogFilePath, bool debugCrashHandler)
{
#if !defined(WZ_CRASHHANDLING_PROVIDER)
	return false;
#else
	#error No available init for crash handling provider
	return false;
#endif
}

bool shutdownCrashHandlingProvider()
{
#if !defined(WZ_CRASHHANDLING_PROVIDER)
	return false;
#else
	// No available shutdown for crash handling provider
	return false;
#endif
}

bool crashHandlingProviderSetTag(const std::string& key, const std::string& value)
{
	ASSERT_OR_RETURN(false, key.size() <= tagKeyMaxLength, "Maximum key length exceeded");
	ASSERT_OR_RETURN(false, value.size() <= tagValueMaxLength, "Maximum value length exceeded");
#if !defined(WZ_CRASHHANDLING_PROVIDER)
	return false;
#else
	// No available setTag for crash handling provider
	return false;
#endif
}

bool crashHandlingProviderSetContext(const std::string& key, const nlohmann::json& contextDictionary)
{
#if !defined(WZ_CRASHHANDLING_PROVIDER)
	return false;
#else
	// No available setTag for crash handling provider
	return false;
#endif
}

bool crashHandlingProviderCaptureException(const char* type, const char* value, const std::string& description, bool captureStackTrace, bool handled, const nlohmann::json *additionalData)
{
#if !defined(WZ_CRASHHANDLING_PROVIDER)
	return false;
#else
	// Not available for crash handling provider
	return false;
#endif
}

bool useCrashHandlingProvider(int argc, const char * const *argv, bool& out_debugCrashHandler)
{
#if !defined(WZ_CRASHHANDLING_PROVIDER)
	return false; // use native crash-handling exception handler
#else
	// if compiled with a crash-handling provider, search for "--wz-crash-rpt"
	bool useProvider = true;
	if (argv)
	{
		for (int i = 0; i < argc; ++i)
		{
			if (argv[i] && !strcasecmp(argv[i], "--wz-crash-rpt"))
			{
				useProvider = false;
			}
#if defined(DEBUG)
			else if (argv[i] && !strcasecmp(argv[i], "--wz-debug-crash-handler"))
			{
				out_debugCrashHandler = true;
			}
#endif
		}
	}
	return useProvider;
#endif
}

bool crashHandlingProviderTestCrash()
{
#if !defined(WZ_CRASHHANDLING_PROVIDER)
	return false; // caller should handle its own way
#else
	// No available method for this crash handling provider?
	return false;
#endif
}
