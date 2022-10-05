#include <ESP8266WiFi.h>
#include <WiFiClientSecureAxTLS.h>
void Line_Notify(String message) ;
#define WIFI_SSID "KIB_2.4G"
#define WIFI_PASSWORD "nongshin"
#define LINE_TOKEN "LaBjxp711IdDzVDnrA96gjCCPLmK6A4RUukJYTYHRau"
int LED_R = D1;
int LED_G = D5;
int relay = D6;
int Smoke = A0;
int sensorThres = 700;
void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(Smoke, INPUT);
  Serial.begin(9600);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  }
void loop() 
{
 int analogSensor = analogRead(Smoke);
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(relay,0);
    delay(5000);
    digitalWrite(relay,1);
    delay(2000);
    Line_Notify("A Fire Warning. Please Call Emergency");
    delay(3000);
  }
  else
  {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(relay,1);
  }
}
void Line_Notify(String message) {
  axTLS::WiFiClientSecure client;
  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");  
    return;
  }
  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  client.print(req); 
  delay(20);
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
}
