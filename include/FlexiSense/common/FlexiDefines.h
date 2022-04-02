/*
-------------------------------------------------------------------------------------
This source file is part of the FlexiSense GUI
For the latest info, see http://flexisense.sourceforge.net/

Copyright (c) 2003-2008 Alessandro Rasulo (mailto: alex9978@gmail.com)

FlexiSense is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 3 of the License, or (at your option) any later
version.

FlexiSense is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
FlexiSense; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.

-------------------------------------------------------------------------------------
*/

/*! \mainpage FlexiSense
 *  \author Alessandro Rasulo (mailto: alex9978@gmail.com)
 *  \date 2003-2008
 *  \version 0.1
 *  \image html logo_small.png
 *
 *  \section sec_desc Intro
 *  FlexiSense is a free GUI library, for the creation of user interfaces\n
 *  for games or other applications. The library is object orientated, written in C++,\n
 *  cross-platform and free renderer, provides transition and motion effects.\n
 *  It support themes.
 */

#ifndef FLEXIDEFINES_H
#define	FLEXIDEFINES_H

/*! Alias */
#define FLX_LOG                 FlexiLog::instance()->log

#define FLX_HRATIO				FlexiManager::instance()->getHRatio
#define FLX_VRATIO				FlexiManager::instance()->getVRatio

//#define FLX_CREATEIMAGE         FlexiManager::instance()->getRenderer()->createImage
#define FLX_LOADIMAGE           FlexiManager::instance()->getRenderer()->loadImage

#define FLX_THEME				FlexiManager::instance()->theme
#define FLX_BACKGROUND		    FlexiManager::instance()->theme.background
#define FLX_FOREGROUND		    FlexiManager::instance()->theme.foreground

#define FLX_GB1X1				FlexiManager::instance()->gridBag1x1
#define FLX_GB1X3				FlexiManager::instance()->gridBag1x3
#define FLX_GB3X1				FlexiManager::instance()->gridBag3x1
#define FLX_GB3X3				FlexiManager::instance()->gridBag3x3

//#define FLX_CONOUT				FlexiManager::instance()->conOut
//#define FLX_CONVISIBLE			FlexiManager::instance()->isConVisible

/*! Resources */
#define FLX_RES_LANGUAGE	0
#define FLX_RES_GAMENAME	1
#define FLX_RES_OK			2
#define FLX_RES_CANCEL		3

/*! Responses */
#define FLX_OK				0
#define FLX_CANCEL			1

/*! Box types */
#define FLX_BOX_FLAT		1
#define FLX_BOX_3D			2
#define FLX_BOX_INV3D		3

/*! Alignments */
#define FLX_ALIGN_INNER		0x0001
#define FLX_ALIGN_OUTER		0x0002
#define FLX_ALIGN_LEFT		0x0004
#define FLX_ALIGN_CENTER	0x0008
#define FLX_ALIGN_RIGHT		0x0010
#define FLX_ALIGN_TOP		0x0020
#define FLX_ALIGN_BOTTOM	0x0040

#define FLX_ALIGN_IN		FLX_ALIGN_INNER|FLX_ALIGN_CENTER
#define FLX_ALIGN_INLEFT	FLX_ALIGN_INNER|FLX_ALIGN_LEFT
#define FLX_ALIGN_INRIGHT	FLX_ALIGN_INNER|FLX_ALIGN_RIGHT
#define FLX_ALIGN_UP		FLX_ALIGN_OUTER|FLX_ALIGN_CENTER|FLX_ALIGN_TOP
#define FLX_ALIGN_UPLEFT	FLX_ALIGN_OUTER|FLX_ALIGN_LEFT|FLX_ALIGN_TOP
#define FLX_ALIGN_UPRIGHT	FLX_ALIGN_OUTER|FLX_ALIGN_RIGHT|FLX_ALIGN_TOP
#define FLX_ALIGN_DN		FLX_ALIGN_OUTER|FLX_ALIGN_CENTER|FLX_ALIGN_BOTTOM
#define FLX_ALIGN_DNLEFT	FLX_ALIGN_OUTER|FLX_ALIGN_LEFT|FLX_ALIGN_BOTTOM
#define FLX_ALIGN_DNRIGHT	FLX_ALIGN_OUTER|FLX_ALIGN_RIGHT|FLX_ALIGN_BOTTOM
#define FLX_ALIGN_OUTLEFT	FLX_ALIGN_OUTER|FLX_ALIGN_LEFT
#define FLX_ALIGN_OUTRIGHT	FLX_ALIGN_OUTER|FLX_ALIGN_RIGHT

