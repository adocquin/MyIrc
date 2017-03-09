/*
** handle.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Fri May 20 05:59:50 2016 Avel Docquin
** Last update Sun Jun  5 19:52:52 2016 masson mathieu
*/

#include "handle.h"

void	init_fd(t_env* const e, int* fd_max,
		fd_set* const fd_read, fd_set* const fd_write)
{
  int	i;

  i = -1;
  FD_ZERO(fd_read);
  FD_ZERO(fd_write);
  while (++i < MAX_FD)
    if (e[i].fd_type != FD_FREE)
      {
	FD_SET(i, fd_read);
	FD_SET(i, fd_write);
	*fd_max = i;
      }
}

int	handle_input(t_env* const e, char* buf, const fd_set* const fd_write,
		     const unsigned int fd)
{
  int	action;

  if (buf[0] == '\n' || buf[0] == '\r')
    return (0);
  action = orders_cmd(e, buf, fd, fd_write);
  if (action != 0)
    return (action);
  if (client_write(e, buf, fd_write, fd) == -1)
    return (-1);
  return (0);
}

int	handle_chat(t_env* const e, char buf[BUFFER],
		    const fd_set* const fd_read, const fd_set* const fd_write)
{
  int	i;

  i = -1;
  while (++i < MAX_FD)
    {
      if (FD_ISSET(i, fd_read))
	{
	  if (e[i].fct_read(e, i, buf, fd_write) == -1)
	    return (-1);
	  if (buf[0] && buf[0] != '\n' && buf[0] != '\r')
	    {
	      if (my_put_nbr(1, e[i].fd) == -1 || my_write(1, ":") == -1
		  || my_write(1, e[i].username) == -1)
		return (-1);
	      if (my_write(1, ": ") == -1 || my_write(1, buf) == -1)
		return (-1);
	    }
	}
    }
  return (0);
}
