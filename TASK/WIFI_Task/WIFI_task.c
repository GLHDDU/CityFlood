#include "WIFI_task.h"
#include "sensors.h"
#include "queue.h"
#include "main.h"
#include "usart2.h"  
#include "wifi.h"
#include "mqtt.h"
#include "dht11.h"
#include "led.h"
#include <stdio.h>
#include <stdlib.h>
#include "timer2.h"
#include "timer4.h"
#include "timer5.h"
#include "widget.h"
#include "Adjustment_task.h"
int wifi_model;
//����������
extern Sensor_Data_t Sensor_Data;
extern Sensor_Data_t Last_Sensor_Data;

//���ڿؼ�����
extern AJ_widget_t AJ_widget_SW;	
extern AJ_widget_t Last_AJ_widget_SW;

//�Զ����ڱ�־λ
extern char IsAuto_flash;

char *cmdid = NULL;  //������λ������Ĺؼ���

//WIFI������
void WIFI_task(void *pvParameters)
{
	printf("WIFI_task\r\n");
	
	WIFI_init();//WIFI��ʼ��
	
  vTaskDelay(100);
	
	while(1)		
	{	
		if(Connect_flag==1) //���ӷ������ɹ�  
		{   		
			Handle_TxDataBuff(); /*1���������ͻ���������*/		
			Handle_RxDataBuff(); /*2���������ջ���������*/			
			Handle_CMDBuf();		 /*3�����������������*/
		}	
		else								//�������ӷ�����
		{ 			
			ReconnectSever();
		}
	  vTaskDelay(100);
	}	
}

//WIFI��ʼ��
void WIFI_init(void)
{
	Usart2_Init(115200);//WIFI		//WIFIģ�鴮��
	TIM4_Init(300,7200);//?       //TIM4��ʼ������ʱʱ�� 300*7200*1000/72000000 = 30ms

	/*while(DHT11_Init())	//DHT11��ʼ��	
	{
		printf("DHT11_INIT error \r\n"); 
	}
		printf("DHT11_INIT success \r\n"); 	
	*/
	WiFi_ResetIO_Init();            //��ʼ��WiFi�ĸ�λIO
  MQTT_Buff_Init();               //��ʼ������,����,�������ݵ� ������ �Լ���״̬����
	AliIoT_Parameter_Init();	    //��ʼ�����Ӱ�����IoTƽ̨MQTT�������Ĳ���
	
}


	
/*�������ͻ���������*/
void Handle_TxDataBuff(void)
{
		if(MQTT_TxDataOutPtr != MQTT_TxDataInPtr){//���ͻ�������������
		//3������ɽ���if
		//��1�֣�0x10 ���ӱ���
		//��2�֣�0x82 ���ı��ģ���ConnectPack_flag��λ����ʾ���ӱ��ĳɹ�
		//��3�֣�SubcribePack_flag��λ��˵�����ӺͶ��ľ��ɹ����������Ŀɷ�
		if((MQTT_TxDataOutPtr[2]==0x10)||((MQTT_TxDataOutPtr[2]==0x82)&&(ConnectPack_flag==1))||(SubcribePack_flag==1)){    
			printf("��������:0x%x\r\n",MQTT_TxDataOutPtr[2]);  //������ʾ��Ϣ
			MQTT_TxData(MQTT_TxDataOutPtr);                       //�������ݣ�����2���ͻ������е����ݣ�
			MQTT_TxDataOutPtr += BUFF_UNIT;                       //ָ������
			if(MQTT_TxDataOutPtr==MQTT_TxDataEndPtr)              //���ָ�뵽������β����
				MQTT_TxDataOutPtr = MQTT_TxDataBuf[0];              //ָ���λ����������ͷ
		} 				
	}	
}

