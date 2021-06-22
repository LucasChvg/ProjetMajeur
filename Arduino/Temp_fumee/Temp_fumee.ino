#include <DHT.h>
#include <DHT_U.h>

#include <Wire.h> 

#define DHTPIN 2    // Changer le pin sur lequel est branché le DHT
#define DHTTYPE DHT11     // DHT 11
#define SLAVE_ADDRESS 0x12 //communication I2C


/************************Hardware Related Macros************************************/
#define         RL_VALUE                     (5)     //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR          (9.83)  //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
                                                     //which is derived from the chart in datasheet

/***********************Software Related Macros************************************/
#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)   //define the time interval(in millisecond) between each samples in the
                                                     //calibration phase
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interval(in millisecond) between each samples in 
                                                     //normal operation
/*****************************Globals***********************************************/        
float           Ro           =  10;                 //Ro is initialized to 10 kilo ohms



DHT dht(DHTPIN, DHTTYPE); 

int redLed = 12;
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A2;
// Your threshold value
int sensorThres = 95;

int VAL_TEMP = 0;
int VAL_GAZ = 0;
int i = 0;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);

  Serial.begin(9600);
  dht.begin();

  Serial.print("Calibrating...\n");                
  Ro = MQCalibration(smokeA0);                       //Calibrating the sensor. Please make sure the sensor is in clean air 
                                                    //when you perform the calibration                    
  Serial.print("Calibration is done...\n"); 
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");

  Wire.begin(SLAVE_ADDRESS);
 
  Wire.onRequest(sendData);
}

void loop() {
  
  int smokeSensor = analogRead(smokeA0);

  VAL_GAZ = smokeSensor;

  Serial.print("Smoke sensor: ");
  Serial.println(smokeSensor);

  if (smokeSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }

  // Lecture du taux d'humidité
  float h = dht.readHumidity();
  // Lecture de la température en Celcius
  float t = dht.readTemperature();
  VAL_TEMP = (int)t;
  
  // Stop le programme et renvoie un message d'erreur si le capteur ne renvoie aucune mesure
  if (isnan(h) || isnan(t)) {
    Serial.println("Echec de lecture !");
    return;
  }

  Serial.print("Humidite: "); 
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");

  
  delay(1000);
}

void sendData(){
  if(i==0){
    send_temp();
    i=1;
  }else{
    send_gaz();
    i=0;
  }
}
void send_temp(){
    Wire.write(VAL_TEMP);
}
void send_gaz(){
    Wire.write(VAL_GAZ);
}


/****************** MQResistanceCalculation ****************************************
Input:   raw_adc - raw value read from adc, which represents the voltage
Output:  the calculated sensor resistance
Remarks: The sensor and the load resistor forms a voltage divider. Given the voltage
         across the load resistor and its resistance, the resistance of the sensor
         could be derived.
************************************************************************************/ 
float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}

/***************************** MQCalibration ****************************************
Input:   mq_pin - analog channel
Output:  Ro of the sensor
Remarks: This function assumes that the sensor is in clean air. It use  
         MQResistanceCalculation to calculates the sensor resistance in clean air 
         and then divides it with RO_CLEAN_AIR_FACTOR. RO_CLEAN_AIR_FACTOR is about 
         10, which differs slightly between different sensors.
************************************************************************************/ 
float MQCalibration(int mq_pin)
{
  int i;
  float val=0;

  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {            //take multiple samples
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value

  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 

  return val; 
}
/*****************************  MQRead *********************************************
Input:   mq_pin - analog channel
Output:  Rs of the sensor
Remarks: This function use MQResistanceCalculation to caculate the sensor resistenc (Rs).
         The Rs changes as the sensor is in the different consentration of the target
         gas. The sample times and the time interval between samples could be configured
         by changing the definition of the macros.
************************************************************************************/ 
float MQRead(int mq_pin)
{
  int i;
  float rs=0;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs/READ_SAMPLE_TIMES;

  return rs;  
}
