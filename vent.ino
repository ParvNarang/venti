#include <Metro.h> //Include Metro library
#include <LiquidCrystal.h>
LiquidCrystal lcd(19,18,17,16,15,14);

Metro ledMetro = Metro(1000);

const int low_key  = 2;
const int mid_key  = 3;
const int high_key = 4;
const int stop_key = 5;
const int motor_f  = 8;
const int motor_b  = 9;

boolean low_flag=0,mid_flag=0,high_flag=0;
int M=0,S=0,t_count=0;

void setup() 
{   lcd.begin(16,2);pinMode(low_key,INPUT_PULLUP);pinMode(mid_key,INPUT_PULLUP);
    pinMode(high_key,INPUT_PULLUP);pinMode(stop_key,INPUT_PULLUP);
    pinMode(motor_f,OUTPUT);pinMode(motor_b,OUTPUT);
    lcd.setCursor(0,0);lcd.print("   VENTILATOR   ");
    lcd.setCursor(0,1);lcd.print("                ");
    digitalWrite(motor_f,LOW);digitalWrite(motor_b,LOW);
}

void loop() 
{   if (ledMetro.check() == 1) 
    {   if(M > 0 || S > 0)
        {   if(S == 0)
            {   if(M >= 0){S=59;M--;}
                else
                {   low_flag=0;mid_flag=0;high_flag=0;M=0;S=0;t_count=5;
                    lcd.setCursor(0,0);lcd.print("   TIME OVER    ");
                    lcd.setCursor(0,1);lcd.print("                ");                                  
                }
            }
            else
            {   S--;                
            }
            lcd.setCursor(11,1);lcd.print(M);
            lcd.setCursor(13,1);
            if(S<10){lcd.print('0');}lcd.print(S); 
        }
        if(t_count>1){t_count--;}
        else if(t_count == 1)
        {   lcd.setCursor(0,0);lcd.print("   VENTILATOR   ");
            lcd.setCursor(0,1);lcd.print("                "); 
            t_count=0;
        }
    }
    if(digitalRead(low_key) == 0)
    {   lcd.setCursor(0,0);lcd.print("  LOW MODE ON   ");
        lcd.setCursor(0,1);lcd.print("TIME LEFT 05:00 ");   
        low_flag=1;mid_flag=0;high_flag=0;M=4;S=60;
        while(digitalRead(low_key) == 0)delay(100);
    }
    if(digitalRead(mid_key) == 0)
    {   lcd.setCursor(0,0);lcd.print("  MID MODE ON   ");
        lcd.setCursor(0,1);lcd.print("TIME LEFT 05:00 ");   
        low_flag=0;mid_flag=1;high_flag=0;M=4;S=60;
        while(digitalRead(mid_key) == 0)delay(100);
    }
    if(digitalRead(high_key) == 0)
    {   lcd.setCursor(0,0);lcd.print(" HIGH MODE ON   ");
        lcd.setCursor(0,1);lcd.print("TIME LEFT 05:00 ");
        low_flag=0;mid_flag=0;high_flag=1;M=4;S=60;
        while(digitalRead(high_key) == 0)delay(100);
    }
    if(digitalRead(stop_key) == 0)
    {   lcd.setCursor(0,0);lcd.print("   VENTILATOR   ");
        lcd.setCursor(0,1);lcd.print("                ");
        low_flag=0;mid_flag=0;high_flag=0;M=0;S=0;
        while(digitalRead(stop_key) == 0)delay(100);
    }
}

