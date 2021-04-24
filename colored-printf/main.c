#include "stdio.h"
#include "colored-printf.h"

int main()
{
    color_printf(CLR_BLACK   "Black\n");
    color_printf(CLR_RED     "Red\n");
    color_printf(CLR_GREEN   "Green\n");
    color_printf(CLR_YELLOW  "Yellow\n");
    color_printf(CLR_BLUE    "Blue\n");
    color_printf(CLR_MAGENTA "Magenta\n");
    color_printf(CLR_CYAN    "Cyan\n");
    color_printf(CLR_WHITE   "White\n");

    color_printf(CLR_GRAY       "Gray\n");
    color_printf(CLR_RED_BR     "Bright red\n");
    color_printf(CLR_GREEN_BR   "Bright green\n");
    color_printf(CLR_YELLOW_BR  "Bright yellow\n");
    color_printf(CLR_BLUE_BR    "Bright blue\n");
    color_printf(CLR_MAGENTA_BR "Bright magenta\n");
    color_printf(CLR_CYAN_BR    "Bright cyan\n");
    color_printf(CLR_WHITE_BR   "Bright white\n");
}
