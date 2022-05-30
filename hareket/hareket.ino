#include <LiquidCrystal.h>
#include <Keypad.h>
#include <String.h>
int LM35 =1;
const int flamepin =13;
const int buzzer = 12;
#define yled 29
#define kled 30
const byte satir = 4;
const byte sutun = 3;
char sifre[4]={'1','1','1','1'};
char sifre1[4];
char tus;
int i = 0;
char tus_takimi[satir][sutun]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
  };
  byte satir_pins[satir]={A2,A3,A7,A6};
  byte sutun_pins[sutun]={A5,A4,A8};
  Keypad keypad = Keypad(makeKeymap(tus_takimi),satir_pins,sutun_pins,satir,sutun);

LiquidCrystal lcd(7,6,5,4,3,2);
float sic;
int pir = 8;
boolean sensordegeri = 0;
int role = 9;
void setup() {
 //Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(yled,OUTPUT);
  pinMode(kled,OUTPUT); 
  pinMode(LM35,INPUT);
  analogReference(INTERNAL1V1);
  pinMode(pir,INPUT);
  pinMode(flamepin,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(role,OUTPUT);
  sic =0;
  digitalWrite(kled,LOW);
  digitalWrite(yled,LOW);
}
void loop() {
  tus = keypad.getKey();
 // Serial.print(tus);
  if(tus){
    
    sifre1[i]=tus;
    i++;
    delay(200);
    }
    if(i == 4){
      delay(100);
      int kontrol = 1;
      for(int j=0;j<4;j++){
        if(sifre[j] != sifre1[j]){
            kontrol = 0;
        }
      }
      if(kontrol == 1){
        digitalWrite(yled,HIGH);
       delay(1500);
       digitalWrite(yled,LOW);
      }
        else{
        digitalWrite(kled,HIGH);
        delay(1500);
        digitalWrite(kled,LOW);
          }
          i = 0;
        Serial.println("");
  
            delay(200);
    }
        
  sic = analogRead(LM35);
  sic=sic*1100/(1024*10);
 // Serial.println(sic);
  //delay(100);
  if(sic < 20.0){
    lcd.clear();
    lcd.print("Sicaklik dustu");
   
    }
  else if (sic > 30.0){
    lcd.clear();
    lcd.print("Sicaklik yukseldi");
    delay(20);
    }
    else{
    lcd.clear();
    lcd.print(sic);
    lcd.print("*C");
     
    }
 //delay(100);

 sensordegeri = digitalRead(pir);
 //delay(100);
 if(sensordegeri == 1){
  digitalWrite(role,HIGH);
  }
  else{
    digitalWrite(role,LOW);
    }
    int yangindegeri = digitalRead (flamepin);
if(yangindegeri == HIGH)
{
  digitalWrite(buzzer, HIGH);
  
  
}
else
{
 digitalWrite(buzzer, LOW); 
}
  
   
}
