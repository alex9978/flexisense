
/** @class FlexiLog
 *  @brief Logger
 *  @author Alessandro Rasulo (mailto: alex9978@gmail.com)
 */

#ifndef FLEXILOG_H
#define	FLEXILOG_H

#include <FlexiSense/FlexiExports.h>
#include <stdio.h>
#include <stdarg.h>

#define MAX_LOG_LINE            4096

class FLX_EXPORT FlexiLog
{
public:
	FlexiLog();
	virtual ~FlexiLog();

    // Static instance
	static FlexiLog *instance   ();

    // Main methods
    bool initialize			    ();
    virtual bool shutdown		();

    // Logging
    bool log                    (int level, const char *str, ...);
    int logLevel;

private:

    // File stream
    FILE *os;

    // Level
    bool isInLogLevel(int level);

    // Buffer
    char    m_buf[MAX_LOG_LINE];

    // Misc
	bool	initialized;
};

#endif

