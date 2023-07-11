// written by Bereket Kebede
// Dextrous robotics
//ATMega3280P

const int DIR = 6;
const int STEP = 7;
const int  steps_per_rev = 200;

float ang_speed;
float speed;
int lock = 0;
float radius = 3;

unsigned long StartTime;
unsigned long CurrentTime;
unsigned long ElapsedTime;


#include <LiquidCrystal_I2C.h>
// Define SDA and SCL pin for LCD:
#define SDAPin A4 // Data pin
#define SCLPin A5 // Clock pin
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered):
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4); //Change to (0x27,16,2) for 1602 LCD



void setup()
{
  StartTime = millis();
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);

  lcd.init();
  lcd.backlight();
}

void loop()
{
  // 400 works
  digitalWrite(DIR, LOW);
  //Serial.println("Spinning Clockwise...");
  
  StartTime = millis();

  for(int i = 0; i<steps_per_rev; i++)
  {
   
    digitalWrite(STEP, HIGH);
    delayMicroseconds(2000);
     digitalWrite(STEP, LOW);
    delayMicroseconds(2000);
  }
  // delay(1000); 
  CurrentTime = millis();
  ElapsedTime = CurrentTime - StartTime;
  // Serial.print("time is: ");
  // Serial.println(ElapsedTime);

  if (lock == 0){
      lock = lock + 1;
      //ang_speed = 1/ElapsedTime;
      ang_speed = 1.00/ (ElapsedTime/1000.00);
  }

  // speed at the center of surface FOV, assume half way from center to edge for disc
  speed = radius * ang_speed * 6.14;

  // Serial.println(ElapsedTime/1000.00);
  Serial.print("ang speed: ");
  Serial.print(ang_speed);
  Serial.print(" rev/s");
  Serial.print("| radius: ");
  Serial.print(radius);
  Serial.print(" mm");
  Serial.print("| speed: ");
  Serial.print(speed);
  Serial.println(" mm/s");

  lcd.setCursor(0,0); // Set the cursor to column 1, line 1 (counting starts at zero)
  lcd.print("speed:"); // Prints string "Display = " on the LCD
  lcd.print(speed); // Prints the measured distance
  lcd.print("cm/s"); // Prints string "Display = " on the LCD
}

