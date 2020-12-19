#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads1115(0x48); // Construct an ads1115 at address 0x48

float sensoriluminacion(int canal_iluminacion){

//int input_pin = canal_iluminacion;
int adc0;
int16_t iluminacion;
adc0=ads1115.readADC_SingleEnded(canal_iluminacion);
Serial.print(adc0);
iluminacion = map(adc0,0,3000,0,100);
 Serial.print("Iluminacion: "); 
  Serial.print(iluminacion);
  Serial.println("%");
delay(1500);

if(iluminacion < 15){
  Serial.println("//////////////////////////////////////////////////////////");
  Serial.println("//////////////////////////////////////////////////////////");
  Serial.println("////////////////////¡OSCURIDAD!///////////////////////////");
  Serial.println("//////////////////////////////////////////////////////////");
  Serial.println("//////////////////////////////////////////////////////////");
  
}


if(iluminacion>=15 && iluminacion <= 25  ){
  Serial.println("//////////////////////////////////////////////////////////");
  Serial.println("//////////////////////////////////////////////////////////");
  Serial.println("////////////////////¡NUBLADO!/////////////////////////////");
  Serial.println("//////////////////////////////////////////////////////////");
  Serial.println("//////////////////////////////////////////////////////////");
  
}

if(iluminacion >25){

  Serial.println("//////////////////////////////////////////////////////////");
  Serial.println("//////////////////////////////////////////////////////////");
  Serial.println("////////////////////¡SOLEADO!/////////////////////////////");
  Serial.println("//////////////////////////////////////////////////////////");
  Serial.println("//////////////////////////////////////////////////////////");
  
}


  
}


void setup() {
  Serial.begin (9600); //Velocidad de funcionamiento del monitor serie
  Serial.println ("Inicializano...");
  ads1115.begin ();//Inicializando ads1115
  Serial.println ("Ajustando la ganancia...");
  ads1115.setGain (GAIN_ONE);
  Serial.println ("Tomando medidas del canal AIN2");

}

void loop() {

  sensoriluminacion(2);
 
}
