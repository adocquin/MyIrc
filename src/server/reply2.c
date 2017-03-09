/*
** reply2.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Sun Jun  5 11:11:24 2016 Avel Docquin
** Last update Sun Jun  5 19:55:25 2016 masson mathieu
*/

#include "reply2.h"

static int	unknown_rpl(char* cmd, const unsigned int fd,
			    const fd_set* const fd_write, const t_env* const e)
{
  if (write_socket(fd, "421 ", fd_write) == -1
      || write_socket(fd, (char*)e[fd].username, fd_write) == -1)
    return (-1);
  if (write_socket(fd, " ", fd_write) == -1
      || write_socket(fd, cmd, fd_write) == -1)
    return (-1);
  if (write_socket(fd, UNKNOWN, fd_write) == -1)
    return (-1);
  return (0);
}

int	rpl_unknown_cmd(char* cmd, const unsigned int fd,
			const fd_set* const fd_write, const t_env* const e)
{
  int	i;
  int	r;

  i = r = -1;
  while (cmd[++i]);
  if (cmd[i] == '\n')
    {
      cmd[i] = '\0';
      r = 0;
    }
  else if (cmd[i - 1] == '\n')
    {
      cmd[i - 1] = '\0';
      r = 1;
    }
  if (unknown_rpl(cmd, fd, fd_write, e) == -1)
    return (-1);
  if (r != -1)
    cmd[i - r] = '\n';
  return (0);
}

int	rpl_no_such_nick(char* cmd, const unsigned int fd,
			 const fd_set* const fd_write, t_env* const e)
{
  if (write_socket(fd, "401 ", fd_write) == -1
      || write_socket(fd, e[fd].username, fd_write) == -1)
    return (-1);
  if (write_socket(fd, " ", fd_write) == -1
      || write_socket(fd, cmd, fd_write) == -1)
    return (-1);
  if (write_socket(fd, NO_NICK, fd_write) == -1)
    return (-1);
  return (0);
}
