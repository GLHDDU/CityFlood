#include "Adjustment_task.h"
#include "queue.h"
#include "main.h"
#include "widget.h"
#include "sensors.h"
#include "lcd.h"
#include "usart3.h"
#include "uart5.h"
//����������
extern Sensor_Data_t Sensor_Data;			//����

//���ڿؼ�����	
extern AJ_widget_t AJ_widget_SW;				//����
extern AJ_widget_t Last_AJ_widget_SW;		//�ϴ�

//�Զ����ڱ�־λ
char IsAuto_flash=Manual;

//������������
void Adjustment_task(void *pvParameters)
{
	printf("Adjustment_task\r\n");
	usart3_init(115200);
	//��������ʼ��
	//while(!Sensors_Init());
	
	//���ڿؼ���ʼ��
	AJ_widgets_Init();
	
	while(1)
	{
		 //�Զ�����
		 if(IsAuto_flash==Auto)
		 {
			 LCD_Fill(6,101,62,155,LIGHTBLUE);	
			 //////////////////////1///////////////////////////
			 /*ˮλ���� -�򿪳�ˮ����ˮλ����*/
			 if((Sensor_Data.WaterLevel1 > WaterLevel1_Max)&&
					(Last_AJ_widget_SW.Drainage_machine1 == AJ_OFF))
			 {
				// AJ_widget_SW.Drainage_machine1 == AJ_ON
				// AJ_widget_SW.Water_level_alarm1 == AJ_ON
				 Drainage_machine1_ON();
				 Voice_control(0x01);
			 } 
			 /*ˮλ���� -�رճ�ˮ����ˮλ����*/
			 if(Sensor_Data.WaterLevel1 < WaterLevel1_Max&&
					 Last_AJ_widget_SW.Drainage_machine1 == AJ_ON)
			 {
				// AJ_widget_SW.Drainage_machine1 == AJ_OFF
				// AJ_widget_SW.Water_level_alarm1 == AJ_OFF		
         Drainage_machine1_OFF();	
         Voice_control(0x0E);				 
			 }
			 
			 /*����ָ������ -�����걨����*/
			 if((Sensor_Data.Rainfall_index1 > Rainfall_index1_Max)&&
					(Last_AJ_widget_SW.Rainfall_alarm1 == AJ_OFF))
			 {
				// AJ_widget_SW.Rainfall_alarm1 == AJ_ON;
				 Rainfall_alarm1_ON();
				 Voice_control(0x07);
			 }
			 /*����ָ������ -�ؽ��걨����*/
			 if((Sensor_Data.Rainfall_index1 < Rainfall_index1_Max)&&
					(Last_AJ_widget_SW.Rainfall_alarm1 == AJ_ON))
			 {
				 Rainfall_alarm1_OFF();
				 Voice_control(0x1A);
			 }
			 
			 /*ˮ������̫�� -��ˮ�ʾ�����*/
			 if((Sensor_Data.water_quality1 > water_quality1_Max)&&
					(Last_AJ_widget_SW.Water_quality_alarm1 == AJ_OFF))
			 {
				 Water_quality_alarm1_ON();
				 Voice_control(0x0A);
			 }
			 /*ˮ����������-��ˮ�ʾ����� -*/
			 if((Sensor_Data.water_quality1 < water_quality1_Max)&&
					(Last_AJ_widget_SW.Water_quality_alarm1 == AJ_ON))
			 {
				Water_quality_alarm1_OFF();
				 Voice_control(0x20);
			 }		 
			 
			 //////////////////2/////////////////////////
			 /*ˮλ���� -�򿪳�ˮ����ˮλ����*/
			 if((Sensor_Data.WaterLevel2 > WaterLevel1_Max)&&
					(Last_AJ_widget_SW.Drainage_machine2 == AJ_OFF))
			 {
				// AJ_widget_SW.Drainage_machine1 == AJ_ON
				// AJ_widget_SW.Water_level_alarm1 == AJ_ON
				 Drainage_machine2_ON();
				 Voice_control(0x02);
			 } 
			 /*ˮλ���� -�رճ�ˮ����ˮλ����*/
			 if(Sensor_Data.WaterLevel2 < WaterLevel1_Max&&
					 Last_AJ_widget_SW.Drainage_machine2 == AJ_ON)
			 {
				// AJ_widget_SW.Drainage_machine1 == AJ_OFF
				// AJ_widget_SW.Water_level_alarm1 == AJ_OFF		
         Drainage_machine2_OFF();	
Voice_control(0x16);				 
			 }
			 
			 /*����ָ������ -�����걨����*/
			 if((Sensor_Data.Rainfall_index2 > Rainfall_index1_Max)&&
					(Last_AJ_widget_SW.Rainfall_alarm2 == AJ_OFF))
			 {
				// AJ_widget_SW.Rainfall_alarm1 == AJ_ON;
				 Rainfall_alarm2_ON();
				 Voice_control(0x08);
			 }
			 /*����ָ������ -�ؽ��걨����*/
			 if((Sensor_Data.Rainfall_index2 < Rainfall_index1_Max)&&
					(Last_AJ_widget_SW.Rainfall_alarm2 == AJ_ON))
			 {
				 Rainfall_alarm2_OFF();
				 Voice_control(0x1C);
				 
			 }
			 
			 /*ˮ������̫�� -��ˮ�ʾ�����*/
			 if((Sensor_Data.water_quality2 > water_quality1_Max)&&
					(Last_AJ_widget_SW.Water_quality_alarm2 == AJ_OFF))
			 {
				 Water_quality_alarm2_ON();
				 Voice_control(0x0B);
			 }
			 /*ˮ����������-��ˮ�ʾ����� -*/
			 if((Sensor_Data.water_quality2 < water_quality1_Max)&&
					(Last_AJ_widget_SW.Water_quality_alarm2 == AJ_ON))
			 {
				Water_quality_alarm2_OFF();
				 Voice_control(0x22);
				 
			 }
			 
			 ////////////////////////3///////////////////////////
			 /*ˮλ���� -�򿪳�ˮ����ˮλ����*/
			 if((Sensor_Data.WaterLevel3 > WaterLevel1_Max)&&
					(Last_AJ_widget_SW.Drainage_machine3 == AJ_OFF))
			 {
				// AJ_widget_SW.Drainage_machine1 == AJ_ON
				// AJ_widget_SW.Water_level_alarm1 == AJ_ON
				 Drainage_machine3_ON();
				 Voice_control(0x03);
			 } 
			 /*ˮλ���� -�رճ�ˮ����ˮλ����*/
			 if(Sensor_Data.WaterLevel3 < WaterLevel1_Max&&
					 Last_AJ_widget_SW.Drainage_machine3 == AJ_ON)
			 {
				// AJ_widget_SW.Drainage_machine1 == AJ_OFF
				// AJ_widget_SW.Water_level_alarm1 == AJ_OFF		
         Drainage_machine3_OFF();	
         Voice_control(0x12);				 
			 }
			 
			 /*����ָ������ -�����걨����*/
			 if((Sensor_Data.Rainfall_index3 > Rainfall_index1_Max)&&
					(Last_AJ_widget_SW.Rainfall_alarm3 == AJ_OFF))
			 {
				// AJ_widget_SW.Rainfall_alarm1 == AJ_ON;
				 Rainfall_alarm3_ON();
				 Voice_control(0x09);
			 }
			 /*����ָ������ -�ؽ��걨����*/
			 if((Sensor_Data.Rainfall_index3 < Rainfall_index1_Max)&&
					(Last_AJ_widget_SW.Rainfall_alarm3 == AJ_ON))
			 {
				 Rainfall_alarm3_OFF();
				 Voice_control(0x1E);
			 }
			 
			 /*ˮ������̫�� -��ˮ�ʾ�����*/
			 if((Sensor_Data.water_quality3 > water_quality1_Max)&&
					(Last_AJ_widget_SW.Water_quality_alarm3== AJ_OFF))
			 {
				 Water_quality_alarm3_ON();
				 Voice_control(0x0C);
			 }
			 /*ˮ����������-��ˮ�ʾ����� -*/
			 if((Sensor_Data.water_quality3 < water_quality1_Max)&&
					(Last_AJ_widget_SW.Water_quality_alarm3 == AJ_ON))
			 {
				Water_quality_alarm3_OFF();
				 Voice_control(0x24);
			 }
				//printf("Auto....\r\n");  
		 }
		 
		 //�ֶ�����
		 if(IsAuto_flash==Manual)
		 {
			 LCD_Fill(6,101,62,155,BROWN);	
			 //////////////////////1////////////////////////////
			 //����ˮ����ˮλ������
				if((AJ_widget_SW.Drainage_machine1 == AJ_ON)&&
					 (Last_AJ_widget_SW.Drainage_machine1 == AJ_OFF))
				{
					Drainage_machine1_ON();
					Voice_control(0x0D);
				}
			 //����ˮ����ˮλ������
				if((AJ_widget_SW.Drainage_machine1 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Drainage_machine1 == AJ_ON))
				{
					Drainage_machine1_OFF();
					Voice_control(0x0E);
				}
				
							 //��ˮλ������
				if((AJ_widget_SW.Water_level_alarm1 == AJ_ON)&&
					 (Last_AJ_widget_SW.Water_level_alarm1 == AJ_OFF))
				{
					Water_level_alarm1_ON();
					Voice_control(0x13);
				}
			 //��ˮλ������
				if((AJ_widget_SW.Water_level_alarm1 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Water_level_alarm1 == AJ_ON))
				{
					Water_level_alarm1_OFF();
					Voice_control(0x14);
				}
				
				//�����꾯����
				if((AJ_widget_SW.Rainfall_alarm1 == AJ_ON)&&
					 (Last_AJ_widget_SW.Rainfall_alarm1 == AJ_OFF))
				{
					Rainfall_alarm1_ON();
					Voice_control(0x19);
				}
			 //�ؽ��꾯����
				if((AJ_widget_SW.Rainfall_alarm1 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Rainfall_alarm1 == AJ_ON))
				{
					Rainfall_alarm1_OFF();
					Voice_control(0x1A);
				}
				
				//��ˮ�ʾ�����
				if((AJ_widget_SW.Water_quality_alarm1 == AJ_ON)&&
					 (Last_AJ_widget_SW.Water_quality_alarm1 == AJ_OFF))
				{
					Water_quality_alarm1_ON();
					Voice_control(0x1F);
				}
			 //��ˮ�ʾ�����
				if((AJ_widget_SW.Water_quality_alarm1 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Water_quality_alarm1 == AJ_ON))
				{
					Water_quality_alarm1_OFF();
					Voice_control(0x20);
				}
				
				 //////////////////////2////////////////////////////
			 //����ˮ����ˮλ������
				if((AJ_widget_SW.Drainage_machine2 == AJ_ON)&&
					 (Last_AJ_widget_SW.Drainage_machine2 == AJ_OFF))
				{
					Drainage_machine2_ON();
					Voice_control(0x0F);
				}
			 //����ˮ����ˮλ������
				if((AJ_widget_SW.Drainage_machine2 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Drainage_machine2 == AJ_ON))
				{
					Drainage_machine2_OFF();
					Voice_control(0x10);
				}
				
							 //��ˮλ������
				if((AJ_widget_SW.Water_level_alarm2 == AJ_ON)&&
					 (Last_AJ_widget_SW.Water_level_alarm2 == AJ_OFF))
				{
					Water_level_alarm2_ON();
					Voice_control(0x15);
				}
			 //��ˮλ������
				if((AJ_widget_SW.Water_level_alarm2 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Water_level_alarm2 == AJ_ON))
				{
					Water_level_alarm2_OFF();
					Voice_control(0x16);
				}
				
				//�����꾯����
				if((AJ_widget_SW.Rainfall_alarm2 == AJ_ON)&&
					 (Last_AJ_widget_SW.Rainfall_alarm2 == AJ_OFF))
				{
					Rainfall_alarm2_ON();
					Voice_control(0x1B);
				}
			 //�ؽ��꾯����
				if((AJ_widget_SW.Rainfall_alarm2 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Rainfall_alarm2 == AJ_ON))
				{
					Rainfall_alarm2_OFF();
					Voice_control(0x1C);
				}
				
				//��ˮ�ʾ�����
				if((AJ_widget_SW.Water_quality_alarm2 == AJ_ON)&&
					 (Last_AJ_widget_SW.Water_quality_alarm2 == AJ_OFF))
				{
					Water_quality_alarm2_ON();
					Voice_control(0x21);
				}
			 //��ˮ�ʾ�����
				if((AJ_widget_SW.Water_quality_alarm2 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Water_quality_alarm2 == AJ_ON))
				{
					Water_quality_alarm2_OFF();
					Voice_control(0x22);
				}  
				
				 //////////////////////3////////////////////////////
			 //����ˮ����ˮλ������
				if((AJ_widget_SW.Drainage_machine3 == AJ_ON)&&
					 (Last_AJ_widget_SW.Drainage_machine3 == AJ_OFF))
				{
					Drainage_machine3_ON();
					Voice_control(0x11);
				}
			 //����ˮ����ˮλ������
				if((AJ_widget_SW.Drainage_machine3 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Drainage_machine3 == AJ_ON))
				{
					Drainage_machine3_OFF();
					Voice_control(0x12);
				}
				
			 //��ˮλ������
				if((AJ_widget_SW.Water_level_alarm3 == AJ_ON)&&
					 (Last_AJ_widget_SW.Water_level_alarm3 == AJ_OFF))
				{
					Water_level_alarm3_ON();
					Voice_control(0x17);
				}
			 //��ˮλ������
				if((AJ_widget_SW.Water_level_alarm3 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Water_level_alarm3 == AJ_ON))
				{
					Water_level_alarm3_OFF();
					Voice_control(0x18);
				}
				
				//�����꾯����
				if((AJ_widget_SW.Rainfall_alarm3 == AJ_ON)&&
					 (Last_AJ_widget_SW.Rainfall_alarm3 == AJ_OFF))
				{
					Rainfall_alarm3_ON();
					Voice_control(0x1D);
				}
			 //�ؽ��꾯����
				if((AJ_widget_SW.Rainfall_alarm3 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Rainfall_alarm3 == AJ_ON))
				{
					Rainfall_alarm3_OFF();
					Voice_control(0x1E);
				}
				
				//��ˮ�ʾ�����
				if((AJ_widget_SW.Water_quality_alarm3 == AJ_ON)&&
					 (Last_AJ_widget_SW.Water_quality_alarm3 == AJ_OFF))
				{
					Water_quality_alarm3_ON();
					Voice_control(0x23);
				}
			 //��ˮ�ʾ�����
				if((AJ_widget_SW.Water_quality_alarm3 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Water_quality_alarm3 == AJ_ON))
				{
					Water_quality_alarm3_OFF();
					Voice_control(0x24);
				}
			
			 }
		 
		 	 
		 //�����ϴοؼ����ص�״̬
		 if(!AJ_widget_SW_IsEqual())
		 {  
			 printf("AJ_widget_SW_Save\r\n");
			 AJ_widget_SW_Save();		 
		 }
		
			vTaskDelay(100);		
	}

}

