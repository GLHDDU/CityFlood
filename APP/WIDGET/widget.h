#ifndef _WIDGET_h_
#define _WIDGET_h_

#include "sys.h"

//调节控件（1:开  0:关）
typedef struct
{
	char Drainage_machine1;//排水机
	char Water_level_alarm1;//水位警报
	char Rainfall_alarm1;//降雨警报
	char Water_quality_alarm1;//水质警报
	
	char Drainage_machine2;//排水机
	char Water_level_alarm2;//水位警报
	char Rainfall_alarm2;//降雨警报
	char Water_quality_alarm2;//水质警报
	
	char Drainage_machine3;//排水机
	char Water_level_alarm3;//水位警报
	char Rainfall_alarm3;//降雨警报
	char Water_quality_alarm3;//水质警报
	
}AJ_widget_t;

void Clear_AJ_widget_SW(void);

void AJ_widgets_Init(void);

void Drainage_machine1_ON(void);//开关排水机及水位警报器
void Drainage_machine1_OFF(void);
void Rainfall_alarm1_ON(void);//开关降雨警报指示灯
void Rainfall_alarm1_OFF(void);
void Water_quality_alarm1_ON(void);//开关水质报警灯
void Water_quality_alarm1_OFF(void);
void Water_level_alarm1_ON(void);//开关水位警报器
void Water_level_alarm1_OFF(void);
///////////////////2///////////////////
void Drainage_machine2_ON(void);//开关排水机及水位警报器
void Drainage_machine2_OFF(void);
void Rainfall_alarm2_ON(void);//开关降雨警报指示灯
void Rainfall_alarm2_OFF(void);
void Water_quality_alarm2_ON(void);//开关水质报警灯
void Water_quality_alarm2_OFF(void);
void Water_level_alarm2_ON(void);//开关水位警报器
void Water_level_alarm2_OFF(void);
///////////////////3///////////////
void Drainage_machine3_ON(void);//开关排水机及水位警报器
void Drainage_machine3_OFF(void);
void Rainfall_alarm3_ON(void);//开关降雨警报指示灯
void Rainfall_alarm3_OFF(void);
void Water_quality_alarm3_ON(void);//开关水质报警灯
void Water_quality_alarm3_OFF(void);
void Water_level_alarm3_ON(void);//开关水位警报器
void Water_level_alarm3_OFF(void);
#endif
