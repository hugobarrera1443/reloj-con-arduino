/**************************************************************************************************************************
 * LaBuhardilladelLoco 2021
 * 
 * Este es un scketch de prueba para ver la funcionalidad de la librería. 
 * 
 * 
 *  ¡Atención si vuestro scketch consume demasiada memoria, la placa Arduino UNO podria estar limitada para proyectos mas grandes! 
 * 
 * Recordad modificar el archivo: C:\Users\usuario\Documents\Arduino\libraries\LiquidMenu-master\src\LiquidMenu_config.h
 * en caso de que useis mas lineas mas pantallas o mas menus en vuestro proyecto.
 * 
 *************************************************************************************************************************/


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


//lineas pantalla 0
LiquidLine linea1_pant0(1, 0, "Pant1");
LiquidLine linea2_pant0(1, 1, "Pant2");
LiquidLine linea3_pant0(1, 0, "Pant3");
LiquidLine linea4_pant0(1, 1, "Pant4");
LiquidLine linea5_pant0(1, 0, "Pant5");

//lineas pantalla 1
LiquidLine linea1_pant1(1, 0, "Pant1 lin1");
LiquidLine linea2_pant1(1, 1, "Pant1 lin2");
LiquidLine linea3_pant1(1, 0, "Pant1 lin3");
LiquidLine linea4_pant1(1, 1, "Pant1 lin4");
LiquidLine linea5_pant1(1, 0, "< atras");

//lineas pantalla 2
LiquidLine linea1_pant2(1, 1, "Pant2 lin1");
LiquidLine linea2_pant2(1, 0, "Pant2 lin2");
LiquidLine linea3_pant2(1, 1, "Pant2 lin3");
LiquidLine linea4_pant2(1, 0, "Pant2 lin4");
LiquidLine linea5_pant2(1, 1, "< atras");

//lineas pantalla 3
LiquidLine linea1_pant3(1, 0, "Pant3 lin1");
LiquidLine linea2_pant3(1, 1, "Pant3 lin2");
LiquidLine linea3_pant3(1, 0, "Pant3 lin3");
LiquidLine linea4_pant3(1, 1, "Pant3 lin4");
LiquidLine linea5_pant3(1, 0, "< atras");

//lineas pantalla 4
LiquidLine linea1_pant4(1, 0, "Pant4 lin1");
LiquidLine linea2_pant4(1, 1, "Pant4 lin2");
LiquidLine linea3_pant4(1, 0, "Pant4 lin3");
LiquidLine linea4_pant4(1, 1, "Pant4 lin4");
LiquidLine linea5_pant4(1, 0, "< atras");

//lineas pantalla 5
LiquidLine linea1_pant5(1, 0, "Pant5 lin1");
LiquidLine linea2_pant5(1, 1, "Pant5 lin2");
LiquidLine linea3_pant5(1, 0, "Pant5 lin3");
LiquidLine linea4_pant5(1, 1, "Pant5 lin4");
LiquidLine linea5_pant5(1, 0, "< atras");


//declaracion de pantallas
LiquidScreen pantalla0;
LiquidScreen pantalla1;
LiquidScreen pantalla2;
LiquidScreen pantalla3;
LiquidScreen pantalla4;
LiquidScreen pantalla5;

LiquidMenu menu(lcd);


