//<MStar Software>
//***********************************************************************************
//MStar Software
//Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
//All software, firmware and related documentation herein (��MStar Software��) are intellectual property of MStar Semiconductor, Inc. (��MStar��) and protected by law, including, but not limited to, copyright law and international treaties.  Any use, modification, reproduction, retransmission, or republication of all or part of MStar Software is expressly prohibited, unless prior written permission has been granted by MStar. 
//By accessing, browsing and/or using MStar Software, you acknowledge that you have read, understood, and agree, to be bound by below terms (��Terms��) and to comply with all applicable laws and regulations:
//
//1. MStar shall retain any and all right, ownership and interest to MStar Software and any modification/derivatives thereof.  No right, ownership, or interest to MStar Software and any modification/derivatives thereof is transferred to you under Terms.
//2. You understand that MStar Software might include, incorporate or be supplied together with third party��s software and the use of MStar Software may require additional licenses from third parties.  Therefore, you hereby agree it is your sole responsibility to separately obtain any and all third party right and license necessary for your use of such third party��s software. 
//3. MStar Software and any modification/derivatives thereof shall be deemed as MStar��s confidential information and you agree to keep MStar��s confidential information in strictest confidence and not disclose to any third party.  
//4. MStar Software is provided on an ��AS IS�� basis without warranties of any kind. Any warranties are hereby expressly disclaimed by MStar, including without limitation, any warranties of merchantability, non-infringement of intellectual property rights, fitness for a particular purpose, error free and in conformity with any international standard.  You agree to waive any claim against MStar for any loss, damage, cost or expense that you may incur related to your use of MStar Software.  In no event shall MStar be liable for any direct, indirect, incidental or consequential damages, including without limitation, lost of profit or revenues, lost or damage of data, and unauthorized system use.  You agree that this Section 4 shall still apply without being affected even if MStar Software has been modified by MStar in accordance with your request or instruction for your use, except otherwise agreed by both parties in writing.
//5. If requested, MStar may from time to time provide technical supports or services in relation with MStar Software to you for your use of MStar Software in conjunction with your or your customer��s product (��Services��).  You understand and agree that, except otherwise agreed by both parties in writing, Services are provided on an ��AS IS�� basis and the warranty disclaimer set forth in Section 4 above shall apply.  
//6. Nothing contained herein shall be construed as by implication, estoppels or otherwise: (a) conferring any license or right to use MStar name, trademark, service mark, symbol or any other identification; (b) obligating MStar or any of its affiliates to furnish any person, including without limitation, you and your customers, any assistance of any kind whatsoever, or any information; or (c) conferring any license or right under any intellectual property right.
//7. These terms shall be governed by and construed in accordance with the laws of Taiwan, R.O.C., excluding its conflict of law rules.  Any and all dispute arising out hereof or related hereto shall be finally settled by arbitration referred to the Chinese Arbitration Association, Taipei in accordance with the ROC Arbitration Law and the Arbitration Rules of the Association by three (3) arbitrators appointed in accordance with the said Rules.  The place of arbitration shall be in Taipei, Taiwan and the language shall be English.  The arbitration award shall be final and binding to both parties.
//
//���B�Ҧ��n��B����ά�������(�U�١uMStar Software�v)����MStar Semiconductor, Inc. (�U�١uMStar�v)�����z�]���v�ì������k��(�]�A��������ۧ@�v�k�ΰ�ڱ���)�ҫO�@�A���󥼸gMStar�ƫe�ѭ���i���ϥΡB�ק�B���s�B�ǰe�Τ��}�����T��C
//�@���z�i�J�B�s���Ψϥ�MStar Software�A�z�Y�n���z�w��Ū�B�F�ѨæP�N���U�C���ڡ]�U�١u�����ڡv�^�ҩ���ñN��u�����k�W���W�w�G
//
//1.	MStar���O��MStar Software�Ψ�ק磌���l�ͪ�������P�������v�Q�B�Ҧ��v�ΧQ�q�A�z�å��]�����ڦӨ��o����MStar Software�Ψ�ק磌���l�ͪ�������P�������v�Q�B�Ҧ��v�ΧQ�q�C
//2.	�z�F��MStar Software�i��t���ε��X���ݩ�ĤT�H���n��ΫY�P�ĤT�H���n��@�ִ��ѡA�Өϥ�MStar Software�i��ݥt��V�ĤT�H���o���v�A�]���z�P�N�z�N�ۦ�t�d�V�����ĤT�H���o���v�H�X�k�ϥ�MStar Software�C
//3.	MStar Software�Ψ�ק磌���l�ͪ����Q����MStar�����K��T�A�z�P�N�N�H�̾��K�O�sMStar�����K��T�B���N�����S������ĤT�H�C
//4.	MStar Software�Y�u�̲{���v�Ҵ��ѦӵL�����O�CMStar�󦹧_�{��MStar Software���ѥ����O�A�]�A��������i�ӫ~�ơB���I�v�B�ŦX�S�w�ϥΥت��B�L�岫�βŦX�����ڼзǤ���O�C�z�P�N�N���|��MStar�D�i�z�]�ϥ�MStar Software�ҥͤ�����l���B�l�`�B�O�ΩΤ�X�C����󱡪p�U�AMStar��󪽱����B�������B���a���Υ��M���l�`�����t�d���A�]�A��������Q���禬�l���B��Ƥ����l�򥢤Ψt�γQ���g���v�ϥΡC�z�æP�N�A������t���ѭ���ĳ�~�A�Y��MStar���̱z���n�D�Ϋ��ܦӭק�MStar Software�A����4�����W�w���~��A�ΦӤ����v�T�C
//5.	�p�g�n�D�AMStar���ɱN���ѧ޳N�䴩�ΪA�Ȥ��z�A�H�Q�z�����~�i�H�PMStar Software�@�P�ϥ�(�U�١u�A�ȡv)�A�z�F�ѨæP�N�A������t���ѭ���ĳ�~�A�Ҧ��A�ȧ��Y�u�H�{���v���ѡA��4���������Ѿ�O�����W�w�����A�Τ��C
//6.	�����ڤ�������ڤ��o�Q������(�L�ר��q�ܡB�T�Ϩ���h�Ψ䥦)�G(a) �¤������v�Q�H�ϥ�MStar���W�١B�ӼСB�A�ȼг��B�Ÿ��Ψ䥦�ѧO�Ϲ��F(b)�Ҥ�MStar�Ψ����Y���~���Ѥ�����H(�]�A��������z�αz���Ȥ�)����Φ�����U�θ�T���q�ȡF��(c) �¤����󴼼z�]���v�C
//7.	���������̤��إ���k�߬��Ǿڪk(���t��Ĭ�k�h)�C�����󥻱��کҥͩλP�����ڬ�������ĳ�̲����̤��إ������k�θӨ�|������W�h�ѨM�A�������3�W����H�H�^��b�x�W�x�_�i��A����H���̤��إ�������|������W�h��X�A����P�_�����ק����B�����觡������O�C
//***********************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef IR_FORMAT_H
#define IR_FORMAT_H

