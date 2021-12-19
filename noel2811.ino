#include <Arduino.h>
#include <FastLED.h>
#include <Wire.h>
#include <U8x8lib.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(SCL, SDA, U8X8_PIN_NONE);

#define NUM_LEDS 150
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
#define LED_PIN 4
#define BUTTON1 6
#define BUTTON2 5
#define MODE_RUN 0
#define MODE_INIT 1
#define MODE_NAME 2
#define AUTO_DURATION 30
CRGB leds[NUM_LEDS];

#define C0 0
#define C1 7
#define C2 23
#define C3 75
#define C4 136
#define C5 255

#define P0 0
#define P1 51
#define P2 255

byte greyscale6[]={C0,C1,C2,C3,C4,C5};

CRGB palette8[]={{C0,C0,C0},{C5,C0,C0},{C0,C5,C0},{C0,C0,C5},{C0,C5,C5},{C5,C0,C5},{C5,C5,C0},{C5,C5,C5}};

CRGB palette27[]={
{P0,P0,P0},{P0,P0,P1},{P0,P0,P2},{P0,P1,P0},{P0,P1,P1},{P0,P1,P2},{P0,P2,P0},{P0,P2,P1},{P0,P2,P2},
{P1,P0,P0},{P1,P0,P1},{P1,P0,P2},{P1,P1,P0},{P1,P1,P1},{P1,P1,P2},{P1,P2,P0},{P1,P2,P1},{P1,P2,P2},
{P2,P0,P0},{P2,P0,P1},{P2,P0,P2},{P2,P1,P0},{P2,P1,P1},{P2,P1,P2},{P2,P2,P0},{P2,P2,P1},{P2,P2,P2}
};

char* pingPong(byte mode)
{
  static byte color;
  static byte index;
  static bool sens;
  switch(mode)
  {
    case MODE_INIT :
      color=random(1, 26);
      index=0;
      sens=true;
      break;
    case MODE_NAME :
      return "PingPong";
  }

  leds[index]=palette27[color];

  if(sens)
  {
    if(index<NUM_LEDS-1) index++;
    else {sens=false; color=random(1, 26);}
  }
  else
  {
    if(index>0) index--;
    else {sens=true; color=random(1, 26);}
  }
  FastLED.show(); 
  delay(5);
  return 0;
}

char* flash(byte mode)
{
  static CRGB color;

  switch(mode)
  {
    case MODE_INIT :
      color=palette27[random(1, 26)];
      break;
    case MODE_NAME :
      return "Flashing";
  }

  byte index[4];
  for(byte i=0; i<sizeof(index);i++)
  {
    index[i]=random(0,NUM_LEDS);
    leds[index[i]]=color;
  }
  FastLED.show(); 
  delay(5);
  for(byte i=0; i<sizeof(index);i++)
  {
    leds[index[i]]=CRGB::Black;
  }
  FastLED.show();
  return 0;
}

char* multicolor(byte mode)
{
  switch(mode)
  {
    case MODE_INIT :
      break;
    case MODE_NAME :
      return "MultiCol";
  }

  leds[random(0,NUM_LEDS)]=palette27[random(1, 26)];
  leds[random(0,NUM_LEDS)]=palette27[random(1, 26)];
  leds[random(0,NUM_LEDS)]=palette27[random(1, 26)];
  leds[random(0,NUM_LEDS)]=palette27[random(1, 26)];
  FastLED.show(); 
  delay(5);
  return 0;
}

char* fadingDots(byte mode)
{
  switch(mode)
  {
    case MODE_INIT :
      break;
    case MODE_NAME :
      return "FadeDots";
  }

  for(byte i=0; i<NUM_LEDS; i++)
    leds[i].fadeToBlackBy( 8 );
  leds[random(0,NUM_LEDS)]=palette27[random(1, 26)];
  FastLED.show(); 
  delay(20);
  return 0;
}

char* blinking(byte mode)
{
  static CRGB color;

  switch(mode)
  {
    case MODE_INIT :
      color=palette27[random(1, 26)];
      break;
    case MODE_NAME :
      return "Blinking";
  }

  for(byte i=0; i<16; i++)
  {
    byte led=random(0,NUM_LEDS);
    leds[led]=color;
    leds[led].fadeLightBy(random(0,256));
  }
  FastLED.show();
  delay(5);
  return 0;
}

