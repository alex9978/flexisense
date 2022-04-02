
#include <string>

#include <FlexiSense/FlexiManager.h>
#include <FlexiSense/FlexiGui.h>
#include <FlexiSense/common/FlexiLog.h>

static FlexiManager defaultManager;

FlexiManager::FlexiManager()
{
	initialized = false;
}

FlexiManager::~FlexiManager()
{
}

FlexiManager *FlexiManager::instance()
{
	return &defaultManager;
}

bool FlexiManager::initialize(FlexiGfxRenderer *gr)
{
	FT_Int maj, min, pat;

    // logger
    FlexiLog::instance()->initialize();

    // set renderer
    gfxRenderer = gr;

    // resource manager
    resourceManager = new FlexiResourceManager();

	FLX_LOG(1, "FlexiManager::initialize()");
	if(!loadConfig("FlexiSense.cfg"))
	{
		// default config values
		imagePath			= "images/";
		fontPath			= "fonts/";
		resourcePath		= "resources/";
		propertyPath		= "resources/properties/";
		themePath			= "themes/";
		themeFile			= "default";
		eventMode			= FLX_ENQUEUED_EVENTS;
		mouseSpeed			= 2;

		// load default theme
		if(!theme.load(themeFile.c_str()))
            FLX_LOG(1, "FlexiManager.initialize() - Error in theme loading.");
	}

	// initialize freetype
	if(FT_Init_FreeType( &ftLib ))
		FLX_LOG(1, "ERROR: an error occurred during FreeType library initialization");
	else
	{
		FT_Library_Version(ftLib, &maj, &min, &pat);
		FLX_LOG(1, "FlexiManager: FreeType library v%i.%i.%i initialization done", maj, min, pat);
	}

	// initialize openil
	ilInit();

	gridBag1x1.setType(FlexiGridBag::FLX_GRIDBAG_1X1);
	gridBag1x3.setType(FlexiGridBag::FLX_GRIDBAG_1X3);
	gridBag3x1.setType(FlexiGridBag::FLX_GRIDBAG_3X1);
	gridBag3x3.setType(FlexiGridBag::FLX_GRIDBAG_3X3);
	
	currentInterface	= 0;
 	defaultFont	 		= new FlexiFont((std::string)"vera.ttf");
    if(FLX_THEME.wallpaper)
    {
        defaultWallpaper    = new FlexiBox(FlexiPosition(0,0), FlexiSize(gr->getScreenSize().width, gr->getScreenSize().height), 0);
        defaultWallpaper->setBackImage( FLX_THEME.wallpaper );
    }   
	defaultPointer		= new FlexiBox(FlexiPosition(0,0), FlexiSize(32,32), 0);
	defaultPointer->setBackImage( FLX_THEME.pointer );

    showFps			 	= false;
	fpsTimer		 	= new FlexiTimer();
	framesDrawed	 	= 0;
	lblFps			 	= new FlexiLabel(FlexiPosition(10, 10), FlexiSize(150, 20), "fps", FLX_ALIGN_INLEFT, 0, 12, 0, 0);
	lblFps->foreColor.set(0xffffffff);
	lblFps->setShadow(true);

	initialized = true;
	return true;
}

void FlexiManager::update()
{
	if(eventMode == FLX_ENQUEUED_EVENTS)
		dequeueEvents();

	if(currentInterface)
		currentInterface->update();
}

void FlexiManager::paint()
{    
	// begin
	gfxRenderer->begin();

    // wallpaper
    if(defaultWallpaper)
        defaultWallpaper->paint();
    
	// draw current interface
	if(currentInterface) currentInterface->paint();

	//if(defaultConsole) defaultConsole->paint();

	// draw dialogs
/*	if(inputDialog) inputDialog->paint();*/

	// draw fps
	if(showFps && lblFps)
	{
        if(fpsTimer->getSeconds() >= 1.0f)
        {
            std::string fpsstr;
            char fpsbuf[30];
            //
            sprintf(fpsbuf, "%i fps", framesDrawed);
            fpsstr = fpsbuf;
            lblFps->setCaption(fpsstr);
            framesDrawed = 0;
            fpsTimer->reset();
        }   		
		lblFps->paint();
	}

/*
	// draw console
	if(defaultConsole) defaultConsole->paint();

	// draw logos
	if(showLogos)
	{
		if(logoEmthesis) logoEmthesis->paint();
		if(logoSharpwave) logoSharpwave->paint();
	}
*/

	// draw pointer (must be last thing drawed..)
    if(defaultPointer)
        defaultPointer->paint();
/*
	// transition
	if(trans && trans->isStarted() && !trans->isDone())
		trans->paint();*/

	// end
	gfxRenderer->end();

	// increment frames drawed counter
	framesDrawed++;
}

