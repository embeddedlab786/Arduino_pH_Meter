#include <LiquidCrystal.h>  
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 

#define SensorPin A0      //pH meter Analog output to Arduino Analog Input 0

float calibration_value = 21.34 + 0.7;
unsigned long int avgValue;  //Store the average value of the sensor feedback
int buf[10], temp;

void setup(){
pinMode(SensorPin, INPUT);
  
lcd.begin(16, 2);  
lcd.clear();  
lcd.setCursor(0, 0);  
lcd.print("Welcome To");     
lcd.setCursor(0, 1);  
lcd.print("       pH Meter"); 
delay(2000);
lcd.clear(); 
}
void loop(){
  
 for(int i=0;i<10;i++){ //Get 10 sample value from the sensor for smooth the value
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++){ //sort the analog from small to large
    for(int j=i+1;j<10;j++){
      if(buf[i]>buf[j]){
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)avgValue+=buf[i];  //take the average value of 6 center sample
    
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue = -5.70 * phValue + calibration_value; //convert the millivolt into pH value
  
  lcd.setCursor(0, 0);  
  lcd.print(" pH Value: ");
  lcd.print(phValue); 
  lcd.print("  ");
      
  lcd.setCursor(1, 1); 
     if(phValue<4)                 lcd.print(" Very Acidic ");
else if(phValue>=4  && phValue<5)  lcd.print("    Acidic   ");
else if(phValue>=5  && phValue<7)  lcd.print(" Acidic-ish  ");
else if(phValue>=7  && phValue<8)  lcd.print("   Neutral   ");
else if(phValue>=8  && phValue<10) lcd.print("Alkaline-ish ");
else if(phValue>=10 && phValue<11) lcd.print("  Alkaline   ");
else if(phValue>=11)               lcd.print("Very alkaline");
      
  delay(1000);
}
