
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
	relations->active = 1;
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


		t_relations *relations = nodes->relations;
		ft_putstr("Node name: ");
		ft_putendl(nodes->name);
		if (nodes->in)
			ft_putendl("(IN)");
		else if (nodes->out)
			ft_putendl("(OUT)");
		ft_putstr("Relations: ");
		if (nodes->tmp)
			ft_putstr(nodes->tmp->name);
		while (relations)
		{
			if (relations->active == 0)
			{
				relations = relations->next;
				continue;
			}

			ft_putstr(relations->to->name);
			ft_putstr(" ");
			if (!relations->next) {
				relations = relations->start;
				break;
			}
			relations = relations->next;
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

// тут может утечка быть из-за копии ссылки на relations
t_nodes *add_out_node(t_nodes *node) {
	t_nodes *copy;

	copy = (t_nodes*)malloc(sizeof(t_nodes));
	copy->is_finish = 0;
	copy->start = node->start;
	copy->name = node->name;
	copy->next = NULL;
	copy->weight = 100000;
	copy->in = 0;
	copy->out = 1;

	// дизейблим связь на предыдущий элемент (вместо нее будет связь tmp с узла in)
	copy->relations = node->relations->start;
	while(copy->relations->to != node->prev)
		copy->relations = copy->relations->next;
	copy->relations->active = 0;
	copy->relations = node->relations->start;

	copy->need_delete = 1;
	copy->tmp = node;
	t_nodes *finish = node;
	while (finish->next)
		finish = finish->next;
	finish->next = copy;


	return copy;
}

void change_direction(t_nodes *nodes) {
	nodes = nodes->start;
	while (!nodes->is_finish)
		nodes = nodes->next;
	while(nodes->prev) {
		t_nodes *need_delete;
		need_delete = nodes;
		nodes = nodes->prev;
		nodes->relations = nodes->relations->start;
		while (nodes->relations->to != need_delete)
			nodes->relations = nodes->relations->next;
		nodes->relations->active = 0;
		nodes->relations = nodes->relations->start;
	}
	nodes = nodes->start;
}

void add_in_out(t_nodes *nodes) {
	nodes = nodes->start;
	while (!nodes->is_finish)
		nodes = nodes->next;

	t_nodes *prev;
	t_nodes *tmp_node; // out node
	while (!nodes->prev->is_start)
	{
		prev = nodes->prev; // like a D node
		prev->in = 1;		// теперь это in node
		while(nodes->relations->to != prev)
			nodes->relations = nodes->relations->next;
		nodes->relations->active = 0;
		nodes->relations = nodes->relations->start;

		tmp_node = add_out_node(prev);
		nodes->tmp = tmp_node;

		nodes = prev;
	}
	nodes->tmp = nodes->prev;
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
	//print_weights(nodes);
	shortest_way(nodes);
	change_direction(nodes);
	//print_relations(nodes);




	add_in_out(nodes);
	print_relations(nodes);
	while (!nodes->is_finish)
		nodes = nodes->next;
	ft_putstr("\n");
	ft_putendl(nodes->name);
	ft_putstr(nodes->tmp->name);

	if (nodes->tmp->in)
		ft_putstr(" weight: -1");
	if (nodes->tmp->out)
		ft_putstr(" weight: 0");
	if (nodes->tmp->relations->active)
		ft_putstr(" ACTIVE");
	ft_putendl("");

	ft_putstr(nodes->tmp->tmp->name);
	if (nodes->tmp->tmp->in)
		ft_putstr(" weight: -1");
	if (nodes->tmp->tmp->out)
		ft_putstr(" weight: 0");
	if (nodes->tmp->tmp->relations->active)
		ft_putstr(" ACTIVE");
	ft_putendl("");

	ft_putstr(nodes->tmp->tmp->tmp->name);
	if (nodes->tmp->tmp->tmp->in)
		ft_putstr(" weight: -1");
	if (nodes->tmp->tmp->tmp->out)
		ft_putstr(" weight: 0");
	ft_putendl("");

	nodes = nodes->start;
	refresh(nodes);
	bellman_ford(nodes);
	shortest_way(nodes);
}