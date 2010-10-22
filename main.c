#define F_CPU 20000000
#define BYTE_LENGTH 833

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>


void long_delay(uint16_t ms);
void zero();
void one();
void init();
void output(uint8_t* data);
void start();
void createData(uint8_t value,uint8_t* data);

int main(void)
{
	init();
	//uint8_t data[8]={0,0,0,0,0,0,0,0};
	uint8_t data[8]={1,1,1,1,1,1,1,1};
	
	while(1)
	{
		//createData(254,data);
		output(data);
		long_delay(20);
	}	
	return 0;
}

void write_int(uint8_t value,uint8_t *data)
{
	createData(value,&data);
                output(&data);
                long_delay(50);
                _delay_ms(10);
}

void long_delay(uint16_t i)
{
	uint16_t c=0;
	for(;c<i;c++)
	{
		_delay_ms(35);
	}
}

void output(uint8_t *data)
{
	start();
	uint8_t i=0;
	for(;i<=7;i++)
	{
		if(*data==0)zero();
		else one();
		data++;
	}
	stop(); //test inv bits
}

void init()
{
	DDRD = 0xff;
}
void start()
{
        PORTD &= ~(1 << PD5);
        delay(1);
}

void stop()
{
        PORTD |= (1 << PD5);
        delay(4);
        
}


void one()
{
        PORTD &= ~(1 << PD5);
        delay(1);
        PORTD |= (1 << PD5);
        delay(1);
}

void zero()
{
        PORTD |= (1 << PD5);
        delay(1);
        PORTD &= ~(1 << PD5);
        delay(1);

}

void createData(uint8_t value,uint8_t *data) //converts int to bit-wise data
{
	//if(value <=127)
	//value+=value;
	uint8_t tmp[8]={1,1,1,1,1,1,1,1};
	uint8_t i = 0;

	while(value > 1)
	{
		tmp[i] = value % 2;
		value = value / 2;
		i++;	
	}

	i=8;	
	do	
	{
		i--;
		*data=tmp[i];
		*data++;
	} while(i>0);
}

void delay(uint8_t count)
{
	count=count*83;
	for(;count>0;count--) _delay_us(10);
}
