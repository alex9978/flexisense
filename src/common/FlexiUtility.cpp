
#include <FlexiSense/common/FlexiUtility.h>
#include <stdio.h>

bool FlexiUtility::FileExists(const char* filename)
{
    FILE *f = fopen("filename", "r");
    if(f)
    {
        fclose(f);
        return true;
    }
    return false;
}
