#include "ft_printf.h"
#include <stdio.h>
//#include <string.h>

//int cmpt = 0;
//int cmptd = 0;
int	cmpt = 0;
//int cmpt_text = 0;
typedef	struct	s_data
{
	int p;
	int w;
	int m;
	int z;
}				t_data;


#define NUMBER 1
#define CHAR 2
#define STRING 3

void print_count(void *data, int type)
{
	// int char string
	// putnumber putchar putstr
	
	if (type == NUMBER)
	{
		ft_putnbr((int )data);
		cmpt +=  ft_strlenD((int)data);
	}
	else if (type == CHAR)
	{
		ft_putchar(((int )data));
		cmpt++;
	}
	else if (type ==STRING)
	{
		ft_putstr(data);
		cmpt +=  ft_strlen(data);
	}
}



void	deTOhex(size_t   nb)
{
	long int r;
	unsigned  long int q;
	int i;
	int j;
	int temp;
	char h[1000000];

	i = 1;
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
		print_count((void *)((int)h[j]), CHAR);
		j--;
	}	
}
void	deTOheX(size_t   nb)
{
	long int r;
	unsigned  long int q;
	int i;
	int j;
	int temp;
	char h[1000000];

	i = 1;
		q = nb;
	while (q) {
		temp = q % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + 55;
		h[i++] = temp;
		q = q / 16;
		j = i - 1;
	}
	while (j)
	{
		//ft_putchar(h[j]);
		print_count((void *)((int)h[j]), CHAR);
		j--;
	}	
}

void	initialize(t_data *data)
{
	data->p = 0;
	data->w = 0;
	data->m = 0;
	data->z = 0;
}

int	wANDp(va_list *args, char **text, t_data *data)
{
	int i;

	i = 0;
	if(**text == '-')
	{
		data->m = 1;
		(*text)++;
		i++;
	}
	else if(**text == '0')
	{
		data->z = 1;
		(*text)++;
		i++;
	}
	if(ft_isdigit(**text)){
		data->w = ft_atoi((char *)*text);
		while (ft_isdigit(**text))
		{
			(*text)++;
			i++;
		}
	}
	else if(**text == '*')
	{
		data->w = va_arg(*args, int);
		(*text)++;
		i++;
	}
	if (**text == '.')
	{
		(*text)++;
		i++;
		if(ft_isdigit(**text)){
			data->p = ft_atoi((char *)*text);
			while (ft_isdigit(**text))
			{
				(*text)++;
				i++;
			}
		}
		else if(**text == '*')
		{
			data->p = va_arg(*args, int);
			(*text)++;
			i++;
		}
	}
//	printf("\nje suis dans wANDp ça return %d\n",i);
	return (i);
}	

void	type_width_for_c(t_data *data)
{
	data->w--;
	if (data->w < 0)
		data->w--;
	while (data->w > 0)
	{
		print_count((void *)' ', CHAR);
		data->w--;
	}
}

void	type_width_for_s(t_data *data)
{
	data->w--;
	if (data->w < 0)
		data->w--;
	while (data->w > 0)
	{
		print_count((void *)" ", STRING);
		data->w--;
	}
}

void	type_width_for_d(t_data *data, va_list *args)
{
	int ci;
	ci =0;
	if (data->p < 0)
	{
		data->p = 0;
	}
	int d = va_arg(*args, int);

	int c =  data->p - ft_strlenD(d);	
	if (c < 0)
		c = 0;

	if (data->w < 0)
		data->w--;
	if (data->m == 0) {
//			int ci;
		if (c != 0)
		 ci = data->w - c - ft_strlenD(d);
		else ci = data->w  - ft_strlenD(d);
	//	printf("\n je suis dans type_width_for_d c = %d ci =%d\n",c,ci);
		while (ci  > 0)
		{
			print_count((void *)' ', CHAR);
			ci--;
		}
	while (c > 0)
	{
		print_count((void *)0, NUMBER);
		//ft_putnbr(0);
		c--;
	}
		print_count((void *)d, NUMBER);
	}
	else if (data->m == 1)
	{
			int ci;
		if (c != 0)
		 ci = data->w - c;
		else ci = data->w  - ft_strlenD(d);
		

		while (ci--  > 0)
		{
		print_count((void *)' ', CHAR);
		}
		while (c--)
			//ft_putnbr(0);
			print_count((void *)0, NUMBER);
		print_count((void *)d, NUMBER);

	}
	initialize(data);
//	cmptd = ci + c + 1;
}
//increment cmpt in other than d
void	get_type( char **text, va_list *args, t_data *data)
{
	int t = 0;
	int i = 0;
	t = wANDp(args, text, data);

	if ((**text == 'd' || **text == 'i') && (*text)++)
	{
		type_width_for_d(data,args);

		
	}
	/*else if (**text == 'i' && (*text)++)
	{
		type_width_for_d(data,args);

		
	}*/

	else if (**text == 'u' && (*text)++)
		ft_putnbrU(va_arg(args,unsigned int));

	else if (**text == 's' && (*text)++)
	{



		if (data->w < 0)
		{
			data->w = -data->w;
			data->m = 1;
		}
		if (data->p < 0)
			data->p = 0;
	
		char *str = va_arg(*args, char*);
		if (str == NULL)
		{
			str = "(null)";
		}
		int len = ft_strlen(str);
		int pre = data->p; 
		//str = "LO\0LO"
		len =  data->p < len ? data->p : len;
		data->w = data->w -  len +1;
		if (data->m == 0)
		{
 
		type_width_for_s(data);
		while(len--)
		print_count((void *)str[i++], CHAR);
		}
		else 
		{
			while(len--)
			print_count((void *)str[i++], CHAR);
			type_width_for_s(data);
		}
	}
	else if (**text == 'x' && (*text)++)
		deTOhex(va_arg(*args, unsigned int));	
	else if (**text == 'X' && (*text)++)
		deTOheX(va_arg(*args, unsigned int));

	else if (**(text ) == 'c' && (*text)++)
	{
		type_width_for_c(data);
		print_count((void * )va_arg(*args, int), CHAR);
	}
	else if (**text == 'p' && (*text)++)
	{
		print_count((void *)"0x", STRING);
		deTOhex((size_t)va_arg(*args, void *));
	}
}

int	ft_printf(const char *format, ...)
{
	va_list args;
	int i;
	int min;
	t_data data;
	char *text;
	cmpt = 0;

	text = (char *) format;
	

	va_start(args, NULL);
	initialize(&data);
	int t = wANDp(&args, &text, &data);

	while (*text)
	{
		if (*text == '%' && text++)
		{
			get_type(&text, &args, &data);

		}
	
		else {
			print_count((void *)((int)*text), CHAR);
			text++;
		
		}
	}
	va_end(args);
	return (cmpt);
}

int	main(int argc, char **argv)
{
	char e = 'k';



	setbuf(stdout, NULL);
int a =	   printf("%s", "test");printf("\n");
int b =	 ft_printf("%s", "test");
printf("\n");
printf("%d  %d\n",a, b);
	return (0);
}
