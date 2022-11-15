/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:45:18 by lsuardi           #+#    #+#             */
/*   Updated: 2022/11/15 23:57:00 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>

void * malloc( size_t size );
void free( void * ptr );
void * realloc( void * ptr, size_t size );
void show_alloc_mem( void );

#endif
