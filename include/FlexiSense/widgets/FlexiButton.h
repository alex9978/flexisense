
/*! FlexiSense
 *  FlexiButton.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Simple button
 */

#ifndef FLEXIBUTTON_H
#define FLEXIBUTTON_H

#include <FlexiSense/FlexiWidget.h>
#include <FlexiSense/widgets/FlexiLabel.h>

class FLX_EXPORT FlexiButton : public FlexiWidget
{
public:
	FlexiButton(const FlexiPosition &p, const FlexiSize &s, const std::string caption, FlexiWidget *prnt);
	virtual ~FlexiButton();
	
	void resize(const FlexiPosition &p, const FlexiSize &s);
	virtual void paint();
	
	// images
	void setPressedImage			(FlexiImage *image);
	void setHilightedImage			(FlexiImage *image);
	
	// pressed
	void setPressedState			(bool state);
	bool getPressedState			() { return pressed; }

	// recordable
	void savePropertyValue			(FILE *file) {}
	void loadPropertyValue			(FILE *file) {}
	
protected:
    FlexiLabel                      *label;
	FlexiImage						*pressedImage,
									*hilightedImage;
	bool 							 pressed;
};

#endif
