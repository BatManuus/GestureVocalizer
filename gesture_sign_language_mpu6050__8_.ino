#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;
#define adc1 A0
#define adc2 A1
int flex2=0,flex1=0;
void setup() 
{  
 Serial.begin(9600);
 Serial.println("Initialize MPU6050");
 while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
 {
  Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
  delay(500);
 }
 checkSettings();
 
}
void checkSettings()
{
 
 Serial.println();  
 Serial.print(" * Sleep Mode:            ");
 Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
 Serial.print(" * Clock Source:          ");
 switch(mpu.getClockSource())
 {
  case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
  case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
  case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
  case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
  case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
  case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
  case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
 }
 Serial.print(" * Accelerometer offsets: ");
 Serial.print(mpu.getAccelOffsetX());
 Serial.print(" / ");
 Serial.print(mpu.getAccelOffsetY());
 Serial.print(" / ");
 Serial.println(mpu.getAccelOffsetZ());
 Serial.println();
}

void loop()
{
  flex1=analogRead(adc1);
  flex2=analogRead(adc2);
  delay(10);
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
  Serial.print(" Xnorm = ");
  Serial.print(normAccel.XAxis);
  Serial.print(" Ynorm = ");
  Serial.print(normAccel.YAxis);
  Serial.print(" Znorm = ");
  Serial.println(normAccel.ZAxis);
  Serial.print(flex2);
  Serial.print("-");
  Serial.print(flex1);
  Serial.print("-");
  delay(1000);
  
  if(flex2<=890)
  {
    if (flex1<50)
    {   
      if(normAccel.XAxis>5){Serial.println("DOWN");delay(500);}
      else if(normAccel.XAxis<-3){Serial.println("UP");}
      else if(normAccel.YAxis>3){Serial.println("ME");}
      else if(normAccel.YAxis<-3){Serial.println("YOU");}
    } 
    else
    {
      if(normAccel.XAxis<-3){Serial.println("DANGER");}        
      else if(normAccel.YAxis<-3){Serial.println("ROCK");}    
    }
  }  
  else  
  {
    if (flex1<50)
    {     
      if(normAccel.XAxis>5){Serial.println("HELP");delay(500);}
      else if(normAccel.XAxis<-3){Serial.println("VICTORY");}
      //else if(normAccel.YAxis>3){Serial.println("");}
      else if(normAccel.YAxis<-3){Serial.println("SCISSORS");}
    }
    else
    {
      if(normAccel.XAxis>5){Serial.println("DOWN");delay(500);}
      else if(normAccel.XAxis<-3){Serial.println("UP");}
      //else if(normAccel.YAxis>3){Serial.println("");}
      else if(normAccel.YAxis<-3){Serial.println("YOU");}      
    }
  }
  /*if (flex2>820)
  {
    if(normAccel.XAxis>5){Serial.println("DOWN");delay(500);}
    else if(normAccel.XAxis<-3){Serial.println("UP");}
    //else if(normAccel.YAxis>3){Serial.println("");}
    else if(normAccel.YAxis<-3){Serial.println("YOU");}
  } 
  else 
  {
    if(normAccel.XAxis>5){Serial.println("WHY");delay(500);}
    else if(normAccel.XAxis<-3){Serial.println("WHAT");}
    //else if(normAccel.YAxis>3){Serial.println("");}
    //else if(normAccel.YAxis<-3){Serial.println("");}
  }*/
}
