//Copy all the lib files to the sketch directory

#include "Framebuffer.h"
void setup() {
  // put your setup code here, to run once:
  test();
}

void loop() {
  // put your main code here, to run repeatedly:

}
/*
    In this example, we are going to draw bitmaps.
    The code is quite straight forward.
*/


int test(void) {
    Framebuffer fb;

    fb.drawString("Soldering Pen",0,0);
    
    
    fb.drawString("+10",101,16);
    fb.drawString("320",71,16);
    fb.drawString("-10",41,16);
    fb.drawString("-20",11,16);

    fb.drawVLine(20,25,3);
    fb.drawVLine(50,25,3);
    fb.drawVLine(80,25,3);
    fb.drawVLine(110,25,3);
    fb.drawHLine(0,28,127);
    fb.drawRectangle(79,29,81,31,1);
    
    fb.show();

    return 0;
}
