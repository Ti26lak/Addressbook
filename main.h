#ifndef CONTACT_H
#define CONTACT_H

#include <stdio.h>  // Needed for FILE* in save/load

typedef struct Contact_data
{
    char Name[32];
    char Mobile_number[11];
    char Mail_ID[35];
} Contacts;

typedef struct AddressBook_Data
{
    Contacts contact_details[100];
    int contact_count;
} AddressBook;

/* Function declarations */
void init_initialization(AddressBook *);
int create_contact(AddressBook *);
void list_contacts(AddressBook *);
int search_contacts(AddressBook *);
int edit_contact(AddressBook *);
void delete_contact(AddressBook *);
int validate_name(char *);
int validate_number(char *);
int validate_mailid(char *);
void savecontacts(AddressBook *);
void loadcontacts(AddressBook *);

#endif // CONTACT_H
