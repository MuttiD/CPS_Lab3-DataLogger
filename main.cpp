#include "mbed.h"
#include "LM75B.h"
#include "C12832.h"

// add objects for LCD
C12832 lcd(p5, p7, p6, p8, p11);
LM75B sensor(p28,p27);

Serial pc(USBTX,USBRX);

// Create the local filesystem under the name "local" on mbed
LocalFileSystem local("local");               

int main ()
{
    
    // create variables for temperature readings
    float temp;
    float minTemp = 100.0;
    float maxTemp = -100.0;
    float totalTemp = 0;
    int numReadings = 0;

    // write temperature readings in the file
    FILE *fp = fopen("/local/temperature.txt", "w");
    
    // for loop counter
    for (int i=0; i<=10; i++){  // ten readings
        // read temperature from sensor
        temp = sensor.read();
        
        // write temperature to file
        fprintf(fp, "%.2f\n", temp);

        // minimum value
        if( temp < minTemp ) {
            minTemp = temp;
        }

        // maximum value
        if ( temp > maxTemp ) {
            maxTemp = temp;
        }
        totalTemp += temp;
        numReadings++;

        // display temperature on the LCD
        lcd.cls();
        lcd.locate(0,3);
        lcd.printf("Tempearture: %.2f C", temp);

        // wait for 7 minutes = 420 seconds
        wait(420);

        // close file
        fclose(fp);

        // calculate average temperature
        float avgTemp = totalTemp / numReadings; 

        // display values on LCD
        lcd.cls();

        lcd.locate(0,0);
        lcd.printf("Min Temp: %.2f C", minTemp);
        lcd.locate(0,8);
        lcd.printf("Max Temp: %.2f C", maxTemp);
        lcd.locate(0,16);
        lcd.printf("Avg Temp: %.2f C", avgTemp);
   
    }
        
}
