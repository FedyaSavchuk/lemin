#ifndef FT_LEMIN_H
# define FT_LEMIN_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

typedef struct			s_nodes
{
	char 				*name;						// имя вершины
	int					weight;						// вес вершины
	struct s_nodes		*next;						// следующая вершина
	struct s_relations	*relations;					// на какие вершины ссылается эта вершина
	struct s_nodes		*prev;						// как мы попали в эту вершину (кратчайший путь)
	struct s_nodes		*start;						// сслыка на первый элемент списка
	int					is_start;					// boolean является ли вершина стартом
	int					is_finish;					// boolean является ли вершина финишем

	// относится к доп узлам
	int					in;							// boolean 'in' = 1, 'out' = 0
	struct s_relations	*tmp;						// ссылка на временные узлы
}						t_nodes;

typedef struct			s_relations
{
	struct s_nodes 		*to;						// ссылка на вершину
	int					relation_weight;			// стоимость перехода к вершине
	struct s_relations	*next;						// следующая связь
	struct s_relations	*start;						// сслыка на первый элемент списка
}						t_relations;

int					get_next_line(const int fd, char **line);
void				bellman_ford(t_nodes *nodes);

#endif
