/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 20:06:07 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/13 17:52:45 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	fdf_usage(int argc)
{
	if (argc != 2)
	{
		ft_putendl("usage: ./FDF source_file");
		exit(1);
	}
}

void	fdf_map_error(void)
{
	ft_putendl("bad map");
	exit(1);
}

void	fdf_other_errors(void)
{
	ft_putendl("error");
	exit(1);
}
