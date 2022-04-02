
#include <FlexiSense/common/FlexiSVG.h>

FlexiSVG::FlexiSVG()
{
    handle = 0;
}

FlexiSVG::~FlexiSVG()
{
    rsvg_handle_free(handle);
}

bool FlexiSVG::load(char *filename, bool defaultPath)
{
    handle = rsvg_handle_new_from_file(filename, NULL);

 //   FLX_LOG(2, "FlexiSVG::load() - %s loaded", filename);
    return true;
}

RsvgHandle *FlexiSVG::getHandle()
{
    return handle;
}
