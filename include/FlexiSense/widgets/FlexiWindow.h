
/*! FlexiSense
 *  FlexiWindow.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Base window
 */

#ifndef FLEXIWINDOW_H
#define FLEXIWINDOW_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/FlexiWidget.h>
#include <FlexiSense/common/FlexiFont.h>
#include <FlexiSense/common/FlexiImage.h>
#include <FlexiSense/widgets/FlexiLabel.h>

#include <cairo/cairo.h>

class FLX_EXPORT FlexiWindow : public FlexiWidget
{
public:
    FlexiWindow             (const FlexiPosition &p, const FlexiSize &s, FlexiWidget *parent);
    virtual ~FlexiWindow    ();
    
    void resize             (const FlexiPosition &p, const FlexiSize &s);
	virtual void paint      ();

    cairo_t *getContext     ();
    
private:
    FlexiImage              *imgSurface;
    cairo_t                 *cairoContext;

    FlexiFont               *fontTitle;
    //FlexiFrame              *frame;
    FlexiLabel              *lblTitle;
};

#endif // FLEXIWINDOW_H
