#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data_customer.h"
#define LINE_LENGTH 256

unsigned long hash(const char *str, int size) {
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash % size;
}

HashTable *new_table(int size) {
	HashTable *table = malloc(sizeof(HashTable));
	table->size = size;
	table->buckets = calloc(size, sizeof(Customer*));
	return table;
}
void add_f(HashTable *table, const char *email, const char *name, int shoesize, const char *food) {
	unsigned long idx = hash(email, table->size);
       	Customer *c_cust = table->buckets[idx];
	while (c_cust != NULL) {
		if (strcmp(c_cust->email, email) == 0) {
			free(c_cust->name);
			free(c_cust->food);
			c_cust->name = strdup(name);
			c_cust->shoesize = shoesize;
			c_cust->food = strdup(food);
			return;
		}
		c_cust = c_cust->next;
	}
	Customer *n_cust = malloc(sizeof(Customer));
	if (!n_cust) {
		fprintf(stderr, "Failed memory for new customer.\n");
		exit(1);
	}
	n_cust->email = strdup(email);
	n_cust->name = strdup(name);
	n_cust->shoesize = shoesize;
	n_cust->food = strdup(food);
	n_cust->next = table->buckets[idx];
	table->buckets[idx] = n_cust;
}

Customer* lookup_f(HashTable *table, const char *email) {
	unsigned long idx = hash(email, table->size);
	Customer *c_cust = table->buckets[idx];
	while (c_cust != NULL) {
		if (strcmp(c_cust->email, email) == 0) {
			return c_cust;
		}
		c_cust = c_cust->next;
	}
	return NULL;
}

void delete_f(HashTable *table, const char *email) {
	unsigned long idx = hash(email, table->size);
	Customer *c_cust = table->buckets[idx];
	Customer *p_cust = NULL;
	while (c_cust != NULL) {
		if (strcmp(c_cust->email, email) == 0) {
			if (p_cust == NULL) {
				table->buckets[idx] = c_cust->next;
			} else {
				p_cust->next = c_cust->next;
			}
			free(c_cust->email);
			free(c_cust->name);
			free(c_cust->food);
			free(c_cust);
			return;
		}
		p_cust = c_cust;
		c_cust = c_cust->next;
	}
}

void list_f(HashTable *table) {
	for (size_t i = 0; i < (size_t)table->size; i++) {
		Customer *c_cust = table->buckets[i];
		while (c_cust) {
			printf("email: %s, name: %s, shoe size: %d, favorite food: %s\n", c_cust->email, c_cust->name,
				c_cust->shoesize, c_cust->food);
			c_cust = c_cust->next;
		}
	}
}

void save_customer_file(HashTable *table, const char *filename) {
	FILE *file = fopen(filename, "w");
	for (size_t i = 0; i < (size_t)table->size; i++) {
		Customer *c_cust = table->buckets[i];
		while (c_cust) {
			fprintf(file, "%s\t%s\t%d\t%s\n", c_cust->email, c_cust->name, c_cust->shoesize, c_cust->food);
			c_cust = c_cust->next;
		}
	}
	fclose(file);
}

void load_customer_file(HashTable *table, const char *filename) {
	FILE *file = fopen(filename, "r");
	char line[LINE_LENGTH];
	while (fgets(line, sizeof(line), file)) {
		char *n_line = strchr(line, '\n');
		if (n_line) {
			*n_line = '\0';
		}
		char *email = strtok(line, "\t");
		char *name = strtok(NULL, "\t");
		char *shoestr = strtok(NULL, "\t");
		char *food = strtok(NULL, "\t");
		if (!email) {
			fprintf(stderr, "missing email\n");
			continue;
		}
		if (!name) {
			fprintf(stderr, "missing name for: %s\n", email);
			continue;
		}
		if (!shoestr) {
			fprintf(stderr, "missing shoe size for: %s\n", email);
			continue;
		}
		if (!food) {
			fprintf(stderr, "missing favorite food for: %s\n", email);
			continue;
		}
		char *p;
		int shoesize = strtol(shoestr, &p, 10);
		if (*p != '\0') {
			fprintf(stderr, "invalid size: %s\n", shoestr);
			continue;
		}
		if (shoesize <= 0) {
			fprintf(stderr, "invalid size: %s\n", shoestr);
			continue;
		}
		add_f(table, email, name, shoesize, food);	
	}
	fclose(file);
}

void free_f(HashTable *table) {
	for (size_t i = 0; i < (size_t)table->size; i++) {
		Customer *c_cust = table->buckets[i];
		while (c_cust) {
			Customer *free_p = c_cust;
			c_cust = c_cust->next;
			free(free_p->email);
			free(free_p->name);
			free(free_p->food);
			free(free_p);
		}
	}
	free(table->buckets);
	free(table);
}




