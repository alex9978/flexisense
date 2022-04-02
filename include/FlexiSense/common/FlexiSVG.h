
/*! FlexiSense
 *  FlexiSVG.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Image resource
 */

#ifndef FLEXISVG_H
#define FLEXISVG_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/common/FlexiLog.h>
#include <librsvg-2/librsvg/rsvg.h>
#include <string>

class FLX_EXPORT FlexiSVG
{
public:
    FlexiSVG                    ();
	virtual ~FlexiSVG           ();

    bool load                   (char *filename, bool defaultPath = true);
    RsvgHandle *getHandle       ();

private:
    std::string			        file;
    RsvgHandle                 *handle;
};

#endif // FLEXIIMAGE_H
