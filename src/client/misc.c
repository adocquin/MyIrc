/*
** misc.c for My_FTP in /home/docqui_a/work/c/MyFTP/src/server/
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Thu Apr 28 22:38:04 2016 Avel Docquin
** Last update	Tue May 24 04:20:27 2016 Avel Docquin
*/

#include "misc.h"

int		my_strlen(const char* const str)
{
  unsigned int	i;

  i = 0;
  while (str[i])
    ++i;
  return (i);
}

int	my_write(const int fd, const char* const str)
{
  if (write(fd, str, my_strlen(str)) == -1)
    {
      perror("write");
      return (-1);
    }
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
