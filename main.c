/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:20:37 by lsuardi           #+#    #+#             */
/*   Updated: 2022/11/16 00:13:05 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef STD
# include <stdlib.h>
#else
# include "malloc.h"
#endif

int main( )
{
	void * ptr[1000] = { NULL };

	ptr[0] = malloc(100000);
	ptr[4] = malloc(1000);
	ptr[5] = malloc(10000);
	//show_alloc_mem();
	//free(ptr[3]);
	free(ptr[5]);
	//free(ptr[7]);
	//free(ptr[8]);
	//free(ptr[4]);
	//show_alloc_mem();
	//ptr[3] = malloc(100);
	//ptr[4] = malloc(0);
	ptr[5] = malloc(10000);
	//ptr[7] = malloc(1000000);
	//ptr[8] = malloc(10);
	//show_alloc_mem();
	for (int i = 0; i < 1000; i++)
	{
		if (ptr[i])
		{
	show_alloc_mem();
			free(ptr[i]);
		}
	}
	return (0);
}
