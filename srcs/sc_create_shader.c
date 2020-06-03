/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_create_shader.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gal <gal@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 15:28:38 by gal               #+#    #+#             */
/*   Updated: 2020/06/03 14:31:24 by gal              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "libft.h"

t_gl_shader	*sc_create_shader(const GLchar* vertex_shader,
								const GLchar* fragment_shader)
{
	t_gl_shader	*gl_shader;
	GLenum ErrorCheckValue = glGetError();
	GLint status;

	if (!(gl_shader = (t_gl_shader*)ft_memalloc(sizeof(t_gl_shader))))
		return (NULL);

	gl_shader->vertex_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(gl_shader->vertex_id, 1, &vertex_shader, NULL);
	glCompileShader(gl_shader->vertex_id);

	gl_shader->frag_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(gl_shader->frag_id, 1, &fragment_shader, NULL);
	glCompileShader(gl_shader->frag_id);

	gl_shader->program_id = glCreateProgram();
	glAttachShader(gl_shader->program_id, gl_shader->vertex_id);
	glAttachShader(gl_shader->program_id, gl_shader->frag_id);
	glBindFragDataLocation(gl_shader->program_id, 0, "outColor");

	glLinkProgram(gl_shader->program_id);
	glUseProgram(gl_shader->program_id);

	glGetShaderiv(gl_shader->vertex_id, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
		printf("Shader did not compile\n");

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
		stderr,
		"ERROR: Could not create the shaders: %s \n",
		gluErrorString(ErrorCheckValue)
		);

		return (NULL);
	}
	return (gl_shader);
}
