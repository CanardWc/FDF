/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 00:27:18 by fgrea             #+#    #+#             */
/*   Updated: 2017/02/18 13:37:15 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_memalloc(size_t size)
{
	int	*str;
	int i;

	i = 0;
	str = (int *)malloc(sizeof(int) * size);
	if (str == NULL)
		return (NULL);
	while (str[i++])
		str[i] = 0;
	return (str);
}
