/*
** misc.c for My_FTP in /home/docqui_a/work/c/MyFTP/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Thu Apr 28 22:38:04 2016 Avel Docquin
** Last update Sun Jun  5 23:19:00 2016 Avel Docquin
*/

#include "misc.h"

unsigned int	my_strlen(const char* const str)
{
  unsigned int	i;

  i = 0;
  while (str[i])
    ++i;
  return (i);
}

int	my_write(const unsigned int fd, const char* const str)
{
  if (write(fd, str, my_strlen(str)) == -1 && errno != EPIPE)
    {
      perror("write");
      return (-1);
    }
  return (0);
}

int	my_put_nbr(const unsigned int fd, unsigned int nb)
{
  char	c[2];

  if (nb > 9)
    my_put_nbr(fd, nb / 10);
  c[0] = (nb % 10 + '0');
  c[1] = '\0';
  if (my_write(fd, c) == -1)
    return (-1);
  return (0);
}

unsigned int	my_compare_tab(const char tab1[], const char tab2[])
{
  unsigned int	i;

  i = 0;
  while (tab1[i] && tab2[i])
    {
      if (tab1[i] == tab2[i])
	++i;
      else
	return (1);
    }
  if (tab1[i] || tab2[i])
    return (1);
  return (0);
}

unsigned int	my_atoi(const char* str)
{
  unsigned int	i;
  unsigned int	res;

  i = res = 0;
  while (str[i])
    {
      res = res * 10 + (str[i] - '0');
      ++i;
    }
  return (res);
}
