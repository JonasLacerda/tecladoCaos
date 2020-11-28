#include <Keypad.h>
#include <Keyboard.h>

#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const byte ROWS = 10; //four rows
const byte COLS = 5; //three columns

bool num;
bool teclado;
bool shift;
bool ctrl;
bool alt;
bool sibol;

char keys[ROWS][COLS] = {
{10,2,';','p',8},
{6,7,'l','o',99},
{11,12,'k','i',14},
{16,'m','j','u',19},
{' ','n','h','y',24},
{' ','b','g','t',29},
{31,'v','f','r',3}, 
{1,37,'d','e',40},
{33,'x','s','w',44},
{46,'z','a','q',49}
};

byte rowPins[ROWS] = {A3, A2, A0, A1, 14, 8, 6, 4, 7, 5}; 
byte colPins[COLS] = {9, 1, 10, 16, 15}; 
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;

//tela neutra
void tela(){
 int y = 35;
  u8g.firstPage();  
  do {
    u8g.drawStr( 0, 22, "Teclado do Caos");
    //verifica se esta no teclado numero
    if(num == 1){
      u8g.drawStr( 50, y, "NUM");
    }else{
      u8g.drawStr( 50, y, "   ");
    }
    //verifica se esta precionado alguma tecla de acao
    if(shift == 1){
      u8g.drawStr( 0, y, "SHIFT");
    }
    else if(ctrl == 1){
      u8g.drawStr( 0, y, "CTRL");
    }
    else if(alt == 1){
      u8g.drawStr( 0, y, "ALT");
    }    
    else{
      u8g.drawStr( 0, y, "   ");
    }
  } while( u8g.nextPage() );
}



void setup() {
    Serial.begin(9600);
    loopCount = 0;
    startTime = millis();
    msg = "";

    Keyboard.begin();
    Keyboard.releaseAll();
    u8g.setColorIndex(3);
    u8g.setFont(u8g_font_unifont);    
    pinMode(8, OUTPUT);
    tela();
}


