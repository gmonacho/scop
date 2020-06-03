/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gal <gal@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 12:45:06 by gal               #+#    #+#             */
/*   Updated: 2020/06/03 22:11:54 by gal              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdio.h>
#include <SDL2/SDL_opengl.h>
#include "obj.h"
#include "ui.h"
#include "libft.h"

const GLchar* vertex_shader =
{
	"#version 150 core\n"\

	"in vec2 position;\n"\

	"void main()\n"\
	"{\n"\
	"  gl_Position = vec4(position, 0.0, 1.0);\n"\
"}\n"
};

const GLchar* fragment_shader =
{
	"#version 150 core\n"\

	"uniform vec3 triangleColor;"

	"out vec4 out_Color;\n"\

	"void main()\n"\
	"{\n"\
	"  out_Color = vec4(triangleColor, 1.0);\n"\
	"}\n"
};

int	main(void)
{
	t_winui		*win;
	SDL_bool	loop;
	GLuint		vao;
	GLuint		vbo;
	// t_obj		*obj;
	t_gl_shader	*gl_shader;

	GLfloat vertices[] = {
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

	// GLfloat 	colors[] =
	// {
	// 	1.0f, 0.0f, 0.0f, 1.0f,
	// 	0.0f, 1.0f, 0.0f, 1.0f,
	// 	0.0f, 0.0f, 1.0f, 1.0f
	// };

	ui_init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	win = ui_new_win("scop", (t_rect){SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800}, SDL_WINDOW_OPENGL, 5);
	SDL_GLContext context = SDL_GL_CreateContext(win->ptr);

	glewExperimental = GL_TRUE;
	glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// obj = obj_parser("./obj_files/cube.obj");

	// for (GLuint i = 0; i < obj->len; i++)
	// 	printf("vertice = %f\n", obj->vertices[i]);

	gl_shader = sc_create_shader(vertex_shader, fragment_shader);
	vbo = sc_create_vbo(vertices, 6);
	GLint uniColor = glGetUniformLocation(gl_shader->program_id, "triangleColor");
	glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
	vao = sc_create_vao();

	printf("%d %d\n", vao, vbo);
	GLint posAttrib = glGetAttribLocation(gl_shader->program_id, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	GLuint gl_error = glGetError();
	if (gl_error != GL_NO_ERROR)
		printf("error : %s\n", gluErrorString(gl_error));
	glEnableVertexAttribArray(posAttrib);

	loop = SDL_TRUE;
	while (loop)
	{
		while (SDL_PollEvent(&win->event))
		{
			if (win->event.type == SDL_QUIT)
				loop = SDL_FALSE;
			if (win->event.type == SDL_KEYUP &&
				win->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				loop = SDL_FALSE;
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// printf("error: %d\n", glGetError());
		SDL_GL_SwapWindow(win->ptr);
	}
	SDL_GL_DeleteContext(context);
	ui_free_win(&win);
	ui_quit(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	return (0);
}
