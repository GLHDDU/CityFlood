#include "User_task.h"
#include "task.h"
#include "delay.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "beep.h"
#include "queue.h"
#include "string.h"
#include "user.h"
#include "stdlib.h"
#include "lcd.h"
#include "hanzi.h"
#include "wifi.h"
#include "Sensors.h"
#include "widget.h"
#include "uart5.h"
//传感器数据
extern Sensor_Data_t Sensor_Data;			//本次
extern AJ_widget_t AJ_widget_SW;	//调节控件开关
int KeyValue;
u8 model=0;
u8 temp1_set=28,temp2_set=25,shine_set=85; 
extern u8 weather1,high_temp1,low_temp1,weather2,high_temp2,low_temp2;
void key_test(void);
void lcd_sensor_refresh(Sensor_Data_t *Sensor_Data);
void draw_weather(u8 weather1,u8 high_temp1,u8 low_temp1,u8 weather2,u8 high_temp2,u8 low_temp2);
void draw_main_page(void);
//void adjuet(void);
	void lcd_actuator_refresh1(AJ_widget_t *AJ_widget_SW) ; //根据云平台结果，刷新数据
//User任务函数(人机交互)
void USER_task(void *pvParameters)
{		
	printf("USER_task\r\n");
	
	LED_Init();		  				//初始化LED
	KEY_Init();							//初始化按键
	BEEP_Init();						//初始化蜂鸣器
	LCD_Init();							//初始化LCD
	LCD_Clear(GRAY);	
	draw_main_page();
	UART5_Configuration();
	while(1)
	{
	  lcd_sensor_refresh(&Sensor_Data);	  //刷新传感器数据
		draw_weather(weather1,high_temp1,low_temp1,weather2,high_temp2,low_temp2);
		key_test();			//按键进程，控制执行器图标
		lcd_actuator_refresh1(&AJ_widget_SW) ; //在没有按键操作情况下。根据按键外其他控制的结果，刷新lcd执行器
		vTaskDelay(100);		
	}
	
}

