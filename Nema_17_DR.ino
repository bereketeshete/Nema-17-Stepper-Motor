// written by Bereket Kebede
// Dextrous robotics


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


void setup()
{
  StartTime = millis();
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
}
void loop()
{
  // 400 works
  digitalWrite(DIR, HIGH);
  //Serial.println("Spinning Clockwise...");
  
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
  speed = radius * ang_speed;

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
}

