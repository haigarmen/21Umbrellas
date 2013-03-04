
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
int noOfStrands = 3;

// strand length variables
int start1LED = 0;
    
int str1Length = 15; //first rib of umbrella
int str2Length = 15; //Second rib of umbrella
int str3Length = 15; //rib 3
int str4Length = 15; //rib 4

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

//  Serial.print(cm);
//  Serial.print(" cm, ");
//  Serial.print(inches);
//  Serial.print("in");
//  Serial.println();

  if (inches <= 10) {


    //------------------Strand 1------------------/
    int start1LED = 0;
    int end1LED = start1LED + str1Length;

Serial.print("start1LED: ");
Serial.println(start1LED);
    
    int i;

for(i = 0; i < noOfStrands; i++) {

  int startLED = end1LED + 1;
  int endLED = end1LED + str2Length;
    
    for(k = startLED; k < endLED; k++) {
      currentMillis = millis();
      if(currentMillis - stepTime1 >= delay1) { //turn off LEDs 
        leds[strLED].b = 0; 
        leds[strLED].g = 0; 
        leds[strLED].r = 0;

        strLED++;

        if(strLED == 15){
          strLED = 0;
        }

        leds[strLED].b = 255; 
        leds[strLED].g = 255; 
        leds[strLED].r = 255;

        stepTime1 = currentMillis;


        //        delay(100);
      }
    }
}    
    //--------------Strand 1-----------------------//

    //------------------Strand 2------------------/
    int j;

int start2LED = end1LED + 1;
int end2LED = end1LED + str2Length;
Serial.print("start2LED: ");
Serial.println(start2LED);

    for(j = start2LED; j < end2LED; j++) {
      currentMillis2 = millis();
      if(currentMillis2 - stepTime2 >= delay2) { //turn off LEDs 
        leds[str2LED].b = 0; 
        leds[str2LED].g = 0; 
        leds[str2LED].r = 0;

        str2LED++;

        if(str2LED == 33){
          str2LED = 15;
        }

        leds[str2LED].b = 255; 
        leds[str2LED].g = 255; 
        leds[str2LED].r = 255;

        stepTime2 = currentMillis2;


        //        delay(100);
      }
    }
    //--------------Strand 2-----------------------//
    //------------------Strand 3------------------/
    int l;
int start3LED = end2LED + 1;
int end3LED = end2LED + str3Length;
Serial.print("start3LED: ");
Serial.println(start3LED);

    for(l = start3LED; l < end3LED; l++) {
      currentMillis3 = millis();
      if(currentMillis3 - stepTime3 >= delay3) { //turn off LEDs 
        leds[str3LED].b = 0; 
        leds[str3LED].g = 0; 
        leds[str3LED].r = 0;

        str3LED++;

        if(str3LED == 51){
          str3LED = 33;
        }

        leds[str3LED].b = 255; 
        leds[str3LED].g = 255; 
        leds[str3LED].r = 255;

        stepTime3 = currentMillis3;


        //        delay(100);




      }
    }
    //--------------Strand 3-----------------------//

    //------------------Strand 4------------------/
    int m;

int start4LED = end3LED + 1;
int end4LED = end3LED + str4Length;

Serial.print("start4LED:");
Serial.println(start4LED);
//Serial.println("end4LED is " + end4LED);

    for(m = start4LED; m < end4LED; m++) {
      currentMillis4 = millis();
      if(currentMillis4 - stepTime4 >= delay4) { //turn off LEDs 
        leds[str4LED].b = 0; 
        leds[str4LED].g = 0; 
        leds[str4LED].r = 0;

        str4LED++;

        if(str4LED == 70){
          str4LED = 52;
        }

        leds[str4LED].b = 255; 
        leds[str4LED].g = 255; 
        leds[str4LED].r = 255;

        stepTime4 = currentMillis4;
        //        delay(100);

      }
    }
    //--------------Strand 4-----------------------//

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

