#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "data_customer.h"
#define BUFF 256


void prompt_u(HashTable *table);

int main() {
	HashTable *table = new_table(100);
	load_customer_file(table, "customers.tsv");
	prompt_u(table);
	return 0;
}

void clear_buff() {
	while (getchar() != '\n');
}

void r_line(char *str) {
	char *n_line = strchr(str, '\n');
	if (n_line) {
		*n_line = '\0';
	}
}
void prompt_u(HashTable *table) {
	char command[BUFF];
	while (1) {
		printf("Please enter a command (add, lookup delete list, save, quit): ");
		if (fgets(command, sizeof(command), stdin) == NULL) {
			fprintf(stderr, "Command input error\n");
			continue;
		}
		r_line(command);
		if (strcmp(command, "add") == 0) {
			char email[BUFF], name[BUFF], food[BUFF];
			int shoesize;
			printf("Please enter email: ");
			if (fgets(email, sizeof(email), stdin) == NULL) {
				fprintf(stderr, "Email read error\n");
				continue;
			}
			r_line(email);
			printf("Please enter name: ");
			if (fgets(name, sizeof(name), stdin) == NULL) {
				fprintf(stderr, "Name read error\n");
				continue;
			}
			r_line(name);

			printf("Please enter shoe size: ");
			if (scanf("%d", &shoesize) != 1) {
				fprintf(stderr, "Shoe size read error\n");
				clear_buff();
				continue;
			}
			clear_buff();
			
			printf("Please enter favorite food: ");
			if (fgets(food, sizeof(food), stdin) == NULL) {
				fprintf(stderr, "Favorite food read error\n");
				continue;
			}
			r_line(food);
			add_f(table, email, name, shoesize, food);
		} else if (strcmp(command, "lookup") == 0) {
			char email[BUFF];
			printf("Please enter email: ");
			if (fgets(email, sizeof(email), stdin) == NULL) {
				fprintf(stderr, "Email read error\n");
				continue;
			}
			r_line(email);

			Customer *customer = lookup_f(table, email);
			if (customer) {
				printf("Email: %s\nName: %s\nShoe Size: %d\nFavorite Food: %s\n\n",
					customer->email, customer->name, customer->shoesize, customer->food);
			} else {
				printf("Unknown Customer\n");
			}
		} else if (strcmp(command, "delete") == 0) {
			char email[BUFF];
			printf("Please enter email: ");
			if (fgets(email, sizeof(email), stdin) == NULL) {
				fprintf(stderr, "Email read error\n");
				continue;
			}
			r_line(email);
			delete_f(table, email);
		} else if (strcmp(command, "list") == 0) {
			list_f(table);
		} else if (strcmp(command, "save") == 0) {
			save_customer_file(table, "customers.tsv");
		} else if (strcmp(command, "quit") == 0) {
			free_f(table);
			break;
		} else {
			printf("Unknown command please try again\n");
		}
	}
}




























