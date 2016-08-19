//program tes koneksi
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
LiquidCrystal lcd(2,3, 4, 5, 6, 7);
const int rxpin = 8;  
const int txpin = 9;  
SoftwareSerial gsm(rxpin, txpin); 

String inString="";
char str,f;

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

void setup() { 
  gsm.begin(9600);   
  lcd.begin(16, 2);
  lcd.print("Tes Koneksi ...");
  delay(1000); 
}

void loop() {
  gsm.println("AT");
  getmodem(); 
  getmodem();  
  lcd.setCursor(0, 1);
  lcd.print(inString);
  delay(2000);
  while(1); 
}



