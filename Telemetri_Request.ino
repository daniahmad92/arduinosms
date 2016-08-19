//program telemetri by request  
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
String noPengirim="";
char str,f;
int adc0,temp,t;   
int i,j,k;

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



void setup()
{
  gsm.begin(9600); 
  lcd.begin(16, 2);
  lcd.print("Tes Koneksi ..");
  delay(1000);
  gsm.println("AT");
  getmodem();
  getmodem();  
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
  lcd.print("  Telemetri 2  ");
  lcd.setCursor(0, 1);
  lcd.print("   By Request  ");
  delay(2000);
  lcd.clear();
  lcd.print("  Telemetri 2  ");
  lcd.setCursor(0, 1);
  lcd.print("Tunggu Perintah");         
}
void loop()
{
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
         i=inString.indexOf(',');
         i=i+2;
         j=inString.indexOf(',',i);
         j=j-1;           
         noPengirim=inString.substring(i,j); 
         lcd.clear();
         lcd.print("SMS:");         
         lcd.print(inString2);   
         if(inString2=="get temp"){
           adc0 = analogRead(0);   
           temp=(adc0*5)/10;
           gsm.print("AT+CMGS=");   
           gsm.println(noPengirim);
           delay(1000); 
           gsm.print("Temperatur="); 
           gsm.print(temp);
           gsm.print(" Celcius");
           gsm.write((byte)26); 
           gsm.println(); 
           delay(1000);    
           gsm.print("AT+CMGD=");
           gsm.println(inbox); 
          delay(5000);
         }
       }
    }
}