//*************************************************************************
// Customer IR Specification parameter define (Please modify them by IR SPEC)
//*************************************************************************
#define IR_MODE_SEL           IR_TYPE_HWDECODE_FULL_MODE//IR_TYPE_HWDECODE_FULL_MODE//IR_TYPE_SWDECODE_MODE//IR_TYPE_SWDECODE_MODE//IR_TYPE_HWDECODE_FULL_MODE//IR_TYPE_FULLDECODE_MODE
#define IR_CHANNEL_USE_AS_UPDOWN   0
#define IR_VOLUME_USE_AS_LEFTRIGHT      0
// IR Header code define
// EosTek Patch Begin
#define IR_HEADER_CODE0         0x09    // Custom 0     //0x04
#define IR_HEADER_CODE1         0xF6    // Custom 1     //0xFB
// EosTek Patch End
//--------------------------------------------------
// [Function] IR NEC 2nd customer code support
// [Support] Chip series after T8/T9 included can support 
// (CODE20!=0xFF) || (CODE21!=0xFF) ==> enable
// (CODE20==0xFF) && (CODE21==0xFF) ==> disable
// default set to disable
#define IR_HEADER_CODE20        0xFF    // NEC 2nd Custom 0 
#define IR_HEADER_CODE21        0xFF    // NEC 2nd Custom 1

