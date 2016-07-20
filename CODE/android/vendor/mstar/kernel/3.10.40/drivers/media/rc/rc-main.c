/* rc-main.c - Remote Controller core module
 *
 * Copyright (C) 2009-2010 by Mauro Carvalho Chehab <mchehab@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

#include <media/rc-core.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/module.h>
#include "rc-core-priv.h"

/* Sizes are in bytes, 256 bytes allows for 32 entries on x64 */
#define IR_TAB_MIN_SIZE	256
#define IR_TAB_MAX_SIZE	8192

/* FIXME: IR_KEYPRESS_TIMEOUT should be protocol specific */
#define IR_KEYPRESS_TIMEOUT 250

/* Used to keep track of known keymaps */
static LIST_HEAD(rc_map_list);
static DEFINE_SPINLOCK(rc_map_lock);

static struct rc_map_table mstar_tv[] = {
    { 0x0046, KEY_POWER },		// 1
    { 0x0050, KEY_0 },			// 2
    { 0x0049, KEY_1 },			// 3
    { 0x0055, KEY_2 },
    { 0x0059, KEY_3 },
    { 0x004D, KEY_4 },
    { 0x0051, KEY_5 },
    { 0x005D, KEY_6 },
    { 0x0048, KEY_7 },
    { 0x0054, KEY_8 },
    { 0x0058, KEY_9 },
    { 0x0047, KEY_RED },
    { 0x004B, KEY_GREEN },
    { 0x0057, KEY_YELLOW },
    { 0x005B, KEY_BLUE },
    { 0x0052, KEY_UP },
    { 0x0013, KEY_DOWN },
    { 0x0006, KEY_LEFT },
    { 0x001A, KEY_RIGHT },
    { 0x000F, KEY_ENTER },
    { 0x001F, KEY_CHANNELUP },
    { 0x0019, KEY_CHANNELDOWN },
    { 0x0016, KEY_VOLUMEUP },
    { 0x0015, KEY_VOLUMEDOWN },
    { 0x0003, KEY_PAGEUP },
    { 0x0005, KEY_PAGEDOWN },
    { 0x0017, KEY_HOME},
    { 0x0007, KEY_MENU },
    { 0x001B, KEY_BACK },
    { 0x005A, KEY_MUTE },
    { 0x000D, KEY_RECORD },     // DVR
    { 0x0042, KEY_HELP },       // GUIDE
    { 0x0014, KEY_INFO },
    { 0x0040, KEY_KP0 },        // WINDOW
    { 0x0004, KEY_KP1 },        // TV_INPUT
    { 0x000E, KEY_REWIND },
    { 0x0012, KEY_FORWARD },
    { 0x0002, KEY_PREVIOUSSONG },
    { 0x001E, KEY_NEXTSONG },
    { 0x0001, KEY_PLAY },
    { 0x001D, KEY_PAUSE },
    { 0x0011, KEY_STOP },
    { 0x0044, KEY_AUDIO },      // (C)SOUND_MODE
    { 0x0056, KEY_CAMERA },     // (C)PICTURE_MODE
    { 0x004C, KEY_ZOOM },       // (C)ASPECT_RATIO
    { 0x005C, KEY_CHANNEL },    // (C)CHANNEL_RETURN
    { 0x0045, KEY_SLEEP },      // (C)SLEEP
    { 0x004A, KEY_EPG },        // (C)EPG
    { 0x0010, KEY_LIST },       // (C)LIST
    { 0x0053, KEY_SUBTITLE },   // (C)SUBTITLE
    { 0x0041, KEY_FN_F1 },      // (C)MTS
    { 0x004E, KEY_FN_F2 },      // (C)FREEZE
    { 0x000A, KEY_FN_F3 },      // (C)TTX
    { 0x0009, KEY_FN_F4 },      // (C)CC
    { 0x001C, KEY_FN_F5 },      // (C)TV_SETTING
    { 0x0008, KEY_FN_F6 },      // (C)SCREENSHOT
    { 0x000B, KEY_F1 },         // MSTAR_BALANCE
    { 0x0018, KEY_F2 },         // MSTAR_INDEX
    { 0x0000, KEY_F3 },         // MSTAR_HOLD
    { 0x000C, KEY_F4 },         // MSTAR_UPDATE
    { 0x004F, KEY_F5 },         // MSTAR_REVEAL
    { 0x005E, KEY_F6 },         // MSTAR_SUBCODE
    { 0x0043, KEY_F7 },         // MSTAR_SIZE
    { 0x005F, KEY_F8 },         // MSTAR_CLOCK
    { 0x00FE, KEY_POWER2 },     // FAKE_POWER
    { 0x00FF, KEY_OK },         // KEY_OK
};

static struct rc_map_table double_tv[] = {
    { 0x0070, KEY_F13 },	//KEY_POWER
    { 0x007b, KEY_F14 },	//KEY_UP
    { 0x007c, KEY_F15 },	//KEY_DOWN
    { 0x007d, KEY_F16 },	//KEY_LEFT
    { 0x007e, KEY_F17 },	//KEY_RIGHT
    { 0x007f, KEY_F18 },	//KEY_ENTER
    { 0x0078, KEY_F19 },	//KEY_BACK
    { 0x0036, KEY_F20 },	//KEY_VOLUMEUP
    { 0x0037, KEY_F21 },	//KEY_VOLUMEDOWN
    { 0x002e, KEY_F22 },	//guide
    //{ 0x007c, KEY_F23 },	//KEY_CHANNELDOWN
    { 0x0077, KEY_F24 },	//home
    { 0x0074, KEY_EDIT },	//info
    { 0x0020, KEY_A },
    { 0x0021, KEY_B },
    { 0x0022, KEY_C },
    { 0x0023, KEY_D },
    { 0x0024, KEY_E },
    { 0x0025, KEY_F },
    { 0x0026, KEY_G },
    { 0x0027, KEY_H },
    { 0x0028, KEY_I },
    { 0x0029, KEY_J },
    { 0x007a, KEY_K},	//KEY_CHANNELBACK
};

static struct rc_map_table double_a_tv[] = {
    { 0x00dc, KEY_F13 },	//KEY_POWER
    { 0x00ca, KEY_F14 },	//KEY_UP & KEY_CHANNELUP
    { 0x00d2, KEY_F15 },	//KEY_DOWN & KEY_CHANNELDOWN
    { 0x00c1, KEY_F16 },	//KEY_LEFT & KEY_VOLUMEDOWN
    { 0x0099, KEY_F17 },	//KEY_RIGHT & KEY_VOLUMEUP
    { 0x00ce, KEY_F18 },	//KEY_ENTER
    { 0x00c5, KEY_F19 },	//KEY_BACK
    //{ 0x0099, KEY_F20 },	//KEY_VOLUMEUP
    //{ 0x00c1, KEY_F21 },	//KEY_VOLUMEDOWN
    { 0x00d0, KEY_F22 },	//guide
    { 0x00d6, KEY_F22 },	//guide --- 0303
    { 0x0082, KEY_F24 },	//home
    { 0x0080, KEY_EDIT },	//info
    { 0x0087, KEY_A },	// 0
    { 0x0092, KEY_B },	// 1
    { 0x0093, KEY_C },	// 2
    { 0x00cc, KEY_D },	// 3
    { 0x008e, KEY_E },	// 4
    { 0x008f, KEY_F },	// 5
    { 0x00c8, KEY_G },	// 6
    { 0x008a, KEY_H },	// 7
    { 0x008b, KEY_I },	// 8
    { 0x00c4, KEY_J },	// 9
    { 0x0081, KEY_K},	//KEY_CHANNELBACK
    { 0x00ca, KEY_L },	//KEY_CHANNELUP
    { 0x00d2, KEY_M },	//KEY_CHANNELDOWN
};

