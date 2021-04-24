#ifndef COLORED_PRINTF
#define COLORED_PRINTF

#define CLR_RESET   "\033[0m"

#define CLR_BLACK   "\033[0;30m"
#define CLR_RED     "\033[0;31m"
#define CLR_GREEN   "\033[0;32m"
#define CLR_YELLOW  "\033[0;33m"
#define CLR_BLUE    "\033[0;34m"
#define CLR_MAGENTA "\033[0;35m"
#define CLR_CYAN    "\033[0;36m"
#define CLR_WHITE   "\033[0;37m"

#define CLR_GRAY       "\033[1;30m"
#define CLR_RED_BR     "\033[1;31m"
#define CLR_GREEN_BR   "\033[1;32m"
#define CLR_YELLOW_BR  "\033[1;33m"
#define CLR_BLUE_BR    "\033[1;34m"
#define CLR_MAGENTA_BR "\033[1;35m"
#define CLR_CYAN_BR    "\033[1;36m"
#define CLR_WHITE_BR   "\033[1;37m"

#define color_printf(fmt, ...) printf(fmt CLR_RESET, ##__VA_ARGS__)
#define color_fprintf(stream, fmt, ...) fprintf(stream, fmt CLR_RESET, ##__VA_ARGS__)

#endif