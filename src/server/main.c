/*
** main.c for my_irc in /home/docqui_a/PSU_2015_myirc/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Mon May 16 23:49:48 2016 Avel Docquin
** Last update Sun Jun  5 23:18:23 2016 Avel Docquin
*/

#include "server.h"

static int	close_env(t_env* const e)
{
  int		i;

  i = -1;
  while (++i < MAX_FD)
    if ((i == 0 && e[i].fd_type == FD_SERVER)
	|| (e[i].fd != 0 && e[i].fd_type != FD_FREE))
      if (close(e[i].fd) == -1)
	{
	  perror("close");
	  return (-1);
	}
  return (0);
}

static int	init_env(t_env* const e, const char** const av)
{
  int		i;
  int		port;

  i = -1;
  port = my_atoi(av[1]);
  while (++i < MAX_FD)
    {
      if (!memset(e[i].username, 0, 10))
	{
	  perror("memset");
	  return (-1);
	}
      e[i].port = port;
      e[i].fd_type = FD_FREE;
      e[i].fct_read = e[i].fct_write = NULL;
      e[i].fd = 0;
      e[i].ch[0] = 0;
      e[i].ch[1] = 0;
      e[i].ch[2] = 0;
    }
  return (0);
}

int	main(int const ac, const char** const av)
{
  t_env	e[MAX_FD];

  if (ac < 2)
    {
      my_write(2, "Usage : ./server port\n");
      return (1);
    }
  if (init_env(e, av) == -1)
    return (-1);
  if (add_server(e) == -1 || manage_server(e) == -1)
    {
      close_env(e);
      return (1);
    }
  if (close_env(e) == -1)
    return (1);
  return (0);
}
