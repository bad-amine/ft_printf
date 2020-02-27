#include "ft_printf.h"
#include <stdio.h>

void	deTOhe(size_t   nb)
{
	long int r;
	unsigned  long int q;
	int i;
	int j;
	int temp;
	char h[1000000];

	i = 1;
/*	if (nb < 0)
	{
		ft_putchar('-');
		q = -nb;
	}
	else*/
		q = nb;
	while (q) {
		temp = q % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + 55 + 32;
		h[i++] = temp;
		q = q / 16;
		j = i - 1;
	}
	while (j)
	{
		ft_putchar(h[j]);
		j--;
	}	
}

void	get_type(const char **text, va_list args)
{
	if (**text == 'd' && *text++)
		ft_putnbr(va_arg(args, int));
	else if (**text == 's' && *text++)
		ft_putstr(va_arg(args, char *));
	else if (**text == 'x' && *text++)
		deTOhe(va_arg(args, unsigned int));
	else if (**text == 'c' && *text++)
		ft_putchar(va_arg(args, int));
	else if (**text == 'p' && *text++)
		deTOhe((size_t)va_arg(args, void *));
}

void	print(const char *text, ...)
{
	va_list args;

	va_start(args, text);
	while (*text)
	{
		if (*text == '%' && text++)
			get_type(&text, args);
		else
			ft_putchar(*text);
		text++;
	}
	va_end(args);
}
int	main()
{
	//char *k = "a%dqwerty%di\n%d%d%di%d";
	//print(k,1, 2);
//	print("%d%#%s$%#%s",1, "qwerty","qwerty");
	char e = 'k';
	print("%p\n", &e);
	printf("%p", &e);
	
//	print("##");
	return (0);
}