static struct rc_map_table double_b_tv[] = {
    { 0x000a, KEY_F13 },	//KEY_POWER
    { 0x0050, KEY_F14 },	//KEY_UP
    { 0x0051, KEY_F15 },	//KEY_DOWN
    { 0x0052, KEY_F16 },	//KEY_LEFT
    { 0x0053, KEY_F17 },	//KEY_RIGHT
    { 0x0054, KEY_F18 },	//KEY_ENTER
    { 0x0041, KEY_F19 },	//KEY_BACK
    { 0x0018, KEY_F20 },	//KEY_VOLUMEUP
    { 0x0019, KEY_F21 },	//KEY_VOLUMEDOWN
    //{ 0x0016, KEY_F22 },	//guide
    { 0x0082, KEY_F24 },	//home
    { 0x000c, KEY_EDIT },	//info
    { 0x0000, KEY_A },	// 0
    { 0x0001, KEY_B },	// 1
    { 0x0002, KEY_C },	// 2
    { 0x0003, KEY_D },	// 3
    { 0x0004, KEY_E },	// 4
    { 0x0005, KEY_F },	// 5
    { 0x0006, KEY_G },	// 6
    { 0x0007, KEY_H },	// 7
    { 0x0008, KEY_I },	// 8
    { 0x0009, KEY_J },	// 9
    { 0x0042, KEY_K},	//KEY_CHANNELBACK
    { 0x0016, KEY_L },	//KEY_CHANNELUP
    { 0x0017, KEY_M },	//KEY_CHANNELDOWN
    { 0x0047, KEY_F14 },	//KEY_UP   ---- 2003
    { 0x0046, KEY_F15 },	//KEY_DOWN   ---- 2003
    { 0x0048, KEY_F16 },	//KEY_LEFT   ---- 2003
    { 0x004a, KEY_F17 },	//KEY_RIGHT   ---- 2003
    { 0x0049, KEY_F18 },	//KEY_ENTER   ---- 2003
    { 0x004c, KEY_F19 },	//KEY_BACK   ---- 2003
    //{ 0x004a, KEY_F20 },	//KEY_VOLUMEUP   ---- 2003
    //{ 0x0048, KEY_F21 },	//KEY_VOLUMEDOWN   ---- 2003
    { 0x004e, KEY_F22 },	//guide   ---- 2003
    { 0x001b, KEY_EDIT },	//info   ---- 2003
    { 0x001a, KEY_K},	//KEY_CHANNELBACK   ---- 2003
    //{ 0x0047, KEY_L },	//KEY_CHANNELUP   ---- 2003
    { 0x004b, KEY_M },	//KEY_CHANNELDOWN   ---- 2003
};

static struct rc_map_table double_c_tv[] = {
    { 0x000b, KEY_F13 },	//KEY_POWER
    { 0x000e, KEY_F14 },	//KEY_UP
    { 0x000a, KEY_F15 },	//KEY_DOWN
    { 0x001a, KEY_F16 },	//KEY_LEFT & KEY_VOLUMEDOWN
    { 0x0012, KEY_F17 },	//KEY_RIGHT & KEY_VOLUMEUP
    { 0x0006, KEY_F18 },	//KEY_ENTER
    { 0x0013, KEY_F19 },	//KEY_BACK
    //{ 0x0012, KEY_F20 },	//KEY_VOLUMEUP
    //{ 0x001a, KEY_F21 },	//KEY_VOLUMEDOWN
    { 0x0041, KEY_F22 },	//guide
    { 0x0082, KEY_F24 },	//home
    { 0x005c, KEY_EDIT },	//info
    { 0x000c, KEY_A },	// 0
    { 0x001b, KEY_B },	// 1
    { 0x000f, KEY_C },	// 2
    { 0x0003, KEY_D },	// 3
    { 0x0019, KEY_E },	// 4
    { 0x0011, KEY_F },	// 5
    { 0x0001, KEY_G },	// 6
    { 0x0009, KEY_H },	// 7
    { 0x001d, KEY_I },	// 8
    { 0x000d, KEY_J },	// 9
    { 0x001C, KEY_K},	//KEY_CHANNELBACK
    //{ 0x000e, KEY_L },	//KEY_CHANNELUP
    //{ 0x000a, KEY_M },	//KEY_CHANNELDOWN
};
static struct rc_map_table double_d_tv[] = {
    { 0x0000, KEY_F13 },	//KEY_POWER
    { 0x0010, KEY_F14 },	//KEY_UP
    { 0x0014, KEY_F15 },	//KEY_DOWN
    { 0x0011, KEY_F16 },	//KEY_LEFT
    { 0x0013, KEY_F17 },	//KEY_RIGHT
    { 0x0012, KEY_F18 },	//KEY_ENTER
    { 0x0016, KEY_F19 },	//KEY_BACK
    { 0x0019, KEY_F20 },	//KEY_VOLUMEUP
    { 0x0022, KEY_F21 },	//KEY_VOLUMEDOWN
    { 0x0040, KEY_F22 },	//guide
    { 0x0082, KEY_F24 },	//home
    { 0x000b, KEY_EDIT },	//info
    { 0x0041, KEY_A },	// 0
    { 0x0031, KEY_B },	// 1
    { 0x0032, KEY_C },	// 2
    { 0x0033, KEY_D },	// 3
    { 0x0034, KEY_E },	// 4
    { 0x0035, KEY_F },	// 5
    { 0x0036, KEY_G },	// 6
    { 0x0037, KEY_H },	// 7
    { 0x0038, KEY_I },	// 8
    { 0x0039, KEY_J },	// 9
    { 0x0042, KEY_K},	//KEY_CHANNELBACK
    { 0x0017, KEY_L },	//KEY_CHANNELUP
    { 0x0020, KEY_M },	//KEY_CHANNELDOWN
};
	
static struct rc_map_table H_tv[] = {
    { 0x0044, KEY_UP },
    { 0x0051, KEY_ENTER },		
    { 0x0045, KEY_POWER },		// 1
    { 0x001c, KEY_LEFT },		// 2
    { 0x0048, KEY_RIGHT },			// 3
    { 0x001d, KEY_DOWN },
    { 0x0019, KEY_BACK },
    { 0x000F, KEY_VOLUMEUP },
    { 0x000E, KEY_VOLUMEDOWN },
    { 0x0050, KEY_CHANNELUP },
    { 0x0056, KEY_CHANNELDOWN },
    { 0x005c, KEY_MENU },
    { 0x0011, KEY_HOME },
    { 0x0010, KEY_MUTE },
    { 0x0003, KEY_0 },
    { 0x0004, KEY_1 },
    { 0x0005, KEY_2 },
    { 0x005f, KEY_3 },
    { 0x0007, KEY_4 },
    { 0x0008, KEY_5 },
    { 0x0009, KEY_6 },
    { 0x000a, KEY_7 },
    { 0x000b, KEY_8 },
    { 0x000c, KEY_9 },
    { 0x0000, KEY_KP1 },        // TV_INPUT
    { 0x0014, KEY_REWIND },
    { 0x0015, KEY_FORWARD },
    { 0x0016, KEY_PLAY },
    { 0x0017, KEY_STOP },
    { 0x001e, KEY_RECORD },
    { 0x001f, KEY_F20 },
    { 0x0058, KEY_F21 },
    { 0x0040, KEY_INFO },
    { 0x0055, KEY_F5 },
    { 0x0049, KEY_EPG },
    { 0x004e, KEY_LIST },
    { 0x004f, KEY_F7 },
    { 0x0057, KEY_F9 },
    { 0x0046, KEY_KP8 },
    { 0x0054, KEY_F10 },
    { 0x005a, KEY_KP7 },
    { 0x001a, KEY_PAGEUP },
    { 0x001b, KEY_PAGEDOWN },
    { 0x005e, KEY_PREVIOUSSONG },
    { 0x0059, KEY_NEXTSONG },
    { 0x004A, KEY_RED },
    { 0x004B, KEY_GREEN },
    { 0x004C, KEY_YELLOW },
    { 0x004D, KEY_BLUE },
    { 0x0053, KEY_FN_F2 },      // (C)FREEZE 
    { 0x0042, KEY_SUBTITLE },   // (C)SUBTITLE
    { 0x005B, KEY_FN_F3 },      // (C)TTX
    { 0x0047, KEY_FN_F4 },      // (C)CC
    { 0x0018, KEY_F2 },         // MSTAR_INDEX
    { 0x0043, KEY_FN_F1 },      // (C)MTS
    { 0x0002, KEY_CHANNEL },    // (C)CHANNEL_RETURN
    { 0x0041, KEY_F4 },      // (C)SOUND_MODE
    { 0x0012, KEY_F6 },         // MSTAR_SUBCODE
    { 0x005D, KEY_FN_F6 },      // (C)SCREENSHOT
    //----------changhong remote-define-------------         
    { 0x00DF, KEY_VIDEO},         
    { 0x009D, KEY_DVD},         
    { 0x0094, KEY_CLEAR},         
    { 0x00F1, KEY_TV2},        
    { 0x00DE, KEY_OPTION},  //no      
    { 0x00D7, KEY_VCR},        
    { 0x00C3, KEY_VCR2},        
    { 0x00D3, KEY_SAT},        
    { 0x00CF, KEY_SAT2},        
    { 0x00CB, KEY_CD},        
    { 0x00C0, KEY_TAPE},        
    { 0x00C4, KEY_RADIO},        
    { 0x00C8, KEY_TUNER},        
    { 0x0083, KEY_PLAYER},        
    { 0x0087, KEY_AUX},        
    { 0x008B, KEY_MP3},        
    { 0x0082, KEY_AB}, //no       
    { 0x0086, KEY_N},        
    { 0x008A, KEY_O},        
    { 0x008E, KEY_P},       
    // { 0x0081, KEY_Q},//text        
    { 0x00D9, KEY_R},        
    { 0x00DD, KEY_S},        
    { 0x00D8, KEY_T},        
    { 0x00DC, KEY_U},        
    { 0x009B, KEY_V},        
    { 0x0099, KEY_W},        
    { 0x0096, KEY_X},        
    { 0x009E, KEY_Y},        
    { 0x009A, KEY_NEXT}, //no       
    { 0x0089, KEY_RESTART},   //no       
    { 0x00D2, KEY_SLOW},   //no     
    { 0x00CE, KEY_SHUFFLE},   //no     
    { 0x00CD, KEY_BREAK},    //no    
    { 0x00C1, KEY_PREVIOUS},    //no    
    { 0x00D6, KEY_DIGITS},   //no        
    { 0x00C6, KEY_F23},          
    { 0x00D1, KEY_F11},        
    { 0x00CA, KEY_F12},        
    { 0x00EC, KEY_KP2},        
    { 0x00ED, KEY_KP3},        
    { 0x00EE, KEY_KP4},        
    //{ 0x00EF, KEY_KP5},        
    { 0x00D5, KEY_FN_F7},   //no    
    // { 0x0093, KEY_FN_F7},        
    //{ 0x00CC, KEY_FN_F8},        
    { 0x0091, KEY_FN_F8},    //no    
    { 0x00D4, KEY_FN_F9},        
    { 0x008F, KEY_FN_F10},        
    { 0x00C7, KEY_FN_F11},        
    { 0x0092, KEY_FN_F12},        
    { 0x00D0, KEY_FN_D},        
    //{ 0x009F, KEY_FN_E},        
    { 0x0090, KEY_FN_F},        
    //{ 0x0095, KEY_FN_S},        
    { 0x00E1, KEY_FN_B},        
    { 0x00E2, KEY_TV},        
    { 0x00E3, KEY_PC},        
    { 0x00E7, KEY_KPDOT},        
    { 0x00F2, KEY_KPMINUS},        
    { 0x00E8, KEY_KPPLUS},        
    { 0x00E9, KEY_Z},        
    { 0x00EA, KEY_SELECT},        
    { 0x00EB, KEY_GOTO},   
    //------End changhong IR----------------------    
    { 0x00FE, KEY_POWER2 },     // FAKE_POWER    
    { 0x00FF, KEY_OK },         // KEY_OK

};

