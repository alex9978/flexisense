
#include <FlexiSense/widgets/FlexiLabel.h>
#include <FlexiSense/FlexiManager.h>

/*! Constructor
 */
FlexiLabel::FlexiLabel(const FlexiPosition &p, const FlexiSize &s, const char *caption, int align, FlexiFont *font, int size, int flags, FlexiWidget *prnt) : FlexiWidget(p, s, prnt)
{
    // set class name
    className           = "label";
    
	setFlags(flags, true);
	
	focusable			= false;
    this->font          = (font)? font : FlexiManager::instance()->getDefaultFont();
	fontSize			= size;
	text				= caption;
	alignment			= align;
    shadow              = false;

	recalcGlyphs		= true;
}

/*! Destructor
 */
FlexiLabel::~FlexiLabel()
{
}

void FlexiLabel::resize(const FlexiPosition &p, const FlexiSize &s)
{
    position = p;
    size = s;
    recalcGlyphs = true;
}

void FlexiLabel::paint()
{	
	FlexiGlyphCache *g = 0;
	FT_BBox	bbox;
	unsigned int previous = 0;
	int x, y, prev_adv = 0;
	float lblW = getSize().width * FLX_HRATIO();

	// check visibility
	if(!visible) return;
	
	// check text presence
	if(text.length() == 0) return;

	// calculate font size	
	fontScaledSize = fontSize * FLX_VRATIO();

	// characters
	nCharsToPaint = text.length();
	int charsToBlendAt = nCharsToPaint + 1;
	char blendStep = 0x00;

	if(recalcGlyphs)
	{
		// ----- TEXT RENDERING: PASS 1a ----- Calculate all glyphs position and kerning -----	

        clearLists();

		for(int i=0; i<nCharsToPaint; i++)
		{
			// get glyph
			g = font->renderGlyph(text[i], fontScaledSize);
			if(!g)
                continue;

			// add to list
			FT_Vector *v = new FT_Vector();
			v->x = prev_adv;
			v->y = 0;
		
			glyph_list.push_back(g);
			pos_list.push_back(v);

			previous = g->_index;
			prev_adv = v->x + g->_advance.x + font->getKerning(previous, g->_index);
		}

		FT_Vector *v = new FT_Vector();
		v->x = prev_adv;
		v->y = 0;
		pos_list.push_back(v);

		// ----- TEXT RENDERING: PASS 1b ----- Multiline and wordwrap ------------------------

	/*	if(getFlags(FLX_MULTILINE|FLX_WORDWRAP))
		{
			int word_start = 0, word_end = 0, xdiff = 0, ydiff = 0;
			bool wrap = false;
			
			for(int i=0; i < nCharsToPaint; i++)
			{
				// wordwrap		
				for(int j=i; j < nCharsToPaint; j++)
				{					
					if(pos[j+1].x + xdiff >= lblW) { wrap = true; break; }
					if(isspace((int)text.charAt(j))) break;			
				}

				if(wrap)
				{
					xdiff = -pos[i].x;
					ydiff += (int)(fontSize * FSManager::instance()->getVRatio());
					wrap = false;
				}
				pos[i].x += xdiff;
				pos[i].y += ydiff;
			}
		}*/

		// ----- TEXT RENDERING: PASS 1c ----- Calculate text bounding box and position -----

		// initialize string bbox to "empty" values
		bbox.xMin = bbox.yMin = 32000;
		bbox.xMax = bbox.yMax = -32000;
		
		int minh = 999999;

		// for each glyph image, compute its bounding box,
        // translate it, and grow the string bbox
		for(int i=0; i<glyph_list.size(); i++)
		{
			FT_BBox glyph_bbox;
			FT_Glyph_Get_CBox(glyph_list[i]->_glyph, ft_glyph_bbox_pixels, &glyph_bbox);
			
			glyph_bbox.xMin += pos_list[i]->x;
			glyph_bbox.xMax += pos_list[i]->x;
			glyph_bbox.yMin += pos_list[i]->y;
			glyph_bbox.yMax += pos_list[i]->y;

			if(glyph_bbox.xMin < bbox.xMin) bbox.xMin = glyph_bbox.xMin;
			if(glyph_bbox.yMin < bbox.yMin) bbox.yMin = glyph_bbox.yMin;
			if(glyph_bbox.xMax > bbox.xMax) bbox.xMax = glyph_bbox.xMax;
			if(glyph_bbox.yMax > bbox.yMax) bbox.yMax = glyph_bbox.yMax;

			//if(glyph_list[i]->_bitmap->top > 0 && glyph_list[i]->_bitmap->top < minh) minh = glyph_list[i]->_bitmap->top;
		}
		
		// check that we really grew the string bbox
		if(bbox.xMin > bbox.xMax)
		{
			bbox.xMin = 0;
			bbox.yMin = 0;
			bbox.xMax = 0;
			bbox.yMax = 0;
		}

		// compute string dimensions in integer pixels
		string_width = bbox.xMax - bbox.xMin;
		string_height = bbox.yMax - bbox.yMin;	

		recalcGlyphs = false;	
	}

	// compute start position
	x = calculate_x_aligned();
	y = calculate_y_aligned();

	// compute string alpha blending
/*	if(string_width > lblW)
	{		
		for(i=0; i<nCharsToPaint; i++)
			if(pos[i+1].x >= lblW)
				break;
		
		nCharsToPaint = i;
		//charsToBlendAt = nCharsToPaint - (nCharsToPaint / 3);
		blendStep = 0xff / (nCharsToPaint - charsToBlendAt);
	}*/

	// ----- TEXT RENDERING: PASS 2 ----- Rasterize text ------------------------------------

	FlexiColor textColor(&foreColor),
               shadowColor(0x000000ff);

	FlexiGfxRenderer *r = FlexiManager::instance()->getRenderer();
	for(int i=0; i<glyph_list.size(); i++)
	{	
		if(shadow)
			r->drawImage(x + pos_list[i]->x + glyph_list[i]->_bitmap->left + 1,
                         y + pos_list[i]->y + string_height - glyph_list[i]->_bitmap->top + 1,
                         glyph_list[i]->_image,
                         &shadowColor);

		r->drawImage(x + pos_list[i]->x + glyph_list[i]->_bitmap->left,
					 y + pos_list[i]->y + string_height - glyph_list[i]->_bitmap->top,
					 glyph_list[i]->_image,
					 &textColor);
	}
}