/*�������ջ���������*/
void Handle_RxDataBuff(void)
{
		if(MQTT_RxDataOutPtr != MQTT_RxDataInPtr){//���ջ�������������														
			printf("���յ�����:\r\n");
			
			/*2.1����յ�����CONNECT����*/
			if(MQTT_RxDataOutPtr[2]==0x20){//�յ�����CONNECT����             			
					switch(MQTT_RxDataOutPtr[5]){//�ж�CONNECT�����Ƿ�ɹ�					
					case 0x00 : printf("CONNECT���ĳɹ�\r\n");  
									ConnectPack_flag = 1;                                        //CONNECT���ĳɹ������ı��Ŀɷ�
						break;                                                                                           
					case 0x01 : printf("�����Ѿܾ�����֧�ֵ�Э��汾��׼������\r\n");
								Connect_flag = 0;                                            //Connect_flag���㣬��������
								break;
					case 0x02 : printf("�����Ѿܾ������ϸ�Ŀͻ��˱�ʶ����׼������\r\n");
								Connect_flag = 0;                                            //Connect_flag���㣬��������
								break;
					case 0x03 : printf("�����Ѿܾ�������˲����ã�׼������\r\n");
								Connect_flag = 0;                                            //Connect_flag���㣬��������
								break;
					case 0x04 : printf("�����Ѿܾ�����Ч���û��������룬׼������\r\n");
								Connect_flag = 0;                                            //Connect_flag���㣬��������						
								break;
					case 0x05 : printf("�����Ѿܾ���δ��Ȩ��׼������\r\n");
								Connect_flag = 0;                                            //Connect_flag���㣬��������						
								break; 
					default   : printf("�����Ѿܾ���δ֪״̬��׼������\r\n");
								Connect_flag = 0;                                            //Connect_flag���㣬��������					
								break;							
				}				
			}		
			
			/*2.2����յ�����SUBACK����*/
			else if(MQTT_RxDataOutPtr[2]==0x90){//�ж�SUBACK�����Ƿ�ɹ�		
				switch(MQTT_RxDataOutPtr[6]){					
					case 0x00 :
					case 0x01 : printf("���ĳɹ�\r\n");
											SubcribePack_flag = 1;                //SubcribePack_flag��1����ʾ���ı��ĳɹ����������Ŀɷ���
											Ping_flag = 0;                        //Ping_flag����
											TIM5_ENABLE_30S();                    //����30s��PING��ʱ��
											TIM2_ENABLE_30S();                    //����30s���ϴ����ݵĶ�ʱ��  //Ŀǰ��30/6=5S�ϱ�һ��  
										//	TempHumi_State();                     //�ȷ�һ������
								break;                               
					default   : printf("����ʧ�ܣ�׼������\r\n"); 
											Connect_flag = 0;                     //Connect_flag���㣬��������
								break;						
				}					
			}
			
			/*2.3����յ�����PINGRESP����*/
			else if(MQTT_RxDataOutPtr[2]==0xD0){ 
				printf("PING���Ļظ�\r\n");
				if(Ping_flag==1){             //���Ping_flag=1����ʾ��һ�η���
					 Ping_flag = 0;    				  //Ҫ���Ping_flag��־
				}else if(Ping_flag>1){ 				//���Ping_flag>1����ʾ�Ƕ�η����ˣ�������2s����Ŀ��ٷ���
					Ping_flag = 0;     				  //Ҫ���Ping_flag��־
					TIM5_ENABLE_30S(); 				  //PING��ʱ���ػ�30s��ʱ��
				}				
			}	
			
			/*2.4����յ����Ƿ�������������������*/			
			else if((MQTT_RxDataOutPtr[2]==0x30)){ //����Ҫ��ȡ��������
				printf("�������ȼ�0����\r\n");
				MQTT_DealPushdata_Qs0(MQTT_RxDataOutPtr);  //�����ȼ�0��������
			}				
							
			MQTT_RxDataOutPtr += BUFF_UNIT;                   //ָ������
			if(MQTT_RxDataOutPtr==MQTT_RxDataEndPtr)          //���ָ�뵽������β����
				MQTT_RxDataOutPtr = MQTT_RxDataBuf[0];          //ָ���λ����������ͷ                        
		}	
}




