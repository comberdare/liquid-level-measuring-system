#include <Arduino.h>
#include <ESP8266WiFi.h>    
#include <ESP8266WebServer.h>

 
const char *ssid = "液位测量系统"; 
const char *password = "12345679"; 

unsigned int EchoPin = 5;
unsigned int TrigPin = 4;
unsigned long Time_Echo_us = 0;
unsigned long Len_mm = 0; 
int i = 0;

ESP8266WebServer esp8266_server(80);
 
void setup() {
  Serial.begin(9600);             
  WiFi.softAP(ssid, password);    
                                   
  Serial.println("");
  Serial.print("Access Point: "); 
  Serial.println(ssid);             
  Serial.print("IP address: ");    
  Serial.println(WiFi.softAPIP());  
  Serial.print("Password: ");      
  Serial.println(password);        

  pinMode(EchoPin, INPUT);
  pinMode(TrigPin, OUTPUT);   

  void handleGET() ;
  void handleNotFound();
  esp8266_server.begin();                         
  esp8266_server.on("/", HTTP_GET, handleGET);  
  esp8266_server.onNotFound(handleNotFound);       

  Serial.println("HTTP esp8266_server started");
  Serial.println("��ӭʹ�ó�����Һλ����ϵͳ");
}
 
void loop() { 
  esp8266_server.handleClient();    
  delayMicroseconds(10);
}

void handleGET(){
  i = i+1;
  Serial.println(" ");
  Serial.print("��ʼ�� ");
  Serial.print(i);
  Serial.println(" �β�������");
  digitalWrite(TrigPin, HIGH);   
  delayMicroseconds(50);
  digitalWrite(TrigPin, LOW);   
  Time_Echo_us = pulseIn(EchoPin, HIGH);     
  Len_mm = Time_Echo_us;
  String LEN = String(Len_mm);
  esp8266_server.send(200, "text/plain", LEN);
  delay(9);


  Serial.print("Time_Echo_us = ");
  Serial.println(Time_Echo_us);
  Serial.print("Len_mm = ");
  Serial.println(Len_mm);  
  Serial.print("LEN = ");
  Serial.println(LEN);    
  Serial.print("�� ");
  Serial.print(i);
  Serial.println(" �β�������");
} 


void handleNotFound(){
  esp8266_server.send(404, "text/plain", "404: Not found"); 
}