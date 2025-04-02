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

6️⃣ Visualizar datos en gráficos en la nube