static struct rc_map_table tongshuai_tv[] = {
    { 0x000b, KEY_UP },
    { 0x000d, KEY_ENTER },
    { 0x000a, KEY_POWER },
    { 0x0010, KEY_LEFT },
    { 0x0011, KEY_RIGHT },
    { 0x000e, KEY_DOWN },
    { 0x0037, KEY_BACK },
    { 0x0015, KEY_VOLUMEUP },
    { 0x001c, KEY_VOLUMEDOWN },
    { 0x0016, KEY_HOME },
    { 0x0040, KEY_MENU },
    { 0x000c, KEY_KP1 },
    { 0x000c, KEY_EPG },
    { 0x0001, KEY_1 },
    { 0x0002, KEY_2 },
    { 0x0003, KEY_3 },
    { 0x0004, KEY_4 },
    { 0x0005, KEY_5 },
    { 0x0006, KEY_6 },
    { 0x0007, KEY_7 },
    { 0x0008, KEY_8 },
    { 0x0009, KEY_9 },
    { 0x0045, KEY_0 },
    { 0x00a9, KEY_RECORD },
};
static struct rc_map_table benq_tv[] = {
   { 0x0000, KEY_POWER },		// 1
    { 0x0003, KEY_0 },			// 2
    { 0x0004, KEY_1 },			// 3
    { 0x0005, KEY_2 },
    { 0x005f, KEY_3 },
    { 0x0007, KEY_4 },
    { 0x0008, KEY_5 },
    { 0x0009, KEY_6 },
    { 0x000A, KEY_7 },
    { 0x000B, KEY_8 },
    { 0x000C, KEY_9 },
    { 0x0002, KEY_RED },
    { 0x000E, KEY_GREEN },
    { 0x0016, KEY_YELLOW },
    { 0x0017, KEY_BLUE },
    { 0x0044, KEY_UP },
    { 0x001d, KEY_DOWN },
    { 0x001C, KEY_LEFT },
    { 0x0048, KEY_RIGHT },
    { 0x0051, KEY_ENTER },
    { 0x005C, KEY_CHANNELUP },
    { 0x0014, KEY_CHANNELDOWN },
    { 0x0019, KEY_VOLUMEUP },
    { 0x0015, KEY_VOLUMEDOWN },
    { 0x0061, KEY_HOME},
    { 0x0012, KEY_MENU },
    { 0x0042, KEY_MUTE },
    { 0x0065, KEY_RECORD },     // DVR
    { 0x0010, KEY_KP1 },        // TV_INPUT    
    { 0x0067, KEY_REWIND },
    { 0x0069, KEY_FORWARD },
    { 0x006A, KEY_PREVIOUSSONG },
    { 0x006C, KEY_NEXTSONG },
    { 0x0068, KEY_PLAY },
    { 0x0060, KEY_PAUSE },
    { 0x006B, KEY_STOP },
    { 0x0059, KEY_AUDIO },      // (C)SOUND_MODE
    { 0x004F, KEY_CAMERA },     // (C)PICTURE_MODE
    { 0x0054, KEY_ZOOM },       // (C)ASPECT_RATIO
    { 0x000F, KEY_CHANNEL },    // (C)CHANNEL_RETURN
    { 0x0053, KEY_SLEEP },      // (C)SLEEP
    { 0x0049, KEY_EPG },        // (C)EPG
    { 0x0050, KEY_SUBTITLE },   // (C)SUBTITLE
    { 0x0043, KEY_FN_F1 },      // (C)MTS
    { 0x0013, KEY_BACK },
    { 0x0045, KEY_INFO },
    { 0x0047, KEY_F9 },//input source hotkey  // 
    { 0x0018, KEY_F10 }, //sursound  
    { 0x000D, KEY_KP7},//Select channel
    { 0x0056, KEY_KP8},// favor
    { 0x0011, KEY_KP5},// low blue
    { 0x0041, KEY_KP6},//tool
    { 0x002D, KEY_KP9},//net
};
static struct rc_map_table bq_tv[] = {
   
    { 0x0007, KEY_HP },
    { 0x000b, KEY_UP },
    { 0x0015, KEY_ENTER },
    { 0x0002, KEY_POWER },
    { 0x000d, KEY_LEFT },
    { 0x000e, KEY_RIGHT },	
    { 0x000c, KEY_DOWN },
    { 0x0085, KEY_BACK },
    { 0x0082, KEY_VOLUMEUP },
    { 0x0083, KEY_VOLUMEDOWN },
    { 0x000f, KEY_CONTEXT_MENU},
    { 0x0092, KEY_HOME },
    { 0x0014, KEY_MUTE },
    { 0x0004, KEY_KP1 },
    { 0x00bb, KEY_MENU },
};

static struct rc_map_table Skyworth_tv[] = {
    { 0x000C, KEY_POWER },
    { 0x0000, KEY_0 },			// 2
    { 0x0001, KEY_1 },			// 3
    { 0x0002, KEY_2 },
    { 0x0003, KEY_3 },
    { 0x0004, KEY_4 },
    { 0x0005, KEY_5 },
    { 0x0006, KEY_6 },
    { 0x0007, KEY_7 },
    { 0x0008, KEY_8 },
    { 0x0009, KEY_9 },
    { 0x0042, KEY_UP },
    { 0x0043, KEY_DOWN },
    { 0x0044, KEY_LEFT },
    { 0x0045, KEY_RIGHT },
    { 0x0046, KEY_ENTER },
    { 0x0012, KEY_CHANNELUP },
    { 0x0013, KEY_CHANNELDOWN },
    { 0x0014, KEY_VOLUMEUP },
    { 0x0015, KEY_VOLUMEDOWN },
    { 0x0036, KEY_HOME},
    { 0x0011, KEY_MENU },
    { 0x005B, KEY_BACK },
    { 0x0016, KEY_INFO },
    { 0x0040, KEY_F12},       //hdmi 
    { 0x000F, KEY_KP1 },        // TV_INPUT
    { 0x0047, KEY_PREVIOUSSONG },
    { 0x0048, KEY_NEXTSONG },
    { 0x0049, KEY_PLAY },
    { 0x004A, KEY_STOP },
    { 0x0025, KEY_EPG },        // (C)EPG
    { 0x0024, KEY_FN_F7},   //3D    
    { 0x0026, KEY_FN_F8},    //net
    { 0x0027, KEY_KPDOT},     //wifi 
    { 0x003C, KEY_PREVIOUS},    //YUV   
    { 0x003D, KEY_DIGITS},   //VGA     
    { 0x003E, KEY_SAT2},     //factory_reset   
    { 0x0039, KEY_SAT},     //burning  
    { 0x0038, KEY_FN_F11},   //ADC_Adjust   
    { 0x0028, KEY_PC},        //white_Balance
    { 0x0051, KEY_F23},    //USB 
    //-------New hot key----
    { 0x0020, KEY_FN_E}, //VHF-L
    { 0x0021, KEY_FN_S}, //VHF-H
    { 0x0022, KEY_QUESTION}, //UHF
    { 0x0023, KEY_EMAIL}, //MAC
    { 0x003A, KEY_CHAT}, //IIC
    { 0x003F, KEY_SEARCH}, //factory mode
    { 0x0053, KEY_CONNECT}, //frequent_preset
    { 0x0041, KEY_FINANCE}, //GINGA
    { 0x000A, KEY_SPORT}, //10+
    //----------------------
    { 0x00FE, KEY_POWER2 },     // FAKE_POWER
    { 0x00FF, KEY_OK },         // KEY_OK
};

