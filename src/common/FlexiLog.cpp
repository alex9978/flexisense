
#include <FlexiSense/common/FlexiLog.h>
#include <stdio.h>

static FlexiLog defaultLog;

FlexiLog::FlexiLog()
{
	initialized = false;
}

FlexiLog::~FlexiLog()
{
    os = 0;
}

FlexiLog *FlexiLog::instance()
{
	return &defaultLog;
}

bool FlexiLog::initialize()
{
    if(initialized)
        return true;
    
    os = fopen("flexisense.log", "w");
    if(!os)
    {
        printf("Error opening output file stream\n");
        return false;
    }

    printf("FlexiLog initialized to 'flexisense.log'\n");
    logLevel = 2;
    initialized = true;
}

bool FlexiLog::shutdown()
{
    fclose(os);
    initialized = false;
}

bool FlexiLog::log(int level, const char* str, ...)
{
    if(!initialized)
        initialize();

    if(isInLogLevel(level))
    {
        va_list ap;
        va_start(ap, str);
        if(vsnprintf(m_buf, MAX_LOG_LINE-1, str, ap) == -1)
            printf("FlexiLog::log, buffer is too small!\n");
        va_end(ap);
        fprintf(os, "%s\n", m_buf);
        fflush(os);
        return true;
    }
    return false;
}

bool FlexiLog::isInLogLevel(int level)
{
    return(level <= logLevel);
}
