#include <Wire.h>
#include <AT24CX.h>

AT24C32 EepromRTC;

void setup() {
  Serial.begin(9600);
}

int i=1  ;
void loop() {
  // read and write byte
  byte variable_byte=235;
  int variable_int=3000;
  long variable_long=48300011;
  float variable_float=3.14;
  
  char cadena[30] = "Naylamp Mechatronics";
  
  if(i==1){
    Serial.println("Guardando datos en la EEPROM...");
    EepromRTC.writeInt(2,12); //cada valor int que gurdo ocupa 2 bytes
    EepromRTC.writeInt(4,22); //(2,4 y 6 son las direcciones en memoria)
    EepromRTC.writeInt(6,23); //  EepromRTC.writeInt graba un dato en posisión de memoria específico        
    i=2;    
  }
  
  
  Serial.println("Leyendo datos guardados...");

  int a = EepromRTC.read(2);
  int b = EepromRTC.readInt(4);
  int c = EepromRTC.readLong(6);
  
  


  Serial.print("hora: ");Serial.println(a);
  Serial.print("minutos: "); Serial.println(b);
  Serial.print("segundos: "); Serial.println(c);
  Serial.println();

  delay(5000);
}