# Hash_table_db
A simple customer database system using a hash table with linked-list chaining

## What the Program Does

Loads customers from customers.tsv

Stores each customer in a hash table bucket based on email hash

Supports commands:

add — insert or replace customer

lookup — find customer by email

delete — remove customer

list — print all customers

save — write current table to customers.tsv

quit — free memory & exit

Important Files

data_customer.h — struct definitions & function prototypes

data_customer.c — hash table logic (add, delete, lookup, load, save)

customer_main.c — command loop + program entry point

customers.tsv — tab-separated customer database

## Key Functions
Hash Table Operations

new_table(size) — create hash table

add_f(table, email, name, shoesize, food) — insert or replace customer

lookup_f(table, email) — find customer by email

delete_f(table, email) — remove a customer

list_f(table) — print all customers

save_customer_file(table, filename) — write table to file

load_customer_file(table, filename) — load customers from file

free_f(table) — free all memory

Support Functions

DJB2 hash() function for bucket selection

prompt_u() — interactive user command loop

r_line() — remove newline from input

## How to Build
Using gcc:
gcc customer_main.c data_customer.c -o businessdb

Or with Makefile:
make

## How to Run
./businessdb


The program will load customers.tsv automatically.

File Format (customers.tsv)
email<TAB>name<TAB>shoe_size<TAB>favorite_food


Example:

sammy@ucsc.edu	Sammy The Slug	27	bananas
bimmy@ucsc.edu	bimmy	4	vegan jerky


## ASCII Design
 ┌──────────────────────────────────────────────────────────┐
 │                        HashTable                          │
 │----------------------------------------------------------│
 │ size = 100                                                │
 │ buckets = Customer*[] -----------------------------------│
 └───────────────┬───────────────┬───────────────┬─────────┘
                 │               │               │
                 ▼               ▼               ▼
        ┌─────────────┐   ┌─────────────┐   ┌─────────────┐
Bucket0 │   Customer   │   │   Customer   │   │   Customer   │
        │ email        │   │ email        │   │ email        │
        │ name         │   │ name         │   │ name         │
        │ shoesize     │   │ shoesize     │   │ shoesize     │
        │ food         │   │ food         │   │ food         │
        │ next  ───────┼──▶│ next  ───────┼──▶│ next = NULL  │
        └─────────────┘   └─────────────┘   └─────────────┘

(Each bucket holds a linked list of Customer nodes)
