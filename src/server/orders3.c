/*
** orders3.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Sun Jun  5 05:15:04 2016 Avel Docquin
** Last update Sun Jun  5 20:21:40 2016 Avel Docquin
*/

#include "orders3.h"

int	names(const char** const cmd, const unsigned int fd,
	      t_env* const e, const fd_set* const fd_write)
{
  int	i;

  if (!e || (cmd[0] && my_compare_tab(cmd[0], "NAMES") != 0))
    return (0);
  i = -1;
  while (e[fd].ch[++i])
    {
      if (e[fd].ch[i] == 1)
	{
	  if (i == 0 && (rpl_namreply(0, fd, fd_write, e) == -1
			 || rpl_end_of_names(CANAL0, fd, fd_write) == -1))
	    return (-1);
    	  if (i == 1 && (rpl_namreply(1, fd, fd_write, e) == -1
			 || rpl_end_of_names(CANAL0, fd, fd_write) == -1))
	    return (-1);
    	  if (i == 2 && (rpl_namreply(2, fd, fd_write, e) == -1
			 || rpl_end_of_names(CANAL0, fd, fd_write) == -1))
	    return (-1);
	}
    }
  return (1);
}

static int	join_canals(const char* const s, const unsigned int fd,
			    t_env* const e, const fd_set* const fd_write)
{
  if (canals_cmp(s) == 0)
    {
      if (rpl_topic(CANAL0, "channel admin", fd, fd_write) == -1)
	return (-1);
      e[fd].ch[0] = 1;
      return (1);
    }
  if (canals_cmp(s) == 1)
    {
      if (rpl_topic(CANAL1, "channel general", fd, fd_write) == -1)
	return (-1);
      e[fd].ch[1] = 1;
      return (1);
    }
  if (canals_cmp(s) == 2)
    {
      if (rpl_topic(CANAL2, "channel general", fd, fd_write) == -1)
	return (-1);
      e[fd].ch[2] = 1;
      return (1);
    }
  return (0);
}

int	join(const char** const cmd, const unsigned int fd,
	     t_env* const e, const fd_set* const fd_write)
{
  if (!e || (cmd[0] && my_compare_tab(cmd[0], "JOIN") != 0))
    return (0);
  if (!cmd[1])
    {
      if (write_socket(fd, "461 ", fd_write) == -1
	  || write_socket(fd, e[fd].username, fd_write) == -1)
	return (-1);
      if (write_socket(fd, ARGS_JOIN, fd_write) == -1
	  || write_socket(fd, "304 ", fd_write) == -1)
	return (-1);
      if (write_socket(fd, e[fd].username, fd_write) == -1
	  || write_socket(fd, SYNTAX_JOIN, fd_write) == -1)
	return (-1);
      return (1);
    }
  if (cmd[1])
    {
      if (join_canals(cmd[1], fd, e, fd_write) != 0)
	return (1);
      else if (rpl_no_such_channel((char*)cmd[1], fd, fd_write) == -1)
	return (-1);
    }
  return (0);
}

static int	join_part(const char* const s, const unsigned int fd,
			  t_env* const e, const fd_set* const fd_write)
{
  int		r;

  r = canals_cmp(s);
  if (r != -1)
    {
      if (e[fd].ch[r] == 1)
	e[fd].ch[r] = 0;
      else if (rpl_not_in_channel((char*)s, fd, fd_write) == -1)
	return (-1);
      return (1);
    }
  if (rpl_no_such_channel((char*)s, fd, fd_write) == -1)
    return (-1);
  return (0);
}

int	part(const char** const cmd, const unsigned int fd,
	     t_env* const e, const fd_set* const fd_write)
{
  int	r;

  if (!e || (cmd[0] && my_compare_tab(cmd[0], "PART") != 0))
    return (0);
  if (!cmd[1])
    {
      if (write_socket(fd, "461 ", fd_write) == -1
	  || write_socket(fd, e[fd].username, fd_write) == -1)
	return (-1);
      if (write_socket(fd, ARGS_PART, fd_write) == -1
	  || write_socket(fd, "304 ", fd_write) == -1)
	return (-1);
      if (write_socket(fd, e[fd].username, fd_write) == -1
	  || write_socket(fd, SYNTAX_PART, fd_write) == -1)
	return (-1);
      return (1);
    }
  if (cmd[1])
    {
      if ((r = join_part(cmd[1], fd, e, fd_write)) == -1)
	return (-1);
      return (1);
    }
  return (0);
}
