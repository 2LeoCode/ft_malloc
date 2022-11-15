/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:04:27 by lsuardi           #+#    #+#             */
/*   Updated: 2022/11/15 23:34:29 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MALLOC_INT_H
# define MALLOC_INT_H

# include <sys/mman.h>
# include <stdint.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>

# include "../malloc.h"

/* Debug */
# include <stdio.h>
# include <string.h>

/* Bonus */
# include <pthread.h>

# define PAGE_SIZE getpagesize()

// TINY_ZONE_SIZE = 4096 * 4 = 16384
# define TINY_ZONE_SIZE (PAGE_SIZE * 4)
// SMALL_ZONE_SIZE = 16384 * 8 = 131072
# define SMALL_ZONE_SIZE (TINY_ZONE_SIZE * 8)
// LARGE_ZONE_SIZE = 131072 * 16 = 2097152
# define LARGE_ZONE_SIZE (SMALL_ZONE_SIZE * 16)

// TINY_MEMORY_SIZE = 16384 - 40 = 16344
# define TINY_MEMORY_SIZE (TINY_ZONE_SIZE - sizeof(t_zone))
// SMALL_MEMORY_SIZE = 16344 * 8 = 131536
# define SMALL_MEMORY_SIZE (TINY_MEMORY_SIZE * 8)
// LARGE_MEMORY_SIZE = 131536 * 16 = 2096896
# define LARGE_MEMORY_SIZE (SMALL_MEMORY_SIZE * 16)

// TINY_AVAILABLE_SIZE = 16344 - 32 = 16312
# define TINY_AVAILABLE_SIZE (TINY_MEMORY_SIZE - sizeof(t_block))
// SMALL_AVAILABLE_SIZE = 16312 * 8 = 131296
# define SMALL_AVAILABLE_SIZE (TINY_AVAILABLE_SIZE * 8)
// LARGE_AVAILABLE_SIZE = 131296 * 16 = 2096896
# define LARGE_AVAILABLE_SIZE (SMALL_AVAILABLE_SIZE * 16)

# if __WORDSIZE == 64

// Align address to 16 bytes boundary

#  define ALIGN_PREV( X ) ((uintptr_t)(X) & ~(16 - 1))
#  define ALIGN_NEXT( X ) ALIGN_PREV((uintptr_t)(X) + 15)
# else
#  define ALIGN_PREV( X ) ((uintptr_t)(X) & ~(8 - 1))
#  define ALIGN_NEXT( X ) ALIGN_PREV((uintptr_t)(X) + 7)
# endif

# define SWAP( A, B ) \
	do \
	{ \
		__auto_type tmp = A; \
		A = B; \
		B = tmp; \
	} \
	while (0)

# define BLOCKS_PER_ZONE 128

typedef struct s_block	t_block;
typedef struct s_zone	t_zone;

struct s_block
{
	t_block *		prev;
	t_block *		next;
	t_zone *		zone;
	bool			freed;
	ptrdiff_t 		index;
	size_t			available_size;
	size_t			allocated_size;
	uint8_t			data[]
	__attribute__((aligned(16)));
};

struct s_zone
{
	t_zone **		addr;
	size_t			reserved_size;
	size_t			allocated_block_cnt;
	size_t			freed_block_cnt;
	t_block	*		blocks[BLOCKS_PER_ZONE];
	t_zone *		next;
	t_zone *		prev;
	uint8_t			memory[]
	__attribute__((aligned(16)));
};

extern struct malloc_zones {
	t_zone *		TINY;
	pthread_mutex_t	TINY_LOCK;
	t_zone *		SMALL;
	pthread_mutex_t	SMALL_LOCK;
	t_zone *		LARGE;
	pthread_mutex_t	LARGE_LOCK;
} g_zones;

#endif
