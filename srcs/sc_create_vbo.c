/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_create_vbo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gal <gal@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 12:05:11 by gal               #+#    #+#             */
/*   Updated: 2020/06/03 20:13:18 by gal              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdio.h>

GLuint	sc_create_vbo(GLfloat *vertices,
							GLuint len)
{
	GLuint		vbo;
	GLenum 		gl_error;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
					sizeof(*vertices) * len,
					vertices,
					GL_STATIC_DRAW);
	gl_error = glGetError();
	if (gl_error != GL_NO_ERROR)
	{
		printf("tamere\n");
		return (0);
	}
	return (vbo);
 }
 