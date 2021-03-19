#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>

// your network name also called SSID
char ssid[] = "iPhone de Pi";
// your network password
char password[] = "pipe12345";

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(50,62,217,1);  // numeric IP for Google (no DNS)
char server[] = "cry.com.co";    // name address for Google (using DNS)

const int MQ_PIN135 = 23;      // Pin del sensor
const int MQ_PIN2 = 24;      // Pin del sensor
const int MQ_PIN3 = 25;      // Pin del sensor
const int MQ_PIN4 = 26;      // Pin del sensor
const int MQ_PIN5 = 27;      // Pin del sensor
const int MQ_PIN6 = 28;      // Pin del sensor
//const int MQ_PIN7 = A7;      // Pin del sensor
//const int MQ_PIN8 = A8;      // Pin del sensor
const int RL_VALUE = 5;      // Resistencia RL del modulo en Kilo ohms
const int R0 = 10;          // Resistencia R0 del sensor en Kilo ohms
 
// Datos para lectura multiple
const int READ_SAMPLE_INTERVAL = 100;    // Tiempo entre muestras
const int READ_SAMPLE_TIMES = 5;       // Numero muestras
 
// Ajustar estos valores para vuestro sensor según el Datasheet
// (opcionalmente, según la calibración que hayáis realizado)
const float X0_2 = 200;   float X0_135=10;  float X0_3=0.1;  float X0_4=200;   float X0_5=200;   float X0_6=200;  // float X0_7=40;  float X0_8=200;        
const float Y0_2 = 1.75;   float Y0_135=2.3; float Y0_3=2.4;  float Y0_4=1.9;   float Y0_5=0.7;   float Y0_6=10;   //float Y0_7=1.7; float Y0_8=9;
const float X1_2 = 10000; float X1_135=200; float X1_3=10;   float X1_4=10000; float X1_5=10000; float X1_6=10000; //float X1_7=4000;float X1_8=10000;
const float Y1_2 = 0.28;  float Y1_135=0.8; float Y1_3=0.12; float Y1_4=4.5;   float Y1_5=0.26;  float Y1_6=10;    //float Y1_7=0.5; float Y1_8=0.29;
 
// Puntos de la curva de concentración {X, Y}
const float punto0_2[] = { log10(X0_2), log10(Y0_2) };
const float punto1_2[] = { log10(X1_2), log10(Y1_2) };

// Puntos de la curva de concentración {X, Y}
const float punto0_135[] = { log10(X0_135), log10(Y0_135) };
const float punto1_135[] = { log10(X1_135), log10(Y1_135) };

// Puntos de la curva de concentración {X, Y}
const float punto0_3[] = { log10(X0_3), log10(Y0_3) };
const float punto1_3[] = { log10(X1_3), log10(Y1_3) };


// Puntos de la curva de concentración {X, Y}
const float punto0_4[] = { log10(X0_4), log10(Y0_4) };
const float punto1_4[] = { log10(X1_4), log10(Y1_4) };

// Puntos de la curva de concentración {X, Y}
const float punto0_5[] = { log10(X0_5), log10(Y0_5) };
const float punto1_5[] = { log10(X1_5), log10(Y1_5) };

 // Puntos de la curva de concentración {X, Y}
const float punto0_6[] = { log10(X0_6), log10(Y0_6) };
const float punto1_6[] = { log10(X1_6), log10(Y1_6) };


 // Puntos de la curva de concentración {X, Y}
//const float punto0_7[] = { log10(X0_7), log10(Y0_7) };
//const float punto1_7[] = { log10(X1_7), log10(Y1_7) };

 // Puntos de la curva de concentración {X, Y}
//const float punto0_8[] = { log10(X0_8), log10(Y0_8) };
//const float punto1_8[] = { log10(X1_8), log10(Y1_8) };

// Calcular pendiente y coordenada abscisas MQ2
const float M2 = (punto1_2[1] - punto0_2[1]) / (punto1_2[0] - punto0_2[0]);
const float B2 = punto0_2[1] - punto0_2[0] * M2;
// Calcular pendiente y coordenada abscisas MQ135
const float M135 = (punto1_135[1] - punto0_135[1]) / (punto1_135[0] - punto0_135[0]);
const float B135 = punto0_135[1] - punto0_135[0] * M135;
// Calcular pendiente y coordenada abscisasMQ3
const float M3 = (punto1_3[1] - punto0_3[1]) / (punto1_3[0] - punto0_3[0]);
const float B3 = punto0_3[1] - punto0_3[0] * M3;
// Calcular pendiente y coordenada abscisasMQ4
const float M4 = (punto1_4[1] - punto0_4[1]) / (punto1_4[0] - punto0_4[0]);
const float B4 = punto0_4[1] - punto0_4[0] * M4;
// Calcular pendiente y coordenada abscisasMQ5
const float M5 = (punto1_5[1] - punto0_5[1]) / (punto1_5[0] - punto0_5[0]);
const float B5 = punto0_5[1] - punto0_5[0] * M5;
// Calcular pendiente y coordenada abscisasMQ6
const float M6 = (punto1_6[1] - punto0_6[1]) / (punto1_6[0] - punto0_6[0]);
const float B6 = punto0_6[1] - punto0_6[0] * M6;
//// Calcular pendiente y coordenada abscisasMQ7
//const float M7 = (punto1_7[1] - punto0_7[1]) / (punto1_7[0] - punto0_7[0]);
//const float B7 = punto0_7[1] - punto0_7[0] * M7;
//
//// Calcular pendiente y coordenada abscisasMQ8
//const float M8 = (punto1_8[1] - punto0_8[1]) / (punto1_8[0] - punto0_8[0]);
//const float B8 = punto0_8[1] - punto0_8[0] * M8;



// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;
  
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

/*void closeconn(){
  
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
  
  }
*/

void setup() {

  
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nIP Address obtained");
  printWifiStatus();
  Serial.println("\nStarting connection to server...");
}
float readMQ(int mq_pin)
{
   float rs = 0;
   for (int i = 0;i<READ_SAMPLE_TIMES;i++) {
      rs += getMQResistance(analogRead(mq_pin));
      delay(READ_SAMPLE_INTERVAL);
   }
   return rs / READ_SAMPLE_TIMES;
}
 
// Obtener resistencia a partir de la lectura analogica
float getMQResistance(int raw_adc)
{
   return (((float)RL_VALUE / 1000.0*(1023 - raw_adc) / raw_adc));
}
 
 
// Obtener concentracion 10^(coord + scope * log (rs/r0)
float getConcentration(float rs_ro_ratio, float M, float B)
{
   return pow(10, B + M * log(rs_ro_ratio));
}

void loop() {
   float rs_med2 = readMQ(MQ_PIN2);      // Obtener la Rs promedio
   float concentrationMQ2 = getConcentration(rs_med2/R0, M2, B2);   // Obtener la concentración

   float rs_med135 = readMQ(MQ_PIN135);      // Obtener la Rs promedio
   float concentrationMQ135 = getConcentration(rs_med135/R0, M135, B135);   // Obtener la concentración

   float rs_med3 = readMQ(MQ_PIN3);      // Obtener la Rs promedio
   float concentrationMQ3 = getConcentration(rs_med3/R0, M3, B3);   // Obtener la concentración

   float rs_med4 = readMQ(MQ_PIN4);      // Obtener la Rs promedio
   float concentrationMQ4 = getConcentration(rs_med4/R0, M4, B4);   // Obtener la concentración

   float rs_med5 = readMQ(MQ_PIN5);      // Obtener la Rs promedio
   float concentrationMQ5 = getConcentration(rs_med5/R0, M5, B5);   // Obtener la concentración

   float rs_med6 = readMQ(MQ_PIN6);      // Obtener la Rs promedio
   float concentrationMQ6 = getConcentration(rs_med6/R0, M6, B6);   // 
  delay(2000);
  /*
    int adc_MQ8 = analogRead(2); //Lemos la salida analógica del MQ135 PB_5
  int adc_MQ7 = analogRead(29); //PE_3
  int adc_MQ6 = analogRead(28); //PE_2
  int adc_MQ5 = analogRead(27); //PE_1
  int adc_MQ4 = analogRead(26); //PD_3
  int adc_MQ3 = analogRead(25); //PD_2
  int adc_MQ2 = analogRead(24); //PD_1
  int adc_MQ135 = analogRead(23);//PD_0
  */
  String cadena = "";
    cadena = "GET /usta/noseproyect/toma.php/" ;
    cadena = cadena + "?dato1=" + concentrationMQ2 ;
    cadena = cadena +"&dato2=" + concentrationMQ3;
    cadena = cadena +"&dato3=" + concentrationMQ5;
    cadena = cadena +"&dato4=" + concentrationMQ6;
    cadena = cadena +"&dato5=" + concentrationMQ4;  //7
    cadena = cadena +"&dato6=" + concentrationMQ4; //8
    cadena = cadena +"&dato7=" + concentrationMQ135;
    cadena = cadena + " HTTP/1.1";
    
   if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request
    Serial.println(cadena); //Para verificar que este bien la peticion
    client.println(cadena);
    //client.println("GET /radio/noseproyect/toma.php/?dato1=1&dato2=2&dato3=3&dato4=4&dato5=5&dato6=6&dato7=7&dato8=8&dato9=9 HTTP/1.1");
    client.println("Host: cry.com.co");
    client.println("Connection: close");
    client.println();
   // delay (1500);
    //client.stop();
  }
   if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();
    
    // do nothing forevermore:
    //while (true);
  }
   delay(5000);

}








