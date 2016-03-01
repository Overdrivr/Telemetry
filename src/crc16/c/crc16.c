#include "crc16.h"

uint16_t crc16(uint8_t* data, uint32_t len)
{
	uint16_t rem  = 0;
	uint16_t i=0;
	for(i = 0 ; i < len ; i++)
	{
		rem = crc16_recursive(data[i],rem);
	}
  return rem;
 }

uint16_t crc16_recursive(uint8_t byte, uint16_t remainder)
{
	uint16_t n = 16;

	remainder  = remainder ^ (byte << (n-8));
	uint16_t j = 0;
	for(j = 1 ; j < 8 ; j++)
	{
		if(remainder & 0x8000)
		{
			remainder  = (remainder << 1) ^ 0x1021;
		}
		else
		{
			remainder  = remainder << 1;
		}
	 	remainder &= 0xffff;
	}

	return remainder;
}
