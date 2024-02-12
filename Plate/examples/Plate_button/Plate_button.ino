#include <Plate.h> 
void setup()  
{
  Plate_Setup(); 
}

void loop()
{
  while(1)
  {
    delay(50);
    Serial.print("button1 = ");
    Serial.print(button(1));
    Serial.print("  button2 = ");
    Serial.print(button(2));
    Serial.print("  button3 = ");
    Serial.print(button(3));
    Serial.print("  button4 = ");
    Serial.println(button(4));
  }
}