
#include <FlexiSense/FlexiWidget.h>
#include <FlexiSense/FlexiManager.h>
#include <FlexiSense/common/FlexiTheme.h>

/*! Constructor 
 *  @param p position
 *  @param s size
 *  @param prnt parent widget
 */
FlexiWidget::FlexiWidget(const FlexiPosition &p, const FlexiSize &s, FlexiWidget *prnt)
{
    // set class name
    className               = "FlexiWidget";

	// set father
	parent      			= prnt;
    
    // children
    children.clear();

	// misc
    container               = false;
	position				= p;
	originalPosition		= getAbsPosition();
  	size                    = s;
	visible					= true;
	active					= true;
	focusable				= true;
	focused					= false;
	hilighted				= false;
	flags					= 0;               

	// color
	backColor				= FLX_BACKGROUND;
	foreColor				= FLX_FOREGROUND;    
    
	// images
	backImage				= 0;
	gridBagType				= FlexiGridBag::FLX_GRIDBAG_1X1;

	// sensitive area
	area					= 0;

	// initialize default listeners
	actionListener 			= 0;
    focusListener			= 0;
	keyListener				= 0;
	mouseListener			= 0;

	// initialize user listeners
	userActionListener 		= 0;
    userFocusListener		= 0;
	userKeyListener			= 0;
	userMouseListener		= 0;
}

/*! Destructor
 */
FlexiWidget::~FlexiWidget()
{
	// delete images
	if(backImage            ) FLX_SAFEDELETEIMAGE(backImage);

	// delete sensitive area
	if(area                 ) delete area;

	// delete default listeners
	if(actionListener       ) delete actionListener;
	if(focusListener        ) delete focusListener;
	if(keyListener          ) delete keyListener;
	if(mouseListener        ) delete mouseListener;

	// delete user listeners
	if(userActionListener   ) delete userActionListener;
	if(userFocusListener    ) delete userFocusListener;
	if(userKeyListener 		) delete userKeyListener;
	if(userMouseListener 	) delete userMouseListener;
    
    // delete children
    if(container)
    {
        std::list<FlexiWidget *>::iterator it;
        for(it=children.begin(); it!=children.end(); it++)
            delete *(it);
        children.clear();
    }
}

/*! Sets the name of the widget
 *  @param newName The new name of the widget
 */
void FlexiWidget::setName(const std::string &newName)
{
    name = newName;
}

/*! Gets the name of the widget
 *  @return the name
 */
const std::string &FlexiWidget::getName() const
{ 
    return name;
}

/*! Gets the parent of the widget
 *  @return the parent
 */
FlexiWidget *FlexiWidget::getParent()
{ 
    return parent;
}

/*! Reparents the widget to another parent
 *  @param newparent the new parent widget
 *  @return true if success
 */
bool FlexiWidget::reparent(FlexiWidget *newParent)
{
    if(!newParent)
        return false;
    else
        parent = newParent;
    
    return true;
}

/*! Return if the widget is a container
 *  @return true if is a container
 */
bool FlexiWidget::isContainer()
{
    return container; 
}

/*! Add a child to the widget, if this widget is a container
 *  @param child the new child
 */
void FlexiWidget::addChild(FlexiWidget *child)
{
    if(container)
        children.push_back(child);
}

/*! Return the list of all children
 *  @return the list of all children
 */
const std::list<FlexiWidget *> FlexiWidget::getChildren() const
{
    return children;
}

/*! Gets the position of the widget
 *  @return the position
 */
const FlexiPosition &FlexiWidget::getPosition()
{ 
    return position;
}

/*! Gets the size of the widget
 *  @return the size
 */
const FlexiSize &FlexiWidget::getSize()
{ 
    return size;
}

/*! Gets the absolute position of the widget (not relative to parent)
 *  @return the absolute position on the screen
 */
const FlexiPosition &FlexiWidget::getAbsPosition()
{
    absolutePosition = (parent)?parent->getAbsPosition()+position : position;
    return absolutePosition;
}

/*! Gets the original position of the widget (without any translation)
 *  @return the original position
 */
const FlexiPosition &FlexiWidget::getOriginalPosition()
{ 
    return originalPosition; 
}

/*! Resize the widget
 *  @param p the new position
 *  @param s the new size
 */
void FlexiWidget::resize(const FlexiPosition &p, const FlexiSize &s)
{
    /*! @todo resize all children */
}

/*! Sets the widget's position
 *  @param p the new position
 */
void FlexiWidget::setPosition(const FlexiPosition &p)
{ 
    resize(p, getSize()); 
}

