#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
 
#define BT1 D1
#define BT2 D2
#define BT3 D3
#define BT4 D4
 
char auth[] = "BaZNCX--57kSqx6F8_Q0lD0AWS-zgAwP";
char ssid[] = "KIB_2.4G";
char pass[] = "nongshin";

WidgetLED BT1Blynk(V10);
WidgetLED BT2Blynk(V11);
WidgetLED BT3Blynk(V12);
WidgetLED BT4Blynk(V13);
void setup()
{
  Serial.begin(9600);
  pinMode(BT1,OUTPUT); 
  pinMode(BT2,OUTPUT); 
  pinMode(BT3,OUTPUT); 
  pinMode(BT4,OUTPUT); 
  Blynk.begin(auth, "KIB_2.4G", "nongshin");
}
BLYNK_CONNECTED() { 
  Blynk.syncVirtual(V1); 
  Blynk.syncVirtual(V2); 
  Blynk.syncVirtual(V3); 
  Blynk.syncVirtual(V4); 

}
void loop()
{
  Blynk.run();
}
BLYNK_WRITE(V1){ 
  Serial.println(param.asInt()); 
    if (param.asInt()){ 
        digitalWrite(BT1, HIGH); 
        BT1Blynk.on();
    } else {
        digitalWrite(BT1, LOW); 
         BT1Blynk.off();
    }
}
BLYNK_WRITE(V2){ 
  Serial.println(param.asInt()); 
    if (param.asInt()){ 
        digitalWrite(BT2, HIGH); 
        BT2Blynk.on();
    } else {
        digitalWrite(BT2, LOW); 
         BT2Blynk.off();
    }
}
BLYNK_WRITE(V3){ 
  Serial.println(param.asInt()); 
    if (param.asInt()){ 
        digitalWrite(BT3, HIGH); 
        BT3Blynk.on();
    } else {
        digitalWrite(BT3, LOW); 
         BT3Blynk.off();
    }
}
BLYNK_WRITE(V4){ 
  Serial.println(param.asInt());
    if (param.asInt()){ 
        digitalWrite(BT4, HIGH); 
        BT4Blynk.on();
    } else {
        digitalWrite(BT4, LOW); 
         BT4Blynk.off();
    }
}
