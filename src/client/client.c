/*
** client.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Thu Apr 28 16:11:13 2016 Avel Docquin
** Last update Sun Jun  5 22:46:13 2016 Avel Docquin
*/

#include "client.h"

static int	quit = 0;

static void	sig_handler(int sig)
{
  if (sig == SIGINT)
    quit = 1;
}

static void	init_fd(t_infos* const infos,
			fd_set* const fd_read, fd_set* const fd_write)
{
  FD_ZERO(fd_read);
  FD_ZERO(fd_write);
  FD_SET(1, fd_read);
  FD_SET(1, fd_write);
  if (infos->mode > 0)
    {
      FD_SET(infos->fd, fd_read);
      FD_SET(infos->fd, fd_write);
    }
}

static int	offline(t_infos* const infos, char* const buf,
			const fd_set* const fd_read,
			const fd_set* const fd_write)
{
  int		r;

  if (!memset(buf, 0, BUFFER))
    {
      perror("memset");
      return (-1);
    }
  if (FD_ISSET(1, fd_read))
    {
      if ((r = read_socket(1, buf, NULL)) == -1)
	return (-1);
      if (r == 0)
	return (1);
      if ((r = handle_input(infos, buf, fd_write, 0)) == -1)
	return (-1);
      if (r != 2 && buf[0] != '\n' && r != 1
	  && (write_socket(1, NICK_USAGE, fd_write) == -1
	      || write_socket(1, SERVER_USAGE, fd_write) == -1))
	return (-1);
      if (r == 2)
	infos->mode = 1;
      if (!memset(buf, 0, BUFFER))
	return (-1);
    }
  return (0);
}

static int		handle_select(t_infos* const infos, char* const buf,
				      fd_set* const fd_read,
				      fd_set* const fd_write)
{
  int			max_fd;
  struct timeval	tv;

  max_fd = 2;
  if (infos->mode > 0)
    max_fd = infos->fd + 1;
  tv.tv_sec = 5;
  tv.tv_usec = 0;
  if (select(max_fd, fd_read, fd_write, NULL, &tv) == -1)
    {
      if (errno == EINTR)
	return (0);
      perror("select");
      return (-1);
    }
  if (quit == 0 && infos->mode == 0)
    quit = offline(infos, buf, fd_read, fd_write);
  else if (quit == 0)
    {
      if (infos->mode == 1)
	quit = connection(infos, fd_write);
      if (quit == 0 && infos->mode == 2)
	quit = online(infos, buf, fd_read, fd_write);
    }
  return (0);
}

int		handle_online(t_infos* const infos)
{
  fd_set	fd_read;
  fd_set	fd_write;
  char		buf[BUFFER];

  signal(SIGINT, sig_handler);
  while (quit == 0)
    {
      if (!memset(buf, 0, BUFFER))
	{
	  perror("memset");
	  return (-1);
	}
      init_fd(infos, &fd_read, &fd_write);
      if (handle_select(infos, buf, &fd_read, &fd_write) == -1)
	return (-1);
    }
  return (quit);
}
