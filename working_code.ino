#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN A4
#define RST_PIN A5
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

// intialize sensor pins, lcd pins and other time & velocity variables
const int ProxSensor=2;
const int ProxSensor2=4;
float t1=0.0,t2=0.0;
float r = 0.0;
int ledPin=7;
int flag = 0;

LiquidCrystal lcd(0, 1, 8, 9, 10, 5);

void setup(){
    //Serial.begin(9600);   // Initiate a serial communication
    
    //intialize lcd and print constant text
    lcd.begin(16, 2);
    lcd.print("Speed(in cm/s):");

    pinMode(3, OUTPUT);          
    pinMode(7, OUTPUT);
    pinMode(ProxSensor,INPUT);
    pinMode(ProxSensor2,INPUT);

    // shift to next row of lcd display
    lcd.setCursor(0, 1);

    SPI.begin();      // Initiate  SPI bus
    mfrc522.PCD_Init();   // Initiate MFRC522
    //Serial.println("Approximate your card to the reader...");
    //Serial.println();

}

void loop() {

    if(digitalRead(ProxSensor)==HIGH){
      
      //digitalWrite(13, HIGH);
      t1 = (float)millis();

    }
    else{
      //digitalWrite(13, LOW);
    }
                
    if(digitalRead(ProxSensor2)==HIGH){

      //digitalWrite(3,HIGH);
      t2 = (float)millis();

    }
    else{
     // digitalWrite(3,LOW);
    }

    if(t1!=0){
      r = (float)(t2-t1);
    }
    
    if(r>0){
      
      r = 10000/r;
      lcd.print(r,2);
      delay(200);
      if(r>70.0){
        //flag=1;
        lcd.print(" Overspeed");
        digitalWrite(3,HIGH);
        delay(500);   
      }
      else{
        lcd.print(" Good to go");
        digitalWrite(7,HIGH);
        delay(500);
      }
      
      
      digitalWrite(7,LOW);
      digitalWrite(3,LOW);
      lcd.clear();

      lcd.begin(16, 2);
      lcd.print("UID Tag : ");
      lcd.setCursor(0, 1);

  
      // reset time & speed variables    
      t1=0.0;
      t2=0.0;
      r=0.0;

      if ( ! mfrc522.PICC_IsNewCardPresent()) 
      {
        return;
      }
      // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial()) 
      {
        return;
      }
      //Show UID on serial monitor
      //Serial.print("UID tag :");
      String content= "";
      byte letter;
      for (byte i = 0; i < mfrc522.uid.size; i++) 
      {
         lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
         lcd.print(mfrc522.uid.uidByte[i], HEX);
         content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
         content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      
      delay(2000);

      lcd.clear();

      lcd.begin(16, 2);
      lcd.print("Speed(in cm/s):");
      lcd.setCursor(0, 1);

      
    }
}
