#pragma once

#if defined( _WIN32 ) || defined( __WIN32__ )
	#define FWSC_SYSTEM_WINDOWS
	#define WIN32_LEAN_AND_MEAN

	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#endif

#if defined( FWSC_SYSTEM_WINDOWS ) && !defined( FWSC_STATIC )
	#ifdef FWSC_EXPORTS
		#define FWSC_API __declspec( dllexport )
	#else
		#define FWSC_API __declspec( dllimport )
	#endif
#else
	#define FWSC_API
#endif

#ifdef _MSC_VER
	#pragma warning(disable : 4251) // Suppress a warning which is meaningless for us
	#pragma warning(disable : 4503) // Suppress warnings about truncated names. Enable again if linker errors occur.
#endif

/** FlexWorld component system.
 */
namespace cs {
}