void loop() {
    loopCount++;
    if ( (millis()-startTime)>5000 ) {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount/5);
        startTime = millis();
        loopCount = 0;
    }
    
    if (kpd.getKeys())
    {
      for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.      
        {          
          if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";
                break;
                    case HOLD:
                    msg = " HOLD.";                    
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                Serial.print("Key ");
                Serial.print(kpd.key[i].kchar);                
                Serial.println(msg);
                if(msg == " HOLD."){
                  if(kpd.key[i].kchar == 31){
                    Keyboard.press(0x81);
                    shift = 1;
                    tela();
                  }
                  else if(kpd.key[i].kchar == 33){
                    Keyboard.press(0x82);
                    alt = 1;
                    tela();
                  }
                  else if(kpd.key[i].kchar == 16){
                    Keyboard.press(0xD8);
                  }
                  else if(kpd.key[i].kchar == 3){
                    tela();
                    num = !num;
                  }
                  else if(kpd.key[i].kchar == 12){
                    Keyboard.press(0xDA);
                  }
                  else if(kpd.key[i].kchar == 11){
                    Keyboard.press(0xD9);
                  }
                  else if(kpd.key[i].kchar == 6){
                    Keyboard.press(0xD7);
                  }
                  else if(kpd.key[i].kchar == 46){
                    Keyboard.press(0x80); 
                    ctrl = 1;
                    tela();  
                  }
                  else{
                     Keyboard.press(kpd.key[i].kchar);
                  }  
                }
                else if(msg == " PRESSED."){
                  
                  if(kpd.key[i].kchar == "40"){
                    Keyboard.write(0x86);
                  }
                  else if(kpd.key[i].kchar == 2){
                    Keyboard.press('.');
                  }   
                  else if(kpd.key[i].kchar == 1){
                    Keyboard.press(0xB3);
                  }                
                  else if(kpd.key[i].kchar == 3){                    
                    num = !num;
                    tela();
                  }
                  else if(kpd.key[i].kchar == 7){
                    Keyboard.press(',');
                  }
                   else if(kpd.key[i].kchar == 33){
                    Keyboard.press(0x82);
                    alt = 1;
                    tela();
                  }
                  else if(kpd.key[i].kchar == 46){
                    Keyboard.press(0x80); 
                    ctrl = 1;
                    tela();  
                  }
                  else if(kpd.key[i].kchar == 16){
                    Keyboard.press(0xD8);
                  }
                  else if(kpd.key[i].kchar == 12){
                    Keyboard.press(0xDA);
                  }
                  else if(kpd.key[i].kchar == 11){
                    Keyboard.press(0xD9);
                  }
                  else if(kpd.key[i].kchar == 6){
                    Keyboard.press(0xD7);
                  }
                  else if(kpd.key[i].kchar == 49){
                    Keyboard.write(0xB1);
                  }
                  else if(kpd.key[i].kchar == 37){
                    if(num == 1){
                      Keyboard.write('7');
                    }else{
                      Keyboard.write('c');
                    }                    
                  }
                  else if(kpd.key[i].kchar == 31){
                    Keyboard.press(0x81);
                    shift = 1;
                    tela(); 
                  }                                                                                 
                  else{
                    if(num == 1){
                      if(kpd.key[i].kchar == 'e'){
                         Keyboard.write('1');
                      }
                      else if(kpd.key[i].kchar == 'r'){
                         Keyboard.write('2');
                      }
                      else if(kpd.key[i].kchar == 't'){
                         Keyboard.write('3');
                      }
                      else if(kpd.key[i].kchar == 'd'){
                         Keyboard.write('4');
                      }
                      else if(kpd.key[i].kchar == 'f'){
                         Keyboard.write('5');
                      }
                      else if(kpd.key[i].kchar == 'g'){
                         Keyboard.write('6');
                      }
                      else if(kpd.key[i].kchar == 'v'){
                         Keyboard.write('8');
                      }
                      else if(kpd.key[i].kchar == 'b'){
                         Keyboard.write('9');
                      }
                      else if(kpd.key[i].kchar == 'w'){
                         Keyboard.write('0');
                      }
                      else if(kpd.key[i].kchar == 'y'){
                         Keyboard.write('=');
                      }
                      else if(kpd.key[i].kchar == 'h'){
                         Keyboard.write('-');
                      }
                      else if(kpd.key[i].kchar == 'u'){
                         Keyboard.write('*');
                      }
                      else if(kpd.key[i].kchar == 'j'){
                         Keyboard.write('/');
                      }
                      else{
                        Keyboard.press(kpd.key[i].kchar);       
                      }
                    }else{
                      Keyboard.press(kpd.key[i].kchar);
                    }                    
                  }                  
                }
                
                else if(msg == " RELEASED." || msg == " IDLE."){
                  if(kpd.key[i].kchar == 46){
                    Keyboard.release(0x80);
                    ctrl = 0;
                    tela();
                  }
                   else if(kpd.key[i].kchar == 3){
                    
                  }                   
                  else if(kpd.key[i].kchar == "40"){
                    Keyboard.release(0x86);
                  }
                   else if(kpd.key[i].kchar == 2){
                    Keyboard.release('.');
                  }
                  else if(kpd.key[i].kchar == 7){
                    Keyboard.release(','); 
                  }
                  else if(kpd.key[i].kchar == 33){
                    Keyboard.release(0x82);
                    alt = 0;
                    tela();
                  }
                  else if(kpd.key[i].kchar == 31){
                    Keyboard.release(0x81);
                    shift = 0;
                    tela();
                  }
                  else if(kpd.key[i].kchar == 16){
                    Keyboard.release(0xD8);
                  }
                  else if(kpd.key[i].kchar == 1 ){
                    Keyboard.release(0xB3);
                  }
                  else if(kpd.key[i].kchar == 12){
                    Keyboard.release(0xDA);
                  }
                  else if(kpd.key[i].kchar == 11){
                    Keyboard.release(0xD9);
                  }
                  else if(kpd.key[i].kchar == 6){
                    Keyboard.release(0xD7);
                  }                  
                  else{
                    Keyboard.release(kpd.key[i].kchar);
                  }
                  
                }
            }
        }
    }    
}
