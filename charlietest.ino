
// Charliplex layout of our pins
// 5 Pins and 20 LEDs
/*
 * e.g. Virtual pin 1 of micro (Pin 3 in reality) should be wired to LED 1 -ve, LED 2 +ve, LED 5 -ve etc...
Pin   1 >    1-   2+   5-   6+  11-  12+  19-  20+
Pin   2 >    1+   2-   3-   4+   9-  10+  17-  18+
Pin   3 >    3+   4-   5+   6-   7-   8+  15-  16+
Pin   4 >    7+   8-   9+  10-  11+  12-  13-  14+
Pin   5 >   13+  14-  15+  16-  17+  18-  19+  20-
 *
 */

// Map the microcontroller pins to the virtual pins. e.g. virtual pin 1 (0th entry) is microcontroller pin 3
int pinMap[5]={3,4,0,1,2};
// Total number of pins
int numPins = 5;
// Total number of LEDs
int numLeds = 20;
// PinStates for each LED. e.g. for first LED to be lit, virtual pin 1 needs to be low, 2 needs to be high, the rest need to be input (2)
byte    ledPins[][5] ={
        { 0,1,2,2,2 },
        { 1,0,2,2,2 },
        { 2,0,1,2,2 },
        { 2,1,0,2,2 },
        { 0,2,1,2,2 },
        { 1,2,0,2,2 },
        { 2,2,0,1,2 },
        { 2,2,1,0,2 },
        { 2,0,2,1,2 },
        { 2,1,2,0,2 },
        { 0,2,2,1,2 },
        { 1,2,2,0,2 },
        { 2,2,2,0,1 },
        { 2,2,2,1,0 },
        { 2,2,0,2,1 },
        { 2,2,1,2,0 },
        { 2,0,2,2,1 },
        { 2,1,2,2,0 },
        { 0,2,2,2,1 },
        { 1,2,2,2,0 },
        };

// Define some pattern modes
const int MODE_CYCLE=0;
const int MODE_PONG=1;
const int MODE_SIN_PONG=2;

// Current mode
int mode = MODE_SIN_PONG;

// Sets a single LED to on, based on the pin mappings
void setLed( int iLed )
{
  bool bInRange = ( iLed >= 0 && iLed < numLeds ); // Ensure pin is in range/valid
  
  // To reduce ghosting, turn all pins to inputs temporarily
  for( int iPin = 0; iPin < numPins; iPin++ )
  {
      pinMode( pinMap[iPin], INPUT );
  }
  
  // Now loop through each pin and set the correct state
  for( int iPin = 0; iPin < numPins; iPin++ )
  {
    // only if LED is valid - actually better to do this check elsewhere.
    if( bInRange )
    {
      // Switch based on the desired state
      switch( ledPins[iLed][iPin] )
      {
        case 0: // OUTPUT / LOW
          pinMode( pinMap[iPin], OUTPUT );
          digitalWrite( pinMap[iPin], LOW );
        break;
        case 1: // OUTPUT / HIGH
          pinMode( pinMap[iPin], OUTPUT );
          digitalWrite( pinMap[iPin], HIGH );
        break;
        default: // INPUT / High Impedance. We already set this above, so no need to do it again.
        break;
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
//  Serial.begin(9600);

}

// Variables to control LED movement for the various modes
float ang = 0; // Angle for the sine function
int iWhich = 0; // Current LED
int iDir = 1;   // Direction of travel
const float PI2 = PI*2.0f; // Wrap point for angle

void loop() {

  switch( mode )
  {
    // PingPong back and forth, but speed up and slow down on a sine wave
    case MODE_SIN_PONG:
    {
      ang += PI*0.03f; // Speed of effect
      if( ang > PI2 ){ ang -= PI2; } // wrap the angle
      float fVal = sin(ang); // range is -1 to 1
      fVal += 1.0; // range is now 0-2
      fVal *= 0.5; // range is now 0-1
    
      iWhich = numLeds*fVal; // Select the LED based on where in the wave we are
      break;
    }

    // Just loop through the LEDs
    case MODE_CYCLE:
      iWhich++;
      iWhich%=numLeds;
      break;

    // PingPing back and forth
    case MODE_PONG:
      iWhich += iDir;
      if( iWhich < 0 || iWhich > numLeds-1 )
      {
        iDir *= -1;
        iWhich += iDir;
      }   
      break;
  }
  
  iWhich %= numLeds; // stay in range (in case of rounding error)
  setLed(iWhich); // Set the LED
  delay(15);
}
