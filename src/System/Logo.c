#include<Drivers/Screen.h>
int length(char * in);
void printLogo(){
char * logo[7];
logo[0] = "     OOOOOO       OO      OOOOO      OOOOOOO     OOOOO     OO     O\n";
logo[1] = "     O     O     O  O     O    O        O       O         O  O    O\n";
logo[2] = "     O     O    O    O    O     O       O      O         O    O   O\n";
logo[3] = "     OOOOOO     OOOOOO    O     O       O      O         OOOOOO   O\n";
logo[4] = "     O   O      O    O    O     O       O      O         O    O   O\n";
logo[5] = "     O    O     O    O    O    O        O       O        O    O   O\n";
logo[6] = "     O     O    O    O    OOOOO      OOOOOOO     OOOOO   O    O   OOOOOOO\n";
for(int i = 0;i<7;i++)
 for(int j = 0;j<length(logo[i]);j++){
   if(logo[i][j]=='O')
   logo[i][j]=219;
 }
for(int i = 0;i<7;i++)
print(logo[i],0x02);
}