/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaner <mtaner@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:07:49 by mtaner            #+#    #+#             */
/*   Updated: 2022/09/03 20:07:51 by mtaner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_type_control(char c, va_list arg)
{
	if (c == 's')
		return (ft_putstr(va_arg(arg, char *)));
	else if (c == 'c')
		return (ft_putchar(va_arg(arg, int)));
	else if (c == 'd' || c == 'i')
		return (ft_abs(va_arg(arg, int)));
	else if (c == 'p')
	{
		ft_putstr("0x");
		return (ft_convert(
				va_arg(arg, unsigned long), "0123456789abcdef") + 2);
	}
	else if (c == 'u')
		return (ft_convert(va_arg(arg, unsigned int), "0123456789"));
	else if (c == '%')
		return (ft_putchar('%'));
	else if (c == 'x')
		return (ft_convert(va_arg(arg, unsigned int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_convert(va_arg(arg, unsigned int), "0123456789ABCDEF"));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		i;
	int		j;

	va_start(arg, str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			j += ft_type_control(str[i + 1], arg);
			i++;
		}
		else
			j += write(1, &str[i], 1);
		i++;
	}
	va_end(arg);
	return (j);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_additions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaner <mtaner@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:08:05 by mtaner            #+#    #+#             */
/*   Updated: 2022/09/03 20:08:08 by mtaner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_abs(int content)
{
	if (content < 0)
	{
		ft_putchar('-');
		if (content == -2147483648)
			return (ft_convert(2147483648, "0123456789") + 1);
		content *= -1;
		return (ft_convert(content, "0123456789") + 1);
	}
	return (ft_convert(content, "0123456789"));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putstr(char *c)
{
	if (!c)
		return (ft_putstr("(null)"));
	return (write(1, c, ft_strlen(c)));
}

int	ft_convert(size_t data, char *base)
{
	int			len;
	static char	str[50];
	char		*ptr;

	len = ft_strlen(base);
	ptr = &str[49];
	*ptr = '\0';
	*--ptr = base[data % len];
	data = data / len;
	while (data != 0)
	{
		*--ptr = base[data % len];
		data = data / len;
	}
	return (ft_putstr(ptr));
}

int main()
{   
    int deneme=5;
    int* denemepointer= &deneme; 
    ft_printf("%.dxd%%c",42);
    printf("%p",denemepointer);
}