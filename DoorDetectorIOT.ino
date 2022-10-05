#include <TridentTD_LineNotify.h> 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define LINE_TOKEN "LaBjxp711IdDzVDnrA96gjCCPLmK6A4RUukJYTYHRau" 
BlynkTimer timer;
char auth[] = "Gq4fpb3XpukZBeRze2as_mJI1xL-Yv1A";
char ssid[] = "KIB_2.4G";
char pass[] = "nongshin";
int relay = D2;
int flag=0;

void notifyOnButtonPress()
{
  int isButtonPressed = digitalRead(D1);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("Someone Opened the door");
    Blynk.notify("Alert : Someone Opened the door");
    LINE.notify("Someone Opened the door");
    digitalWrite(relay, HIGH);
    delay(3000);   
    digitalWrite(relay, LOW);
    delay(1000);  
    flag=1;
  }
  else if (isButtonPressed==0)
  {
    digitalWrite(relay, HIGH);
    delay(1000); 
    flag=0;
  }
}