/*! Orientations */
#define FLX_HORIZONTAL		1
#define FLX_VERTICAL		2

/*! Flags */
#define FLX_MULTILINE		0x0001
#define FLX_WORDWRAP		0x0002
#define FLX_NOBORDER		0x0004
#define FLX_TRASPARENT		0x0008

#define FLX_ON				true
#define FLX_OFF				false

/*! Limits */
//#define FLX_MAX_LABEL_LEN	1024

/*! Keys constants */
enum FLX_KEYS
{
	KEY_ESCAPE		= 1,
	KEY_1			= 2,
	KEY_2			= 3,
	KEY_3			= 4,
	KEY_4			= 5,
	KEY_5			= 6,
	KEY_6			= 7,
	KEY_7			= 8,
	KEY_8			= 9,
	KEY_9			= 10,
	KEY_0			= 11,
	KEY_MINUS		= 12,
	KEY_EQUALS		= 13,
	KEY_BACKSPACE	= 14,
	KEY_TAB 		= 15,
	KEY_Q			= 16,
	KEY_W			= 17,
	KEY_E			= 18,
	KEY_R			= 19,
	KEY_T			= 20,
	KEY_Y			= 21,
	KEY_U			= 22,
	KEY_I			= 23,
	KEY_O			= 24,
	KEY_P			= 25,
	KEY_LEFTBRACKET	= 26,
	KEY_RIGHTBRACKET= 27,
	KEY_ENTER		= 28,
	KEY_LCTRL		= 29,
	KEY_A			= 30,
	KEY_S			= 31,
	KEY_D			= 32,
	KEY_F			= 33,
	KEY_G			= 34,
	KEY_H			= 35,
	KEY_J			= 36,
	KEY_K			= 37,
	KEY_L			= 38,
	KEY_SEMICOLON	= 39,
	KEY_QUOTE		= 40,
	KEY_RQUOTE		= 41,
	KEY_LSHIFT		= 42,
	KEY_BACKSLASH	= 43,
	KEY_Z			= 44,
	KEY_X			= 45,
	KEY_C			= 46,
	KEY_V			= 47,
	KEY_B			= 48,
	KEY_N			= 49,
	KEY_M			= 50,
	KEY_COMMA		= 51,
	KEY_DOT 		= 52,
	KEY_SLASH		= 53,
	KEY_RSHIFT		= 54,
	KEY_ASTERISK	= 55,
	KEY_RALT		= 56,
	KEY_SPACE		= 57,
	KEY_CAPSLOCK	= 58,
	KEY_F1			= 59,
	KEY_F2			= 60,
	KEY_F3			= 61,
	KEY_F4			= 62,
	KEY_F5			= 63,
	KEY_F6			= 64,
	KEY_F7			= 65,
	KEY_F8			= 66,
	KEY_F9			= 67,
	KEY_F10 		= 68,
	KEY_NUMLOCK 	= 69,
	KEY_SCROLLOCK	= 70,
	KEY_HOME		= 71,
	KEY_KP7 		= 71,
	KEY_UP			= 72,
	KEY_KP8 		= 72,
	KEY_PAGEUP		= 73,
	KEY_KP9 		= 73,
	KEY_KP_MINUS	= 74,
	KEY_LEFT		= 75,
	KEY_KP4 		= 75,
	KEY_KP5 		= 76,
	KEY_RIGHT		= 77,
	KEY_KP6 		= 77,
	KEY_KP_PLUS 	= 78,
	KEY_END 		= 79,
	KEY_KP1 		= 79,
	KEY_DOWN		= 80,
	KEY_KP2 		= 80,
	KEY_PAGEDOWN	= 81,
	KEY_KP3 		= 81,
	KEY_INSERT		= 82,
	KEY_KP0 		= 82,
	KEY_DELETE		= 83,
	KEY_KP_DOT		= 83,
	// 84 - 86
	KEY_F11 		= 87,
	KEY_F12 		= 88,

	MOUSE_LEFT		= 0,
	MOUSE_MIDDLE	= 1,
	MOUSE_RIGHT 	= 2
};

#endif	// FLEXIDEFINES_H

