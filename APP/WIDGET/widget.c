#include "widget.h"
#include "usart3.h"
#include "mqtt.h"
#include "string.h"       //������Ҫ��ͷ�ļ�
AJ_widget_t AJ_widget_SW;	//���ڿؼ�����
AJ_widget_t Last_AJ_widget_SW;	//���ڿؼ�����

/****************************��ʼ��**********************************************/
void AJ_widgets_Init(void)
{

	//��zigbee�����ݡ�����Ҫ��ʼ��
	Clear_AJ_widget_SW();		/*���ر�־λ����*/
}

/*���ر�־λ����*/
void Clear_AJ_widget_SW(void)
{
	AJ_widget_SW.Drainage_machine1=0;//��ˮ��
	AJ_widget_SW.Water_level_alarm1=0;//ˮλ����
	AJ_widget_SW.Rainfall_alarm1=0;//���꾯��
	AJ_widget_SW.Water_quality_alarm1=0;//ˮ�ʾ���
	
	AJ_widget_SW.Drainage_machine2=0;//��ˮ��
	AJ_widget_SW.Water_level_alarm2=0;//ˮλ����
	AJ_widget_SW.Rainfall_alarm2=0;//���꾯��
	AJ_widget_SW.Water_quality_alarm2=0;//ˮ�ʾ���
	
	AJ_widget_SW.Drainage_machine3=0;//��ˮ��
	AJ_widget_SW.Water_level_alarm3=0;//ˮλ����
	AJ_widget_SW.Rainfall_alarm3=0;//���꾯��
	AJ_widget_SW.Water_quality_alarm3=0;//ˮ�ʾ���
}

/*********************************�ؼ�ʵ��***************************************/
char temp[256];
/////////////1///////////////////
//������ˮ��
void Drainage_machine1_ON(void)
{
	u3_printf("Drainage_machine1_ON");
	printf("Drainage_machine1_ON\r\n");
		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Drainage_machine1\":1},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
void Drainage_machine1_OFF(void)
{
	u3_printf("Drainage_machine1_OFF");
	printf("Drainage_machine1_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Drainage_machine1\":0},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
//����ˮλ������
void Water_level_alarm1_ON(void)
{
	u3_printf("Water_level_alarm1_ON");
	printf("Water_level_alarm1_ON\r\n");
		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_level_alarm1\":1},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
void Water_level_alarm1_OFF(void)
{
	u3_printf("Water_level_alarm1_OFF");
	printf("Water_level_alarm1_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_level_alarm1\":0},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}

//���ؽ��꾯��ָʾ��
void Rainfall_alarm1_ON(void)
{
	u3_printf("Rainfall_alarm1_ON");
	printf("Rainfall_alarm1_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Rainfall_alarm1\":1},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
void Rainfall_alarm1_OFF(void)
{
	u3_printf("Rainfall_alarm1_OFF");
	printf("Rainfall_alarm1_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Rainfall_alarm1\":0},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}

//����ˮ�ʱ�����
void Water_quality_alarm1_ON(void)
{
	u3_printf("Water_quality_alarm1_ON");
	printf("Water_quality_alarm1_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_quality_alarm1\":1},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
void Water_quality_alarm1_OFF(void)
{
	u3_printf("Water_quality_alarm1_OFF");
	printf("Water_quality_alarm1_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_quality_alarm1\":0},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}

///////////////////2///////////////////
//������ˮ��
void Drainage_machine2_ON(void)
{
	u3_printf("Drainage_machine2_ON");
	printf("Drainage_machine2_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Drainage_machine2\":1},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
void Drainage_machine2_OFF(void)
{
	u3_printf("Drainage_machine2_OFF");
	printf("Drainage_machine2_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Drainage_machine2\":0},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}


//����ˮλ������
void Water_level_alarm2_ON(void)
{
	u3_printf("Water_level_alarm2_ON");
	printf("Water_level_alarm2_ON\r\n");
		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_level_alarm2\":1},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
void Water_level_alarm2_OFF(void)
{
	u3_printf("Water_level_alarm2_OFF");
	printf("Water_level_alarm2_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_level_alarm2\":0},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}

//���ؽ��꾯��ָʾ��
void Rainfall_alarm2_ON(void)
{
	u3_printf("Rainfall_alarm2_ON");
	printf("Rainfall_alarm2_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Rainfall_alarm2\":1},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
void Rainfall_alarm2_OFF(void)
{
	u3_printf("Rainfall_alarm2_OFF");
	printf("Rainfall_alarm2_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Rainfall_alarm2\":0},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}

//����ˮ�ʱ�����
void Water_quality_alarm2_ON(void)
{
	u3_printf("Water_quality_alarm2_ON");
	printf("Water_quality_alarm2_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_quality_alarm2\":1},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
void Water_quality_alarm2_OFF(void)
{
	u3_printf("Water_quality_alarm2_OFF");
	printf("Water_quality_alarm2_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_quality_alarm2\":0},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
////////////////////3////////////////////////
//������ˮ��
void Drainage_machine3_ON(void)
{
	u3_printf("Drainage_machine3_ON");
	printf("Drainage_machine3_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Drainage_machine3\":1},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
void Drainage_machine3_OFF(void)
{
	u3_printf("Drainage_machine3_OFF");
	printf("Drainage_machine3_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Drainage_machine3\":0},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}

//����ˮλ������
void Water_level_alarm3_ON(void)
{
	u3_printf("Water_level_alarm3_ON");
	printf("Water_level_alarm3_ON\r\n");
		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_level_alarm3\":1},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
void Water_level_alarm3_OFF(void)
{
	u3_printf("Water_level_alarm3_OFF");
	printf("Water_level_alarm3_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_level_alarm3\":0},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}

//���ؽ��꾯��ָʾ��
void Rainfall_alarm3_ON(void)
{
	u3_printf("Rainfall_alarm3_ON");
	printf("Rainfall_alarm3_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Rainfall_alarm3\":1},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
void Rainfall_alarm3_OFF(void)
{
	u3_printf("Rainfall_alarm3_OFF");
	printf("Rainfall_alarm3_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Rainfall_alarm3\":0},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}

//����ˮ�ʱ�����
void Water_quality_alarm3_ON(void)
{
	u3_printf("Water_quality_alarm3_ON");
	printf("Water_quality_alarm3_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_quality_alarm3\":1},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}
void Water_quality_alarm3_OFF(void)
{
	u3_printf("Water_quality_alarm3_OFF");
	printf("Water_quality_alarm3_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_quality_alarm3\":0},\"version\":\"1.0.0\"}");  //�����ظ�ʪ���¶�����
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //������ݣ�������������
}



