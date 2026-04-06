/*
Name:Machani Tilak
ID:25021_258
Starting Date:16-09-2025
Ending Date:27-09-2025


Description:
PROJECT TITLE:AddressBook
Contents and Functionalities:
1.Add Contact
2.Search Contact
3.Edit Contact
4.Delete Contact
5.Display Contacts
6.Save and Exit
*/



#include <stdio.h>
#include "main.h"

int main()
{
    int option;
    AddressBook addressbook;
    addressbook.contact_count = 0;

    loadcontacts(&addressbook);
    //Print all the Functionaluities which needs to be performed operations
    while (1)
    {
        printf("\nAddress book menu\n");
        printf("1. Add contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. Display contacts\n");
        printf("6. Save & Exit\n");
        printf("Enter the option: ");
        scanf("%d", &option);


        switch (option)                         //using which case which option needs to be checked
        {
            case 1:
                create_contact(&addressbook);   //going to create contact function call
                break;

            case 2:
                search_contacts(&addressbook);      //Going to Search contact function call
                break;

            case 3:
                edit_contact(&addressbook);         //going to Edit contact function call
                break;

            case 4:
                delete_contact(&addressbook);       //Going to delete function call
                break;

            case 5:
                list_contacts(&addressbook);        //Going to display all the contacts in the terminal function call
                break;

            case 6:
                savecontacts(&addressbook);         //Going to function call for store in text file which acts as a database
                printf("Contacts saved. Exiting...\n");
                return 0;

            default:
                printf("Invalid option.\n");        //If not option then it will print Invalid option
                break;
        }
    }
}
