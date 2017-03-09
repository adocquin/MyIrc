/*
** orders.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Wed May 25 00:51:58 2016 Avel Docquin
** Last update Sun Jun  5 20:22:13 2016 Avel Docquin
*/

#include "orders.h"

int	canals_cmp(const char* const s)
{
  if (my_compare_tab(s, CANAL0) == 0 || my_compare_tab(s, "#admin\n") == 0
      || my_compare_tab(s, "#admin\r\n") == 0)
    return (0);
  if (my_compare_tab(s, CANAL1) == 0 || my_compare_tab(s, "#general1\n") == 0
      || my_compare_tab(s, "#general1\r\n") == 0)
    return (1);
  if (my_compare_tab(s, CANAL2) == 0 || my_compare_tab(s, "#general2\n") == 0
      || my_compare_tab(s, "#general2\r\n") == 0)
    return (2);
  return (-1);
}

static int	user(const char** const cmd, const unsigned int fd,
		     t_env* const e, const fd_set* const fd_write)
{
  if (!e || (cmd[0] && my_compare_tab(cmd[0], "USER") != 0))
    return (0);
  if (cmd[1] && cmd[2] && cmd[3])
    {
      if (write_socket(fd, "PING\r\n", fd_write) == -1)
	return (-1);
      return (1);
    }
  else
    {
      if (write_socket(fd, ERR_ARGS, fd_write) == -1)
	return (-1);
      return (1);
    }
  return (0);
}

static int	nick(const char** const cmd, const unsigned int fd,
		     t_env* const e, const fd_set* const fd_write)
{
  if (cmd[0] && my_compare_tab(cmd[0], "NICK") != 0)
    return (0);
  if (cmd[1])
    {
      if (!username_cp(e[fd].username, cmd[1]))
	{
	  if (write_socket(fd, ERR_NICK, fd_write) == -1)
	    return (-1);
	}
      my_write(fd, "PING\r\n");
      return (1);
    }
  else
    {
      if (write_socket(fd, ERR_ARGS, fd_write) == -1)
	return (-1);
      return (1);
    }
  return (0);
}

static int	func_tab(optr** tab, char*** cmd, char* const buf)
{
  if (!(*tab = malloc(sizeof(optr) * 10)))
    {
      perror("malloc");
      return (-1);
    }
  (*tab)[0] = nick;
  (*tab)[1] = user;
  (*tab)[2] = pong;
  (*tab)[3] = quit;
  (*tab)[4] = privmsg;
  (*tab)[5] = list;
  (*tab)[6] = join;
  (*tab)[7] = part;
  (*tab)[8] = names;
  (*tab)[9] = NULL;
  if (!(*cmd = command_to_tab(buf, *cmd)))
    {
      free(*tab);
      return (-1);
    }
  return (0);
}

int		orders_cmd(t_env* const e, char* const buf,
			   const unsigned int fd, const fd_set* const fd_write)
{
  optr* 	tab;
  char**	cmd;
  int		i;
  int		action;
  int		r;

  i = -1;
  cmd = NULL;
  tab = NULL;
  r = action = 0;
  if (func_tab(&tab, &cmd, buf) == -1)
    return (-1);
  while (tab[++i] && r == 0)
    {
      if ((action = tab[i](cmd, fd, e, fd_write)) != 0)
	r = 1;
    }
  free(tab);
  free_2d_tab(cmd);
  return (action);
}