/*! Sets the widget's size
 *  @param s the new size
 */
void FlexiWidget::setSize(const FlexiSize &s)
{ 
    resize(getPosition(), s);
}

/*! Shows the widget
 */
void FlexiWidget::show()
{
	visible = true;
	activate();
	callActionListener( new FlexiActionEvent(FLX_EVENT_ACTION_SHOW) );
}

/*! Hides the widget 
 */
void FlexiWidget::hide()
{
	visible = false;
	deactivate();
	callActionListener( new FlexiActionEvent(FLX_EVENT_ACTION_HIDE) );
}

/*! Activate the widget
 */
void FlexiWidget::activate()
{
	active = true;
	callActionListener( new FlexiActionEvent(FLX_EVENT_ACTION_ACTIVATE) );
}

/*! Deactivate the widget
 */
void FlexiWidget::deactivate()
{
	active = false;
	callActionListener( new FlexiActionEvent(FLX_EVENT_ACTION_DEACTIVATE) );
}

/*! Returns if the widget is visible
 *  @return true if is visible
 */
bool FlexiWidget::isVisible()
{ 
    return visible;
}

/*! Returns if the widget is active
 *  @return true if is active
 */
bool FlexiWidget::isActive()
{
    return active;
}

/*! Set if a widget can receive focus
 *  @param focuseable true if the widget can get focused
 */
void FlexiWidget::setFocusable(bool focusable)
{
    this->focusable = focusable; 
}

/*! Sets the focus to the widget
 */
void FlexiWidget::setFocus() 
{
    focused = true;
}

/*! Gets if the widget can receive focus
 *  @return true if is focusable
 */
bool FlexiWidget::isFocusable() 
{
    return focusable; 
}

/*! Returns if the widget is focused
 *  @return true if the widget is focused
 */
bool FlexiWidget::isFocused() 
{
    return focused; 
}   

/*! Sets the widget hilight status
 *  @param hilight true if hilighted
 */
void FlexiWidget::setHilighted(bool hilight) 
{
    hilighted = hilight;
}

/*! Returns if the widget is hilighted
 *  @return true if hilighted
 */
bool FlexiWidget::isHilighted() 
{
    return hilighted; 
}

/*! Dispatch a focus event to all the children 
 *  @param event the focus event
 */
void FlexiWidget::dispatchFocusEvent(FlexiFocusEvent *event)
{
	FlexiWidget *widget;
	std::list<FlexiWidget *>::iterator it;

	// try to consume event with our elements
	for(it=children.begin(); it!=children.end() && !event->isConsumed(); it++)
	{
	    widget = *(it);
        if(!widget->isContainer())
			if(widget->isFocusable()) widget->callFocusListener(event);
    }

	// try to consume dispatching event to all containers childs
	for(it=children.begin(); it!=children.end() && !event->isConsumed(); it++)
	{
	    widget = *(it);
		if(widget->isContainer())
			widget->dispatchFocusEvent(event);
	}

	// consume event directly with ourself
	if(!event->isConsumed()) callFocusListener(event);
}

/*! Dispatch a mouse event to all the children
 *  @param event the mouse event
 */
void FlexiWidget::dispatchMouseEvent(FlexiMouseEvent *event)
{
	FlexiWidget *widget;
	std::list<FlexiWidget *>::iterator it;

	// try to consume event with our elements
	for(it=children.begin(); it!=children.end() && !event->isConsumed(); it++)
	{
	    widget = *(it);
        if(!widget->isContainer())
            if(widget->isMouseOver(event->getMouseX(), event->getMouseY()))
            {
                // highlight it
				widget->setHilighted(true);

				// send got focus
				if(event->getType() != FLX_EVENT_MOUSE_MOVE)
				{
					FlexiFocusEvent *fevent = new FlexiFocusEvent(FLX_EVENT_GOTFOCUS);
					widget->callFocusListener(fevent);
					if(fevent) delete fevent;
				}

				// send mouse event
				widget->callMouseListener(event);
            }
            else
                widget->setHilighted(false);
    }

	// try to consume dispatching event to all containers childs
	for(it=children.begin(); it!=children.end() && !event->isConsumed(); it++)
	{
	    widget = *(it);
		if(widget->isContainer())
			widget->dispatchMouseEvent(event);
	}

	// consume event directly with ourself
	if(!event->isConsumed() && isMouseOver(event->getMouseX(), event->getMouseY()))
    {
		// send got focus
		if(event->getType() != FLX_EVENT_MOUSE_MOVE)
		{
			FlexiFocusEvent *fevent = new FlexiFocusEvent(FLX_EVENT_GOTFOCUS);
			callFocusListener(fevent);
			if(fevent) delete fevent;
		}

		// send mouse event
		callMouseListener(event);
    }
}

