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

void setup() {
  analogReference(DEFAULT);
  Serial.begin(9600);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
}

double getUltrasonicSensor(void){
  unsigned long duration;
  digitalWrite(13, HIGH);
  delayMicroseconds(30);
  digitalWrite(13, LOW);
  duration = pulseIn(12, HIGH , 30000UL);
  return duration*0.17;
  
}

void loop() {
  method0();
  method1();
  method2();
  method3();
  method4();
  method5();
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
  return 0;
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
  return 0;
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
  return 0;
}

void method3(){//원판길
  while(true){
    Motor0.drive(250);// 느리게 직진
    Motor1.drive(250);
    delay(2500);
    Motor0.drive(-250);//반시계
    Motor1.drive(250);
    delay(530);
    Motor0.drive(250);// 느리게 직진
    Motor1.drive(250);
    delay(300);
    while(sensor1 < THRESHOLD0 ){
      Motor0.drive(250);// 느리게 직진
      Motor1.drive(250);
    } 
    Motor0.drive(250);//시계
    Motor1.drive(-250);
    delay(700);    
    while(sensor3 < THRESHOLD0 ){
      Motor0.drive(250);//원 커브
      Motor1.drive(157);
    }
    Motor0.drive(250);//
    Motor1.drive(250);   
    delay(200);
    Motor0.drive(-250);
    Motor1.drive(250);// 90도 회전
    delay(770);
    Motor0.drive(250);
    Motor1.drive(250);
    delay(800);
    break;
  }
  return 0;
}

void method4(){ //원판길 ~ 검검검 넘어까지
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
      Motor0.drive(250);
      Motor1.drive(250); 
      delay(1000);
      break;
    }  
    //검 검 검 
  }
  return 0;
}


void method5(){ // 끝까지 라인 트레이싱
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
    else if(sensor1 > THRESHOLD0 && sensor2 > THRESHOLD0 && sensor3 < THRESHOLD0){
      Motor0.drive(250);
      Motor1.drive(-50);
    }
    //흰 흰 검
    else if(sensor1 < THRESHOLD0 && sensor2 < THRESHOLD0 && sensor3 < THRESHOLD0){   
      Motor0.drive(250);
      Motor1.drive(250); 
      delay(1500);
      Motor0.drive(0);
      Motor1.drive(0); 
      delay(1000000);
      break;
    }
  }
  return 0;
}
