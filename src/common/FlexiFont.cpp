
#include <FlexiSense/common/FlexiFont.h>
#include <FlexiSense/FlexiManager.h>
#include <stdlib.h>

FlexiFont::FlexiFont(std::string fontname)
{
	// set file = default path + filename
	std::string file = FlexiManager::instance()->fontPath + fontname;

	if(FT_New_Face(FlexiManager::instance()->getFreeType(), file.c_str(), 0, &face))
		FLX_LOG(1, "ERROR: Can't load font '%s'", fontname.c_str());

	FLX_LOG(1, "FlexiFont: Font '%s' loaded. (Family: %s, Style: %s, Kerning: %s)", fontname.c_str(), face->family_name, face->style_name, (FT_HAS_KERNING(face))?"yes":"no");
    
	fontname = fontname.substr(0, fontname.length()-4);
	name = fontname;
	currentSize = 0;
}

FlexiFont::~FlexiFont()
{
    FlexiResourceManager *rm = FlexiManager::instance()->getResourceManager();

	for(unsigned int i=0; i<glyphCache.size(); i++)
    {
		FT_Done_Glyph((FT_GlyphRec_*)glyphCache[i]->_glyph);
        delete glyphCache[i]->_image;
    }

	FLX_LOG(1, "FlexiFont(%s): %i font glyphs cached", name.c_str(), glyphCache.size());

	glyphCache.clear();
	FT_Done_Face(face);
}

const std::string &FlexiFont::getName() const
{
    return name;
}

bool FlexiFont::setCharmap(long encoding)
{
	if(FT_Select_Charmap(face, (FT_Encoding_)encoding))
	{
		FLX_LOG(1, "FlexiFont: No charmap in the face corresponds to the encoding queried");
		return false;
	}
	return true;
}

FlexiGlyphCache *FlexiFont::renderGlyph(unsigned char chr, int size)
{
	// convert character code to glyph index
	FT_UInt glyph_index = FT_Get_Char_Index(face, chr);

	// try to get it from cache
	int num = getChachedGlyph(chr, size);
	if(num >= 0)
		return glyphCache[num];

	// create new item in cache
	FlexiGlyphCache *glyphItem = new FlexiGlyphCache;
	glyphItem->_char = chr;
	glyphItem->_size = size;
	glyphItem->_index = glyph_index;

	// set size
	if(currentSize != size)
	{
		FT_Set_Pixel_Sizes(face, 0, size);
		currentSize = size;
	}

	// load glyph image into the slot without rendering
	if(FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT)) return 0;

	// extract glyph image and store it in our table
	FT_GlyphSlot slot = face->glyph;
	if(FT_Get_Glyph(slot, &glyphItem->_glyph)) return 0;

	// store position increment
	glyphItem->_advance.x = slot->advance.x >> 6;
	glyphItem->_advance.y = slot->advance.y >> 6;

	// renderize glyph
	if(FT_Glyph_To_Bitmap(&glyphItem->_glyph, FT_RENDER_MODE_NORMAL, 0, 0))
        return 0;
	glyphItem->_bitmap = (FT_BitmapGlyph)glyphItem->_glyph;

	// make texture name
    char buf[sizeof(int)*8+1];
    sprintf(buf, "%i", size);
    
	std::string filename = "fonts/cache/";
	filename += name;
	filename += "_";
	filename += int(chr);
	filename += "_";
	filename += buf;
	filename += ".tga";

	if(!FlexiUtility::FileExists(filename.c_str()))
	{
		// create new texture
		FT_Bitmap *bm = &glyphItem->_bitmap->bitmap;
		unsigned int w = pow(2,(((int)sqrtf(bm->pitch))+1));
		unsigned int h = pow(2,(((int)sqrtf(bm->rows))+1));
		unsigned int imageName, hDiff = h-bm->rows;
		ilGenImages(1, &imageName);
		ilBindImage(imageName);
		ilTexImage(w, h, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, 0);
		ilClearColour(255,255,255,0);
		ilClearImage();

		// copy data
		unsigned long index = 0, *buf = (unsigned long *)ilGetData();
		for(int b=0; b<bm->rows; b++)
		{
			for(int a=0; a<bm->width; a++)			
				buf[w*(bm->rows-(b+1-hDiff))+a] = 0x00ffffff | (bm->buffer[index+a] << 24);
			
			index += bm->pitch;
		}

		// save texture
		ilSave(IL_TGA, (char *)filename.c_str());
	}

    glyphItem->_image = FLX_LOADIMAGE((char *)filename.c_str());

	// add to cache
	glyphCache.push_back(glyphItem);

	return glyphItem;
}

int FlexiFont::getKerning(unsigned int leftIndex, unsigned int rightIndex)
{
	// retrieve kerning distance and return pen offset
	if(FT_HAS_KERNING(face) && leftIndex && rightIndex)
	{
		FT_Vector delta;
		FT_Get_Kerning(face, leftIndex, rightIndex, FT_KERNING_DEFAULT, &delta);
		return delta.x >> 6;
	}
	return 0;
}

int FlexiFont::getChachedGlyph(unsigned char chr, int size)
{
	for(int i=glyphCache.size()-1; i>=0; i--)
		if(glyphCache[i]->_char == chr && glyphCache[i]->_size == size)
			return i;

	return -1;
}
