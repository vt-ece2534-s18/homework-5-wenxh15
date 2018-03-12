#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <LED_HAL.h>
#include <Buttons_HAL.h>
#include <Timer_HAL.h>
#include <ADC_HAL.h>
#include <stdio.h>

Graphics_Context g_sContext;

void InitGraphics() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&g_sContext,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_setFont(&g_sContext, &g_sFontCmtt16);
    Graphics_clearDisplay(&g_sContext);
}

void LCDDrawChar(unsigned row, unsigned col, int8_t c) {
    Graphics_drawString(&g_sContext,
                        &c,
                        1,
                        8 * (col % 16),
                        16 * (row % 8),
                        OPAQUE_TEXT);
}


int main(void) {
    WDT_A_hold(WDT_A_BASE);
    unsigned vx, vy;
    char buf[10];

    initADC_Multi();
    initJoyStick();
    InitGraphics();
    InitHWTimer1();
    Init1sTimer();
    InitButtons();
    InitLEDs();

    StartOneShot1sTimer();
    startADC();

    // The number of zeros and ones produced on the pseudo-random string
    int ones = 0;
    int zeros = 0;

    while (1) {
        if (Booster_Top_Button_Pushed())
            Toggle_Launchpad_Left_LED();

        getSampleJoyStick(&vx, &vy);

        int randBit = (vx%2) ^ (vy%2);
        if (randBit)
            ones++;
        else
            zeros++;

        int percent = (ones * 100) / (ones + zeros);
        char digits[3];

        digits[0] = (percent / 10) + '0';
        digits[1] = (percent % 10) + '0';
        digits[2] = 0;
        Graphics_drawString(&g_sContext, (int8_t *) digits, -1, 20, 50, true);

    }

}
