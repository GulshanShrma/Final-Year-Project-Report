#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 13, 9, 10, 11, 12); //LCD pins connected to arduino pin
int buz = 5; //
int alc = 2 ; //0;
int sw = 4 ; //1;
int mt = 8; //
int mag = 6;
//above are arduino pins of connection

void setup()
{

  pinMode(buz, OUTPUT);
  pinMode(alc, INPUT);
  pinMode(sw, INPUT);
  pinMode(mt, OUTPUT);
  pinMode(mag, INPUT);
  Serial.begin(9600);

  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("Smart bike");
  lcd.setCursor(0, 1);
  lcd.print("helmet");

  digitalWrite(buz, HIGH);
  digitalWrite(mt, LOW);

  delay(1000);
  digitalWrite(mt, HIGH);
  digitalWrite(buz, LOW);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PLEASE PUT");
  lcd.setCursor(0, 1);
  lcd.print("HELMET");
  while (digitalRead(sw) == HIGH);
  digitalWrite(buz, HIGH);
  lcd.clear();
}

//Main Loop To Calculate RPM and Update LCD Display
void loop()
{

  if (digitalRead(sw) == LOW)
  {

    lcd.clear();
    digitalWrite(mt, LOW);
    lcd.setCursor(0, 0);
    lcd.print("IGNITION ON");
    while ( digitalRead(alc) == HIGH && digitalRead(sw) == LOW)
    {

      if (digitalRead(mag) == HIGH)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BIKE GOT IN");
        lcd.setCursor(0, 1);
        lcd.print("ACCIDENT");
        init_sms();
        send_data("YOUR BIKE GOT INTO THE ACCIDENT");
        send_sms();
        delay(5500);
      }
      else

      {

      }
    }
  }

  if (digitalRead(sw) == HIGH)
  { lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" ");
    lcd.setCursor(0, 0);
    lcd.print("NO HELMET");

    digitalWrite(buz, HIGH);
    delay(500);
    digitalWrite(buz, LOW);
    delay(500);
    digitalWrite(buz, HIGH);
    delay(500);
    digitalWrite(buz, LOW);
    delay(500);
    digitalWrite(buz, HIGH);
    delay(500);

    digitalWrite(buz, LOW);
    delay(500);
    digitalWrite(buz, HIGH);
    delay(500);

    if (digitalRead(sw) == HIGH)
    {
      digitalWrite(mt, HIGH);
      while ( digitalRead(alc) == HIGH && digitalRead(sw) == HIGH)
      {
        if (digitalRead(mag) == HIGH)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("BIKE GOT IN");
          lcd.setCursor(0, 1);
          lcd.print("ACCIDENT");

          init_sms();
          send_data("YOUR BIKE GOT INTO THE ACCIDENT");
          send_sms();

          delay(5500);
        }
        else

        {

        }

      }

    }
  }

  if (digitalRead(alc) == LOW)
  { lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" ");
    lcd.setCursor(0, 0);
    lcd.print("ALCOHOL DETECTED");

    digitalWrite(buz, HIGH);
    delay(500);
    digitalWrite(buz, LOW);
    delay(500);
    digitalWrite(buz, HIGH);
    delay(500);
    digitalWrite(buz, LOW);
    delay(500);
    digitalWrite(buz, HIGH);

    delay(500);
    digitalWrite(buz, LOW);
    delay(500);
    digitalWrite(buz, HIGH);
    delay(500);

    if (digitalRead(alc) == LOW)
    {
      digitalWrite(mt, HIGH);
      while ( digitalRead(alc) == LOW )
      {
        if (digitalRead(mag) == HIGH)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("BIKE GOT IN");
          lcd.setCursor(0, 1);
          lcd.print("ACCIDENT");
          init_sms();
          send_data("YOUR BIKE GOT INTO THE ACCIDENT");
          send_sms();

          delay(5500);
        }
        else

        {

        }
      }
    }
  }
}

void init_sms()
{
  Serial.println("AT + CMGF = 1");
  delay(200);
  Serial.println("AT + CMGS = \"+918684884488\"");
  delay(200);
}
void send_data(String message)
{
  Serial.println(message);
  delay(200);
}
void send_sms()
{
  Serial.write(26);
}