/*! Sets the one or more flags of the widget 
 *  @param flags the flags to be set
 *  @param value true or false
 */
void FlexiWidget::setFlags(int flags, bool value)
{
	if(value)
		this->flags |= flags;
	else
		this->flags &= ~flags;
}

/*! Gets one or more flags of the widget
 *  @param flags the flags to be read
 *  @return flags status
 */
bool FlexiWidget::getFlags(int flags)
{
	return ((this->flags & flags) != 0);
}

/*! Sets the background image of the widget
 *  @param image the image
 *  @param gridBagType the type of gridbag to use
 *  @sa FlexiGridBag
 */
void FlexiWidget::setBackImage(FlexiImage *image, int gridBagType)
{
	 backImage = image;
	 gridBagType = gridBagType;
	 backColor.set(FLX_WHITE);
}

/*! Set the sensitive area of the widget
 *  @param sensitive_area the sensitive area
 *  @return true if success
 */
bool FlexiWidget::setSensitiveArea(FlexiSensitiveArea *sensitive_area)
{
	// check sensitive area pointer
	if(!sensitive_area) return false;

	// set element
	if(area) delete area;
	area = sensitive_area;

	return true;
}

/*! Tells if mouse is over the sensitive area of the widget
 *  @return true if the mouse is over
 */
bool FlexiWidget::isMouseOver(int mouseX, int mouseY)
{
	if(!area)
        return false;

	if(parent)
	{
	 	mouseX = mouseX - parent->getAbsPosition().x;
	 	mouseY = mouseY - parent->getAbsPosition().y;
	}

	return area->isMouseOver(mouseX, mouseY);
}

/*! Sets the widget's tag data
 *  @param value the tag
 */
void FlexiWidget::setTag(long value)
{
    tag = value;
}

/*! Gets the widget's tag data
 *  @return the tag
 */
long FlexiWidget::getTag()
{
    return tag; 
}

/*! Add a default action listener to the widget 
 *  @param listener an action listener
 */
void FlexiWidget::addActionListener(FlexiActionListener *listener)
{
	if(actionListener) delete actionListener;
	actionListener = listener;
}

/*! Add a default focus listener to the widget 
 *  @param listener a focus listener
 */
void FlexiWidget::addFocusListener(FlexiFocusListener *listener)
{
	if(focusListener) delete focusListener;
	focusListener = listener;
}

/*! Add a default key listener to the widget 
 *  @param listener a key listener
 */
void FlexiWidget::addKeyListener(FlexiKeyListener *listener)
{
	if(keyListener) delete keyListener;
	keyListener = listener;
}

/*! Add a default mouse listener to the widget 
 *  @param listener a mouse listener
 */
void FlexiWidget::addMouseListener(FlexiMouseListener *listener)
{
	if(mouseListener) delete mouseListener;
	mouseListener = listener;
}

/*! Add an user defined action listener to the widget 
 *  @param listener an action listener
 */
void FlexiWidget::addUserActionListener(FlexiActionListener *listener)
{
	if(userActionListener) delete userActionListener;
	userActionListener = listener;
}

/*! Add an user defined focus listener to the widget 
 *  @param listener a focus listener
 */
void FlexiWidget::addUserFocusListener(FlexiFocusListener *listener)
{
	if(userFocusListener) delete userFocusListener;
	userFocusListener = listener;
}

/*! Add an user defined key listener to the widget 
 *  @param listener a key listener
 */
void FlexiWidget::addUserKeyListener(FlexiKeyListener *listener)
{
	if(userKeyListener) delete userKeyListener;
	userKeyListener = listener;
}

/*! Add an user defined mouse listener to the widget 
 *  @param listener a mouse listener
 */
void FlexiWidget::addUserMouseListener(FlexiMouseListener *listener)
{
	if(userMouseListener) delete userMouseListener;
	userMouseListener = listener;
}

/*! Calls the associated action listener of this widget
 *  @param event an action event
 */
