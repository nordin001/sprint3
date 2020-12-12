float sensortemperatura(int canal_temperatura){

 
 int adc4; // EL VARIABLE para para leer la valor digital del ADC
 int16_t temperatura;
 adc4=ads1115.readADC_SingleEnded (canal_temperatura);
  temperatura = (((adc4*4.096)/32767)-0.79)/0.034;//la funcion que cambia la valor analogica a una valor de temperatura en C.
    
  Serial.print("la temperatura vale: ");
  Serial.print(temperatura);
  Serial.println("ºC");
  delay(1500);
  
}
