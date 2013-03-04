
/* by Robert Werner
 floatingbob@icloud.com
 This sketch allows you to drive a strand of LEDs with a TM1809 chip. These
 LEDs currently drive from one pin, into LEDs that are hooked up in series. 
 Four strands blink at random speeds.
 */
 
 
 /*
 1. create functions and variables for multiple strands and LEDs
 2. randomize the velocity for each strand
 3. add sensor trigger
 4. delay the effect after it's been triggered 
 */
 
//--------------Maxbotix EZ1 Sensor Global Variables-----------------//
const int sensorPin = 5;
long value = 0;
int cm = 0;
int inches = 0;
//------------------------------------------------------------------//

#include <FastSPI_LED.h>
#define NUM_LEDS 74
struct CRGB { 
  unsigned char b; 
  unsigned char r; 
  unsigned char g; 
};
struct CRGB *leds;
int aPin = 4;

//----Millis Clock Global Variables------------------------------//
unsigned long currentMillis = 0;
unsigned long currentMillis2 = 0;
unsigned long currentMillis3 = 0;
unsigned long currentMillis4 = 0;
unsigned long stepTime1 = 0; // last time the light stepped
unsigned long stepTime2 = 0; //last time strand 2 light stepped
unsigned long stepTime3 = 0;
unsigned long stepTime4 = 0;
//unsigned long delay1 = random(10, 100); // sequential delay stepping from LED to LED 
//unsigned long delay2 = random(10, 100);
//unsigned long delay3 = random(10, 100);
//unsigned long delay4 = random(10, 100);
unsigned long delay1 = 100; // sequential delay stepping from LED to LED 
unsigned long delay2 = 100;
unsigned long delay3 = 100;
unsigned long delay4 = 100;
// strand number
int strandNo = 3;

// strand length variables
int start1LED = 0;
    
int str1Length = 15; //first rib of umbrella
int str2Length = 15; //Second rib of umbrella
int str3Length = 15; //rib 3
int str4Length = 15; //rib 4

int strLED = 0; //first rib of umbrella

int str1LED = 0; //first rib of umbrella
int str2LED = 16; //Second rib of umbrella
int str3LED = 34; //rib 3
int str4LED = 51; //rib 4

int reset = 0; //reset all LEDs when not sensing people
//---------------------------------------------------------------//

void setup()
{
  FastSPI_LED.setLeds(NUM_LEDS);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_SM16716);
  FastSPI_LED.setChipset(CFastSPI_LED::SPI_TM1809);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_LPD6803);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_HL1606);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_595);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_WS2801);
  FastSPI_LED.setPin(4); //set pin to drive LEDs
  FastSPI_LED.init(); //initiate the library for emenint use
  FastSPI_LED.start();
  leds = (struct CRGB*)FastSPI_LED.getRGBData(); 
  Serial.begin(9600);
  Serial.println("serial");

}

void loop (){
//  value = pulseIn(sensorPin, HIGH);
  value = 10;
  cm = value/58; //pulse width is 58 microseconds per cm
  inches = value / 147; //which is 147 microseconds per inch

  if (inches <= 10) {
    
    int strLED[] = {0, 16, 34, 52 };
    int end1LED = start1LED + str1Length;
    int i;



  for(i = 0; i < 4; i++) {
      currentMillis = millis();

  Serial.print("strandNo: ");
  Serial.println(i);
  
  int startLED = strLED[i];
  int endLED = strLED[i] + str1Length;
  Serial.print("startLED: ");
  Serial.println(startLED);
    
  Serial.print("endLED: ");
  Serial.println(endLED);

    for(int j = startLED; j < endLED; j++) {
      int currentLED = j;
      Serial.print("currentLED: ");
      Serial.println(j);

      if(currentMillis - stepTime1 >= delay1) { //turn off LEDs 
        leds[currentLED+strLED[i]].b = 0;
        Serial.print("LED: ");
        Serial.print(currentLED);
        Serial.println(" is off.");
        
        leds[currentLED].g = 0; 
        leds[currentLED].r = 0;

        if(j == str1Length){
          j = 0;
        }

        currentLED++;

// turn on LEDs 
        leds[currentLED].b = 255; 
        Serial.print("LED: ");
        Serial.print(currentLED);
        Serial.println(" is on.");
        leds[currentLED].g = 255; 
        leds[currentLED].r = 255;

        stepTime1 = currentMillis;
      }
    }
}    

    FastSPI_LED.show();
    //Serial.println("LED's On ");
  }
  else{
    
    int n;
//    delay(8000);
    
    for(n = 0; n < NUM_LEDS; n++){
      leds[reset].b = 0;
      leds[reset].g = 0;
      leds[reset].r = 0;
      reset++;
      
      if(reset == NUM_LEDS){
        reset = 0;
      }

      FastSPI_LED.show();
      Serial.println("No people detected. ");
    }
  }
}

