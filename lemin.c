
#include "lemin.h"

void add_relation(t_nodes *from, t_nodes *to)
{
	t_relations *relations;
	t_relations *start_relations;
	t_relations *new_relations;

	if (!from->relations)
	{
		relations = (t_relations*)malloc(sizeof(t_relations));
		start_relations = relations;
		from->relations = relations;
	} else {
		relations = from->relations;
		start_relations = from->relations->start;
		while (relations->next)
			relations = relations->next;
		new_relations = (t_relations*)malloc(sizeof(t_relations));
		relations->next = new_relations;
		relations = new_relations;
	}
	relations->next = NULL;
	relations->start = start_relations;
	relations->to = to;
	relations->relation_weight = 1;
	relations = start_relations;
}

t_nodes *read_nodes(char **line)
{
	t_nodes *node;
	t_nodes *new_node;
	t_nodes *start;

	node = (t_nodes*)malloc(sizeof(t_nodes));
	node->name = line[0];
	node->weight = 0;
	node->next = NULL;
	node->is_finish = 0;
	node->is_start = 1;
	node->start = node;
	start = node;

	int i = 1;
	while (line[i])
	{
		new_node = (t_nodes*)malloc(sizeof(t_nodes));
		node->next = new_node;
		node = new_node;
		node->name = line[i];
		node->weight = 100000;
		node->next = NULL;
		node->is_finish = 0;
		node->is_start = 0;
		node->start = start;
		i++;
	}
	node->is_finish = 1;
	return start;
}



// work with one symbol only
void read_relations(char **line, t_nodes *nodes)
{
	int i = 0;
	while (line[i])
	{
		char from_name[2];
		char to_name[2];
		from_name[0] = line[i][0];
		from_name[1] = '\0';
		to_name[0] = line[i][2];
		to_name[1] = '\0';


		t_nodes *from;
		from = nodes;
		while(from->name[0] != from_name[0])
			from = from->next;

		t_nodes *to;
		to = nodes;
		while(to->name[0] != to_name[0])
			to = to->next;

		add_relation(from, to);
		add_relation(to, from);
		nodes = nodes->start;
		i++;
	}
}

void print_relations(t_nodes *nodes)
{
	while (nodes)
	{
		ft_putstr("Node name: ");
		ft_putendl(nodes->name);
		ft_putstr("Relations: ");
		while (nodes->relations)
		{
			ft_putstr(nodes->relations->to->name);
			ft_putstr(" ");
			if (!nodes->relations->next) {
				nodes->relations = nodes->relations->start;
				break;
			}
			nodes->relations = nodes->relations->next;
		}
		ft_putendl("");
		ft_putendl("");
		if (!nodes->next)
		{
			nodes = nodes->start;
			break;
		}
		nodes = nodes->next;
	}
}

void shortest_way(t_nodes *nodes)
{

	while (!nodes->is_finish) {
		nodes = nodes->next;
	}
	while (nodes) {
		ft_putstr(nodes->name);
		if (!nodes->prev)
			break;
		nodes = nodes->prev;
	}

	nodes = nodes->start;
}

void print_weights(t_nodes *nodes)
{
	while (nodes) {
		ft_putstr("NODE: ");
		ft_putstr(nodes->name);
		ft_putstr("  WEIGHT: ");
		ft_putnbr(nodes->weight);
		ft_putendl("");
		if (!nodes->next)
			break;
		nodes = nodes->next;
	}
	nodes = nodes->start;
}

int main(int argc, char **argv)
{
	char *line;
	t_nodes *nodes;

	get_next_line(0, &line);
	nodes = read_nodes(ft_strsplit(line, ' '));
	free(line);
	get_next_line(0, &line);

	nodes = nodes->start;
	read_relations(ft_strsplit(line, ' '), nodes);
	nodes = nodes->start;
	//print_relations(nodes);

	bellman_ford(nodes);
	print_weights(nodes);
	shortest_way(nodes);
}