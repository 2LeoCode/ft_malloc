/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:34:47 by lsuardi           #+#    #+#             */
/*   Updated: 2022/11/15 23:57:15 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

static void * ft_memcpy(void * dst, const void * src, size_t n)
{
	uint8_t * d = dst;
	const uint8_t * s = src;

	while (n--)
		*d++ = *s++;
	return (dst);
}

void * realloc( void * ptr, size_t size )
{
	t_block * block;
	t_zone * zone;
	void * new_ptr;
	size_t memory_size;

	if (!ptr)
		return (malloc(size));
	block = (void *)((uint8_t *)ptr - sizeof(t_block));
	if (block->available_size >= size)
	{
		block->allocated_size = size;
		return (ptr);
	}
	zone = block->zone;
	memory_size = zone == g_zones.TINY ? TINY_MEMORY_SIZE :
		zone == g_zones.SMALL ? SMALL_MEMORY_SIZE :
		LARGE_MEMORY_SIZE;
	if (!block->next && memory_size - zone->reserved_size - sizeof(t_block) >= size)
	{
		zone->reserved_size += size - block->available_size;
		block->available_size += size - block->available_size;
		block->allocated_size = size;
		return (ptr);
	}
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, block->allocated_size);
	free(ptr);
	return (new_ptr);
}
