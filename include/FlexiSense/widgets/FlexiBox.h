
/*! @class FlexiBox
 *  @brief Simple box
 *  @author Alessandro Rasulo (mailto: alex9978@gmail.com)
 */

#ifndef FLEXIBOX_H
#define FLEXIBOX_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/FlexiWidget.h>

class FLX_EXPORT FlexiBox : public FlexiWidget
{
public:
    FlexiBox(const FlexiPosition &p, const FlexiSize &s, FlexiWidget *prnt);
    virtual ~FlexiBox();
    
    void resize(const FlexiPosition &p, const FlexiSize &s);
	virtual void paint();
    
protected:
private:
};

#endif // FLEXIBOX_H
