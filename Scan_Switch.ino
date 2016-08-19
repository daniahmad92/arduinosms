//program scan switch
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
LiquidCrystal lcd(2,3, 4, 5, 6, 7);
const int rxpin = 8; 
const int txpin = 9; 
SoftwareSerial gsm(rxpin, txpin); 

String inString="";
char str,f,scan;

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
  pinMode(A2,LOW);  
  pinMode(A3,LOW);
  pinMode(A4,LOW);
  pinMode(A5,LOW);
  digitalWrite(A2,HIGH); 
  digitalWrite(A3,HIGH);
  digitalWrite(A4,HIGH);
  digitalWrite(A5,HIGH);
  delay(2000);
}

void loop() {
  lcd.clear();
  lcd.print("Scan Switch");
  scan=1;  
  while(scan){
      if(digitalRead(A2)==0){ 
          lcd.setCursor(0,1);
          lcd.print("Switch 1 Aktif");        
          //gantilah nomor HP dibaris bawah ini sesuai
          //dg nomor HP yg akan di SMS       
          gsm.println("AT+CMGS=085794817745");  
          delay(1000); 
          gsm.print("Switch 1 aktif !"); 
          gsm.write((byte)26); 
          gsm.println();     
          scan=0;
      }
      else if(digitalRead(A3)==0){ 
          lcd.setCursor(0,1);
          lcd.print("Switch 2 Aktif");        
          //gantilah nomor HP dibaris bawah ini sesuai
          //dg nomor HP yg akan di SMS       
          gsm.println("AT+CMGS=085794817745");  
          delay(1000); 
          gsm.print("Switch 2 aktif !"); 
          gsm.write((byte)26); 
          gsm.println();     
          scan=0;
      }
      else if(digitalRead(A4)==0){ 
          lcd.setCursor(0,1);
          lcd.print("Switch 3 Aktif");        
          //gantilah nomor HP dibaris bawah ini sesuai
          //dg nomor HP yg akan di SMS       
          gsm.println("AT+CMGS=085794817745");  
          delay(1000); 
          gsm.print("Switch 3 aktif !"); 
          gsm.write((byte)26); 
          gsm.println();     
          scan=0;
      }
      else if(digitalRead(A5)==0){ 
          lcd.setCursor(0,1);
          lcd.print("Switch 4 Aktif");        
          //gantilah nomor HP dibaris bawah ini sesuai
          //dg nomor HP yg akan di SMS       
          gsm.println("AT+CMGS=085794817745");  
          delay(1000); 
          gsm.print("Switch 4 aktif !"); 
          gsm.write((byte)26); 
          gsm.println();     
          scan=0;
      }
  }
  delay(2000);
  lcd.clear();
  lcd.print("SMS Terkirim..");
  delay(2000);
  lcd.clear();
     
}