bool FlexiManager::shutdown()
{
	FLX_LOG(1, "FlexiManager::shutdown()");

//	saveConfig("FlexiSense.cfg");

	// delete fps text
	if(lblFps) delete lblFps;

	// delete font
	if(defaultFont) delete defaultFont;

	// delete pointer
	if(defaultPointer) delete defaultPointer;

	// delete console
/*	if(defaultConsole) delete defaultConsole;

	// delete logos
	if(logoEmthesis) delete logoEmthesis;
	if(logoSharpwave) delete logoSharpwave;*/

	// delete commands queue
	commands.clear();

	// delete plug-ins
	if(gfxRenderer) delete gfxRenderer;

	// delete fps related things
	if(fpsTimer) delete fpsTimer;

	// delete transition
//	if(trans) delete trans;

	// delete interfaces
    std::list<FlexiGui *>::iterator it;
	for(it=interfaces.begin(); it!=interfaces.end(); it++)
        delete *(it);
	interfaces.clear();

	// shutdown openil
	ilShutDown();

	// shutdown freetype
	FT_Done_FreeType(ftLib);

    // res
    if(resourceManager) delete resourceManager;

    // shutdown logger
    FlexiLog::instance()->shutdown();

	return true;
}

bool FlexiManager::setEventMode(int mode)
{
	switch(mode)
	{
	case FLX_ENQUEUED_EVENTS:
	case FLX_THREADED_EVENTS:
		eventMode = mode;
		return true;
    default:
        return false;
	}	
}

void FlexiManager::produceNewEvent(int type, int keyCode, int keyAscii, int modifiers, float mouseX, float mouseY, int mouseButtons, int mouseWheel)
{
	FlexiEventParam *ep = new FlexiEventParam(type, keyCode, keyAscii, modifiers, mouseX, mouseY, mouseButtons, mouseWheel);
//	long threadId = 0;

	switch(eventMode)
	{
	case FLX_ENQUEUED_EVENTS:
		enqueueEvent(ep);
		break;

	case FLX_THREADED_EVENTS:
		//CreateThread(NULL, 0, FlexiEventThreadFunction, (void *)ep, 0, (DWORD *)&threadId);
		break;
	}
}

bool FlexiManager::addInterface(FlexiGui *gui)
{
    if(gui)
    {
        interfaces.push_back(gui);
        gui->init();
        gui->loadProperties();
        if(!currentInterface)
            setCurrentInterface(gui);
        return true;
    }
    else
        return false;
}

void FlexiManager::deleteInterface(std::string &name)
{
    FlexiGui *interface = 0;
    std::list<FlexiGui *>::iterator it;
	for(it=interfaces.begin(); it!=interfaces.end(); it++)
	{
        interface = *(it);
        if(interface->name == name)
        {
            delete *(it);
            return;
        }
	}
}

