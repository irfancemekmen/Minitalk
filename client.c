/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iekmen <iekmen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:40:37 by iekmen            #+#    #+#             */
/*   Updated: 2026/03/03 02:26:05 by iekmen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t	g_ack = 0;

static void	mt_sendbit(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_ack = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_ack)
			pause();
		bit--;
	}
}

static void	mt_ack(int sig)
{
	(void)sig;
	g_ack = 1;
}

static void	mt_init_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = mt_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
}

static int	mt_validate_pid(int pid)
{
	if (pid <= 0)
	{
		write(1, "Check PID!\n", 12);
		return (0);
	}
	if (kill(pid, 0) == -1)
	{
		write(1, "Invalid PID!\n", 14);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3)
	{
		write(1, "Check Arguments!\n", 18);
		return (1);
	}
	mt_init_signal();
	pid = mt_atoi(av[1]);
	if (!mt_validate_pid(pid))
		return (1);
	i = 0;
	while (av[2][i])
		mt_sendbit(pid, (av[2][i++]));
	mt_sendbit(pid, '\n');
	return (0);
}

