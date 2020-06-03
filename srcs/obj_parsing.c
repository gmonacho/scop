/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gal <gal@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 22:24:39 by gal               #+#    #+#             */
/*   Updated: 2020/06/03 11:55:20 by gal              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include <fcntl.h>
#include "libft.h"
#include "ui.h"

static char	*obj_read_file(int fd)
{
	char	*text;
	char	*line;
	char	*tmp;

	text = NULL;
	while ((get_next_line(fd, &line)) > 0)
	{
		tmp = text;
		text = ft_strjoin(text, line);
		ft_strdel(&tmp);
		ft_strdel(&line);
	}
	return (text);
}

static GLuint		obj_get_v_depht(char *text)
{
	int		v_depth;
	int		i;
	char	*tmp;

	v_depth = 0;
	tmp = ft_strstr(text, "v ");
	if (tmp)
	{
		i = 0;
		i++;
		while (tmp[i] && tmp[i] != 'v')
		{
			if (tmp[i] == '.')
				v_depth++;
			i++;
		}
	}
	return (v_depth);
}

static int			obj_extract_vertice(char *text,
										int depth,
										t_list **list)
{
	GLfloat	*vertices;
	int		v_count;
	int 	i;

	v_count = 0;
	i = 0;
	if (!(vertices = (GLfloat*)ft_memalloc(sizeof(GLfloat) * depth)))
		return (0);
	while (text[i] && v_count < depth)
	{
		while (text[i] && !ft_isdigit(text[i]) && text[i] != '-')
			i++;
		vertices[v_count++] = ft_atof(&text[i]);
		while (text[i] && ft_isdigit(text[i]))
			i++;
		i++;
		while (text[i] && ft_isdigit(text[i]))
			i++;
	}
	ft_lstadd(list, ft_lstnew_move(vertices, sizeof(vertices)));
	return (1);
}

static GLfloat		*obj_convert_list(t_list **list, int depth, int len)
{
	GLfloat	*vertices;
	t_list	*l;
	int		i;
	int		i_depth;

	if (!(vertices = (GLfloat*)ft_memalloc(sizeof(GLfloat) * len)))
		return (NULL);
	l = *list;
	i = 0;
	while (l)
	{
		i_depth = 0;
		while (i_depth < depth)
			vertices[i++] = ((GLfloat*)l->content)[i_depth++];
		l = l->next;
	}
	return (vertices);
}

static int		obj_extract_vertices(char *text, t_obj *obj)
{
	t_list	*list;
	char	*start;
	char	*tmp;

	start = text;

	obj->v_depth = obj_get_v_depht(text);
	while (*text)
	{
		if ((tmp = ft_strstr(text, "v ")))
		{
			obj_extract_vertice(tmp, obj->v_depth, &list);
			text = tmp + 2;
		}
		text++;
	}
	text = start;
	obj->len = ft_lstlen(&list) * obj->v_depth;
	if (!(obj->vertices = obj_convert_list(&list, obj->v_depth, obj->len)))
		return (0);
	return (1);
}

t_obj				*obj_parser(const char *path)
{
	t_obj	*obj;
	int		fd;
	char	*text;

	text = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	if (!(obj = (t_obj*)ft_memalloc(sizeof(t_obj))))
		return (NULL);
	if ((text = obj_read_file(fd)))
		obj_extract_vertices(text, obj);
	if (text)
		ft_strdel(&text);
	return (obj);
}
