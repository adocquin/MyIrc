/*
** misc.h for MyFTP in /home/docqui_a/work/c/MyFTP/src/server/
**
** Made by avel docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Thu Apr 28 22:38:42 2016 Avel Docquin
** Last update Sun Jun  5 13:26:52 2016 Avel Docquin
*/

#ifndef _MISC_H_
# define _MISC_H_

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

unsigned int	my_strlen(const char* const str);
int		my_write(const unsigned int fd, const char* const str);
int		my_put_nbr(const unsigned int fd, unsigned int nb);
unsigned int	my_compare_tab(const char tab1[], const char tab2[]);
unsigned int	my_atoi(const char* str);

#endif /* !_MISC_H_ */
