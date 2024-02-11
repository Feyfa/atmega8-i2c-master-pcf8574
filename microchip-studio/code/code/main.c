#include <avr/io.h>
#include <util/delay.h>
#include "i2cMaster/i2cMaster.h"

int main(void)
{
	DDRD = 0xFF;
	
	// init i2c as master
	i2c_master_init();
	
	while(1)
	{
		// check whether the slave with address 64 is ready
		if(i2c_master_isDeviceReady(64))
		{
			// write data to the slave with address 64, 64 as write
			// ~(1 << 4)
			// ~(00010000)
			// 11101111
			// I use pull up mode
			i2c_master_transmit(64, ~(1 << 4));
			// read data from slave with address 65, 65 as read
			// example 
			// PORTD = i2c_master_receive(65) | 0xF0;
			// PORTD = 10101110 | 11110000
			// PORTD = 11111110
			// the goal in OR with 0xF0 is, we want to change the starting bits (4 - 7) to 1, and the bits (0 - 3) remain their value
			PORTD = i2c_master_receive(65) | 0xF0;
			_delay_ms(300);
			
			i2c_master_transmit(64, ~(1 << 5));
			PORTD = i2c_master_receive(65) | 0xF0;
			_delay_ms(300);
			
			i2c_master_transmit(64, ~(1 << 6));
			PORTD = i2c_master_receive(65) | 0xF0;
			_delay_ms(300);
			
			i2c_master_transmit(64, ~(1 << 7));
			PORTD = i2c_master_receive(65) | 0xF0;
			_delay_ms(300);
		}
	}
}

