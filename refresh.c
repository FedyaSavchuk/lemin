//
// Created by Fedya Savchuk on 18/07/2020.
//

#include "lemin.h"

// если пути пересикаются - делаем возвращаем граф в исходное состяние с удалением пересикающихся связей и временных ссылок/нодов
void refresh(t_nodes *nodes) {
	while (nodes) {
		nodes->prev = NULL;
		if (!nodes->is_start)
			nodes->weight = 10000;
		else
			nodes->weight = 0;
		nodes = nodes->next;
	}
}
