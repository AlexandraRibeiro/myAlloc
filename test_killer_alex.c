/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_killer_alex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/01 20:20:48 by aribeiro          #+#    #+#             */
/*   Updated: 2017/01/03 13:30:29 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

/*
** change according the version to test
*/
#include "memory.h"

static void	my_putchar(char c)
{
	write(1, &c, 1);
}

static void	my_putstr(char const *str, char const *str1, char const *str2)
{
	size_t	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
		my_putchar(str[i++]);
	if (str1 == NULL)
		return ;
	i = 0;
	while (str1[i] != '\0')
		my_putchar(str1[i++]);
	if (str2 == NULL)
		return ;
	i = 0;
	while (str2[i] != '\0')
		my_putchar(str2[i++]);	
}


static void	*my_memcpy(void *s1, const void *s2, size_t n)
{
	char	*ptr1;
	char	*ptr2;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ptr1 = (char*)s1;
	ptr2 = (char*)s2;
	i = 0;
	while (i < n)
	{
		ptr1[i] = ptr2[i];
		i++;
	}
	s1 = (void *)ptr1;
	return (s1);
}

// to put before a malloc or free or realloc
static void	stress_zone(char *s1)
{
	my_memcpy((void *)(((int)s1/getpagesize()) * getpagesize()),
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 65);
}


int main()
{
	char	*s1;
	char 	*s2;
	char 	*s3;
	int		i;
	int		j;
	
	s1 = (char *)malloc(16);
	// to destruct the zone struct
	stress_zone(s1);
	s2 = (char *)malloc(16);
	s3 = (char *)malloc(16);
	i = (void *)s2 - (void *)s1;
	j = i;
	my_memcpy(s1,"Hello from s1 !", 16);
	my_memcpy(s2,"Hello from s2 !", 16);
	my_memcpy(s3,"Hello from s3 !", 16);
	
	my_putstr("s1 = ", s1, "\n");
	my_putstr("s2 = ", s2, "\n");
	my_putstr("s3 = ", s3, "\n");
	my_putstr("", "", "\n\n");
	if(i < 0)
		i = -i;
	s2[i] = '\0';	
	while (i-- > 0)
		s2[i] = 'A';
	my_putstr("s2 = ", s2, "\n");
	my_putstr("s1 = ", s1, "\n");
	my_putstr("s3 = ", s3, "\n");
	
	if (j < 0)
		s2 = (char *)realloc(s2, -j + 33);
	else
		s2 = (char *)realloc(s2, j + 33);
	my_putstr("s2 = ", s2, "\n");
	my_putstr("s1 = ", s1, "\n");
	my_putstr("s3 = ", s3, "\n");
	
		
	return 0;
}

