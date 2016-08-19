//program kirim SMS
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
}

void loop() {
  lcd.clear();
  lcd.print("Tes Kirim SMS ..");  
  //-- silahkan baris dibawah ini diganti nomor HP
  //  yang akan dikirimi SMS
//  gsm.println("AT+CMGS=08126752xxxx"); //no HP yang akan di SMS  
  gsm.println("AT+CMGS=085794817745"); //no HP yang akan di SMS
  delay(1000); 
  gsm.print("Terima kasih ... SMSduino"); 
  gsm.write((byte)26); 
  gsm.println();     
  delay(2000);
  lcd.clear();
  lcd.print("SMS Terkirim..");
  while(1);   
}