static struct  eos_xxh_tv_button eos_xxh_tv[]=
{
	{
		.ccode = 0x807F,
		.nbuttons = 65,
		.ir_table = &mstar_tv[0],
	},
	{
		.ccode = 0x09F6,
		.nbuttons = 118,
		.ir_table = &H_tv[0],
	},
	{
		.ccode = 0xbebe,
		.nbuttons = 25,
		.ir_table = &double_tv[0],
	},		
	{
		.ccode = 0x01fd,
		.nbuttons = 25,
		.ir_table = &double_a_tv[0],
	},		
	{
		.ccode = 0x00ff,
		.nbuttons = 35,
		.ir_table = &double_b_tv[0],
	},		
	{
		.ccode = 0x449b,
		.nbuttons = 25,
		.ir_table = &double_c_tv[0],
	},	
	{
		.ccode = 0x2013,
		.nbuttons = 25,
		.ir_table = &double_d_tv[0],
	},	
	{
		.ccode = 0x4040,
		.nbuttons = 24,
		.ir_table = &tongshuai_tv[0],
	},
	{
		.ccode = 0x609F,
		.nbuttons = 53,
		.ir_table = &benq_tv[0],
	},
	{
		.ccode = 0x0030,
		.nbuttons = 18,
		.ir_table = &bq_tv[0],
	},
     {
		.ccode = 0x09F8,
		.nbuttons = 52,
		.ir_table = &Skyworth_tv[0],
	},
};

static struct rc_map_list *seek_rc_map(const char *name)
{
	struct rc_map_list *map = NULL;

	spin_lock(&rc_map_lock);
	list_for_each_entry(map, &rc_map_list, list) {
		if (!strcmp(name, map->map.name)) {
			spin_unlock(&rc_map_lock);
			return map;
		}
	}
	spin_unlock(&rc_map_lock);

	return NULL;
}

struct rc_map *rc_map_get(const char *name)
{

	struct rc_map_list *map;

	map = seek_rc_map(name);
#ifdef MODULE
	if (!map) {
		int rc = request_module(name);
		if (rc < 0) {
			printk(KERN_ERR "Couldn't load IR keymap %s\n", name);
			return NULL;
		}
		msleep(20);	/* Give some time for IR to register */

		map = seek_rc_map(name);
	}
#endif
	if (!map) {
		printk(KERN_ERR "IR keymap %s not found\n", name);
		return NULL;
	}

	printk(KERN_INFO "Registered IR keymap %s\n", map->map.name);

	return &map->map;
}
EXPORT_SYMBOL_GPL(rc_map_get);

int rc_map_register(struct rc_map_list *map)
{
	spin_lock(&rc_map_lock);
	list_add_tail(&map->list, &rc_map_list);
	spin_unlock(&rc_map_lock);
	return 0;
}
EXPORT_SYMBOL_GPL(rc_map_register);

void rc_map_unregister(struct rc_map_list *map)
{
	spin_lock(&rc_map_lock);
	list_del(&map->list);
	spin_unlock(&rc_map_lock);
}
EXPORT_SYMBOL_GPL(rc_map_unregister);


static struct rc_map_table empty[] = {
	{ 0x2a, KEY_COFFEE },
};

static struct rc_map_list empty_map = {
	.map = {
		.scan    = empty,
		.size    = ARRAY_SIZE(empty),
		.rc_type = RC_TYPE_UNKNOWN,	/* Legacy IR type */
		.name    = RC_MAP_EMPTY,
	}
};

/**
 * ir_create_table() - initializes a scancode table
 * @rc_map:	the rc_map to initialize
 * @name:	name to assign to the table
 * @rc_type:	ir type to assign to the new table
 * @size:	initial size of the table
 * @return:	zero on success or a negative error code
 *
 * This routine will initialize the rc_map and will allocate
 * memory to hold at least the specified number of elements.
 */
static int ir_create_table(struct rc_map *rc_map,
			   const char *name, u64 rc_type, size_t size)
{
	rc_map->name = name;
	rc_map->rc_type = rc_type;
	rc_map->alloc = roundup_pow_of_two(size * sizeof(struct rc_map_table));
	rc_map->size = rc_map->alloc / sizeof(struct rc_map_table);
	rc_map->scan = kmalloc(rc_map->alloc, GFP_KERNEL);
	if (!rc_map->scan)
		return -ENOMEM;

	IR_dprintk(1, "Allocated space for %u keycode entries (%u bytes)\n",
		   rc_map->size, rc_map->alloc);
	return 0;
}

/**
 * ir_free_table() - frees memory allocated by a scancode table
 * @rc_map:	the table whose mappings need to be freed
 *
 * This routine will free memory alloctaed for key mappings used by given
 * scancode table.
 */
static void ir_free_table(struct rc_map *rc_map)
{
	rc_map->size = 0;
	kfree(rc_map->scan);
	rc_map->scan = NULL;
}

/**
 * ir_resize_table() - resizes a scancode table if necessary
 * @rc_map:	the rc_map to resize
 * @gfp_flags:	gfp flags to use when allocating memory
 * @return:	zero on success or a negative error code
 *
 * This routine will shrink the rc_map if it has lots of
 * unused entries and grow it if it is full.
 */
static int ir_resize_table(struct rc_map *rc_map, gfp_t gfp_flags)
{
	unsigned int oldalloc = rc_map->alloc;
	unsigned int newalloc = oldalloc;
	struct rc_map_table *oldscan = rc_map->scan;
	struct rc_map_table *newscan;

	if (rc_map->size == rc_map->len) {
		/* All entries in use -> grow keytable */
		if (rc_map->alloc >= IR_TAB_MAX_SIZE)
			return -ENOMEM;

		newalloc *= 2;
		IR_dprintk(1, "Growing table to %u bytes\n", newalloc);
	}

	if ((rc_map->len * 3 < rc_map->size) && (oldalloc > IR_TAB_MIN_SIZE)) {
		/* Less than 1/3 of entries in use -> shrink keytable */
		newalloc /= 2;
		IR_dprintk(1, "Shrinking table to %u bytes\n", newalloc);
	}

	if (newalloc == oldalloc)
		return 0;

	newscan = kmalloc(newalloc, gfp_flags);
	if (!newscan) {
		IR_dprintk(1, "Failed to kmalloc %u bytes\n", newalloc);
		return -ENOMEM;
	}

	memcpy(newscan, rc_map->scan, rc_map->len * sizeof(struct rc_map_table));
	rc_map->scan = newscan;
	rc_map->alloc = newalloc;
	rc_map->size = rc_map->alloc / sizeof(struct rc_map_table);
	kfree(oldscan);
	return 0;
}

/**
 * ir_update_mapping() - set a keycode in the scancode->keycode table
 * @dev:	the struct rc_dev device descriptor
 * @rc_map:	scancode table to be adjusted
 * @index:	index of the mapping that needs to be updated
 * @keycode:	the desired keycode
 * @return:	previous keycode assigned to the mapping
 *
 * This routine is used to update scancode->keycode mapping at given
 * position.
 */
