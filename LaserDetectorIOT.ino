#define BLYNK_PRINT Serial
#define USING_AXTLS
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiClientSecureAxTLS.h>
using namespace axTLS;
char auth[] = "CPCwIrOeTPoLUaT9lTWgkKEWNQvyUdeN";
#define WIFI_SSID "KIB_2.4G"
#define WIFI_PASSWORD "nongshin"
#define LINE_TOKEN "LaBjxp711IdDzVDnrA96gjCCPLmK6A4RUukJYTYHRau"
#define SW D2
#define PiezoPin D7
#define Laser D1

String message = "! ! Thief ! !";
void Line_Notify(String message) ;
void setup() {
pinMode(SW, INPUT);
pinMode(PiezoPin, OUTPUT);
pinMode(Laser, OUTPUT);
Serial.begin(9600);
WiFi.mode(WIFI_STA);
  Blynk.begin(auth,WIFI_SSID,WIFI_PASSWORD); 
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());
digitalWrite(PiezoPin,1);
digitalWrite(Laser,0);
}
void loop() {
    Blynk.run(); 
if (digitalRead(SW) == LOW) {
while (digitalRead(SW) == LOW) delay(10);
Serial.println("Enter !");
Line_Notify(message);
loop:
digitalWrite(PiezoPin, 0);
delay(3000);
digitalWrite(PiezoPin, 1);
delay(1000);
goto loop;   
}
delay(10);
}
void Line_Notify(String message) {
WiFiClientSecure client;
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
req += "Content-Type: application/x-www-form-urlencoded\r\n";
req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
req += "\r\n";
req += "message=" + message;
client.print(req);
delay(20);
while (client.connected()) {
String line = client.readStringUntil('\n');
if (line == "\r") {
break;
return;
}
}
}
