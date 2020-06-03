#ifndef OBJ_H
# define OBJ_H
# include <GL/glew.h>

typedef struct	s_obj
{
	GLfloat		*vertices;
	GLuint		v_depth;
	GLuint		len;
}				t_obj;

t_obj				*obj_parser(const char *path);

#endif