//�����ϴοؼ����ص�״̬
void AJ_widget_SW_Save(void)
{
		Last_AJ_widget_SW.Drainage_machine1   	 =AJ_widget_SW.Drainage_machine1;//��ˮ��
		Last_AJ_widget_SW.Water_level_alarm1	 	 =AJ_widget_SW.Water_level_alarm1;//ˮλ����
		Last_AJ_widget_SW.Rainfall_alarm1 			 =AJ_widget_SW.Rainfall_alarm1;//���꾯��
		Last_AJ_widget_SW.Water_quality_alarm1   =AJ_widget_SW.Water_quality_alarm1;//ˮ�ʾ���
	
		Last_AJ_widget_SW.Drainage_machine2   	 =AJ_widget_SW.Drainage_machine2;//��ˮ��
		Last_AJ_widget_SW.Water_level_alarm2	 	 =AJ_widget_SW.Water_level_alarm2;//ˮλ����
		Last_AJ_widget_SW.Rainfall_alarm2 			 =AJ_widget_SW.Rainfall_alarm2;//���꾯��
		Last_AJ_widget_SW.Water_quality_alarm2   =AJ_widget_SW.Water_quality_alarm2;//ˮ�ʾ���
	
		Last_AJ_widget_SW.Drainage_machine3   	 =AJ_widget_SW.Drainage_machine3;//��ˮ��
		Last_AJ_widget_SW.Water_level_alarm3	 	 =AJ_widget_SW.Water_level_alarm3;//ˮλ����
		Last_AJ_widget_SW.Rainfall_alarm3 			 =AJ_widget_SW.Rainfall_alarm3;//���꾯��
		Last_AJ_widget_SW.Water_quality_alarm3   =AJ_widget_SW.Water_quality_alarm3;//ˮ�ʾ���
}

