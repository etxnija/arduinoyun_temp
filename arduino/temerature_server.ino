

// Possible commands are listed here:
// "tempF"          -> Tempertatur in F
// "tempC"          -> Temperatiure in C
// "
//
// https://www.virtuabotix.com/virtuabotix-dht22-pinout-coding-guide/
// https://www.virtuabotix.com/product/virtuabotix-dht22-temperature-humidity-sensor-arduino-microcontroller-circuits/
// http://www.amazon.com/Ventisonic%C2%AE-Digital-Temperature-Humidity-Arduino/dp/B00KD3GUVM/ref=pd_sbs_indust_6?ie=UTF8&refRID=1Z3KTK1SRPQK8NAPARGE


#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <dht22.h>
#include <Versalino.h>

// Listen on default port 5555, the webserver on the Yun
// will forward there all the HTTP requests for us.
YunServer server;
dht22 myDHT22 = dht22(7); //using pin 7 as our IO

void setup() {
  Serial.begin(9600);

  // Bridge startup
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();

  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) {
    // Process request
    process(client);

    // Close connection and free resources.
    client.stop();
  }

  delay(50); // Poll every 50ms
}

void process(YunClient client) {
  // read the command
    digitalWrite(13, HIGH);
    String command = client.readString();
    command.trim();        //kill whitespace
    myDHT22.read();
  
  if (command == "tempF") {
    double myDegreesF = myDHT22.fahrenheit();
    client.println(myDegreesF);
  }
  else if (command == "tempC") {
    double myDegreesC= myDHT22.celcius();
    client.println(myDegreesC);
  }
  else if(command == "humidity") {
    double myHuminity = myDHT22.humidity;
    client.println(myHuminity);
  }
  else  {
     client.println(F("Not Found"));
  }
  digitalWrite(13, LOW);

}

