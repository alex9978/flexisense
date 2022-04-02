
#include <FlexiSense/listeners/DefaultButtonListeners.h>

// Default mouse listenener

void ButtonMouseListener::onClick(FlexiMouseEvent *event)
{
	FlexiButton *btn = (FlexiButton *) event->getSource();
	btn->setPressedState(true);
}

void ButtonMouseListener::onRelease(FlexiMouseEvent *event)
{
	FlexiButton *btn = (FlexiButton *) event->getSource();
	btn->setPressedState(false);
}

// Default focus listenener

void ButtonFocusListener::onLostFocus(FlexiFocusEvent *event)
{
	FlexiButton *btn = (FlexiButton *) event->getSource();
	btn->setPressedState(false);
}

// Default key listenener

void ButtonKeyListener::onKeyDown(FlexiKeyEvent *event)
{
	FlexiButton *btn = (FlexiButton *) event->getSource();
	btn->setPressedState(true);
}

void ButtonKeyListener::onKeyUp(FlexiKeyEvent *event)
{
	FlexiButton *btn = (FlexiButton *) event->getSource();
	btn->setPressedState(false);
}

