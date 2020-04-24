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
 * Nokia 5110 initialization
*******************************/

/*******************************
 * Soil humidity sensor initialization
*******************************/

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
  // Leemos la temperatura en grados Fahrenheit
  float f = dht.readTemperature(true);
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
  // Calcular el índice de calor en Fahrenheit
  float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
 
}
