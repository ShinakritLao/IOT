#include <TridentTD_LineNotify.h> 
#include <ESP8266WiFi.h>
#define LINE_TOKEN "LaBjxp711IdDzVDnrA96gjCCPLmK6A4RUukJYTYHRau" 
char ssid[] = "KIB_2.4G";
char pass[] = "nongshin";

int RelayOnPump = D4;
int SoilSensor  = A0;
int sensorValue = 0;
void setup() {
  Serial.begin(115200); 
  Serial.println();   
  Serial.println(LINE.getVersion());   
  WiFi.begin(ssid, pass);   
  Serial.printf("WiFi connecting to %s\n",  ssid);   
  while (WiFi.status() != WL_CONNECTED) {     
  Serial.print(".");    
  delay(200);      
  }   
  Serial.printf("\nWiFi connected\nIP : ");   
  Serial.println(WiFi.localIP());   
  LINE.setToken(LINE_TOKEN);   
  pinMode(RelayOnPump, OUTPUT);
  pinMode(SoilSensor, INPUT);
}

void loop() {
  sensorValue = analogRead(A0); 
  if (sensorValue >=600 && sensorValue <=800) {
    LINE.notify("รถน้ำแล้วจ้า");
    digitalWrite(RelayOnPump, LOW);
  }else {
    digitalWrite(RelayOnPump, HIGH);
  }
}
