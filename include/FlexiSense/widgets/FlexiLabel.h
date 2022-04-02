
/*! @class FlexiLabel
 *  @brief Label for text output
 *  @author Alessandro Rasulo (mailto: alex9978@gmail.com)
 */

#ifndef FLEXILABEL_H
#define FLEXILABEL_H

#include <FlexiSense/common/FlexiDefines.h>
#include <FlexiSense/common/FlexiFont.h>
#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/FlexiWidget.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

class FLX_EXPORT FlexiLabel : public FlexiWidget
{
public:
	FlexiLabel(const FlexiPosition &p, const FlexiSize &s, const char *caption, int align, FlexiFont *font, int size, int flags, FlexiWidget *prnt);
	virtual ~FlexiLabel();
	
    void resize(const FlexiPosition &p, const FlexiSize &s);
	virtual void paint();

	void setCaption         (std::string &caption);
	std::string &getCaption ();
	void setFont            (FlexiFont *font);
	void setFontSize        (int size);
	void setAlignment       (int align);
	void setShadow          (bool shadowed);

	// recordable
/*	void savePropertyValue	(FILE *file) {}
	void loadPropertyValue	(FILE *file) {}*/

private:
	FlexiFont			*font;
	int                  fontSize,
						 fontScaledSize;
	bool				 shadow,
						 recalcGlyphs;
	
	std::string			 text;
	int                  alignment,
						 nCharsToPaint,
						 string_width,
						 string_height;

	float				 calculate_x_aligned();
	float				 calculate_y_aligned();
    
    void                 clearLists();	

	// glyphs and positions
	std::vector<FlexiGlyphCache	*>	glyph_list;
	std::vector<FT_Vector *>        pos_list;
};

#endif

