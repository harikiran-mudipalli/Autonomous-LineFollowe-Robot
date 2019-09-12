int a,b,c,d,e,f,g;
void setup() {
  // I used 8 IR sensor pairs array 
  // Below are the pin numbers I connected onto arduino Mega board
  pinMode(31, INPUT); 
  pinMode(33, INPUT); 
  pinMode(35, INPUT);
  pinMode(37, INPUT);
  pinMode(39, INPUT);
  pinMode(41, INPUT);
  pinMode(43, INPUT);
  // I used two motors for movement
  // Below are the motor pins
  pinMode(44, OUTPUT); //right motor 1
  pinMode(46, OUTPUT); //right motor 2
  pinMode(48, OUTPUT); //left motor 1
  pinMode(50, OUTPUT); //left motor 2
  // pwm - Pulse Width Modulation
  // these pins are used to control the speed of the motor in this project
  // These work on all analog pin and digital pins with '~' symbol 
  pinMode(3, OUTPUT); //pwm pin for left motor to control speed
  pinMode(2, OUTPUT); //pwm pin for right motor
  Serial.begin(9600);
}

void loop()
{
  WELCOME:
  
a = digitalRead(31); // Left most IR pair on sensor array
b = digitalRead(33);
c = digitalRead(35);
d = digitalRead(37);// Middel IR pair on sensor array
e = digitalRead(39);
f = digitalRead(41);
g = digitalRead(43); // Right most IR pair on sensor array

// Condition for the robot to move forward when there is a straight line
if(a==HIGH && g==HIGH && ( d==LOW || e==LOW ))
{
straight();
Serial.println("Straight");
}

else if( (a==LOW || b==LOW) && (d==LOW || e==LOW) && (g==LOW || f==LOW)  )
{
  analogWrite(2,200);
  analogWrite(3,200);
  digitalWrite(48,HIGH);
  digitalWrite(50,LOW);
  digitalWrite(44,HIGH);
  digitalWrite(46,LOW);
  delay(20);
//this will allow the bot move a very minute distance on the white line for confirmation ..... adjust according to your motor
  if( (digitalRead(31)==LOW && digitalRead(33)==LOW) && ( digitalRead(37)==LOW && digitalRead(39)==LOW ) && ( digitalRead(41)==LOW && digitalRead(43)==LOW ) ){
//if it enters here it is confirmed that we have a left and right turn......as per my code i gave most priority to left of all =>i havent checked wether i have another line before it (Junction +)
  analogWrite(2,200);
  analogWrite(3,200);
  digitalWrite(48,HIGH);
  digitalWrite(50,LOW);
  digitalWrite(44,HIGH);
  digitalWrite(46,LOW);
  delay(140);
  
  leftturn();
  }
  else{
    goto WELCOME;
    }
}

//This is the case where i have right path noticed

else if( a==HIGH && (g==LOW || f==LOW) && (e==LOW || d==LOW))
{
  analogWrite(2,200);
  analogWrite(3,200);
  digitalWrite(48,HIGH);
  digitalWrite(50,LOW);
  digitalWrite(44,HIGH);
  digitalWrite(46,LOW);
  delay(25);

  //By going a very minute distance i verify 
  
  if( (digitalRead(31)==HIGH && digitalRead(33)==HIGH) && ( digitalRead(37)==LOW && digitalRead(39)==LOW ) && ( digitalRead(41)==LOW || digitalRead(43)==LOW ) ){
  //If it enters in here then it is verified
  analogWrite(2,200);
  analogWrite(3,200);
  digitalWrite(48,HIGH);
  digitalWrite(50,LOW);
  digitalWrite(44,HIGH);
  digitalWrite(46,LOW);
  delay(140); 
  //Now i take bot little more distance straight and check wether i have a straight line along with right
  if ( ( digitalRead(37)==LOW || digitalRead(39)==LOW ) && ( digitalRead(43)==HIGH ) && (digitalRead(31)==HIGH ) ){
//If it enters here it means i also have a straight line after right=>my priority is straight than right
      //My prority in my coding is Left > Straight > Right
     
  
  straight();
  }

  else if( (digitalRead(31)==HIGH && digitalRead(33)==HIGH) && ( digitalRead(37)==HIGH && digitalRead(39)==HIGH ) && ( digitalRead(41)==HIGH && digitalRead(43)==HIGH ) ) {
//If it enters here it means that there is no straight line after right => only possibility is Right   
  analogWrite(2,200);
  analogWrite(3,200);
  digitalWrite(48,HIGH);
  digitalWrite(50,LOW);
  digitalWrite(44,HIGH);
  digitalWrite(46,LOW);
  delay(30);
       rightturn();
    }
  
  }
}
}
  //This is how i take turns

