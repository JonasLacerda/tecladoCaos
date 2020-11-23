#include <Keypad.h>
#include <Keyboard.h>

const byte ROWS = 10; //four rows
const byte COLS = 5; //three columns

char keys[ROWS][COLS] = {
{10,':',';','p',8},
{6,'.','l','o',0},
{10,',','k','i',14},
{15,'m','j','u',19},
{32,'n','h','y',24},
{32,'b','g','t',29},
{33,'v','f','r',34},
{35,'c','d','e',27},
{40,'x','s','w',44},
{32,'z','a','q',49}
};

byte rowPins[ROWS] = {A3, A2, A0, A1, 14, 8, 6, 4, 7, 5}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {9, 1, 10, 16, 15}; //connect to the column pinouts of the kpd

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
                  Keyboard.press(kpd.key[i].kchar);
                }
                else if(msg == " PRESSED."){
                  Keyboard.press(kpd.key[i].kchar);
                }
                else if(msg == " RELEASED."){
                  Keyboard.release(kpd.key[i].kchar);
                }
            }
        }
    }
}  // End loop  que merda e essa 
