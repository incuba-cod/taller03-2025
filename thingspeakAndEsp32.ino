    #include <WiFi.h>
    //#include "secrets.h"
    #include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
    
    char ssid[] = "INCUBAGRARIA -1";   // your network SSID (name) 
    char pass[] ="incuba062016" ;   // your network password
    int keyIndex = 0;            // your network key Index number (needed only for WEP)
    WiFiClient  client;
    
    unsigned long myChannelNumber =2913045 ;
    const char * myWriteAPIKey = "J2STDMLM2SL9ZNQV";
    
    int number = 0;
    
    void setup() {
      Serial.begin(115200);  //Initialize serial
      while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo native USB port only
      }
      
      WiFi.mode(WIFI_STA);   
      ThingSpeak.begin(client);  // Initialize ThingSpeak
    }
    
    void loop() {
    
      // Connect or reconnect to WiFi
      if(WiFi.status() != WL_CONNECTED){
        Serial.print("Attempting to connect to SSID: ");
        //Serial.println(SECRET_SSID);
        while(WiFi.status() != WL_CONNECTED){
          WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
          Serial.print(".");
          delay(5000);     
        } 
        Serial.println("\nConnected.");
      }
    
      // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
      // pieces of information in a channel.  Here, we write to field 1.
      int x = ThingSpeak.writeField(myChannelNumber, 1, number, myWriteAPIKey);
      if(x == 200){
        Serial.println("Channel update successful.");
      }
      else{
        Serial.println("Problem updating channel. HTTP error code " + String(x));
      }
      
      // change the value
      number++;
      if(number > 99){
        number = 0;
      }
      
      delay(20000); // Wait 20 seconds to update the channel again
    }
