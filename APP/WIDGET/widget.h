#ifndef _WIDGET_h_
#define _WIDGET_h_

#include "sys.h"

//���ڿؼ���1:��  0:�أ�
typedef struct
{
	char Drainage_machine1;//��ˮ��
	char Water_level_alarm1;//ˮλ����
	char Rainfall_alarm1;//���꾯��
	char Water_quality_alarm1;//ˮ�ʾ���
	
	char Drainage_machine2;//��ˮ��
	char Water_level_alarm2;//ˮλ����
	char Rainfall_alarm2;//���꾯��
	char Water_quality_alarm2;//ˮ�ʾ���
	
	char Drainage_machine3;//��ˮ��
	char Water_level_alarm3;//ˮλ����
	char Rainfall_alarm3;//���꾯��
	char Water_quality_alarm3;//ˮ�ʾ���
	
}AJ_widget_t;

void Clear_AJ_widget_SW(void);

void AJ_widgets_Init(void);

void Drainage_machine1_ON(void);//������ˮ����ˮλ������
void Drainage_machine1_OFF(void);
void Rainfall_alarm1_ON(void);//���ؽ��꾯��ָʾ��
void Rainfall_alarm1_OFF(void);
void Water_quality_alarm1_ON(void);//����ˮ�ʱ�����
void Water_quality_alarm1_OFF(void);
void Water_level_alarm1_ON(void);//����ˮλ������
void Water_level_alarm1_OFF(void);
///////////////////2///////////////////
void Drainage_machine2_ON(void);//������ˮ����ˮλ������
void Drainage_machine2_OFF(void);
void Rainfall_alarm2_ON(void);//���ؽ��꾯��ָʾ��
void Rainfall_alarm2_OFF(void);
void Water_quality_alarm2_ON(void);//����ˮ�ʱ�����
void Water_quality_alarm2_OFF(void);
void Water_level_alarm2_ON(void);//����ˮλ������
void Water_level_alarm2_OFF(void);
///////////////////3///////////////
void Drainage_machine3_ON(void);//������ˮ����ˮλ������
void Drainage_machine3_OFF(void);
void Rainfall_alarm3_ON(void);//���ؽ��꾯��ָʾ��
void Rainfall_alarm3_OFF(void);
void Water_quality_alarm3_ON(void);//����ˮ�ʱ�����
void Water_quality_alarm3_OFF(void);
void Water_level_alarm3_ON(void);//����ˮλ������
void Water_level_alarm3_OFF(void);
#endif
