#ifndef _sn3DDLPdevDefine_H
#define _sn3DDLPdevDefine_H

#include <tchar.h>
#include <Windows.h>

#define STRING_LENGTH_MAX 1000
#define PACKAGELEN      16
#define PACKAGELEN_HS   1025
namespace sn3DDLPdev
{
typedef enum{
    CMD_NULL 		= 0x00,
    CMD_CLOSE_HDMI 	= 0x01,    /*�ر�hdmi�ڵ��ź������Ҳ���ǲ���Ҫ����źŸ�ͶӰ��*/
    CMD_OPEN_HDMI	= 0x02,    /*����hdmi�ڵ��ź������Ҳ��������źŸ�ͶӰ��*/
    CMD_WHITE		= 0x03,    /*ͶӰһ�Ű�ɫ��ͼƬ*/
    CMD_CROSS		= 0x04,    /*ͶӰһ�Ŵ���ʮ�ֵ�ͼƬ*/
    CMD_RASTER		= 0x05,    /*ͶӰһ�Ź�դͼ*/
    CMD_SCAN  		= 0x06,    /*ͶӰһϵ�й�դͼ������ÿ��ͶӰ���Ժ���ʱһ��ʱ���ٴ������ */
    CMD_SET   		= 0x07,	   /*���ò�������*/
    CMD_INQUIRE 	= 0x08,	   /*��ѯ������滹������������ȷ��Ҫ��ѯʲô���� */
    CMD_VIDEO		= 0x09,    /*�����ⴥ��ģʽΪvideoģʽ��Ҳ���ǹ̶�ʱ������������ɼ� */
    CMD_ORTH_RASTER = 0x0a,	   /*ͶӰ������դ */
    CMD_GREY		= 0x0b,    /*ͶӰ�Ҷ�ͼ */
    CMD_SPECKLE     = 0x0c,    /*ͶӰɢ��ͼ */
    CMD_RED         = 0x0d,    /*ͶӰ��ɫͼƬ */
    CMD_GREEN       = 0x0e,    /*ͶӰ��ɫͼƬ*/
    CMD_BLUE        = 0x0f,    /*ͶӰ��ɫͼƬ */
    CMD_WRITE_USERDATA= 0x10,   /*д�û����ݣ���դ���ݺ��Զ������ݣ�*/
    CMD_READ_USERDATA=0x11,     /*��ȡ�û����ݣ���դ���ݺ��Զ������ݣ�*/
    CMD_TEMP_SET    =0x12,       /*��ʱ���ò��������õĲ��������浽flash�У�����������й�����Ƶ���޸Ĳ���*/
	CMD_BINARY = 0x13,			/*ͶӰ��ֵ����*/
	CMD_TIMER = 0x14,			/*��ʱ��*/
	CMD_SHOW_SPLASH_BY_INDEX = 0x15,/*Ͷָ��splashͼ*/
	CMD_USERDATA = 0x17,       /* �û����ݣ����кź��豸�Ƿ���ܣ� */
	CMD_STRIP_STEP = 0x18,    /* ����ͶӰ���� ����ָ���赥��ͶӰ��Set���*/
	CMD_BLACK = 0x19,         /*ͶӰһ�ź�ɫ��ͼƬ*/

}prot_hid_cmd;

typedef enum
{ 
    SCMD_TRIGGER    = 0x01,  //ͶӰ�������Ҫ����
    SCMD_NO_TRIGGER = 0x02  //ͶӰ�������Ҫ����
}prot_hid_sub_cmd;

typedef enum
    {
        SCMD_DELAY_TIME_SET = 0x01,             /* ͶӰͼƬˢ���ȶ�����ʱ���� */
        SCMD_CAMERA_NUM_SET = 0x02,             /* ����������� */
        SCMD_CAMERA_TYPY_SET = 0x03,            /* ����������ã�����������Ͳ������������*/
        SCMD_VIDEO_PERIOD_SET = 0x04,           /* videoģʽ�Ĺ̶�ʱ�������� */
        SCMD_2ND_DELAY_TIME_SET = 0x05,         /* �ȴ�����ɼ��ʹ����ʱ������ */
        SCMD_LED_STATUS_SET     = 0x06,         /* ����LED�ȵĿ���״̬�������Ƶ�״̬ͨ������������ 0��ȫ�� 1��R�� 2��G�� 3��B�� 4: R�� 5��G�� 6��B�� 7��ȫ���� */
        SCMD_LED_BRIGHTNESS_SET = 0x07,         /* ����LED�ȵ����ȣ�����ֵ���������Ƶ�����ͨ������������R,G,B ��������˳����������� */
        SCMD_TRIGGER_WIDTH_SET  = 0x08,         /* ���ô���������,��λms(1-50)*/
        SCMD_TRIGGER_MODE_SET   = 0x09,         /* ���ô�����ʽ����������0x00�����崥���� ������0x01�����崥����*/
        SCMD_STRIPE_SET         = 0x0a,         /* �������Ƶ���Ϣ*/
        SCMD_FAN_OPENTEMP_SET   = 0x0b,          /* ���÷��ȿ����¶ȣ� <80���϶� ��*/
        SCMD_PROJECT_CUT        = 0x0c,
		SCMD_TRIGGER_ONOFF      = 0x0d,        /* �����Ƿ���������ź�*/ 
		SCMD_TRIGGER_DIV        = 0x0f,        /* ���ô����źŵķ�Ƶϵ��*/ 
		SCMD_TRIGGER_ILLUMATION = 0x10,       /* ���ô����ź��ع�ʱ��*/
		SCMD_TRIGGER_PRE_DARK   = 0x11,        /* ���ô����ź�ǰ�غڵ�ƽʱ��*/
		SCMD_TRIGGER_POST_DARK  = 0x12,        /* ���ô����źź��غڵ�ƽʱ��*/
    }prot_hid_sub_cmd_set;

