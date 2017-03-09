/*
** misc.h for MyFTP in /home/docqui_a/work/c/MyFTP/src/server/
**
** Made by avel docquin
** Login   <docqui_a@epitech.net>
**
** Started on  Thu Apr 28 22:38:42 2016 avel docquin
** Last update Wed Jun  1 00:55:38 2016 Avel Docquin
*/

#ifndef _MISC_H_
# define _MISC_H_

#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int		my_strlen(const char* const str);
int		my_write(int fd, const char* const str);
unsigned int	my_atoi(const char* str);
unsigned int	my_compare_tab(const char tab1[], const char tab2[]);

#endif /* !_MISC_H_ */
