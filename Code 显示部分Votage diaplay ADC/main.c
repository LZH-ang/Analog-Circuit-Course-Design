
#include<reg51.h>
#include<intrins.h>
unsigned int count,show,cp;
long sum;
#define Amp 319/100 //运放放大倍数
#include<display.c>
#include<adc.c>

void timer0_init(void)
{
	TMOD = 0x01;
	TH0 = (65536 - 2000) / 256;
	TL0 = (65536 - 2000) % 256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}
void timer0_isr(void) interrupt 1
{
	TH0 = (65536 - 2000) / 256;
	TL0 = (65536 - 2000) % 256;
	cp++;
	if(cp>=4)cp=0;
	display();	
}
void main()
{
		timer0_init();
		P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;		  //高阻输入模式的特点是只能作为输入使用，但是可以获得比较高的输入阻抗，											
    P2M0 = 0x00;			//这在模拟比较器和ADC应用中是必需的。
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    P6M0 = 0x00;
    P6M1 = 0x00;
    P7M0 = 0x00;
    P7M1 = 0x00;
    InitADC();                      //初始化ADC
    while (1)
    {
				Voltage = GetADCResult(0x00);
				Voltage <<= 2;
				Voltage |= ADC_LOW2;
				adc = Voltage;
				sum += (u16)(adc * 100 / 204.5);
				count++;
				if(count>=500)
				{
					show = (sum / 500)*Amp;
					sum = 0;
					count = 0;
				}
		}
}