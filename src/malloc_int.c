/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:38:43 by lsuardi           #+#    #+#             */
/*   Updated: 2022/11/12 22:04:41 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_int.h"

struct malloc_zones g_zones = { NULL, { }, NULL, { }, NULL, { } };
