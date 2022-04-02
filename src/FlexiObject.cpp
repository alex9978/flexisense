
#include <FlexiSense/FlexiObject.h>

/*! Constructor
 */
FlexiObject::FlexiObject()
{
    className = "<unknown>";
}

/*! Destructor
 */
FlexiObject::~FlexiObject()
{
}

/*! Get the classname of the object
 *  @return classname
 */
const std::string &FlexiObject::getClassName() const
{
	return className;
}
