/*
** commands.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Sat Jun  4 07:39:51 2016 Avel Docquin
** Last update Sun Jun  5 09:07:54 2016 Avel Docquin
*/

#include "commands.h"

int	list(const char** const cmd, t_infos* infos,
	     const fd_set* const fd_write, const unsigned int i)
{
  if (i == 1 || infos->mode != 2 || !cmd[0]
      || my_compare_tab(cmd[0], "/list") != 0)
    return (0);
  if (!cmd[1] && write_socket(infos->fd, "LIST\r\n", fd_write) == -1)
    return (-1);
  if (cmd[1] && cmd_send("LIST", cmd[1], infos, fd_write) == -1)
    return (-1);
  return (1);
}

int	msg(const char** const cmd, t_infos* infos,
	    const fd_set* const fd_write, const unsigned int i)
{
  if (i == 1 || infos->mode != 2 || !cmd[0]
      || my_compare_tab(cmd[0], "/msg") != 0)
    return (0);
  if (!cmd[1] && write_socket(infos->fd, "PRIVMSG\r\n", fd_write) == -1)
    return (-1);
  if ((cmd[1] && !cmd[2])
      && cmd_send("PRIVMSG", cmd[1], infos, fd_write) == -1)
    return (-1);
  if (cmd[1] && cmd[2]
      && priv_msg_send("PRIVMSG", cmd, infos, fd_write) == -1)
    return (-1);
  return (1);
}

int	join(const char** const cmd, t_infos* infos,
	     const fd_set* const fd_write, const unsigned int i)
{
  if (i == 1 || infos->mode != 2 || !cmd[0]
      || my_compare_tab(cmd[0], "/join") != 0)
    return (0);
  if (!cmd[1] && write_socket(infos->fd, "JOIN\r\n", fd_write) == -1)
    return (-1);
  if (cmd[1] && cmd_send("JOIN", cmd[1], infos, fd_write) == -1)
    return (-1);
  return (1);
}

int	users(const char** const cmd, t_infos* infos,
	      const fd_set* const fd_write, const unsigned int i)
{
  if (i == 1 || infos->mode != 2 || !cmd[0]
      || my_compare_tab(cmd[0], "/users") != 0)
    return (0);
  if (write_socket(infos->fd, "NAMES\r\n", fd_write) == -1)
    return (-1);
  return (1);
}

int	part(const char** const cmd, t_infos* infos,
	     const fd_set* const fd_write, const unsigned int i)
{
  if (i == 1 || infos->mode != 2 || !cmd[0]
      || my_compare_tab(cmd[0], "/part") != 0)
    return (0);
  if (!cmd[1] && write_socket(infos->fd, "PART\r\n", fd_write) == -1)
    return (-1);
  if (cmd[1] && cmd_send("PART", cmd[1], infos, fd_write) == -1)
    return (-1);
  return (1);
}
