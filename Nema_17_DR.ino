// written by Bereket Kebede
// Dextrous robotics
//ATMega3280P

const int DIR = 6;
const int STEP = 7;
const int  steps_per_rev = 200;

float ang_speed;
float speed;
int lock = 0;
float radius = 2.00; // 2cm radius

unsigned long StartTime;
unsigned long CurrentTime;
unsigned long ElapsedTime = 0;
float period = 0;
float frequency = 0;
int count_rotation = 0;

#include <LiquidCrystal_I2C.h>
// Define SDA and SCL pin for LCD:
#define SDAPin A4 // Data pin
#define SCLPin A5 // Clock pin
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered):
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4); //Change to (0x27,16,2) for 1602 LCD


void setup()
{
  
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);

  lcd.init();
  lcd.backlight();
  StartTime = millis();
}

void loop()
{
  // 400 works
  //digitalWrite(DIR, LOW);
  //Serial.println("Spinning Clockwise...");
  
  //StartTime = millis();

  counter_clockwise();

  // buffer
  // 5 sec counter clokwise
  // 5 sec clockwise 

  // if (ElapsedTime > 5000 && ElapsedTime < 15000){
  //   digitalWrite(DIR, HIGH);
  //   for(int i = 0; i<steps_per_rev; i++)
  //   {
    
  //     digitalWrite(STEP, HIGH);
  //     delayMicroseconds(2000);
  //     digitalWrite(STEP, LOW);
  //     delayMicroseconds(2000);
  //   }
  // }
  // else if (15000 <= ElapsedTime && ElapsedTime <= 25000){
  //   digitalWrite(DIR, LOW);
  //   for(int i = 0; i<steps_per_rev; i++)
  //   {
    
  //     digitalWrite(STEP, HIGH);
  //     delayMicroseconds(2000);
  //     digitalWrite(STEP, LOW);
  //     delayMicroseconds(2000);
  //   }
  // }
  // else{
  // }
    
  
  //delay(200); 
  CurrentTime = millis();
  ElapsedTime = CurrentTime - StartTime;
  // Serial.print("time is: ");
  // Serial.println(ElapsedTime);

  if (lock == 0){
      lock = lock + 1;
      //ang_speed = 1/ElapsedTime;
      period = ElapsedTime;
      //ang_speed = 1.00/ (ElapsedTime/1000.00);
      //if (lock =1){
      frequency = 1000.00/period;
      ang_speed = 6.14 * frequency;
  }


  // speed at the center of surface FOV, assume half way from center to edge for disc
  speed = radius * ang_speed ;
  count_rotation = count_rotation + 1;
  // Serial.println(ElapsedTime/1000.00);


  if (ElapsedTime <5000){
   
    Serial.print("ang speed: ");
    Serial.print(ang_speed);
    Serial.print(" rad/s");
    Serial.print("| radius: ");
    Serial.print(radius);
    Serial.print(" cm");
    Serial.print("| speed: ");
    Serial.print(speed);
    Serial.print(" cm/s");
    Serial.print("| StartTime: ");
    Serial.print(StartTime);
    Serial.print("| CurrentTime: ");
    Serial.print(CurrentTime);
    Serial.print("| ElapesedTime: ");
    Serial.print(ElapsedTime);
    Serial.print("| Period: ");
    Serial.print(period);
    Serial.print(" ms");
    Serial.print("| frequency: ");
    Serial.print(frequency, 2);
    Serial.print(" hz");
    Serial.print("| rot count: ");
    Serial.println(count_rotation);

    lcd.setCursor(0,0); // Set the cursor to column 1, line 1 (counting starts at zero)
    lcd.print("speed:"); // Prints string "Display = " on the LCD
    lcd.print(speed); // Prints the measured distance
    lcd.print("cm/s"); // Prints string "Display = " on the LCD
}
}


void counter_clockwise(){
  digitalWrite(DIR, HIGH);
  for(int i = 0; i<steps_per_rev; i++)
  {
  
    digitalWrite(STEP, HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(2000);
  }
}

