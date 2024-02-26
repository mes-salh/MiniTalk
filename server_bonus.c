/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:29:24 by mes-salh          #+#    #+#             */
/*   Updated: 2024/02/26 05:26:03 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_header(void)
{
	ft_putstr_fd("\033[38;2;0;255;0m", 1);
	ft_putstr_fd("███████╗███████╗██████╗ ██╗   ██╗███████╗██████╗ \n", 1);
	ft_putstr_fd("██╔════╝██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗\n", 1);
	ft_putstr_fd("███████╗█████╗  ██████╔╝██║   ██║█████╗  ██████╔╝\n", 1);
	ft_putstr_fd("╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝██╔══╝  ██╔══██╗\n", 1);
	ft_putstr_fd("███████║███████╗██║  ██║ ╚████╔╝ ███████╗██║  ██║\n", 1);
	ft_putstr_fd("╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝\n", 1);
	ft_putstr_fd("██████╗  ██████╗ ███╗   ██╗██╗   ██╗███████╗\n", 1);
	ft_putstr_fd("██╔══██╗██╔═══██╗████╗  ██║██║   ██║██╔════╝\n", 1);
	ft_putstr_fd("██████╔╝██║   ██║██╔██╗ ██║██║   ██║███████╗\n", 1);
	ft_putstr_fd("██╔══██╗██║   ██║██║╚██╗██║██║   ██║╚════██║\n", 1);
	ft_putstr_fd("██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████║\n", 1);
	ft_putstr_fd("╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝\n", 1);
	ft_putstr_fd("                    PID : ", 1);
	ft_putnbr(getpid());
	ft_putchar('\n');
	ft_putstr_fd("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n", 1);
	ft_putstr_fd("\033[0m", 1);
}

// void	checker(int *i, char *c, int *client_pid, int pid)
// {
// 	if (pid != *client_pid)
// 	{
// 		*client_pid = pid;
// 		*i = 7;
// 		*c = 0;
// 	}
// }

// void	mes_handlesig(int sig, siginfo_t *info, void *just)
// {
// 	static int	i = 7;
// 	static char	c = 0;
// 	static int	client_pid = 0;
// 	int			pid;

// 	just = NULL;
// 	pid = info->si_pid;
// 	if (client_pid == 0)
// 		client_pid = pid;
// 	checker(&i, &c, &client_pid, pid);
// 	if (sig == SIGUSR2)
// 		c |= (1 << i);
// 	i--;
// 	if (i < 0)
// 	{
// 		if (c == 0)
// 			kill (client_pid, SIGUSR1);
// 		else
// 			write(1, &c, 1);
// 		i = 7;
// 		c = 0;
// 	}
// }
void	mes_handlesig(int sig, siginfo_t *info, void *just)
{
	static int		bit;
	static char		c;
	static pid_t	pid;

	(void)just;
	if (pid != info->si_pid)
	{
		bit = 0;
		c = 0;
	}
	c = c << 1 | (sig - SIGUSR1);
	bit++;
	if (bit == 8)
	{
		if (c == 0)
			kill(info->si_pid, SIGUSR1);
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
	}
	pid = info->si_pid;
	(void)info;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = mes_handlesig;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, 0) == -1 || sigaction(SIGUSR2, &sa, 0) == -1)
	{
		ft_putstr_fd("Error\n", 1);
		exit(1);
	}
	ft_header();
	while (1)
		pause();
	return (0);
}
