#ifndef PCF8563_H
#define PCF8563_H


void time_init();

void pcf_init();

//----------------BCDת10����-----------
uchar bcd_dec(uchar bat);

#endif