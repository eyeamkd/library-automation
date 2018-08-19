#include <Servo.h>

//All Credit Technic 1510
//
//
//
//
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#define SS_PIN 10
#define RST_PIN 9 
#define led_g 5 
#define led_r 4  
#define buzz 8
MFRC522 mfrc522(SS_PIN, RST_PIN);   
LiquidCrystal lcd(6 , 7, 5, 4, 3, 2);
Servo myservo;
 
void setup() 
{
  
  SPI.begin();  
  Serial.begin(9600);    
  mfrc522.PCD_Init();   
  lcd.begin(16, 2);
  lcd.print("Scan ID Card"); 
  myservo.attach(A0);
  myservo.write(0); 
  pinMode(led_g,OUTPUT);
  pinMode(led_r,OUTPUT);  
  pinMode(buzz,OUTPUT);
  noTone(buzz);  
  digitalWrite(buzz,LOW);
  Serial.println("Put your card into the reader.."); 
  Serial.println(); 
  
  

}
void loop() 
{

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    lcd.setCursor(0, 1);
     lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     lcd.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
lcd.clear();
lcd.begin(16, 2);
 lcd.print("Message : ");
 content.toUpperCase();
  if (content.substring(1) == "27 C6 68 89"||content.substring(1) == "B0 09 51 D3") //Plz change to your cards UID
  { 
     noTone(buzz); 
   lcd.setCursor(0,1);
    lcd.print("Welcome Kunal"); 
    digitalWrite(led_g,HIGH);  
     
    myservo.write(180); 
    delay(1000);  
    myservo.write(0);  
    digitalWrite(led_g,LOW); 
   lcd.clear();
    setup();
  }
 
 else   {  
   noTone(buzz); 
  digitalWrite(buzz,HIGH);
  lcd.setCursor(0, 1);
    lcd.print(" Access denied"); 
    digitalWrite(led_r,HIGH); 
   tone(buzz,5);
    delay(1000);   
    noTone(buzz);
    digitalWrite(led_r,LOW);
    delay(1000);
    lcd.clear();
      setup();
      }
} 
