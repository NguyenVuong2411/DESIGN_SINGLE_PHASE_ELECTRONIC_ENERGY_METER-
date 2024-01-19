#include <ESP8266WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include "secrets.h"
#include "SoftwareSerial.h"

SoftwareSerial uart1(D1, D2); // Kết nối UART mềm thứ nhất trên chân D1 (RX) và D1 (TX)
SoftwareSerial uart2(D5, D6); // Kết nối UART mềm thứ hai trên chân D5 (RX) và D6 (TX)

char ssid[] = "OPPO F11";   // ten wifi 
char pass[] = "vuong123";   // password
int keyIndex = 0;            
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

void setup() {
  Serial.begin(115200); 
  //mySerial.begin(9600);
  uart1.begin(9600);    // Kết nối UART mềm thứ nhất với tốc độ baud 9600
  uart2.begin(9600);    // Kết nối UART mềm thứ hai với tốc độ baud 9600
   // Initialize serial  
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak

}

void loop() {
  uint8_t receivedData[4];
  uint8_t receivedData1[4];
  float dong=0; 
  float Wh=0;
  // Connect or reconnect to WiFi
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network.
      delay(5000);     
    } 
        if (uart1.available()>= sizeof(receivedData)) {
               uart1.readBytes(receivedData, sizeof(receivedData));
               memcpy(&dong, receivedData, sizeof(float));
              }
     
       if (uart2.available()>= sizeof(receivedData1)) {
             uart2.readBytes(receivedData1, sizeof(receivedData1));
             memcpy(&Wh, receivedData1, sizeof(float));
              }
       ThingSpeak.setField(1, dong);
       ThingSpeak.setField(2, Wh);
       
       int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  delay(15000); // chờ 15s update the channel.
}
