
// Charliplex layout of our pins

/* 4 Pins and 10 LEDs 
int pinMap[5]={3,4,0,1};

int numPins = 4;
int numLeds = 10;
byte    ledPins[][4] ={
        { 0,1,2,2 },
        { 1,0,2,2 },
        { 2,0,1,2 },
        { 2,1,0,2 },
        { 0,2,1,2 },
        { 1,2,0,2 },
        { 2,2,0,1 },
        { 2,2,1,0 },
        { 2,0,2,1 },
        { 2,1,2,0 },
        };
*/

// 5 Pins and 20 LEDs

/*
 * 
Pin   1 >    1-   2+   5-   6+  11-  12+  19-  20+
Pin   2 >    1+   2-   3-   4+   9-  10+  17-  18+
Pin   3 >    3+   4-   5+   6-   7-   8+  15-  16+
Pin   4 >    7+   8-   9+  10-  11+  12-  13-  14+
Pin   5 >   13+  14-  15+  16-  17+  18-  19+  20-
 *
 */

int pinMap[5]={3,4,0,1,2};

int numPins = 5;
int numLeds = 20;
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

const int MODE_CYCLE=0;
const int MODE_PONG=1;
const int MODE_SIN_PONG=2;

int mode = MODE_SIN_PONG;

void setLed( int iLed )
{
  bool bInRange = ( iLed >= 0
  && iLed < numLeds );
  for( int iPin = 0; iPin < numPins; iPin++ )
  {
      pinMode( pinMap[iPin], INPUT );
  }
    
  for( int iPin = 0; iPin < numPins; iPin++ )
  {
    if( bInRange )
    {
      switch( ledPins[iLed][iPin] )
      {
        case 0:
          pinMode( pinMap[iPin], OUTPUT );
          digitalWrite( pinMap[iPin], LOW );
        break;
        case 1:
          pinMode( pinMap[iPin], OUTPUT );
          digitalWrite( pinMap[iPin], HIGH );
        break;
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
//  Serial.begin(9600);

}

float ang = 0;
int iWhich = 0;
int iDir = 1;
const float PI2 = PI*2.0f;
void loop() {

  switch( mode )
  {
    case MODE_SIN_PONG:
    {
      ang += PI*0.03f;
      if( ang > PI2 ){ ang -= PI2; }
      float fVal = sin(ang); // -1 to 1
      fVal += 1.0; // 0-2
      fVal *= 0.5; // 0-1
    
      iWhich = numLeds*fVal;
      break;
    }

    case MODE_CYCLE:
      iWhich++;
      iWhich%=numLeds;
      break;

    case MODE_PONG:
      iWhich += iDir;
      if( iWhich < 0 || iWhich > numLeds-1 )
      {
        iDir *= -1;
        iWhich += iDir;
      }   
      break;
  }
  
  if( iWhich >= numLeds ){ iWhich = numLeds-1; }
  setLed(iWhich);
  iWhich %= numLeds;
  delay(15);
}
