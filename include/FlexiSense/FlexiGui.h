
/*! FlexiSense
 *  FlexiGui.h --- Interface
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#ifndef FLEXIGUI_H
#define FLEXIGUI_H

#include <FlexiSense/FlexiExports.h>
#include <FlexiSense/FlexiManager.h>
#include <FlexiSense/FlexiObject.h>
#include <FlexiSense/FlexiWidget.h>
#include <FlexiSense/common/FlexiCatalog.h>

#include <list>
#include <string>

class FLX_EXPORT FlexiGui : public FlexiObject
{
friend class FlexiManager;
//friend class FlexiWidget;

public:
	FlexiGui(std::string &interfaceName);
	virtual ~FlexiGui();

	virtual void init			() {}
	virtual void update			() {}
	void paint					();

	/*! Children */
	bool addChild			    (FlexiWidget *child);

	/*! Events */
	void wrapKeyEventGenerator	(FlexiKeyListener *listener);

	/*! Properties */
	void saveProperties			();
	void loadProperties			();

	/*! Fonts */
	void setInterfaceFont		(FlexiFont *font);

	std::string					 name;					// gui name

protected:
	std::list<FlexiWidget *>	 widgets;			    // elements

	FlexiWidget		    		*focusedComponent;		// focused component
	FlexiWidget	    			*rolloveredComponent;	// last component touched by mouse
	FlexiKeyListener			*wrappedKeyListener;

	// private methods
	void callWrappedKeyListener	(FlexiKeyEvent *event);
};

#endif
