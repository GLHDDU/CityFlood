#ifndef _SENSORS_h_
#define _SENSORS_h_

#include "sys.h"

//各项环境指标阈值
#define WaterLevel1_Max   100
#define Rainfall_index1_Max   100
#define water_quality1_Max 100

//传感器数据
typedef struct
{	
	int WaterLevel1;		//水位
	int Rainfall_index1; //降雨指数
	int Current_temperature1;		//环境温度
	int Current_humidity1;			//环境湿度
	int water_quality1;		//水质浊度

	int WaterLevel2;		//水位
	int Rainfall_index2; //降雨指数
	int Current_temperature2;		//环境温度
	int Current_humidity2;			//环境湿度
	int water_quality2;		//水质浊度

	int WaterLevel3;		//水位
	int Rainfall_index3; //降雨指数
	int Current_temperature3;		//环境温度
	int Current_humidity3;			//环境湿度
	int water_quality3;		//水质浊度	
	
}Sensor_Data_t;


u8 Sensors_Init(void);
u8 Water_Level_Sensor_Init(void);
u8 Soil_Moisture_Sensor_Init(void);
u8 Air_Quality_Sensor_Init(void);
u8 Raindrop_Sensor_Init(void);

void Get_Sensors_Data(Sensor_Data_t *Sensor_Data);
void SensorData_Save(void);
uint16_t SensorData_IsEqual(void);

#endif
