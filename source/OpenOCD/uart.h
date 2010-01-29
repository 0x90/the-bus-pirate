#include "base.h"

#define UART_NORMAL_SPEED 34
#define UART_FAST_SPEED    3

extern uint8_t *buf_recv;
extern uint16_t bytes_recv;
extern uint16_t bytes_to_recv;

extern uint8_t *buf_send;
extern uint16_t bytes_send;
extern uint16_t bytes_send_available;;

unsigned char UART1RXRdy(void);
unsigned char UART1RX(void);
void UART1TX(char c);
void UART1Speed(uint8_t brg);
void InitializeUART1(void);
void UART1TX_Int(void);
