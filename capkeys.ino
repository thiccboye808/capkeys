// capacitive sense keys
//
// by thiccboye808/kerochan
//
// enters keypresses when a touch is sensed 
// on connected conductors, coins r recomended
//
// use 1m ohm resitors between send and receive pins for
// each "key"

//#define DEBUG_MODE // switches keyboard for serial output

#include <CapacitiveSensor.h>
#ifndef DEBUG_MODE
#include <Keyboard.h>
#endif
const uint8_t SENSOR_NUM = 2; // number of sensors
const long THR = 1000; // may or may not need tuning
const char KEYS[ SENSOR_NUM ] = { 'z', 'x' };
CapacitiveSensor sensors[ SENSOR_NUM ] = { CapacitiveSensor( 3, 4 ), CapacitiveSensor( 6, 5 ) };
long values[ SENSOR_NUM ];

// enable pin
#define ENPIN 7 // allows for an on/off switch

// neopixel status indicator
//#define NEOPIXEL
#ifdef NEOPIXEL
#define NEOPIXEL_PIN 40
#define NEOPIXEL_ON Color( 0, 15, 0 )
#define NEOPIXEL_OFF Color( 15, 0, 0 )
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel = Adafruit_NeoPixel( 1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800 );
#endif

void setup() 
{
#ifdef ENPIN
  pinMode( ENPIN, INPUT_PULLUP );
#endif
#ifdef DEBUG_MODE
  Serial.begin( 9600 );
#else
  Keyboard.begin();
#endif
#ifdef NEOPIXEL
  pixel.begin();
#endif
}

void loop() 
{
  long start = millis();
  for( uint8_t i = 0; i < SENSOR_NUM; i ++ )
   values[ i ] = sensors[ i ].capacitiveSensor( 10 );
#ifdef NEOPIXEL
  pixel.clear();
#endif
#ifdef ENPIN
  if( digitalRead( ENPIN ) )
  {
#endif
#ifdef DEBUG_MODE
    Serial.print( millis() - start );
    for( uint8_t i = 0; i < SENSOR_NUM; i ++ )
    {
      Serial.print( '\t' );
      if( values[ i ] < THR )
        Serial.print( ' ' );
      else
        Serial.print( '*' );
      Serial.print( values[ i ] );
    }
    Serial.println();
#else
    for( uint8_t i = 0; i < SENSOR_NUM; i ++ )
      if( values[ i ] < THR )
        Keyboard.release( KEYS[ i ] );
      else
        Keyboard.press( KEYS[ i ] );
#endif
#ifdef ENPIN
#ifdef NEOPIXEL
    pixel.setPixelColor( 0, pixel.NEOPIXEL_ON );
  }
  else
    pixel.setPixelColor( 0, pixel.NEOPIXEL_OFF );
  pixel.show();
#else
  }
#endif
#endif
}
