#define BLYNK_TEMPLATE_ID "TMPL37DmRuejo"
#define BLYNK_TEMPLATE_NAME "Mini IoT Project"
#define BLYNK_AUTH_TOKEN "EHn2og4rCLN1pGelp-u9uBVlEzoQKwDg"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN D4        
#define DHTTYPE DHT11      

char ssid[] = "nihal";        
char pass[] = "nihal123";     


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensorData() {
  int gas = analogRead(A0); 
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
                    
  Serial.printf("Gas: %d  Temp: %.2f Humi: %.2f \n", gas,temp,humi); 
  Blynk.virtualWrite(V0, gas); Blynk.virtualWrite(V1, temp); Blynk.virtualWrite(V2, humi);      

  if (gas  > 100) Blynk.logEvent("gas_alert", "⚠️ Gas Leakage Detected!");
  if (temp > 30) Blynk.logEvent("temp_alert", "⚠️ high Temp Detected!");

}

void setup() {
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2500L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
