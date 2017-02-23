/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 14:39:59 by aribeiro          #+#    #+#             */
/*   Updated: 2017/02/23 11:29:27 by aribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int		main()
{
	int i;
	// char *tiny = NULL;
	// char *tiny2 = NULL;
	// char *tiny3 = NULL;
	//
	// char *small = NULL;
	// char *small2 = NULL;
	// char *small3 = NULL;

	char *large= NULL;
	// char *large2 = NULL;
	// char *large3 = NULL;

//
// /*******************************************************************************
// **								TEST TINY
// *******************************************************************************/
// 	i = 0;
// 	tiny = (char *)malloc(sizeof(char) * 100);
// 	tiny2 = (char *)malloc(sizeof(char) * 80);
// 	tiny3 = (char *)malloc(sizeof(char) * 40);
// write(1, "\n-> retour main\n", 16);
// printf("(debug main) ADDR 1er ptr tiny = %p\n", tiny);
// printf("(debug main) ADDR 2eme ptr tiny2 = %p, decalage avec tiny = %ld\n", tiny2, tiny2 - tiny);
// printf("(debug main) ADDR 3eme ptr tiny3 = %p, decalage avec tiny2 = %ld\n", tiny3, tiny3 - tiny2);
// 	while (i < 126)
// 	{
// 		tiny[i] = 'A';
// 		i++;
// 	}
// 	tiny[i] = '\n';
// 	tiny[++i] = '\0';
//
//
// 	i = 0;
// 	while (i < 126)
// 	{
// 		tiny2[i] = 'B';
// 		i++;
// 	}
// 	tiny2[i] = '\n';
// 	tiny2[++i] = '\0';
//
//
// 	i = 0;
// 	while (i < 126)
// 	{
// 		tiny3[i] = 'C';
// 		i++;
// 	}
// 	tiny3[i] = '\n';
// 	tiny3[++i] = '\0';
//
//
// 	ft_putstr_fd(tiny, 1);
// 	ft_putstr_fd(tiny2, 1);
// 	ft_putstr_fd(tiny3, 1);
//
// 	printf("(debug main) ADDR 1er ptr tiny = %p\n", tiny);
// 	printf("(debug main) ADDR 2eme ptr tiny2 = %p, decalage avec tiny = %ld\n", tiny2, tiny2 - tiny);
// 	printf("(debug main) ADDR 3eme ptr tiny3 = %p, decalage avec tiny2 = %ld\n", tiny3, tiny3 - tiny2);
//
// 	i = 0;
// 	while (i < 126)
// 	{
// 		tiny3[i] = 'D';
// 		i++;
// 	}
// 	tiny3[i] = '\n';
// 	tiny3[++i] = '\0';
//
// 	i = 0;
// 	while (i < 126)
// 	{
// 		tiny2[i] = 'E';
// 		i++;
// 	}
// 	tiny2[i] = '\n';
// 	tiny2[++i] = '\0';
//
// 	i = 0;
// 	while (i < 126)
// 	{
// 		tiny[i] = 'F';
// 		i++;
// 	}
// 	tiny[i] = '\n';
// 	tiny[++i] = '\0';
//
// 	ft_putstr_fd(tiny, 1);
// 	ft_putstr_fd(tiny2, 1);
// 	ft_putstr_fd(tiny3, 1);
//
//
// 	/*******************************************************************************
// 	**								TEST SMALL
// 	*******************************************************************************/
// 	i = 0;
//
// 	small = (char *)malloc(sizeof(char) * (TI_MAX + 1));
// 	small2 = (char *)malloc(sizeof(char) * 200);
// 	small3 = (char *)malloc(sizeof(char) * SM_MAX); //SM_MAX
// write(1, "\n-> retour main\n", 16);
// printf("(debug main) ADDR 1er ptr small = %p\n", small);
// printf("(debug main) ADDR 2eme ptr small2 = %p, decalage avec small = %ld\n", small2, small2 - small);
// printf("(debug main) ADDR 3eme ptr small3 = %p, decalage avec small2 = %ld\n", small3, small3 - small2);
// 	while (i < 99)
// 	{
// 		small[i] = 'A';
// 		i++;
// 	}
// 	small[i] = '\n';
// 	small[++i] = '\0';
//
//
// 	i = 0;
// 	while (i < 198)
// 	{
// 		small2[i] = 'B';
// 		i++;
// 	}
// 	small2[i] = '\n';
// 	small2[++i] = '\0';
//
//
// 	i = 0;
// 	while (i < 484)
// 	{
// 		small3[i] = 'C';
// 		i++;
// 	}
// 	small3[i] = '\n';
// 	small3[++i] = '\0';
//
//
// 	ft_putstr_fd(small, 1);
// 	ft_putstr_fd(small2, 1);
// 	ft_putstr_fd(small3, 1);
//
// 	printf("(debug main) ADDR 1er ptr small = %p\n", small);
// 	printf("(debug main) ADDR 2eme ptr small2 = %p, decalage avec small = %ld\n", small2, small2 - small);
// 	printf("(debug main) ADDR 3eme ptr small3 = %p, decalage avec small2 = %ld\n", small3, small3 - small2);
//
// 	i = 0;
// 	while (i < 99)
// 	{
// 		small3[i] = 'D';
// 		i++;
// 	}
// 	small3[i] = '\n';
// 	small3[++i] = '\0';
//
// 	i = 0;
// 	while (i < 198)
// 	{
// 		small2[i] = 'E';
// 		i++;
// 	}
// 	small2[i] = '\n';
// 	small2[++i] = '\0';
//
// 	i = 0;
// 	while (i < 483)
// 	{
// 		small[i] = 'F';
// 		i++;
// 	}
// 	small[i] = '\n';
// 	small[++i] = '\0';
//
// 	ft_putstr_fd(small, 1);
// 	ft_putstr_fd(small2, 1);
// 	ft_putstr_fd(small3, 1);
//

	/*******************************************************************************
	**								TEST LARGE
	*******************************************************************************/
	i = 0;
	// printf("\n\n_________________________________________________________________\n");
	// printf("sizeof t_header_lg = %zu\n",sizeof(t_header_lg));
	// printf("_________________________________________________________________\n\n");

		large = (char *)malloc(sizeof(char) * 10000);
		// large2 = (char *)malloc(sizeof(char) * 4000);
		// large3 = (char *)malloc(sizeof(char) * 10300);
	write(1, "\n-> retour main\n", 16);
	// printf("(debug main) ADDR 1er ptr large = %p\n", large);
	// printf("(debug main) ADDR 2eme ptr large2 = %p\n", large2);
	// printf("(debug main) ADDR 3eme ptr large3 = %p\n", large3);
		while (i < 4006)
		{
			large[i] = 'L';
			i++;
		}
		large[i] = '\n';
		large[++i] = '\0';


		// i = 0;
		// while (i < 3999)
		// {
		// 	large2[i] = 'l';
		// 	i++;
		// }
		// large2[i] = '\n';
		// large2[++i] = '\0';
		//
		//
		// i = 0;
		// while (i < 10299)
		// {
		// 	large3[i] = 'X';
		// 	i++;
		// }
		// large3[i] = '\n';
		// large3[++i] = '\0';


		ft_putstr_fd(large, 1);
		// ft_putstr_fd(large2, 1);
		// ft_putstr_fd(large3, 1);

		show_alloc_map();
		// my_free((void *)large);
		// show_alloc_map();

	return (0);
}
