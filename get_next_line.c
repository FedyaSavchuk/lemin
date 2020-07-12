/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspeeder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 13:57:16 by hspeeder          #+#    #+#             */
/*   Updated: 2019/09/13 13:57:17 by hspeeder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>
#define BUFF_SIZE 5

static char			*ft_fix_join(char **content, char *buf)
{
	char			*tmp;

	tmp = ft_strjoin(*content, buf);
	free(*content);
	return (tmp);
}

static int			write_line(t_list *fd_list, char **line)
{
	char			*ptr;
	int				len;
	int				i;
	char			*temp;

	ptr = fd_list->content;
	len = 0;
	while (((char *)(fd_list->content))[len] != '\n' &&
	((char *)(fd_list->content))[len] != '\0')
		len++;
	line[0] = (char *)malloc(sizeof(char) * (len + 1));
	if (!line[0])
		return (-1);
	i = -1;
	while (len > ++i)
		line[0][i] = ((char *)(fd_list->content))[i];
	ptr = ptr + i;
	if ((((char *)(fd_list->content))[i]) == '\n')
		ptr++;
	temp = ft_strdup(ptr);
	free(fd_list->content);
	fd_list->content = temp;
	line[0][i] = '\0';
	return (1);
}

static int			read_file(t_list **fd_list, char **line)
{
	char			buff[BUFF_SIZE + 1];
	int				fd_return;

	if ((*fd_list)->content != NULL)
		if (ft_strchr((*fd_list)->content, '\n'))
			return (write_line(*fd_list, line));
	fd_return = read((*fd_list)->content_size, buff, BUFF_SIZE);
	buff[fd_return] = '\0';
	while (fd_return > 0)
	{
		if ((*fd_list)->content != NULL)
			(*fd_list)->content =
					ft_fix_join((char**)(&((*fd_list)->content)), buff);
		else
			(*fd_list)->content = ft_strdup(buff);
		return (read_file(fd_list, line));
	}
	if (fd_return == -1)
		return (-1);
	if (ft_strlen((*fd_list)->content) > 0)
		return (write_line((*fd_list), line));
	return (0);
}

static int			search_fd(t_list *fd_list, char **line,
		t_list *start, const int fd)
{
	int				save;

	while (fd_list != NULL)
	{
		if ((int)(fd_list->content_size) == fd)
		{
			save = read_file(&fd_list, line);
			fd_list = start;
			return (save);
		}
		fd_list = fd_list->next;
	}
	return (2);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*fd_list;
	t_list			*start;
	t_list			*new_elem;
	int				save;

	if (fd < 0 || line == NULL)
		return (-1);
	start = fd_list;
	if (fd_list != NULL)
	{
		save = search_fd(fd_list, line, start, fd);
		if (save != 2)
			return (save);
	}
	fd_list = start;
	if (fd_list == NULL)
		fd_list = ft_lstnew(NULL, 1);
	else
	{
		new_elem = ft_lstnew(NULL, 1);
		new_elem->next = fd_list;
		fd_list = new_elem;
	}
	fd_list->content_size = (size_t)fd;
	return (read_file(&fd_list, line));
}
