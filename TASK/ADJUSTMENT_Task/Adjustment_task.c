#include "Adjustment_task.h"
#include "queue.h"
#include "main.h"
#include "widget.h"
#include "sensors.h"
#include "lcd.h"
#include "usart3.h"
#include "uart5.h"
//传感器数据
extern Sensor_Data_t Sensor_Data;			//本次

//调节控件开关	
extern AJ_widget_t AJ_widget_SW;				//本次
extern AJ_widget_t Last_AJ_widget_SW;		//上次

//自动调节标志位
char IsAuto_flash=Manual;

//传感器任务函数
void Adjustment_task(void *pvParameters)
{
	printf("Adjustment_task\r\n");
	usart3_init(115200);
	//传感器初始化
	//while(!Sensors_Init());
	
	//调节控件初始化
	AJ_widgets_Init();
	
	while(1)
	{
		 //自动调节
		 if(IsAuto_flash==Auto)
		 {
			 LCD_Fill(6,101,62,155,LIGHTBLUE);	
			 //////////////////////1///////////////////////////
			 /*水位过高 -打开抽水机和水位警报*/
			 if((Sensor_Data.WaterLevel1 > WaterLevel1_Max)&&
					(Last_AJ_widget_SW.Drainage_machine1 == AJ_OFF))
			 {
				// AJ_widget_SW.Drainage_machine1 == AJ_ON
				// AJ_widget_SW.Water_level_alarm1 == AJ_ON
				 Drainage_machine1_ON();
				 Voice_control(0x01);
			 } 
			 /*水位正常 -关闭抽水机和水位警报*/
			 if(Sensor_Data.WaterLevel1 < WaterLevel1_Max&&
					 Last_AJ_widget_SW.Drainage_machine1 == AJ_ON)
			 {
				// AJ_widget_SW.Drainage_machine1 == AJ_OFF
				// AJ_widget_SW.Water_level_alarm1 == AJ_OFF		
         Drainage_machine1_OFF();	
         Voice_control(0x0E);				 
			 }
			 
			 /*降雨指数过大 -开降雨报警器*/
			 if((Sensor_Data.Rainfall_index1 > Rainfall_index1_Max)&&
					(Last_AJ_widget_SW.Rainfall_alarm1 == AJ_OFF))
			 {
				// AJ_widget_SW.Rainfall_alarm1 == AJ_ON;
				 Rainfall_alarm1_ON();
				 Voice_control(0x07);
			 }
			 /*降雨指数正常 -关降雨报警器*/
			 if((Sensor_Data.Rainfall_index1 < Rainfall_index1_Max)&&
					(Last_AJ_widget_SW.Rainfall_alarm1 == AJ_ON))
			 {
				 Rainfall_alarm1_OFF();
				 Voice_control(0x1A);
			 }
			 
			 /*水体质量太差 -开水质警报灯*/
			 if((Sensor_Data.water_quality1 > water_quality1_Max)&&
					(Last_AJ_widget_SW.Water_quality_alarm1 == AJ_OFF))
			 {
				 Water_quality_alarm1_ON();
				 Voice_control(0x0A);
			 }
			 /*水体质量正常-关水质警报灯 -*/
			 if((Sensor_Data.water_quality1 < water_quality1_Max)&&
					(Last_AJ_widget_SW.Water_quality_alarm1 == AJ_ON))
			 {
				Water_quality_alarm1_OFF();
				 Voice_control(0x20);
			 }		 
			 
			 //////////////////2/////////////////////////
			 /*水位过高 -打开抽水机和水位警报*/
			 if((Sensor_Data.WaterLevel2 > WaterLevel1_Max)&&
					(Last_AJ_widget_SW.Drainage_machine2 == AJ_OFF))
			 {
				// AJ_widget_SW.Drainage_machine1 == AJ_ON
				// AJ_widget_SW.Water_level_alarm1 == AJ_ON
				 Drainage_machine2_ON();
				 Voice_control(0x02);
			 } 
			 /*水位正常 -关闭抽水机和水位警报*/
			 if(Sensor_Data.WaterLevel2 < WaterLevel1_Max&&
					 Last_AJ_widget_SW.Drainage_machine2 == AJ_ON)
			 {
				// AJ_widget_SW.Drainage_machine1 == AJ_OFF
				// AJ_widget_SW.Water_level_alarm1 == AJ_OFF		
         Drainage_machine2_OFF();	
Voice_control(0x16);				 
			 }
			 
			 /*降雨指数过大 -开降雨报警器*/
			 if((Sensor_Data.Rainfall_index2 > Rainfall_index1_Max)&&
					(Last_AJ_widget_SW.Rainfall_alarm2 == AJ_OFF))
			 {
				// AJ_widget_SW.Rainfall_alarm1 == AJ_ON;
				 Rainfall_alarm2_ON();
				 Voice_control(0x08);
			 }
			 /*降雨指数正常 -关降雨报警器*/
			 if((Sensor_Data.Rainfall_index2 < Rainfall_index1_Max)&&
					(Last_AJ_widget_SW.Rainfall_alarm2 == AJ_ON))
			 {
				 Rainfall_alarm2_OFF();
				 Voice_control(0x1C);
				 
			 }
			 
			 /*水体质量太差 -开水质警报灯*/
			 if((Sensor_Data.water_quality2 > water_quality1_Max)&&
					(Last_AJ_widget_SW.Water_quality_alarm2 == AJ_OFF))
			 {
				 Water_quality_alarm2_ON();
				 Voice_control(0x0B);
			 }
			 /*水体质量正常-关水质警报灯 -*/
			 if((Sensor_Data.water_quality2 < water_quality1_Max)&&
					(Last_AJ_widget_SW.Water_quality_alarm2 == AJ_ON))
			 {
				Water_quality_alarm2_OFF();
				 Voice_control(0x22);
				 
			 }
			 
			 ////////////////////////3///////////////////////////
			 /*水位过高 -打开抽水机和水位警报*/
			 if((Sensor_Data.WaterLevel3 > WaterLevel1_Max)&&
					(Last_AJ_widget_SW.Drainage_machine3 == AJ_OFF))
			 {
				// AJ_widget_SW.Drainage_machine1 == AJ_ON
				// AJ_widget_SW.Water_level_alarm1 == AJ_ON
				 Drainage_machine3_ON();
				 Voice_control(0x03);
			 } 
			 /*水位正常 -关闭抽水机和水位警报*/
			 if(Sensor_Data.WaterLevel3 < WaterLevel1_Max&&
					 Last_AJ_widget_SW.Drainage_machine3 == AJ_ON)
			 {
				// AJ_widget_SW.Drainage_machine1 == AJ_OFF
				// AJ_widget_SW.Water_level_alarm1 == AJ_OFF		
         Drainage_machine3_OFF();	
         Voice_control(0x12);				 
			 }
			 
			 /*降雨指数过大 -开降雨报警器*/
			 if((Sensor_Data.Rainfall_index3 > Rainfall_index1_Max)&&
					(Last_AJ_widget_SW.Rainfall_alarm3 == AJ_OFF))
			 {
				// AJ_widget_SW.Rainfall_alarm1 == AJ_ON;
				 Rainfall_alarm3_ON();
				 Voice_control(0x09);
			 }
			 /*降雨指数正常 -关降雨报警器*/
			 if((Sensor_Data.Rainfall_index3 < Rainfall_index1_Max)&&
					(Last_AJ_widget_SW.Rainfall_alarm3 == AJ_ON))
			 {
				 Rainfall_alarm3_OFF();
				 Voice_control(0x1E);
			 }
			 
			 /*水体质量太差 -开水质警报灯*/
			 if((Sensor_Data.water_quality3 > water_quality1_Max)&&
					(Last_AJ_widget_SW.Water_quality_alarm3== AJ_OFF))
			 {
				 Water_quality_alarm3_ON();
				 Voice_control(0x0C);
			 }
			 /*水体质量正常-关水质警报灯 -*/
			 if((Sensor_Data.water_quality3 < water_quality1_Max)&&
					(Last_AJ_widget_SW.Water_quality_alarm3 == AJ_ON))
			 {
				Water_quality_alarm3_OFF();
				 Voice_control(0x24);
			 }
				//printf("Auto....\r\n");  
		 }
		 
		 //手动调节
		 if(IsAuto_flash==Manual)
		 {
			 LCD_Fill(6,101,62,155,BROWN);	
			 //////////////////////1////////////////////////////
			 //开排水机和水位警报器
				if((AJ_widget_SW.Drainage_machine1 == AJ_ON)&&
					 (Last_AJ_widget_SW.Drainage_machine1 == AJ_OFF))
				{
					Drainage_machine1_ON();
					Voice_control(0x0D);
				}
			 //关排水机和水位警报器
				if((AJ_widget_SW.Drainage_machine1 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Drainage_machine1 == AJ_ON))
				{
					Drainage_machine1_OFF();
					Voice_control(0x0E);
				}
				
							 //开水位警报器
				if((AJ_widget_SW.Water_level_alarm1 == AJ_ON)&&
					 (Last_AJ_widget_SW.Water_level_alarm1 == AJ_OFF))
				{
					Water_level_alarm1_ON();
					Voice_control(0x13);
				}
			 //关水位警报器
				if((AJ_widget_SW.Water_level_alarm1 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Water_level_alarm1 == AJ_ON))
				{
					Water_level_alarm1_OFF();
					Voice_control(0x14);
				}
				
				//开降雨警报器
				if((AJ_widget_SW.Rainfall_alarm1 == AJ_ON)&&
					 (Last_AJ_widget_SW.Rainfall_alarm1 == AJ_OFF))
				{
					Rainfall_alarm1_ON();
					Voice_control(0x19);
				}
			 //关降雨警报器
				if((AJ_widget_SW.Rainfall_alarm1 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Rainfall_alarm1 == AJ_ON))
				{
					Rainfall_alarm1_OFF();
					Voice_control(0x1A);
				}
				
				//开水质警报器
				if((AJ_widget_SW.Water_quality_alarm1 == AJ_ON)&&
					 (Last_AJ_widget_SW.Water_quality_alarm1 == AJ_OFF))
				{
					Water_quality_alarm1_ON();
					Voice_control(0x1F);
				}
			 //关水质警报器
				if((AJ_widget_SW.Water_quality_alarm1 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Water_quality_alarm1 == AJ_ON))
				{
					Water_quality_alarm1_OFF();
					Voice_control(0x20);
				}
				
				 //////////////////////2////////////////////////////
			 //开排水机和水位警报器
				if((AJ_widget_SW.Drainage_machine2 == AJ_ON)&&
					 (Last_AJ_widget_SW.Drainage_machine2 == AJ_OFF))
				{
					Drainage_machine2_ON();
					Voice_control(0x0F);
				}
			 //关排水机和水位警报器
				if((AJ_widget_SW.Drainage_machine2 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Drainage_machine2 == AJ_ON))
				{
					Drainage_machine2_OFF();
					Voice_control(0x10);
				}
				
							 //开水位警报器
				if((AJ_widget_SW.Water_level_alarm2 == AJ_ON)&&
					 (Last_AJ_widget_SW.Water_level_alarm2 == AJ_OFF))
				{
					Water_level_alarm2_ON();
					Voice_control(0x15);
				}
			 //关水位警报器
				if((AJ_widget_SW.Water_level_alarm2 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Water_level_alarm2 == AJ_ON))
				{
					Water_level_alarm2_OFF();
					Voice_control(0x16);
				}
				
				//开降雨警报器
				if((AJ_widget_SW.Rainfall_alarm2 == AJ_ON)&&
					 (Last_AJ_widget_SW.Rainfall_alarm2 == AJ_OFF))
				{
					Rainfall_alarm2_ON();
					Voice_control(0x1B);
				}
			 //关降雨警报器
				if((AJ_widget_SW.Rainfall_alarm2 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Rainfall_alarm2 == AJ_ON))
				{
					Rainfall_alarm2_OFF();
					Voice_control(0x1C);
				}
				
				//开水质警报器
				if((AJ_widget_SW.Water_quality_alarm2 == AJ_ON)&&
					 (Last_AJ_widget_SW.Water_quality_alarm2 == AJ_OFF))
				{
					Water_quality_alarm2_ON();
					Voice_control(0x21);
				}
			 //关水质警报器
				if((AJ_widget_SW.Water_quality_alarm2 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Water_quality_alarm2 == AJ_ON))
				{
					Water_quality_alarm2_OFF();
					Voice_control(0x22);
				}  
				
				 //////////////////////3////////////////////////////
			 //开排水机和水位警报器
				if((AJ_widget_SW.Drainage_machine3 == AJ_ON)&&
					 (Last_AJ_widget_SW.Drainage_machine3 == AJ_OFF))
				{
					Drainage_machine3_ON();
					Voice_control(0x11);
				}
			 //关排水机和水位警报器
				if((AJ_widget_SW.Drainage_machine3 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Drainage_machine3 == AJ_ON))
				{
					Drainage_machine3_OFF();
					Voice_control(0x12);
				}
				
			 //开水位警报器
				if((AJ_widget_SW.Water_level_alarm3 == AJ_ON)&&
					 (Last_AJ_widget_SW.Water_level_alarm3 == AJ_OFF))
				{
					Water_level_alarm3_ON();
					Voice_control(0x17);
				}
			 //关水位警报器
				if((AJ_widget_SW.Water_level_alarm3 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Water_level_alarm3 == AJ_ON))
				{
					Water_level_alarm3_OFF();
					Voice_control(0x18);
				}
				
				//开降雨警报器
				if((AJ_widget_SW.Rainfall_alarm3 == AJ_ON)&&
					 (Last_AJ_widget_SW.Rainfall_alarm3 == AJ_OFF))
				{
					Rainfall_alarm3_ON();
					Voice_control(0x1D);
				}
			 //关降雨警报器
				if((AJ_widget_SW.Rainfall_alarm3 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Rainfall_alarm3 == AJ_ON))
				{
					Rainfall_alarm3_OFF();
					Voice_control(0x1E);
				}
				
				//开水质警报器
				if((AJ_widget_SW.Water_quality_alarm3 == AJ_ON)&&
					 (Last_AJ_widget_SW.Water_quality_alarm3 == AJ_OFF))
				{
					Water_quality_alarm3_ON();
					Voice_control(0x23);
				}
			 //关水质警报器
				if((AJ_widget_SW.Water_quality_alarm3 == AJ_OFF)&&
					 (Last_AJ_widget_SW.Water_quality_alarm3 == AJ_ON))
				{
					Water_quality_alarm3_OFF();
					Voice_control(0x24);
				}
			
			 }
		 
		 	 
		 //保存上次控件开关的状态
		 if(!AJ_widget_SW_IsEqual())
		 {  
			 printf("AJ_widget_SW_Save\r\n");
			 AJ_widget_SW_Save();		 
		 }
		
			vTaskDelay(100);		
	}

}

