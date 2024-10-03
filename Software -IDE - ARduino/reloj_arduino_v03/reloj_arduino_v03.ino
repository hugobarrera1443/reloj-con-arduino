//--------------------------------
//    Librerias a utilizar
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
#include <AT24CX.h>
//--------------------------------
//--------------------------------
//  Defino las notas musicales
//--------------------------------
#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880
//frequencies for the tones we're going to use
//used http://home.mit.bme.hu/~bako/tonecalc/tonecalc.htm to get these
//--------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                      Declaración de Arrays de Strings
//------------------------------------------------------------------------------------------------------------------------------------------------------
String daysOfTheWeek[7] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" }; //Dias de la Semana
String daysOfTheWeek_c[7] = { "Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab" };//dias de la semana comprimidos para mostrar en LCD
String monthsNames[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre" };//NOmbre de los meses
//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------
//                Declaración de Puertos
//------------------------------------------------------------
int buzer=3;  // buzer para alarma
int speakerPin;
int ledPin=13;
int btn1=12;  // Botón para fijar la hora
int btn2=11;  // Botón para fijar el día
int btn3=10;  // Botón para fijar alarma
int btn4=9;   // Botón para subir horas/minutos/segundos (+)
int btn5=8;   // Botón para bajar horas/minutos/segundos (-)
int btn6=7;   // Botón para setear los cambios
int DHT11=5;  // sensor de temperatura y Humedad
//-----------------------------------------------------------
//-----------------------------------------------------
//          variables para manejar la alarma
//-----------------------------------------------------
int hora;
int minutos;
int segundos;
int h;
int m;
int s;
//----------------------------------------------------
//-----------------------------------------
// Declaro el Objeto y lo creo 
// RTC_DS1307 rtc;el otro modelo que existe
RTC_DS3231 rtc; 
//----------------------------------------- 
//-----------------------------------------------------------
// declaro el objeto LCD y le paso la dirección en memoria
// y los caracteres y lineas a representar 
//-----------------------------------------------------------
LiquidCrystal_I2C lcd(0x3f,16,2); 
//-----------------------------------------------------------
//-----------------------------------------------------------
//declaor el objeto eeprom del RTC
//-----------------------------------------------------------
AT24C32 EepromRTC;
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
     //------------------------------------------
     //declaro los puerto comno salida de datos 
     //------------------------------------------
     pinMode(buzer,OUTPUT);
     pinMode(ledPin,OUTPUT); 
     //-------------------------------------------
    
     lcd.init();                //inicializo la pantalla LCD
     lcd.backlight();           //Prendo la luz de la pantalla LCD
     lcd.setCursor(0,0);        //posiciono el cursor en la posisión 0, renglón 0
     lcd.print("ServicePack");  //Imprimo información de la empresa
     lcd.setCursor(0,1);        //posiciono el cursor en la posisión 0, renglón 1
     lcd.print("2022");         //Imprimo 2022
     Serial.begin(9600);        //Inicializo la consola serial
     delay(1000); 
     //--------------------------------------------
     // detecto si el reloj de tiempo real 
     // esta conectado o no
     // y genero por pantalla informe
     //--------------------------------------------
     if(!rtc.begin()){
        Serial.println(F("RTC - Desconectado"));
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("RTC - Desconectado");
        while (1);
       }
     //------------------------------------------- 
     //------------------------------------------- 
     // leo los datos de la alarma cada vez que 
     // arranca el arduino, leo la memoria Eeprom
     // del RTC.   
     //------------------------------------------- 
     leer_alarma();   
     //-------------------------------------------   
     //-------------------------------------------------------------------------------------------------------------  
     // Si se ha perdido la corriente, fijar fecha y hora
     // con la hora en la que compilé el programa, 
     // ACA HA]Y que ACOMODAR PARA QUE EL USUARIO FIJE LA 
     // LA HORA EL 
     if(rtc.lostPower()){
       rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Fijar a fecha y hora de compilacion
       //rtc.adjust(DateTime(2020, 10, 26, 7, 26, 0));   //FIJO LA HORA CON VALORES A MI ELECCION
       //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //FIJO LA HORA CON LA HORA EN QUE EL SOFT SE COMPILO
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Fecha y Hora");
       lcd.setCursor(0,1);
       lcd.print("Desactualizada");
       // Fijar a fecha y hora específica.
       // En el ejemplo, 26 de Octubre de 2020 a las 07:26:00
       //rtc.adjust(DateTime(2020, 10, 26, 7, 26, 0)); 
      }
    //--------------------------------------------------------------------------------------------------------------  
    delay(3000);
    lcd.clear();   //limpio la pantalla
}
//---------------------------------------------------------
//    Imprime en la consola serial la fecha y hora
//---------------------------------------------------------
void printDate(DateTime date){
     Serial.print(date.year(), DEC);
     Serial.print('/');
     Serial.print(date.month(), DEC);
     Serial.print('/');
     Serial.print(date.day(), DEC);
     Serial.print(" (");
     Serial.print(daysOfTheWeek[date.dayOfTheWeek()]);
     Serial.print(") ");
     Serial.print(date.hour(), DEC);
     Serial.print(':');
     Serial.print(date.minute(), DEC);
     Serial.print(':');
     Serial.print(date.second(), DEC);
     Serial.println();
}
//---------------------------------------------------------
//            Imprime en la pantalla la hora.
//---------------------------------------------------------
void printDate_lcd(DateTime date){
     lcd.setCursor(0,0);
     lcd.print(date.year(), DEC);
     lcd.print('/');
     lcd.print(date.month(), DEC);
     lcd.print('/');
     lcd.print(date.day(), DEC);
     lcd.print(" (");
     lcd.print(daysOfTheWeek_c[date.dayOfTheWeek()]);
     lcd.print(") ");
     lcd.setCursor(0,1);
     lcd.print(date.hour(), DEC);
     lcd.print(':');
     lcd.print(date.minute(), DEC);
     lcd.print(':');
     lcd.print(date.second(), DEC);  
} 