void lcd_actuator_refresh(int keystrokes[],AJ_widget_t *AJ_widget_SW)  //LCD执行器更新
 {
		 	switch(keystrokes[0])
					{
						case 1:  //如果是风扇2设置模式
							Draw_word(7+118*3,678,112,112,0xffff,shuizhiyujing[0]);
			        Draw_word(7,678,112,112,0x8e388e,choushuiji[0]);//选中的，变色
						Draw_word(7+118*3+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
						Draw_word(7+10,639,24,39,0x8e388e,tianqi_shuzhi[1]);  //刷新数字
						break;
						case 2:  //如果是风扇2设置模式
							Draw_word(7+118*3,678,112,112,0xffff,shuizhiyujing[0]);
			        Draw_word(7,678,112,112,0x8e388e,choushuiji[0]);//选中的，变色
						Draw_word(7+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
						Draw_word(7+44,639,24,39,0x8e388e,tianqi_shuzhi[2]);  //刷新数字
						break;
						case 3:  //如果是风扇2设置模式
							Draw_word(7+118*3,678,112,112,0xffff,shuizhiyujing[0]);
			        Draw_word(7,678,112,112,0x8e388e,choushuiji[0]);//选中的，变色
						Draw_word(7+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
						Draw_word(7+78,639,24,39,0x8e388e,tianqi_shuzhi[3]);  //刷新数字
						break;
						
						case 4:  //如果是风扇2设置模式
							Draw_word(7,678,112,112,0xffff,choushuiji[0]);
							Draw_word(7+118,678,112,112,0x8e388e,shuiweiyujing[0]);
						Draw_word(7+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
						Draw_word(7+118+10,639,24,39,0x8e388e,tianqi_shuzhi[1]);  //刷新数字
						break;
						case 5:  //如果是风扇2设置模式
							Draw_word(7,678,112,112,0xffff,choushuiji[0]);
							Draw_word(7+118,678,112,112,0x8e388e,shuiweiyujing[0]);
						Draw_word(7+118+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
						Draw_word(7+118+44,639,24,39,0x8e388e,tianqi_shuzhi[2]);  //刷新数字
						break;
						case 6:  //如果是风扇2设置模式
							Draw_word(7,678,112,112,0xffff,choushuiji[0]);
							Draw_word(7+118,678,112,112,0x8e388e,shuiweiyujing[0]);
						Draw_word(7+118+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
						Draw_word(7+118+78,639,24,39,0x8e388e,tianqi_shuzhi[3]);  //刷新数字
						break;


						case 7:  ////如果是抽水机设置模式
							Draw_word(7+118,678,112,112,0xffff,shuiweiyujing[0]);
							Draw_word(7+118*2,678,112,112,0x8e388e,jiangyubaojing[0]);
						Draw_word(7+118+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
						Draw_word(7+118*2+10,639,24,39,0x8e388e,tianqi_shuzhi[1]);  //刷新数字
						break;
						case 8:  ////如果是抽水机设置模式
							Draw_word(7+118,678,112,112,0xffff,shuiweiyujing[0]);
							Draw_word(7+118*2,678,112,112,0x8e388e,jiangyubaojing[0]);
						Draw_word(7+118*2+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
						Draw_word(7+118*2+44,639,24,39,0x8e388e,tianqi_shuzhi[2]);  //刷新数字
						break;
						case 9:  ////如果是抽水机设置模式
							Draw_word(7+118,678,112,112,0xffff,shuiweiyujing[0]);
							Draw_word(7+118*2,678,112,112,0x8e388e,jiangyubaojing[0]);
						Draw_word(7+118*2+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
						Draw_word(7+118*2+78,639,24,39,0x8e388e,tianqi_shuzhi[3]);  //刷新数字
						break;
						
						case 10:  //如果是照明灯设置模式
							Draw_word(7+118*2,678,112,112,0xffff,jiangyubaojing[0]);
							Draw_word(7+118*3,678,112,112,0x8e388e,shuizhiyujing[0]);
						Draw_word(7+118*2+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
						Draw_word(7+118*3+10,639,24,39,0x8e388e,tianqi_shuzhi[1]);  //刷新数字
						break;
						case 11:  //如果是照明灯设置模式
							Draw_word(7+118*2,678,112,112,0xffff,jiangyubaojing[0]);
							Draw_word(7+118*3,678,112,112,0x8e388e,shuizhiyujing[0]);
						Draw_word(7+118*3+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
						Draw_word(7+118*3+44,639,24,39,0x8e388e,tianqi_shuzhi[2]);  //刷新数字
						break;
						case 12:  //如果是照明灯设置模式
							Draw_word(7+118*2,678,112,112,0xffff,jiangyubaojing[0]);
							Draw_word(7+118*3,678,112,112,0x8e388e,shuizhiyujing[0]);
						Draw_word(7+118*3+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
						Draw_word(7+118*3+78,639,24,39,0x8e388e,tianqi_shuzhi[3]);  //刷新数字
						break;
						default:
            printf("++key is error\n");  //0xcd2626
            break;
					}
	   delay_ms(100);//动态效果停留
		////////////////////////////////			
		if(keystrokes[1]==1||AJ_widget_SW->Drainage_machine1)
		{
		//	AJ_widget_SW->Drainage_machine1=AJ_ON;
			Draw_word(7+10,639,24,39,0xcd2626,tianqi_shuzhi[1]);  //刷新数字
		}
		else 
		{
		//	AJ_widget_SW->Drainage_machine1=AJ_OFF;
			Draw_word(7+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
		}
		if(keystrokes[2]==1||AJ_widget_SW->Drainage_machine2)
		{
		//	AJ_widget_SW->Drainage_machine2=AJ_ON;
			Draw_word(7+44,639,24,39,0xcd2626,tianqi_shuzhi[2]);  //刷新数字
		}
		else
		{
		//	AJ_widget_SW->Drainage_machine2=AJ_OFF;
			Draw_word(7+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
		}
		if(keystrokes[3]==1||AJ_widget_SW->Drainage_machine3)
		{
		//	AJ_widget_SW->Drainage_machine3=AJ_ON;
			Draw_word(7+78,639,24,39,0xcd2626,tianqi_shuzhi[3]);  //刷新数字
		}
		else
		{
		//	AJ_widget_SW->Drainage_machine3=AJ_OFF;
			Draw_word(7+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
		}                                       
		if(keystrokes[1]||keystrokes[2]||keystrokes[3]||AJ_widget_SW->Drainage_machine1||AJ_widget_SW->Drainage_machine2||AJ_widget_SW->Drainage_machine3)
			Draw_word(7,678,112,112,0xcd2626,choushuiji[0]);  //选中的，变色
		else
      Draw_word(7,678,112,112,0xffff,choushuiji[0]);  //不变色
		////////////////////////////////////
		if(keystrokes[4]==1||AJ_widget_SW->Water_level_alarm1)
		{
		//	AJ_widget_SW->Water_level_alarm1=AJ_ON;
			Draw_word(7+118+10,639,24,39,0xcd2626,tianqi_shuzhi[1]);  //刷新数字
		}
		else
		{
		//	AJ_widget_SW->Water_level_alarm1=AJ_OFF;
			Draw_word(7+118+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
		}
		if(keystrokes[5]==1||AJ_widget_SW->Water_level_alarm2)
		{
		//	AJ_widget_SW->Water_level_alarm2=AJ_ON;
			Draw_word(7+118+44,639,24,39,0xcd2626,tianqi_shuzhi[2]);  //刷新数字
		}
		else
		{
		//	AJ_widget_SW->Water_level_alarm2=AJ_OFF;
			Draw_word(7+118+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
		}
		if(keystrokes[6]==1||AJ_widget_SW->Water_level_alarm3)
		{
		//	AJ_widget_SW->Water_level_alarm3=AJ_ON;
			Draw_word(7+118+78,639,24,39,0xcd2626,tianqi_shuzhi[3]);  //刷新数字
		}
		else
		{
			AJ_widget_SW->Water_level_alarm3=AJ_OFF;
			Draw_word(7+118+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
		}
		if(keystrokes[4]||keystrokes[5]||keystrokes[6]||AJ_widget_SW->Water_level_alarm1||AJ_widget_SW->Water_level_alarm2||AJ_widget_SW->Water_level_alarm3)
			Draw_word(7+118,678,112,112,0xcd2626,shuiweiyujing[0]);  //选中的，变色
		else
      Draw_word(7+118,678,112,112,0xffff,shuiweiyujing[0]);  //不变色
		/////////////////////////////////////
		if(keystrokes[7]==1||AJ_widget_SW->Rainfall_alarm1)
		{
			//AJ_widget_SW->Rainfall_alarm1=AJ_ON;
			Draw_word(7+118*2+10,639,24,39,0xcd2626,tianqi_shuzhi[1]);  //刷新数字
		}
		else 
		{
			//AJ_widget_SW->Rainfall_alarm1=AJ_OFF;
			Draw_word(7+118*2+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
		}
		if(keystrokes[8]==1||AJ_widget_SW->Rainfall_alarm2)
		{
			//AJ_widget_SW->Rainfall_alarm2=AJ_ON;
			Draw_word(7+118*2+44,639,24,39,0xcd2626,tianqi_shuzhi[2]);  //刷新数字
		}
		else 
		{
		//	AJ_widget_SW->Rainfall_alarm2=AJ_OFF;
			Draw_word(7+118*2+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
		}
		if(keystrokes[9]==1||AJ_widget_SW->Rainfall_alarm3)
		{
		//	AJ_widget_SW->Rainfall_alarm3=AJ_ON;
			Draw_word(7+118*2+78,639,24,39,0xcd2626,tianqi_shuzhi[3]);  //刷新数字
		}
		else 
		{
			AJ_widget_SW->Rainfall_alarm3=AJ_OFF;
			Draw_word(7+118*2+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
		}
		if(keystrokes[7]||keystrokes[8]||keystrokes[9]||AJ_widget_SW->Rainfall_alarm1||AJ_widget_SW->Rainfall_alarm2||AJ_widget_SW->Rainfall_alarm3)
			Draw_word(7+118*2,678,112,112,0xcd2626,jiangyubaojing[0]); //选中的，变色
		else
      Draw_word(7+118*2,678,112,112,0xffff,jiangyubaojing[0]);  //不变色
		/////////////////////////////////////////
		if(keystrokes[10]==1||AJ_widget_SW->Water_quality_alarm1)
		{
		//	AJ_widget_SW->Water_quality_alarm1=AJ_ON;
			Draw_word(7+118*3+10,639,24,39,0xcd2626,tianqi_shuzhi[1]);  //刷新数字
		}
		else
		{
		//	AJ_widget_SW->Water_quality_alarm1=AJ_OFF;
			Draw_word(7+118*3+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
		}
		if(keystrokes[11]==1||AJ_widget_SW->Water_quality_alarm2)
		{
		//	AJ_widget_SW->Water_quality_alarm2=AJ_ON;
			Draw_word(7+118*3+44,639,24,39,0xcd2626,tianqi_shuzhi[2]);  //刷新数字
		}
		else
		{
		//	AJ_widget_SW->Water_quality_alarm2=AJ_OFF;
			Draw_word(7+118*3+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
		}
		if(keystrokes[12]==1||AJ_widget_SW->Water_quality_alarm3)
		{
		//	AJ_widget_SW->Water_quality_alarm3=AJ_ON;
			Draw_word(7+118*3+78,639,24,39,0xcd2626,tianqi_shuzhi[3]);  //刷新数字
		}
		else
		{
		//	AJ_widget_SW->Water_quality_alarm3=AJ_OFF;
			Draw_word(7+118*3+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
		}
		if(keystrokes[10]||keystrokes[11]||keystrokes[12]||AJ_widget_SW->Water_quality_alarm1||AJ_widget_SW->Water_quality_alarm2||AJ_widget_SW->Water_quality_alarm3)
			Draw_word(7+118*3,678,112,112,0xcd2626,shuizhiyujing[0]);  //选中的，变色
		else
      Draw_word(7+118*3,678,112,112,0xffff,shuizhiyujing[0]);  //不变色
	//printf("E\r\n");
}


 void key_test(void)
{
		 vu8 key=0;
	
static	int keystrokes[13]={0};
key=KEY_Scan(0);	//得到键值
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//控制蜂鸣器
					
					keystrokes[0]++;
				keystrokes[0]=(keystrokes[0]%13);
				printf("WKUP_PRES:%d\r\n",keystrokes[0]);
					break; 
				case KEY1_PRES:	//加加按钮	按下
					switch(keystrokes[0])
					{
						case 1:  //如果是风扇2设置模式
							keystrokes[1]=!keystrokes[1];
						AJ_widget_SW.Drainage_machine1=!AJ_widget_SW.Drainage_machine1;
						break;
						case 2:  //如果是风扇2设置模式
							keystrokes[2]=!keystrokes[2];
						AJ_widget_SW.Drainage_machine2=!AJ_widget_SW.Drainage_machine2;
						break;
						case 3:  ////如果是抽水机设置模式
							keystrokes[3]=!keystrokes[3];
						AJ_widget_SW.Drainage_machine3=!AJ_widget_SW.Drainage_machine3;
						break;
						case 4:  //如果是照明灯设置模式
							keystrokes[4]=!keystrokes[4];
						AJ_widget_SW.Water_level_alarm1=!AJ_widget_SW.Water_level_alarm1;
						break;
						case 5:  //如果是风扇2设置模式
							keystrokes[5]=!keystrokes[5];
						AJ_widget_SW.Water_level_alarm2=!AJ_widget_SW.Water_level_alarm2;
						break;
						case 6:  //如果是风扇2设置模式
							keystrokes[6]=!keystrokes[6];
						AJ_widget_SW.Water_level_alarm3=!AJ_widget_SW.Water_level_alarm3;
						break;
						case 7:  ////如果是抽水机设置模式
							keystrokes[7]=!keystrokes[7];
						AJ_widget_SW.Rainfall_alarm1=!AJ_widget_SW.Rainfall_alarm1;
						break;
						case 8:  //如果是照明灯设置模式
							keystrokes[8]=!keystrokes[8];
						AJ_widget_SW.Rainfall_alarm2=!AJ_widget_SW.Rainfall_alarm2;
						break;
						case 9:  //如果是风扇2设置模式
							keystrokes[9]=!keystrokes[9];
						AJ_widget_SW.Rainfall_alarm3=!AJ_widget_SW.Rainfall_alarm3;
						break;
						case 10:  //如果是风扇2设置模式
							keystrokes[10]=!keystrokes[10];
						AJ_widget_SW.Water_quality_alarm1=!AJ_widget_SW.Water_quality_alarm1;
						break;
						case 11:  ////如果是抽水机设置模式
							keystrokes[11]=!keystrokes[11];
						AJ_widget_SW.Water_quality_alarm2=!AJ_widget_SW.Water_quality_alarm2;
						break;
						case 12:  //如果是照明灯设置模式
							keystrokes[12]=!keystrokes[12];
						AJ_widget_SW.Water_quality_alarm3=!AJ_widget_SW.Water_quality_alarm3;
						break;
						default:
            printf("++key is error\n");
            break;
					}
					printf("KEY1_PRES:%d,%d\r\n",keystrokes[0],keystrokes[keystrokes[0]]);
					break;
				case KEY0_PRES:	//减减按钮按下
								switch(model)
					{
						case 1:  //如果是温度阈值1设置模式
							temp1_set--;
						break;
						case 2:  //如果是温度阈值2设置模式
							temp2_set--;
						break;
						case 3:  ////如果是光照度阈值设置模式
							shine_set--;
						break;
						default:
            printf("--key is error\n");
            break;
					}
					break;
					
			}
			lcd_actuator_refresh(keystrokes,&AJ_widget_SW);
		}
	}

	
	void draw_main_page(void)
	{
				    //标题
        Draw_word(42,22,56,56,0xcd2626,title[0]);
        Draw_word(42+66,22,56,56,0xcd2626,title[1]);
        Draw_word(42+66*2,22,56,56,0xcd2626,title[2]);
        Draw_word(42+66*3,22,56,56,0xcd2626,title[3]);
        Draw_word(42+66*4,22,56,56,0xcd2626,title[4]);
        Draw_word(42+66*5,22,56,56,0xcd2626,title[5]);
		
		LCD_Fill(40, 80, 42+66*4+66, 83, 0XF81F); //绘制线条
		LCD_Fill(42+66, 87, 42+66*6+2, 90, MAGENTA); //绘制线条
		
		//绘制表格
		LCD_Fill(5, 100, 475, 100, BLACK); //绘制线条
		LCD_Fill(5, 100+56, 475, 100+56, BLACK); //绘制线条
		LCD_Fill(5, 100+56*2, 475, 100+56*2, BLACK); //绘制线条
		LCD_Fill(5, 100+56*3, 475, 100+56*3, BLACK); //绘制线条
		LCD_Fill(5, 100+56*4, 475, 100+56*4, BLACK); //绘制线条
		LCD_Fill(5, 100+56*5, 475, 100+56*5, BLACK); //绘制线条
		LCD_Fill(5, 100+56*6, 475, 100+56*6, BLACK); //绘制线条
		
		LCD_Fill(4, 100, 4, 100+56*6, BLACK); //绘制线条
		LCD_Fill(63, 100, 63, 100+56*6, BLACK); //绘制线条
		LCD_Fill(185, 100, 185, 100+56*6, BLACK); //绘制线条
		LCD_Fill(282, 100, 282, 100+56*6, BLACK); //绘制线条
		LCD_Fill(379, 100, 379, 100+56*6, BLACK); //绘制线条
		LCD_Fill(476, 100, 476, 100+56*6, BLACK); //绘制线条
		
			Draw_word(186,103,48,48,0xff00,churukou[1]);
			Draw_word(186+48,103,48,48,0xff00,churukou[2]);
			Draw_word(283,103,48,48,0xff00,zhongdaung[0]);
			Draw_word(283+48,103,48,48,0xff00,zhongdaung[1]);
			Draw_word(380,103,48,48,0xff00,churukou[0]);
			Draw_word(380+48,103,48,48,0xff00,churukou[2]);
				//环境温度
        Draw_word(64,100+56,48,48,0xff00,shuwei[0]);
        Draw_word(64+48,100+56,48,48,0xff00,shuwei[1]);
        Draw_word(64+48*2,100+56,48,48,0xff00,fenghao[0]);

				//环境湿度
        Draw_word(64,156+56,48,48,0xff00,jiangyu[0]);
        Draw_word(64+48,156+56,48,48,0xff00,jiangyu[1]);
        Draw_word(64+48*2,156+56,48,48,0xff00,fenghao[0]);

				//环境光照
        Draw_word(64,212+56,48,48,0xff00,wendu[0]);
        Draw_word(64+48,212+56,48,48,0xff00,wendu[1]);
        Draw_word(64+48*2,212+56,48,48,0xff00,fenghao[0]);

				//土壤湿度
        Draw_word(64,268+56,48,48,0xff00,shidu[0]);
        Draw_word(64+48,268+56,48,48,0xff00,shidu[1]);
        Draw_word(64+48*2,268+56,48,48,0xff00,fenghao[0]);

				//水位高度
        Draw_word(64,324+56,48,48,0xff00,shuizhi[0]);
        Draw_word(64+48,324+56,48,48,0xff00,shuizhi[1]);
        Draw_word(64+48*2,324+56,48,48,0xff00,fenghao[0]);

				
				
				//数据标志绘制
				Draw_word(6,100+56,56,56,0xff11,shuiwei_biao[0]);
				Draw_word(6,156+56,56,56,0xff11,yudi_biao[0]);
				Draw_word(6,212+56,56,56,0xff11,wendu_biao[0]);
				Draw_word(6,268+56,56,56,0xff11,shidu_biao[0]);
				Draw_word(6,324+56,56,56,0xff11,shuizhi_biao[0]);

						
				
				//执行器图标
				Draw_word(7,678,112,112,0xffff,choushuiji[0]);
				Draw_word(7+118,678,112,112,0xffff,shuiweiyujing[0]);
				Draw_word(7+118*2,678,112,112,0xffff,jiangyubaojing[0]);
				Draw_word(7+118*3,678,112,112,0xffff,shuizhiyujing[0]);
				
				//执行器上标数字
				Draw_word(7+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
 				Draw_word(7+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
				Draw_word(7+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
				Draw_word(7+118+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
				Draw_word(7+118+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
				Draw_word(7+118+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
				Draw_word(7+118*2+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
				Draw_word(7+118*2+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
				Draw_word(7+118*2+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
				Draw_word(7+118*3+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
				Draw_word(7+118*3+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
				Draw_word(7+118*3+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
				
				//绘制天气图标
				///今日天气文字
				Draw_word(32,487-39,48,48,DARKBLUE,tianqi[0]);
				Draw_word(32+48,487-39,48,48,DARKBLUE,tianqi[2]);
				Draw_word(32+48*2,487-39,48,48,DARKBLUE,tianqi[3]);
				Draw_word(32+48*3,487-39,48,48,DARKBLUE,tianqi[4]);
				///明日天气文字
				Draw_word(240+32,487-39,48,48,DARKBLUE,tianqi[1]);
				Draw_word(240+32+48,487-39,48,48,DARKBLUE,tianqi[2]);
				Draw_word(240+32+48*2,487-39,48,48,DARKBLUE,tianqi[3]);
				Draw_word(240+32+48*3,487-39,48,48,DARKBLUE,tianqi[4]);
				Draw_word(140+20*3,540+16*2+40-39,40,39,LBBLUE,du_fuhao[0]);
				Draw_word(140+236+20*3,540+16*2+40-39,40,39,LBBLUE,du_fuhao[0]);
				Draw_word(140+20*3,540+16-39,40,39,LBBLUE,du_fuhao[0]);
				Draw_word(140+236+20*3,540+16-39,40,39,LBBLUE,du_fuhao[0]);
		
	}
	
	//刷新lcd传感器数据
	void lcd_sensor_refresh(Sensor_Data_t *Sensor_Data)
	{
		static int last_level1=1;
		static int last_rain1=1;
		static int last_temp1=1;
		static int last_humi1=1;
		static int last_water_quality1=1;
		static int last_level2=1;
		static int last_rain2=1;
		static int last_temp2=1;
		static int last_humi2=1;
		static int last_water_quality2=1;
		static int last_level3=1;
		static int last_rain3=1;
		static int last_temp3=1;
		static int last_humi3=1;
		static int last_water_quality3=0;
		////////////////////////1/////////////////////////
				//水位数据
		if(last_level1!=Sensor_Data->WaterLevel1)
			{
		    LCD_Fill(186,156+2,281,156+48-2,GRAY);	
		    if(Sensor_Data->WaterLevel1<0)
				Draw_word(186,156,24,48,0xff00,fuhao[0]);
				Draw_word(210,156,24,48,0xff00,shuzhi[(abs(Sensor_Data->WaterLevel1)/100)%10]);
				Draw_word(210+24,156,24,48,0xff00,shuzhi[(abs(Sensor_Data->WaterLevel1)/10)%10]);
				Draw_word(210+24*2,156,24,48,0xff00,shuzhi[abs(Sensor_Data->WaterLevel1)%10]);
			}
			if(last_rain1!=Sensor_Data->Rainfall_index1)
			{
				LCD_Fill(186,212+2,281,212+48,GRAY);		
				if(Sensor_Data->Rainfall_index1<0)
				Draw_word(186,212,24,48,0xff00,fuhao[0]);
				Draw_word(210,212,24,48,0xff00,shuzhi[(abs(Sensor_Data->Rainfall_index1)/100)%10]);
				Draw_word(210+24,212,24,48,0xff00,shuzhi[(abs(Sensor_Data->Rainfall_index1)/10)%10]);
				Draw_word(210+24*2,212,24,48,0xff00,shuzhi[abs(Sensor_Data->Rainfall_index1)%10]);
			}
				if(last_temp1!=Sensor_Data->Current_temperature1)
			{
				LCD_Fill(186,268+2,281,268+48,GRAY);	
				if(Sensor_Data->Current_temperature1<0)
				Draw_word(186,268,24,48,0xff00,fuhao[0]);
				Draw_word(210,268,24,48,0xff00,shuzhi[(abs(Sensor_Data->Current_temperature1)/100)%10]);
				Draw_word(210+24,268,24,48,0xff00,shuzhi[(abs(Sensor_Data->Current_temperature1)/10)%10]);
				Draw_word(210+24*2,268,24,48,0xff00,shuzhi[abs(Sensor_Data->Current_temperature1)%10]);
			}
			if(last_humi1!=Sensor_Data->Current_humidity1)
			{
				LCD_Fill(186,324+2,281,324+48,GRAY);	
				if(Sensor_Data->Current_humidity1<0)
				Draw_word(186,324,24,48,0xff00,fuhao[0]);
				Draw_word(210,324,24,48,0xff00,shuzhi[(abs(Sensor_Data->Current_humidity1)/100)%10]);
				Draw_word(210+24,324,24,48,0xff00,shuzhi[(abs(Sensor_Data->Current_humidity1)/10)%10]);
				Draw_word(210+24*2,324,24,48,0xff00,shuzhi[abs(Sensor_Data->Current_humidity1)%10]);
			}
				if(last_water_quality1!=Sensor_Data->WaterLevel1)
			{
				LCD_Fill(186,380+2,281,380+48,GRAY);		
				if(Sensor_Data->WaterLevel1<0)
				Draw_word(186,380,24,48,0xff00,fuhao[0]);
				Draw_word(210,380,24,48,0xff00,shuzhi[(abs(Sensor_Data->water_quality1)/100)%10]);
				Draw_word(210+24,380,24,48,0xff00,shuzhi[(abs(Sensor_Data->water_quality1)/10)%10]);
				Draw_word(210+24*2,380+2,24,48,0xff00,shuzhi[abs(Sensor_Data->water_quality1)%10]);
			}
				/////////////////////2///////////////////////////
				if(last_level2!=Sensor_Data->WaterLevel2)
			{
				LCD_Fill(283,156+2,378,156+48,GRAY);	
				if(Sensor_Data->WaterLevel2<0)
				Draw_word(283,156,24,48,0xff00,fuhao[0]);
				Draw_word(283+24,156,24,48,0xff00,shuzhi[(abs(Sensor_Data->WaterLevel2)/100)%10]);
				Draw_word(283+24*2,156,24,48,0xff00,shuzhi[(abs(Sensor_Data->WaterLevel2)/10)%10]);
				Draw_word(283+24*3,156,24,48,0xff00,shuzhi[abs(Sensor_Data->WaterLevel2)%10]);
			}
				if(last_rain2!=Sensor_Data->Rainfall_index2)
			{
				LCD_Fill(283,212+2,378,212+48,GRAY);	
				if(Sensor_Data->Rainfall_index2<0)
				Draw_word(283,212,24,48,0xff00,fuhao[0]);
				Draw_word(283+24,212,24,48,0xff00,shuzhi[(abs(Sensor_Data->Rainfall_index2)/100)%10]);
				Draw_word(283+24*2,212,24,48,0xff00,shuzhi[(abs(Sensor_Data->Rainfall_index2)/10)%10]);
				Draw_word(283+24*3,212,24,48,0xff00,shuzhi[abs(Sensor_Data->Rainfall_index2)%10]);
			}
				if(last_temp2!=Sensor_Data->Current_temperature2)
			{
				LCD_Fill(283,268+2,378,268+48,GRAY);	
				if(Sensor_Data->Current_temperature2<0)
				Draw_word(283,268,24,48,0xff00,fuhao[0]);
				Draw_word(283+24,268,24,48,0xff00,shuzhi[(abs(Sensor_Data->Current_temperature2)/100)%10]);
				Draw_word(283+24*2,268,24,48,0xff00,shuzhi[(abs(Sensor_Data->Current_temperature2)/10)%10]);
				Draw_word(283+24*3,268,24,48,0xff00,shuzhi[abs(Sensor_Data->Current_temperature2)%10]);
			}
				if(last_humi2!=Sensor_Data->Current_humidity2)
			{
				LCD_Fill(283,324+2,378,324+48,GRAY);		
				if(Sensor_Data->Current_humidity2<0)
				Draw_word(283,324,24,48,0xff00,fuhao[0]);
				Draw_word(283+24,324,24,48,0xff00,shuzhi[(abs(Sensor_Data->Current_humidity2)/100)%10]);
				Draw_word(283+24*2,324,24,48,0xff00,shuzhi[(abs(Sensor_Data->Current_humidity2)/10)%10]);
				Draw_word(283+24*3,324,24,48,0xff00,shuzhi[abs(Sensor_Data->Current_humidity2)%10]);
			}
				if(last_water_quality2!=Sensor_Data->WaterLevel2)
			{
				LCD_Fill(283,380+2,378,380+48,GRAY);		
				if(Sensor_Data->WaterLevel2<0)
				Draw_word(283,380,24,48,0xff00,fuhao[0]);
				Draw_word(283+24,380,24,48,0xff00,shuzhi[(abs(Sensor_Data->water_quality2)/100)%10]);
				Draw_word(283+24*2,380,24,48,0xff00,shuzhi[(abs(Sensor_Data->water_quality2)/10)%10]);
				Draw_word(283+24*3,380,24,48,0xff00,shuzhi[abs(Sensor_Data->water_quality2)%10]);
			}
			
			////////////////////3////////////////////////////
				if(last_level3!=Sensor_Data->WaterLevel3)
			{
				LCD_Fill(380,156+2,475,156+48,GRAY);	
				if(Sensor_Data->WaterLevel3<0)
				Draw_word(380,156,24,48,0xff00,fuhao[0]);
				Draw_word(380+24,156,24,48,0xff00,shuzhi[(abs(Sensor_Data->WaterLevel3)/100)%10]);
				Draw_word(380+24*2,156,24,48,0xff00,shuzhi[(abs(Sensor_Data->WaterLevel3)/10)%10]);
				Draw_word(380+24*3,156,24,48,0xff00,shuzhi[abs(Sensor_Data->WaterLevel3)%10]);
			}
				if(last_rain3!=Sensor_Data->Rainfall_index3)
			{
				LCD_Fill(380,212+2,475,212+48,GRAY);	
				if(Sensor_Data->Rainfall_index3<0)
				Draw_word(380,212,24,48,0xff00,fuhao[0]);
				Draw_word(380+24,212,24,48,0xff00,shuzhi[(abs(Sensor_Data->Rainfall_index3)/100)%10]);
				Draw_word(380+24*2,212,24,48,0xff00,shuzhi[(abs(Sensor_Data->Rainfall_index3)/10)%10]);
				Draw_word(380+24*3,212,24,48,0xff00,shuzhi[abs(Sensor_Data->Rainfall_index3)%10]);
			}
				if(last_temp3!=Sensor_Data->Current_temperature3)
			{
				LCD_Fill(380,268+2,475,268+48,GRAY);	
				if(Sensor_Data->Current_temperature3<0)
				Draw_word(380,268,24,48,0xff00,fuhao[0]);
				Draw_word(380+24,268,24,48,0xff00,shuzhi[(abs(Sensor_Data->Current_temperature3)/100)%10]);
				Draw_word(380+24*2,268,24,48,0xff00,shuzhi[(abs(Sensor_Data->Current_temperature3)/10)%10]);
				Draw_word(380+24*3,268,24,48,0xff00,shuzhi[abs(Sensor_Data->Current_temperature3)%10]);
			}
				if(last_humi3!=Sensor_Data->Current_humidity3)
			{
				LCD_Fill(380,324+2,475,324+48,GRAY);		
				if(Sensor_Data->Current_humidity3<0)
				Draw_word(380,324,24,48,0xff00,fuhao[0]);
				Draw_word(380+24,324,24,48,0xff00,shuzhi[(abs(Sensor_Data->Current_humidity3)/100)%10]);
				Draw_word(380+24*2,324,24,48,0xff00,shuzhi[(abs(Sensor_Data->Current_humidity3)/10)%10]);
				Draw_word(380+24*3,324,24,48,0xff00,shuzhi[abs(Sensor_Data->Current_humidity3)%10]);
			}
				if(last_water_quality3!=Sensor_Data->WaterLevel3)
			{
				LCD_Fill(380,380+2,475,380+48,GRAY);		
				if(Sensor_Data->WaterLevel3<0)
				Draw_word(380,380,24,48,0xff00,fuhao[0]);
				Draw_word(380+24,380,24,48,0xff00,shuzhi[(abs(Sensor_Data->water_quality3)/100)%10]);
				Draw_word(380+24*2,380,24,48,0xff00,shuzhi[(abs(Sensor_Data->water_quality3)/10)%10]);
				Draw_word(380+24*3,380,24,48,0xff00,shuzhi[abs(Sensor_Data->water_quality3)%10]);
			}
			
			
				last_level1=Sensor_Data->WaterLevel1;
				last_rain1=Sensor_Data->Rainfall_index1;
				last_temp1=Sensor_Data->Current_temperature1;
				last_humi1=Sensor_Data->Current_humidity1;
				last_water_quality1=Sensor_Data->water_quality1;
				last_level2=Sensor_Data->WaterLevel2;
				last_rain2=Sensor_Data->Rainfall_index2;
				last_temp2=Sensor_Data->Current_temperature2;
				last_humi2=Sensor_Data->Current_humidity2;
				last_water_quality2=Sensor_Data->water_quality2;
				last_level3=Sensor_Data->WaterLevel3;
				last_rain3=Sensor_Data->Rainfall_index3;                                                                      
				last_temp3=Sensor_Data->Current_temperature3;
				last_humi3=Sensor_Data->Current_humidity3;
				last_water_quality3=Sensor_Data->water_quality3;
	}
	
	
	
	//刷新传感器图标
void lcd_sensorlogo_refresh(int data)
	{
		if(Sensor_Data.water_quality1 > water_quality1_Max||Sensor_Data.water_quality2 > water_quality1_Max||Sensor_Data.water_quality3 > water_quality1_Max)
			Draw_word(6,324+56,56,56,RED,shuizhi_biao[0]);
		else
			Draw_word(6,324+56,56,56,0xff11,shuizhi_biao[0]);

		if(Sensor_Data.Current_humidity1 > 60||Sensor_Data.Current_humidity2 > 60||Sensor_Data.Current_humidity3 > 60)
			Draw_word(6,268+56,56,56,RED,shidu_biao[0]);
		else
			Draw_word(6,268+56,56,56,0xff11,shidu_biao[0]);

		if(Sensor_Data.Current_temperature1 > 24||Sensor_Data.Current_temperature2 > 24||Sensor_Data.Current_temperature3 > 24)
			Draw_word(6,212+56,56,56,RED,wendu_biao[0]);
		else
			Draw_word(6,212+56,56,56,0xff11,wendu_biao[0]);

		if(Sensor_Data.Rainfall_index1 > Rainfall_index1_Max||Sensor_Data.Rainfall_index2 > Rainfall_index1_Max||Sensor_Data.Rainfall_index3 > Rainfall_index1_Max)
			Draw_word(6,156+56,56,56,RED,yudi_biao[0]);
		else
			Draw_word(6,156+56,56,56,0xff11,yudi_biao[0]);

    if(Sensor_Data.WaterLevel1 > WaterLevel1_Max||Sensor_Data.WaterLevel2 > WaterLevel1_Max||Sensor_Data.WaterLevel3 > WaterLevel1_Max)
			Draw_word(6,100+56,56,56,RED,shuiwei_biao[0]);
    else
			Draw_word(6,100+56,56,56,0xff11,shuiwei_biao[0]);
	  }
		

	void draw_weather(u8 weather1,u8 high_temp1,u8 low_temp1,u8 weather2,u8 high_temp2,u8 low_temp2)
	{
		static int last_weather1=8;
		static int last_high_temp1=8;
		static int last_low_temp1=8;
		static int last_weather2=8;
		static int last_high_temp2=8;
		static int last_low_temp2=8;

		if(last_weather1!=weather1) //刷新第一天图标
		{
			LCD_Fill(8, 540-39,8+128, 540+128-39, GRAY);
			//LCD_Fill(150,540+16,150+80,540+16+40,GRAY);	
			if((0<=weather1)&&(weather1<=3))
			{
				Draw_word(8,540-39,128,128,LIGHTBLUE,qing_logo[0]);  //刷新logo
			}
			if(weather1==9)
			{
							Draw_word(8,540-39,128,128,LIGHTBLUE,ying_logo[0]);  //刷新logo
			}
			if((4<=weather1)&&(weather1<=8))
			{
							Draw_word(8,540-39,128,128,LIGHTBLUE,duoyun_logo[0]);  //刷新logo
			}
			if(10<=weather1)
			{
							Draw_word(8,540-39,128,128,LIGHTBLUE,yu_logo[0]);  //刷新logo
			}
			
		}
		if(last_weather2!=weather2) //刷新第二天图标
		{
			LCD_Fill(8+236, 540-39,8+128+236, 540+128-39, GRAY);
			//LCD_Fill(150+236,540+16,150+80+236,540+16+40,GRAY);
				if((0<=weather1)&&(weather1<=3))
			{
							Draw_word(8+236,540-39,128,128,LIGHTBLUE,qing_logo[0]);  //刷新logo
			}
			if(weather1==9)
			{
							Draw_word(8+236,540-39,128,128,LIGHTBLUE,ying_logo[0]);  //刷新logo
			}
			if((4<=weather1)&&(weather1<=8))
			{
							Draw_word(8+236,540-39,128,128,LIGHTBLUE,duoyun_logo[0]);  //刷新logo
			}
			if(10<=weather1)
			{
							Draw_word(8+236,540-39,128,128,LIGHTBLUE,yu_logo[0]);  //刷新logo
			
			}
			
		}
		
		if(last_low_temp1!=low_temp1) //刷新第一天最低温度
		{
			LCD_Fill(140,540+16*2+40-39,140+60, 540+16*2+80-39,GRAY);
			if(low_temp1<0)  //负数
			Draw_word(140,540+16*2+40-39,24,39,LBBLUE,tianqi_shuzhi[10]);  //刷新数字
			Draw_word(140+20,540+16*2+40-39,24,39,LBBLUE,tianqi_shuzhi[(abs(low_temp1)/10)%10]);  //刷新数字
			Draw_word(140+20*2,540+16*2+40-39,24,39,LBBLUE,tianqi_shuzhi[abs(low_temp1)%10]);  //刷新数字
		}
		if(last_high_temp1!=high_temp1) //刷新第一天最高温度
		{
			LCD_Fill(140,540+16-39,140+60, 540+16+39-39,GRAY);
			if(high_temp1<0)  //负数
			Draw_word(140,540+16-39,24,39,LBBLUE,tianqi_shuzhi[10]);  //刷新数字
			Draw_word(140+20,540+16-39,24,39,LBBLUE,tianqi_shuzhi[(abs(high_temp1)/10)%10]);  //刷新数字
			Draw_word(140+20*2,540+16-39,24,39,LBBLUE,tianqi_shuzhi[abs(high_temp1)%10]);  //刷新数字
		}
				if(last_low_temp2!=low_temp2) //刷新第二天最低温度
		{
			LCD_Fill(120+236,540+16*2+40-39,140+236+20*3, 540+16*2+80-39,GRAY);
			if(low_temp2<1)  //负数
			Draw_word(140+236,540+16*2+40-39,24,39,LBBLUE,tianqi_shuzhi[10]);  //刷新数字
			Draw_word(140+236+20,540+16*2+40-39,24,39,LBBLUE,tianqi_shuzhi[(abs(low_temp2)/10)%10]);  //刷新数字
			Draw_word(140+236+20*2,540+16*2+40-39,24,39,LBBLUE,tianqi_shuzhi[abs(low_temp2)%10]);  //刷新数字
		}
		if(last_high_temp2!=high_temp2) //刷新第二天最高温度
		{
			LCD_Fill(140+236,540+16-39,140+236+20*3, 540+16+39-39,GRAY);
			if(high_temp2<1)  //负数
			Draw_word(140+236,540+16-39,24,39,LBBLUE,tianqi_shuzhi[10]);  //刷新数字
			Draw_word(140+236+20,540+16-39,24,39,LBBLUE,tianqi_shuzhi[(abs(high_temp2)/10)%10]);  //刷新数字
			Draw_word(140+236+20*2,540+16-39,24,39,LBBLUE,tianqi_shuzhi[abs(high_temp2)%10]);  //刷新数字
		}
		
		last_weather1=weather1;
		last_low_temp1=low_temp1;
		last_high_temp1=high_temp1;
		last_weather2=weather2;
		last_low_temp2=low_temp2;
		last_high_temp2=high_temp2;
	};

	//在没有按键操作情况下。根据按键外其他控制的结果，刷新lcd执行器
void lcd_actuator_refresh1(AJ_widget_t *AJ_widget_SW)  //根据云平台结果，刷新数据
		{
			if(AJ_widget_SW->Drainage_machine1==AJ_ON)
		{
			
			Draw_word(7+10,639,24,39,0xcd2626,tianqi_shuzhi[1]);  //刷新数字
		}
		else
		{
			Draw_word(7+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
		}
		if(AJ_widget_SW->Drainage_machine2==AJ_ON)
		{
						Draw_word(7+44,639,24,39,0xcd2626,tianqi_shuzhi[2]);  //刷新数字
		}
		else
		{
			Draw_word(7+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
		}
		if(AJ_widget_SW->Drainage_machine3==AJ_ON)
		{
			Draw_word(7+78,639,24,39,0xcd2626,tianqi_shuzhi[3]);  //刷新数字
		}
		else
		{
			Draw_word(7+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
		}                                       
		if(AJ_widget_SW->Drainage_machine1||AJ_widget_SW->Drainage_machine2||AJ_widget_SW->Drainage_machine3)
			Draw_word(7,678,112,112,0xcd2626,choushuiji[0]);  //选中的，变色
		else
      Draw_word(7,678,112,112,0xffff,choushuiji[0]);  //不变色
		////////////////////////////////////
		if(AJ_widget_SW->Water_level_alarm1)
		{
			Draw_word(7+118+10,639,24,39,0xcd2626,tianqi_shuzhi[1]);  //刷新数字
		}
		else
		{
			Draw_word(7+118+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
		}
		if(AJ_widget_SW->Water_level_alarm2)
		{
			Draw_word(7+118+44,639,24,39,0xcd2626,tianqi_shuzhi[2]);  //刷新数字
		}
		else
		{
			Draw_word(7+118+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
		}
		if(AJ_widget_SW->Water_level_alarm3)
		{
			Draw_word(7+118+78,639,24,39,0xcd2626,tianqi_shuzhi[3]);  //刷新数字
		}
		else
		{
			Draw_word(7+118+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
		}
		if(AJ_widget_SW->Water_level_alarm1||AJ_widget_SW->Water_level_alarm2||AJ_widget_SW->Water_level_alarm3)
			Draw_word(7+118,678,112,112,0xcd2626,shuiweiyujing[0]);  //选中的，变色
		else
      Draw_word(7+118,678,112,112,0xffff,shuiweiyujing[0]);  //不变色
		/////////////////////////////////////
		if(AJ_widget_SW->Rainfall_alarm1)
		{
			Draw_word(7+118*2+10,639,24,39,0xcd2626,tianqi_shuzhi[1]);  //刷新数字
		}
		else 
		{
			Draw_word(7+118*2+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
		}
		if(AJ_widget_SW->Rainfall_alarm2)
		{
			Draw_word(7+118*2+44,639,24,39,0xcd2626,tianqi_shuzhi[2]);  //刷新数字
		}
		else 
		{
			Draw_word(7+118*2+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
		}
		if(AJ_widget_SW->Rainfall_alarm3)
		{
			Draw_word(7+118*2+78,639,24,39,0xcd2626,tianqi_shuzhi[3]);  //刷新数字
		}
		else 
		{
			Draw_word(7+118*2+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
		}
		if(AJ_widget_SW->Rainfall_alarm1||AJ_widget_SW->Rainfall_alarm2||AJ_widget_SW->Rainfall_alarm3)
			Draw_word(7+118*2,678,112,112,0xcd2626,jiangyubaojing[0]); //选中的，变色
		else
      Draw_word(7+118*2,678,112,112,0xffff,jiangyubaojing[0]);  //不变色
		/////////////////////////////////////////
		if(AJ_widget_SW->Water_quality_alarm1)
		{
			Draw_word(7+118*3+10,639,24,39,0xcd2626,tianqi_shuzhi[1]);  //刷新数字
		}
		else
		{
			Draw_word(7+118*3+10,639,24,39,0xffff,tianqi_shuzhi[1]);  //刷新数字
		}
		if(AJ_widget_SW->Water_quality_alarm2)
		{
			Draw_word(7+118*3+44,639,24,39,0xcd2626,tianqi_shuzhi[2]);  //刷新数字
		}
		else
		{
			Draw_word(7+118*3+44,639,24,39,0xffff,tianqi_shuzhi[2]);  //刷新数字
		}
		if(AJ_widget_SW->Water_quality_alarm3)
		{
			Draw_word(7+118*3+78,639,24,39,0xcd2626,tianqi_shuzhi[3]);  //刷新数字
		}
		else
		{
			Draw_word(7+118*3+78,639,24,39,0xffff,tianqi_shuzhi[3]);  //刷新数字
		}
		if(AJ_widget_SW->Water_quality_alarm1||AJ_widget_SW->Water_quality_alarm2||AJ_widget_SW->Water_quality_alarm3)
			Draw_word(7+118*3,678,112,112,0xcd2626,shuizhiyujing[0]);  //选中的，变色
		else
      Draw_word(7+118*3,678,112,112,0xffff,shuizhiyujing[0]);  //不变色

	}
		
	
