//
// Created by Fedya Savchuk on 12/07/2020.
//

#include "lemin.h"

int get_len(t_nodes *node)
{
	int len;
	t_nodes *tmp;

	len = 0;
	tmp = node->start;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return len;
}

//void print_shortest_way(t_nodes *node)
//{
//	while (!node->is_finish)
//		node = node->next;
//	while (node->prev)
//	{
//		ft_putendl(node->name);
//		node = node->prev;
//	}
//	ft_putendl(node->name);
//	node = node->start;
//}

// проходим по всем вершинам и ищем кратчайшие пути до каждой вершины (n - 1, нде n количество узлов)
// если мы в вершине с макс инт -> идем к следующей вершине

void search_min_wights(t_nodes *node)
{
	t_relations *relations;

	while (1)
	{
		// если node = макс инт, то из этой вершины мы уж точно не придем никуда дешево, скипаем это вершину
		relations = node->relations->start;
		if (node->weight > 10000 || !relations)
		{
			if (!node->next)
				break;
			node = node->next;
			continue;
		}
		// TODO поведение при пересечении
		if (node->tmp)
		{
			if (node->in && node->tmp->weight > node->weight - 1)
			{
				node->tmp->weight = node->weight - 1;
				node->tmp->prev = node;
			}
		}

		while (relations)
		{
			if (!relations->active) {
				relations = relations->next;
				continue;
			}
			// если это более дешевый путь до этой вершины - сохраняем новую цену и предыдущий узел
			if (relations->to->weight > node->weight + relations->relation_weight)
			{
				relations->to->weight = node->weight + relations->relation_weight;
				relations->to->prev = node;
			}
			relations = relations->next;
		}
		if (!node->next)
			break;
		node = node->next;
	}
}

void	bellman_ford(t_nodes *nodes) {
	int i;
	int v_count;

	i = 0;
	v_count = get_len(nodes);				// количество вершин в графе
	while (i < v_count - 1)					// проходим по всем вершинам v_count - 1 раз
	{
		nodes = nodes->start;				// переводим указатель на старт
		search_min_wights(nodes);
		i++;
	}
}