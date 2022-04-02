
/*! @class FlexiFont
 *  @brief Font class with TrueType support
 *  @author Alessandro Rasulo (mailto: alex9978@gmail.com)
 */

#ifndef FLEXIFONT_H
#define FLEXIFONT_H

#include <FlexiSense/common/FlexiImage.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <string>
#include <vector>

// Flexi Charmap encodings
#define FLX_ENCODING_NONE			FT_ENCODING_NONE			// reserved
#define FLX_ENCODING_UNICODE		FT_ENCODING_UNICODE			// unicode
#define FLX_ENCODING_MS_SYMBOL		FT_ENCODING_MS_SYMBOL		// microsoft symbol encoding
#define FLX_ENCODING_MS_SJIS		FT_ENCODING_MS_SJIS			// japanese
#define FLX_ENCODING_MS_GB2312		FT_ENCODING_MS_GB2312		// simplified chinese
#define FLX_ENCODING_MS_BIG5		FT_ENCODING_MS_BIG5			// traditional chinese
#define FLX_ENCODING_MS_WANSUNG		FT_ENCODING_MS_WANSUNG		// korean wansung
#define FLX_ENCODING_MS_JOHAB		FT_ENCODING_MS_JOHAB		// korean standard
#define FLX_ENCODING_ADOBE_LATIN_1	FT_ENCODING_ADOBE_LATIN_1	// adobe latin-1
#define FLX_ENCODING_ADOBE_STANDARD	FT_ENCODING_ADOBE_STANDARD	// adobe standard
#define FLX_ENCODING_ADOBE_EXPERT	FT_ENCODING_ADOBE_EXPERT	// adobe expert
#define FLX_ENCODING_ADOBE_CUSTOM	FT_ENCODING_ADOBE_CUSTOM	// custom encoding
#define FLX_ENCODING_APPLE_ROMAN	FT_ENCODING_APPLE_ROMAN		// 8-bit apple roman encoding
#define FLX_ENCODING_OLD_LATIN_2	FT_ENCODING_OLD_LATIN_2		// deprecated and was never used

typedef struct flexi_glyphcache
{
	unsigned char		 _char;
	int 				 _size;
	unsigned int		 _index;
	FT_Vector			 _advance;
	FT_GlyphRec			*_glyph;
	FT_BitmapGlyphRec	*_bitmap;
	FlexiImage			*_image;
} FlexiGlyphCache;

class FLX_EXPORT FlexiFont
{
public:
	FlexiFont(std::string fontname);
	virtual ~FlexiFont();

    const std::string &getName      () const;
	bool setCharmap                 (long encoding);
	FlexiGlyphCache *renderGlyph    (unsigned char chr, int size);
	int getKerning                  (unsigned int leftIndex, unsigned int rightIndex);

protected:
	FT_Face						    face;
	std::string					    name;
	int 						    currentSize;
	std::vector<FlexiGlyphCache *>	glyphCache;

private:
	int getChachedGlyph(unsigned char chr, int size);
};

#endif