char* wave(byte mode)
{
  static byte color;
  static byte index=0;

  switch(mode)
  {
    case MODE_INIT :
      index=0;
      break;
    case MODE_NAME :
      return "ColWaves";
  }

  for(byte i=NUM_LEDS-1; i>0; i--)
    leds[i]=leds[i-1];

  if(!index)
    color=random(1, 26);

  leds[0]=palette27[color];
  if(++index<16)
  {
    leds[0].fadeToBlackBy((16-index)<<4);
  }
  else if(index<32)
  {
    leds[0].fadeToBlackBy((index-16)<<4);
  }
  else if(index<40)
  {
    leds[0]=0;
  }
  else
  {
    leds[0]=0;
    index=0;
  }

  FastLED.show();
  delay(50);
  return 0;
}

char* fullSpeedo(byte mode)
{
  switch(mode)
  {
    case MODE_INIT :
      break;
    case MODE_NAME :
      return "MaxSpeed";
  }
  
  for(byte i=NUM_LEDS-1; i>0; i--)
    leds[i]=leds[i-1];
  leds[0]=palette27[random(1, 26)];
  FastLED.show();
  delay(20);
  return 0;
}

char* halfSpeedo(byte mode)
{
  switch(mode)
  {
    case MODE_INIT :
      break;
    case MODE_NAME :
      return "LongWorm";
  }

  static word count=0;
  for(byte i=NUM_LEDS-1; i>0; i--)
    leds[i]=leds[i-1];
  if(++count<NUM_LEDS)
    leds[0]=palette27[random(1, 26)];
  else if(count<NUM_LEDS*2)
    leds[0]=0;
  else
    count=0;
  FastLED.show();
  delay(20);
  return 0;
}

char* rainbow(byte mode)
{
  static byte count;
  switch(mode)
  {
    case MODE_INIT :
      count=0;
      break;
    case MODE_NAME :
      return "Rainbows";
  }

  for(byte i=NUM_LEDS-1; i>0; i--)
    leds[i]=leds[i-1];
  leds[0]=CHSV( (++count)<<1, 255, 255);
  FastLED.show();
  delay(10);
  return 0;
}

char* topDown(byte mode)
{
  static byte color;
  static word count;

  switch(mode)
  {
    case MODE_INIT :
      count=0;
      break;
    case MODE_NAME :
      return "Top&Down";
  }

  if(!count)
    color=random(1, 26);
  if(++count<NUM_LEDS)
    leds[count]=palette27[color];
  else if(count<(NUM_LEDS*2))
    leds[(NUM_LEDS*2)-count-1]=0;
  else
    count=0;
  FastLED.show();
  delay(20);
  return 0;
}

char* randomMono(byte mode)
{
  static byte inOut;
  static byte count;
  static CRGB color;

  switch(mode)
  {
    case MODE_INIT :
      for(byte i=0; i<NUM_LEDS; i++)
        leds[i]=0;
      inOut=1;
      count=NUM_LEDS;
      break;
    case MODE_NAME :
      return "AllRandz";
  }
  
  if(count==NUM_LEDS)
  {
    if(inOut)
      color=palette27[random(1, 26)];
    else
      color=CRGB::Black;
  }
  if(count-->0)
  {
    byte index=random(NUM_LEDS);
    while(color==leds[index])
    {
      if(++index==NUM_LEDS)
        index=0;
    }
    leds[index]=color;
  }
  else
  {
    count=NUM_LEDS;
    inOut=!inOut;
  }
  FastLED.show();
  delay(20);
  return 0;
}

void pacManGhost(int frame, int first,long color,bool upDown)
{
  frame-=first;
  if((frame>=0)&&(frame<NUM_LEDS-4))
  {
    if(!upDown) frame=NUM_LEDS-4-frame;
    leds[frame]=color;
    leds[frame+1]=color;
    leds[frame+2]=color;
    leds[frame+3]=color;
  }
}
char* pacMan(byte mode)
{
  static int frame;

  switch(mode)
  {
    case MODE_INIT :
      frame=0;
      break;
    case MODE_NAME :
      return "PAC MAN";
  }

  for(byte index=0; index<NUM_LEDS; index++)
  {
    if(!(index&3))
      leds[index]=0xFF8000;
    else
      leds[index]=0;
  }
  pacManGhost(frame,15,0x0000FF,true);
  pacManGhost(frame,45,0xFF0000,false);
  pacManGhost(frame,60,0xFF00FF,true);
  pacManGhost(frame,90,0x00FFFF,false);
//  pacManGhost(frame,120,0x0000FF,true);


//  if(!(frame&15))
//  {
//    if(!random(4))
//      pacManGhost(frame,120,0x0000FF,random(4));
//  }
  frame++;
  if(frame>90+NUM_LEDS) frame=0;

  FastLED.show();
  delay(50);
  return 0;
}

