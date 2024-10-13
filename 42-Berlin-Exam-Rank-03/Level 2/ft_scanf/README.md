## Subject

```
Assignment name  : ft_scanf
Expected files   : ft_scanf.c
Allowed functions: fgetc, ungetc, ferror, feof, isspace, isdigit, stdin, va_start, va_arg, va_copy va_end
--------------------------------------------------------------------------------

Reproduce the behavior of the function scanf (man scanf) with the file given.

No options (*, m, `)
No maximum field width
No types modifier characters (Ch, hh, l ...)
No conversions beginning with %n

void skip_input_space()
{

}

int scan_char(va_list ap)
{
	return(0);
}

int scan_int(va_list ap)
{
	return(0);
}

int scan_string(va_list ap)
{
	return (0);
}

int receive_input(const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(fd, ap);
		case 'd':
			return scan_int(fd, ap);
		case 's':
			skip_input_space(fd);
			return scan_string(fd, ap);
		default:
			return 1;
	}
}

int ft_scanf(const char *format ...)
{
	int i = 0;
	int result = 0;
	va_list ap;
	
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (receive_input (&(format[i]),ap) != 1)
				break;
			else
				result++;
		}
		i++;
	}
	return (result);
}
