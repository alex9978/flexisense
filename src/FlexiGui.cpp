
/*! FlexiSense
 *  FlexiGui.cpp
 *  Author: Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  Notes:
 */

#include <FlexiSense/FlexiGui.h>

FlexiGui::FlexiGui(std::string &interfaceName)
{
	name				= interfaceName;

	focusedComponent 	= 0;
	rolloveredComponent	= 0;
	wrappedKeyListener	= 0;
}

FlexiGui::~FlexiGui()
{
	// write properties
	saveProperties();

	// delete wrapped listeners
	if(wrappedKeyListener) delete wrappedKeyListener;

	// delete elements
	std::list<FlexiWidget *>::iterator it;
	for(it=widgets.begin(); it!=widgets.end(); it++)
        delete *(it);
	widgets.clear();
}

bool FlexiGui::addChild(FlexiWidget *child)
{
    if(!child || !child->isContainer())
        return false;
    
	widgets.push_back(child);
	return true;
}

void FlexiGui::paint()
{    
	// draw all widgets
	std::list<FlexiWidget *>::iterator it;
	for(it=widgets.begin(); it!=widgets.end(); it++)
	{
        FlexiWidget *w = *(it);
        //
        if(w->isVisible())
            w->paint();
	}
}

void FlexiGui::wrapKeyEventGenerator(FlexiKeyListener *listener)
{
	if(wrappedKeyListener)
        delete wrappedKeyListener;
    
	wrappedKeyListener = listener;
}

void FlexiGui::saveProperties()
{
/*	// if no interface name exits
	if(name == "") return;

	// filename
	SWString filename = FSManager::instance()->resourcePath + name;
	filename += ".fpv";

	// open file
	FILE *fp = fopen(filename.GetStr(), "wb");
	if(fp == NULL) return;

	// write data
	FlexiWidget *wid;
	for(SWint i=0; i<containers.NumElems(); i++)
	{
		FlexiComponent **comps = containers[i]->components;
		int noc = containers[i]->numberOfComponents;

		for(int j=0; j<noc; j++)
			if(comps[j]->getType() == FLX_WIDGET)
			{
				wid = (FlexiWidget *)comps[j];
				if(wid->recordable) wid->savePropertyValue(fp);
			}
	}

	// close file
	long size = flen(fp);
	fclose(fp);

	// if no data recorded remove file
	if(size == 0) remove(filename.GetStr());*/
}

void FlexiGui::loadProperties()
{
/*	// if no interface name exits
	if(name == "") return;

	// filename
	SWString filename = FSManager::instance()->resourcePath + name;
	filename += ".fpv";

	// open file
	FILE *fp = fopen(filename.GetStr(), "rb");
	if(fp == NULL) return;

	// load data
	FlexiWidget *wid;
	for(int i=0; i<containers.NumElems(); i++)
	{
		FlexiComponent **comps = containers[i]->components;
		int noc = containers[i]->numberOfComponents;

		for(int j=0; j<noc; j++)
			if(comps[j]->getType() == FLX_WIDGET)
			{
				wid = (FlexiWidget *)comps[j];
				if(wid->recordable)	wid->loadPropertyValue(fp);
			}
	}

	// close file
	fclose(fp);*/
}

void FlexiGui::setInterfaceFont(FlexiFont *font)
{
//    std::vector<FlexiElement *>::iterator it;
//	for(it=elements.begin(); it!=elements.end(); it++)
//        *(it)->setComponentsFont(font);
}

void FlexiGui::callWrappedKeyListener(FlexiKeyEvent *event)
{
	// set event's source component
	event->setSource(this);

	// try to execute event's related code
	switch( event->getType() )
	{
		case FLX_EVENT_KEY_DOWN:	wrappedKeyListener->onKeyDown(event);	break;
		case FLX_EVENT_KEY_UP:		wrappedKeyListener->onKeyUp(event);		break;
		case FLX_EVENT_PRESS:		wrappedKeyListener->onKeyPress(event);	break;
	}

	// consume event
	event->consume();
}
