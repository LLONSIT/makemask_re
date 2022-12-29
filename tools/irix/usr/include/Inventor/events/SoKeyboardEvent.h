/*
 * Copyright 1991-1996, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 */
//  -*- C++ -*-

/*
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 2.2 $
 |
 |   Classes:
 |	SoKeyboardEvent
 |
 |   Author(s): David Mott, Gavin Bell
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  _SO_KEYBOARD_EVENT_
#define  _SO_KEYBOARD_EVENT_

#include <Inventor/SbBasic.h>
#include <Inventor/events/SoButtonEvent.h>

// some convenience macros for determining if an event matches

#define SO_KEY_PRESS_EVENT(EVENT,KEY) \
    (SoKeyboardEvent::isKeyPressEvent(EVENT,SoKeyboardEvent::KEY))

#define SO_KEY_RELEASE_EVENT(EVENT,KEY) \
    (SoKeyboardEvent::isKeyReleaseEvent(EVENT,SoKeyboardEvent::KEY))



class SoKeyboardEvent : public SoButtonEvent {

    SO_EVENT_HEADER();
    
  public:
  
    // the keyboard keys...
    enum Key {
	// Special constant for any key
	ANY = 0, 


	// Modifiers

	LEFT_SHIFT = 0xffe1, 
	RIGHT_SHIFT = 0xffe2, 
	LEFT_CONTROL = 0xffe3, 
	RIGHT_CONTROL = 0xffe4, 
	LEFT_ALT = 0xffe9, 
	RIGHT_ALT = 0xffea, 
	
	
	// Numbers
	
	NUMBER_0 = 0x030, 
	NUMBER_1 = 0x031, 
	NUMBER_2 = 0x032, 
	NUMBER_3 = 0x033, 
	NUMBER_4 = 0x034, 
	NUMBER_5 = 0x035, 
	NUMBER_6 = 0x036, 
	NUMBER_7 = 0x037, 
	NUMBER_8 = 0x038, 
	NUMBER_9 = 0x039, 
	
	
	// Letters
	
	A = 0x061, 
	B = 0x062, 
	C = 0x063, 
	D = 0x064, 
	E = 0x065, 
	F = 0x066, 
	G = 0x067, 
	H = 0x068, 
	I = 0x069, 
	J = 0x06a, 
	K = 0x06b, 
	L = 0x06c, 
	M = 0x06d, 
	N = 0x06e, 
	O = 0x06f, 
	P = 0x070, 
	Q = 0x071, 
	R = 0x072, 
	S = 0x073, 
	T = 0x074, 
	U = 0x075, 
	V = 0x076, 
	W = 0x077, 
	X = 0x078, 
	Y = 0x079, 
	Z = 0x07a, 
	
	
	// Cursor control & motion
	
	HOME = 0xff50, 
	LEFT_ARROW = 0xff51, 
	UP_ARROW = 0xff52, 
	RIGHT_ARROW = 0xff53, 
	DOWN_ARROW = 0xff54, 
	PAGE_UP = 0xff55, 
	PAGE_DOWN = 0xff56, 
	PRIOR = 0xff55, 
	NEXT = 0xff56, 
	END = 0xff57, 
	
		
	// Keypad Functions
	
	PAD_ENTER = 0xff8d, 
	PAD_F1 = 0xff91, 
	PAD_F2 = 0xff92, 
	PAD_F3 = 0xff93, 
	PAD_F4 = 0xff94, 
	
	PAD_0 = 0xff9e,
	PAD_1 = 0xff9c, 
	PAD_2 = 0xff99, 
	PAD_3 = 0xff9b, 
	PAD_4 = 0xff96, 
	PAD_5 = 0xff9d, 
	PAD_6 = 0xff98, 
	PAD_7 = 0xff95, 
	PAD_8 = 0xff97, 
	PAD_9 = 0xff9a, 
	
	PAD_ADD = 0xffab, 
	PAD_SUBTRACT = 0xffad, 
	PAD_MULTIPLY = 0xffaa, 
	PAD_DIVIDE = 0xffaf, 
	
	PAD_SPACE = 0xff8d, 
	PAD_TAB = 0xff89,
	PAD_INSERT = 0xff9e, 
	PAD_DELETE = 0xff9f, 
	PAD_PERIOD = 0xff9f, 
	
	// Function keys
	
	F1 = 0xffbe, 
	F2 = 0xffbf, 
	F3 = 0xffc0, 
	F4 = 0xffc1, 
	F5 = 0xffc2, 
	F6 = 0xffc3, 
	F7 = 0xffc4,
	F8 = 0xffc5, 
	F9 = 0xffc6, 
	F10 = 0xffc7, 
	F11 = 0xffc8, 
	F12 = 0xffc9, 
	
	
	// Misc Functions
	
	BACKSPACE = 0xff08, 
	TAB = 0xff09, 
	RETURN = 0xff0d, 
	ENTER = 0xff0d, 
	PAUSE = 0xff13, 
	SCROLL_LOCK = 0xff14, 
	ESCAPE = 0xff1b, 
	DELETE = 0xffff, 
	PRINT = 0xff61, 
	INSERT = 0xff63, 
	NUM_LOCK = 0xff7f, 
	CAPS_LOCK = 0xffe5, 
	SHIFT_LOCK = 0xffe6, 
	
	SPACE = 0x020, 
	APOSTROPHE = 0x027, 
	COMMA = 0x02c, 
	MINUS = 0x02d, 
	PERIOD = 0x02e, 
	SLASH = 0x02f, 
	
	SEMICOLON = 0x03b, 
	EQUAL = 0x03d, 
	
	BRACKETLEFT = 0x05b, 
	BACKSLASH = 0x05c, 
	BRACKETRIGHT = 0x05d, 
	GRAVE = 0x060
    };
    
    // constructor
    SoKeyboardEvent();
    virtual ~SoKeyboardEvent();
    
    // set/get which key generated the event (e.g. SoKeyboardEvent::A)
    void		  setKey(SoKeyboardEvent::Key whichKey)	{ key = whichKey; }
    SoKeyboardEvent::Key  getKey() const			{ return key; }
    
    // convenience routines to see if an SoEvent is a press or release
    // of the passed keyboard key
    static SbBool	isKeyPressEvent(
			    const SoEvent *e,
			    SoKeyboardEvent::Key whichKey);
			    
    static SbBool	isKeyReleaseEvent(
			    const SoEvent *e,
			    SoKeyboardEvent::Key whichKey);
    
    // Convenience routine that returns the character representing the
    // key, if it's printable. If not, this returns NUL ('\0').
    char		getPrintableCharacter() const;

  SoINTERNAL public:
    static void		initClass();
    
  private:
    Key			key;	// which key
};


#endif /* _SO_KEYBOARD_EVENT_ */
