//라인트레인싱 센서
#define in_1 13
#define in_2 14
#define in_3 15
//모터 정의
#include <L298Drv.h>
L298Drv Motor0(7, 22); //왼쪽 모터
L298Drv Motor1(8, 23); //오른쪽 모터
L298Drv Motor2(9, 24);


#define sensor1 analogRead(in_3) //D1,K1,IN3 왼쪽 센서
#define sensor2 analogRead(in_2) //D2,K2,IN2 가운대 센서
#define sensor3 analogRead(in_1) //D3,K3,IN3 오른쪽 센서
#define THRESHOLD0 int(120)//문턱값
const int gpin1 = 0; //오른쪽
const int gpin2 = 1; //왼쪽


void setup() {
  analogReference(DEFAULT);
  Serial.begin(9600);
  pinMode(10, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
}

double getUltrasonicSensor(void){
  unsigned long duration;
  digitalWrite(11, HIGH);
  delayMicroseconds(30);
  digitalWrite(11, LOW);
  duration = pulseIn(10, HIGH , 30000UL);
  return duration*0.17;
  
}

double getUltrasonicSensor2(void){
  unsigned long duration1;
  digitalWrite(13, HIGH);
  delayMicroseconds(30);
  digitalWrite(13, LOW);
  duration1 = pulseIn(12, HIGH , 30000UL);
  return duration1*0.17;
}


void loop() {
  method0();
  method1();
  method2();
  method3();
  method4();
}


void method0(){ //박스 시작
  while(true){
  if(sensor1 > THRESHOLD0 && sensor2 > THRESHOLD0 && sensor3 > THRESHOLD0 ){ 
    Motor0.drive(250);
    Motor1.drive(250);
  }
  else if(sensor1 < THRESHOLD0 && sensor2 < THRESHOLD0 && sensor3 < THRESHOLD0 ){
    Motor0.drive(250);
    Motor1.drive(250);
  }
  else if (sensor1 > THRESHOLD0 && sensor2 < THRESHOLD0 && sensor3 > THRESHOLD0){
    break;
  }
  }
  
}


void method1(){ //검검검 까지 라인 트레이싱
  while(true){
    if (sensor1 > THRESHOLD0 && sensor2 < THRESHOLD0 && sensor3 > THRESHOLD0){
      Motor0.drive(250);
      Motor1.drive(250);
    }
    else if (sensor1 < THRESHOLD0 && sensor2 > THRESHOLD0 && sensor3 > THRESHOLD0){
      Motor0.drive(-50);
      Motor1.drive(250);  
    }
    //검 흰 흰 
    else if (sensor1 < THRESHOLD0 && sensor2 < THRESHOLD0 && sensor3 > THRESHOLD0){
      Motor0.drive(-250);
      Motor1.drive(250);  
    }
    //검 검 흰 
    else if(sensor1 > THRESHOLD0 && sensor2 > THRESHOLD0 && sensor3 < THRESHOLD0){
      Motor0.drive(250);
      Motor1.drive(-50);
    }
    //흰 흰 검
    else if (sensor1 > THRESHOLD0 && sensor2 < THRESHOLD0 && sensor3 < THRESHOLD0){
      Motor0.drive(250);
      Motor1.drive(-250);  
    }
    //흰 검 검 
    else if(sensor1 < THRESHOLD0 && sensor2 < THRESHOLD0 && sensor3 < THRESHOLD0){ 
      break;
    }  
    //검 검 검 
  }
  
}

void method2(){// 검검검~언덕길 까지의 라인 트레이싱
  while(true){
    if (sensor1 > THRESHOLD0 && sensor2 < THRESHOLD0 && sensor3 > THRESHOLD0){
      break;
    }
    //흰 검 흰
    else if(sensor1 < THRESHOLD0 && sensor2 < THRESHOLD0 && sensor3 < THRESHOLD0){ 
      Motor0.drive(250);
      Motor1.drive(250);
    }
    //검 검 검
    else if (sensor1 < THRESHOLD0 && sensor2 > THRESHOLD0 && sensor3 > THRESHOLD0){
      Motor0.drive(-50);
      Motor1.drive(250);  
    }
    //검 흰 흰 
    else if(sensor1 > THRESHOLD0 && sensor2 > THRESHOLD0 && sensor3 < THRESHOLD0){
      Motor0.drive(250);
      Motor1.drive(-50);
    }
    //흰 흰 검
    else if(sensor1 > THRESHOLD0 && sensor2 > THRESHOLD0 && sensor3 > THRESHOLD0){ 
      break;
    }  
    //흰 흰 흰
  }
  
}


void method3(){
    Motor0.drive(250);// 느리게 직진
    Motor1.drive(250);
    delay(5000);
}

void method4() {
  while(true){
  int rightsensor = analogRead(gpin1); //오른쪽
  int leftsensor = analogRead(gpin2); //왼쪽
    if(rightsensor > 400 && leftsensor > 400){ //적외선 센서 모두 경기장 내부일 때)
      if (getUltrasonicSensor() < 250){
        if(sensor1 < THRESHOLD0 && sensor2 < THRESHOLD0 && sensor3 < THRESHOLD0){ 
          Motor0.drive(250);
          Motor1.drive(250);
          delay(100);
          Serial.println(getUltrasonicSensor());
          } // 경기장 안에있으면서 상대가 250 이내에 있고 센서값 모두 검은색일시 직진
        else{
          Motor0.drive(-250);
          Motor1.drive(-250);
          delay(500);
          Serial.println(getUltrasonicSensor());
        } //경기장 안에 있으면서 상대가 250이내에 있지만 센서값이 하나라도 흰색이 나오면 후진 잠깐
      }
    /////////////    상대방이 초음파 센서에 감지 O ↑ 감지 X ↓  ////////////////////////// 
      else {
        if(sensor1 < THRESHOLD0 && sensor2 < THRESHOLD0 && sensor3 < THRESHOLD0){
          if(getUltrasonicSensor2() > 250){
            Motor0.drive(-150);
            Motor1.drive(150);
            delay(100);
          }
          else{
            Motor0.drive(150);
            Motor1.drive(-150);
            delay(100);
          }
        } //경기장 내부에 있으면서 상대가 250범위 밖에있으면서 센서값 모두 검은색일시 회전
        
        else{
          Motor0.drive(-250);
          Motor1.drive(-250);
          delay(500);
          Serial.println(getUltrasonicSensor());
        } //경기장 내부에 있으면서 상대방이 250 범위 밖에있을 시 센서값이 하나라도 흰색이 나오면 후진
      }
    } 
    else if (rightsensor < 400 && leftsensor > 400) { //오른쪽 적외선 센서가 흰선에 닿을경우
       Motor0.drive(50);
       Motor1.drive(250);
       delay(1000);
       Motor0.drive(250);
       Motor1.drive(250);
       delay(500);
    }
    else if (rightsensor > 400 && leftsensor < 400) { //왼쪽센서가 닿을경우
       Motor0.drive(250);
       Motor1.drive(50);
       delay(1000);
       Motor0.drive(250);
       Motor1.drive(250);
       delay(500);
    }
    else if (rightsensor < 400 && leftsensor < 400) { //왼쪽센서가 닿을경우
       Motor0.drive(250);
       Motor1.drive(250);
       delay(1000);
    }
  }

  
}
