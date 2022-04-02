
#include <FlexiSense/common/FlexiCatalog.h>

FlexiCatalog::FlexiCatalog()
{
}

FlexiCatalog::~FlexiCatalog()
{
    strings.clear();
}

bool FlexiCatalog::load(char *filename)
{
    TiXmlDocument doc(filename);

	if(!doc.LoadFile())
        return false;

	TiXmlHandle     hDoc(&doc);
	TiXmlElement   *pElem;
	TiXmlHandle     hRoot(0);
	std::string     name;

	/*! block: name */
    pElem = hDoc.FirstChildElement().Element();
    // should always have a valid root but handle gracefully if it does
    if(!pElem)
        return false;
    name = pElem->Value();
    if(name != "FlexiCatalog")
        return false;

    // save this for later
    hRoot = TiXmlHandle(pElem);

	/*! block: string table */
    strings.clear();        // trash existing table
    pElem = hRoot.FirstChild("strings").FirstChild().Element();
    for(pElem=0; pElem!=0; pElem=pElem->NextSiblingElement())
    {
        const char *pKey = pElem->Value();
        const char *pText = pElem->GetText();
        if(pKey && pText)
            strings[pKey]=pText;
    }

	return true;
}

std::string FlexiCatalog::getString(char *id)
{
    return strings[id];
}
