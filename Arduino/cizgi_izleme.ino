#include <QTRSensors.h>

#define Kp 0.1 // Kendi deneyimlerinizle bulmanız gerekli küçük bir değer ile başlayıp, büyütebilirsiniz en kararlı Kp değerini bulana kadar.. 0.4
#define Kd 2.4 // Bunu da küçük bir değerden başlatın ve deneyimleyerek büyütün. ( Not: Kp < Kd) 2.0
#define rightMaxSpeed 94
#define leftMaxSpeed 95
#define rightBaseSpeed 65 // robot için kp ve kd değerlerini tutturduysanız şayet motorların dönmesi gereken hız budur
#define leftBaseSpeed 66 // yukarıdaki değer ile aynıdır


#define rightMotor1 2
#define rightMotor2 3
#define rightMotorPWM 9
#define leftMotor1 4
#define leftMotor2 5
#define leftMotorPWM 10


QTRSensors qtr;

const uint8_t SensorCount = 16;
unsigned int sensorValues[SensorCount];



void setup()
{
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49}, SensorCount);
  qtr.setEmitterPin(2);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);


  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode


  int i;
  for (int i = 0; i < 100; i++) { // tercihe bağlı alandır ya robotunuzu hatta yürüterek kalibre edin veya bunu otomatik yapın.
    //otomatik kalibrasyon için burasının yorumunu kaldırın
    if ( i  < 25 || i >= 75 ) {// sensörleri, karşılaşılabilecek en aydınlık ve en karanlık okumalara maruz bırakmak için sola ve sağa çevirin.
      turn_right();
    } //bu fonksiyonları yazacaz
    else {
      turn_left();
    }
    qtr.calibrate();
    delay(20);
  }
  wait(); //motorları durdur
  digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration

  delay(1000); // Ana döngüye girmeden önce botu konumlandırmak için 1 saniye bekleyin
}
int lastError = 0;
void loop()
{
  // read calibrated sensor values and obtain a measure of the line position
  // from 0 to 7000 (for a white line, use readLineWhite() instead)
  unsigned int position = qtr.readLineBlack(sensorValues);


  int error = position - 7500;
  int motorSpeed = Kp * error + Kd * (error - lastError);
  lastError = error;
  int rightMotorSpeed = rightBaseSpeed + motorSpeed;
  int leftMotorSpeed = leftBaseSpeed - motorSpeed;
  if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed;
  if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed;
  if (rightMotorSpeed < 0) rightMotorSpeed = 0;
  if (leftMotorSpeed < 0) leftMotorSpeed = 0;
  

    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(rightMotorPWM, rightMotorSpeed);

    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    analogWrite(leftMotorPWM, leftMotorSpeed);
  
}
void wait() {
      digitalWrite(rightMotor1,LOW);
    digitalWrite(rightMotor2, LOW);
   

    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    
}
void turn_left() {
      digitalWrite(rightMotor1,HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite (rightMotorPWM,rightBaseSpeed); 

    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    analogWrite (leftMotorPWM,leftBaseSpeed);
}
void turn_right() {
      digitalWrite(rightMotor1,LOW);
    digitalWrite(rightMotor2, HIGH);
    analogWrite (rightMotorPWM,rightBaseSpeed);   

    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    analogWrite (leftMotorPWM,leftBaseSpeed);    
}