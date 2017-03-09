/*
** parser.c for MyFTP in /media/sf_work/c/MyFTP
**
** Made by Avel Docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Wed May  4 00:29:13 2016 Avel Docquin
** Last update Sun Jun  5 19:51:36 2016 masson mathieu
*/

#include "parser.h"

void		free_2d_tab(char **tab)
{
  unsigned int	i;

  i = 0;
  if (tab)
    {
      while (tab[i])
	{
	  free(tab[i]);
	  ++i;
	}
      free(tab);
    }
}

static unsigned int	count_word(const char cmd[], const char c)
{
  unsigned int		i;
  unsigned int		word;
  int			tmp;

  i = word = 0;
  while (cmd[i])
    {
      if (cmd[i] == c)
	{
	  tmp = i + 1;
	  if (cmd[tmp] != c)
	    ++word;
	}
      ++i;
    }
  ++word;
  return (word);
}

static char*	command_word(const char cmd[], unsigned int pos, const char c)
{
  unsigned int	d;
  unsigned int	i;
  char*		word;

  d = 0;
  i = pos;
  while (cmd[i] && cmd[i] != '\n' && cmd[i] != c)
    {
      ++d;
      ++i;
    }
  if (!(word = (char*)malloc(sizeof(char) * (d + 1))))
    {
      perror("malloc");
      return (NULL);
    }
  word[d] = '\0';
  i = 0;
  while (cmd[pos] && cmd[pos] != '\n' && cmd[pos] != c)
    {
      word[i] = cmd[pos];
      ++i;
      ++pos;
    }
  return (word);
}

char**		command_to_tab(const char cmd[], char** tab, const char c)
{
  unsigned int	i;
  unsigned int	pos;
  unsigned int	tmp;

  if (my_strlen(cmd) == 0)
    return (NULL);
  i = count_word(cmd, c);
  if (!(tab = (char**)malloc(sizeof(char*) * (i + 1))))
    {
      perror("malloc");
      return (NULL);
    }
  tab[i] = NULL;
  tmp = pos = 0;
  while (tmp < i)
    {
      if (c == ' ')
	while (cmd[pos] == ' ')
	  ++pos;
      if (!(tab[tmp] = command_word(cmd, pos, c)))
	return (NULL);
      pos += my_strlen(tab[tmp]) + 1;
      ++tmp;
    }
  return (tab);
}
