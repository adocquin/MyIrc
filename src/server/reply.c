/*
** reply.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Sun Jun  5 05:58:19 2016 Avel Docquin
** Last update Sun Jun  5 20:23:49 2016 Avel Docquin
*/

#include "reply.h"

int	rpl_end_of_names(char* canal, const unsigned int fd,
			 const fd_set* const fd_write)
{
  if (write_socket(fd, "366 ", fd_write) == -1
      || write_socket(fd, canal, fd_write) == -1)
    return (-1);
  if (write_socket(fd, END_NAMES, fd_write) == -1)
    return (-1);
  return (0);
}

int	rpl_namreply(const unsigned int canal, const unsigned int fd,
		     const fd_set* const fd_write, t_env* const e)
{
  int	i;

  if (write_socket(fd, "353 ", fd_write) == -1)
    return (-1);
  if (canal == 0 && write_socket(fd, CANAL0, fd_write) == -1)
    return (-1);
  if (canal == 1 && write_socket(fd, CANAL1, fd_write) == -1)
    return (-1);
  if (canal == 2 && write_socket(fd, CANAL2, fd_write) == -1)
    return (-1);
  if (write_socket(fd, " :", fd_write) == -1)
    return (-1);
  i = -1;
  while (++i < MAX_FD)
    {
      if (e[i].ch[canal] == 1
	  && write_socket(fd, e[i].username, fd_write) == -1)
	return (-1);
      if (e[i].ch[canal] == 1 && write_socket(fd, " ", fd_write) == -1)
	return (-1);
    }
  if (write_socket(fd, "\r\n", fd_write) == -1)
    return (-1);
  return (0);
}

int	rpl_not_in_channel(char* canal, const unsigned int fd,
			   const fd_set* const fd_write)
{
  if (write_socket(fd, "442 ", fd_write) == -1
      || write_socket(fd, canal, fd_write) == -1)
    return (-1);
  if (write_socket(fd, NOT_IN_CHANNEL, fd_write) == -1)
    return (-1);
  return (0);
}

int	rpl_no_such_channel(char* canal, const unsigned int fd,
			    const fd_set* const fd_write)
{
  if (write_socket(fd, "403 ", fd_write) == -1
      || write_socket(fd, canal, fd_write) == -1)
    return (-1);
  if (write_socket(fd, BAD_JOIN, fd_write) == -1)
    return (-1);
  return (0);
}

int	rpl_topic(char* canal, const char* const sujet,
		  const unsigned int fd, const fd_set* const fd_write)
{
  if (write_socket(fd, "332 ", fd_write) == -1
      || write_socket(fd, canal, fd_write) == -1)
    return (-1);
  if (write_socket(fd, " :", fd_write) == -1
      || write_socket(fd, (char*)sujet, fd_write) == -1)
    return (-1);
  if (write_socket(fd, "\r\n", fd_write) == -1)
    return (-1);
  return (0);
}
