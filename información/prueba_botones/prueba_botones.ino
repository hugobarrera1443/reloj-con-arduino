//------------------------------------------------------------
//                Declaración de Puertos
//------------------------------------------------------------
int btn1=12;  // Botón para fijar la hora
int btn2=11;  // Botón para fijar el día
int btn3=10;  // Botón para fijar alarma
int btn4=9;   // Botón para subir horas/minutos/segundos (+)
int btn5=8;   // Botón para bajar horas/minutos/segundos (-)
int btn6=7;   // Botón para setear los cambios
//-----------------------------------------------------------

void setup() {
     //-------------------------------------------
     //declaro los puerto comno entrada de datos 
     //-------------------------------------------
     pinMode(btn1,INPUT);
     pinMode(btn2,INPUT);
     pinMode(btn3,INPUT);
     pinMode(btn4,INPUT);
     pinMode(btn5,INPUT);
     pinMode(btn6,INPUT);   
     Serial.begin(9600);   
}

void loop(){
     status();
}

void status(){
     Serial.print(digitalRead(btn1));
     delay(500);
     Serial.print(digitalRead(btn2));
     delay(500);
     Serial.print(digitalRead(btn3));
     delay(500);
     Serial.print(digitalRead(btn4));
     delay(500);
     Serial.print(digitalRead(btn5));
     delay(500);
     Serial.print(digitalRead(btn6));
     delay(500);
     Serial.println();     
     return;
}