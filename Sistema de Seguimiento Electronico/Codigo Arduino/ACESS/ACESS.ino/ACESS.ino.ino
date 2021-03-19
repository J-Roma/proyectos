#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 53
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Iniciar comunicacion serial
  SPI.begin();      // Iniciar  SPI bus
  mfrc522.PCD_Init();   // Iniciar MFRC522
  Serial.println("Acerca la tarjeta o llavero al lector...");
  Serial.println();

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
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "0D C0 4E 39") //UID Que proporciona acceso
  {
    Serial.println("Acceso autorizado");
    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println("Acceso denegado");
    delay(3000);
  }
} 