//-----------------------------------------------------
//        FUNCION PARA HACER SONAR LA ALARMA 
//-----------------------------------------------------
void alarma(DateTime date){
     if(date.hour()==hora && date.minute()==minutos){
        Serial.println("ALARMA ACTIVADA");
        march();
    } 
}
//----------------------------------------------------

//----------------------------------------------------
//         Función para seatear la alarma 
//----------------------------------------------------
void setear_alarma(){
     h=0;
     m=0;
     s=0;  
     int bandera=1;
     int bandera1=0;
     lcd.setCursor(0,0);
     lcd.print("Ingrese Alarma");
     delay(1000); 
     lcd.setCursor(0,1);
     while(bandera1==0){
           //------------------------------------        
           // genero la hora a guardar en la 
           // alarma btn4 (+) sube el valor en 
           // 1, btn5 (-) baja el valor en uno
           // btn6 fija la hora en la alarma
           while(bandera==1){ 
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Ingrese la Hora");               
            lcd.setCursor(0,1);           
            if(digitalRead(btn4)==0){
              if(h<24){
                 h+=1;
                 lcd.print(h);
                 lcd.print(':');
                 lcd.print(m);
                 lcd.print(':'); 
                 lcd.print(s); 
                 Serial.println(h);   
                 delay(500);                                             
                }
             }                
            if(digitalRead(btn5)==0){
               if(h>=0){
                 h-=1;
                 lcd.print(h, DEC);
                 lcd.print(':');
                 lcd.print(m, DEC);
                 lcd.print(':'); 
                 lcd.print(s, DEC); 
                 Serial.println(h);   
                 delay(500);                            
                }
             }
           if(digitalRead(btn6)==0){
             bandera=2;
             hora=h;
             delay(500); 
             } 
            //lcd.setCursor(0,1);   
            //delay(500);             
            }
           //------------------------------------
           //------------------------------------        
           // genero los minutos a guardar en la 
           // alarma btn4 (+) sube el valor en 
           // 1, btn5 (-) baja el valor en uno
           // btn6 fija los minutos en la alarma          
          while(bandera==2){
           lcd.clear();             
           lcd.setCursor(0,0);
           lcd.print("Ingrese los Minutos");               
           lcd.setCursor(0,1);              
           lcd.setCursor(0,1);
           //delay(500);
           if(digitalRead(btn4)==0){
              if(m<60){
                 m+=1;
                 lcd.print(h, DEC);
                 lcd.print(":");
                 lcd.print(m, DEC);
                 lcd.print(":");  
                 lcd.print(s, DEC); 
                 delay(500);                                           
                }
           }
           if(digitalRead(btn5)==0){
              if(m>=0){
                 m-=1;
                 lcd.print(h, DEC);
                 lcd.print(":");
                 lcd.print(m, DEC);
                 lcd.print(":");  
                 lcd.print(s, DEC); 
                 delay(500);                    
                }
             }
           if(digitalRead(btn6)==0){
             bandera=3;
             minutos=m;
             delay(500); 
           } 
               
          }
           //------------------------------------   
          //-------------------------------------        
           // genero los segundos a guardar en la 
           // alarma btn4 (+) sube el valor en 
           // 1, btn5 (-) baja el valor en uno
           // btn6 fija los segundos en la alarma                  
          while(bandera==3){
           lcd.clear();            
           lcd.setCursor(0,0);
           lcd.print("Ingrese los Segundos");               
           lcd.setCursor(0,1);              
           //delay(500);
           if(digitalRead(btn4)==0){
              if(s<60){
                 s+=1;
                 lcd.print(h, DEC);
                 lcd.print(":");
                 lcd.print(m, DEC);
                 lcd.print(":");  
                 lcd.print(s, DEC);
                 delay(500);                                                     
                }
           }                
           if(digitalRead(btn5)==0){
              if(s>0){
                 s-=1;
                 lcd.print(h, DEC);
                 lcd.print(":");
                 lcd.print(m, DEC);
                 lcd.print(":");  
                 lcd.print(s, DEC); 
                 delay(500);   
                 Serial.println(h);                            
                }
             }
           if(digitalRead(btn6)==0){
              Serial.println("SALIR");             
              bandera1=1;
              bandera=4;
              segundos=s
              ;
              delay(500); 
            
            } 
               
          }    
          //--------------------------------------
        }
     escribir_alarma();
     return;
     
}
//-----------------------------------------------------

