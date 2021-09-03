#include"SystemTime.h"
#include"IO.h"

long long TimeAtBoot = 0;
int readPit(void) {
  unsigned count = 0;
  cli();
  outportb(0x43,0b0000000);
  count = inportb(0x40);		
  count |= inportb(0x40)<<8;		
  return count;
}
void setPit(unsigned count) {
 cli();
 outportb(0x40,count&0xFF);		// Low byte
 outportb(0x40,(count&0xFF00)>>8);	// High byte
 return;
}

int getSeconds(){
    int cmos_address = 0x70;
    int cmos_data    = 0x71;
    outportb(cmos_address, 0x0);
    int second = inportb(cmos_data);
    second = (second & 0x0F) + ((second / 16) * 10);
    return second;
}
int getMinutes(){
    int cmos_address = 0x70;
    int cmos_data    = 0x71;
    outportb(cmos_address, 0x02);
    int minute = inportb(cmos_data);
    minute = (minute & 0x0F) + ((minute / 16) * 10);
    return minute;
}
int getHours(){
    int cmos_address = 0x70;
    int cmos_data    = 0x71;
    outportb(cmos_address, 0x04);
    int  hour = inportb(cmos_data);
    hour = (hour & 0x0F) + ((hour / 16) * 10);
    return hour;
}
void time_init(){
 TimeAtBoot = (getSeconds()+(getMinutes()*60)+(getHours()*3600));
}
long long currentTime(){
     return (getSeconds()+(getMinutes()*60)+(getHours()*3600));
} 
long long getTimeFromBoot(){
    return (getSeconds()+(getMinutes()*60)+(getHours()*3600))-TimeAtBoot;
}