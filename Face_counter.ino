/***************************************************
 HUSKYLENS An Easy-to-use AI Machine Vision Sensor
 <https://www.dfrobot.com/product-1922.html>
 
 ***************************************************
 This example shows the basic function of library for HUSKYLENS via Serial.
 
 Created 2020-03-13
 By [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://wiki.dfrobot.com/HUSKYLENS_V1.0_SKU_SEN0305_SEN0336#target_23>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
int counter = 0;
int ID0 = 0;
HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX
//HUSKYLENS green line >> Pin 10; blue line >> Pin 11
void printResult(HUSKYLENSResult result);

void setup() {
    Serial.begin(115200);
    mySerial.begin(9600);
    while (!huskylens.begin(mySerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
}

void loop() 
{
    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if(!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
    else
    {
        Serial.println(F("###########"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);
        }  
    }
         if (huskylens.request())
         {
          
            Serial.println("#######");
            Serial.println(String()+F(" blocks et arrows = ID0. Count:")+huskylens.count(ID0));
            for (int i = 0; i < huskylens.count(); i++)
            {
                HUSKYLENSResult result = huskylens.get(ID0, i);
                printResult(result);
            }

           
         }         
          
          else
          {
            Serial.println("Fail to request objects from Huskylens!");
          }

           if (huskylens.count(ID0) == 1)
            {
                Serial.println("###1###");
                counter++;
                Serial.println(String()+F("count moi ça mafia:")+counter);
            }
            delay(1000);
    
 }

void printResult(HUSKYLENSResult result){
   
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
        
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
        
    }
    else{
        Serial.println("Object unknown!");
        
    }

    
    
   /* if(result.ID == 0 )
    {
      
      count++;      
      Serial.println(count);       
    }
    
    else if ((result.ID >= 1) && (result.ID != lastID))
    {
      Serial.println("reconnu");
      
    }
     
     / count--;
     // Serial.println(count);
     
    
    return 0;  */  
}
