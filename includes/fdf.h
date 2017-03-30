/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 21:15:03 by fgrea             #+#    #+#             */
/*   Updated: 2017/03/30 14:50:38 by fgrea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>

typedef struct		s_map
{
	int				**map;
	ssize_t			x;
	ssize_t			y;
}					t_map;

typedef struct		s_pxl
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	t_map			*imap;

	int				r;
	int				g;
	int				b;

	int				iwidth;
	int				iheight;
	int				ix;
	int				iy;

	int				czoom;
	int				cxcenter;
	int				cycenter;
	float			c1;
	float			c2;
	float			c3;

	float			zoom;
	float			xdcl;
	float			ydcl;
	int				dpth;

	int				size;
	int				bx1;
	int				bx2;
	int				by1;
	int				by2;
	int				dx;
	int				dy;
	int				e;

	int				c;
	int				ci;
	int				cj;
}					t_pxl;

void				fdf_create_hud(t_pxl *pxl);
char				*fdf_bress(t_pxl *pxl, t_map *imap);
t_map				*fdf_parcing(char *argv);
void				*fdf_create_image(t_map *smap, t_pxl *pxl);
t_pxl				*fdf_depths_colors(t_pxl *pxl, int depths);
t_pxl				*fdf_set_color(t_pxl *pxl, int set_base);
char				*fdf_image_pxl(t_pxl *pxl, t_map *imap);
void				fdf_usage(int argc);
void				fdf_other_errors();
int					fdf_key_capture(int kcd, t_pxl *pxl);
void				*fdf_kcd_for_img(t_pxl *pxl, t_map *imap);
void				fdf_map_error(void);

#endif
