
/*! FlexiSense
 *  FlexiTheme.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Theme class
 */

#ifndef FLEXITHEME_H
#define FLEXITHEME_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/common/FlexiColor.h>
#include <FlexiSense/common/FlexiImage.h>
#include <FlexiSense/common/FlexiLog.h>

#include <tinyxml.h>
#include <string>

#define FLX_SAFEDELETEIMAGE(x)	if(!FLX_THEME.isImageTheme(x)) delete x;

class FLX_EXPORT FlexiTheme
{
public:
	FlexiTheme();
	virtual ~FlexiTheme();

	/*! Load theme */
	bool load(const char *themeName);
	void unload();
	bool isLoaded() { return loaded; }

	// Returns true if image is contained in this theme
	bool isImageTheme(FlexiImage *image);

	// The default background color
	FlexiColor		background;

	// The default foreground color used for labels and text
    FlexiColor		foreground;

    // The default window titlebar text color
    FlexiColor      wnd_titlebar_textcolor;
    
	/*! Wallpaper for screens */
	FlexiImage     *wallpaper;
    
    /*! Mouse pointers */
    FlexiImage     *pointer;

	/*! Generic frame border skin */
    FlexiImage     *frame,
                   *frame_border;

	/*! Window skin */
	FlexiImage	   *wnd_titlebar,
                   *wnd_titlebar_inactive,
                   *wnd_side,
                   *wnd_bottom;

	/*! Window buttons skin */
	FlexiImage	    button_close_normal;
	FlexiImage	    button_close_focus;
	FlexiImage	    button_close_pressed;

	/*! Button skin */
	FlexiImage	    button_inactive;
	FlexiImage	   *btn_normal;
	FlexiImage	    button_focus;
	FlexiImage	    button_pressed;

	/*! Text entry skin */
	FlexiImage	    text_entry;
	FlexiImage	    text_entry_focus;
    
    /*! Properties */
    int             wnd_titlebar_height,
                    wnd_side_width,
                    wnd_bottom_height;

private:
	std::string		subPath;
	bool			loaded;    
};

#endif // FLEXITHEME_H
