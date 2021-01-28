#define MAX_ITEMS 5
const int sensor_pin1 = A0;
const int sensor_pin2 = A1;
const int sensor_pin3 = A3;
const int sensor_pin4 = A4;
const int sensor_pin5 = A5;
const int bomba_pint = 8;
const int sensor_digital_pin1 = 9;
const int sensor_digital_pin2 = 10;
const int sensor_digital_pin3 = 11;
const int sensor_digital_pin4 = 12;
const int sensor_digital_pin5 = 13;
void setup() {
   Serial.begin(9600);
   pinMode(bomba_pint, OUTPUT);
   digitalWrite(bomba_pint, LOW); 
   pinMode(sensor_digital_pin1, INPUT);
   pinMode(sensor_digital_pin2, INPUT);
   pinMode(sensor_digital_pin3, INPUT);
   pinMode(sensor_digital_pin4, INPUT);
   pinMode(sensor_digital_pin5, INPUT);
}

class SensorClass{
  private:
    int FailedSensorsDisable[MAX_ITEMS];
    int ActiveSensorsEnable[MAX_ITEMS];
  public:
    void ActiveSensors(int sensors[5], int analogPin[5], int sensors_status[5]) {
      bool flag  = false;
      int conuntFailed = 0;
      int countSuccess;
      for (int i = 0; i < 5; i++) {
        if (sensors_status[i] == 1) {
          Serial.println(i);
          Serial.println("ERROR");  
          FailedSensorsDisable[i] = analogPin[i];
          conuntFailed++;
        } else {
          ActiveSensorsEnable[i] = analogPin[i];
          countSuccess++;
          if (sensors[i] > 600 && sensors[i] <= 1012) {
            flag = true;   
          }
        }
      }
      if (flag) {
        toWater();
      }
    }
};

SensorClass SC1;
 
void loop() 
{
   int humedad_sensor1 = analogRead(sensor_pin1);
   int humedad_sensor2 = analogRead(sensor_pin2);
   int humedad_sensor3 = analogRead(sensor_pin3);
   int humedad_sensor4 = analogRead(sensor_pin4);
   //int humedad_sensor5 = analogRead(sensor_pin5);
   int sensor1_status1 = digitalRead(sensor_digital_pin1);
   int sensor1_status2 = digitalRead(sensor_digital_pin2);
   int sensor1_status3 = digitalRead(sensor_digital_pin3);
   int sensor1_status4 = digitalRead(sensor_digital_pin4);
   //int sensor1_status5 = digitalRead(sensor_digital_pin5);
   Serial.println(humedad_sensor4);
   Serial.println(sensor1_status4);
   int listSensorData[4] = {
      humedad_sensor1,
      humedad_sensor2,
      humedad_sensor3,
      humedad_sensor4,
    };
   int analogPin[4] = {
    sensor_pin1,
    sensor_pin2,
    sensor_pin3,
    sensor_pin4,
    };
   int sensors_status[4] = {
    sensor1_status1,
    sensor1_status2,
    sensor1_status3,
    sensor1_status4,
   };
   SC1.ActiveSensors(listSensorData, analogPin, sensors_status);
   delay(1000);
}

void readHumedad(int humedad_sensor1, int humedad_sensor2, int humedad_sensor3, int humedad_sensor4, int humedad_sensor5) {
  bool flag = false;
  int humedadparam = 600;
}


void toWater() 
{
   Serial.println("INICIO REGADO");
   digitalWrite(bomba_pint, HIGH);   // poner el Pin en HIGH
   //delay(600000);               // esperar 10 segundos
   delay(10000);
   digitalWrite(bomba_pint, LOW);    // poner el Pin en LOW
   delay(10000);   
   Serial.println("FIN REGADO");
}
