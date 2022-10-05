#include <TridentTD_LineNotify.h> 
#define SSID "KIB_2.4G" 
#define PASSWORD "nongshin" 
#define LINE_TOKEN "LaBjxp711IdDzVDnrA96gjCCPLmK6A4RUukJYTYHRau" 
 
int state = 1; int sensor_pin = D2; 
 
void setup() {   
  
  Serial.begin(115200); 
  Serial.println();   
  Serial.println(LINE.getVersion());   
  WiFi.begin(SSID, PASSWORD);   
  Serial.printf("WiFi connecting to %s\n",  SSID);   
  while (WiFi.status() != WL_CONNECTED) {     
    Serial.print(".");     delay(200);      
    }   Serial.printf("\nWiFi connected\nIP : ");   
    
    Serial.println(WiFi.localIP());   
    LINE.setToken(LINE_TOKEN);   
    pinMode(sensor_pin , INPUT); }

void loop() {   
  int sensor = digitalRead(sensor_pin);  
  if (sensor == 1 and state == 1) {     
    LINE.notify("You Have Recrived The Letter");    
    LINE.notifySticker(4,271);   
    state = 0;   
    }  else if (sensor == 0 and state == 0) {   
      Serial.println("No object");    
      state = 1;  
    }
}
