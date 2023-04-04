#ifndef _SENSORS_h_
#define _SENSORS_h_

#include "sys.h"

//�����ָ����ֵ
#define WaterLevel1_Max   100
#define Rainfall_index1_Max   100
#define water_quality1_Max 100

//����������
typedef struct
{	
	int WaterLevel1;		//ˮλ
	int Rainfall_index1; //����ָ��
	int Current_temperature1;		//�����¶�
	int Current_humidity1;			//����ʪ��
	int water_quality1;		//ˮ���Ƕ�

	int WaterLevel2;		//ˮλ
	int Rainfall_index2; //����ָ��
	int Current_temperature2;		//�����¶�
	int Current_humidity2;			//����ʪ��
	int water_quality2;		//ˮ���Ƕ�

	int WaterLevel3;		//ˮλ
	int Rainfall_index3; //����ָ��
	int Current_temperature3;		//�����¶�
	int Current_humidity3;			//����ʪ��
	int water_quality3;		//ˮ���Ƕ�	
	
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
