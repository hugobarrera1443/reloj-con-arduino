/************************************************************************************************************************
 * LaBuhardilladelLoco 2021
 * 
 * Este es un ejemplo de uso de la libreria LiquidMenu en la que crearemos multiples lineas
 * 
 * Recordad modificar el archivo: C:\Users\usuario\Documents\Arduino\libraries\LiquidMenu-master\src\LiquidMenu_config.h
 * en caso de que useis mas lineas mas pantallas o mas menus en vuetro proyecto.
 * 
 * 
 ************************************************************************************************************************/


#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2);

//ENCODER
#define outputA 6
#define outputB 7
#define sw 4

int aState;
int aLastState;  

int incremento=0;

LiquidLine linea1(1, 0, "lin1");
LiquidLine linea2(1, 1, "lin2");
LiquidLine linea3(1, 0, "lin3");
LiquidLine linea4(1, 1, "lin4");
LiquidLine linea5(1, 0, "lin5");
LiquidLine linea6(1, 1, "lin6");
LiquidLine linea7(1, 0, "lin7");
LiquidLine linea8(1, 1, "lin8");
LiquidLine linea9(1, 0, "lin9");
LiquidLine linea10(1, 1, "lin10");
LiquidLine linea11(1, 0, "lin11");
LiquidLine linea12(1, 1, "lin12");
LiquidLine linea13(1, 0, "lin13");
LiquidLine linea14(1, 1, "lin14");
LiquidLine linea15(1, 0, "lin15");


LiquidScreen pantalla1;
LiquidMenu menu(lcd);


void setup() {

  pinMode(sw,INPUT_PULLUP);
  lcd.init();
  //lcd.begin();
  lcd.backlight();
  
  pantalla1.add_line(linea1);
  pantalla1.add_line(linea2);
  pantalla1.add_line(linea3);
  pantalla1.add_line(linea4);
  pantalla1.add_line(linea5);
  pantalla1.add_line(linea6);
  pantalla1.add_line(linea7);
  pantalla1.add_line(linea8);
  pantalla1.add_line(linea9);
  pantalla1.add_line(linea10);
  pantalla1.add_line(linea11);
  pantalla1.add_line(linea12);
  pantalla1.add_line(linea13);
  pantalla1.add_line(linea14);
  pantalla1.add_line(linea15);

  linea1.set_focusPosition(Position::LEFT); 
  linea2.set_focusPosition(Position::LEFT); 
  linea3.set_focusPosition(Position::LEFT); 
  linea4.set_focusPosition(Position::LEFT); 
  linea5.set_focusPosition(Position::LEFT); 
  linea6.set_focusPosition(Position::LEFT); 
  linea7.set_focusPosition(Position::LEFT); 
  linea8.set_focusPosition(Position::LEFT); 
  linea9.set_focusPosition(Position::LEFT); 
  linea10.set_focusPosition(Position::LEFT); 
  linea11.set_focusPosition(Position::LEFT); 
  linea12.set_focusPosition(Position::LEFT); 
  linea13.set_focusPosition(Position::LEFT); 
  linea14.set_focusPosition(Position::LEFT); 
  linea15.set_focusPosition(Position::LEFT); 

  linea1.attach_function(1, fn_vacio); 
  linea2.attach_function(1, fn_vacio);
  linea3.attach_function(1, fn_vacio);
  linea4.attach_function(1, fn_vacio);
  linea4.attach_function(1, fn_vacio);
  linea5.attach_function(1, fn_vacio);
  linea6.attach_function(1, fn_vacio);
  linea7.attach_function(1, fn_vacio);
  linea8.attach_function(1, fn_vacio);
  linea9.attach_function(1, fn_vacio);
  linea10.attach_function(1,fn_vacio);
  linea11.attach_function(1,fn_vacio);
  linea12.attach_function(1,fn_vacio);
  linea13.attach_function(1,fn_vacio);
  linea14.attach_function(1,fn_vacio);
  linea15.attach_function(1,fn_vacio);


  
  menu.add_screen(pantalla1);
  pantalla1.set_displayLineCount(2);

  menu.init();
  menu.set_focusedLine(0);
  menu.update();
}

void loop() {

  selectOption();
 
  aState = digitalRead(outputA); 
  if (aState != aLastState){ 
  
    if (digitalRead(outputB) != aState) { 
      
      incremento++;
      if(incremento>1){
        incremento = 0;
        menu.switch_focus(false);
      }
  
    } else {
      
      incremento++;
      if(incremento>1){
        incremento = 0;
        menu.switch_focus(true);
      }
      
    }
      menu.update();
      aLastState = aState;
  }

}



//Funciones:::::
void selectOption(){
  if(digitalRead(sw) == LOW){
      menu.call_function(1);
      delay(500);
  }
}



void fn_vacio(){ 
  
}
