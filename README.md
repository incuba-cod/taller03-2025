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
