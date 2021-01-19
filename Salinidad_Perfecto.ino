 float sensorsalinidad(int canal_salinidad){
    const int SalValue = 6300;
    const int NoSalValue = 40;
    int power_pin = 5; //El pin que usamos es el 5
    int adc1;
    digitalWrite (power_pin, HIGH);
    delay (100);
   
    int salinidad;
    adc1 = ads1115.readADC_SingleEnded(canal_salinidad); //Se miden valores con el sensor de salinidad
    salinidad = 100 * NoSalValue / (NoSalValue - SalValue) - adc1 * 100 / (NoSalValue - SalValue);//Se define la fórmula para hallar la salinidad
    digitalWrite (power_pin, LOW);

    if (salinidad < 0) { //Si la salinidad es inferior a 0, se ajusta para que sea 0 y así calibrarlo completamente

      salinidad = 0;
    }

    if (salinidad > 100) { //Si la salinidad es superior a 100, se ajusta para que sea 100 y así calibrarlo completamente

      salinidad = 100;
    }

    //Serial.print("AIN1: ");
    //Serial.println(adc1);

    //Se escribe en pantalla el porcentaje de salinidad
    Serial.print("Salinidad (%): ");
    Serial.print(salinidad);
    Serial.println("%");


    if (salinidad > 20) { //Si el valor de la salinidad es mayor a 20 es perjudicial para la planta

      Serial.println("//////////////////////////////////////////////////////////");
      Serial.println("////////////////¡ALERTA! ¡ALERTA! ¡ALERTA!////////////////");
      Serial.println("///////////////////¡HAY MUCHA SALINIDAD///////////////////");
      Serial.println("//////////////////////////////////////////////////////////");

    } else { //Si la salinidad es inferior a 20 entonces es idónea

      Serial.println("////////////////////SALINIDAD IDÓNEA////////////////////");

    }

    Serial.println("");
    Serial.println("");


    delay(2500); //Tiene un temporizador entre comprobación de un segundo y medio.

    return salinidad;
    }
