# taller03-2025
taller esp32 con ds18b20 con conexión a thingspeak

¿Te gustaría aprender a medir temperatura con el sensor DS18B20 y enviar los datos a la nube en ThingSpeak? 🚀 En este taller, te enseñaremos paso a paso cómo hacerlo con un ESP32.

📌 ¿Qué aprenderás?  
✅ Conectar y programar el sensor DS18B20 en un ESP32  
✅ Enviar datos a la nube usando ThingSpeak  
✅ Visualizar la información en gráficos en tiempo real  
✅ Aplicaciones prácticas para IoT  

🛠 Materiales y requisitos  
🔹 ESP32  
🔹 Sensor DS18B20 (con resistencia de 4.7kΩ)  
🔹 Cables y protoboard  
🔹 Conexión a Internet vía WiFi  
🔹 Editor Arduino IDE  

🏗 Paso a Paso: ESP32 con DS18B20 y conexión a ThingSpeak  
1️⃣ Configuración del entorno de desarrollo
Antes de comenzar, asegúrate de tener el Arduino IDE instalado y configurado para el ESP32:

🔹 Instalar Arduino IDE (si aún no lo tienes)
🔹 Agregar la placa ESP32 en el Administrador de tarjetas

🔹 Instalar librerías necesarias:

    OneWire → Para la comunicación con el DS18B20
    
    DallasTemperature → Para interpretar los datos del sensor
    
    WiFi → Para la conexión a Internet
    
    HTTPClient → Para enviar datos a ThingSpeak
2️⃣ Conexión del ESP32 con el DS18B20
El DS18B20 es un sensor de temperatura digital que se comunica mediante el protocolo OneWire.

🔌 Conexión de pines:  

DS18B20	ESP32  
VCC	---- 3.3V  
GND	---- GND  
DQ	---- GPIO 4 (u otro pin digital)  
⚠ IMPORTANTE: Conectar una resistencia de 4.7kΩ entre el pin DQ y VCC para garantizar la comunicación.  

3️⃣ Programación para leer temperatura
Ahora, cargamos el siguiente código para leer la temperatura y mostrarla en el monitor serie:

        
    #include "OneWire.h"
    #include "DallasTemperature.h"
    
    #define ONE_WIRE_BUS 4
    
    OneWire oneWire(ONE_WIRE_BUS);
    DallasTemperature sensors(&oneWire);
    
    void setup(void)
    {
      Serial.begin(9600);
      Serial.println("Dallas Temperature IC Control Library Demo");
      sensors.begin();
      
    }
    
    void loop(void)
    {
      Serial.print("Requesting temperatures...");
      sensors.requestTemperatures(); // Send the command to get temperatures
      Serial.println("DONE");
      float tempC = sensors.getTempCByIndex(0);
    
      if (tempC != DEVICE_DISCONNECTED_C)
      {
        Serial.print("Temperature for the device 1 (index 0) is: ");
        Serial.println(tempC);
      }
      else
      {
        Serial.println("Error: Could not read temperature data");
      }
    
      
    }
    
✅ Sube el código al ESP32 y abre el Monitor Serie para ver la temperatura en tiempo real.

4️⃣ Crear una cuenta y canal en ThingSpeak
Ve a ThingSpeak y crea una cuenta.

Crea un nuevo canal y asigna un campo para la temperatura.

Copia la API Key de Escritura (Write API Key) porque la usaremos en el código.

5️⃣ Enviar datos del ESP32 a ThingSpeak


        #include <WiFi.h>
        #include "secrets.h"
        #include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
        
        char ssid[] = SECRET_SSID;   // your network SSID (name) 
        char pass[] = SECRET_PASS;   // your network password
        int keyIndex = 0;            // your network key Index number (needed only for WEP)
        WiFiClient  client;
        
        unsigned long myChannelNumber = SECRET_CH_ID;
        const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
        
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
            Serial.println(SECRET_SSID);
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


6️⃣ Enviar datos del sensor ds18b20 a ThingSpeak

        #include <WiFi.h>
        #include "secrets.h"
        #include "ThingSpeak.h" // Siempre incluir ThingSpeak después de otros headers y macros personalizados
        #include <OneWire.h>
        #include <DallasTemperature.h>
        
        #define ONE_WIRE_BUS 4  // Definimos el pin donde está conectado el sensor DS18B20
        
        // Configuración para la comunicación con el sensor DS18B20
        OneWire oneWire(ONE_WIRE_BUS);
        DallasTemperature sensors(&oneWire);
        
        // Datos de la red WiFi
        char ssid[] = "NOMBRE";   // Nombre de la red WiFi
        char pass[] = "CONTRASEÑA";   // Contraseña de la red WiFi
        WiFiClient  client;  // Cliente WiFi para conectarse a ThingSpeak
        
        // Configuración de ThingSpeak
        unsigned long myChannelNumber = chanel;  // Número del canal de ThingSpeak
        const char * myWriteAPIKey = "apikay";   // API Key para escribir en el canal
        
        void setup() {
          Serial.begin(115200);  // Iniciamos la comunicación serie
          sensors.begin();  // Iniciamos el sensor DS18B20
          
          // Configuración de WiFi
          WiFi.mode(WIFI_STA);  // Configura el ESP32 en modo estación
          ThingSpeak.begin(client);  // Inicializa la comunicación con ThingSpeak
        }
        
        void loop() {
          // Verifica si el ESP32 está conectado a WiFi, si no, intenta conectarse
          if (WiFi.status() != WL_CONNECTED) {
            Serial.print("Intentando conectar a la red: ");
            Serial.println(SECRET_SSID);
            while (WiFi.status() != WL_CONNECTED) {
              WiFi.begin(ssid, pass);  // Se intenta conectar a la red
              Serial.print(".");
              delay(5000);  // Espera antes de intentar de nuevo
            }
            Serial.println("\nConectado.");
          }
        
          // Obtiene la temperatura en grados Celsius desde el sensor DS18B20
          float tempC = sensors.getTempCByIndex(0);
        
          // Envía la temperatura a ThingSpeak en el campo 1 del canal
          int x = ThingSpeak.writeField(myChannelNumber, 1, tempC, myWriteAPIKey);
        
          // Espera 20 segundos antes de enviar el siguiente dato
          delay(20000);
        }


8️⃣ Link de video





