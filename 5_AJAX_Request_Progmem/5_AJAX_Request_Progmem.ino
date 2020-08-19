#include "index.h"
#include <SPI.h>
#include <WiFi101.h>
/*
 Hello 
 I design developer tools for embedded electronic systems. You can buy my projects design files.
 https://www.altiumdesignerprojects.com
*/
#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
#define WINC_EN   3  

char ssid[] = "TP-LINK-MCU";      
char pass[] = "15253545";  

int keyIndex = 0;                // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
WiFiServer server(80);

String HTTP_req;            // stores the HTTP request
int analog_val;
String convert_char = index_page; 

void setup(){
  pinMode(WINC_EN, OUTPUT); 
  digitalWrite(WINC_EN,HIGH);
  
  Serial.begin(9600);
  WiFi.setPins (WINC_CS, WINC_IRQ, WINC_RST);

  if (WiFi.status() == WL_NO_SHIELD){
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    delay(500);
  }
  server.begin();
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


void loop(){
  // listen for incoming clients
  WiFiClient client = server.available();
  if(client){
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while(client.connected()){
      if(client.available()){
        char c = client.read();
        HTTP_req += c;
        //Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: keep-alive");
            client.println();
            // AJAX request....
            if(HTTP_req.indexOf("request") > -1) {  // 192.168.2.50/request
               analog_val = analogRead(A0);         // read analog pin A0
               client.print("<p><h1>Analog A0: ");
               client.print(analog_val);
               client.println("</h1></p>");              
            }else{  // HTTP request for web page
               client.println(convert_char); 
            }            
            
            Serial.print(HTTP_req);
            HTTP_req = "";            // finished with request, empty string                    
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
