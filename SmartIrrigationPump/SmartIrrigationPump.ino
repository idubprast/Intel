#define BLYNK_PRINT Serial

#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>
char auth[] = "your-token-here"; //diisi dengan no token yang ada di aplikasi

BLEPeripheral  blePeripheral;

const boolean DEBUG = true;
int relayPin = 8;
int sensorPin = A0;
float nilaiSensor;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relayPin,OUTPUT);
  pinMode(sensorPin, INPUT);
  digitalWrite(relayPin, HIGH);  

  blePeripheral.setLocalName("Pump");//nama bluetooth bebas
  blePeripheral.setDeviceName("Pump");//nama bluetooth bebas
  blePeripheral.setAppearance(384);
  Serial.println("Blynk akan mulai sekarang");
  Blynk.begin(auth, blePeripheral);
  blePeripheral.begin();

  Serial.println("Menunggu untuk terhubung.........");
  

}

void loop() {
  Blynk.run(); //untuk memulai blynk
  blePeripheral.poll(); //untuk mendapatkan data
  
  nilaiSensor = analogRead(sensorPin);//membaca data dari sensor
  nilaiSensor = map(nilaiSensor, 0,1023,0,1000); //mengubah hasil kedalam rentangan 0 sampai 1000
  Serial.println(nilaiSensor);
  Blynk.virtualWrite(V0, nilaiSensor); //menampilkan hasil pada app

  if(nilaiSensor > 900){ //jika tidak ada kandungan air
    digitalWrite(relayPin, LOW); //maka pump akan menyala

  }
  else
  {
    digitalWrite(relayPin, HIGH); //jika ada kandungan air, maka pump mati
  }
  delay(250);
}

