#pragma once

typedef struct Customer {
	char *email;
	char *name;
	int shoesize;
	char *food;
	struct Customer *next;
} Customer;

typedef struct {
	Customer **buckets;
	int size;
} HashTable; 

HashTable *new_table(int size);
void free_f(HashTable *table);
Customer *lookup_f(HashTable *table, const char *email);
void add_f(HashTable *table, const char *email, const char *name, int shoesize, const char *food);
void delete_f(HashTable *table, const char *email);
void list_f(HashTable *table);
void load_customer_file(HashTable *table, const char *filename);
void save_customer_file(HashTable *table, const char *filename);
