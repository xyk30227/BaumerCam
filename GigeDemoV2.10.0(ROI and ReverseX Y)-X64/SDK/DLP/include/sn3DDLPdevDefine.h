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
    CMD_CLOSE_HDMI 	= 0x01,    /*关闭hdmi口的信号输出，也就是不需要输出信号给投影机*/
    CMD_OPEN_HDMI	= 0x02,    /*开启hdmi口的信号输出，也就是输出信号给投影机*/
    CMD_WHITE		= 0x03,    /*投影一张白色的图片*/
    CMD_CROSS		= 0x04,    /*投影一张带有十字的图片*/
    CMD_RASTER		= 0x05,    /*投影一张光栅图*/
    CMD_SCAN  		= 0x06,    /*投影一系列光栅图，并且每次投影完以后延时一段时间再触发相机 */
    CMD_SET   		= 0x07,	   /*设置参数命令*/
    CMD_INQUIRE 	= 0x08,	   /*查询命令，后面还有子命令用于确定要查询什么东西 */
    CMD_VIDEO		= 0x09,    /*设置外触发模式为video模式，也就是固定时间间隔触发相机采集 */
    CMD_ORTH_RASTER = 0x0a,	   /*投影正交光栅 */
    CMD_GREY		= 0x0b,    /*投影灰度图 */
    CMD_SPECKLE     = 0x0c,    /*投影散斑图 */
    CMD_RED         = 0x0d,    /*投影红色图片 */
    CMD_GREEN       = 0x0e,    /*投影绿色图片*/
    CMD_BLUE        = 0x0f,    /*投影蓝色图片 */
    CMD_WRITE_USERDATA= 0x10,   /*写用户数据（光栅数据和自定义数据）*/
    CMD_READ_USERDATA=0x11,     /*读取用户数据（光栅数据和自定义数据）*/
    CMD_TEMP_SET    =0x12,       /*临时设置参数，设置的参数不保存到flash中，用于软件运行过程中频繁修改参数*/
	CMD_BINARY = 0x13,			/*投影二值条纹*/
	CMD_TIMER = 0x14,			/*定时器*/
	CMD_SHOW_SPLASH_BY_INDEX = 0x15,/*投指定splash图*/
	CMD_USERDATA = 0x17,       /* 用户数据（序列号和设备是否加密） */
	CMD_STRIP_STEP = 0x18,    /* 单步投影命令 参数指定需单步投影的Set编号*/
	CMD_BLACK = 0x19,         /*投影一张黑色的图片*/

}prot_hid_cmd;

typedef enum
{ 
    SCMD_TRIGGER    = 0x01,  //投影命令后需要触发
    SCMD_NO_TRIGGER = 0x02  //投影命令后不需要触发
}prot_hid_sub_cmd;

typedef enum
    {
        SCMD_DELAY_TIME_SET = 0x01,             /* 投影图片刷新稳定的延时设置 */
        SCMD_CAMERA_NUM_SET = 0x02,             /* 相机个数设置 */
        SCMD_CAMERA_TYPY_SET = 0x03,            /* 相机类型设置（带反馈相机和不带反馈相机）*/
        SCMD_VIDEO_PERIOD_SET = 0x04,           /* video模式的固定时间间隔设置 */
        SCMD_2ND_DELAY_TIME_SET = 0x05,         /* 等待相机采集和传输的时间设置 */
        SCMD_LED_STATUS_SET     = 0x06,         /* 设置LED等的开关状态，各个灯的状态通过参数决定（ 0：全关 1：R开 2：G开 3：B开 4: R关 5：G关 6：B关 7：全开） */
        SCMD_LED_BRIGHTNESS_SET = 0x07,         /* 设置LED等的亮度（电流值），各个灯的亮度通过参数决定（R,G,B 按照这种顺序给出参数） */
        SCMD_TRIGGER_WIDTH_SET  = 0x08,         /* 设置触发脉冲宽度,单位ms(1-50)*/
        SCMD_TRIGGER_MODE_SET   = 0x09,         /* 设置触发方式，（参数是0x00负脉冲触发， 参数是0x01正脉冲触发）*/
        SCMD_STRIPE_SET         = 0x0a,         /* 设置条纹的信息*/
        SCMD_FAN_OPENTEMP_SET   = 0x0b,          /* 设置风扇开启温度（ <80摄氏度 ）*/
        SCMD_PROJECT_CUT        = 0x0c,
		SCMD_TRIGGER_ONOFF      = 0x0d,        /* 设置是否产生触发信号*/ 
		SCMD_TRIGGER_DIV        = 0x0f,        /* 设置触发信号的分频系数*/ 
		SCMD_TRIGGER_ILLUMATION = 0x10,       /* 设置触发信号曝光时间*/
		SCMD_TRIGGER_PRE_DARK   = 0x11,        /* 设置触发信号前沿黑电平时间*/
		SCMD_TRIGGER_POST_DARK  = 0x12,        /* 设置触发信号后沿黑电平时间*/
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
        SCMD_TRIGGER_WIDTH_GET  = 0x09,         /* 查询触发脉冲宽度,单位ms(1-50)*/
        SCMD_TRIGGER_MODE_GET   = 0x0a,         /* 查询触发方式，（参数是0x00负脉冲触发， 参数是0x01正脉冲触发）*/
        SCMD_PROJECTOR_TEMP_GET = 0x0b,         /* 获取当前光机的温度 */
        SCMD_FAN_OPENTEMP_GET   = 0x0c          /* 查询风扇开启温度*/

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
	{  /*根据协议定义确定这些枚举值*/
		DLP_STRIP_BLACK  = 0x19, 
		DLP_STRIP_RED    = 0x0d,
		DLP_STRIP_GREEN  = 0x0e,
		DLP_STRIP_BLUE   = 0x0f,
		DLP_STRIP_WHITE  = 0x03,
	}eDlpStripColor_e;
    typedef enum
    { //0：全关 1：R开 2：G开 3：B开 4: R关 5：G关 6：B关 7：全开
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