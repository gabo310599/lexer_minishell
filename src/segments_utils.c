/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:32:29 by gojeda            #+#    #+#             */
/*   Updated: 2025/12/17 17:44:46 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

//Inicializamos un segmento
void	lexer_start_segment(t_lexer *lx, bool expand)
{
	lx->current_expand = expand;
	lx->current_seg = segment_new(ft_strdup(""), expand);
}

//Cerramos el segmento
void	lexer_end_segment(t_lexer *lx)
{
	if (!lx->current_seg)
		return ;
	token_add_segment(lx->current_word, lx->current_seg);
	lx->current_seg = NULL;
}
