#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
// RTC_DS1307 rtc;
RTC_DS3231 rtc;
 
String daysOfTheWeek[7] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
String daysOfTheWeek_c[7] = { "Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab" };//dias de la semana comprimidos para mostrar en LCD
String monthsNames[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre" };
//------------------------------------------------------------
//Declaración de Puertos
//------------------------------------------------------------
int buzer=3;  // buzer para alarma
int btn1=12;  // Botón para fijar la hora
int btn2=11;  // Botón para fijar el día
int btn3=10;  // Botón para fijar alarma
int btn4=9;   // Botón para subir horas/minutos/segundos (+)
int btn5=8;   // Botón para bajar horas/minutos/segundos (-)
int btn6=7;   // Botón para setear los cambios
int DHT11=5;  // sensor de temperatura y Humedad
//-----------------------------------------------------------

LiquidCrystal_I2C lcd(0x3f,16,2); // declaro el objeto LCD y le paso la dirección en memoria y los caracteres y lineas a representar 
void setup() {
     pinMode(btn1,INPUT);
     pinMode(btn2,INPUT);
     pinMode(btn3,INPUT);
     pinMode(btn4,INPUT);
     pinMode(btn5,INPUT);
     pinMode(btn6,INPUT);
     pinMode(buzer,OUTPUT);
     // inicializo la pantalla LCD
     lcd.init();
     // Prendo la luz de la pantalla LCD
     lcd.backlight();
     lcd.setCursor(0,0);
     //información de la empresa
     lcd.print("ServicePack");
     lcd.setCursor(0,1);
     lcd.print("Volvimos en 2021");
     Serial.begin(9600);
     delay(1000); 
     if(!rtc.begin()){
        Serial.println(F("RTC - Desconectado"));
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("RTC - Desconectado");
        while (1);
       }
     // Si se ha perdido la corriente, fijar fecha y hora
     if(rtc.lostPower()){
       // Fijar a fecha y hora de compilacion
       rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Fecha y Hora");
       lcd.setCursor(0,1);
       lcd.print("Desactualizada");
       // Fijar a fecha y hora específica. En el ejemplo, 21 de Enero de 2016 a las 03:00:00
       //rtc.adjust(DateTime(2020, 10, 26, 7, 26, 0)); 
      }
    delay(3000);
    lcd.clear(); 
    //rtc.adjust(DateTime(2020, 10, 26, 7, 26, 0));   //FIJO LA HORA CON VALORES A MI ELECCION
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //FIJO LA HORA CON LA HORA EN QUE EL SOFT SE COMPILO
}
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
// variables para manejar la alarma
//-----------------------------------------------------
int hora=19;
int minutos=44;
int segundos=0;
int h;
int m;
int s;
//-----------------------------------------------------

void alarma(DateTime date){
   if(date.hour()==hora && date.minute()==minutos){
     Serial.println("ALARMA ACTIVADA");
     tone(buzer, 250,2000);
     tone(buzer, 500,2000);
    } 
  }
  
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
     //--------------------------------------
     //generar la rutina que guarde la alarma 
     //en memoria
     //--------------------------------------             
     return;
     
}

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
void loop() {
     // Obtener fecha actual y mostrar por Serial
     DateTime now = rtc.now();
     printDate(now);//imprimir consola serial la hora y fecha
     lcd.backlight();
     printDate_lcd(now);//imprimir en pantalla LCD la hora y fecha
     //------------------------------------------------------------------
     //controlo si alguien presionó el Switch de configurar alarma, 
     //si lo hizo  llamo a setear alarma
     if(digitalRead(btn3)==0){
       setear_alarma();
     }
     //------------------------------------------------------------------
    alarma(now); //lamada a la función alarma
    delay(1000);
}