static unsigned int ir_update_mapping(struct rc_dev *dev,
				      struct rc_map *rc_map,
				      unsigned int index,
				      unsigned int new_keycode)
{
	int old_keycode = rc_map->scan[index].keycode;
	int i;

	/* Did the user wish to remove the mapping? */
	if (new_keycode == KEY_RESERVED || new_keycode == KEY_UNKNOWN) {
		IR_dprintk(1, "#%d: Deleting scan 0x%04x\n",
			   index, rc_map->scan[index].scancode);
		rc_map->len--;
		memmove(&rc_map->scan[index], &rc_map->scan[index+ 1],
			(rc_map->len - index) * sizeof(struct rc_map_table));
	} else {
		IR_dprintk(1, "#%d: %s scan 0x%04x with key 0x%04x\n",
			   index,
			   old_keycode == KEY_RESERVED ? "New" : "Replacing",
			   rc_map->scan[index].scancode, new_keycode);
		rc_map->scan[index].keycode = new_keycode;
		__set_bit(new_keycode, dev->input_dev->keybit);
	}

	if (old_keycode != KEY_RESERVED) {
		/* A previous mapping was updated... */
		__clear_bit(old_keycode, dev->input_dev->keybit);
		/* ... but another scancode might use the same keycode */
		for (i = 0; i < rc_map->len; i++) {
			if (rc_map->scan[i].keycode == old_keycode) {
				__set_bit(old_keycode, dev->input_dev->keybit);
				break;
			}
		}

		/* Possibly shrink the keytable, failure is not a problem */
		ir_resize_table(rc_map, GFP_ATOMIC);
	}

	return old_keycode;
}

/**
 * ir_establish_scancode() - set a keycode in the scancode->keycode table
 * @dev:	the struct rc_dev device descriptor
 * @rc_map:	scancode table to be searched
 * @scancode:	the desired scancode
 * @resize:	controls whether we allowed to resize the table to
 *		accommodate not yet present scancodes
 * @return:	index of the mapping containing scancode in question
 *		or -1U in case of failure.
 *
 * This routine is used to locate given scancode in rc_map.
 * If scancode is not yet present the routine will allocate a new slot
 * for it.
 */
static unsigned int ir_establish_scancode(struct rc_dev *dev,
					  struct rc_map *rc_map,
					  unsigned int scancode,
					  bool resize)
{
	unsigned int i;

	/*
	 * Unfortunately, some hardware-based IR decoders don't provide
	 * all bits for the complete IR code. In general, they provide only
	 * the command part of the IR code. Yet, as it is possible to replace
	 * the provided IR with another one, it is needed to allow loading
	 * IR tables from other remotes. So, we support specifying a mask to
	 * indicate the valid bits of the scancodes.
	 */
	if (dev->scanmask)
		scancode &= dev->scanmask;

	/* First check if we already have a mapping for this ir command */
	for (i = 0; i < rc_map->len; i++) {
		if (rc_map->scan[i].scancode == scancode)
			return i;

		/* Keytable is sorted from lowest to highest scancode */
		if (rc_map->scan[i].scancode >= scancode)
			break;
	}

	/* No previous mapping found, we might need to grow the table */
	if (rc_map->size == rc_map->len) {
		if (!resize || ir_resize_table(rc_map, GFP_ATOMIC))
			return -1U;
	}

	/* i is the proper index to insert our new keycode */
	if (i < rc_map->len)
		memmove(&rc_map->scan[i + 1], &rc_map->scan[i],
			(rc_map->len - i) * sizeof(struct rc_map_table));
	rc_map->scan[i].scancode = scancode;
	rc_map->scan[i].keycode = KEY_RESERVED;
	rc_map->len++;

	return i;
}

/**
 * ir_setkeycode() - set a keycode in the scancode->keycode table
 * @idev:	the struct input_dev device descriptor
 * @scancode:	the desired scancode
 * @keycode:	result
 * @return:	-EINVAL if the keycode could not be inserted, otherwise zero.
 *
 * This routine is used to handle evdev EVIOCSKEY ioctl.
 */
static int ir_setkeycode(struct input_dev *idev,
			 const struct input_keymap_entry *ke,
			 unsigned int *old_keycode)
{
	struct rc_dev *rdev = input_get_drvdata(idev);
	struct rc_map *rc_map = &rdev->rc_map;
	unsigned int index;
	unsigned int scancode;
	int retval = 0;
	unsigned long flags;

	spin_lock_irqsave(&rc_map->lock, flags);

	if (ke->flags & INPUT_KEYMAP_BY_INDEX) {
		index = ke->index;
		if (index >= rc_map->len) {
			retval = -EINVAL;
			goto out;
		}
	} else {
		retval = input_scancode_to_scalar(ke, &scancode);
		if (retval)
			goto out;

		index = ir_establish_scancode(rdev, rc_map, scancode, true);
		if (index >= rc_map->len) {
			retval = -ENOMEM;
			goto out;
		}
	}

	*old_keycode = ir_update_mapping(rdev, rc_map, index, ke->keycode);

out:
	spin_unlock_irqrestore(&rc_map->lock, flags);
	return retval;
}

/**
 * ir_setkeytable() - sets several entries in the scancode->keycode table
 * @dev:	the struct rc_dev device descriptor
 * @to:		the struct rc_map to copy entries to
 * @from:	the struct rc_map to copy entries from
 * @return:	-ENOMEM if all keycodes could not be inserted, otherwise zero.
 *
 * This routine is used to handle table initialization.
 */
static int ir_setkeytable(struct rc_dev *dev,
			  const struct rc_map *from)
{
	struct rc_map *rc_map = &dev->rc_map;
	unsigned int i, index;
	int rc;

	rc = ir_create_table(rc_map, from->name,
			     from->rc_type, from->size);
	if (rc)
		return rc;

	IR_dprintk(1, "Allocated space for %u keycode entries (%u bytes)\n",
		   rc_map->size, rc_map->alloc);

	for (i = 0; i < from->size; i++) {
		index = ir_establish_scancode(dev, rc_map,
					      from->scan[i].scancode, false);
		if (index >= rc_map->len) {
			rc = -ENOMEM;
			break;
		}

		ir_update_mapping(dev, rc_map, index,
				  from->scan[i].keycode);
	}

	if (rc)
		ir_free_table(rc_map);

	return rc;
}

/**
 * ir_lookup_by_scancode() - locate mapping by scancode
 * @rc_map:	the struct rc_map to search
 * @scancode:	scancode to look for in the table
 * @return:	index in the table, -1U if not found
 *
 * This routine performs binary search in RC keykeymap table for
 * given scancode.
 */
static unsigned int ir_lookup_by_scancode(const struct rc_map *rc_map,
					  unsigned int scancode)
{
	int start = 0;
	int end = rc_map->len - 1;
	int mid;

	while (start <= end) {
		mid = (start + end) / 2;
		if (rc_map->scan[mid].scancode < scancode)
			start = mid + 1;
		else if (rc_map->scan[mid].scancode > scancode)
			end = mid - 1;
		else
			return mid;
	}

	return -1U;
}


/**
 * ir_lookup_by_scancode_ccode() - locate mapping by scancode and ccode
 * @rc_map:	the struct rc_map to search
 * @scancode:	scancode to look for in the table
 * @return:	index in the table, -1U if not found
 *
 * This routine performs binary search in RC keykeymap table for
 * given scancode.
 */
static unsigned int ir_lookup_by_scancode_ccode(const struct rc_map *rc_map,
					  unsigned int scancode,unsigned int ccode)
{
	int ccode_num = 0;
	int i;
	int Find_cc_flag = 0;
	
	for (i = 0; i < sizeof(eos_xxh_tv)/sizeof(struct eos_xxh_tv_button); i++)
	{
		if(ccode == eos_xxh_tv[i].ccode)
		{
			Find_cc_flag = 1;
			ccode_num = i;
			break;
		}
	}
	if (!Find_cc_flag)
		goto xxh_err;

	for (i = 0; i < eos_xxh_tv[ccode_num].nbuttons; i++)
	{
		if(scancode == eos_xxh_tv[ccode_num].ir_table[i].scancode)
		{
		//printk("##### xxh##### (ccode=%x , scancode=%x) \n",ccode,scancode); //xxh
			return eos_xxh_tv[ccode_num].ir_table[i].keycode;
		}
	}
	//printk("##### xxh##### (ccode=%x have define,but scancode=%x,not define,please add. ) \n",ccode,scancode); //xxh
	return -1U;
xxh_err:
	//printk("##### xxh##### (ccode=%x,and scancode=%x,not define,please add. ) \n",ccode,scancode); //xxh
	return -1U;	
}

/**
 * ir_getkeycode() - get a keycode from the scancode->keycode table
 * @idev:	the struct input_dev device descriptor
 * @scancode:	the desired scancode
 * @keycode:	used to return the keycode, if found, or KEY_RESERVED
 * @return:	always returns zero.
 *
 * This routine is used to handle evdev EVIOCGKEY ioctl.
 */
static int ir_getkeycode(struct input_dev *idev,
			 struct input_keymap_entry *ke)
{
	struct rc_dev *rdev = input_get_drvdata(idev);
	struct rc_map *rc_map = &rdev->rc_map;
	struct rc_map_table *entry;
	unsigned long flags;
	unsigned int index;
	unsigned int scancode;
	int retval;

