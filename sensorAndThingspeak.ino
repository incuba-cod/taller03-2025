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