/*! Sets the caption of the label
 *  @param caption The string to set
 */
void FlexiLabel::setCaption(std::string &caption)
{
	text = caption;
	recalcGlyphs = true;
}

/*! Gets the caption of the label
 *  @return The caption
 */
std::string &FlexiLabel::getCaption()
{   
    return text;
}

/*! Sets the font of the label
 *  @param font A loaded font
 */
void FlexiLabel::setFont(FlexiFont *font)
{
	this->font = font; 
	recalcGlyphs = true;
}

/*! Sets the font size
 *  @param size The size of the font
 */
void FlexiLabel::setFontSize(int size)
{ 
    fontSize = size;
    recalcGlyphs = true;
}

/*! Sets the alignment of the label
 *  @param Label alignment
 *  @sa FLX_ALIGN
 */
void FlexiLabel::setAlignment(int align)
{ 
    alignment = align;
}

/*! Sets the shadow visibility
 *  @param shadowed as boolean
 */
void FlexiLabel::setShadow(bool shadowed)
{ 
    shadow = shadowed;
}

void FlexiLabel::clearLists()
{
    for(int i=0; i<pos_list.size(); i++)
        delete pos_list[i];
	
    pos_list.clear();
    glyph_list.clear();
}

float FlexiLabel::calculate_x_aligned()
{
	float absX = getAbsPosition().x * FLX_HRATIO();
	float lblW = getSize().width * FLX_HRATIO();

	// calculate aligned coordinate
	if( (alignment & FLX_ALIGN_INNER) ||
 	  ( (alignment & FLX_ALIGN_OUTER) && (alignment & FLX_ALIGN_TOP || alignment & FLX_ALIGN_BOTTOM) ) )
	{
		//    *           *           *
		//   +-----+   +-----+   +-----+
		//   |*    |   |  *  |   |    *|
		//   +-----+   +-----+   +-----+
		//    *           *           *
		if(alignment & FLX_ALIGN_LEFT)			return absX;
		else if(alignment & FLX_ALIGN_CENTER)	return absX + (lblW - string_width) / 2;
		else if(alignment & FLX_ALIGN_RIGHT)	return absX + lblW - string_width;
	}
	else if(alignment & FLX_ALIGN_OUTER)
	{	
		//
		//   +-----+   +-----+ 
		//  *|     |   |     |*
		//   +-----+   +-----+
		//
 		if(alignment & FLX_ALIGN_LEFT)			return absX - string_width - 4;
		else if(alignment & FLX_ALIGN_RIGHT)	return absX + lblW + 4;
	}

	return absX;
}

float FlexiLabel::calculate_y_aligned()
{
	float absY = getAbsPosition().y * FLX_VRATIO();
	float lblH = getSize().height * FLX_VRATIO();

	// calculate aligned coordinate
	if((alignment & FLX_ALIGN_OUTER) && (alignment & FLX_ALIGN_TOP))
	{
		//    *           *           *
		//   +-----+   +-----+   +-----+
		//   |     |   |     |   |     |
		//   +-----+   +-----+   +-----+
		//
		return absY - string_height - 2;
	}
	else if((alignment & FLX_ALIGN_OUTER) && (alignment & FLX_ALIGN_BOTTOM))
	{
		//
		//   +-----+   +-----+   +-----+
		//   |     |   |     |   |     |
		//   +-----+   +-----+   +-----+
		//    *           *           *
		return absY + lblH + 2;	
	}
	else	
	{
		//
		//   +-----+   +-----+   +-----+
		//  *|*    |   |  *  |   |    *|*
		//   +-----+   +-----+   +-----+
		//
		return absY + ((lblH - string_height) / 2);
	}
}
