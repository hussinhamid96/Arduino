#include <IRremote.h>
#include <Servo.h>

#define RECEIVE_PIN 11
#define LED_PIN 5

//check is used to prevent from redundant entry
int check = 0;

//declare vairable for servo and irreicever and for decode results
Servo servo;
IRrecv irreceiver(RECEIVE_PIN);
decode_results results;

void setup() {
  
  Serial.begin(9600);
  //servo attach to pin 9
  servo.attach(9);
  servo.write(90);
  //turn on irreceiver and led
  irreceiver.enableIRIn();
  pinMode(LED_PIN, OUTPUT);

}
  // put your main code here, to run repeatedly:
 
void(* resetFunc) (void) = 0;

void loop() {

  if(irreceiver.decode(&results)){
    int idea = results.value;
    Serial.println(idea,HEX);
    //0x7A85 is for button 3 its used to lock 
    if(idea == 0x7A85){
      if(check == 0){
        //led will turn off if door lock is lock
        digitalWrite(LED_PIN,LOW);
        
        for(int angle = 90; angle < 180; angle++){
          servo.write(angle);
          delay(10);
          
        }
        check =1;
       }      
    }
    //0x18E7 is for button 2 its used to unlock 
    if(idea == 0x18E7){
      if(check == 1){
        //led will turn on if door lock is unlock
        digitalWrite(LED_PIN,HIGH);
        
        for(int angle = 180; angle > 90; angle--){
          servo.write(angle);
          delay(10);
        }
        
        check = 0;
      }
      
     }   
    //resume() used to get the next data from remote
    irreceiver.resume();
  }
  
  
}
