/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iekmen <iekmen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:40:25 by iekmen            #+#    #+#             */
/*   Updated: 2026/03/06 01:43:05 by iekmen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>
#include <signal.h>

static void	mt_handle(int sig, siginfo_t *info, void *context)
{
	static int	bit = 128;
	static char	c = 0;

	(void)context;
	if (sig == SIGUSR1)
		c = c | bit;
	bit = bit / 2;
	if (bit == 0)
	{
		if (c == '\n')
			kill(info->si_pid, SIGUSR2);
		write(1, &c, 1);
		bit = 128;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	write(1, "Server PID: ", 12);
	mt_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = mt_handle;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
