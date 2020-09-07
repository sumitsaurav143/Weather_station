#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include <BMP180.h>
#include <Wire.h>
#include <DHT.h>

#define DHTPIN 2          
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
BMP180 bmp180;


//#define ALTITUDE 1655.0
#define USERNAME "SUMIT"
#define DEVICE_ID "ESP8266"
#define DEVICE_CREDENTIAL "MYPROJECT12345"
#define SSID "Mywifi"
#define SSID_PASSWORD "heartless"
unsigned int currentTs = 0;
unsigned long lastCheck = 0;
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);



void setup()
{
  thing.add_wifi(SSID, SSID_PASSWORD);
  pinMode(D3, OUTPUT);
  thing["LIGHT"] << digitalPin(D3);
  pinMode(14, OUTPUT);
  thing["RELAY"] << digitalPin(14);
  bmp180.init();
  Serial.begin(9600);
  Serial.println("BMP180 Demo");
  if (!bmp180.hasValidID())
    Serial.println("Error - please check the BMP180 board!");
    
  dht.begin();
  thing["dht11"] >> [](pson& out){
    out["humidity"]=dht.readHumidity();
    out["celsius"]=dht.readTemperature();
    out["fahrenheit"]=dht.readTemperature(true);
    
    //thing["BMP180"] >> [](pson& out){
    out["pressure"] = bmp180.getPressure();
   // out[“lon”] = gps.getLongitude();
};
    
  };
//  if (pressure.begin())
//    Serial.println("BMP180 init success");
//  else
//  {
//    Serial.println("BMP180 init fail\n\n");
//    while(1);
//  }
//}

void loop()
{
  thing.handle();
  
  Serial.print("Temperature: ");
  Serial.print(bmp180.getTemperature());
  Serial.println(" C");
  
  Serial.print("Pressure: ");
  Serial.print(bmp180.getPressure());
  Serial.println(" hPa");
  
  Serial.println();
  delay(2000);

  
//  char status;
//  double T,P,p0,a;
//  thing.handle();
//  unsigned long currentTs = millis();
//  if(currentTs-lastCheck>=60*5*1000){
//    lastCheck=currentTs;
//  }
//  Serial.println();
//  Serial.print("provided altitude: ");
//  Serial.print(ALTITUDE,0);
//  Serial.print(" meters, ");
//  Serial.print(ALTITUDE*3.28084,0);
//  Serial.println(" feet");
//  status = pressure.startTemperature();
//  if (status != 0)
//  {
//    delay(status);
//    status = pressure.getTemperature(T);
//    if (status != 0)
//    {
//      Serial.print("temperature: ");
//      Serial.print(T,2);
//      Serial.print(" deg C, ");
//      Serial.print((9.0/5.0)*T+32.0,2);
//      Serial.println(" deg F");
//      status = pressure.startPressure(3);
//      if (status != 0)
//      {
//        delay(status);
//        status = pressure.getPressure(P,T);
//        if (status != 0)
//        {
//          Serial.print("absolute pressure: ");
//          Serial.print(P,2);
//          Serial.print(" mb, ");
//          Serial.print(P*0.0295333727,2);
//          Serial.println(" inHg");
//          p0 = pressure.sealevel(P,ALTITUDE);
//          Serial.print("relative (sea-level) pressure: ");
//          Serial.print(p0,2);
//          Serial.print(" mb, ");
//          Serial.print(p0*0.0295333727,2);
//          Serial.println(" inHg");
//          a = pressure.altitude(P,p0);
//          Serial.print("computed altitude: ");
//          Serial.print(a,0);
//          Serial.print(" meters, ");
//          Serial.print(a*3.28084,0);
//          Serial.println(" feet");
//        }
//        else Serial.println("error retrieving pressure measurement\n");
//      }
//      else Serial.println("error starting pressure measurement\n");
//    }
//    else Serial.println("error retrieving temperature measurement\n");
//  }
//  else Serial.println("error starting temperature measurement\n");
//  delay(5000);
    if(dht.readTemperature()>30){
      thing.call_endpoint("My_Mail");
    }
}

