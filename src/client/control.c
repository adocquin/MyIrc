/*
** control.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Tue May 24 18:45:34 2016 Avel Docquin
** Last update Sun Jun  5 20:10:23 2016 Avel Docquin
*/

#include "control.h"

int	nick(const char** const cmd, t_infos* infos,
	     const fd_set* const fd_write, const unsigned int i)
{
  int	len;

  if (i == 1 || !cmd[0] || my_compare_tab(cmd[0], "/nick") != 0)
    return (0);
  if (!cmd[1])
    {
      if (write_socket(1, NICK_USAGE, fd_write) == -1)
	return (-1);
      return (1);
    }
  if (!memset(infos->username, 0, USERNAME))
    return (-1);
  len = my_strlen(cmd[1]);
  if (len  < 1 || len > 9)
    {
      if (write_socket(1, NICK_USAGE, fd_write) == -1)
	return (-1);
      return (1);
    }
  if (!strcpy(infos->username, cmd[1]))
    return (-1);
  if (infos->mode == 2
      && cmd_send("NICK", infos->username, infos, fd_write) == -1)
    return (-1);
  return (1);
}

static int	server_connection(char** address, t_infos* infos)
{
  if (!(infos = init_infos(infos, (char** const)address)))
    {
      free_2d_tab(address);
      return (-1);
    }
  if (connect(infos->fd, (struct sockaddr *)&infos->s_in,
	      sizeof(infos->s_in)) == -1)
    {
      free_2d_tab(address);
      perror(ERROR);
      return (1);
    }
  free_2d_tab(address);
  return (2);
}

int		server(const char** const cmd, t_infos* infos,
		       const fd_set* const fd_write, const unsigned int i)
{
  char**	address;
  int		r;

  address = NULL;
  if (i == 1 || !cmd[0] || infos->mode != 0
      || my_compare_tab(cmd[0], "/server") != 0)
    return (0);
  if (!cmd[1])
    {
      if (write_socket(1, SERVER_USAGE, fd_write) == -1)
	return (-1);
      return (1);
    }
  if (!(address = command_to_tab(cmd[1], address, ':')))
    return (-1);
  if (address[1] && !address[2]){
    r = server_connection(address, infos);
    return (r);
  }
  return (0);
}

int	ping(const char** const cmd, t_infos* infos,
	     const fd_set* const fd_write, const unsigned int i)
{
  if (i == 0 || !cmd[0] || infos->mode == 0)
    return (0);
  if (my_compare_tab(cmd[0], "PING\r") != 0
      && my_compare_tab(cmd[0], "PING") != 0)
    return (0);
  if (!cmd[1] && write_socket(infos->fd, "PONG\r\n", fd_write) == -1)
    return (-1);
  if (cmd[1] && cmd_send("PONG", cmd[1], infos, fd_write) == -1)
    return (-1);
  return (1);
}

int		handle_input(t_infos* const infos, const char* const buf,
			     const fd_set* const fd_write,
			     const unsigned int i)
{
  optr		*tab;
  char**	cmd;
  int		d;
  int		action;

  cmd = NULL;
  d = -1;
  tab = NULL;
  if (func_tab(&tab) == -1)
    return (-1);
  if (!(cmd = command_to_tab(buf, cmd, ' ')))
    {
      free(tab);
      return (-1);
    }
  while (tab[++d])
    if ((action = tab[d]((const char** const)cmd, infos, fd_write, i)) != 0)
      {
	free(tab);
	free_2d_tab(cmd);
	return (action);
      }
  free(tab);
  free_2d_tab(cmd);
  return (0);
}
