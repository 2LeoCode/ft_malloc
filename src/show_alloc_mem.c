/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:46:07 by lsuardi           #+#    #+#             */
/*   Updated: 2022/11/16 00:04:22 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"
#include <stdio.h>

# define SHOW_ZONE_MEM( TYPE ) \
	do \
	{ \
		printf("%s : %p\n", # TYPE, !g_zones.TYPE ? NULL : g_zones.TYPE->memory); \
		for (t_zone * zone = g_zones.TYPE; zone; zone = zone->next) \
		{ \
			for (size_t i = 0; i < zone->allocated_block_cnt; ++i) \
			{ \
				t_block * block = zone->blocks[i]; \
				printf( \
					"%p - %p : %zu bytes\n", block->data,\
					(void *)(block->data + block->allocated_size), \
					block->allocated_size \
				); \
			} \
		} \
	} \
	while (0)

void show_alloc_mem( void )
{
	SHOW_ZONE_MEM(TINY);
	SHOW_ZONE_MEM(SMALL);
	SHOW_ZONE_MEM(LARGE);
}
