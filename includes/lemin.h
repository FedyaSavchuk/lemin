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

	// относится к доп узлам. В зависимости на какой узел указывает tmp (in или out), мы понимаем какой вес имеет связь (0 или -1)
	int					in;							// boolean 'in' = 1 - это узел in
	int 				out;						// boolean 'out' = 1 - это узел out
	struct s_nodes		*tmp;						// ссылка на временные узлы
	int 				need_delete;				// для удаления временных узлов

}						t_nodes;

typedef struct			s_relations
{
	struct s_nodes 		*to;						// ссылка на вершину
	int 				active;						// активна ли ссылка (можно ли по ней перейти или связь не активна)
	int					relation_weight;			// стоимость перехода к вершине
	struct s_relations	*next;						// следующая связь
	struct s_relations	*start;						// сслыка на первый элемент списка
	int 				need_delete;				// для удаления временных узлов
}						t_relations;

int					get_next_line(const int fd, char **line);
void				bellman_ford(t_nodes *nodes);
void				refresh(t_nodes *nodes);

#endif
