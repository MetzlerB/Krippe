#include <Arduino.h>
#include <FastLED.h>
#include <random>
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>

// How many leds in your strip?
#define NUM_LEDS 145
//pin 0 bis 133 Rahmen
//pin 134 bis 144 Krippe/Stadt
//pin 145 Lagerfeuer
const int x = NUM_LEDS;

// For led chips like WS2812, which have hue_color data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 17 


// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
Serial.begin(115200);

  pinMode(DATA_PIN, OUTPUT);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  // put your setup code here, to run once:
  srand( (unsigned)time( NULL ) );

   
}
//-----------------------------------------------Init-----------------------------

//RGB-Array
unsigned char RGB_x[3] = {0,0,0};
//unsigned char *rgb_u;
//rgb_u = RGB_x;

//HSV-Array
unsigned char HSV_x[3] = {0,0,0};
//unsigned char *hsv;
//hsv = HSV;

unsigned char brightness = 50;

//-----------------------------------------------Functions----------------------------------------

//Sequence-Load  // Intro Loading Sequence
void Load(){
  for (int i = 0; i < x; i++){
      leds[i] = CRGB::Red;
      leds[i] %= 50;
    }
    FastLED.show();
    
  for (int i = 0; i < x; i++){
  
    leds[i] = CRGB::Green;
    leds[i] %= 50;
    FastLED.show();
    delay(20);
  }
  return;
}

//Sequence-count_up
void LED(int LEDnum,unsigned char RGB_cu[],unsigned char Helligkeit,unsigned char HSV_cu[],int RGB_HSV){
      
      switch (RGB_HSV) {
        case 1:
          leds[LEDnum] = CRGB(RGB_cu[0],RGB_cu[1],RGB_cu[2]);
          leds[LEDnum] %= Helligkeit;
        break;

        case 2:
          leds[LEDnum] = CHSV(HSV_cu[0],HSV_cu[1],HSV_cu[2]);
        break;

      }
      //FastLED.show();
}

//Sequence-kill

void kill(){
for (int i = 0; i < x; i++) {
    leds[i] = CRGB::Black;
    leds[i] %= 100;
    }
  FastLED.show();
  delay(2000);

}

int sign(){
  int sign = 0;
  switch (rand()% 2)
  {
  case 0 :
    sign = 1;
    break;
  case 1 :
    sign = -1;
    break;
  }
  
  return sign;
} 


/*
void Flacker(int flacknum){
  
   int a = Flacker_array[flacknum];
    Serial.println(flacknum);
    Serial.println(Flacker_array[flacknum]);
    delay(2000);
  //hue_color = random(5,30);

}
*/

