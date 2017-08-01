#define BLYNK_PRINT Serial
#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>
char auth[] = "your-token-here"; //diisi dengan no token yang ada di aplikasi

BLEPeripheral  blePeripheral;

int CO2_PIN = 5;
int alarm = 13;

int maxCO2 = 5000;    //min ppm of CO2 in caseof fire
int value_CO2 = 0;
int count_CO2 = 0;

const boolean DEBUG = true;   //make true to see outputs in serial monitor

void setup()
{
    pinMode(CO2_PIN,INPUT);
    pinMode(alarm,OUTPUT);
    Serial.begin(9600);
    if(DEBUG)
    {
      Serial.println("Program started");
    }

    blePeripheral.setLocalName("Fire");//nama bluetooth bebas
    blePeripheral.setDeviceName("Fire");//nama bluetooth bebas
    blePeripheral.setAppearance(384);
    Serial.println("Blynk akan mulai sekarang");
    Blynk.begin(auth, blePeripheral);
    blePeripheral.begin();

}


void loop()
{
  
  Blynk.run(); //untuk memulai blynk
  blePeripheral.poll(); //untuk mendapatkan data
    int co2 = CO2_sensor();
    if(( co2 >= maxCO2 ) ) 
    {
      if(DEBUG)
      {
        Serial.println("Fire! Fire! Fire!");  
      }
      digitalWrite(alarm,HIGH);  
    }
    else{
      digitalWrite(alarm,LOW);  
    }
    delay(2000);
}


int CO2_sensor()
{
  unsigned long Th = pulseIn(CO2_PIN, HIGH, 1004000);
  Serial.println(Th);

  Th = Th / 1000;

  if (Th > 2)
  {
    unsigned long value = ((2000 * (Th - 2)) / (Th + (1004 - Th) - 4));
    value_CO2 += value;
    count_CO2 += 1;
  }

  if (DEBUG)
  {
    Serial.print("CO2 : ");
    Serial.print(value_CO2 / count_CO2);
    float val = value_CO2 / count_CO2;
    Serial.println("ppm     ");
    Blynk.virtualWrite(V0, val);
  }

  return value_CO2 / count_CO2;
}