void FlexiWidget::callActionListener(FlexiActionEvent *event)
{
	// set event's source component
	event->setSource(this);

	// try to execute event's related code
	switch( event->getType() )
	{
	case FLX_EVENT_ACTION_ACTIVATE:
		if(actionListener) actionListener->onActivate(event);
		if(userActionListener) userActionListener->onActivate(event);
		break;

	case FLX_EVENT_ACTION_DEACTIVATE:
		if(actionListener) actionListener->onDeActivate(event);
		if(userActionListener) userActionListener->onDeActivate(event);
		break;

	case FLX_EVENT_ACTION_SHOW:
		if(actionListener) actionListener->onShow(event);
		if(userActionListener) userActionListener->onShow(event);
		break;

	case FLX_EVENT_ACTION_HIDE:
		if(actionListener) actionListener->onHide(event);
		if(userActionListener) userActionListener->onHide(event);
		break;

	case FLX_EVENT_ACTION_VALUECHANGE:
		if(actionListener) actionListener->onValueChange(event);
		if(userActionListener) userActionListener->onValueChange(event);
		break;

	case FLX_EVENT_ACTION_DONE:
		if(actionListener) actionListener->onDone(event);
		if(userActionListener) userActionListener->onDone(event);
		break;
	}

	// delete event (internal use only)
	if(event) delete event;
}

/*! Calls the associated focus listener of this widget
 *  @param event a focus event
 */
void FlexiWidget::callFocusListener(FlexiFocusEvent *event)
{
	// check active
	if(!active) return;

	// set event's source component
	event->setSource(this);

	// try to execute event's related code
	switch( event->getType() )
	{
	case FLX_EVENT_GOTFOCUS:
		if(focusListener) focusListener->onFocus(event);
		if(userFocusListener) userFocusListener->onFocus(event);
		focused = true;
		break;

	case FLX_EVENT_LOSTFOCUS:
		if(focusListener) focusListener->onLostFocus(event);
		if(userFocusListener) userFocusListener->onLostFocus(event);
		focused = false;
		break;

	case FLX_EVENT_MOUSEIN:
		if(focusListener) focusListener->onMouseIn(event);
		if(userFocusListener) userFocusListener->onMouseIn(event);
		break;

	case FLX_EVENT_MOUSEOUT:
		if(focusListener) focusListener->onMouseOut(event);
		if(userFocusListener) userFocusListener->onMouseOut(event);
		break;
	}

	// consume event
	event->consume();
}

/*! Calls the associated key listener of this widget
 *  @param event a key event
 */
void FlexiWidget::callKeyListener(FlexiKeyEvent *event)
{
	// check active
	if(!active) return;

	// set event's source component
	event->setSource(this);

	// try to execute event's related code
	switch( event->getType() )
	{
	case FLX_EVENT_KEY_DOWN:
		if(keyListener) keyListener->onKeyDown(event);
		if(userKeyListener) userKeyListener->onKeyDown(event);
		break;

	case FLX_EVENT_KEY_UP:
		if(keyListener) keyListener->onKeyUp(event);
		if(userKeyListener) userKeyListener->onKeyUp(event);
		break;

	case FLX_EVENT_PRESS:
		if(keyListener) keyListener->onKeyPress(event);
		if(userKeyListener) userKeyListener->onKeyPress(event);
		break;
	}

	// consume event
	event->consume();
}

/*! Calls the associated mouse listener of this widget
 *  @param event a mouse event
 */
void FlexiWidget::callMouseListener(FlexiMouseEvent *event)
{
	// check active
	if(!active) return;

	// set event's source component
	event->setSource(this);

	// try to execute event's related code
	switch( event->getType() )
	{
	case FLX_EVENT_MOUSE_CLICK:
		if(mouseListener) mouseListener->onClick(event);
		if(userMouseListener) userMouseListener->onClick(event);
   		break;

	case FLX_EVENT_MOUSE_DRAG:
   		if(mouseListener) mouseListener->onDrag(event);
   		if(userMouseListener) userMouseListener->onDrag(event);
   		break;

	case FLX_EVENT_MOUSE_RELEASE:
   		if(mouseListener) mouseListener->onRelease(event);
   		if(userMouseListener) userMouseListener->onRelease(event);
   		break;

	case FLX_EVENT_MOUSE_MOVE:
   		if(mouseListener) mouseListener->onMove(event);
   		if(userMouseListener) userMouseListener->onMove(event);
   		break;

	case FLX_EVENT_MOUSE_WHEEL:
   		if(mouseListener) mouseListener->onWheelMove(event);
   		if(userMouseListener) userMouseListener->onWheelMove(event);
   		break;
	}

	// consume event
	event->consume();
}

/*! Paint the widget
 */
void FlexiWidget::paint()
{
    // paint children
    if(container)
    {        
        std::list<FlexiWidget *>::iterator it;
        for(it=children.begin(); it!=children.end(); it++)
        {
            FlexiWidget *w = *(it);
            w->paint();
        }
    }
}

