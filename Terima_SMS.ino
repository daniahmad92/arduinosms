//program terima SMS
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
LiquidCrystal lcd(2,3, 4, 5, 6, 7);
const int rxpin = 8; 
const int txpin = 9;  
SoftwareSerial gsm(rxpin, txpin); 

String inString="";

String inString2="";
String Stemp="";
String inbox="";
char str,f;
int i,j;


void setup() { 
  Serial.begin(9600);  
  gsm.begin(9600);   
  lcd.begin(16, 2);
  lcd.print("Tes Koneksi ..");
  delay(1000);
  gsm.println("AT");
  getmodem();
  getmodem();
  lcd.setCursor(0, 1);
  lcd.print(inString);
  if(inString=="OK") {
    lcd.clear();
    lcd.print(" Koneksi OK ");
    }
   else{
    lcd.clear();
    lcd.print(" Gagal ... ");
    lcd.setCursor(0,1);
    lcd.print("Coba lagi !");
    while(1);
    }   
  delay(2000);
  lcd.clear();
  lcd.print("Tes Terima SMS ..");
  lcd.setCursor(0,1);
  lcd.print("Tunggu SMS");
}

void loop() {  
  getmodem();  
  getmodem2();     
  i=inString2.indexOf(':');   
  if(i>0)
    {
     Stemp=inString2.substring(0,i);    
     if(Stemp=="+CMTI")
       {         
         i=inString2.indexOf(',');
         j=inString2.length ();
         i=i+1;
         inbox=inString2.substring(i,j);        
         gsm.print("AT+CMGR=");
         gsm.println(inbox);        
         getmodem();
         getmodem();
         getmodem2(); 
         lcd.clear();
         lcd.print("   Isi SMS :   ");
         lcd.setCursor(0,1); 
         lcd.print(inString2);        
         gsm.print("AT+CMGD=");
         gsm.println(inbox); 
         delay(5000);
         lcd.clear();
         lcd.print("Tes Terima SMS ..");
         lcd.setCursor(0,1);
         lcd.print("Tunggu SMS");
       }
    } 
}
//=====================
void getmodem()
{ 
 f=1; 
 inString="";
 while(f)
 {
   if(gsm.available())     
     {
       str=gsm.read();               
       switch (str)
         {
           case '\r': break;
           case '\n':f=0; break;
           default:inString+=(char)str;
         }        
     }
 }
} 
//=========================
void getmodem2()
{
 f=1;
 inString2="";
 while(f)
 {
   if(gsm.available()>0)
     {
       str=gsm.read();            
       switch (str)
         {
           case '\r': break;
           case '\n':f=0; break;
           default:inString2+=(char)str;
         }
     }
 }
} 



