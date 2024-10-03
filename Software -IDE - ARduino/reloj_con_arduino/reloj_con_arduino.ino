#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
// RTC_DS1307 rtc;
RTC_DS3231 rtc;
 
String daysOfTheWeek[7] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
String daysOfTheWeek_c[7] = { "Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab" };//dias de la semana comprimidos para mostrar en LCD
String monthsNames[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre" };
int buzer=3;
LiquidCrystal_I2C lcd(0x3f,16,2); 
void setup() {
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
int hora=19;
int minutos=44;
void alarma(DateTime date){
   if(date.hour()==hora && date.minute()==minutos){
     Serial.println("ALARMA ACTIVADA");
     tone(buzer, 250,2000);
     tone(buzer, 500,2000);
    } 
  }
void loop() {
     // Obtener fecha actual y mostrar por Serial
     DateTime now = rtc.now();
     printDate(now);
     lcd.backlight();
     printDate_lcd(now);
     alarma(now);
     delay(1000);
}
