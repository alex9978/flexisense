
/*! @class FlexiManager
 *  @brief Class that manage the FlexiSense engine
 *  @author Alessandro Rasulo (mailto: alex9978@gmail.com)
 */

#ifndef FLEXIMANAGER_H
#define FLEXIMANAGER_H

// freetype
#include <ft2build.h>
#include FT_FREETYPE_H

// openil
#include <IL/il.h>

// common
#include <FlexiSense/common/FlexiCatalog.h>
#include <FlexiSense/common/FlexiColor.h>
#include <FlexiSense/common/FlexiCommand.h>
#include <FlexiSense/common/FlexiEventParam.h>
#include <FlexiSense/common/FlexiFont.h>
#include <FlexiSense/common/FlexiGridBag.h>
#include <FlexiSense/common/FlexiImage.h>
#include <FlexiSense/common/FlexiTheme.h>
#include <FlexiSense/common/FlexiTimer.h>
#include <FlexiSense/common/FlexiUtility.h>

// listeners
#include <FlexiSense/listeners/FlexiKeyListener.h>

// widgets
#include <FlexiSense/widgets/FlexiBox.h>
#include <FlexiSense/widgets/FlexiButton.h>
#include <FlexiSense/widgets/FlexiLabel.h>
#include <FlexiSense/widgets/FlexiWindow.h>
/*
#include <Button/Boolean/FlexiBoolean.h>
#include <Button/CycleButton/FlexiCycleButton.h>
#include <Button/LabelButton/FlexiLabelButton.h>
#include <Button/CycleLabelButton/FlexiCycleLabelButton.h>
#include <Console/FlexiConsole.h>
#include <Group/FlexiGroup.h>
#include <Input/FlexiInput.h>
#include <Line/FlexiLine.h>
#include <List/FlexiList.h>
#include <ProgressBar/FlexiProgressBar.h>
#include <Valuator/PowerBar/FlexiPowerBar.h>
#include <Valuator/ScrollBar/FlexiScrollBar.h>
#include <Window/Screen/FlexiScreen.h>
 */

#include <FlexiSense/FlexiGfxRenderer.h>
#include <FlexiSense/FlexiResourceManager.h>

#include <list>

// event mode
#define FLX_ENQUEUED_EVENTS		0
#define FLX_THREADED_EVENTS		1

class FlexiGui;

class FLX_EXPORT FlexiManager
{
public:
	FlexiManager();
	virtual ~FlexiManager();

	// Static instance
	static FlexiManager *instance();

	// Main methods
	bool initialize			    (FlexiGfxRenderer *gr=0);
	void update					();
	void paint					();
	virtual bool shutdown		();
	bool isInitialized	    	() { return initialized; }

	// Events
	bool setEventMode			(int mode);
	void produceNewEvent		(int type, int keyCode, int keyAscii, int modifiers, float mouseX, float mouseY, int mouseButtons, int mouseWheel);

	// Interfaces
	bool addInterface			(FlexiGui *gui);
	void deleteInterface		(std::string &name);
	void setCurrentInterface	(FlexiGui *gui);
	FlexiGui *getCurrentInterface() { return currentInterface; }

	// Screen ratios
	float getHRatio             ();
	float getVRatio             ();
	void forceRatioUpdate		();

	// I/O commands (interface to game loop)
	FlexiCommand *getCommand	();
	void sendCommand			(int ioCommand, int params = 0);

	// Mouse Pointer
	void showPointer			() { defaultPointer->show(); }
	void hidePointer			() { defaultPointer->hide(); }
	bool isPointerVisible		() { return defaultPointer->isVisible(); }

    // On screen informations
	void showFPS				(bool enable) { showFps = enable; }

	// Default elements
	FlexiFont *getDefaultFont	() { return defaultFont; }

    // Renderer
    FlexiGfxRenderer *getRenderer() { return gfxRenderer; }

    // Resource manager
    FlexiResourceManager *getResourceManager() { return resourceManager; }
    
	// Theme
	FlexiTheme					 theme;
	FlexiGridBag				 gridBag1x1;
	FlexiGridBag				 gridBag1x3;
	FlexiGridBag				 gridBag3x1;
	FlexiGridBag				 gridBag3x3;

	// Configuration variables
	std::string					 fontPath;
	std::string					 resourcePath;
	std::string					 imagePath;
	std::string					 propertyPath;
	std::string					 themePath;
	std::string					 themeFile;
	int     					 eventMode;
	std::string                  mouseSpeed;

    // Misc
    FT_Library getFreeType      () { return ftLib; }

private:
    
    // FreeType 2
	FT_Library					 ftLib;

	// Configuration
	bool loadConfig			    (const char *filename);
	bool saveConfig			    (const char *filename);

	// Events
	void enqueueEvent			(FlexiEventParam *param);
	void dequeueEvents			();
	void generateKeyEvent		(int type, int keycode, unsigned char keyascii, int modifiers, long event_id = 0);
 	void generateMouseEvent		(int type, float mouseX, float mouseY, int mouseButtons, int mouseWheel, long event_id = 0);
	std::list<FlexiEventParam *> eventsQueue;

	// Event thread
	//static DWORD WINAPI FlexiEventThreadFunction(void *p);

	// Interfaces
	std::list<FlexiGui *>		 interfaces;
	FlexiGui					*currentInterface;

	// Default elements
	FlexiFont					*defaultFont;
	FlexiBox					*defaultWallpaper,
                                *defaultPointer;

    // Graphics renderer
	FlexiGfxRenderer			*gfxRenderer;

    // Resource manager
    FlexiResourceManager        *resourceManager;

	// I/O Commands
	std::list<FlexiCommand *>	 commands;

	// On screen informations: PFS
	FlexiTimer					*fpsTimer;
	FlexiLabel					*lblFps;	
	int 						 framesDrawed;
	bool						 showFps;

	// Misc
	bool						 initialized;
};

#endif
