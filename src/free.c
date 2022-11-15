/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:22:12 by lsuardi           #+#    #+#             */
/*   Updated: 2022/11/16 00:23:15 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

void free( void * ptr )
{
	t_block * block;
	t_zone * zone;

	if (!ptr)
		return ;
	block = (void *)((uint8_t *)ptr - sizeof(t_block));
	zone = block->zone;
	if (!block->freed)
	{
		block->freed = true;
		++zone->freed_block_cnt;
		if (block->prev)
		{
			block->prev->next = block->next;
			block->prev->available_size += block->available_size + sizeof(t_block);
			zone->blocks[block->index] = zone->blocks[--zone->freed_block_cnt];
		}
		if (block->next)
			block->next->prev = block->prev;
		SWAP(
			zone->blocks[block->index],
			zone->blocks[zone->allocated_block_cnt - 1]
		);
		--zone->allocated_block_cnt;
	}
	printf("%p\n", zone);
	if (!zone->allocated_block_cnt)
	{
		t_zone * tmp = NULL;
		t_zone ** addr = NULL;
		if (zone->next)
		{
			printf("tmp got next\n");
			tmp = zone->next;
			zone->next->prev = zone->prev;
		}
		if (zone->prev)
			zone->prev->next = zone->next;
		while (zone->prev)
			zone = zone->prev;
		addr = zone->addr;
		munmap(
			zone,
			zone == g_zones.TINY ? TINY_ZONE_SIZE :
			zone == g_zones.SMALL ? SMALL_ZONE_SIZE :
			LARGE_ZONE_SIZE
		);
		*addr = tmp;
		if (*addr)
		{
			write(1, "got here\n", 9);
			(*addr)->addr = addr;
		}
	}
}
