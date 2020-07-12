#ifndef FT_LEMIN_H
# define FT_LEMIN_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

typedef struct			s_nodes
{
	char 				*name;
	int					weight;
	struct s_nodes		*next;
	struct s_relations	*relations;
	struct s_nodes		*prev;
	struct s_nodes		*start;
	int					is_start;
	int					is_finish;
}						t_nodes;

typedef struct			s_relations
{
	struct s_nodes 		*to;
	int					relation_weight;
	struct s_relations	*next;
	struct s_relations	*start;
}						t_relations;

int					get_next_line(const int fd, char **line);
void				bellman_ford(t_nodes *nodes);

#endif
