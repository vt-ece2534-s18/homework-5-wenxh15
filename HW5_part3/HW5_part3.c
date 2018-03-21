#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <LED_HAL.h>
#include <Buttons_HAL.h>
#include <Timer_HAL.h>





Graphics_Context g_sContext;

void InitGraphics() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&g_sContext,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_setFont(&g_sContext, &g_sFontCmtt40);
    Graphics_clearDisplay(&g_sContext);
}


void moveCircle() {
    unsigned i ;
     static unsigned x = 0, y = 63;
     i = 127;

     Graphics_drawCircle(&g_sContext, x, y, 5);
     Graphics_drawCircle(&g_sContext, i, y, 5);
     StartOneShot10mTimer();
     Graphics_clearDisplay(&g_sContext);

     while (1){
         x=(rand()%128);
         if(x <= 5){
             i = 127+x;
             Graphics_drawCircle(&g_sContext, x, y, 5);
             Graphics_drawCircle(&g_sContext, i, y, 5);
             StartOneShot10mTimer();
             Graphics_clearDisplay(&g_sContext);
         }
         else if (x >= 122){
             i = x-127;
             Graphics_drawCircle(&g_sContext, x, y, 5);
             Graphics_drawCircle(&g_sContext, i, y, 5);
             StartOneShot10mTimer();
             Graphics_clearDisplay(&g_sContext);
         }
         else if(x>=63 &&x<=65){
             i = x-5;
             Graphics_drawCircle(&g_sContext, x, y, 5);
             Graphics_drawCircle(&g_sContext, i, y, 5);
             StartOneShot10mTimer();
             Graphics_clearDisplay(&g_sContext);
         }
         else if (x>=61 && x<63){
             i = 5+x;
             Graphics_drawCircle(&g_sContext, x, y, 5);
             Graphics_drawCircle(&g_sContext, i, y, 5);
             StartOneShot10mTimer();
             Graphics_clearDisplay(&g_sContext);
         }
         else {
             Graphics_drawCircle(&g_sContext, x, y, 5);
             StartOneShot10mTimer();
             Graphics_clearDisplay(&g_sContext);
         }
}
}
int main(void) {
    WDT_A_hold(WDT_A_BASE);

    Init10mTimer();
    StartOneShot10mTimer();
    InitButtons();
    InitLEDs();
    InitTimer2();
    InitGraphics();


    Graphics_fillCircle(&g_sContext, 63, 63, 5);
    while (1) {
        if (Booster_Top_Button_Pushed())
            Toggle_Launchpad_Left_LED();

        if (OneShot10mTimerExpired()) {
            moveCircle();
            StartOneShot10mTimer();
        }

    }

}
