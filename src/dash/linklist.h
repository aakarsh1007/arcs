struct list_node {
	void *data;
	struct list_node *next;
};

typedef struct list_node lnk_list;

struct list_node * list_create(void *data);

uint32_t list_len(struct list_node *list);

void list_append(struct list_node *list, void *data);

void * list_get(struct list_node *list, uint32_t i);

void list_set(struct list_node *list, uint32_t i, void *data);

void list_free(struct list_node *list);

void list_itterate(struct list_node *list, void (*func)(void*));
