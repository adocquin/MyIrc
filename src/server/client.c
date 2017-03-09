/*
** client.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Tue May 17 02:36:06 2016 Avel Docquin
** Last update Sun Jun  5 23:16:46 2016 Avel Docquin
*/

#include "server.h"

char*	username_cp(char* const username, const char* const cmd)
{
  int	i;

  i = 0;
  while (cmd[i] && cmd[i] != '\r' && cmd[i] != '\n')
    ++i;
  if (i > USERNAME)
    return (NULL);
  i = -1;
  while (++i < USERNAME + 1 && cmd[i] && cmd[i] != '\r' && cmd[i] != '\n')
    username[i] = cmd[i];
  username[i] = '\0';
  return (username);
}

int		client_write(const t_env* const e, char *buf,
			     const fd_set* const fd_write,
			     const unsigned int fd)
{
  int		i;
  unsigned int	tmp;
  unsigned int	r;

  i = tmp = -1;
  r = 0;
  while (++tmp < 3)
    if (e[fd].ch[tmp] == 1)
      i = 1;
  if (i == -1 && rpl_unknown_cmd(buf, fd, fd_write, e) == -1)
    return (-1);
  i = tmp = -1;
  while (++i < MAX_FD)
    if (e[i].fd_type != FD_FREE && e[i].fd_type == FD_CLIENT)
      {
	while (++tmp < 3)
	  if (e[fd].ch[tmp] == 1 && e[i].ch[tmp] == 1)
	    r = 1;
	tmp = 0;
	if (r == 1 && msg_send(e[fd].username, buf, e[i].fd, fd_write) == -1)
	  return (-1);
	r = 0;
      }
  return (0);
}

static int	client_close(t_env* const e, const unsigned int fd)
{
  if (my_put_nbr(1, fd) == -1
      || my_write(1, ": Connection closed\n") == -1)
    return (-1);
  if (close(fd) == -1)
    {
      perror("client close");
      return (-1);
    }
  e[fd].fd_type = FD_FREE;
  return (0);
}

int		client_read(t_env* const e, const unsigned int fd,
			    char* buf, const fd_set* const fd_write)
{
  ssize_t	r;
  socklen_t 	c_length;
  int		action;

  action = 0;
  c_length = (socklen_t)sizeof(struct sockaddr_in);;
  r = recvfrom(fd, buf, BUFFER, 0, (struct sockaddr*)&e[fd].sin, &c_length);
  if (r == -1 && errno == ENOMEM)
    {
      perror("client recvfrom");
      return (-1);
    }
  else if (r == -1)
    r = 0;
  if (r > 0 && (action = handle_input(e, buf, fd_write, fd)) == -1)
    return (-1);
  if (action == -2)
    r = 0;
  if (r == 0 && client_close(e, fd) == -1)
    return (-1);
  return (0);
}

int	add_client(t_env* e, int s)
{
  int	cs;
  int	client_sin_len;

  client_sin_len = sizeof(e[0].sin);
  cs = accept(s, (struct sockaddr*)&e[0].sin, (socklen_t*)&client_sin_len);
  if (cs == -1)
    {
      perror("client accept");
      return (-1);
    }
  username_cp(e[cs].username, "Anonymous");
  e[cs].fd = cs;
  e[cs].fd_type = FD_CLIENT;
  e[cs].fct_read = (fct)&(client_read);
  e[cs].fct_write = (fct)&(client_write);
  return (0);
}
