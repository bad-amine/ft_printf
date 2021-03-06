#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

void	ft_putchar(char c);
void	ft_putnbr(int nb);
void	ft_putnbrU(unsigned int nb);
void	ft_putstr(char *str);
int		ft_atoi(char *str);
int		ft_isdigit(int c);
size_t	ft_strlenD(int n);
int	ft_strlen(char *str);
#endif
