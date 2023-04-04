#include "widget.h"
#include "usart3.h"
#include "mqtt.h"
#include "string.h"       //包含需要的头文件
AJ_widget_t AJ_widget_SW;	//调节控件开关
AJ_widget_t Last_AJ_widget_SW;	//调节控件开关

/****************************初始化**********************************************/
void AJ_widgets_Init(void)
{

	//从zigbee拿数据。不需要初始化
	Clear_AJ_widget_SW();		/*开关标志位清零*/
}

/*开关标志位清零*/
void Clear_AJ_widget_SW(void)
{
	AJ_widget_SW.Drainage_machine1=0;//排水机
	AJ_widget_SW.Water_level_alarm1=0;//水位警报
	AJ_widget_SW.Rainfall_alarm1=0;//降雨警报
	AJ_widget_SW.Water_quality_alarm1=0;//水质警报
	
	AJ_widget_SW.Drainage_machine2=0;//排水机
	AJ_widget_SW.Water_level_alarm2=0;//水位警报
	AJ_widget_SW.Rainfall_alarm2=0;//降雨警报
	AJ_widget_SW.Water_quality_alarm2=0;//水质警报
	
	AJ_widget_SW.Drainage_machine3=0;//排水机
	AJ_widget_SW.Water_level_alarm3=0;//水位警报
	AJ_widget_SW.Rainfall_alarm3=0;//降雨警报
	AJ_widget_SW.Water_quality_alarm3=0;//水质警报
}

/*********************************控件实现***************************************/
char temp[256];
/////////////1///////////////////
//开关排水机
void Drainage_machine1_ON(void)
{
	u3_printf("Drainage_machine1_ON");
	printf("Drainage_machine1_ON\r\n");
		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Drainage_machine1\":1},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
void Drainage_machine1_OFF(void)
{
	u3_printf("Drainage_machine1_OFF");
	printf("Drainage_machine1_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Drainage_machine1\":0},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
//开关水位警报器
void Water_level_alarm1_ON(void)
{
	u3_printf("Water_level_alarm1_ON");
	printf("Water_level_alarm1_ON\r\n");
		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_level_alarm1\":1},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
void Water_level_alarm1_OFF(void)
{
	u3_printf("Water_level_alarm1_OFF");
	printf("Water_level_alarm1_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_level_alarm1\":0},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}

//开关降雨警报指示灯
void Rainfall_alarm1_ON(void)
{
	u3_printf("Rainfall_alarm1_ON");
	printf("Rainfall_alarm1_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Rainfall_alarm1\":1},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
void Rainfall_alarm1_OFF(void)
{
	u3_printf("Rainfall_alarm1_OFF");
	printf("Rainfall_alarm1_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Rainfall_alarm1\":0},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}

//开关水质报警灯
void Water_quality_alarm1_ON(void)
{
	u3_printf("Water_quality_alarm1_ON");
	printf("Water_quality_alarm1_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_quality_alarm1\":1},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
void Water_quality_alarm1_OFF(void)
{
	u3_printf("Water_quality_alarm1_OFF");
	printf("Water_quality_alarm1_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_quality_alarm1\":0},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}

///////////////////2///////////////////
//开关排水机
void Drainage_machine2_ON(void)
{
	u3_printf("Drainage_machine2_ON");
	printf("Drainage_machine2_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Drainage_machine2\":1},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
void Drainage_machine2_OFF(void)
{
	u3_printf("Drainage_machine2_OFF");
	printf("Drainage_machine2_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Drainage_machine2\":0},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}


//开关水位警报器
void Water_level_alarm2_ON(void)
{
	u3_printf("Water_level_alarm2_ON");
	printf("Water_level_alarm2_ON\r\n");
		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_level_alarm2\":1},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
void Water_level_alarm2_OFF(void)
{
	u3_printf("Water_level_alarm2_OFF");
	printf("Water_level_alarm2_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_level_alarm2\":0},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}

//开关降雨警报指示灯
void Rainfall_alarm2_ON(void)
{
	u3_printf("Rainfall_alarm2_ON");
	printf("Rainfall_alarm2_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Rainfall_alarm2\":1},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
void Rainfall_alarm2_OFF(void)
{
	u3_printf("Rainfall_alarm2_OFF");
	printf("Rainfall_alarm2_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Rainfall_alarm2\":0},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}

//开关水质报警灯
void Water_quality_alarm2_ON(void)
{
	u3_printf("Water_quality_alarm2_ON");
	printf("Water_quality_alarm2_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_quality_alarm2\":1},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
void Water_quality_alarm2_OFF(void)
{
	u3_printf("Water_quality_alarm2_OFF");
	printf("Water_quality_alarm2_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_quality_alarm2\":0},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
////////////////////3////////////////////////
//开关排水机
void Drainage_machine3_ON(void)
{
	u3_printf("Drainage_machine3_ON");
	printf("Drainage_machine3_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Drainage_machine3\":1},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
void Drainage_machine3_OFF(void)
{
	u3_printf("Drainage_machine3_OFF");
	printf("Drainage_machine3_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Drainage_machine3\":0},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}

//开关水位警报器
void Water_level_alarm3_ON(void)
{
	u3_printf("Water_level_alarm3_ON");
	printf("Water_level_alarm3_ON\r\n");
		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_level_alarm3\":1},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
void Water_level_alarm3_OFF(void)
{
	u3_printf("Water_level_alarm3_OFF");
	printf("Water_level_alarm3_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_level_alarm3\":0},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}

//开关降雨警报指示灯
void Rainfall_alarm3_ON(void)
{
	u3_printf("Rainfall_alarm3_ON");
	printf("Rainfall_alarm3_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Rainfall_alarm3\":1},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
void Rainfall_alarm3_OFF(void)
{
	u3_printf("Rainfall_alarm3_OFF");
	printf("Rainfall_alarm3_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Rainfall_alarm3\":0},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}

//开关水质报警灯
void Water_quality_alarm3_ON(void)
{
	u3_printf("Water_quality_alarm3_ON");
	printf("Water_quality_alarm3_ON\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_quality_alarm3\":1},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}
void Water_quality_alarm3_OFF(void)
{
	u3_printf("Water_quality_alarm3_OFF");
	printf("Water_quality_alarm3_OFF\r\n");
	sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"Water_quality_alarm3\":0},\"version\":\"1.0.0\"}");  //构建回复湿度温度数据
	MQTT_PublishQs0(P_TOPIC_NAME,temp,strlen(temp));   //添加数据，发布给服务器
}



