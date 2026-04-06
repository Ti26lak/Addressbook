#include <stdio.h>
#include "main.h"

void savecontacts(AddressBook *addressbook) {
    FILE *fptr = fopen("contact.txt", "w");  // save all contacts
    if(!fptr) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fptr, "#%d\n", addressbook->contact_count);  // write count
    for(int i = 0; i < addressbook->contact_count; i++) {
        fprintf(fptr, "%s,%s,%s\n",
            addressbook->contact_details[i].Name,
            addressbook->contact_details[i].Mobile_number,
            addressbook->contact_details[i].Mail_ID);
    }
    fclose(fptr);
}

void loadcontacts(AddressBook *addressbook) {
    FILE *fptr = fopen("contact.txt", "r");
    if(!fptr) {
        addressbook->contact_count = 0;
        return;
    }

    fscanf(fptr, "#%d\n", &addressbook->contact_count);
    for(int i = 0; i < addressbook->contact_count; i++) {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
            addressbook->contact_details[i].Name,
            addressbook->contact_details[i].Mobile_number,
            addressbook->contact_details[i].Mail_ID);
    }
    fclose(fptr);
}