    typedef enum
    {
        SCMD_VERSION_GET        = 0x01,
        SCMD_DELAY_TIME_GET   	= 0x02,
        SCMD_CAMERA_NUM_GET		= 0x03,
        SCMD_CAMERA_TYPE_GET	= 0x04,
        SCMD_VIDEO_PERIOD_GET	= 0x05,
        SCMD_2ND_DELAY_TIME_GET	= 0x06,
        SCMD_VIDEO_STATUS_GET   = 0x07,
        SCMD_LED_BRIGHTNESS_GET	= 0x08,
        SCMD_TRIGGER_WIDTH_GET  = 0x09,         /* ��ѯ����������,��λms(1-50)*/
        SCMD_TRIGGER_MODE_GET   = 0x0a,         /* ��ѯ������ʽ����������0x00�����崥���� ������0x01�����崥����*/
        SCMD_PROJECTOR_TEMP_GET = 0x0b,         /* ��ȡ��ǰ������¶� */
        SCMD_FAN_OPENTEMP_GET   = 0x0c          /* ��ѯ���ȿ����¶�*/

    }prot_hid_sub_cmd_inquire;

    typedef enum
    {
        RCMD_OK = 0xF0,
        RCMD_ERR = 0xF1,
    }prot_hid_resp_cmd;

	typedef enum
	{
		TRIGGER_PRE        = 0x11,
		TRIGGER_ILLUMATION = 0x10,
		TRIGGER_POST       = 0x12,
	}eTriggerTimeType;
	typedef enum
	{
		DLP_STRIP_MODE = 0x01,
		DLP_SPLASH_MODE = 0x02,
	}eDlpWorkingMode;
	typedef enum
	{  /*����Э�鶨��ȷ����Щö��ֵ*/
		DLP_STRIP_BLACK  = 0x19, 
		DLP_STRIP_RED    = 0x0d,
		DLP_STRIP_GREEN  = 0x0e,
		DLP_STRIP_BLUE   = 0x0f,
		DLP_STRIP_WHITE  = 0x03,
	}eDlpStripColor_e;
    typedef enum
    { //0��ȫ�� 1��R�� 2��G�� 3��B�� 4: R�� 5��G�� 6��B�� 7��ȫ��
        ALL_OFF = 0X00,
        ONLY_R_ON,
        ONLY_G_ON,
        ONLY_B_ON,
        ONLY_R_OFF,
        ONLY_G_OFF,
        ONLY_B_OFF,
        ALL_ON
    }prot_ledstatus;

	typedef enum
	{
		SCMD_START_TIMER = 0x1,
		SCMD_STOP_TIMER = 0x2,
		SCMD_GET_TIME = 0x3,
		SCMD_RESET_TIMER = 0x4,
	}prot_timer_cmd;
}


#endif	//_sn3DDLPdevDefine_H