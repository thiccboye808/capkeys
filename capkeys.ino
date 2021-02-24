// capacitive sense keyboard
//
// by thiccboye808/kerochan
//
// enters keypresses when a touch is sensed 
// on connected coins]
//
// use 1m ohm resitors between send and receive pins for
// each "key"
//
// could b used on anything with capacitive qualites
// but coins work great for thisW

//#define DEBUG_MODE // switches keyboard for serial output

#include <CapacitiveSensor.h>
#ifndef DEBUG_MODE
#include <Keyboard.h>
#endif
const uint8_t SENSOR_NUM = 2; // number of sensors (duh)
const long THR = 1000; // may or may not need tuning
const int ENPIN = 7; // enable pin
const char KEYS[ SENSOR_NUM ] = { 'z', 'x' };
CapacitiveSensor sensors[ SENSOR_NUM ] = { CapacitiveSensor( 3, 4 ), CapacitiveSensor( 6, 5 ) };
long values[ SENSOR_NUM ];

// metro m0 express only
#define METRO_NEO_PIXEL
#ifdef METRO_NEO_PIXEL
#define NEO_PIXEL_PIN 40
#define NEO_PIXEL_ON Color( 0, 15, 0 )
#define NEO_PIXEL_OFF Color( 15, 0, 0 )
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel = Adafruit_NeoPixel( 1, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800 );
#endif

void setup() 
{
  pinMode( ENPIN, INPUT_PULLUP );
#ifdef DEBUG_MODE
  Serial.begin( 9600 );
#else
  Keyboard.begin();
#endif
#ifdef METRO_NEO_PIXEL
  pixel.begin();
#endif
}

void loop() 
{
  long start = millis();
  for( uint8_t i = 0; i < SENSOR_NUM; i ++ )
   values[ i ] = sensors[ i ].capacitiveSensor( 10 );
#ifdef METRO_NEO_PIXEL
  pixel.clear();
#endif
  if( digitalRead( ENPIN ) )
  {
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
#ifdef METRO_NEO_PIXEL
    pixel.setPixelColor( 0, pixel.NEO_PIXEL_ON );
  }
  else
    pixel.setPixelColor( 0, pixel.NEO_PIXEL_OFF );
  pixel.show();
#else
  }
#endif
}
