#include "mbed.h"
#include "LM75B.h"
#include "C12832.h"

C12832 lcd(p5, p7, p6, p8, p11);

LM75B sensor(p28,p27);
Serial pc(USBTX,USBRX);

LocalFileSystem local("local");               // Create the local filesystem under the name "local"

int main ()
{

    //Try to open the LM75B
    if (sensor.open()) {
        printf("Device detected!\n");

        while (1) {
            lcd.cls();
            lcd.locate(0,3);
            lcd.printf("Temp = %.3f\n", (float)sensor);
            wait(1.0);
        }

    } else {
        error("Device not detected!\n");
    }

}




 
int main() {
    FILE *fp = fopen("/local/out.txt", "w");  // Open "out.txt" on the local file system for writing
    fprintf(fp, "Hello World!");
    fclose(fp);
}






int main()
{
    int j=0;
    lcd.cls();
    lcd.locate(0,3);
    lcd.printf("mbed application board!");

    while(true) {   // this is the third thread
        lcd.locate(0,15);
        lcd.printf("Counting : %d",j);
        j++;
        wait(1.0);
    }
}