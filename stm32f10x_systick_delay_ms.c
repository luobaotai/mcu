#include "stm32f10x.h"

u16 fac_us, fac_ms;

void delay_init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;	      //为系统时钟的1/8，实际上也就是在计算1usSysTick的VAL减的数目
	fac_ms=(u16)fac_us*1000;		//代表每个ms需要的systick时钟数，即每毫秒SysTick的VAL减的数目   
}

void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达，看CTRL的第16位（COUNTFLAG）是否为1，看STRL的第0位（ENABLE）是否为1   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
} 

int i=0;

int main(){
	
	while(1){
		i++;
		delay_init();
		delay_ms(1000);
	}
}
