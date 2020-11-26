#include <Keypad.h>
#include <Keyboard.h>

#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const byte ROWS = 10; //four rows
const byte COLS = 5; //three columns

char keys[ROWS][COLS] = {
{10,':',';','p',8},
{6,'.','l','o',99},
{11,12,'k','i',14},
{16,'m','j','u',19},
{' ','n','h','y',24},
{' ','b','g','t',29},
{31,'v','f','r',35},
{36,37,'d','e',27},
{33,'x','s','w',44},
{46,'z','a','q',49}
};

byte rowPins[ROWS] = {A3, A2, A0, A1, 14, 8, 6, 4, 7, 5}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {9, 1, 10, 16, 15}; //connect to the column pinouts of the kaaq
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;


void setup() {
    Serial.begin(9600);
    loopCount = 0;
    startTime = millis();
    msg = "";

    Keyboard.begin();

    u8g.setColorIndex(3);
    u8g.setFont(u8g_font_unifont);    
    pinMode(8, OUTPUT);
    u8g.firstPage();  
    do {
      u8g.drawStr( 0, 22, "Teclado do Caos");
    } while( u8g.nextPage() );
}


void loop() {
    loopCount++;
    if ( (millis()-startTime)>5000 ) {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount/5);
        startTime = millis();
        loopCount = 0;
    }

    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
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
                    Keyboard.press(0x85);
                    u8g.firstPage(); 
                    do {
                      u8g.drawStr( 0, 22, "Teclado do Caos");
                      u8g.drawStr( 0, 33, "SHIFT");
                    } while( u8g.nextPage() );
                  }
                  else if(kpd.key[i].kchar == 33){
                    Keyboard.press(0x86);
                    u8g.firstPage(); 
                    do {
                      u8g.drawStr( 0, 22, "Teclado do Caos");
                      u8g.drawStr( 0, 33, "ALT");
                    } while( u8g.nextPage() );
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
                  else if(kpd.key[i].kchar == 46){
                    Keyboard.press(0x84); 
                    u8g.firstPage(); 
                    do {
                      u8g.drawStr( 0, 22, "Teclado do Caos");
                      u8g.drawStr( 0, 33, "CTRL");
                    } while( u8g.nextPage() );  
                  }
                  else{
                     Keyboard.press(kpd.key[i].kchar);
                  }  
                }
                else if(msg == " PRESSED."){
                  if(kpd.key[i].kchar == 27){
                    Keyboard.write(0x86);
                  }
                   else if(kpd.key[i].kchar == 33){
                    Keyboard.press(0x86);
                    u8g.firstPage(); 
                    do {
                      u8g.drawStr( 0, 22, "Teclado do Caos");
                      u8g.drawStr( 0, 33, "ALT");
                    } while( u8g.nextPage() );
                  }
                  else if(kpd.key[i].kchar == 46){
                    Keyboard.press(0x84); 
                    u8g.firstPage(); 
                    do {
                      u8g.drawStr( 0, 22, "Teclado do Caos");
                      u8g.drawStr( 0, 33, "CTRL");
                    } while( u8g.nextPage() );  
                  }
                  else if(kpd.key[i].kchar == 16){
                    Keyboard.press(0xD8);
                  }
                  else if(kpd.key[i].kchar == 35){
                    Keyboard.press(0xB3);
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
                    Keyboard.write('c');
                  }
                  else if(kpd.key[i].kchar == 31){
                    Keyboard.press(0x85);
                    u8g.firstPage(); 
                    do {
                      u8g.drawStr( 0, 22, "Teclado do Caos");
                      u8g.drawStr( 0, 33, "SHIFT");
                    } while( u8g.nextPage() ); 
                  }                   
                  else{
                    Keyboard.press(kpd.key[i].kchar);
                  }                  
                }
                
                else if(msg == " RELEASED." || msg == " IDLE."){
                  if(kpd.key[i].kchar == 46){
                    Keyboard.release(0x84);
                    u8g.firstPage();  
                    do {
                      u8g.drawStr( 0, 22, "Teclado do Caos");
                    } while( u8g.nextPage() );
                  }
                  else if(kpd.key[i].kchar == 33){
                    Keyboard.release(0x86);
                    u8g.firstPage();  
                    do {
                      u8g.drawStr( 0, 22, "Teclado do Caos");
                    } while( u8g.nextPage() ); 
                  }
                  else if(kpd.key[i].kchar == 31){
                    Keyboard.release(0x85);
                    u8g.firstPage();  
                    do {
                      u8g.drawStr( 0, 22, "Teclado do Caos");
                    } while( u8g.nextPage() );
                  }
                  else if(kpd.key[i].kchar == 16){
                    Keyboard.release(0xD8);
                  }
                  else if(kpd.key[i].kchar == 35){
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
