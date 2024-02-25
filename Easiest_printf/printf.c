#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>


void put_string(char *string, int *length) {
    if (!string)
        string = "(null)";
    while (*string)
        *length += write(1, string++, 1);
}

void put_digit(long long int number, int base, int *length) {
    char *hexadecimal = "0123456789abcdef";

    if (number < 0) {
        number = -number;
        *length += write(1, "-", 1);
    }
    if (number >= base)
        put_digit(number / base, base, length);
    *length += write(1, &hexadecimal[number % base], 1);
}

int ft_printf(const char *format, ...) {
    int length = 0;
    va_list args;
    va_start(args, format);

    for (; *format; format++) {
        if (*format == '%') {
            switch (*++format) {
                case 's':
                    put_string(va_arg(args, char*), &length);
                    break;
                case 'd':
                    put_digit(va_arg(args, int), 10, &length);
                    break;
                case 'x':
                    put_digit(va_arg(args, unsigned int), 16, &length);
                    break;
                default:
                    length += write(1, format, 1);
                    break;
            }
        } else {
            length += write(1, format, 1);
        }
    }
    va_end(args);
    return length;
}

int main()
{
    int count;

    // Test various formats
    count = ft_printf("String: %s\n", "Hello, World!");
    printf("Printed %d characters.\n\n", count);
    ft_printf("Printed %d characters.\n\n", count);

    count = ft_printf("Decimal: %d\n", 12345);
    printf("Printed %d characters.\n\n", count);
    ft_printf("Printed %d characters.\n\n", count);

    count = ft_printf("Negative Decimal: %d\n", -678);
    printf("Printed %d characters.\n\n", count);

    count = ft_printf("Hexadecimal: %x\n", 0xABCDEF);
    printf("Printed %d characters.\n\n", count);

    count = ft_printf("Multiple: %s, %d, %x\n", "Test", 789, 0x123);
    printf("Printed %d characters.\n", count);

    return 0;
}
