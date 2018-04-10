/*
** orders2.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Thu May 26 23:12:23 2016 Avel Docquin
** Last update Sun Jun  5 15:21:33 2016 Avel Docquin
*/

#include "orders2.h"

int	list(const char** const cmd, const unsigned int fd,
	     t_env* const e, const fd_set* const fd_write)
{
  if (!e || (cmd[0] && my_compare_tab(cmd[0], "LIST") != 0))
    return (0);
  if (write_socket(fd, "321 ", fd_write) == -1
      || write_socket(fd, e[fd].username, fd_write) == -1)
    return (-1);
  if (write_socket(fd, " Channel :Users Name\r\n322 ", fd_write) == -1
      || write_socket(fd, e[fd].username, fd_write) == -1)
    return (-1);
  if (write_socket(fd, ADMIN, fd_write) == -1
      || write_socket(fd, "322 ", fd_write) == -1)
    return (-1);
  if (write_socket(fd, e[fd].username, fd_write) == -1
      || write_socket(fd, GENERAL1, fd_write) == -1)
    return (-1);
  if (write_socket(fd, "322 ", fd_write) == -1
      || write_socket(fd, e[fd].username, fd_write) == -1)
    return (-1);
  if (write_socket(fd, GENERAL2, fd_write) == -1
      || write_socket(fd, "323 ", fd_write) == -1)
    return (-1);
  if (write_socket(fd, e[fd].username, fd_write) == -1
      || write_socket(fd, " :End of channel list.\r\n", fd_write) == -1)
    return (-1);
  return (1);
}

int	privmsg(const char** const cmd, const unsigned int fd,
		t_env* const e, const fd_set* const fd_write)
{
  int	i;
  int	r;

  r = 0;
  if (!e || (cmd[0] && my_compare_tab(cmd[0], "PRIVMSG") != 0))
    return (0);
  if ((!cmd[1] && write_socket(fd, ERR_RECIP, fd_write) == -1)
      || ((cmd[1] && !cmd[2]) && write_socket(fd, ERR_TEXT, fd_write) == -1))
    return (-1);
  i = -1;
  if (cmd[1] && cmd[2])
    while (++i < MAX_FD)
      {
	if (e[i].fd_type != FD_FREE
	    && my_compare_tab(e[i].username, cmd[1]) == 0)
	  {
	    if (msg_send(e[fd].username, cmd[2], e[i].fd, fd_write) == -1)
	      return (-1);
	    r = 1;
	  }
      }
  if (r == 0 && rpl_no_such_nick((char*)cmd[1], fd, fd_write, e) == -1)
    return (-1);
  return (1);
}

int	pong(const char** const cmd, const unsigned int fd,
	     t_env* const e, const fd_set* const fd_write)
{
  if (!e || (cmd[0] && my_compare_tab(cmd[0], "PONG") != 0))
    return (0);
  if (write_socket(fd, "001 MY_IRC\r\n", fd_write) == -1)
    return (-1);
  return (1);
}

int	quit(const char** const cmd, const unsigned int fd, t_env* const e)
{
  if (fd == 0 || !e || !cmd[0])
    return (0);
  if (my_compare_tab(cmd[0], "QUIT") != 0)
    return (0);
  return (-2);
}
