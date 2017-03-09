/*
** server.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Tue May 17 01:14:00 2016 Avel Docquin
** Last update Sun Jun  5 20:24:18 2016 Avel Docquin
*/

#include "server.h"

static int	end = 0;

static void	sig_handler(int sig)
{
  if (sig == SIGINT)
    end = 1;
}

static int	server_read(t_env* const e, int fd)
{
  if (my_write(1, "New client\n") == -1)
    return (-1);
  if (add_client(e, fd) == -1)
    return (-1);
  return (0);
}

int	add_server(t_env* const e)
{
  int	s;

  if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("server socket");
      return (-1);
    }
  username_cp(e[s].username, "Server");
  e[s].fd = s;
  e[s].fd_type = FD_SERVER;
  e[s].fct_read = (fct)&(server_read);
  e[s].fct_write = NULL;
  e[s].sin.sin_family = AF_INET;
  e[s].sin.sin_port = htons(e[0].port);
  e[s].sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (struct sockaddr*)&e[s].sin, sizeof(e[s].sin)) == -1)
    {
      perror("server bind");
      return (-1);
    }
  if (listen(s, 42) == -1)
    {
      perror("server listen");
      return (-1);
    }
  return (0);
}

static int	init_select(char *buf, struct timeval *tv, int *fd_max)
{
  tv->tv_sec = 20;
  tv->tv_usec = 0;
  *fd_max = 0;
  if (!memset(buf, 0, BUFFER))
    {
      perror("memset");
      return (-1);
    }
  return (0);
}

int			manage_server(t_env* const e)
{
  int			fd_max;
  fd_set		fd_read, fd_write;
  char			buf[BUFFER];
  struct timeval	tv;

  signal(SIGINT, sig_handler);
  while (end != 1)
    {
      if (init_select(buf, &tv, &fd_max) == -1)
	return (-1);
      init_fd(e, &fd_max, &fd_read, &fd_write);
      if (select(fd_max + 1, &fd_read, &fd_write, NULL, &tv) == -1)
	{
	  if (errno == EINTR)
	    return (0);
	  perror("select");
	  return (-1);
	}
      if (handle_chat(e, buf, &fd_read, &fd_write) == -1)
	return (-1);
    }
  return (0);
}