	spin_lock_irqsave(&rc_map->lock, flags);

	if (ke->flags & INPUT_KEYMAP_BY_INDEX) {
		index = ke->index;
	} else {
		retval = input_scancode_to_scalar(ke, &scancode);
		if (retval)
			goto out;

		index = ir_lookup_by_scancode(rc_map, scancode);
	}

	if (index < rc_map->len) {
		entry = &rc_map->scan[index];

		ke->index = index;
		ke->keycode = entry->keycode;
		ke->len = sizeof(entry->scancode);
		memcpy(ke->scancode, &entry->scancode, sizeof(entry->scancode));

	} else if (!(ke->flags & INPUT_KEYMAP_BY_INDEX)) {
		/*
		 * We do not really know the valid range of scancodes
		 * so let's respond with KEY_RESERVED to anything we
		 * do not have mapping for [yet].
		 */
		ke->index = index;
		ke->keycode = KEY_RESERVED;
	} else {
		retval = -EINVAL;
		goto out;
	}

	retval = 0;

out:
	spin_unlock_irqrestore(&rc_map->lock, flags);
	return retval;
}

/**
 * rc_g_keycode_from_table() - gets the keycode that corresponds to a scancode
 * @dev:	the struct rc_dev descriptor of the device
 * @scancode:	the scancode to look for
 * @return:	the corresponding keycode, or KEY_RESERVED
 *
 * This routine is used by drivers which need to convert a scancode to a
 * keycode. Normally it should not be used since drivers should have no
 * interest in keycodes.
 */
u32 rc_g_keycode_from_table(struct rc_dev *dev, u32 scancode)
{
	struct rc_map *rc_map = &dev->rc_map;
	unsigned int keycode;
	unsigned int index;
	unsigned long flags;

	spin_lock_irqsave(&rc_map->lock, flags);

	index = ir_lookup_by_scancode(rc_map, scancode);
	keycode = index < rc_map->len ?
			rc_map->scan[index].keycode : KEY_RESERVED;

	spin_unlock_irqrestore(&rc_map->lock, flags);

	if (keycode != KEY_RESERVED)
		IR_dprintk(1, "%s: scancode 0x%04x keycode 0x%02x\n",
			   dev->input_name, scancode, keycode);

	return keycode;
}
EXPORT_SYMBOL_GPL(rc_g_keycode_from_table);


/**
 * rc_g_keycode_from_eos_xxh_table() - gets the keycode that corresponds to a scancode
 * @dev:	the struct rc_dev descriptor of the device
 * @scancode:	the scancode to look for
 * @return:	the corresponding keycode, or KEY_RESERVED
 *
 * This routine is used by drivers which need to convert a scancode to a
 * keycode. Normally it should not be used since drivers should have no
 * interest in keycodes.
 */

u32 rc_g_keycode_from_eos_xxh_table(struct rc_dev *dev, u32 scancode,u32 ccode)
{
	struct rc_map *rc_map = &dev->rc_map;
	unsigned int keycode;
	unsigned int index;
	unsigned long flags;

	spin_lock_irqsave(&rc_map->lock, flags);

	keycode = ir_lookup_by_scancode_ccode(rc_map, scancode,ccode);
	//keycode = index < rc_map->len ?
	//		rc_map->scan[index].keycode : KEY_RESERVED;

	spin_unlock_irqrestore(&rc_map->lock, flags);

	if (keycode != KEY_RESERVED)
	{
		//printk("xxh === %s,%d ===(%s: scancode 0x%04x keycode 0x%02x ) \n",__FUNCTION__,__LINE__,dev->input_name, scancode, keycode); //xxh
		IR_dprintk(1, "%s: scancode 0x%04x keycode 0x%02x\n",
		dev->input_name, scancode, keycode);
	}
	return keycode;
}

EXPORT_SYMBOL_GPL(rc_g_keycode_from_eos_xxh_table);
/**
 * ir_do_keyup() - internal function to signal the release of a keypress
 * @dev:	the struct rc_dev descriptor of the device
 * @sync:	whether or not to call input_sync
 *
 * This function is used internally to release a keypress, it must be
 * called with keylock held.
 */
static void ir_do_keyup(struct rc_dev *dev, bool sync)
{
	if (!dev->keypressed)
		return;

	IR_dprintk(1, "keyup key 0x%04x\n", dev->last_keycode);
	input_report_key(dev->input_dev, dev->last_keycode, 0);
	if (sync)
		input_sync(dev->input_dev);
	dev->keypressed = false;
}

/**
 * rc_keyup() - signals the release of a keypress
 * @dev:	the struct rc_dev descriptor of the device
 *
 * This routine is used to signal that a key has been released on the
 * remote control.
 */
void rc_keyup(struct rc_dev *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->keylock, flags);
	ir_do_keyup(dev, true);
	spin_unlock_irqrestore(&dev->keylock, flags);
}
EXPORT_SYMBOL_GPL(rc_keyup);

/**
 * ir_timer_keyup() - generates a keyup event after a timeout
 * @cookie:	a pointer to the struct rc_dev for the device
 *
 * This routine will generate a keyup event some time after a keydown event
 * is generated when no further activity has been detected.
 */
static void ir_timer_keyup(unsigned long cookie)
{
	struct rc_dev *dev = (struct rc_dev *)cookie;
	unsigned long flags;

	/*
	 * ir->keyup_jiffies is used to prevent a race condition if a
	 * hardware interrupt occurs at this point and the keyup timer
	 * event is moved further into the future as a result.
	 *
	 * The timer will then be reactivated and this function called
	 * again in the future. We need to exit gracefully in that case
	 * to allow the input subsystem to do its auto-repeat magic or
	 * a keyup event might follow immediately after the keydown.
	 */
	spin_lock_irqsave(&dev->keylock, flags);
	if (time_is_before_eq_jiffies(dev->keyup_jiffies))
		ir_do_keyup(dev, true);
	spin_unlock_irqrestore(&dev->keylock, flags);
}

/**
 * rc_repeat() - signals that a key is still pressed
 * @dev:	the struct rc_dev descriptor of the device
 *
 * This routine is used by IR decoders when a repeat message which does
 * not include the necessary bits to reproduce the scancode has been
 * received.
 */
void rc_repeat(struct rc_dev *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->keylock, flags);

	input_event(dev->input_dev, EV_MSC, MSC_SCAN, dev->last_scancode);
	input_sync(dev->input_dev);

	if (!dev->keypressed)
		goto out;

	dev->keyup_jiffies = jiffies + msecs_to_jiffies(IR_KEYPRESS_TIMEOUT);
	mod_timer(&dev->timer_keyup, dev->keyup_jiffies);

out:
	spin_unlock_irqrestore(&dev->keylock, flags);
}
EXPORT_SYMBOL_GPL(rc_repeat);

/**
 * ir_do_keydown() - internal function to process a keypress
 * @dev:	the struct rc_dev descriptor of the device
 * @scancode:   the scancode of the keypress
 * @keycode:    the keycode of the keypress
 * @toggle:     the toggle value of the keypress
 *
 * This function is used internally to register a keypress, it must be
 * called with keylock held.
 */
static void ir_do_keydown(struct rc_dev *dev, int scancode,
			  u32 keycode, u8 toggle)
{
	bool new_event = !dev->keypressed ||
			 dev->last_scancode != scancode ||
			 dev->last_toggle != toggle;

	if (new_event && dev->keypressed)
		ir_do_keyup(dev, false);

	input_event(dev->input_dev, EV_MSC, MSC_SCAN, scancode);

	if (new_event && keycode != KEY_RESERVED) {
		/* Register a keypress */
		dev->keypressed = true;
		dev->last_scancode = scancode;
		dev->last_toggle = toggle;
		dev->last_keycode = keycode;

		IR_dprintk(1, "%s: key down event, "
			   "key 0x%04x, scancode 0x%04x\n",
			   dev->input_name, keycode, scancode);
		input_report_key(dev->input_dev, keycode, 1);
	}

	input_sync(dev->input_dev);
}

/**
 * rc_keydown() - generates input event for a key press
 * @dev:	the struct rc_dev descriptor of the device
 * @scancode:   the scancode that we're seeking
 * @toggle:     the toggle value (protocol dependent, if the protocol doesn't
 *              support toggle values, this should be set to zero)
 *
 * This routine is used to signal that a key has been pressed on the
 * remote control.
 */
