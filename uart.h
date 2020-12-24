void uart_putchar(char c, FILE *stream);
char uart_getchar(FILE *stream);
void USART_TX(unsigned char data);

void uart_init(unsigned int baud);

/* http://www.ermicro.com/blog/?p=325 */

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