void FlexiManager::setCurrentInterface(FlexiGui *gui)
{
    if(gui)
        currentInterface = gui;
}
/*
void FlexiManager::setTransition(FlexiTransition *transition)
{
	if(trans) delete trans;
	trans = transition;
}

void FlexiManager::startTransition(FlexiSense *toInterface)
{
	if(trans && !trans->isStarted())
	{
		trans->setInterfaces(currentInterface, toInterface);
		trans->start();
	}
}

SWbool FlexiManager::isTransitionDone()
{
	if(trans) return trans->isDone();
	return SW_TRUE;
}

void FlexiManager::conOut(const char *format_string, ...)
{
	char buffer[FLX_CONSOLE_MAXLINECHARS];
	va_list vlist;

	va_start(vlist, format_string);
	vsprintf(buffer, format_string, vlist);
	va_end(vlist);

	if(defaultConsole)
		defaultConsole->out("%s", buffer);
}
*/
void FlexiManager::forceRatioUpdate()
{
/*    std::list<FlexiGui *>::iterator it;
	for(it=interfaces.begin(); it!=interfaces.end(); it++)
	{
        interface = *(it);
        if(interface->name == name)
        {
            delete *(it);
            return;
        }
	}

	for(int i=0; i<interfaces.NumElems(); i++)
		for(int j=0; j<interfaces[i]->containers.NumElems(); j++)
			interfaces[i]->containers[j]->forceSizeUpdate();*/
}

void FlexiManager::generateKeyEvent(int type, int keycode, unsigned char keyascii, int modifiers, long event_id)
{
	// check current interface
	if(!currentInterface)
		return;

    // create event
	FlexiKeyEvent *event = new FlexiKeyEvent(type, keycode, keyascii, modifiers, event_id);

	// check if there is a wrapped listener
    // else check if a component is focused
	if(currentInterface->wrappedKeyListener)
		currentInterface->callWrappedKeyListener(event);
	else if(currentInterface->focusedComponent)
		currentInterface->focusedComponent->callKeyListener(event);

	// delete event
	if(event) delete event;
}

void FlexiManager::generateMouseEvent(int type, float mouseX, float mouseY, int mouseButtons, int mouseWheel, long event_id)
{
	// move pointer
    if(defaultPointer)
        defaultPointer->setPosition(FlexiPosition(mouseX/getHRatio(), mouseY/getVRatio()));

 	// check current interface
	if(!currentInterface)
		return;

	// create event
	FlexiMouseEvent *event = new FlexiMouseEvent(type, mouseX/getHRatio(), mouseY/getVRatio(), mouseButtons, mouseWheel, event_id);
	event->setSource(currentInterface);

	// check dialogs
	/*if(inputDialog)
	{
		inputDialog->dispatchMouseEvent(event);
	}
	else*/
	{
		// dispatch to all containers
		FlexiWidget *w;
        std::list<FlexiWidget *>::iterator it;
        for(it=currentInterface->widgets.begin(); it!=currentInterface->widgets.end(); it++)
        {
            w = *(it);
            if(w->isContainer())
                w->dispatchMouseEvent(event);
        }
	}

	if(type != FLX_EVENT_MOUSE_MOVE)
	{
		// send lost focus to last focused element
		if( event->isConsumed() &&
			currentInterface->focusedComponent &&
			currentInterface->focusedComponent != event->getSource() )
		{
			FlexiFocusEvent *fevent = new FlexiFocusEvent(FLX_EVENT_LOSTFOCUS);
			currentInterface->focusedComponent->callFocusListener(fevent);
			if(fevent) delete fevent;
		}

		// get focused element
		currentInterface->focusedComponent = (FlexiWidget *)event->getSource();
	}
	else
	{
		// send mouse out to last rollovered component
		if( event->isConsumed() &&
			currentInterface->rolloveredComponent &&
			currentInterface->rolloveredComponent != event->getSource() )
		{
			FlexiFocusEvent *fevent = new FlexiFocusEvent(FLX_EVENT_MOUSEOUT);
			currentInterface->rolloveredComponent->callFocusListener(fevent);
			if(fevent) delete fevent;
		}

		// get rollovered component and send mouse in
		if( event->isConsumed() &&
			currentInterface->rolloveredComponent != event->getSource() )
		{
			currentInterface->rolloveredComponent = (FlexiWidget *) event->getSource();
			FlexiFocusEvent *fevent = new FlexiFocusEvent(FLX_EVENT_MOUSEIN);
			currentInterface->rolloveredComponent->callFocusListener(fevent);
			if(fevent) delete fevent;
		}
	}

	// delete event
	if(event) delete event;
}

