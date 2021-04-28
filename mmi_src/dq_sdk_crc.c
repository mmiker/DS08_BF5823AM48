
#include "dq_sdk_crc.h"

unsigned short CRC16_CCITT_FALSE(unsigned char *puchMsg, unsigned int usDataLen) {
    unsigned short wCRCin = 0xFFFF;
    unsigned short wCPoly = 0x1021;
    unsigned char wChar = 0;
	int i = 0;
    while (usDataLen--) {
        wChar = *(puchMsg++);
        wCRCin = wCRCin ^ (wChar << 8);
        for(i = 0;i < 8;i++) {
            if(wCRCin & 0x8000)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }
    return (wCRCin) ;
}
