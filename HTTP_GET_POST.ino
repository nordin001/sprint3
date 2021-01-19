float wifi(int humedad,int salinidad,int temperatura,int luz) {

  String data[ 5 ];  // Podemos enviar hasta 8 datos

  data[ 1 ] = String(humedad); //Escribimos el dato 1. Recuerda actualizar numFields
#ifdef PRINT_DEBUG_MESSAGES
  Serial.print( "Humedad = " );
  Serial.println( data[ 1 ] );
#endif

  data[ 2 ] = String(salinidad); //Escribimos el dato 2. Recuerda actualizar numFields
#ifdef PRINT_DEBUG_MESSAGES
  Serial.print( "Salinidad = " );
  Serial.println( data[ 2 ] );
#endif

  data[ 3 ] = String(temperatura); //Escribimos el dato 2. Recuerda actualizar numFields
#ifdef PRINT_DEBUG_MESSAGES
  Serial.print( "Temperatura = " );
  Serial.println( data[ 3 ] );
#endif

  data[ 4 ] = String(luz); //Escribimos el dato 2. Recuerda actualizar numFields
#ifdef PRINT_DEBUG_MESSAGES
  Serial.print( "Iluminacion = " );
  Serial.println( data[ 4 ] );
#endif

  //Selecciona si quieres enviar con GET(ThingSpeak o Dweet) o con POST(ThingSpeak)
  HTTPPost( data, 4 );
  //HTTPGet( data, NUM_FIELDS_TO_SEND );

  //Selecciona si quieres un retardo de 15seg para hacer pruebas o dormir el SparkFun
  delay( 15000 );
  //Serial.print( "Goodnight" );
  //ESP.deepSleep( sleepTimeSeconds * 1000000 );

}
