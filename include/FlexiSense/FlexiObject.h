
/*! @class FlexiObject
 *  @brief Base object
 *  @author Alessandro Rasulo (mailto: alex9978@gmail.com)
 */

#ifndef FLEXIOBJECT_H
#define FLEXIOBJECT_H

#include <FlexiSense/FlexiExports.h>
#include <string>

class FLX_EXPORT FlexiObject
{
public:
    FlexiObject();
    virtual ~FlexiObject();

    // Gets the name of the class
	const std::string &getClassName() const;

protected:
    std::string     className;
};

#endif // FLEXIOBJECT_H
