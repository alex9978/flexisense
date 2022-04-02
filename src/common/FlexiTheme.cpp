
/*! FlexiSense
 *  FlexiTheme.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Theme class
 */

#include <FlexiSense/common/FlexiTheme.h>
#include <FlexiSense/FlexiGfxRenderer.h>
#include <FlexiSense/FlexiManager.h>

FlexiTheme::FlexiTheme()
{
	loaded = false;
}

FlexiTheme::~FlexiTheme()
{
    unload();
}

bool FlexiTheme::load(const char *themeName)
{    
    // put loaded to false
    loaded = false;

    // get resource manager
    FlexiResourceManager *rm = FlexiManager::instance()->getResourceManager();
    
    // get filename
    std::string path = FlexiManager::instance()->themePath + themeName,
                file = path + "/theme.xml";                
    
    // create xml document
    TiXmlDocument doc(file.c_str());      
    
    // load file
	if(!doc.LoadFile())
    {
        FLX_LOG(1, "FlexiTheme.load() - Failed to load theme file '%s'", file.c_str());
        return false;
    }

	TiXmlHandle     hDoc(&doc);
	TiXmlElement   *pElem;
	TiXmlHandle     hRoot(0);
	std::string     name;

	/*! block: name */
    pElem = hDoc.FirstChildElement().Element();    
    if(!pElem)
    {
        FLX_LOG(1, "FlexiTheme.load() - FirstChildElement() not found");
        return false;
    }    
    name = pElem->Value();
    if(name != "FlexiTheme")
    {
        FLX_LOG(1, "FlexiTheme.load() - Wrong XML file type");
        return false;
    }

    // save this for later
    hRoot = TiXmlHandle(pElem);

	/*! block: colors */    
    unsigned int color = 0;
    pElem = hRoot.FirstChild("colors").FirstChild().Element();
    for(pElem; pElem; pElem=pElem->NextSiblingElement())
    {
        std::string key = pElem->Value(),
                    text = pElem->Attribute("color");
            
        sscanf(text.c_str(), "%x", &color);
        
        if(key == "background")
            background.set(color);
        else if(key == "foreground")
            foreground.set(color);
        else if(key == "wnd_titlebar_textcolor")
            wnd_titlebar_textcolor.set(color);
    }
    
    /*! block: images */    
    pElem = hRoot.FirstChild("images").FirstChild().Element();
    for(pElem; pElem; pElem=pElem->NextSiblingElement())
    {
        std::string key = pElem->Value(),
                    text = pElem->Attribute("image"),
                    tmpfile = path + "/" + text;        

        if(key == "wallpaper")
            wallpaper = rm->getImage((char *)tmpfile.c_str());
        else if(key == "pointer")
            pointer = rm->getImage((char *)tmpfile.c_str());
        else if(key == "frame")
            frame = rm->getImage((char *)tmpfile.c_str());
        else if(key == "wnd_titlebar")
            wnd_titlebar = rm->getImage((char *)tmpfile.c_str());
        else if(key == "wnd_titlebar_inactive")
            wnd_titlebar_inactive = rm->getImage((char *)tmpfile.c_str());
        else if(key == "wnd_side")
            wnd_side = rm->getImage((char *)tmpfile.c_str());
        else if(key == "wnd_bottom")
            wnd_bottom = rm->getImage((char *)tmpfile.c_str());
        else if(key == "btn_normal")
            btn_normal = rm->getImage((char *)tmpfile.c_str());
    }
    
    /*! block: properties */    
    pElem = hRoot.FirstChild("properties").FirstChild().Element();
    for(pElem; pElem; pElem=pElem->NextSiblingElement())
    {
        std::string key = pElem->Value(),
                    text = pElem->Attribute("value");
        
        if(key == "wnd_titlebar_height")
            wnd_titlebar_height = atoi(text.c_str());
        else if(key == "wnd_side_width")
            wnd_side_width = atoi(text.c_str());
        else if(key == "wnd_bottom_height")
            wnd_bottom_height = atoi(text.c_str());
    }
    
    FLX_LOG(1, "FlexiTheme::load() - Theme '%s' loaded", themeName);
    loaded = true;
	return true;
}

void FlexiTheme::unload()
{
    FlexiResourceManager *rm = FlexiManager::instance()->getResourceManager();

    rm->releaseResource(wallpaper);
    rm->releaseResource(pointer);
    rm->releaseResource(frame);
    rm->releaseResource(wnd_titlebar);
    rm->releaseResource(wnd_titlebar_inactive);
    rm->releaseResource(wnd_side);
    rm->releaseResource(wnd_bottom);
    rm->releaseResource(btn_normal);

	loaded = false;
}

bool FlexiTheme::isImageTheme(FlexiImage *image)
{
	if(	(image == wallpaper) ||
        (image == pointer) ||
        (image == frame) ||
		(image == frame_border) ||
		(image == wnd_titlebar) ||
		(image == wnd_titlebar_inactive) ||
        (image == wnd_side) ||
        (image == wnd_bottom) ||
		(image == &button_close_normal) ||
		(image == &button_close_focus) ||
		(image == &button_close_pressed) ||
		(image == &button_inactive) ||
		(image == btn_normal) ||
		(image == &button_focus) ||
		(image == &button_pressed) ||
		(image == &text_entry) ||
		(image == &text_entry_focus))
		return true;

	return false;
}
