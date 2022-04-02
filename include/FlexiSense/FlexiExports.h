
/*! FlexiSense
 *  FlexiExports.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXIEXPORTS_H
#define FLEXIEXPORTS_H

#ifdef FLEXISENSE_EXPORTS
    #ifdef LINUX
        #define FLX_EXPORT
    #elif WINDOWS
        #define FLX_EXPORT	__declspec(dllexport)
    #endif
#else
    #ifdef LINUX
        #define FLX_EXPORT
    #elif WINDOWS
        #define FLX_EXPORT	__declspec(dllimport)
    #endif
#endif

#endif // FLEXIEXPORTS_H
