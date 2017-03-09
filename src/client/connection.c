/*
** connection.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Thu Jun  2 01:52:18 2016 Avel Docquin
** Last update Sun Jun  5 20:09:56 2016 Avel Docquin
*/

#include "connection.h"

static int	client_read(t_infos* const infos, char* const buf,
			    const fd_set* const fd_read,
			    const fd_set* const fd_write)
{
  ssize_t	s;
  int		r;

  if (!memset(buf, 0, BUFFER))
    {
      perror("memset");
      return (-1);
    }
  if (FD_ISSET(1, fd_read))
    {
      if ((s = read_socket(1, buf, NULL)) == -1)
	return (-1);
      if (buf[0]
	  && (r = handle_input(infos, buf, fd_write, 0)) == -1)
	return (-1);
      if (buf[0]
	  && r == 0 && write_socket(infos->fd, buf, fd_write) == -1)
	return (-1);
    }
  return (0);
}

int		online(t_infos* const infos, char* const buf,
		       const fd_set* const fd_read,
		       const fd_set* const fd_write)
{
  ssize_t	s;
  int		r;

  if (FD_ISSET(infos->fd, fd_read))
    {
      if ((s = read_socket(infos->fd, buf, &infos->s_in)) == -1)
	return (s);
      if (s == 0)
	{
	  infos->mode = 0;
	  return (1);
	}
      r = 0;
      if (buf[0] != 0 && (r = handle_input(infos, buf, fd_write, 1)) == -1)
	return (-1);
      if (r == 2)
	return (0);
      if (s > 0 && r == 0 && write_socket(1, buf, fd_write) == -1)
	return (-1);
    }
  if (client_read(infos, buf, fd_read, fd_write) == -1)
    return (-1);
  return (0);
}

int	connection(t_infos* const infos,
		   const fd_set* const fd_write)
{
  if (cmd_send("NICK", infos->username, infos, fd_write) == -1)
    return (-1);
  if (write_socket(infos->fd, USER, fd_write) == -1)
    return (-1);
  infos->mode = 2;
  return (0);
}
