#include <stdio.h>
#include <stdlib.h>

typedef struct list_element {
	char string[15][50];

	struct list_element* next;
	struct list_element* prev;
};

struct list_element* create_first(struct list_element* prev, char n[15][50], int k) {

	struct list_element* new_node;
	new_node = malloc(sizeof(struct list_element));
	if (!new_node)
		return NULL;

	for (int i = 0; i < k; i++) {
		printf("%s: ", n[i]);
		gets_s(new_node->string[i], 50);
	}

	new_node->prev = prev;
	new_node->next = NULL;
	return new_node;
}

void create_element(struct list_element* start, int i, char n[15][50], int k) {
	struct list_element* nextsafe;

	struct list_element* new_node;
	new_node = start;
	while (i - 1) {
		if (new_node->next)
			new_node = new_node->next;
		else {
			printf("Element doesn't exist!");
			system("pause");
			return;
		}
		i--;
	}

	nextsafe = new_node->next;
	new_node->next = malloc(sizeof(struct list_element));
	if (!new_node->next)
		return;

	new_node->next->prev = new_node;
	new_node->next->next = nextsafe;
	if (nextsafe)
		if (nextsafe->next)
			nextsafe->prev = new_node->next;

	for (int i = 0; i < k; i++) {
		printf("%s: ", &n[i]);
		gets_s(new_node->next->string[i], 50);
	}

}

void print_element(struct list_element* start, int i, char n[15][50], int k) {
	struct list_element* new_node;
	new_node = start;

	while (i) {
		if (new_node->next)
			new_node = new_node->next;
		else {
			printf("Element doesnt exist!");
			system("pause");
			return;
		}
		i--;
	}
	if (new_node)
		for (int i = 0; i < k; i++)
			printf(" %s: %s \n", n[i], new_node->string[i]);
	else
		printf("List is empty!");
	system("pause");
}

void delete_element(struct list_element* start, int i) {
	struct list_element* nextsafe;

	struct list_element* new_node;
	new_node = start;
	while (i) {
		if (new_node->next)
			new_node = new_node->next;
		else {
			printf("Element doesn't exist!");
			system("pause");
			return;
		}
		i--;
	}

	new_node->prev->next = new_node->next;
	if (new_node->next)
		new_node->next->prev = new_node->prev;

	free(new_node);
	system("pause");
}

void print_all(struct list_element* start, char n[15][50], int k) {
	struct list_element* new_node;
	new_node = start;


	if (new_node)
		while (new_node->next) {
			new_node = new_node->next;
			for (int i = 0; i < k; i++)
				printf(" %s: %s \n", n[i], new_node->string[i]);
		}
	else
		printf("list is empty!");
	system("pause");
}

int main(void) {
	int nr = 0, check = 1, kom = 0;
	char menue = 0;
	char names[15][50];
	char t;

	struct list_element* start;
	start = malloc(sizeof(struct list_element));
	if (!start)
		return NULL;
	printf("How many different components do you want to have? \n");
	scanf_s(" %d", &kom);
	while (getchar() == "\n");

	for (int i = 0; i < kom; i++) {
		printf("Name of the %d. component:", i + 1);
		gets_s(names[i], 50);
	}
	start->next = create_first(start, names, kom);

	do {
		system("cls");
		printf("Press '1' to add a new Element \nPress '2' to print an Element \nPress '3' to delete an Element \nPress '4' to print all Elements \nAny other key ends the program \n");
		menue = getchar();
		switch (menue) {
		case '1':
			printf("which place for the new element?");
			scanf_s(" %d", &nr);
			while (getchar() == "\n");
			create_element(start, nr, names, kom);
			break;
		case '2':
			printf("which one should I print?");
			scanf_s(" %d", &nr);
			while (getchar() == "\n");
			print_element(start, nr, names, kom);
			break;
		case '3':
			printf("which one should i delete?");
			scanf_s(" %d", &nr);
			while (getchar() == "\n");
			delete_element(start, nr);
			break;
		case '4':
			print_all(start, names, kom);
			break;
		default:
			printf("do you really want to exit? (j/n) \n");
			scanf_s(" %c", &t);
			while (getchar() == "\n");
			if (t == 'j')
				check = 0;
			break;
		}
	} while (check);

	system("pause");
}
