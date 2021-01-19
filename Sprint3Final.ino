
#include <ESP8266WiFi.h>

// Comentar/Descomentar para ver mensajes de depuracion en monitor serie y/o respuesta del HTTP server
#define PRINT_DEBUG_MESSAGES
//#define PRINT_HTTP_RESPONSE

// Comentar/Descomentar para conexion Fuera/Dentro de UPV
#define WiFi_CONNECTION_UPV

// Selecciona que servidor REST quieres utilizar entre ThingSpeak y Dweet
#define REST_SERVER_THINGSPEAK //Selecciona tu canal para ver los datos en la web (https://thingspeak.com/channels/360979)
//#define REST_SERVER_DWEET //Selecciona tu canal para ver los datos en la web (http://dweet.io/follow/PruebaGTI)

///////////////////////////////////////////////////////
/////////////// WiFi Definitions /////////////////////
//////////////////////////////////////////////////////

#ifdef WiFi_CONNECTION_UPV //Conexion UPV
const char WiFiSSID[] = "GTI1";
const char WiFiPSK[] = "1PV.arduino.Toledo";
#else //Conexion fuera de la UPV
const char WiFiSSID[] = "MIWIFI_5G_4DLM";
const char WiFiPSK[] = "wpi2PMvueqnS";
#endif



///////////////////////////////////////////////////////
/////////////// SERVER Definitions /////////////////////
//////////////////////////////////////////////////////

#if defined(WiFi_CONNECTION_UPV) //Conexion UPV
  const char Server_Host[] = "proxy.upv.es";
  const int Server_HttpPort = 8080;
#elif defined(REST_SERVER_THINGSPEAK) //Conexion fuera de la UPV
  const char Server_Host[] = "api.thingspeak.com";
  const int Server_HttpPort = 80;
#else
  const char Server_Host[] = "dweet.io";
  const int Server_HttpPort = 80;
#endif
WiFiClient client;

///////////////////////////////////////////////////////
/////////////// HTTP REST Connection ////////////////
//////////////////////////////////////////////////////

#ifdef REST_SERVER_THINGSPEAK 
  const char Rest_Host[] = "api.thingspeak.com";
  String MyWriteAPIKey="NZ1F9CKYX5G6KRKG"; // Escribe la clave de tu canal ThingSpeak
#else 
  const char Rest_Host[] = "dweet.io";
  String MyWriteAPIKey="cdiocurso2018g06"; // Escribe la clave de tu canal Dweet
#endif

#define NUM_FIELDS_TO_SEND 4 //Numero de medidas a enviar al servidor REST (Entre 1 y 8)

/////////////////////////////////////////////////////
/////////////// Pin Definitions ////////////////
//////////////////////////////////////////////////////

const int LED_PIN = 5; // Thing's onboard, green LED

/////////////////////////////////////////////////////
/////////////// WiFi Connection ////////////////
//////////////////////////////////////////////////////

void connectWiFi()
{
  byte ledStatus = LOW;

#ifdef PRINT_DEBUG_MESSAGES
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
#endif

  WiFi.begin(WiFiSSID, WiFiPSK);

  while (WiFi.status() != WL_CONNECTED)
  {
    // Blink the LED
    digitalWrite(LED_PIN, ledStatus); // Write LED high/low
    ledStatus = (ledStatus == HIGH) ? LOW : HIGH;
#ifdef PRINT_DEBUG_MESSAGES
    Serial.println(".");
#endif
    delay(500);
  }
#ifdef PRINT_DEBUG_MESSAGES
  Serial.println( "WiFi Connected" );
  Serial.println(WiFi.localIP()); // Print the IP address
#endif
}

/////////////////////////////////////////////////////
/////////////// HTTP POST  ThingSpeak////////////////
//////////////////////////////////////////////////////

void HTTPPost(String fieldData[4], int numFields) {

  // Esta funcion construye el string de datos a enviar a ThingSpeak mediante el metodo HTTP POST
  // La funcion envia "numFields" datos, del array fieldData.
  // Asegurate de ajustar numFields al número adecuado de datos que necesitas enviar y activa los campos en tu canal web

  if (client.connect( Server_Host , Server_HttpPort )) {

    // Construimos el string de datos. Si tienes multiples campos asegurate de no pasarte de 1440 caracteres

    String PostData = "api_key=" + MyWriteAPIKey ;
    for ( int field = 1; field < (numFields + 1); field++ ) {
      PostData += "&field" + String( field ) + "=" + fieldData[ field ];
    }

    // POST data via HTTP
#ifdef PRINT_DEBUG_MESSAGES
    Serial.println( "Connecting to ThingSpeak for update..." );
#endif
    client.println( "POST http://" + String(Rest_Host) + "/update HTTP/1.1" );
    client.println( "Host: " + String(Rest_Host) );
    client.println( "Connection: close" );
    client.println( "Content-Type: application/x-www-form-urlencoded" );
    client.println( "Content-Length: " + String( PostData.length() ) );
    client.println();
    client.println( PostData );
#ifdef PRINT_DEBUG_MESSAGES
    Serial.println( PostData );
    Serial.println();
    //Para ver la respuesta del servidor
#ifdef PRINT_HTTP_RESPONSE
    delay(500);
    Serial.println();
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    Serial.println();
    Serial.println();
#endif
#endif
  }
}





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

#ifdef PRINT_DEBUG_MESSAGES
  Serial.begin(9600);
#endif

  connectWiFi();
  digitalWrite(LED_PIN, HIGH);

#ifdef PRINT_DEBUG_MESSAGES
  Serial.print("Server_Host: ");
  Serial.println(Server_Host);
  Serial.print("Port: ");
  Serial.println(String( Server_HttpPort ));
  Serial.print("Server_Rest: ");
  Serial.println(Rest_Host);
#endif

}


void loop() {
  int timesegundos = 5 ; //el variable del tiempoen segundos
  int humedad;
  int salinidad;
  int temperatura;
  int luz;
  humedad=sensorhumedad(1);//la funcion de el sensor de humedad
  salinidad=sensorsalinidad(3);//la function del sensor de salinidad
  temperatura=sensortemperatura(2);//la function del sensor de temperatura
  luz=sensoriluminacion(0);//La funcion del sensor de iluminacion
  wifi(humedad, salinidad, temperatura, luz);
  Serial.println("sleep time to save energy , see you ");
  //ESP.deepSleep(timesegundos*1000000);// dormiendo


}