// IR Timing define
#define IR_HEADER_CODE_TIME     9000    // us
#define IR_OFF_CODE_TIME        4500    // us
#define IR_OFF_CODE_RP_TIME     2500    // us
#define IR_LOGI_01H_TIME        560     // us
#define IR_LOGI_0_TIME          1120    // us
#define IR_LOGI_1_TIME          2240    // us
#define IR_TIMEOUT_CYC          140000  // us

#define IR_HEADER_CODE_TIME_UB  20
#define IR_HEADER_CODE_TIME_LB  -20
#define IR_OFF_CODE_TIME_UB  20
#define IR_OFF_CODE_TIME_LB  -20
#define IR_OFF_CODE_RP_TIME_UB  20
#define IR_OFF_CODE_RP_TIME_LB  -20
#define IR_LOGI_01H_TIME_UB  35
#define IR_LOGI_01H_TIME_LB  -30
#define IR_LOGI_0_TIME_UB  20
#define IR_LOGI_0_TIME_LB  -20
#define IR_LOGI_1_TIME_UB  20
#define IR_LOGI_1_TIME_LB  -20
// IR Format define
#define IRKEY_DUMY              0xFF
#define IRDA_KEY_MAPPING_POWER  IRKEY_POWER

#define IR_LEADER_CODE_CHECKING_OPTION 0xBF
#define ENABLE_IR_MSTAR_SOURCE_HOTKEY   0
typedef enum _IrCommandType
{
    IRKEY_TV_ANTENNA        = 0x0C,
#ifndef ENABLE_DMP
    IRKEY_TV_RADIO          = 0x03,//same as IRKEY_PAGE_UP
#endif
    IRKEY_CHANNEL_LIST      = 0x10,
    IRKEY_CHANNEL_FAV_LIST  = 0x08,
    IRKEY_CHANNEL_RETURN    = 0x5C,
    IRKEY_CHANNEL_PLUS      = 0x1F,
    IRKEY_CHANNEL_MINUS     = 0x19,

    IRKEY_AUDIO             = 0x44,
    IRKEY_VOLUME_PLUS       = 0x16,
    IRKEY_VOLUME_MINUS      = 0x15,

    IRKEY_UP                = 0x52,
    // EosTek Patch Begin
    IRKEY_POWER             = 0x45,
    // EosTek Patch End
    IRKEY_EXIT              = 0x1B,
    IRKEY_MENU              = 0x07,
    IRKEY_DOWN              = 0x13,
    IRKEY_LEFT              = 0x06,
    IRKEY_SELECT            = 0x0F,
    IRKEY_RIGHT             = 0x1A,

    IRKEY_NUM_0             = 0x50,
    IRKEY_NUM_1             = 0x49,
    IRKEY_NUM_2             = 0x55,
    IRKEY_NUM_3             = 0x59,
    IRKEY_NUM_4             = 0x4D,
    IRKEY_NUM_5             = 0x51,
    IRKEY_NUM_6             = 0x5D,
    IRKEY_NUM_7             = 0x48,
    IRKEY_NUM_8             = 0x54,
    IRKEY_NUM_9             = 0x58,

    IRKEY_MUTE              = 0x5A,
    IRKEY_FREEZE            = 0x4E,
#ifdef ENABLE_DMP
    IRKEY_PAGE_UP           = 0x03,
#endif
    IRKEY_PAGE_DOWN         = 0x05,
    IRKEY_CLOCK             = 0x5F,

    IRKEY_INFO              = 0x14,
    IRKEY_RED               = 0x47,
    IRKEY_GREEN             = 0x4B,
    IRKEY_YELLOW            = 0x57,
    IRKEY_BLUE              = 0x5B,
    IRKEY_MTS               = 0x41,
    IRKEY_NINE_LATTICE      = IRKEY_DUMY,
    IRKEY_TTX               = 0x0A,
    IRKEY_CC                = 0x09,
    IRKEY_INPUT_SOURCE      = 0x04,
    IRKEY_CRADRD            = IRKEY_DUMY-1,
    IRKEY_PICTURE           = 0x40,
    IRKEY_ZOOM              = 0x4C,
#if ENABLE_IR_MSTAR_SOURCE_HOTKEY
    IRKEY_AV                = 0x4E,
    IRKEY_HDMI              = 0x02,
    IRKEY_SCART             = 0x1E,
    IRKEY_PC                = 0x01,
    IRKEY_DTV               = 0x0D,
    IRKEY_TV                = 0x11,
    IRKEY_COMPONENT         = 0x1D,
    IRKEY_SV                = 0X17,

    IRKEY_DASH              = IRKEY_DUMY-7,  // no use
    IRKEY_BACKWARD          = IRKEY_DUMY-8,  // no use
    IRKEY_FORWARD           = IRKEY_DUMY-9, // no use
    IRKEY_PLAY              = IRKEY_DUMY-10, // no use
    IRKEY_RECORD            = IRKEY_DUMY-11, // no use
    IRKEY_STOP              = IRKEY_DUMY-12, // no use
    IRKEY_PAUSE             = IRKEY_DUMY-13, // no use
    IRKEY_MEMORY_RECALL 	= IRKEY_DUMY-14, // no use
#else
    IRKEY_DASH              = IRKEY_DUMY-15,
    IRKEY_BACKWARD          = 0x02,
    IRKEY_FORWARD           = 0x1E,
    IRKEY_PLAY              = 0x01,
    IRKEY_RECORD            = 0x0D,
    IRKEY_STOP              = 0x11,
    IRKEY_PAUSE             = 0x1D,
    IRKEY_MEMORY_RECALL 	  = 0X17,

    IRKEY_AV                = IRKEY_DUMY-7, // no use
    IRKEY_HDMI              = IRKEY_DUMY-8, // no use
    IRKEY_SCART             = IRKEY_DUMY-9, // no use
    IRKEY_PC                = IRKEY_DUMY-10, // no use
    IRKEY_DTV               = IRKEY_DUMY-11, // no use
    IRKEY_TV                = IRKEY_DUMY-12, // no use
    IRKEY_COMPONENT  = IRKEY_DUMY-13, // no use
    IRKEY_SV                = IRKEY_DUMY-14, // no use
#endif
    IRKEY_SLEEP             = 0x52,
    IRKEY_EPG               = 0x4A,

    IRKEY_P_CHECK           = 0x57,
    IRKEY_S_CHECK           = 0x5b,

  	IRKEY_MIX               = 0x1C,
    IRKEY_INDEX             = 0x18,
    IRKEY_HOLD              = 0x00,
    IRKEY_PREVIOUS          = 0x0E,
    IRKEY_NEXT              = 0x12,
  //IRKEY_BRIGHTNESS_PLUS   = 0x0E,
  //IRKEY_BRIGHTNESS_MINUS  = 0x12,

    IRKEY_POWERONLY         = 0xFE,

    IRKEY_TTX_MODE          = 0x22,
    IRKEY_RED2              = 0x72,
    IRKEY_GREEN2            = 0x71,
    IRKEY_UPDATE            = 0x0C,
    IRKEY_SUBTITLE          = 0x53,
//  IRKEY_SUBCODE           = 0x53,
    IRKEY_TIME           	  = 0x26,

    IRKEY_SIZE              = 0x43,
    IRKEY_REVEAL            = 0x4F,
    IRKEY_RETURN            = 0x00,
    IRKEY_ADJUST            = IRKEY_DUMY-2,
    IRKEY_TV_INPUT          = IRKEY_DUMY-3,
    IRKEY_KEY_DISABLE_KEYPAD = IRKEY_DUMY-4,
    IRKEY_BACK              = IRKEY_DUMY-5,
    IRKEY_SUBPAGE   =   IRKEY_DUMY-6,


}IrCommandType;
//*************************************************************************
#endif

