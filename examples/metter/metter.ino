#include <ESP8266WiFi.h>

#include <IoTplant_DigitalPin.h>
#include <IoTplant_WIFI.h>


//หลอดไฟ  แสดงสถานนะ  WIFI  
const int LED_Red  =  D7;
const int LED_Green = D8; 
 
//หลอดไฟแสดงสถานะการส่งข้อมูล
const int LED_REQUEST = D6;
//หลอดไฟแสดงสถานะ
DigitalPin WIFI_GREEN(LED_Green);
DigitalPin WIFI_RED(LED_Red);


//gpio
const int gpio = A0; 

//wifi 
char ssid[] = "ssid-wifi";
char pass[] = "password-wifi";




void setup() {
  //led bein
  WIFI_GREEN.begin();
  WIFI_RED.begin();

  set_req(LED_REQUEST);
  Serial.begin(115200); 

  WIFI_RED.on();
  if(wifi(ssid,pass)){
      WIFI_GREEN.on();
      WIFI_RED.off();        
  }else{
      WIFI_GREEN.off(); 
      WIFI_RED.on();
  }
    
}

void loop() {
   readingIn = analogRead(gpio);
   readingIn = convertToPercent(readingIn);
   api_send("xxxxx"); //api-key

}
