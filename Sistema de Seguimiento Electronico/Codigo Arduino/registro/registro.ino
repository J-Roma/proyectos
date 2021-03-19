#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(10,11); // Configura el puerto serial para el SIM900. Para el Arduino MEGA utilizar pines 10 y 11

 void setup() {
  gprsSerial.begin(19200);
  Serial.begin(19200);

  Serial.println("Config SIM900...");
  delay(2000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();

//Verificacion funcionamiento SIM 900
  gprsSerial.println("AT");
  delay(100);
  toSerial();
  
//Devuelve el estado de calidad de la señal de cobertura
  gprsSerial.println("AT+CSQ");
  delay(100);
  toSerial();

  // attach or detach from GPRS service 
  gprsSerial.println("AT+CGATT?");
  delay(100);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(2000);
  toSerial();

  // bearer settings 
  //Conexion al servidor y enviar los dos datos requeridos por el metodo GET a la base de datos.
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"internet.movistar.com.co\"");
  delay(2000);
  toSerial();

  // bearer settings
   gprsSerial.println("AT+SAPBR=1,1");
  delay(2000);
  toSerial();
  
  gprsSerial.println("AT+SAPBR=2,1");
  delay(2000);
  toSerial();
  
  http();

}

void http ()
{ 
   // initialize http service
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();

   gprsSerial.println("AT+HTTPPARA=\"CID\",1" );
   delay(2000); 
   toSerial();
  // put your main code here, to run repeatedly:
   String url = "AT+HTTPPARA=\"URL\",\"http://www.app-ipuc.com/proyecto/index.php?valor=jhosep";
   int h1= 1 ;
  //url = url + "?valor=";
 // url = url+ h1 ;
 // con /default.aspx supuestamente se soluciona el error

   url = url + "\"";
   
   gprsSerial.println(url);
    delay(2000);
    toSerial();

   // set http action type 0 = GET, 1 = POST, 2 = HEAD
   gprsSerial.println("AT+HTTPACTION=0");
   delay(6000);
   toSerial();

   // read server response
   gprsSerial.println("AT+HTTPREAD"); 
   delay(1000);
   toSerial();

   gprsSerial.println("");
   gprsSerial.println("AT+HTTPTERM");
   toSerial();
   delay(300);

   gprsSerial.println("");
   delay(10000);
  }

void loop() {
  
    
}
void toSerial()
{
  while(gprsSerial.available()!=0)
  {
    Serial.write(gprsSerial.read());
  }
}

