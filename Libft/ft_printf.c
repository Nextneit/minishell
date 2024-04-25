/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:56:59 by etornay-          #+#    #+#             */
/*   Updated: 2023/09/26 12:34:18 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_filter(char const *content, int i, va_list *args)
{
	int	filter;

	filter = 0;
	if (content[i] == 'c')
		filter += ft_putchar(va_arg(*args, int));
	if (content[i] == 's')
		filter += ft_putstr(va_arg(*args, char *));
	if (content[i] == 'p')
		filter += ft_putpointer(va_arg(*args, unsigned long long));
	if (content[i] == 'd' || content[i] == 'i')
		filter += ft_putnum_dec(va_arg(*args, int));
	if (content[i] == 'u')
		filter += ft_putnum_nosign(va_arg(*args, unsigned int));
	if (content[i] == 'x' || content[i] == 'X')
		filter += ft_puthexa(va_arg(*args, unsigned int), content[i]);
	if (content[i] == '%')
		filter += ft_putchar('%');
	return (filter);
}

int	ft_printf(char const *content, ...)
{
	va_list	args;
	int		i;
	int		c;

	i = 0;
	c = 0;
	va_start(args, content);
	while (content[i])
	{
		if (content[i] != '%')
			c += ft_putchar(content[i]);
		else
		{
			i++;
			c += ft_filter(content, i, &args);
		}
		i++;
	}
	va_end(args);
	return (c);
}

/* #include <limits.h>
int	main(void)
{
	int a;
	a = ft_printf("%d", 147483648);
	printf("\nMi Total: %d\n", a);
	a = printf("%d", 147483648);
	printf("\nPrintf Total: %d\n", a);
}
 */