void loop() {
  
  #ifndef Flacker_array  // if x has not been #defined
  int Flacker_array[x];
  for (int i = 144; i < x; ++i) {
      Flacker_array[i] = rand()% 35 + 5; //25 + 20;
    }
  #endif

  #ifndef Background_array  // if x has not been #defined
  int Background_array[x];
  int rrr = 0;
  int rr  = 10;
  int r   = 20;
  int m   = 67;
  int l   = 113;
  int ll  = 123;
  int lll = 133;
  int sky = 200;
    for (int i = rrr; i < rr; ++i) {
      Background_array[i] = 20;
    }
    for (int i = rr; i < r; ++i) {
      Background_array[i] = 25;
    }
    for (int i = r; i < m; ++i) {
      Background_array[i] = sky;
    }
    for (int i = m; i < l; ++i) {
      Background_array[i] = sky;
    }
    for (int i = l; i < ll; ++i) {
      Background_array[i] = 25;
    }
    for (int i = ll; i < lll; ++i) {
      Background_array[i] = 20;
    }
  #endif

//-----------------------------------------------Loading sequence----------------------------------------
Load();
delay(200);
kill();
//Flacker(x);
//-----------------------------------------------Loop----------------------------------------

  //Flacker-Loop-Counter 
  int k = 100000;
  //Define hue values 
  unsigned char hue_color = 0; //0-45 Rotgelb töne
  unsigned char Saturation = 255; //255 max
  unsigned char power = 255;  //random
  
  /*
  for (int i = 0; i < x; i++)
    {
      int a= Flacker_array[i];
      Serial.println(i+100000);
      Serial.println(a);
      a = a + ( (rand()% 5)*sign() );
      Serial.println(i+200000);
      Serial.println(a);
      delay(2000);
    }
*/
  //Schwellwerte Blinken
  int o = 50;
  int u = 70;
  uint8_t light = 0;
  int lightstep = 1;
  //uint8_t
  while(k>0){ 
    for (int i = rrr; i < lll; i++) {
      leds[i] = CHSV(Background_array[i],Saturation,light);
    } 
      if(light >= 100){
        sky = 42;
        for (int i = r; i < m; ++i) {
          Background_array[i] = sky;
        }
        for (int i = m; i < l; ++i) {
          Background_array[i] = sky;
        }
      }else{
        sky = 200;
        for (int i = r; i < m; ++i) {
          Background_array[i] = sky;
        }
        for (int i = m; i < l; ++i) {
          Background_array[i] = sky;
        }
      }

      light += lightstep;
      if(light>=255||light<=0){
        lightstep *= -1;
      }
      



    //Krippe direkt
    leds[133] = CHSV(20,Saturation,random(200,255));
    leds[134] = CHSV(42,Saturation,random(200,255));
    //Häuser von Links nach Rechts
    //Haus 1
    leds[135] = CHSV(10,Saturation,random(u,o));
    //Haus 2
    leds[136] = CHSV(25,Saturation,random(u,o));
    //Haus 3
    int haus3 = random(u,o);
    leds[137] = CHSV(42,Saturation,haus3);
    leds[138] = CHSV(25,Saturation,haus3);
    //Haus 4
    int haus4 = random(u,o);
    leds[139] = CHSV(42,Saturation,haus4);
    leds[140] = CHSV(21,Saturation,haus4);
    leds[141] = CHSV(30,Saturation,haus4);
    leds[142] = CHSV(10,Saturation,haus4);
    leds[143] = CHSV(20,Saturation,haus4);
    //Lagerfeuer
    for (int i = 144; i < x; i++) {
      leds[i] = CHSV(Flacker_array[i],Saturation,random(120,150));
      }

    if(light >= 110){
      for (int i = 133; i < 135; i++) {
        leds[i] %= 50;
      }
    }  

    if(light >= 110){
      for (int i = 135; i < x; i++) {
        leds[i] %= 0;
      }
    }

    //refreshing array
    for (int i = 0; i < x; i++)
    {
      int a= Flacker_array[i];
      a = a + ( (rand()% 1)*sign() );
      Flacker_array[i] = a;
      if (a < 20){
          Flacker_array[i] = a+1;
      }
      if (a > 25){
          Flacker_array[i] = a-1;
      }

    }

    




    //delay(random(20,50));
    delay(random(100,250));
    FastLED.show();
    k--;
  }


/*
  while(k>0){ 
    
    hue_color = rand()% 30 + 5;//random(5,30);
    Serial.println(hue_color);

    for (int i = 0; i < 10; i++)
    {
      int f = hue_color+i;
      if (f >= 42){f = f-12;}
      
      for (int i = 0; i < x; i++) {
          leds[i] = CHSV(f,Saturation,power);
      }
  
       
      Serial.println(f);
      FastLED.show();
      delay(random(20,50));
      power = random(150,255);
    }
    //delay(random(100,300));
    
    k--;
  }
*/
}


/*
int light = 0

    for(int i = 0; i<10 ;i++){
    HSV_x[0] = f;   //random(0,255);
            HSV_x[1] = 255;
            HSV_x[2] = 180;
            LED(i, HSV_y, brightness, HSV_x,2);
    leds[0] = CHSV(50,255,50);
    
    FastLED.show();
    delay(20);
    }

*/