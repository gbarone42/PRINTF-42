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

int main()
{
    int count;

    // Test various formats
    count = ft_printf("String: %s\n", "Hello, World!");
    printf("Printed %d characters.\n\n", count);

    count = ft_printf("Decimal: %d\n", 12345);
    printf("Printed %d characters.\n\n", count);

    count = ft_printf("Negative Decimal: %d\n", -678);
    printf("Printed %d characters.\n\n", count);

    count = ft_printf("Hexadecimal: %x\n", 0xABCDEF);
    printf("Printed %d characters.\n\n", count);

    count = ft_printf("Multiple: %s, %d, %x\n", "Test", 789, 0x123);
    printf("Printed %d characters.\n", count);

    return 0;
}
//                COMMENTED CODE BELOW IS THE SAME AS ABOVE                 ///////////////////////////
//
// // Function to print a string and keep track of the number of characters printed.
// static void print_str(char *str, int *count)
// {
//     // Iterate through each character of the string until the null terminator
//     while (*str)
//     {
//         write(1, str++, 1); // Write the current character to stdout
//         (*count)++;         // Increment the count
//     }
// }

// // Function to print an integer and keep track of the number of characters printed.
// static void print_num(int n, int *count)
// {
//     if (n < 0)
//     {
//         write(1, "-", 1); // Write negative sign for negative numbers
//         n = -n;           // Make the number positive
//         (*count)++;       // Increment the count
//     }
//     if (n > 9)
//     {
//         print_num(n / 10, count); // Recursively print digits
//     }
//     char c = n % 10 + '0';       // Convert the last digit to a character
//     write(1, &c, 1);             // Write the digit
//     (*count)++;                  // Increment the count
// }

// // Function to print a hexadecimal number and keep track of the number of characters printed.
// static void print_hex(unsigned int n, int *count)
// {
//     char *hex = "0123456789abcdef"; // String representing hexadecimal digits
//     if (n > 15)
//     {
//         print_hex(n / 16, count); // Recursively process each hex digit
//     }
//     write(1, &hex[n % 16], 1);    // Write the corresponding hex digit
//     (*count)++;                   // Increment the count
// }

// // Our custom printf function
// int ft_printf(const char *format, ...)
// {
//     va_list args;
//     va_start(args, format); // Start variadic arguments
//     int count = 0;          // Count of printed characters

//     // Iterate through the format string
//     for (const char *p = format; *p; p++)
//     {
//         if (*p == '%') // Check for format specifier
//         {
//             switch (*++p) // Check the character following '%'
//             {
//                 case 's': // String format
//                     print_str(va_arg(args, char*), &count);
//                     break;
//                 case 'd': // Integer format
//                     print_num(va_arg(args, int), &count);
//                     break;
//                 case 'x': // Hexadecimal format
//                     print_hex(va_arg(args, unsigned int), &count);
//                     break;
//                 default:
//                     write(1, p, 1); // If unknown format, print the character as is
//                     count++;
//             }
//         }
//         else
//         {
//             write(1, p, 1); // Print non-format characters as is
//             count++;
//         }
//     }
//     va_end(args); // End variadic arguments
//     return count; // Return the number of characters printed
// }

// int main() {
//     int count;

//     // Test with a string
//     count = ft_printf("String: %s\n", "Hello, World!");
//     printf("Printed %d characters.\n\n", count);

//     // Test with a decimal number
//     count = ft_printf("Decimal: %d\n", 12345);
//     printf("Printed %d characters.\n\n", count);

//     // Test with a negative decimal number
//     count = ft_printf("Negative Decimal: %d\n", -678);
//     printf("Printed %d characters.\n\n", count);

//     // Test with a hexadecimal number
//     count = ft_printf("Hexadecimal: %x\n", 0xABCDEF);
//     printf("Printed %d characters.\n\n", count);

//     // Test with multiple format specifiers
//     count = ft_printf("Multiple: %s, %d, %x\n", "Test", 789, 0x123);
//     printf("Printed %d characters.\n", count);

//     return 0;
// }