float FlexiManager::getHRatio()
{
/*	if(gfxRenderer)
        return gfxRenderer->getScreenHorizontalRatio();
    else*/
        return 1.0f;
}

float FlexiManager::getVRatio()
{
/*	if(gfxRenderer)
        return gfxRenderer->getScreenVerticalRatio();
    else*/
        return 1.0f;
}

FlexiCommand *FlexiManager::getCommand()
{
    FlexiCommand *cmd;
    std::list<FlexiCommand *>::iterator it;
	it=commands.begin();
	if(it!=commands.end())
	{
        cmd = *(it);
        delete *(it);
        return cmd;
	}
	else
        return 0;
}

void FlexiManager::sendCommand(int ioCommand, int params)
{
	// create new command
	FlexiCommand *cmd = new FlexiCommand(ioCommand, params);
	// append to command list
	if(cmd)
		commands.push_back(cmd);
}

/*int FlexiManager::showInputDialog(char *caption, char *description, char *defaultText, char **returnText)
{
	inputDialog = new FlexiInputDialog(caption, description, defaultText);
	if(!inputDialog) return FLX_CANCEL;

	// copy instance pointer
	FlexiInputDialog *tempDialog = inputDialog;
	*returnText = 0;

	// focus input
	currentInterface->focusedComponent = inputDialog->input;
	FlexiFocusEvent *fevent = new FlexiFocusEvent(FLX_EVENT_GOTFOCUS);
	currentInterface->focusedComponent->callFocusListener(fevent);
	if(fevent) delete fevent;

	// loop
	while( !inputDialog->isDone() )
	{
		Sleep(100);
	}

	// get response and evaluate it
	int response = inputDialog->getResponse();
	if(response == FLX_OK)
		*returnText = inputDialog->getText().GetStr();

	// free resources
	inputDialog	= 0;
	currentInterface->focusedComponent = 0;
	currentInterface->rolloveredComponent = 0;
	Sleep(100);
	delete tempDialog;

	return response;
}*/

bool FlexiManager::loadConfig(const char *filename)
{
/*	char buffer[512];
	FILE *f = fopen(filename, "rt");
	if(f)
	{
		fscanf(f, "\n[paths]\n");
		fscanf(f, "ImagePath=%s\n", &buffer);		imagePath = buffer;		// load image path
		fscanf(f, "FontPath=%s\n", &buffer);		fontPath = buffer;		// load font path
		fscanf(f, "ResourcePath=%s\n", &buffer);	resourcePath = buffer;	// load resources path
		fscanf(f, "PropertyPath=%s\n", &buffer);	propertyPath = buffer;	// load properties path
		fscanf(f, "ThemePath=%s\n", &buffer);		themePath = buffer;		// load themes path

		fscanf(f, "\n[theme]\n");
		fscanf(f, "ThemeFile=%s\n", &buffer);		themeFile = buffer;		// load theme file

		fscanf(f, "\n[events]\n");
		fscanf(f, "ThreadedEvents=%i\n", &eventMode);						// load event mode

		//close file
		fclose(f);

		// load theme
		if(themeFile != "")
			theme.load(themeFile);

		return true;
	}*/
	return false;
}

bool FlexiManager::saveConfig(const char *filename)
{
/*	FILE *f = fopen(filename, "wt");
	if(f)
	{
		fprintf(f, "\n[paths]\n");
		fprintf(f, "ImagePath=%s\n", imagePath.GetStr());			// save image path
		fprintf(f, "FontPath=%s\n", fontPath.GetStr());				// save font path
		fprintf(f, "ResourcePath=%s\n", resourcePath.GetStr());		// save resource path
		fprintf(f, "PropertyPath=%s\n", propertyPath.GetStr());		// save property path
		fprintf(f, "ThemePath=%s\n", themePath.GetStr());			// save theme path

		fprintf(f, "\n[theme]\n");
		fprintf(f, "ThemeFile=%s\n", themeFile.GetStr());			// theme file

		fprintf(f, "\n[events]\n");
		fprintf(f, "ThreadedEvents=%i\n", eventMode);				// save event mode

		fclose(f);
		return true;
	}*/
	return false;
}