/*���������������*/
void Handle_CMDBuf(void)
{
		if(MQTT_CMDOutPtr != MQTT_CMDInPtr){//˵�����������������			       
			printf("����:%s\r\n",&MQTT_CMDOutPtr[2]);
			
			/*3.1�򵥲����ͽ������*/
			
			//���ص�demo
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"powerstate\":1}"))
			{                
				led_green_on();
				printf("led_green_on !        \r\n");
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"powerstate\":0}"))
			{
				led_green_off();
				printf("led_green_off !       \r\n");
			}			
			
						//��ȵ��
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"IsAuto\":1}"))
			{                
				IsAuto_flash=Auto;
				printf("Auto controling!\r\n");
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"IsAuto\":0}"))
			{
				IsAuto_flash=Manual;	
				printf("Manual controing!\r\n");
			}		
			//��ˮ����
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Drainage_machine1\":1}"))
			{                
				AJ_widget_SW.Drainage_machine1=AJ_ON;	
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Drainage_machine1\":0}"))
			{
				AJ_widget_SW.Drainage_machine1=AJ_OFF;	
			}			
			//ˮλ����
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Water_level_alarm1\":1}"))
			{                
				AJ_widget_SW.Water_level_alarm1=AJ_ON;	
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Water_level_alarm1\":0}"))
			{
				AJ_widget_SW.Water_level_alarm1=AJ_OFF;	
			}						
			//���꾯��
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Rainfall_alarm1\":1}"))
			{                
				AJ_widget_SW.Rainfall_alarm1=AJ_ON;	
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Rainfall_alarm1\":0}"))
			{
				AJ_widget_SW.Rainfall_alarm1=AJ_OFF;	
			}			
			//ˮ�ʾ���
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Water_quality_alarm1\":1}"))
			{                
				AJ_widget_SW.Water_quality_alarm1=AJ_ON;	
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Water_quality_alarm1\":0}"))
			{
				AJ_widget_SW.Water_quality_alarm1=AJ_OFF;	
			}				
			
						//��ˮ����
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Drainage_machine2\":1}"))
			{                
				AJ_widget_SW.Drainage_machine2=AJ_ON;	
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Drainage_machine2\":0}"))
			{
				AJ_widget_SW.Drainage_machine2=AJ_OFF;	
			}			
			//ˮλ����
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Water_level_alarm2\":1}"))
			{                
				AJ_widget_SW.Water_level_alarm2=AJ_ON;	
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Water_level_alarm2\":0}"))
			{
				AJ_widget_SW.Water_level_alarm2=AJ_OFF;	
			}						
			//���꾯��
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Rainfall_alarm2\":1}"))
			{                
				AJ_widget_SW.Rainfall_alarm2=AJ_ON;	
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Rainfall_alarm2\":0}"))
			{
				AJ_widget_SW.Rainfall_alarm2=AJ_OFF;	
			}			
			//ˮ�ʾ���
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Water_quality_alarm2\":1}"))
			{                
				AJ_widget_SW.Water_quality_alarm2=AJ_ON;	
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Water_quality_alarm2\":0}"))
			{
				AJ_widget_SW.Water_quality_alarm2=AJ_OFF;	
			}				
			
						//��ˮ����
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Drainage_machine3\":1}"))
			{                
				AJ_widget_SW.Drainage_machine3=AJ_ON;	
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Drainage_machine3\":0}"))
			{
				AJ_widget_SW.Drainage_machine3=AJ_OFF;	
			}			
			//ˮλ����
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Water_level_alarm3\":1}"))
			{                
				AJ_widget_SW.Water_level_alarm3=AJ_ON;	
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Water_level_alarm3\":0}"))
			{
				AJ_widget_SW.Water_level_alarm3=AJ_OFF;	
			}						
			//���꾯��
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Rainfall_alarm3\":1}"))
			{                
				AJ_widget_SW.Rainfall_alarm3=AJ_ON;	
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Rainfall_alarm3\":0}"))
			{
				AJ_widget_SW.Rainfall_alarm3=AJ_OFF;	
			}			
			//ˮ�ʾ���
			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Water_quality_alarm3\":1}"))
			{                
				AJ_widget_SW.Water_quality_alarm3=AJ_ON;	
			}else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"Water_quality_alarm3\":0}"))
			{
				AJ_widget_SW.Water_quality_alarm3=AJ_OFF;	
			}				
			

		/*3.2רҵ���ݷ���*/		
			