void rc_keydown(struct rc_dev *dev, int scancode, u8 toggle)
{
	unsigned long flags;
	u32 keycode = rc_g_keycode_from_table(dev, scancode);

	spin_lock_irqsave(&dev->keylock, flags);
	ir_do_keydown(dev, scancode, keycode, toggle);

	if (dev->keypressed) {
		dev->keyup_jiffies = jiffies + msecs_to_jiffies(IR_KEYPRESS_TIMEOUT);
		mod_timer(&dev->timer_keyup, dev->keyup_jiffies);
	}
	spin_unlock_irqrestore(&dev->keylock, flags);
}
EXPORT_SYMBOL_GPL(rc_keydown);

/**
 * rc_keydown_notimeout() - generates input event for a key press without
 *                          an automatic keyup event at a later time
 * @dev:	the struct rc_dev descriptor of the device
 * @scancode:   the scancode that we're seeking
 * @toggle:     the toggle value (protocol dependent, if the protocol doesn't
 *              support toggle values, this should be set to zero)
 *
 * This routine is used to signal that a key has been pressed on the
 * remote control. The driver must manually call rc_keyup() at a later stage.
 */
void rc_keydown_notimeout(struct rc_dev *dev, int scancode, u8 toggle)
{
	unsigned long flags;
	u32 keycode = rc_g_keycode_from_table(dev, scancode);

	spin_lock_irqsave(&dev->keylock, flags);
	ir_do_keydown(dev, scancode, keycode, toggle);
	spin_unlock_irqrestore(&dev->keylock, flags);
}
EXPORT_SYMBOL_GPL(rc_keydown_notimeout);

/**
 * rc_keydown_eos_xxh_notimeout() - generates input event for a key press without
 *                          an automatic keyup event at a later time
 * @dev:	the struct rc_dev descriptor of the device
 * @scancode:   the scancode that we're seeking
 * @toggle:     the toggle value (protocol dependent, if the protocol doesn't
 *              support toggle values, this should be set to zero)
 *
 * This routine is used to signal that a key has been pressed on the
 * remote control. The driver must manually call rc_keyup() at a later stage.
 */
void rc_keydown_eos_xxh_notimeout(struct rc_dev *dev, int scancode,int ccode, u8 toggle)
{
	unsigned long flags;
	u32 keycode = rc_g_keycode_from_eos_xxh_table(dev, scancode,ccode);

	spin_lock_irqsave(&dev->keylock, flags);
	ir_do_keydown(dev, scancode, keycode, toggle);
	spin_unlock_irqrestore(&dev->keylock, flags);
}
EXPORT_SYMBOL_GPL(rc_keydown_eos_xxh_notimeout);

static int ir_open(struct input_dev *idev)
{
	struct rc_dev *rdev = input_get_drvdata(idev);

	return rdev->open(rdev);
}

static void ir_close(struct input_dev *idev)
{
	struct rc_dev *rdev = input_get_drvdata(idev);

	 if (rdev)
		rdev->close(rdev);
}

/* class for /sys/class/rc */
static char *rc_devnode(struct device *dev, umode_t *mode)
{
	return kasprintf(GFP_KERNEL, "rc/%s", dev_name(dev));
}

static struct class rc_class = {
	.name		= "rc",
	.devnode	= rc_devnode,
};

/*
 * These are the protocol textual descriptions that are
 * used by the sysfs protocols file. Note that the order
 * of the entries is relevant.
 */
static struct {
	u64	type;
	char	*name;
} proto_names[] = {
	{ RC_BIT_NONE,		"none"		},
	{ RC_BIT_OTHER,		"other"		},
	{ RC_BIT_UNKNOWN,	"unknown"	},
	{ RC_BIT_RC5 |
	  RC_BIT_RC5X,		"rc-5"		},
	{ RC_BIT_NEC,		"nec"		},
	{ RC_BIT_RC6_0 |
	  RC_BIT_RC6_6A_20 |
	  RC_BIT_RC6_6A_24 |
	  RC_BIT_RC6_6A_32 |
	  RC_BIT_RC6_MCE,	"rc-6"		},
	{ RC_BIT_JVC,		"jvc"		},
	{ RC_BIT_SONY12 |
	  RC_BIT_SONY15 |
	  RC_BIT_SONY20,	"sony"		},
	{ RC_BIT_RC5_SZ,	"rc-5-sz"	},
	{ RC_BIT_SANYO,		"sanyo"		},
	{ RC_BIT_MCE_KBD,	"mce_kbd"	},
	{ RC_BIT_LIRC,		"lirc"		},
};

/**
 * show_protocols() - shows the current IR protocol(s)
 * @device:	the device descriptor
 * @mattr:	the device attribute struct (unused)
 * @buf:	a pointer to the output buffer
 *
 * This routine is a callback routine for input read the IR protocol type(s).
 * it is trigged by reading /sys/class/rc/rc?/protocols.
 * It returns the protocol names of supported protocols.
 * Enabled protocols are printed in brackets.
 *
 * dev->lock is taken to guard against races between device
 * registration, store_protocols and show_protocols.
 */
static ssize_t show_protocols(struct device *device,
			      struct device_attribute *mattr, char *buf)
{
	struct rc_dev *dev = to_rc_dev(device);
	u64 allowed, enabled;
	char *tmp = buf;
	int i;

	/* Device is being removed */
	if (!dev)
		return -EINVAL;

	mutex_lock(&dev->lock);

	enabled = dev->enabled_protocols;
	if (dev->driver_type == RC_DRIVER_SCANCODE)
		allowed = dev->allowed_protos;
	else if (dev->raw)
		allowed = ir_raw_get_allowed_protocols();
	else {
		mutex_unlock(&dev->lock);
		return -ENODEV;
	}

	IR_dprintk(1, "allowed - 0x%llx, enabled - 0x%llx\n",
		   (long long)allowed,
		   (long long)enabled);

	for (i = 0; i < ARRAY_SIZE(proto_names); i++) {
		if (allowed & enabled & proto_names[i].type)
			tmp += sprintf(tmp, "[%s] ", proto_names[i].name);
		else if (allowed & proto_names[i].type)
			tmp += sprintf(tmp, "%s ", proto_names[i].name);

		if (allowed & proto_names[i].type)
			allowed &= ~proto_names[i].type;
	}

	if (tmp != buf)
		tmp--;
	*tmp = '\n';

	mutex_unlock(&dev->lock);

	return tmp + 1 - buf;
}

/**
 * store_protocols() - changes the current IR protocol(s)
 * @device:	the device descriptor
 * @mattr:	the device attribute struct (unused)
 * @buf:	a pointer to the input buffer
 * @len:	length of the input buffer
 *
 * This routine is for changing the IR protocol type.
 * It is trigged by writing to /sys/class/rc/rc?/protocols.
 * Writing "+proto" will add a protocol to the list of enabled protocols.
 * Writing "-proto" will remove a protocol from the list of enabled protocols.
 * Writing "proto" will enable only "proto".
 * Writing "none" will disable all protocols.
 * Returns -EINVAL if an invalid protocol combination or unknown protocol name
 * is used, otherwise @len.
 *
 * dev->lock is taken to guard against races between device
 * registration, store_protocols and show_protocols.
 */
static ssize_t store_protocols(struct device *device,
			       struct device_attribute *mattr,
			       const char *data,
			       size_t len)
{
	struct rc_dev *dev = to_rc_dev(device);
	bool enable, disable;
	const char *tmp;
	u64 type;
	u64 mask;
	int rc, i, count = 0;
	ssize_t ret;

	/* Device is being removed */
	if (!dev)
		return -EINVAL;

	mutex_lock(&dev->lock);

	if (dev->driver_type != RC_DRIVER_SCANCODE && !dev->raw) {
		IR_dprintk(1, "Protocol switching not supported\n");
		ret = -EINVAL;
		goto out;
	}
	type = dev->enabled_protocols;

	while ((tmp = strsep((char **) &data, " \n")) != NULL) {
		if (!*tmp)
			break;

		if (*tmp == '+') {
			enable = true;
			disable = false;
			tmp++;
		} else if (*tmp == '-') {
			enable = false;
			disable = true;
			tmp++;
		} else {
			enable = false;
			disable = false;
		}

		for (i = 0; i < ARRAY_SIZE(proto_names); i++) {
			if (!strcasecmp(tmp, proto_names[i].name)) {
				mask = proto_names[i].type;
				break;
			}
		}

		if (i == ARRAY_SIZE(proto_names)) {
			IR_dprintk(1, "Unknown protocol: '%s'\n", tmp);
			ret = -EINVAL;
			goto out;
		}

		count++;

		if (enable)
			type |= mask;
		else if (disable)
			type &= ~mask;
		else
			type = mask;
	}

	if (!count) {
		IR_dprintk(1, "Protocol not specified\n");
		ret = -EINVAL;
		goto out;
	}

	if (dev->change_protocol) {
		rc = dev->change_protocol(dev, &type);
		if (rc < 0) {
			IR_dprintk(1, "Error setting protocols to 0x%llx\n",
				   (long long)type);
			ret = -EINVAL;
			goto out;
		}
	}

	dev->enabled_protocols = type;
	IR_dprintk(1, "Current protocol(s): 0x%llx\n",
		   (long long)type);

	ret = len;

out:
	mutex_unlock(&dev->lock);
	return ret;
}

