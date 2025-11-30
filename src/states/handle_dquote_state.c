/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dquote_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:44:00 by gojeda            #+#    #+#             */
/*   Updated: 2025/11/30 19:34:35 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h";

static void	escapes_dquote(const char *line, char next, t_lexer *lx, size_t *i)
{
	if (!next) {
		lexer_add_char(lx, '\\');
		(*i)++;
		return ;
	}
	if (next == '"' || next == '\\' || next == '$')
	{
		lexer_add_char(lx, next);
		*i += 2;
		return ;
	}
	lexer_add_char(lx, '\\');
	(*i)++;
	return ;
}

void	handle_in_dquote(t_lexer *lx, const char *line,
			size_t *i, int *state)
{
	char	c;

	if (!line[*i])
	{
		lx->error = 1;
		return ;
	}
	c = line[*i];
	if (c == '"')
	{
		*state = NORMAL;
		(*i)++;
		return ;
	}
	if (line[*i] == '\\')
	{
		escapes_dquote(line, line[*i + 1], lx, i);
		return ;
	}
	lexer_add_char(lx, c);
	(*i)++;
}
