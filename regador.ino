
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

/********************************
 * Variables de control
********************************/
bool isButtonPressed = false;
int buttonPin = 3;
int button; // To keep track of button pressed to know when we put water.

unsigned long elapsedTime;
unsigned long startCount;

void setup() {
  // Inicializamos comunicación serie
  Serial.begin(9600);
  elapsedTime = 0;
  startCount = millis();
  // Comenzamos el sensor DHT
  dht.begin();
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(soil_pin, INPUT);
}

void loop() {
    // Esperamos 5 segundos entre medidas
  unsigned long currentTime = millis();
  elapsedTime = currentTime - startCount;

  // Comprobamos si hay pulsacion de boton, que indica riego.
  button = digitalRead(buttonPin);
  if (button != LOW && !isButtonPressed) {
    isButtonPressed = true;
  }

  if (elapsedTime > 5000) {
    elapsedTime = 0;
    startCount = millis();
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
    soil_value = readSensor(soil_pin);
    // Map to percentage
    //soil_value = map(soil_value, 550, 0, 0, 100);
    // Print to serial console.
    Serial.print("Humedad");
    Serial.print("\t");
    Serial.print("Temperatura");
    Serial.print("\t");
    Serial.print("Indice calor");
    Serial.print("\t");
    Serial.print("Humedad Suelo");
    Serial.print("\t");
    Serial.print("Is Button Pressed? ");
    Serial.print("\n");
    Serial.print(h);
    Serial.print("\t");
    Serial.print("\t");
    Serial.print(t);
    Serial.print("\t");
    Serial.print("\t");
    Serial.print(hic);
    Serial.print("\t");
    Serial.print("\t");
    Serial.print(soil_value);
    Serial.print("\t");
    Serial.print("\t");
    if (isButtonPressed) {
      Serial.print("True");
    } else {
      Serial.print("False");
    }

    Serial.print("\n");
  
    // Reset the value of the button
    isButtonPressed = false;
    delay(1000);
  }
}

//  This function returns the analog soil moisture measurement
int readSensor(int pin) {
	digitalWrite(pin, HIGH);	// Turn the sensor ON
	delay(10);							// Allow power to settle
	int val = analogRead(pin);	// Read the analog value form sensor
	digitalWrite(pin, LOW);		// Turn the sensor OFF
	return val;							// Return analog moisture value
}
