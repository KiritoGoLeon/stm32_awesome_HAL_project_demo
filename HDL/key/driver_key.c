#include "driver_key.h"

static KeyFifoTypedef keyFifo;

void driver_key_init(void)
{
	memset(&keyFifo,0,sizeof(keyFifo));
}

void driver_key_handle(void)
{
	
}
void driver_key_exit(void)
{
	
}

// °´¼üÉ¨Ãè
static void  key_scan(void)
{
	
}

uint8_t driver_get_key(void)
{
	uint8_t ret = 0;
	
	if(keyFifo.read_p == keyFifo.write_p){
		return ret;
	}else{
			ret = keyFifo.buff[keyFifo.read_p++];
			if(keyFifo.read_p > KEY_SIZE){
				keyFifo.read_p = 0;
			}
	}
}