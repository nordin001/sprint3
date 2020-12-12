int sensorhumedad(int canal_humedad){
  const int AirValue = 31250;  // Medimos valor en seco
  const int WaterValue = 16800;  // Medimos valor en agua
  int16_t humedad;
  int16_t adc0;
  adc0 = ads1115.readADC_SingleEnded(canal_humedad); //Se miden valores con el sensor de temperatura
  humedad = 100*AirValue/(AirValue-WaterValue)-adc0*100/(AirValue-WaterValue); //Se define la fórmula para hallar la humedad
  //Serial.print(adc0);
  //Serial.print("AIN0: ");
  if(humedad > 95){ //Si el valor de la humedad es mayor a 95 es perjudicial para la planta

  Serial.println("//////////////////////////////////////////////////////////");
  Serial.println("////////////////¡ALERTA! ¡ALERTA! ¡ALERTA!////////////////");
  Serial.println("////////////////////¡HAY MUCHA HUMEDAD////////////////////");
  Serial.println("//////////////////////////////////////////////////////////");
  
  } else if (humedad < 20) { //Si el valor de la humedad es menor de 20 es muy baja para la planta 

  Serial.println("//////////////////////////////////////////////////////////");
  Serial.println("////////////////¡ALERTA! ¡ALERTA! ¡ALERTA!////////////////");
  Serial.println("/////////////////////¡te necesita mas agua ////////////////////");
  Serial.println("//////////////////////////////////////////////////////////");
  
  } else if (20 <= humedad <= 95){ //Si el valor de la humedad se encuentra entre 20 y 95 es un valor idóneo.
    
  Serial.println("//////////////////////////////////////////////////////////");
  Serial.println("//////////////////////HUMEDAD IDÓNEA//////////////////////");
  Serial.println("//////////////////////////////////////////////////////////");
  
  }
  //Serial.println(adc0);
  Serial.print("HR (%): ");

  if (humedad < 0 ){

    humedad =0;
  }
  Serial.print(humedad);
  Serial.println("%");

  delay(2500);
  
  }