char* plusOne(byte mode)
{
  static CRGB color;
  static int pos;
  static bool upDown;
  static int num;

  switch(mode)
  {
    case MODE_INIT :
      color=palette27[random(1, 26)];
      pos=0;
      upDown=true;
      num=1;
      break;
    case MODE_NAME :
      return "One&More";
  }


  if((pos>=0)&&(pos<NUM_LEDS))
  leds[pos]=color;
  if(upDown)
  {
    if((pos-num>=0)&&(pos-num<NUM_LEDS))
      leds[pos-num]=0;
    pos++;
    if(pos>=NUM_LEDS+num)
    {
      pos--;
      upDown=false;
      num++;
    }
  }
  else
  {
    if((pos+num>0)&&(pos+num<NUM_LEDS))
      leds[pos+num]=0;
    pos--;
    if(pos+num<0)
    {
      pos=0;
      upDown=true;
      num++;
    }
  }
  FastLED.show();
  delay(2);
  return 0;
}

char* storm(byte mode)
{
  static byte animStep;
  static CRGB color;
  static word pos;
  static bool upDown;

  switch(mode)
  {
    case MODE_INIT :
      animStep=0;
      break;
    case MODE_NAME :
      return "Storming";
  }

  if(!animStep)
  {
    color=palette27[random(1, 26)];
    pos=random(0,NUM_LEDS-16);
    upDown=random(0,2);
    if(!upDown) pos+=16;
    for(byte i=0; i<NUM_LEDS; i++)
      leds[i]=0;
  }
  leds[pos]=color;
  pos=upDown?(pos+1):(pos-1);
  animStep++;
  if(animStep==16)
    animStep=0;
  FastLED.show();
  delay(5);
  return 0;
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  randomSeed(analogRead(0));

  u8x8.begin();
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_profont29_2x3_r);
}

char*(*function[])(byte) =
{
  autoChange,
  rainbow,
  flash,
  topDown,
  blinking,
  halfSpeedo,
  storm,
  multicolor,
  wave,
  fadingDots,
  pingPong,
  randomMono,
  fullSpeedo,
  plusOne
};

byte numFunctions=sizeof(function)/sizeof(*function);
int program=0;
byte runningMode=MODE_INIT;

char* autoChange(byte mode)
{
  static unsigned long startTime;
  static int program;
  static byte runningMode;

  switch(mode)
  {
    case MODE_INIT :
      program=1;
      startTime=millis();
      runningMode=MODE_INIT;
      break;
    case MODE_NAME :
      return "AUTO";
  }

  if(runningMode==MODE_INIT)
  {
    (*function[program])(MODE_INIT);
    u8x8.drawString(0,0,(*function[program])(MODE_NAME));
    runningMode=MODE_RUN;
  }
  (*function[program])(MODE_RUN);

  unsigned long currentTime=millis();
  int seconds=AUTO_DURATION-(int)((currentTime-startTime)/1000);
  static int lastSeconds;
  char text[8];
  sprintf(text,"%d ",seconds);
  text[3]=0;
  if(seconds<0)
  {
     startTime=millis();
    program++;
    if(program>=numFunctions) program=1;
    runningMode=MODE_INIT;
  }
  else if(seconds!=lastSeconds)
  {
    u8x8.drawString(10,4,text);
    lastSeconds=seconds;
  }

  return 0;
}

void loop()
{
static byte button1,button2;

  if(runningMode==MODE_INIT)
  {
    (*function[program])(MODE_INIT);
    u8x8.clearLine(4);
    u8x8.clearLine(5);
    u8x8.clearLine(6);
    u8x8.clearLine(7);
    u8x8.drawString(0,program?0:4,(*function[program])(MODE_NAME));
    runningMode=MODE_RUN;
  }
  (*function[program])(MODE_RUN);

  if((digitalRead(BUTTON1)==LOW)&&(button1==HIGH))
  {
    program++;
    if(program>=numFunctions) program=0;
    runningMode=MODE_INIT;
  }
  button1=digitalRead(BUTTON1);
  if((digitalRead(BUTTON2)==LOW)&&(button2==HIGH))
  {
    program--;
    if(program<0) program=numFunctions-1;
    runningMode=MODE_INIT;
  }
  button2=digitalRead(BUTTON2);

}

