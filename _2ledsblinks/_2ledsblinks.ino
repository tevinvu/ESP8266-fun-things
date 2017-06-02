// LED pin 4 and 5 blink 
int led5 = 5;
int led4 = 4;

void setup() {
  pinMode(led5, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  
  // OFF
  digitalWrite(led5, LOW);                                
  delay(500);             
  digitalWrite(led4, LOW);                                
  delay(300); 
  // ON
  digitalWrite(led5, HIGH); 
  delay(300); 
  digitalWrite(led4, HIGH);                                
  delay(500);       
               
}
