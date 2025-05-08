/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-temperature-via-web
 */

#include <WiFi.h>
#include <dhtnew.h>

const char* ssid = "TP-Link_D50B";  // change your network SSID (name)
const char* password = "41624151";   // change your network password (use for WPA, or use as key for WEP)

DHTNEW mySensor(5);  // Arduino pin connected to DS18B20 sensor's DQ pin

WiFiServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(10);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    // read the HTTP request header line by line
    while (client.connected()) {
      if (client.available()) {
        String HTTP_header = client.readStringUntil('\n');  // read the header line of HTTP request

        if (HTTP_header.equals("\r"))  // the end of HTTP request
          break;

        Serial.print("<< ");
        Serial.println(HTTP_header);  // print HTTP request to Serial Monitor
      }
    }

    // send the HTTP response
    // send the HTTP response header
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  // the connection will be closed after completion of the response
    client.println();                     // the separator between HTTP header and body
    // send the HTTP response body
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    client.println("</head>");

    client.println("<p>");

    client.println("<script type='text/javascript'>  "); 
    client.println("setTimeout(function(){ window.location.reload(1); }, 1000); ");
    client.println(" </script>");
    
    mySensor.read();

    client.print("Temperature: <span style=\"color: red;\">");
    float temperature = mySensor.getTemperature();
    //float temperature = getTemperature();
    client.print(temperature, 2);
    client.println("&deg;C</span>");

    client.print("<br />");

    client.print("Humiduty <span style=\"color: green;\">");
    float humidity = mySensor.getHumidity();
    //float temperature = getTemperature();
    client.print(humidity, 2);
    client.println(" %");

    client.println("</p>");
    client.println("</html>");
    client.flush();


    // give the web browser time to receive the data
    delay(10);

    // close the connection:
    client.stop();
  }
}

void printWifiStatus() {
  // print your board's IP address:
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // print the received signal strength:
  Serial.print("signal strength (RSSI):");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}