//		//�ŷ���1 demo
//		if(strstr((char *)MQTT_CMDOutPtr+2, (const char *)"\"params\":{\"Ventilator1\"") != NULL)//רҵ���ݷ���������Ӣ�ĺ�����
//		{			 
//			cmdid=USER_GetSteeringJsonValue((char *)MQTT_CMDOutPtr+2, (char *)"Ventilator1");
//			printf("�����������ݣ�%s\r\n",cmdid);
//			if(*cmdid=='1')
//			{
//				AJ_widget_SW.Ventilator1=AJ_ON;	
//			}				
//			else if(*cmdid=='0')
//			{
//				AJ_widget_SW.Ventilator1=AJ_OFF;		
//			}
//		}			
			
				 MQTT_CMDOutPtr += BUFF_UNIT;                             //ָ������
				 if(MQTT_CMDOutPtr==MQTT_CMDEndPtr)           	          //���ָ�뵽������β����
					MQTT_CMDOutPtr = MQTT_CMDBuf[0];          	            //ָ���λ����������ͷ				
			}	
}
/*����������*/
void ReconnectSever(void)
{
		printf("��Ҫ���ӷ�����\r\n");                //���������Ϣ
		TIM_Cmd(TIM4,DISABLE);                          //�ر�TIM4 
		TIM_Cmd(TIM5,DISABLE);                          //�ر�TIM5  
		WiFi_RxCounter=0;                               //WiFi������������������                        
		memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);         //���WiFi���ջ����� 
		if(wifi_model==0)
		{
			if(get_current_weather()==0){   			     		//���WiFi�����Ʒ�������������0����ʾ��ȷ������if
					printf("��ȡ�������ݳɹ�\r\n");             //���������Ϣ
					WiFi_RxCounter=0;                             //WiFi������������������                        
					memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);       //���WiFi���ջ����� 		
					MQTT_Buff_ReInit(); //���³�ʼ�����ͻ�����  
				 wifi_model=1;		
				}	
	  }
		if(WiFi_Connect_IoTServer()==0){   			     		//���WiFi�����Ʒ�������������0����ʾ��ȷ������if
			printf("����TCP���ӳɹ�\r\n");             //���������Ϣ
			Connect_flag = 1;                             //Connect_flag��1����ʾ���ӳɹ�	
			WiFi_RxCounter=0;                             //WiFi������������������                        
			memset(WiFi_RX_BUF,0,WiFi_RXBUFF_SIZE);       //���WiFi���ջ����� 		
			MQTT_Buff_ReInit();                           //���³�ʼ�����ͻ�����                    
		}			
}

