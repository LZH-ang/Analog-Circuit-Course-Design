#define u8 unsigned char
#define u16 unsigned int
#include "intrins.h"

#define FOSC    11059200L
#define BAUD    115200

typedef unsigned char BYTE;
typedef unsigned int WORD;



sfr T2H   = 0xd6;               //定时器2高8位
sfr T2L   = 0xd7;               //定时器2低8位

sfr P1M1 = 0x91;    //PxM1.n,PxM0.n     =00--->Standard,    01--->push-pull
sfr P1M0 = 0x92;    //                  =10--->pure input,  11--->open drain
sfr P0M1 = 0x93;
sfr P0M0 = 0x94;
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sfr P3M1 = 0xB1;
sfr P3M0 = 0xB2;
sfr P4M1 = 0xB3;
sfr P4M0 = 0xB4;
sfr P5M1 = 0xC9;
sfr P5M0 = 0xCA;
sfr P6M1 = 0xCB;
sfr P6M0 = 0xCC;
sfr P7M1 = 0xE1;
sfr P7M0 = 0xE2;

sfr  AUXR       =   0x8e;       //辅助寄存器                              

sfr ADC_CONTR   =   0xBC;           //ADC控制寄存器
sfr ADC_RES     =   0xBD;           //ADC高8位结果
sfr ADC_LOW2    =   0xBE;           //ADC低2位结果
sfr P1ASF       =   0x9D;           //P1口第2功能控制寄存器

#define ADC_POWER   0x80            //ADC电源控制位
#define ADC_FLAG    0x10            //ADC完成标志
#define ADC_START   0x08            //ADC起始控制位
#define ADC_SPEEDLL 0x00            //540个时钟
#define ADC_SPEEDL  0x20            //360个时钟
#define ADC_SPEEDH  0x40            //180个时钟
#define ADC_SPEEDHH 0x60            //90个时钟

void InitADC();
BYTE GetADCResult(BYTE ch);
void Delay(WORD n);
unsigned int Voltage;
float adc;
unsigned char channel,ch;

/*----------------------------
读取ADC结果
----------------------------*/
unsigned char GetADCResult(unsigned char ch)
{
	unsigned int ad_result;
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //等待4个NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//等待ADC转换完成
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC
		ad_result = ADC_RES;
    return ad_result;                 //返回ADC结果
}


/*----------------------------
初始化ADC
----------------------------*/
void InitADC()
{
    P1ASF = 0xff;                   //设置P1口为AD口
		P1M1 = 1;
		P1M0 = 0;
    ADC_RES = 0;                    //清除结果寄存器
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay(2);                       //ADC上电并延时
}


/*----------------------------
软件延时
----------------------------*/
void Delay(WORD n)
{
    WORD x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}
