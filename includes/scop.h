/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gal <gal@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:53:04 by gal               #+#    #+#             */
/*   Updated: 2020/06/03 20:09:13 by gal              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H_
# define SCOP_H_
# include <GL/glew.h>

typedef struct	s_gl_shader
{
	GLuint		vertex_id;
	GLuint		frag_id;
	GLuint		program_id;
}				t_gl_shader;

GLuint	sc_create_vbo(GLfloat *vertices,
							GLuint len);

GLuint	sc_create_vao();

t_gl_shader	*sc_create_shader(const GLchar* vertex_shader,
								const GLchar* fragment_shader);

#endif
 