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
            if(HTTP_req.indexOf("req") > -1) {  // 192.168.2.50/req
               client.println("<br><h1>Altium Designer Projects</h1>"); 
               client.println("<br><h1>www.altiumdesignerprojects.com</h1>");               
            }else{  // HTTP request for web page
               client.println("<!DOCTYPE html>");
               client.println("<html><body><h1>The XMLHttpRequest Object</h1>");
               client.println("<!DOCTYPE html>");
               client.println("<button type=\"button\" onclick=\"loadDoc()\">AJAX DATA</button> ");
               client.println("<br/><p><div id=\"demo\"></div></p> ");
               client.println("<script>");
               client.println("function loadDoc(){");
               client.println("var xhttp = new XMLHttpRequest();");
               client.println("xhttp.onreadystatechange = function(){");
               client.println("if (this.readyState == 4 && this.status == 200){document.getElementById(\"demo\").innerHTML = this.responseText;}}; ");
               client.println("xhttp.open(\"GET\", \"req\", true);");
               client.println("xhttp.send(null);");
               client.println("}");
               client.println("</script>");
               client.println("</body>");
               client.println("</html>");
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
