/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_locks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:36:23 by lsuardi           #+#    #+#             */
/*   Updated: 2022/11/12 22:04:53 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"
#include <stdlib.h>

/* Bonus */
__attribute__((constructor))
void init_locks( void )
{
	if (pthread_mutex_init(&g_zones.TINY_LOCK, NULL)
	|| pthread_mutex_init(&g_zones.SMALL_LOCK, NULL)
	|| pthread_mutex_init(&g_zones.LARGE_LOCK, NULL))
	{
		write(2, "Error: failed to initialize locks for malloc\n", 45);
		exit(1);
	}
}
