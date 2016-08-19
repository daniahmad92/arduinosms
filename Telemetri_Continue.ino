//program telemetri continue  
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
LiquidCrystal lcd(2,3, 4, 5, 6, 7);
const int rxpin = 8; 
const int txpin = 9; 
SoftwareSerial gsm(rxpin, txpin); 
String inString="";
char str,f;
int adc0,temp,t; 

void getmodem()
{ 
 f=1; 
 while(f)
 {
   if(gsm.available())     
     {
       str=gsm.read(); 
       Serial.print(str);         
       switch (str)
         {
           case '\r': break;
           case '\n':f=0; break;
           default:inString+=(char)str;
         }        
     }
 }
} 

void setup()
{
  gsm.begin(9600); 
  lcd.begin(16, 2);
  lcd.print("  Telemetri 1  ");
  lcd.setCursor(0, 1);
  lcd.print("   Continue  ");
  delay(2000);
  lcd.clear();
  lcd.print("Temp=");         
}
void loop()
{
  for(t=0;t<300;t++);{
  adc0 = analogRead(0);   
  temp=(adc0*5)/10;
  lcd.setCursor(5,0);
  lcd.print(temp);    
  lcd.print(" Celcius");
  delay(1000);
  }  
 //gantilah nomor HP dibaris bawah ini sesuai
 //dg nomor HP yg akan di SMS       
 gsm.println("AT+CMGS=08126752xxxx");   
 delay(1000); 
 gsm.print("Temperatur="); 
 gsm.print(temp);
 gsm.print(" Celcius");
 gsm.write((byte)26); 
 gsm.println();     
  
}

