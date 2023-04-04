#include "Sensors.h"
#include "dht11.h"
#include "timer6.h"
#include "USART3.h"
extern u8  USART3_RX_ABUF[USART3_MAX_RECV_LEN]; 
extern u8  USART3_RX_BBUF[USART3_MAX_RECV_LEN]; 
extern u8  USART3_RX_CBUF[USART3_MAX_RECV_LEN]; 

//����������
Sensor_Data_t Sensor_Data;
Sensor_Data_t Last_Sensor_Data;

/*���д����� ��ʼ��*/
u8 Sensors_Init(void)
{	
	//TIM6_Init();								//��ʱ��ȡ����
	
	while(!(Water_Level_Sensor_Init()&&			//ˮλ������ ��ʼ��
					Soil_Moisture_Sensor_Init()&&		//����ʪ�ȴ����� ��ʼ��
					Air_Quality_Sensor_Init()&&			//�������������� ��ʼ��
					Raindrop_Sensor_Init()))				//��δ����� ��ʼ��
	{
		printf("Sensors initialized fail!\r\n");
	}

	printf("Sensors initialized seccess!\r\n");
	
	return 1;
		
}


/*��ȡ����������*/
void Get_Sensors_Data(Sensor_Data_t *Sensor_Data)
{	
/////////////////1//////////////////////	
	sscanf((const char *)USART3_RX_ABUF,"%2d",&(Sensor_Data->Current_temperature1));
	sscanf((const char *)USART3_RX_ABUF+3,"%2d",&(Sensor_Data->Current_humidity1));
	sscanf((const char *)USART3_RX_ABUF+8,"%2d",&(Sensor_Data->WaterLevel1));
	//Sensor_Data->WaterLevel1=Sensor_Data->WaterLevel1*29;
	sscanf((const char *)USART3_RX_ABUF+10,"%2d",&(Sensor_Data->Rainfall_index1));
//	Sensor_Data->Rainfall_index1=Sensor_Data->Rainfall_index1*29;
	sscanf((const char *)USART3_RX_ABUF+12,"%2d",&(Sensor_Data->water_quality1));
//	Sensor_Data->water_quality1=Sensor_Data->water_quality1*29;
	
	printf("TMEP:%d\n HUMI:%d\n LEVEL:%d\n RAINFALL:%d\n QUATY:%d\n\r",
	Sensor_Data->Current_temperature1,Sensor_Data->Current_humidity1,Sensor_Data->WaterLevel1,Sensor_Data->Rainfall_index1,Sensor_Data->water_quality1);	
	printf("-------------------------1\r\n");
	////////////////2/////////////////////////
		sscanf((const char *)USART3_RX_BBUF,"%2d",&(Sensor_Data->Current_temperature2));
	sscanf((const char *)USART3_RX_BBUF+3,"%2d",&(Sensor_Data->Current_humidity2));
	sscanf((const char *)USART3_RX_BBUF+8,"%2d",&(Sensor_Data->WaterLevel2));
//	Sensor_Data->WaterLevel2=Sensor_Data->WaterLevel2*29;
	sscanf((const char *)USART3_RX_BBUF+10,"%2d",&(Sensor_Data->Rainfall_index2));
//	Sensor_Data->Rainfall_index2=Sensor_Data->Rainfall_index2*29;
	sscanf((const char *)USART3_RX_BBUF+12,"%2d",&(Sensor_Data->water_quality2));
//	Sensor_Data->water_quality2=Sensor_Data->water_quality2*29;
	
	printf("TMEP:%d\n HUMI:%d\n LEVEL:%d\n RAINFALL:%d\n QUATY:%d\n\r",
	Sensor_Data->Current_temperature2,Sensor_Data->Current_humidity2,Sensor_Data->WaterLevel2,Sensor_Data->Rainfall_index2,Sensor_Data->water_quality2);	
	printf("-------------------------2\r\n");
	//////////////////3///////////////////////
		sscanf((const char *)USART3_RX_CBUF,"%2d",&(Sensor_Data->Current_temperature3));
	sscanf((const char *)USART3_RX_CBUF+3,"%2d",&(Sensor_Data->Current_humidity3));
	sscanf((const char *)USART3_RX_CBUF+8,"%2d",&(Sensor_Data->WaterLevel3));
//	Sensor_Data->WaterLevel3=Sensor_Data->WaterLevel3*29;
	sscanf((const char *)USART3_RX_CBUF+10,"%2d",&(Sensor_Data->Rainfall_index3));
//	Sensor_Data->Rainfall_index3=Sensor_Data->Rainfall_index3*29;
	sscanf((const char *)USART3_RX_CBUF+12,"%2d",&(Sensor_Data->water_quality3));
//	Sensor_Data->water_quality3=Sensor_Data->water_quality3*29;
	
	printf("TMEP:%d\n HUMI:%d\n LEVEL:%d\n RAINFALL:%d\n QUATY:%d\n\r",
	Sensor_Data->Current_temperature3,Sensor_Data->Current_humidity3,Sensor_Data->WaterLevel3,Sensor_Data->Rainfall_index3,Sensor_Data->water_quality3);	
	printf("-------------------------3\r\n");
	/*//1����ȡˮλ����
		//printf("1����ȡˮλ����..\r\n");
		Sensor_Data->Water_Level=100;//ģ�⸳ֵ
	
	//2����ȡ����ʪ��
		//printf("2����ȡ����ʪ��..\r\n");
		Sensor_Data->Soil_Moisture=200;//ģ�⸳ֵ
	
	//3����ȡ��������
		//printf("3����ȡ��������..\r\n");
		Sensor_Data->Air_Quality=300;//ģ�⸳ֵ
	
	//4����ȡ���
		//printf("4����ȡ���..\r\n");	
		Sensor_Data->Raindrop=400;//ģ�⸳ֵ
	
	//5����ȡ����ʪ��
		//printf("��ȡ����ʪ��..\r\n");	
		Sensor_Data->Humidity=500;//ģ�⸳ֵ
	
	//5����ȡ�����¶�
		//printf("��ȡ�����¶�..\r\n");	
		Sensor_Data->Temperature=600;	//ģ�⸳ֵ
		*/
		
}