void leftturn(){
  while(digitalRead(31)==HIGH){
    analogWrite(2,200);
    analogWrite(3,200);
    digitalWrite(48, LOW);
    digitalWrite(50, HIGH);
    digitalWrite(44, HIGH);
    digitalWrite(46, LOW);
    delay(1);
    digitalWrite(48, LOW);
    digitalWrite(50, LOW);
    digitalWrite(44, LOW);
    digitalWrite(46, LOW);
    delay(1);
    }
    while(digitalRead(35)==HIGH || digitalRead(37)==HIGH){
      analogWrite(2,200);
  analogWrite(3,200);
    digitalWrite(48, LOW);
    analogWrite(50, 180);
    analogWrite(44, 180);
    digitalWrite(46, LOW);
    delay(1);
    digitalWrite(48, LOW);
    digitalWrite(50, LOW);
    digitalWrite(44, LOW);
    digitalWrite(46, LOW);
    delay(3);
    }
    if(digitalRead(39)==LOW){
      analogWrite(2,200);
  analogWrite(3,200);
      analogWrite(48, HIGH);
      digitalWrite(50, LOW);
      digitalWrite(44, LOW);
      analogWrite(46, 150);
      delay(2);
      
      digitalWrite(48, LOW);
      digitalWrite(50, LOW);
      digitalWrite(44, LOW);
      digitalWrite(46, LOW);
      delay(2);
      }
    
 }


void straight()
{
  if( digitalRead(39)==HIGH || digitalRead(35)==LOW ){
    analogWrite(2,250);
  analogWrite(3,250);
    digitalWrite(48, HIGH);
    digitalWrite(50, LOW);
    digitalWrite(44, HIGH);
    digitalWrite(46, LOW);
    delay(1);
    digitalWrite(48, LOW);
    digitalWrite(50, LOW);
    analogWrite(44, 180);
    digitalWrite(46, LOW);
    delay(1);
    return;
  }
  if(digitalRead(37)==HIGH || digitalRead(41)==LOW ){
    analogWrite(2,250);
  analogWrite(3,250);
    digitalWrite(48, HIGH);
    digitalWrite(50, LOW);
    digitalWrite(44, HIGH);
    digitalWrite(46, LOW);
    delay(1);
    analogWrite(48, 180);
    digitalWrite(50, LOW);
    digitalWrite(44, LOW);
    digitalWrite(46, LOW);
    delay(1);
    return;
  }
 analogWrite(2,250);
  analogWrite(3,250);
    digitalWrite(48, HIGH);
    digitalWrite(50, LOW);
    digitalWrite(44, HIGH);
    digitalWrite(46, LOW);
    delay(1);
    
  }

//Turnover means when i reach dead-end i return back
void turnover(){
  while(digitalRead(43)==HIGH){
    analogWrite(2,250);
  analogWrite(3,250);
    digitalWrite(48, HIGH);
    digitalWrite(50, LOW);
    digitalWrite(44, LOW);
    digitalWrite(46, HIGH);
    delay(1);
    digitalWrite(48, LOW);
    digitalWrite(50, LOW);
    digitalWrite(44, LOW);
    digitalWrite(46, LOW);
    delay(1);
    }

    while(digitalRead(39)==HIGH || digitalRead(41)==HIGH){
      analogWrite(2,250);
  analogWrite(3,250);
    analogWrite(48, 180);
    digitalWrite(50, LOW);
    digitalWrite(44, LOW);
    analogWrite(46, 180);
    delay(1);
    digitalWrite(48, LOW);
    digitalWrite(50, LOW);
    digitalWrite(44, LOW);
    digitalWrite(46, LOW);
    delay(3);
    }
    if(digitalRead(37)==LOW){
      analogWrite(2,250);
  analogWrite(3,250);
      digitalWrite(48, LOW);
      analogWrite(50, 150);
      analogWrite(44, 150);
      digitalWrite(46, LOW);
      delay(2);
      digitalWrite(48, LOW);
      digitalWrite(50, LOW);
      digitalWrite(44, LOW);
      digitalWrite(46, LOW);
      delay(3);
      }
      
      
  }

void rightturn(){
    while(digitalRead(43)==HIGH){
      analogWrite(2,250);
  analogWrite(3,250);
    digitalWrite(48, HIGH);
    digitalWrite(50, LOW);
    digitalWrite(44, LOW);
    digitalWrite(46, HIGH);
    delay(1);
    digitalWrite(48, LOW);
    digitalWrite(50, LOW);
    digitalWrite(44, LOW);
    digitalWrite(46, LOW);
    delay(1);
    }

    while(digitalRead(39)==HIGH || digitalRead(41)==HIGH){
      analogWrite(2,250);
  analogWrite(3,250);
    analogWrite(48, 180);
    digitalWrite(50, LOW);
    digitalWrite(44, LOW);
    analogWrite(46, 180);
    delay(1);
    digitalWrite(48, LOW);
    digitalWrite(50, LOW);
    digitalWrite(44, LOW);
    digitalWrite(46, LOW);
    delay(3);
    }
    if(digitalRead(37)==LOW){
      /*digitalWrite(lm1, LOW);
      analogWrite(lm2, 150);
      analogWrite(rm1, 150);
      digitalWrite(rm2, LOW);
      delay(1);*/
      digitalWrite(48, LOW);
      digitalWrite(50, LOW);
      digitalWrite(44, LOW);
      digitalWrite(46, LOW);
      delay(2);
      }
     
 }
