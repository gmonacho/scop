/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_create_vao.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gal <gal@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 19:45:38 by gal               #+#    #+#             */
/*   Updated: 2020/06/03 20:08:54 by gal              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"


GLuint	sc_create_vao()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	return (vao);
}