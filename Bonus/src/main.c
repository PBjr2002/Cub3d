/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:30:23 by adimas-d          #+#    #+#             */
/*   Updated: 2025/01/07 11:33:44 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/*
 1- tratar da separacao do bonus para o normal
 2- norminette - feito
 3- dar free das coisas - feito(leaks do mlx ?)
 4- conseguir usar o rato para fechar as janela - feito (carregar no botao R)
 */

int	error_handling(int error)
{
	if (error == 1)
		return (ft_printf("Error\nThis program "\
			"only accepts 2 arguments.\n"), 1);
	else if (error == 2)
		return (ft_printf("Error\nWrong file format "\
			"or file doesn't exist.\n"), 1);
	else if (error == 3)
		return (ft_printf("Error\nFile doesn't have "\
			"a square or rectangular map.\n"), 1);
	else
		return (ft_printf("Error\n"), 1);
}

void	ft_circle_coord(t_data *data, int i, int j)
{
	t_vector	*plr_circ;
	double		angle;
	double		r;
	int			x;
	int			y;

	plr_circ = (t_vector *)ft_calloc(181, sizeof(t_vector));
	angle = ft_map_step(data);
	r = angle / 2;
	x = 7 * angle + r;
	y = 7 * angle + r;
	while (i <= 360)
	{
		angle = i;
		plr_circ[j].x = x - r * cos(angle * M_PI / 180);
		plr_circ[j].y = y - r * sin(angle * M_PI / 180);
		i += 2;
		j++;
	}
	data->mini_plr = plr_circ;
}

int	main(int ac, char **av)
{
	t_data		data;

	init_data(&data);
	if (ac != 2)
		return (free(data.timeval), error_handling(1));
	if (parsing(&data, av[1]) == 1)
		return (free_data(&data), error_handling(0));
	ft_circle_coord(&data, 0, 0);
	ft_creat_window(&data);
	if (check_xpms(&data) == 1)
		return (free_data(&data), error_handling(2));
	mlx_mouse_move(data.mlx, data.mlx_window, W_WIDTH / 2, W_HEIGHT / 2);
	mlx_mouse_hide(data.mlx, data.mlx_window);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_hook(data.mlx_window, KeyPress, KeyPressMask, ft_key_push, &data);
	mlx_hook(data.mlx_window, KeyRelease, KeyReleaseMask, \
		ft_key_release, &data);
	mlx_hook(data.mlx_window, 17, 0, ft_close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
