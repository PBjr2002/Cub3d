/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:30:23 by adimas-d          #+#    #+#             */
/*   Updated: 2025/01/06 18:06:20 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	main(int ac, char **av)
{
	t_data		data;

	init_data(&data);
	if (ac != 2)
		return (free(data.timeval), error_handling(1));
	if (parsing(&data, av[1]) == 1)
		return (free_data(&data), error_handling(0));
	ft_creat_window(&data);
	if (check_xpms(&data) == 1)
		return (free_data(&data), error_handling(2));
	mlx_loop_hook(data.mlx, render, &data);
	mlx_hook(data.mlx_window, KeyPress, KeyPressMask, ft_key_push, &data);
	mlx_hook(data.mlx_window, KeyRelease, KeyReleaseMask, \
		ft_key_release, &data);
	mlx_hook(data.mlx_window, 17, 0, ft_close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
