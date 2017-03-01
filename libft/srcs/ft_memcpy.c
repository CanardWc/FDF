/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 03:38:12 by fgrea             #+#    #+#             */
/*   Updated: 2016/11/18 12:53:57 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*str;
	char	*dst;

	if (n == 0 || dest == src)
		return (dest);
	str = (char *)src;
	dst = (char *)dest;
	while (n--)
		*dst++ = *str++;
	return (dest);
}