/*�ϴ�����������*/
void Upload_Sensors_Data(Sensor_Data_t *Sensor_Data)
{	
	char temp[256];
	printf("A\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":\
	{\"WaterLevel1\":%2d,\"Rainfall_index1\":%2d,\"Current_temperature1\":%2d,\"Current_humidity1\":%2d,\"water_quality1\":%2d},\"version\":\"1.0.0\"}",\
	Sensor_Data->WaterLevel1,Sensor_Data->Rainfall_index1,Sensor_Data->Current_temperature1,Sensor_Data->Current_humidity1,Sensor_Data->water_quality1);  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //�������ݣ�������������
	
sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":\
	{\"WaterLevel2\":%2d,\"Rainfall_index2\":%2d,\"Current_temperature2\":%2d,\"Current_humidity2\":%2d,\"water_quality2\":%2d},\"version\":\"1.0.0\"}",\
	Sensor_Data->WaterLevel2,Sensor_Data->Rainfall_index2,Sensor_Data->Current_temperature2,Sensor_Data->Current_humidity2,Sensor_Data->water_quality2);  //�����ظ�ʪ���¶�����
		MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //�������ݣ�������������

	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":\
	{\"WaterLevel3\":%2d,\"Rainfall_index3\":%2d,\"Current_temperature3\":%2d,\"Current_humidity3\":%2d,\"water_quality3\":%2d,},\"version\":\"1.0.0\"}",\
	Sensor_Data->WaterLevel3,Sensor_Data->Rainfall_index3,Sensor_Data->Current_temperature3,Sensor_Data->Current_humidity3,Sensor_Data->water_quality3);  //�����ظ�ʪ���¶�����
		MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //�������ݣ�������������


	
	printf("B\r\n");
}


/*����demo(�ɼ���ʪ�ȣ���������������)*/
void TempHumi_State(void)    
{  
	u8 tempdata,humidata;	
	char temp[256];  
	//DHT11_Read_Data(&tempdata,&humidata);	//��ȡ��ʪ��ֵ(���Թ��ˣ��ڶ�ʱ���ж�������������������Ῠ����ԭ����)	
	tempdata=10;
	humidata=20;
	//�����������Ȳ���
	printf("test�¶ȣ�%d  ʪ�ȣ�%d\r\n",tempdata,humidata);

	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"CuTemperature\":%2d,\"CurrentHumidity\":%2d},\"version\":\"1.0.0\"}",tempdata,humidata);  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //�������ݣ�������������	
	
}
/*******************************************************************
*������unsigned char *USER_GetSteeringJsonValue(char *cJson, char *Tag)
*���ܣ�jsonΪ�ַ������У���json��ʽ�е�Ŀ�����Tag��Ӧ��ֵ�ַ���ת��Ϊ�ַ���
*���룺
		char *cJson json�ַ���
		char *Tag Ҫ�����Ķ����ǩ
*�����������ֵ
*����˵�����û������ڴ˻����ϸ������չ�ú���������ֻ�Ǹ��򵥵�DEMO
*******************************************************************/
char temp1[16];  // Ŀ���ַ�����
char *USER_GetSteeringJsonValue(char *cJson, char *Tag)
{ 
	char *target = NULL;
  char *dest_str; // Ŀ���ַ���
	int8_t i=0;
	memset(temp1, 0x00, 128);
	sprintf(temp1,"\"%s\":\"",Tag);
	target=strstr((const char *)cJson, (const char *)temp1);
	if(target == NULL)
	{
		printf("���ַ���\r\n");
		return NULL;
	}
	i=strlen((const char *)temp1);
	target=target+i;   //��ַΪ���ݵ�ַ
	memset(temp1, 0x00, 128);
	for(i=0; i<12; i++, target++)//��ֵ����10��λΪ�Ƿ�������2^32=4294967296
	{
		if((*target!='"'))
		{
			temp1[i]=*target;
		}
		else
		{
			break;
		}
	}
	temp1[i+1] = '\0';
		//u1_printf("��ȡ������:%s\r\n",temp1);   
    dest_str = (char *)malloc(sizeof(char) * (sizeof(temp1) + 1)); /* Ϊ�ַ�������ѿռ� */
    strncpy(dest_str, temp1, sizeof(temp1));  // ��C��׼�⺯��strncpy�����ַ�
	  printf("��������Ļ�ùؼ���:%s\r\n",dest_str);
	return dest_str;
}

