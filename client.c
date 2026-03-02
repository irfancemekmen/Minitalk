/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iekmen <iekmen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:40:37 by iekmen            #+#    #+#             */
/*   Updated: 2026/03/03 00:04:49 by iekmen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	mt_sendbit(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (c >> bit & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
		bit--;
	}
}

void	mt_ack(int sig)
{
	(void)sig;
	write(1, "Message received!\n", 18);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int	pid;
	int	i;

	i = 0;
	if (argc != 3)
	{
		write(1, "Check Arguments!\n", 18);
		return (1);
	}
	sa.sa_handler = mt_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	pid = mt_atoi(argv[1]);
	if (pid <= 0)
	{
		write(1, "Check PID!\n", 12);
		return (1);
	}
	if (kill(pid, 0) == -1)
	{
		write(1, "Invalid PID!\n", 13);
		return (1);
	}
	while (argv[2][i])
		mt_sendbit(pid, (argv[2][i++]));
	mt_sendbit(pid, '\n');
	return (0);
}
