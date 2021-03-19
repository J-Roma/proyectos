#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#define SS_PIN 53
#define RST_PIN 9
SoftwareSerial gprsSerial(10,11); // Configura el puerto serial para el SIM900
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
//byte ActualUID[4];
String a= " ";
void setup() 
{
  gprsSerial.begin(19200);
  Serial.begin(19200);   // Iniciar comunicacion serial
  SPI.begin();      // Iniciar  SPI bus
  mfrc522.PCD_Init();   // Iniciar MFRC522
  Serial.println("Acerca la tarjeta o llavero al lector...");
  Serial.println();
  conexion();
}
void conexion ()
{
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

  }
  void toSerial()
{
  while(gprsSerial.available()!=0)
  {
    Serial.write(gprsSerial.read());
  }
}
void loop() 
{
  
  // Buscar UID nueva
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Seleccionar una UID
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostrar UID en Monitor serial
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : "");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
     //ActualUID[i]=mfrc522.uid.uidByte[i]; 
     //a= "" + ActualUID[i] ;
     
  }
  
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "0DC04E39") //UID Que proporciona acceso
  {
    a= "" + content.substring(1) ;
    Serial.println("Acceso autorizado");
    Serial.println();
    
    // initialize http service
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();

   gprsSerial.println("AT+HTTPPARA=\"CID\",1" );
   delay(2000); 
   toSerial();
  // put your main code here, to run repeatedly:
   String url = "AT+HTTPPARA=\"URL\",\"http://www.app-ipuc.com/proyecto/autorow.php";
   //tag llavero 0D C0 4E 39
   url = url + "?tag=";
   url = url+ a ;
   url = url + "\"";
   
   gprsSerial.println(url);
    delay(2000);
    toSerial();

   // Accion HTTP 0 = GET, 1 = POST, 2 = HEAD
   gprsSerial.println("AT+HTTPACTION=0");
   delay(6000);
   toSerial();

   // Leer Respuesta del servidor 
   gprsSerial.println("AT+HTTPREAD"); 
   delay(1000);
   toSerial();
  // Termina la conexion HTTP
   gprsSerial.println("");
   gprsSerial.println("AT+HTTPTERM");
   toSerial();
   delay(300);

   gprsSerial.println("");
   delay(10000);
    delay(3000);
  }
 
 else   {
    Serial.println("Acceso denegado");
    delay(3000);
  }
} 
