#include "delay.h"
#include "USART3.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 
//#include "usart1.h"
#include "stdlib.h"
 
//���ڽ��ջ����� 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.
u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
u8  USART3_RX_ABUF[USART3_MAX_RECV_LEN]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ� 
u8  USART3_RX_BBUF[USART3_MAX_RECV_LEN]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ� 
u8  USART3_RX_CBUF[USART3_MAX_RECV_LEN]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ� 

//ͨ���жϽ�������2���ַ�֮���ʱ������10ms�������ǲ���һ������������.
//���2���ַ����ռ������10ms,����Ϊ����1����������.Ҳ���ǳ���10msû�н��յ�
//�κ�����,���ʾ�˴ν������.
//���յ�������״̬
//[15]:0,û�н��յ�����;1,���յ���һ������.
//[14:0]:���յ������ݳ���
u8 sensor_souce=0;
vu16 USART3_RX_STA=0;   	
void USART3_IRQHandler(void)
{
	u8 Res;	      
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//���յ�����
	{	 
		Res =USART_ReceiveData(USART3);	 
		if((USART3_RX_STA&0x8000)==0)//�������һ������,��û�б�����,���ٽ�����������
		{ 
			
		    if((USART3_RX_STA&0X7FFF)<USART3_MAX_RECV_LEN)	//�����Խ�������
				{
					
					if(Res!='A'&&Res!='B'&&Res!='C')
					{
						USART3_RX_BUF[USART3_RX_STA++]=Res;	//��¼���յ���ֵ
					}	
          else 
					{
						if(Res=='A')  //���ݰ�������־��
							sensor_souce=1;
						if(Res=='B')
							sensor_souce=2;
						if(Res=='C')
							sensor_souce=3;
						USART3_RX_STA|=0x8000;	//����Ϣ��������� 				
					} 					
				}
				else 
				{
					USART3_RX_STA|=0x8000;	//����Ϣ��������� 										
				} 
		}
		
		USART3_RX_Data();
	}  				 											 
}   
 
 
//��ʼ��IO ����3
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void usart3_init(u32 bound)
{  
 
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //����3ʱ��ʹ��
 
 	USART_DeInit(USART3);  //��λ����3
		 //USART3_TX   PB10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PB10
   
    //USART3_RX	  PB11
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB11
	
	USART_InitStructure.USART_BaudRate = bound;//������һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(USART3, &USART_InitStructure); //��ʼ������	3
  
 
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 
	
	//ʹ�ܽ����ж�
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�   
	
	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	USART3_RX_STA=0;		//����
}
 
//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u3_printf(char* fmt,...) //...��ʾ�ɱ����������ɱ�������һ���б���������ר�ŵ�ָ��ָ�����������޶����������� 
{  
	u16 i,j; 
	va_list ap; //��ʼ��ָ��ɱ�����б���ָ��
	va_start(ap,fmt); //����һ���ɱ�����ĵ�ַ����ap����apָ��ɱ�����б��Ŀ�ʼ
	vsprintf((char*)USART3_TX_BUF,fmt,ap); //������fmt��apָ��Ŀɱ����һ��ת���ɸ�ʽ���ַ�������(char*)USART3_TX_BUF�����У�������ͬsprintf������ֻ�ǲ������Ͳ�ͬ
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART3,USART3_TX_BUF[j]);  //�Ѹ�ʽ���ַ����ӿ����崮���ͳ�ȥ 
	} 
}
 
void USART3_RX_Data()
{
	u8 len=0;
	u8 i=0;
	if(USART3_RX_STA&0x8000)
		{	
							   
			len=USART3_RX_STA&0X7FFF;//�õ��˴ν��յ������ݳ���
			USART3_RX_BUF[len]=0;	 	//���������
			
			if(len>USART3_MAX_RECV_LEN-2)
			{
				len=USART3_MAX_RECV_LEN-1;
				USART3_RX_BUF[len]=0;	 	//���������
			}
			
			USART3_RX_BUF[USART3_MAX_RECV_LEN-1]=0x01;
			for(i=0;i<USART3_MAX_RECV_LEN;i++)			
			{
				if(sensor_souce==1)  //������ڴ�����
				USART3_RX_ABUF[i]=USART3_RX_BUF[i];
				if(sensor_souce==2)  //�����жδ�����
				USART3_RX_BBUF[i]=USART3_RX_BUF[i];
				if(sensor_souce==3)  //���Գ��ڴ�����
				USART3_RX_CBUF[i]=USART3_RX_BUF[i];
			}
			printf("���յ�������Ϊ��%s\r\n",USART3_RX_BUF);
			USART3_RX_STA=0;
		}
 
}