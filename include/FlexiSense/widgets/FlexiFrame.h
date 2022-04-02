
/*! FlexiSense
 *  FlexiFrame.h
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes: Base frame
 */

#ifndef FLEXIFRAME_H
#define FLEXIFRAME_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/FlexiWidget.h>

class FLX_EXPORT FlexiFrame : public FlexiWidget
{
public:
    FlexiFrame(const FlexiPosition &p, const FlexiSize &s, FlexiWidget *prnt);
    virtual ~FlexiFrame();
    
    void resize(const FlexiPosition &p, const FlexiSize &s);
	virtual void paint();
    
protected:
private:
};

#endif // FLEXIFRAME_H
