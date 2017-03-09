/*
** socket.c for my_irc in /home/docqui_a/PSU_2015_myirc/src/client/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Mon May 23 05:17:53 2016 Avel Docquin
** Last update Sun Jun  5 23:25:13 2016 Avel Docquin
*/

#include "socket.h"

static int	sigpipe = 0;

static void	sig_handler(int sig)
{
  if (sig == SIGPIPE)
    sigpipe = 1;
}

static int	msg_append(const char* const cmd,
			   const char* const arg, char** str)
{
  int		i;
  unsigned int	len;

  i = -1;
  while (arg[++i]);
  len = my_strlen(cmd) + my_strlen(arg) + 4;
  if (arg[i] != '\n' && arg[i - 1] != '\n')
    len = my_strlen(cmd) + my_strlen(arg) + 5;
  if (!(*str = malloc(len)))
    {
      perror("malloc");
      return (-1);
    }
  if (!strcpy(*str, cmd) || !strcat(*str, " ")
      || !strcat(*str, ":") || !strcat(*str, " ") || !strcat(*str, arg))
    i = -1;
  if (i != -1 && arg[i] != '\n' && arg[i - 1] != '\n' && !strcat(*str, "\n"))
    i = -1;
  if (i == -1)
    {
      free(*str);
      perror("cmd_append");
      return (-1);
    }
  return (0);
}

int	msg_send(const char* const cmd, const char* const arg,
		 const unsigned int fd, const fd_set* const fd_write)
{
  char	*str;

  str = NULL;
  if (msg_append(cmd, arg, &str) == -1)
    return (-1);
  if (write_socket(fd, str, fd_write) == -1)
    {
      free(str);
      return (-1);
    }
  free(str);
  return (0);
}

int	write_socket(unsigned int fd, char* buf, const fd_set* const fd_write)
{
  int	len;
  int	tmp;
  int	r;

  signal(SIGPIPE, sig_handler);
  if (FD_ISSET(fd, fd_write))
    {
      tmp = r = my_strlen(buf);
      len = 0;
      r = tmp;
      while (len != r && sigpipe == 0)
	{
	  r -= len;
	  if ((len = write(fd, buf + len, r)) == -1 && sigpipe != 1)
	    {
	      perror("write socket");
	      return (-1);
	    }
	}
    }
  return (0);
}
