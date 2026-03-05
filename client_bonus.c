/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iekmen <iekmen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:03:44 by iekmen            #+#    #+#             */
/*   Updated: 2026/03/06 02:07:16 by iekmen           ###   ########.fr       */
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
	if (sig == SIGUSR2)
		write(1, "Message received\n", 17);
	g_ack = 1;
}

static void	mt_init_signal(void)
{
	struct sigaction	sa;

	mt_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = mt_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
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
	if (pid <= 0)
	{
		write(1, "Check PID!\n", 12);
		return (1);
	}
	i = 0;
	while (av[2][i])
		mt_sendbit(pid, (av[2][i++]));
	mt_sendbit(pid, '\0');
	return (0);
}
