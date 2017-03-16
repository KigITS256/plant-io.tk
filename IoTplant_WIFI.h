

// #include <ESP8266WiFi.h>
#include "include/ArduinoJson.h"
// #include "include/ESP8266WiFi/ESP8266WiFi.h"

WiFiClient client;   
unsigned long previousMillis = 0; 
const long interval = 10000; 
#define SERVER_PORT 80   
const char* server_ip = "plant-io.tk";  

 int _req = 0;

class iot
{
public:
  void set_req(int pin);
  bool wifi();
  void getStatus(int gpio);
  void api_send(String api,String values="");
 
  
  
  
};

void set_req(int pin){
    pinMode(pin, OUTPUT);
    _req = pin;

}

//Connect WiFi router
bool wifi(const char* ssid,const char* passw)
{


  int _cnt=0,_retry=30;
  bool _conn = false;


  WiFi.begin(ssid,passw);
  while ((WiFi.status() != WL_CONNECTED) && (_cnt <= _retry))
  {
    delay(500);
    Serial.print(".");
    _cnt++;
  }

  if(WiFi.status() == WL_CONNECTED)
  {
    _conn = true;
    Serial.println("\nWiFi for IoTplant Connected !");
    Serial.println("IP address: ");         
    Serial.println(WiFi.localIP());  
  }else{
    _conn = false;
  }

  return _conn;
}


void api_repost_switch(int gpio){

   pinMode(gpio, OUTPUT);
    

   while(client.available())               //ตรวจเช็คว่ามีการส่งค่ากลับมาจาก Server หรือไม่        
    {
          String line = client.readStringUntil('\n');       //อ่านค่าที่ Server ตอบหลับมาทีละบรรทัด
                     //แสดงค่าที่ได้ทาง Serial Port
          line.trim();
          StaticJsonBuffer<200> jsonBuffer;

          JsonObject& root = jsonBuffer.parseObject(line);
          
          const char* b_status = root["status"];
      
          
      
          if(String(b_status)=="off"){
                Serial.printf("switch : off");
                digitalWrite(gpio, LOW);
          }else if(String(b_status)=="on"){
                Serial.printf("switch : on");
                digitalWrite(gpio, HIGH);
                    
          }
         
          
    }

}


void api_send(String api,String values=""){
   

    String str_get1  = "GET /app/api/status/?api="+api;      
    String str_get2  = " HTTP/1.1\r\n";
    String str_host = "Host: plant-io.tk\r\n\r\n";
    if(values!=""){
          str_get1  = "GET /app/api/in_status/?api="+api+"&humidity="+values;  
    }



  unsigned long currentMillis = millis();           //อ่านค่าเวลาที่ ESP เริ่มทำงานจนถึงเวลาปัจจุบัน
  if(currentMillis - previousMillis >= interval)     /*ถ้าหากเวลาปัจจุบันลบกับเวลาก่อหน้านี้ มีค่า
                            มากกว่าค่า interval ให้คำสั่งภายใน if ทำงาน*/ 
  {
        previousMillis = currentMillis;         /*ให้เวลาปัจจุบัน เท่ากับ เวลาก่อนหน้าเพื่อใช้
                            คำนวณเงื่อนไขในรอบถัดไป*/
         Serial.println("Connect TCP Server");
    int cnt=0;
    while (!client.connect(server_ip,SERVER_PORT))  //เชื่อมต่อกับ Server และรอจนกว่าเชื่อมต่อสำเร็จ
    {
          Serial.print(".");
          delay(100);
          cnt++;
          if(cnt>30)                //ถ้าหากใช้เวลาเชื่อมต่อเกิน 5 วินาที ให้ออกจากฟังก์ชั่น
          return;
    } 
   
          
   Serial.println("Success");

   
   client.print(str_get1+str_get2+str_host);       //ส่งคำสั่ง HTTP GET ไปยัง Server
   Serial.println(str_get1+str_get2+str_host);

   digitalWrite(_req, HIGH);
   delay(1000);
   digitalWrite(_req, LOW);
   delay(100);
  } 

}

