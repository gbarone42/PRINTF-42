#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>


static void print_str(char *str, int *count)
{
    while (*str)
    {
        write(1, str++, 1);
        (*count)++;
    }
}

static void print_num(int n, int *count)
{
    if (n < 0)
    {
        write(1, "-", 1);
        n = -n;
        (*count)++;
    }
    if (n > 9)
    {
        print_num(n / 10, count);
    }
    char c = n % 10 + '0';
    write(1, &c, 1);
    (*count)++;
}

static void print_hex(unsigned int n, int *count)
{
    char *hex = "0123456789abcdef";
    if (n > 15)
    {
        print_hex(n / 16, count);
    }
    write(1, &hex[n % 16], 1);
    (*count)++;
}

int ft_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int count = 0;

    for (const char *p = format; *p; p++)
    {
        if (*p == '%')
        {
            switch (*++p)
            {
                case 's':
                    print_str(va_arg(args, char*), &count);
                    break;
                case 'd':
                    print_num(va_arg(args, int), &count);
                    break;
                case 'x':
                    print_hex(va_arg(args, unsigned int), &count);
                    break;
                default:
                    write(1, p, 1);
                    count++;
            }
        }
        else
        {
            write(1, p, 1);
            count++;
        }
    }
    va_end(args);
    return count;
}

int main() {
    int count;

    // Test with a string
    count = ft_printf("String: %s\n", "Hello, World!");
    printf("Printed %d characters.\n\n", count);

    // Test with a decimal number
    count = ft_printf("Decimal: %d\n", 12345);
    printf("Printed %d characters.\n\n", count);

    // Test with a negative decimal number
    count = ft_printf("Negative Decimal: %d\n", -678);
    printf("Printed %d characters.\n\n", count);

    // Test with a hexadecimal number
    count = ft_printf("Hexadecimal: %x\n", 0xABCDEF);
    printf("Printed %d characters.\n\n", count);

    // Test with multiple format specifiers
    count = ft_printf("Multiple: %s, %d, %x\n", "Test", 789, 0x123);
    printf("Printed %d characters.\n", count);

    return 0;
}