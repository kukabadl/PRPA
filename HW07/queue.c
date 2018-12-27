#include "queue.h"

queue_t * push_to_queue (queue_t *queue, void *data)
{
	queue_t * tmp = (queue_t *)malloc(sizeof(queue_t));
	tmp->data = data;
	tmp->predchozi = a;
	return tmp;
}

queue_t * create_queue(int capacity){
  for (int i = 0; i < capacity; i++){
    = (queue_t *)malloc(sizeof(queue_t));
  }
}

queue_t * pop_from_queue (queue_t *queue)
{
	*data = a->data;
	queue_t * tmp = a->predchozi;
	free (a);
	return tmp;
}


int main()
{
	int a;
	queue_t * zasobnik = NULL;

	zasobnik = push (zasobnik, 10);
	zasobnik = push (zasobnik, 33);
	zasobnik = pop (zasobnik, &a);
	printf("pop: %d\n", a);
	zasobnik = pop (zasobnik, &a);
	printf("pop: %d\n", a);

	return 0;
}
