// written by Bereket Kebede
// Dextrous robotics


const int DIR = 6;
const int STEP = 7;
const int  steps_per_rev = 2000;

void setup()
{
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
}
void loop()
{
  // 400 works
  digitalWrite(DIR, HIGH);
  Serial.println("Spinning Clockwise...");
  
  for(int i = 0; i<steps_per_rev; i++)
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(5000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(5000);
  }
  // delay(1000); 
  
}