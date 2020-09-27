
#include <DHT.h>
#include <DHT_U.h>

// TODO Add basic config and read of DHT11 humidity and temp sensor
// TODO Add basic soil humidity sensor
// TODO Add basic use of LCD Nokia 5115

/*******************************
 * DHT temp and humidity sensor initialization
*******************************/
#define DHTTYPE DHT11
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

/*******************************
 * Soil humidity sensor initialization
*******************************/
int soil_pin = A0;
int soil_value;

void setup() {
  // Inicializamos comunicación serie
  Serial.begin(9600);
 
  // Comenzamos el sensor DHT
  dht.begin();
}

void loop() {
    // Esperamos 5 segundos entre medidas
  delay(5000);
 
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }

  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);

  // Leemos soil moisture
  soil_value = analogRead(soil_pin);
  // Map to percentage
  soil_value = map(soil_value, 550, 0, 0, 100);
  // Print to serial console.
  Serial.print("Humedad Ambiente: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");

  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");

  Serial.print("Humedad de Suelo: ");
  Serial.print(soil_value);
  Serial.println("%");
 
}