void FlexiManager::enqueueEvent(FlexiEventParam *param)
{
	eventsQueue.push_back(param);
}

void FlexiManager::dequeueEvents()
{
	FlexiEventParam *ep;
    std::list<FlexiEventParam *>::iterator it;
	for(it=eventsQueue.begin(); it!=eventsQueue.end(); it++)
	{
		ep = *(it);

		// execute event function
		switch(ep->type)
		{
		case FLX_EVENT_PRESS:
            FlexiManager::instance()->generateKeyEvent(FLX_EVENT_PRESS, ep->keyCode, ep->keyAscii, ep->modifiers);
            break;
		case FLX_EVENT_KEY_DOWN:
            FlexiManager::instance()->generateKeyEvent(FLX_EVENT_KEY_DOWN, ep->keyCode, '\0', ep->modifiers);
            break;
		case FLX_EVENT_KEY_UP:
            FlexiManager::instance()->generateKeyEvent(FLX_EVENT_KEY_UP, ep->keyCode, '\0', ep->modifiers);
            break;
		case FLX_EVENT_MOUSE_DRAG:		
            FlexiManager::instance()->generateMouseEvent(FLX_EVENT_MOUSE_DRAG, ep->mouseX, ep->mouseY, ep->mouseButtons, ep->mouseWheel);
            break;
		case FLX_EVENT_MOUSE_MOVE:		
            FlexiManager::instance()->generateMouseEvent(FLX_EVENT_MOUSE_MOVE, ep->mouseX, ep->mouseY, 0, ep->mouseWheel);
            break;
		case FLX_EVENT_MOUSE_CLICK:		
            FlexiManager::instance()->generateMouseEvent(FLX_EVENT_MOUSE_CLICK, ep->mouseX, ep->mouseY, ep->mouseButtons, ep->mouseWheel);
            break;
		case FLX_EVENT_MOUSE_RELEASE:	
            FlexiManager::instance()->generateMouseEvent(FLX_EVENT_MOUSE_RELEASE, ep->mouseX, ep->mouseY, ep->mouseButtons, ep->mouseWheel);
            break;
		}

		// delete parameter
		delete *(it);
	}
	eventsQueue.clear();
}

/*DWORD WINAPI FlexiManager::FlexiEventThreadFunction(void *p)
{
	// cast the parameter passed
	FlexiEventParam *tp = (FlexiEventParam *) p;

	// execute event function
	switch(tp->type)
	{
	case FLX_EVENT_PRESS:			FlexiManager::instance()->generateKeyEvent(FLX_EVENT_PRESS,		   tp->keyCode, tp->keyAscii, 0);					break;
	case FLX_EVENT_KEY_DOWN:		FlexiManager::instance()->generateKeyEvent(FLX_EVENT_KEY_DOWN,		   tp->keyCode, '\0', 0);							break;
	case FLX_EVENT_KEY_UP:			FlexiManager::instance()->generateKeyEvent(FLX_EVENT_KEY_UP,		   tp->keyCode, '\0', 0);							break;
	case FLX_EVENT_MOUSE_DRAG:		FlexiManager::instance()->generateMouseEvent(FLX_EVENT_MOUSE_DRAG,	   tp->mouseX, tp->mouseY, tp->mouseButtons, 0);	break;
	case FLX_EVENT_MOUSE_MOVE:		FlexiManager::instance()->generateMouseEvent(FLX_EVENT_MOUSE_MOVE,	   tp->mouseX, tp->mouseY, 0, 0);					break;
	case FLX_EVENT_MOUSE_CLICK:		FlexiManager::instance()->generateMouseEvent(FLX_EVENT_MOUSE_CLICK,   tp->mouseX, tp->mouseY, tp->mouseButtons, 0);	break;
	case FLX_EVENT_MOUSE_RELEASE:	FlexiManager::instance()->generateMouseEvent(FLX_EVENT_MOUSE_RELEASE, tp->mouseX, tp->mouseY, tp->mouseButtons, 0);	break;
	}

	// delete parameter
	if(tp) delete tp;

	// exit thread
	ExitThread(0);
	return 0;
}*/
