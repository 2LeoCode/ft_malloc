/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:54:14 by lsuardi           #+#    #+#             */
/*   Updated: 2022/11/16 00:22:06 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "malloc_int.h"

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putnbr(size_t n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

# define MALLOC_ZONE_DECL( TYPE ) \
	void * malloc_zone_ ## TYPE ( size_t size ) \
	{ \
		/* Bonus */ \
		pthread_mutex_lock(&g_zones.TYPE ## _LOCK); \
 \
		static t_block * last_block = NULL; \
		static t_zone * prev_zone = NULL; \
		t_zone ** zone; \
		t_block * block; \
		size_t real_size = ALIGN_NEXT(size) + sizeof(t_block); \
 \
		zone = &g_zones.TYPE; \
		while (*zone && (*zone)->allocated_block_cnt == BLOCKS_PER_ZONE) \
		{ \
			prev_zone = *zone; \
			zone = &(*zone)->next; \
		} \
		CheckZone: \
		if (!*zone) \
		{ \
			*zone = mmap( \
				NULL, TYPE ## _ZONE_SIZE, PROT_READ | PROT_WRITE, \
				MAP_ANON | MAP_PRIVATE, -1, 0 \
			); \
			if (*zone == MAP_FAILED) \
			{ \
				errno = ENOMEM; \
				return (NULL); \
			} \
			(*zone)->addr = zone; \
			(*zone)->allocated_block_cnt = 0; \
			(*zone)->freed_block_cnt = 0; \
			(*zone)->reserved_size = 0; \
			(*zone)->next = NULL; \
			(*zone)->prev = prev_zone; \
			if (prev_zone) \
			{ \
				write(1, "prev_zone->next = *zone\n", 24); \
				prev_zone->next = *zone; \
			} \
			prev_zone = *zone; \
		} \
		for (size_t i = 0; i < (*zone)->freed_block_cnt; ++i) \
		{ \
			block = (*zone)->blocks[(*zone)->allocated_block_cnt + i]; \
			if (block->available_size >= size) \
			{ \
				block->freed = false; \
				block->allocated_size = size; \
				--(*zone)->freed_block_cnt; \
				SWAP( \
					(*zone)->blocks[(*zone)->allocated_block_cnt + i], \
					(*zone)->blocks[(*zone)->allocated_block_cnt] \
				); \
				goto Success; \
			} \
		} \
		if ((*zone)->reserved_size + real_size \
			> TYPE ## _MEMORY_SIZE) \
		{ \
			zone = &(*zone)->next; \
			goto CheckZone; \
		} \
		memmove( \
			(*zone)->blocks + (*zone)->allocated_block_cnt + (*zone)->freed_block_cnt, \
			(*zone)->blocks + (*zone)->allocated_block_cnt, \
			sizeof(*(*zone)->blocks) * (*zone)->freed_block_cnt \
		); \
		block = (*zone)->blocks[(*zone)->allocated_block_cnt] \
			= (t_block *)((*zone)->memory + (*zone)->reserved_size); \
		block->prev = last_block; \
		if (last_block) \
			last_block->next = block; \
		last_block = block; \
		block->next = NULL; \
		block->zone = *zone; \
		block->freed = false; \
		block->allocated_size = size; \
		if (size <= 24) \
			block->available_size = 32; \
		else \
			block->available_size = ALIGN_NEXT(size); \
		(*zone)->reserved_size += real_size; \
		Success: \
		block->index = (*zone)->allocated_block_cnt++; \
		/* Bonus */ \
		pthread_mutex_unlock(&g_zones.TYPE ## _LOCK); \
		return (block->data); \
	}

MALLOC_ZONE_DECL(TINY)
MALLOC_ZONE_DECL(SMALL)
MALLOC_ZONE_DECL(LARGE)

void * malloc( size_t size )
{
	if (size <= TINY_AVAILABLE_SIZE)
		return (malloc_zone_TINY(size));
	if (size <= SMALL_AVAILABLE_SIZE)
		return (malloc_zone_SMALL(size));
	return (malloc_zone_LARGE(size));
}