static void rc_dev_release(struct device *device)
{
}

#define ADD_HOTPLUG_VAR(fmt, val...)					\
	do {								\
		int err = add_uevent_var(env, fmt, val);		\
		if (err)						\
			return err;					\
	} while (0)

static int rc_dev_uevent(struct device *device, struct kobj_uevent_env *env)
{
	struct rc_dev *dev = to_rc_dev(device);

	if (!dev || !dev->input_dev)
		return -ENODEV;

	if (dev->rc_map.name)
		ADD_HOTPLUG_VAR("NAME=%s", dev->rc_map.name);
	if (dev->driver_name)
		ADD_HOTPLUG_VAR("DRV_NAME=%s", dev->driver_name);

	return 0;
}

/*
 * Static device attribute struct with the sysfs attributes for IR's
 */
static DEVICE_ATTR(protocols, S_IRUGO | S_IWUSR,
		   show_protocols, store_protocols);

static struct attribute *rc_dev_attrs[] = {
	&dev_attr_protocols.attr,
	NULL,
};

static struct attribute_group rc_dev_attr_grp = {
	.attrs	= rc_dev_attrs,
};

static const struct attribute_group *rc_dev_attr_groups[] = {
	&rc_dev_attr_grp,
	NULL
};

static struct device_type rc_dev_type = {
	.groups		= rc_dev_attr_groups,
	.release	= rc_dev_release,
	.uevent		= rc_dev_uevent,
};

struct rc_dev *rc_allocate_device(void)
{
	struct rc_dev *dev;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return NULL;

	dev->input_dev = input_allocate_device();
	if (!dev->input_dev) {
		kfree(dev);
		return NULL;
	}

	dev->input_dev->getkeycode = ir_getkeycode;
	dev->input_dev->setkeycode = ir_setkeycode;
	input_set_drvdata(dev->input_dev, dev);

	spin_lock_init(&dev->rc_map.lock);
	spin_lock_init(&dev->keylock);
	mutex_init(&dev->lock);
	setup_timer(&dev->timer_keyup, ir_timer_keyup, (unsigned long)dev);

	dev->dev.type = &rc_dev_type;
	dev->dev.class = &rc_class;
	device_initialize(&dev->dev);

	__module_get(THIS_MODULE);
	return dev;
}
EXPORT_SYMBOL_GPL(rc_allocate_device);

void rc_free_device(struct rc_dev *dev)
{
	if (!dev)
		return;

	if (dev->input_dev)
		input_free_device(dev->input_dev);

	put_device(&dev->dev);

	kfree(dev);
	module_put(THIS_MODULE);
}
EXPORT_SYMBOL_GPL(rc_free_device);

int rc_register_device(struct rc_dev *dev)
{
	static bool raw_init = false; /* raw decoders loaded? */
	static atomic_t devno = ATOMIC_INIT(0);
	struct rc_map *rc_map;
	const char *path;
	int rc;

	if (!dev || !dev->map_name)
		return -EINVAL;

	rc_map = rc_map_get(dev->map_name);
	if (!rc_map)
		rc_map = rc_map_get(RC_MAP_EMPTY);
	if (!rc_map || !rc_map->scan || rc_map->size == 0)
		return -EINVAL;

	set_bit(EV_KEY, dev->input_dev->evbit);
	set_bit(EV_REP, dev->input_dev->evbit);
	set_bit(EV_MSC, dev->input_dev->evbit);
	set_bit(MSC_SCAN, dev->input_dev->mscbit);
	if (dev->open)
		dev->input_dev->open = ir_open;
	if (dev->close)
		dev->input_dev->close = ir_close;

	/*
	 * Take the lock here, as the device sysfs node will appear
	 * when device_add() is called, which may trigger an ir-keytable udev
	 * rule, which will in turn call show_protocols and access
	 * dev->enabled_protocols before it has been initialized.
	 */
	mutex_lock(&dev->lock);

	dev->devno = (unsigned long)(atomic_inc_return(&devno) - 1);
	dev_set_name(&dev->dev, "rc%ld", dev->devno);
	dev_set_drvdata(&dev->dev, dev);
	rc = device_add(&dev->dev);
	if (rc)
		goto out_unlock;

	rc = ir_setkeytable(dev, rc_map);
	if (rc)
		goto out_dev;

	dev->input_dev->dev.parent = &dev->dev;
	memcpy(&dev->input_dev->id, &dev->input_id, sizeof(dev->input_id));
	dev->input_dev->phys = dev->input_phys;
	dev->input_dev->name = dev->input_name;
	rc = input_register_device(dev->input_dev);
	if (rc)
		goto out_table;

	/*
	 * Default delay of 250ms is too short for some protocols, especially
	 * since the timeout is currently set to 250ms. Increase it to 500ms,
	 * to avoid wrong repetition of the keycodes. Note that this must be
	 * set after the call to input_register_device().
	 */
	dev->input_dev->rep[REP_DELAY] = 500;

	/*
	 * As a repeat event on protocols like RC-5 and NEC take as long as
	 * 110/114ms, using 33ms as a repeat period is not the right thing
	 * to do.
	 */
	dev->input_dev->rep[REP_PERIOD] = 125;

	path = kobject_get_path(&dev->dev.kobj, GFP_KERNEL);
	printk(KERN_INFO "%s: %s as %s\n",
		dev_name(&dev->dev),
		dev->input_name ? dev->input_name : "Unspecified device",
		path ? path : "N/A");
	kfree(path);

	if (dev->driver_type == RC_DRIVER_IR_RAW) {
		/* Load raw decoders, if they aren't already */
		if (!raw_init) {
			IR_dprintk(1, "Loading raw decoders\n");
			ir_raw_init();
			raw_init = true;
		}
		rc = ir_raw_event_register(dev);
		if (rc < 0)
			goto out_input;
	}

	if (dev->change_protocol) {
		u64 rc_type = (1 << rc_map->rc_type);
		rc = dev->change_protocol(dev, &rc_type);
		if (rc < 0)
			goto out_raw;
		dev->enabled_protocols = rc_type;
	}

	mutex_unlock(&dev->lock);

	IR_dprintk(1, "Registered rc%ld (driver: %s, remote: %s, mode %s)\n",
		   dev->devno,
		   dev->driver_name ? dev->driver_name : "unknown",
		   rc_map->name ? rc_map->name : "unknown",
		   dev->driver_type == RC_DRIVER_IR_RAW ? "raw" : "cooked");

	return 0;

out_raw:
	if (dev->driver_type == RC_DRIVER_IR_RAW)
		ir_raw_event_unregister(dev);
out_input:
	input_unregister_device(dev->input_dev);
	dev->input_dev = NULL;
out_table:
	ir_free_table(&dev->rc_map);
out_dev:
	device_del(&dev->dev);
out_unlock:
	mutex_unlock(&dev->lock);
	return rc;
}
EXPORT_SYMBOL_GPL(rc_register_device);

void rc_unregister_device(struct rc_dev *dev)
{
	if (!dev)
		return;

	del_timer_sync(&dev->timer_keyup);

	if (dev->driver_type == RC_DRIVER_IR_RAW)
		ir_raw_event_unregister(dev);

	/* Freeing the table should also call the stop callback */
	ir_free_table(&dev->rc_map);
	IR_dprintk(1, "Freed keycode table\n");

	input_unregister_device(dev->input_dev);
	dev->input_dev = NULL;

	device_del(&dev->dev);

	rc_free_device(dev);
}

EXPORT_SYMBOL_GPL(rc_unregister_device);

/*
 * Init/exit code for the module. Basically, creates/removes /sys/class/rc
 */

static int __init rc_core_init(void)
{
	int rc = class_register(&rc_class);
	if (rc) {
		printk(KERN_ERR "rc_core: unable to register rc class\n");
		return rc;
	}

	rc_map_register(&empty_map);

	return 0;
}

static void __exit rc_core_exit(void)
{
	class_unregister(&rc_class);
	rc_map_unregister(&empty_map);
}

subsys_initcall(rc_core_init);
module_exit(rc_core_exit);

int rc_core_debug;    /* ir_debug level (0,1,2) */
EXPORT_SYMBOL_GPL(rc_core_debug);
module_param_named(debug, rc_core_debug, int, 0644);

MODULE_AUTHOR("Mauro Carvalho Chehab <mchehab@redhat.com>");
MODULE_LICENSE("GPL");
