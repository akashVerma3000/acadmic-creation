#include<reg51.h>
#define motor P0
#define display_port P2      //Data pins connected to port 2 on microcontroller
sbit rs = P3^2;  //RS pin connected to pin 2 of port 3
sbit rw = P3^3;  // RW pin connected to pin 3 of port 3
sbit e =  P3^4;  //E pin connected to pin 4 of port 3

sbit h =  P1^0;
sbit p =  P1^1;
sbit b =  P1^2;

void msdelay(unsigned int time)  // Function for creating delay in milliseconds.
{
    unsigned i,j ;
    for(i=0;i<time;i++)    
    for(j=0;j<120;j++);
}
void lcd_cmd(unsigned char command)  //Function to send command instruction to LCD
{
    display_port = command;
    rs= 0;
    rw=0;
    e=1;
    msdelay(1);
    e=0;
}

void lcd_data(unsigned char disp_data)  //Function to send display data to LCD
{
    display_port = disp_data;
    rs= 1;
    rw=0;
    e=1;
    msdelay(1);
    e=0;
}

 void lcd_init()    //Function to prepare the LCD  and get it ready
{
    lcd_cmd(0x38);  // for using 2 lines and 5X7 matrix of LCD
    msdelay(10);
	  lcd_cmd(0xC0);  // for using 2 lines and 5X7 matrix of LCD
    msdelay(10);
    lcd_cmd(0x0F);  // turn display ON, cursor blinking
    msdelay(10);
    lcd_cmd(0x01);  //clear screen
    msdelay(10);
    lcd_cmd(0x00);  // bring cursor to position 1 of line 1
    msdelay(10);
}

void printstr(char s[])		//printing the string on lcd
{
	int l=0;
    lcd_init();
    while(s[l] != '\0') // searching the null terminator in the sentence
    {
        lcd_data(s[l]);
        l++;
			  if(l==15)
					lcd_cmd(0xC0);
    }
		msdelay(500);
		lcd_cmd(0x01);
		msdelay(200);		
}

void main()
{
	unsigned int i;
	p=1,h=1,b=0;
	while(1)
	{
	if(p==0)
	{
		unsigned char a[32]="PUT YOUR HAND HERE TO GET WATER";    //string of 32 characters with a null terminator.
		printstr(a);
	}	
if(h==0&&p==0)
		{
			msdelay(20);
			if(h==0)
			{
				motor=0x05;
				msdelay(2000);
				motor=0x00;
				for(i=0;i<50;i++)
				{
					if(p==1)
					{
						motor=0x06;
						msdelay(2000);
						motor=0x00;
						break;
					}
					if(i>45)
					{
					  b=1;
						msdelay(600);
						b=0;
					}
						msdelay(200);
				}
				if(i==50)
				{
					motor=0x06;
					msdelay(2000);
					motor=0x00;
				}
			}		
		}	
}
}