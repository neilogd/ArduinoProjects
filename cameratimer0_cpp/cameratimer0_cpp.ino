int displayPins[] = 
{
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

int delayPotAnalog = 0;
int triggerPin = 13;
int flashPin = 11;

long initialDelay = 95000;     // 95ms.
long singleUnitDelay = 2500;   // 2.5ms

void setup() {
  // Setup display pin modes.
  for(int i = 0; i < 10; ++i)
  {
    int pin = displayPins[i];
    pinMode(pin, OUTPUT);
  }
  
  pinMode(flashPin, OUTPUT);
}

void displayValue(int value)
{
  for(int i = 0; i < 10; ++i)
  {
    int pin = displayPins[i];
    digitalWrite(pin, (value > i) ? HIGH : LOW);
  }
}

void accurateDelay(long microseconds)
{
  if(microseconds > 16383)
  {
    delay(microseconds / 1000);  
  }
  else
  {
    delayMicroseconds(microseconds);
  }
}

void triggerShutter()
{
  displayValue(0);
  for(int i = 0; i < 5; ++i)
  {
    int pin = displayPins[i];
    digitalWrite(pin, HIGH);
  }
}

void triggerFlash()
{
  /*
  for(int i = 5; i < 10; ++i)
  {
    int pin = displayPins[i];
    digitalWrite(pin, HIGH);
  }
  */
  digitalWrite(flashPin, HIGH);
  digitalWrite(flashPin, LOW);
}

static long lastDelayMultiple = -1;
void loop()
{ 
  // Grab delay pot.
  int analogValue = analogRead(delayPotAnalog);
  long delayMultiple = analogValue / (1024 / 10);
  if(delayMultiple > 10)
  {
    delayMultiple = 10;
  }
  
  if(delayMultiple != lastDelayMultiple)
  {
    // write value to display.
    displayValue(delayMultiple);
    lastDelayMultiple = delayMultiple;
  }
  
  if(digitalRead(triggerPin) == HIGH)
  {
    long triggerDelay = delayMultiple == 0 ? 5000 : singleUnitDelay * delayMultiple;
    accurateDelay(initialDelay + triggerDelay);   
    triggerFlash();   
    while(digitalRead(triggerPin) == HIGH);
  }
}

