
/** @class FlexiCatalog
 *  @brief Strings catalog resource
 *  @author Alessandro Rasulo (mailto: alex9978@gmail.com)
 */

#ifndef FLEXICATALOG_H
#define FLEXICATALOG_H

#include <FlexiSense/FlexiExports.h>
#include <tinyxml.h>
#include <map>
#include <string>

class FLX_EXPORT FlexiCatalog
{
public:
	FlexiCatalog			();
	virtual ~FlexiCatalog   ();

	bool load   			(char *filename);
	std::string getString	(char *id);

private:
    std::map<std::string,std::string> strings;
};

#endif