//�ж�ǰ�����οؼ����ص�״̬�Ƿ����
uint16_t AJ_widget_SW_IsEqual(void)
{
	if(		Last_AJ_widget_SW.Drainage_machine1   	 ==AJ_widget_SW.Drainage_machine1&&//��ˮ��
				Last_AJ_widget_SW.Water_level_alarm1	 	 ==AJ_widget_SW.Water_level_alarm1&&//ˮλ����
				Last_AJ_widget_SW.Rainfall_alarm1 			 ==AJ_widget_SW.Rainfall_alarm1&&//���꾯��
				Last_AJ_widget_SW.Water_quality_alarm1   ==AJ_widget_SW.Water_quality_alarm1&&//ˮ�ʾ���
			
				Last_AJ_widget_SW.Drainage_machine2   	 ==AJ_widget_SW.Drainage_machine2&&//��ˮ��
				Last_AJ_widget_SW.Water_level_alarm2	 	 ==AJ_widget_SW.Water_level_alarm2&&//ˮλ����
				Last_AJ_widget_SW.Rainfall_alarm2 			 ==AJ_widget_SW.Rainfall_alarm2&&//���꾯��
				Last_AJ_widget_SW.Water_quality_alarm2   ==AJ_widget_SW.Water_quality_alarm2&&//ˮ�ʾ���
			
				Last_AJ_widget_SW.Drainage_machine3   	 ==AJ_widget_SW.Drainage_machine3&&//��ˮ��
				Last_AJ_widget_SW.Water_level_alarm3	 	 ==AJ_widget_SW.Water_level_alarm3&&//ˮλ����
				Last_AJ_widget_SW.Rainfall_alarm3 			 ==AJ_widget_SW.Rainfall_alarm3&&//���꾯��
				Last_AJ_widget_SW.Water_quality_alarm3   ==AJ_widget_SW.Water_quality_alarm3)//ˮ�ʾ���
		return 1;
	else
	  return 0; 
}
