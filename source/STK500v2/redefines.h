/* Definitions to get the existing code working with the Bus Pirate */
#define uart_sendchar(X) UART1TX(X)
#define uart_getchar(X) UART1RX()
#define uart_init() Initialize(); InitializeUART1() //do both
#define LED_INIT BP_LEDMODE_DIR=0 //LED to output
#define LED_ON BP_LEDMODE=1 //LED ON
#define LED_OFF BP_LEDMODE=0 //LED OFF
#define uint8_t unsigned char
#define uint16_t unsigned int
