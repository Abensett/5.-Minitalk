/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 23:00:11 by abensett          #+#    #+#             */
/*   Updated: 2021/12/19 13:30:28 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static void	ft_count(int signum)
{
	static int	counter = 0;

	if (signum == SIGUSR1)
		counter++;
	else
	{
		ft_putstr_fd("The message was well received : ", 1);
		ft_putnbr_fd(counter, 1);
		ft_putstr_fd(" confirmation signals were received by the client\n", 1);
		exit(0);
	}
}

static void	ft_send(int s_pid, char *str)
{
	int		i;
	char	char_tosend;

	while (*str)
	{
		i = 8;
		char_tosend = *str++;
		while (i--)
		{
			if (char_tosend >> i & 1)
				kill(s_pid, SIGUSR2);
			else
				kill(s_pid, SIGUSR1);
			usleep(100);
		}
	}
	i = 8;
	while (i--)
	{
		kill(s_pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sigaction;

	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putstr_fd("The appropriate format is ./client pid str\n", 1);
		return (-1);
	}
	s_sigaction.sa_handler = ft_count;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	ft_send(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
