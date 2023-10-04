#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int ss, mm, hh, MM, DD, YYYY, AP;
int k = 0;
const int tempSensorPin = A1;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
  if (k <= 0)
  {
    Details();
  }

  ss = ss + 1;

  if (ss == 60)
  {
    ss = 0;
    mm = mm + 1;

    if (mm == 60)
    {
      mm = 0;
      hh = hh + 1;

      if (hh == 12)
      {
        AP = AP + 1;
        printTime2();

        if (AP % 2 == 0)
        {
          DD = DD + 1;
        }

        if (DD == 28)
        {
          DD = 1;
          MM = MM + 1;

          if (MM == 13)
          {
            MM = 1;
            YYYY = YYYY + 1;
          }
        }
      }

      if (hh == 13)
      {
        hh = 1;
      }
    }
  }

  int sensorValue = analogRead(tempSensorPin);
  float tempC = map(sensorValue, 0, 1023, 0, 100); 

  
  printTime2();

  
  lcd.setCursor(0, 3);
  lcd.print("Temp: ");
  lcd.print(tempC);
  lcd.print(" C");

  delay(1000);
}

void line()
{
  Serial.println("");
}

void Details()
{
  Serial.println("Entrer une heure:");

  while (Serial.available() == 0);
  hh = Serial.parseInt();


  line();

  Serial.println("Entrer les minutes:");
  while (Serial.available() == 0);
  mm = Serial.parseInt();

  line();

  Serial.println("Entrer les secondes:");
  while (Serial.available() == 0);
  ss = Serial.parseInt();

  line();

  Serial.println("Entrer matin (0) ou apres-midi (1)");
  while (Serial.available() == 0);
  AP = Serial.parseInt();

  line();

  Serial.println("Entrer le mois:");
  while (Serial.available() == 0);
  MM = Serial.parseInt();

  line();

  Serial.println("Entrer le jour:");
  while (Serial.available() == 0);
  DD = Serial.parseInt();

  line();

  Serial.println("Entrer l'annee:");
  while (Serial.available() == 0);
  YYYY = Serial.parseInt();

  line();

  k = k + 1;
}

void printTime(int x)
{
  if (x <= 9)
  {
    lcd.print("0");
    lcd.print(x);
  }
  else
  {
    lcd.print(x);
  }
}

void printTime2()
{
  lcd.setCursor(0, 0);
  printTime(hh);
  lcd.print(":");
  printTime(mm);
  lcd.print(":");
  printTime(ss);
  lcd.print(" ");
  
  if (AP % 2 == 0)
  {
    lcd.print("AM");
  }

  if (AP % 2 == 1)
  {
    lcd.print("PM");
  }

  lcd.setCursor(0, 1);
  printTime(MM);
  lcd.print("/");
  printTime(DD);
  lcd.print("/");
  printTime(YYYY);
  lcd.print("....");
  
  delay(1000);
} 