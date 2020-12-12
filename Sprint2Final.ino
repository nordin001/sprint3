#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads1115(0x48); // Construct an ads1115 at address 0x48
void setup() {
  
 Serial.begin (9600); //Velocidad de funcionamiento del monitor serie
  Serial.println ("Inicializano...");
  ads1115.begin ();//Inicializando ads1115
  Serial.println ("Ajustando la ganancia...");
  ads1115.setGain (GAIN_ONE);
  Serial.println ("Tomando medidas de los canales A0 A1 A2");
}


void loop() {
  int timesegundos = 5 ; //el variable del tiempoen segundos
    sensorhumedad(0);//la funcion de el sensor de humedad
    sensorsalinidad(1);//la function del sensor de salinidad
    sensortemperatura(2);//la function del sensor de temperatura
    Serial.println("sleep time to save energy , see you ");
    ESP.deepSleep(timesegundos*1000000);// dormiendo

      //Serial.println("El microcontrolador está en sleep mode por 10 minutos ");
      //ESP.deepSleep(90000000);

  }
      