/*ˮλ������ ��ʼ��*/
u8 Water_Level_Sensor_Init(void)
{
	
	return 1;//seccess
}

/*����ʪ�ȴ����� ��ʼ��*/
u8 Soil_Moisture_Sensor_Init(void)
{
	
	return 1;//seccess
}

/*�������������� ��ʼ��*/
u8 Air_Quality_Sensor_Init(void)
{
	
	return 1;//seccess
}

/*��δ����� ��ʼ��*/
u8 Raindrop_Sensor_Init(void)
{
	
	return 1;//seccess
}


//�����ϴδ���������
void SensorData_Save(void)
{
		Last_Sensor_Data.WaterLevel1          =Sensor_Data.WaterLevel1;
		Last_Sensor_Data.Rainfall_index1	    =Sensor_Data.Rainfall_index1;
		Last_Sensor_Data.Current_temperature1 =Sensor_Data.Current_temperature1;
		Last_Sensor_Data.Current_humidity1    =Sensor_Data.Current_humidity1;
	  Last_Sensor_Data.water_quality1       =Sensor_Data.water_quality1;
	
	  Last_Sensor_Data.WaterLevel2          =Sensor_Data.WaterLevel2;
		Last_Sensor_Data.Rainfall_index2	    =Sensor_Data.Rainfall_index2;
		Last_Sensor_Data.Current_temperature2 =Sensor_Data.Current_temperature2;
		Last_Sensor_Data.Current_humidity2    =Sensor_Data.Current_humidity2;
	  Last_Sensor_Data.water_quality2       =Sensor_Data.water_quality2;
	
		Last_Sensor_Data.WaterLevel3          =Sensor_Data.WaterLevel3;
		Last_Sensor_Data.Rainfall_index3	    =Sensor_Data.Rainfall_index3;
		Last_Sensor_Data.Current_temperature3 =Sensor_Data.Current_temperature3;
		Last_Sensor_Data.Current_humidity3    =Sensor_Data.Current_humidity3;
	  Last_Sensor_Data.water_quality3       =Sensor_Data.water_quality3;
}


//�ж�ǰ�����δ����������Ƿ���ȣ�ֻ�����ݱ仯���ϴ���
uint16_t SensorData_IsEqual(void)
{
	if(		Last_Sensor_Data.WaterLevel1          ==Sensor_Data.WaterLevel1&&
				Last_Sensor_Data.Rainfall_index1	    ==Sensor_Data.Rainfall_index1&&
				Last_Sensor_Data.Current_temperature1 ==Sensor_Data.Current_temperature1&&
				Last_Sensor_Data.Current_humidity1    ==Sensor_Data.Current_humidity1&&
				Last_Sensor_Data.water_quality1       ==Sensor_Data.water_quality1&&
			
				Last_Sensor_Data.WaterLevel2          ==Sensor_Data.WaterLevel2&&
				Last_Sensor_Data.Rainfall_index2	    ==Sensor_Data.Rainfall_index2&&
				Last_Sensor_Data.Current_temperature2 ==Sensor_Data.Current_temperature2&&
				Last_Sensor_Data.Current_humidity2    ==Sensor_Data.Current_humidity2&&
				Last_Sensor_Data.water_quality2       ==Sensor_Data.water_quality2&&
			
				Last_Sensor_Data.WaterLevel3          ==Sensor_Data.WaterLevel3&&
				Last_Sensor_Data.Rainfall_index3	    ==Sensor_Data.Rainfall_index3&&
				Last_Sensor_Data.Current_temperature3 ==Sensor_Data.Current_temperature3&&
				Last_Sensor_Data.Current_humidity3    ==Sensor_Data.Current_humidity3&&
				Last_Sensor_Data.water_quality3       ==Sensor_Data.water_quality3)
		return 1;
	else
	  return 0; 
}


