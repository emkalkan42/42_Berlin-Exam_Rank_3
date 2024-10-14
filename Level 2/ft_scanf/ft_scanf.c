#include <stdarg.h>
#include <ctype.h>
#include <stdio.h>

void skip_input_space()
{
    int c;
    while ((c = fgetc(stdin)) != -1 && isspace(c))
        ;
    if (c != -1)
        ungetc(c, stdin);
}

int scan_char(va_list ap)
{
    char *ch = va_arg(ap, char *);
    int c = fgetc(stdin);
    if (c == -1)
        return 0;
    *ch = (char)c;
    return 1;
}

int scan_int(va_list ap)
{
    int *num = va_arg(ap, int *);
    int c, sign = 1, value = 0;

    skip_input_space();
    
    c = fgetc(stdin);
    if (c == '-')
    {
        sign = -1;
        c = fgetc(stdin);
    }

    if (!isdigit(c))
    {
        if (c != -1)
            ungetc(c, stdin);
        return 0;
    }

    while (isdigit(c))
    {
        value = value * 10 + (c - '0');
        c = fgetc(stdin);
    }

    *num = value * sign;

    if (c != -1)
        ungetc(c, stdin);

    return 1;
}

int scan_string(va_list ap)
{
    char *str = va_arg(ap, char *);
    int c;

    skip_input_space();
    
    while ((c = fgetc(stdin)) != -1 && !isspace(c))
        *str++ = (char)c;

    *str = '\0';
    
    if (c != -1)
        ungetc(c, stdin);
    
    return 1;
}

int receive_input(const char **format, va_list ap)
{
    switch (**format)
    {
        case 'c':
            return scan_char(ap);
        case 'd':
            return scan_int(ap);
        case 's':
            skip_input_space();
            return scan_string(ap);
        default:
            return 0;
    }
}

int ft_scanf(const char *format, ...)
{
    int i = 0;
    int result = 0;
    va_list ap;

    va_start(ap, format);

    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            i++;
            if (receive_input(&(format[i]), ap) == 0)
                break;
            else
                result++;
        }
        i++;
    }

    va_end(ap); // Clean up the va_list
    return result;
}
