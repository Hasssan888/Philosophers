#include "philo.h"

int	ft_isdigit(int d)
{
	return (d >= '0' && d <= '9');
}

long	ft_atoi(const char *str)
{
	long	r;
	int					i;
	int					s;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return ((int)r * s);
}