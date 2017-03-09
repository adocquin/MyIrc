/*
** infos.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Wed Jun  1 01:29:00 2016 Avel Docquin
** Last update Sun Jun  5 20:10:52 2016 Avel Docquin
*/

#include "infos.h"

int		priv_msg_send(const char* const cmd, const char** const args,
			      const t_infos* const infos,
			      const fd_set* const fd_write)
{
  char		*str;
  unsigned int	len;

  len = my_strlen(cmd) + my_strlen(args[1]) + my_strlen(args[2]) + 6;
  if (!(str = malloc(len)))
    {
      perror("malloc");
      return (-1);
    }
  if (!strcpy(str, cmd) || !strcat(str, " ")
      || !strcat(str, args[1]) || !strcat(str, " ")
      || !strcat(str, args[2]) || !strcat(str, "\r\n"))
    {
      perror("cmd_append");
      return (-1);
    }
  if (write_socket(infos->fd, str, fd_write) == -1)
    {
      free(str);
      return (-1);
    }
  free(str);
  return (0);
}

int	cmd_send(const char* const cmd, const char* const arg,
		 const t_infos* const infos, const fd_set* const fd_write)
{
  char	*str;

  if (!(str = malloc(my_strlen(cmd) + my_strlen(arg) + 5)))
    {
      perror("malloc");
      return (-1);
    }
  if (!strcpy(str, cmd) || !strcat(str, " ")
      || !strcat(str, arg) || !strcat(str, "\r\n"))
    {
      perror("cmd_append");
      return (-1);
    }
  if (write_socket(infos->fd, str, fd_write) == -1)
    {
      free(str);
      return (-1);
    }
  free(str);
  return (0);
}

t_infos*	init_infos(t_infos* const infos, char** const cmd)
{
  if (!cmd)
    {
      if (!strcpy(infos->username, "Anonymous"))
	return (NULL);
      if (!(infos->pe = getprotobyname("TCP")))
	return (NULL);
      infos->s_in.sin_family = AF_INET;
      infos->mode = 0;
      infos->fd = 0;
      return (infos);
    }
  infos->ip = cmd[0];
  infos->port = my_atoi(cmd[1]);
  infos->s_in.sin_port = htons(infos->port);
  infos->s_in.sin_addr.s_addr = inet_addr(infos->ip);
  if ((infos->fd = socket(AF_INET, SOCK_STREAM, infos->pe->p_proto)) == -1)
    return (NULL);
  return (infos);
}