//保存上次控件开关的状态
void AJ_widget_SW_Save(void)
{
		Last_AJ_widget_SW.Drainage_machine1   	 =AJ_widget_SW.Drainage_machine1;//排水机
		Last_AJ_widget_SW.Water_level_alarm1	 	 =AJ_widget_SW.Water_level_alarm1;//水位警报
		Last_AJ_widget_SW.Rainfall_alarm1 			 =AJ_widget_SW.Rainfall_alarm1;//降雨警报
		Last_AJ_widget_SW.Water_quality_alarm1   =AJ_widget_SW.Water_quality_alarm1;//水质警报
	
		Last_AJ_widget_SW.Drainage_machine2   	 =AJ_widget_SW.Drainage_machine2;//排水机
		Last_AJ_widget_SW.Water_level_alarm2	 	 =AJ_widget_SW.Water_level_alarm2;//水位警报
		Last_AJ_widget_SW.Rainfall_alarm2 			 =AJ_widget_SW.Rainfall_alarm2;//降雨警报
		Last_AJ_widget_SW.Water_quality_alarm2   =AJ_widget_SW.Water_quality_alarm2;//水质警报
	
		Last_AJ_widget_SW.Drainage_machine3   	 =AJ_widget_SW.Drainage_machine3;//排水机
		Last_AJ_widget_SW.Water_level_alarm3	 	 =AJ_widget_SW.Water_level_alarm3;//水位警报
		Last_AJ_widget_SW.Rainfall_alarm3 			 =AJ_widget_SW.Rainfall_alarm3;//降雨警报
		Last_AJ_widget_SW.Water_quality_alarm3   =AJ_widget_SW.Water_quality_alarm3;//水质警报
}