//-----------------------------------------------------
// función de prueba para controlar el funcionamiento 
// los puertos de entrada.
//-----------------------------------------------------
void status(){
     Serial.print(digitalRead(btn1));
     Serial.print(digitalRead(btn2));
     Serial.print(digitalRead(btn3));
     Serial.print(digitalRead(btn4));
     Serial.print(digitalRead(btn5));
     Serial.print(digitalRead(btn6));
     Serial.println();     
     return;
}
//------------------------------------------------------------------------------------
//        Función para generar sonido en un buzer  
//------------------------------------------------------------------------------------
void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds){ 
     digitalWrite(ledPin, HIGH); 
     //use led to visualize the notes being played
    
    int x; 
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++) 
      { 
        digitalWrite(speakerPin,HIGH);
        delayMicroseconds(delayAmount);
        digitalWrite(speakerPin,LOW);
        delayMicroseconds(delayAmount);
      }    
        digitalWrite(ledPin, LOW);
        //set led back to low
    
        delay(20);
        //a little delay to make all notes sound separate
} 
//------------------------------------------------------------------------------------
//-----------------------------------------------------
//        Función para tocar la marcha Imperial
//-----------------------------------------------------  	 
void march(){ 
    //for the sheet music see:
    //http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0016254
    //this is just a translation of said sheet music to frequencies / time in ms
    //used 500 ms for a quart note
    speakerPin=buzer;
    beep(speakerPin, a, 500); 
    beep(speakerPin, a, 500); 
    beep(speakerPin, a, 500); 
    beep(speakerPin, f, 350); 
    beep(speakerPin, cH, 150);
    
    beep(speakerPin, a, 500);
    beep(speakerPin, f, 350);
    beep(speakerPin, cH, 150);
    beep(speakerPin, a, 1000);
    //first bit
    
    beep(speakerPin, eH, 500);
    beep(speakerPin, eH, 500);
    beep(speakerPin, eH, 500); 
    beep(speakerPin, fH, 350); 
    beep(speakerPin, cH, 150);
    
    beep(speakerPin, gS, 500);
    beep(speakerPin, f, 350);
    beep(speakerPin, cH, 150);
    beep(speakerPin, a, 1000);
    //second bit...
    
    beep(speakerPin, aH, 500);
    beep(speakerPin, a, 350); 
    beep(speakerPin, a, 150);
    beep(speakerPin, aH, 500);
    beep(speakerPin, gSH, 250); 
    beep(speakerPin, gH, 250);
    
    beep(speakerPin, fSH, 125);
    beep(speakerPin, fH, 125); 
    beep(speakerPin, fSH, 250);
    delay(250);
    beep(speakerPin, aS, 250); 
    beep(speakerPin, dSH, 500); 
    beep(speakerPin, dH, 250); 
    beep(speakerPin, cSH, 250); 
    //start of the interesting bit
    
    beep(speakerPin, cH, 125); 
    beep(speakerPin, b, 125); 
    beep(speakerPin, cH, 250); 
    delay(250);
    beep(speakerPin, f, 125); 
    beep(speakerPin, gS, 500); 
    beep(speakerPin, f, 375); 
    beep(speakerPin, a, 125); 
    
    beep(speakerPin, cH, 500); 
    beep(speakerPin, a, 375); 
    beep(speakerPin, cH, 125); 
    beep(speakerPin, eH, 1000); 
    //more interesting stuff (this doesn't quite get it right somehow)
    
    beep(speakerPin, aH, 500);
    beep(speakerPin, a, 350); 
    beep(speakerPin, a, 150);
    beep(speakerPin, aH, 500);
    beep(speakerPin, gSH, 250); 
    beep(speakerPin, gH, 250);
    
    beep(speakerPin, fSH, 125);
    beep(speakerPin, fH, 125); 
    beep(speakerPin, fSH, 250);
    delay(250);
    beep(speakerPin, aS, 250); 
    beep(speakerPin, dSH, 500); 
    beep(speakerPin, dH, 250); 
    beep(speakerPin, cSH, 250); 
    //repeat... repeat
    
    beep(speakerPin, cH, 125); 
    beep(speakerPin, b, 125); 
    beep(speakerPin, cH, 250); 
    delay(250);
    beep(speakerPin, f, 250); 
    beep(speakerPin, gS, 500); 
    beep(speakerPin, f, 375); 
    beep(speakerPin, cH, 125); 
           
    beep(speakerPin, a, 500); 
    beep(speakerPin, f, 375); 
    beep(speakerPin, c, 125); 
    beep(speakerPin, a, 1000); 
    //and we're done \ó/ 
}
//-----------------------------------------------------
//       Función para leer los datos de la alarma
//       dentro de la memoria Eeprom del RTC
//-----------------------------------------------------
void leer_alarma(){
     hora=EepromRTC.readInt(2); //EepromRTC.readInt lle un valor entero
     minutos=EepromRTC.readInt(4); // de la dirección de memoria pasada como
     segundos=EepromRTC.readInt(6); // parámetro y se guarda el valor en una variable del mismo tipo
     Serial.println("LEER ALARMA EN Eeprom");  
     Serial.print("HORA:"); 
     Serial.print(hora);
     Serial.print(" Minutos:");
     Serial.print(minutos);
     Serial.print(" Segundos:");
     Serial.print(segundos);             
     return;
}
//-----------------------------------------------------
//-----------------------------------------------------
//       Función para escribir los datos la alarma
//       en la memoria Eeprom del RTC
//-----------------------------------------------------
void escribir_alarma(){
     //--------------------------------------
     //guardo los datos de la alarma 
     //en la memoria EEprom del RTC
     //--------------------------------------
     EepromRTC.writeInt(2,h); //cada valor int que gurdo ocupa 2 bytes
     EepromRTC.writeInt(4,m); //(2,4 y 6 son las direcciones en memoria)
     EepromRTC.writeInt(6,s); //  EepromRTC.writeInt graba un dato en posisión de memoria específico       
     //--------------------------------------    
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("ALARMA CARGADA");
     lcd.setCursor(0,1);
     lcd.print(h);
     lcd.print(":");
     lcd.print(m);
     lcd.print(":");   
     lcd.print(s);    
     Serial.print("ALARMA CARGADA");
     Serial.print("   ");
     Serial.print(h);
     Serial.print(":");
     Serial.print(m);
     Serial.print(":");
     Serial.println(s);
     delay(2000);
     hora=h;
     minutos=m;
     segundos=s;
     return;
}
//-----------------------------------------------------

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
void loop() { 
    
     //------------------------------------------------------------------    
     DateTime now = rtc.now(); // Obtener fecha actual y hora actual desde el RTC
     printDate(now);           // imprimir consola serial la hora y fecha
     lcd.backlight();          // enciende la luz de fondo de la pantalla 
     printDate_lcd(now);       // imprimir en pantalla LCD la hora y fecha
     //------------------------------------------------------------------
     //controlo si alguien presionó el Switch de configurar alarma, 
     //si lo hizo  llamo a setear alarma
     if(digitalRead(btn3)==0){
       setear_alarma(); // llamada a función para setear la alarma
     }
    //------------------------------------------------------------------
    //  Lamada a la función Alarma para ver si tiene que sonar o no 
    //------------------------------------------------------------------
    alarma(now); //lamada a la función alarma
    //------------------------------------------------------------------
    
    delay(1000);
}