void setup() {

  pinMode(sw,INPUT_PULLUP);
  lcd.init();
  //lcd.begin();
  lcd.backlight();

//añadir lineas a pantalla 0
  pantalla0.add_line(linea1_pant0);
  pantalla0.add_line(linea2_pant0);
  pantalla0.add_line(linea3_pant0);
  pantalla0.add_line(linea4_pant0);
  pantalla0.add_line(linea5_pant0);

//añadir lineas a pantalla 1
  pantalla1.add_line(linea1_pant1);
  pantalla1.add_line(linea2_pant1);
  pantalla1.add_line(linea3_pant1);
  pantalla1.add_line(linea4_pant1);
  pantalla1.add_line(linea5_pant1);

//añadir lineas a pantalla 2
  pantalla2.add_line(linea1_pant2);
  pantalla2.add_line(linea2_pant2);
  pantalla2.add_line(linea3_pant2);
  pantalla2.add_line(linea4_pant2);
  pantalla2.add_line(linea5_pant2);

//añadir lineas a pantalla 3
  pantalla3.add_line(linea1_pant3);
  pantalla3.add_line(linea2_pant3);
  pantalla3.add_line(linea3_pant3);
  pantalla3.add_line(linea4_pant3);
  pantalla3.add_line(linea5_pant3);

//añadir lineas a pantalla 4
  pantalla4.add_line(linea1_pant4);
  pantalla4.add_line(linea2_pant4);
  pantalla4.add_line(linea3_pant4);
  pantalla4.add_line(linea4_pant4);
  pantalla4.add_line(linea5_pant4);  

//añadir lineas a pantalla 5
  pantalla5.add_line(linea1_pant5);
  pantalla5.add_line(linea2_pant5);
  pantalla5.add_line(linea3_pant5);
  pantalla5.add_line(linea4_pant5);
  pantalla5.add_line(linea5_pant5);

  
  //definir posicion del selector lineas de patalla 0
  linea1_pant0.set_focusPosition(Position::LEFT); 
  linea2_pant0.set_focusPosition(Position::LEFT); 
  linea3_pant0.set_focusPosition(Position::LEFT); 
  linea4_pant0.set_focusPosition(Position::LEFT); 
  linea5_pant0.set_focusPosition(Position::LEFT); 

  //definir posicion del selector lineas de patalla 1
  linea1_pant1.set_focusPosition(Position::LEFT); 
  linea2_pant1.set_focusPosition(Position::LEFT); 
  linea3_pant1.set_focusPosition(Position::LEFT); 
  linea4_pant1.set_focusPosition(Position::LEFT); 
  linea5_pant1.set_focusPosition(Position::LEFT); 

  //definir posicion del selector lineas de patalla 2
  linea1_pant2.set_focusPosition(Position::LEFT); 
  linea2_pant2.set_focusPosition(Position::LEFT); 
  linea3_pant2.set_focusPosition(Position::LEFT); 
  linea4_pant2.set_focusPosition(Position::LEFT); 
  linea5_pant2.set_focusPosition(Position::LEFT); 

  //definir posicion del selector lineas de patalla 3
  linea1_pant3.set_focusPosition(Position::LEFT); 
  linea2_pant3.set_focusPosition(Position::LEFT); 
  linea3_pant3.set_focusPosition(Position::LEFT); 
  linea4_pant3.set_focusPosition(Position::LEFT); 
  linea5_pant3.set_focusPosition(Position::LEFT);

  //definir posicion del selector lineas de patalla 4
  linea1_pant4.set_focusPosition(Position::LEFT); 
  linea2_pant4.set_focusPosition(Position::LEFT); 
  linea3_pant4.set_focusPosition(Position::LEFT); 
  linea4_pant4.set_focusPosition(Position::LEFT); 
  linea5_pant4.set_focusPosition(Position::LEFT);

  //definir posicion del selector lineas de patalla 5
  linea1_pant5.set_focusPosition(Position::LEFT); 
  linea2_pant5.set_focusPosition(Position::LEFT); 
  linea3_pant5.set_focusPosition(Position::LEFT); 
  linea4_pant5.set_focusPosition(Position::LEFT); 
  linea5_pant5.set_focusPosition(Position::LEFT);  


 
  linea1_pant0.attach_function(1, fn_ir_a_pantalla1); 
  linea2_pant0.attach_function(1, fn_ir_a_pantalla2); 
  linea3_pant0.attach_function(1, fn_ir_a_pantalla3); 
  linea4_pant0.attach_function(1, fn_ir_a_pantalla4); 
  linea5_pant0.attach_function(1, fn_ir_a_pantalla5); 

  linea1_pant1.attach_function(1, fn_vacio); 
  linea2_pant1.attach_function(1, fn_vacio); 
  linea3_pant1.attach_function(1, fn_vacio); 
  linea4_pant1.attach_function(1, fn_vacio); 
  linea5_pant1.attach_function(1, fn_atras);

  linea1_pant2.attach_function(1, fn_vacio); 
  linea2_pant2.attach_function(1, fn_vacio); 
  linea3_pant2.attach_function(1, fn_vacio); 
  linea4_pant2.attach_function(1, fn_vacio); 
  linea5_pant2.attach_function(1, fn_atras);

  linea1_pant3.attach_function(1, fn_vacio); 
  linea2_pant3.attach_function(1, fn_vacio); 
  linea3_pant3.attach_function(1, fn_vacio); 
  linea4_pant3.attach_function(1, fn_vacio); 
  linea5_pant3.attach_function(1, fn_atras);
  
  linea1_pant4.attach_function(1, fn_vacio); 
  linea2_pant4.attach_function(1, fn_vacio); 
  linea3_pant4.attach_function(1, fn_vacio); 
  linea4_pant4.attach_function(1, fn_vacio); 
  linea5_pant4.attach_function(1, fn_atras);

  linea1_pant5.attach_function(1, fn_vacio); 
  linea2_pant5.attach_function(1, fn_vacio); 
  linea3_pant5.attach_function(1, fn_vacio); 
  linea4_pant5.attach_function(1, fn_vacio); 
  linea5_pant5.attach_function(1, fn_atras);


  menu.add_screen(pantalla0);
  menu.add_screen(pantalla1);
  menu.add_screen(pantalla2);
  menu.add_screen(pantalla3);
  menu.add_screen(pantalla4);
  menu.add_screen(pantalla5);
  
  pantalla0.set_displayLineCount(2);
  pantalla1.set_displayLineCount(2);
  pantalla2.set_displayLineCount(2);
  pantalla3.set_displayLineCount(2);
  pantalla4.set_displayLineCount(2);
  pantalla5.set_displayLineCount(2);
  
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
      if(incremento>0){
        incremento = 0;
        menu.switch_focus(false);
      }
  
    } else {
      
      incremento++;
      if(incremento>0){
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




void fn_ir_a_pantalla1(){
    
  menu.change_screen(2);
  menu.set_focusedLine(0);
}

void fn_ir_a_pantalla2(){
   
  menu.change_screen(3);
   menu.set_focusedLine(0);
}

void fn_ir_a_pantalla3(){
   
  menu.change_screen(4);
   menu.set_focusedLine(0);
}

void fn_ir_a_pantalla4(){
   
  menu.change_screen(5);
   menu.set_focusedLine(0);
}

void fn_ir_a_pantalla5(){
   
  menu.change_screen(6);
   menu.set_focusedLine(0);
}


void fn_atras(){
  
  menu.change_screen(1);
    menu.set_focusedLine(0);
}

void fn_vacio(){ 
  
}