//判断前后两次控件开关的状态是否相等
uint16_t AJ_widget_SW_IsEqual(void)
{
	if(		Last_AJ_widget_SW.Drainage_machine1   	 ==AJ_widget_SW.Drainage_machine1&&//排水机
				Last_AJ_widget_SW.Water_level_alarm1	 	 ==AJ_widget_SW.Water_level_alarm1&&//水位警报
				Last_AJ_widget_SW.Rainfall_alarm1 			 ==AJ_widget_SW.Rainfall_alarm1&&//降雨警报
				Last_AJ_widget_SW.Water_quality_alarm1   ==AJ_widget_SW.Water_quality_alarm1&&//水质警报
			
				Last_AJ_widget_SW.Drainage_machine2   	 ==AJ_widget_SW.Drainage_machine2&&//排水机
				Last_AJ_widget_SW.Water_level_alarm2	 	 ==AJ_widget_SW.Water_level_alarm2&&//水位警报
				Last_AJ_widget_SW.Rainfall_alarm2 			 ==AJ_widget_SW.Rainfall_alarm2&&//降雨警报
				Last_AJ_widget_SW.Water_quality_alarm2   ==AJ_widget_SW.Water_quality_alarm2&&//水质警报
			
				Last_AJ_widget_SW.Drainage_machine3   	 ==AJ_widget_SW.Drainage_machine3&&//排水机
				Last_AJ_widget_SW.Water_level_alarm3	 	 ==AJ_widget_SW.Water_level_alarm3&&//水位警报
				Last_AJ_widget_SW.Rainfall_alarm3 			 ==AJ_widget_SW.Rainfall_alarm3&&//降雨警报
				Last_AJ_widget_SW.Water_quality_alarm3   ==AJ_widget_SW.Water_quality_alarm3)//水质警报
		return 1;
	else
	  return 0; 
}
