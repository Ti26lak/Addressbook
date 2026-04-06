#include <stdio.h>
#include<string.h>
#include "main.h"
#include<ctype.h>

//Create contact definition
int create_contact(AddressBook *addressbook)
{
    int arr = addressbook->contact_count;
    Contacts var;

    // Name input loop
    while (1) {
        printf("Enter the Name of a person: ");
        scanf(" %32[^\n]", var.Name);

        if (validate_name(var.Name)) {
            break;  // valid -> exit loop
        } else {
            printf("Enter the name clearly. It should contain only alphanumeric characters.\n");
        }
    }

// Mobile number input loop
while (1) {
    int check = 1;
    printf("\nEnter the mobile number: ");
    scanf(" %10[^\n]", var.Mobile_number);

    // Flush extra characters if user typed more than 10
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);  

    // Check length == 10
    if (strlen(var.Mobile_number) != 10) {
        printf("Mobile number must be exactly 10 digits!\n");
        continue;
    }

    // Check only digits
    int valid = 1;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(var.Mobile_number[i])) {
            valid = 0;
            break;
        }
    }
    if (!valid) {
        printf("Mobile number must contain only digits!\n");
        continue;
    }

    // Duplicate check
    for (int i = 0; i < arr; i++) {
        if (strcmp(addressbook->contact_details[i].Mobile_number, var.Mobile_number) == 0) {
            printf("The number you entered already exists.\n");
            check = 0;
            break;
        }
    }

    if (check) {
        break;  // valid number accepted
    }
}

    // Mail ID input loop
    while (1) {
        int check=1;
        printf("\nEnter Mail Id: ");
        scanf(" %34[^\n]", var.Mail_ID);

        if (!(validate_mailid(var.Mail_ID))) {
            continue;
        }
        for(int i=0;i<arr;i++){
            if(strcmp(addressbook->contact_details[i].Mail_ID,var.Mail_ID)==0){
                printf("Mail already exixts or Invalid Mail Address\n");
                printf("Please Enter the Valid Mail Id");
                check=0;
                break;
            }
        }
        if(check){
        break;
        }
    }

    // Save to address book
    addressbook->contact_details[arr] = var;            //It needs to be done as a array to store th contact count 
    addressbook->contact_count++;

    printf("\nContact created Successfully !!!");
    return 1;
}


//Needs to be search contact
int search_contacts(AddressBook *addressbook) {
    int ret;
    int value;

    //Searching then menu
    while (1) {
        printf("\nSearch Menu:");
        printf("\n1. Name");
        printf("\n2. Mobile Number");
        printf("\n3. Email ID");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &value);                //In order to search by their name

        // Exit condition
        if (value == 4) {
            printf("\nExiting search...\n");
            break;
        }

        char str[100];
        printf("Enter the value to search: ");
        scanf(" %[^\n]", str);

        ret = 0;
        printf("-----------------------------------------------------------------------------\n");
        printf("%-20s %-20s %-30s\n", "Name", "Mobile Number", "Mail ID");
        printf("-----------------------------------------------------------------------------\n");

        for (int i = 0; i < addressbook->contact_count; i++) {
            int flag = 0;

            switch (value) {                        //From here it should we can select the value
                case 1: // Search by Name
                    if (strstr(addressbook->contact_details[i].Name, str) != NULL)
                        flag = 1;
                    break;
                case 2: // Search by Mobile Number
                    if (strstr(addressbook->contact_details[i].Mobile_number, str) != NULL)
                        flag = 1;
                    break;
                case 3: // Search by Email ID
                    if (strstr(addressbook->contact_details[i].Mail_ID, str) != NULL)
                        flag = 1;
                    break;
                default:        //not selected then it will exit the switch case
                    printf("Invalid option! Please try again.\n");
            }

            if (flag) {         //if it search option is true then it is enter the if condidtion block
                printf("%-20s %-20s %-30s\n",
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Mobile_number,
                       addressbook->contact_details[i].Mail_ID);
                ret = 1;
            }
        }
        //flag checks for the contact not found
        if (!ret) {
            printf("No contact found with this value.\n");
        }

        printf("-----------------------------------------------------------------------------\n");
    }

    return 1;
}



//Edit contact function definition
int edit_contact(AddressBook *addressbook) {
    char str[100];
    int matches[100], size = 0;

    // Step 1: Ask which contact to edit
    printf("\nEnter the name/mobile/mail of the contact to edit: ");
    scanf(" %99[^\n]", str);

    // Step 2: Search (collect all matches)
    for (int i = 0; i < addressbook->contact_count; i++) {
        if ((strstr(addressbook->contact_details[i].Name, str) != NULL) ||
            (strstr(addressbook->contact_details[i].Mobile_number, str) != NULL) ||
            (strstr(addressbook->contact_details[i].Mail_ID, str) != NULL)) {
            matches[size++] = i;
        }
    }
    //here it should check whether the contact is found or not
    if (size == 0) {
        printf("\nContact not found\n");
        return 1;
    }

    // Step 3: If multiple matches, show all and ask user to choose
    int idx;
    if (size > 1) {
        printf("\nFound multiple contacts:\n");
        for (int k = 0; k < size; k++) {
            int ind = matches[k];
            printf("%d -> %s\t%s\t%s\n", k,
                   addressbook->contact_details[ind].Name,
                   addressbook->contact_details[ind].Mobile_number,
                   addressbook->contact_details[ind].Mail_ID);
        }
        int choice;
        printf("Enter the number of the contact you want to edit: ");       //according to their index it should check
        scanf("%d", &choice);
        if (choice < 0 || choice >= size) {
            printf("Invalid selection.\n");             //if not present it will show invalid selection
            return 1;
        }
        idx = matches[choice];
    } else {
        idx = matches[0];  // only one match
    }

    // Step 4: Loop for editing multiple fields
    int opt;
    do {                                        //if it matches with the multiple contact then it will show according to our choice
        printf("\nEdit Contact menu:\n");
        printf("1. Name\n2. Mobile number\n3. Mail ID\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &opt);

        switch(opt) {                                   //This fisrt choice to edit by name
            case 1:
                printf("Enter new Name: ");
                scanf(" %31[^\n]", addressbook->contact_details[idx].Name);
                printf("Name updated successfully.\n");
                break;
            case 2: {                                   //Second is to edit by their phone number
                char new_num[100];  // big enough to hold over-typed input
                while (1) {
                    int check = 1;
                    printf("Enter new Mobile number: ");
                scanf(" %[^\n]", new_num);

        // Check length == 10
                    if (strlen(new_num) != 10) {
                printf("Mobile number must be exactly 10 digits!\n");       //printing the error message if it more than 10
                continue;
                }

        // Check only digits
        int valid = 1;
        for (int i = 0; i < 10; i++) {
            if (!isdigit(new_num[i])) {
                valid = 0;
                break;
            }
        }
        if (!valid) {                   //not valid means it will return the error message
            printf("Mobile number must contain only digits!\n");
            continue;
        }

        // Duplicate check (ignore current contact itself)
        for (int i = 0; i < addressbook->contact_count; i++) {
            if (i != idx && strcmp(addressbook->contact_details[i].Mobile_number, new_num) == 0) {
                printf("The number you entered already exists.\n");
                check = 0;
                break;
            }
        }

        if (check) {                                        //if it doesn't matches with the number and it is exactly equal to correct requirement then it will update in the contact
            strcpy(addressbook->contact_details[idx].Mobile_number, new_num);
            printf("Mobile number updated successfully.\n");
            break;
        }
    }
    break;
}

//while editing the mail it checks for the unique mail id
case 3: {
    char new_mail[50];
    while (1) {
        int check = 1;
        printf("Enter new Mail ID: ");
        scanf(" %34[^\n]", new_mail);

        // Validate email
        if (!validate_mailid(new_mail)) {
            printf("Invalid Mail ID. Please try again.\n");
            continue;
        }

        // Duplicate check (ignore current contact itself)
        for (int i = 0; i < addressbook->contact_count; i++) {
            if (i != idx && strcmp(addressbook->contact_details[i].Mail_ID, new_mail) == 0) {
                printf("Mail ID already exists.\n");
                check = 0;
                break;
            }
        }
        //flag where it will check for the email updation
        if (check) {
            strcpy(addressbook->contact_details[idx].Mail_ID, new_mail);
            printf("Mail ID updated successfully.\n");
            break;
        }
    }
    break;
}
            //This case is for exiting
            case 4:
            {
                printf("Exiting edit menu.\n");
                break;
            }
            default:
                printf("Invalid option. Try again.\n");
        }
    } while(opt != 4);

    printf("\nAll changes saved for this contact.\n");
    return 1;
}


//Delete Function definition
void delete_contact(AddressBook *addressbook) {
    int del;
    printf("\nEnter the option to be deleted by their: ");
    printf("\n1.Name\n2.Mobile No\n3.Mail id\n");
    scanf("%d", &del);

    char str[100];
    switch (del) {
        case 1: {
            printf("Deleting contact by their name\n");
            printf("Please enter the name to search: ");
            scanf(" %[^\n]", str);

            int rep[100], size = 0;
            // Search for substring match in names
            for (int i = 0; i < addressbook->contact_count; i++) {
                if (strstr(addressbook->contact_details[i].Name, str) != NULL) {
                    rep[size++] = i;
                }
            }

            if (size == 0) {
                printf("No contact found with name containing '%s'\n", str);
                return;
            } 
            else if (size == 1) {
                // Ask Y/N before deleting
                int ind = rep[0];
                printf("Found: %s %s %s\n",
                       addressbook->contact_details[ind].Name,
                       addressbook->contact_details[ind].Mobile_number,
                       addressbook->contact_details[ind].Mail_ID);

                char ch;
                printf("Do you really want to delete this contact? (y/n): ");
                scanf(" %c", &ch);

                if (ch == 'y' || ch == 'Y') {                   //It checks for whether it asks once before deleting
                    for (int i = ind; i < addressbook->contact_count - 1; i++) {
                        addressbook->contact_details[i] = addressbook->contact_details[i + 1];
                    }
                    addressbook->contact_count--;
                    printf("Contact deleted successfully.\n");
                } else {
                    printf("Deletion cancelled.\n");
                }
            } 
            else {                                                        //It is the condition for it exists multiple contacts
                printf("Found multiple contacts:\n");
                for (int k = 0; k < size; k++) {
                    int ind = rep[k];
                    printf("%d -> %s %s %s\n", ind,
                           addressbook->contact_details[ind].Name,
                           addressbook->contact_details[ind].Mobile_number,
                           addressbook->contact_details[ind].Mail_ID);
                }

                int j;
                printf("Enter the index of the contact to delete: ");
                scanf("%d", &j);

                int flag = 0;                                               //if it matches it  uses substring and check for flag to set
                for (int k = 0; k < size; k++) {
                    if (j == rep[k]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag) {                                             //if flag then it will ask for index which needs to be deleted
                    for (int i = j; i < addressbook->contact_count - 1; i++) {
                        addressbook->contact_details[i] = addressbook->contact_details[i + 1];
                    }
                    addressbook->contact_count--;
                    printf("Contact deleted successfully.\n");          //Prinitng the statement after deleting
                } else {
                    printf("Invalid index. Try again.\n");
                }
            }
            break;
        }


        //It checks for phone number because phone number always unique
        case 2: {                       
            printf("Deleting contact by their phone no.\n");
            printf("Please enter the phone number: ");
            scanf(" %[^\n]", str);

            int rep[100], size = 0;
            for (int i = 0; i < addressbook->contact_count; i++) {
                if (strcmp(addressbook->contact_details[i].Mobile_number, str) == 0) {
                    rep[size++] = i;
                }
            }

            if (size == 0) {
                printf("No contact found with phone number '%s'\n", str);
                return;
            } 
            else if (size == 1) {
                int ind = rep[0];
                printf("Found: %s %s %s\n",
                       addressbook->contact_details[ind].Name,
                       addressbook->contact_details[ind].Mobile_number,
                       addressbook->contact_details[ind].Mail_ID);

                char ch;
                printf("Do you really want to delete this contact? (y/n): ");
                scanf(" %c", &ch);

                if (ch == 'y' || ch == 'Y') {                   //Before deleting it will ask for confirmation
                    for (int i = ind; i < addressbook->contact_count - 1; i++) {
                        addressbook->contact_details[i] = addressbook->contact_details[i + 1];
                    }
                    addressbook->contact_count--;
                    printf("Contact deleted successfully.\n");
                } else {
                    printf("Deletion cancelled.\n");        //Delete concelled if pressed no
                }
            } 
            else {
                printf("Found multiple contacts with same phone number:\n");
                for (int k = 0; k < size; k++) {
                    int ind = rep[k];
                    printf("%d -> %s %s %s\n", ind,
                           addressbook->contact_details[ind].Name,
                           addressbook->contact_details[ind].Mobile_number,
                           addressbook->contact_details[ind].Mail_ID);
                }

                int j;
                printf("Enter the index of the contact to delete: ");
                scanf("%d", &j);

                int flag = 0;
                for (int k = 0; k < size; k++) {
                    if (j == rep[k]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag) {
                    for (int i = j; i < addressbook->contact_count - 1; i++) {
                        addressbook->contact_details[i] = addressbook->contact_details[i + 1];
                    }
                    addressbook->contact_count--;
                    printf("Contact deleted successfully.\n");
                } else {
                    printf("Invalid index. Try again.\n");
                }
            }
            break;
        }
        //checks for email id which needs to be deleted
        case 3: {                                   
            printf("Deleting contact by their mail ID\n");
            printf("Please enter the mail ID: ");
            scanf(" %[^\n]", str);

            int rep[100], size = 0;
            for (int i = 0; i < addressbook->contact_count; i++) {
                if (strcmp(addressbook->contact_details[i].Mail_ID, str) == 0) {
                    rep[size++] = i;
                }
            }

            if (size == 0) {
                printf("No contact found with mail ID '%s'\n", str);
                return;
            } 
            else if (size == 1) {
                int ind = rep[0];
                printf("Found: %s %s %s\n",
                       addressbook->contact_details[ind].Name,
                       addressbook->contact_details[ind].Mobile_number,
                       addressbook->contact_details[ind].Mail_ID);

                char ch;
                printf("Do you really want to delete this contact? (y/n): ");
                scanf(" %c", &ch);

                if (ch == 'y' || ch == 'Y') {
                    for (int i = ind; i < addressbook->contact_count - 1; i++) {
                        addressbook->contact_details[i] = addressbook->contact_details[i + 1];
                    }
                    addressbook->contact_count--;
                    printf("Contact deleted successfully.\n");
                } else {
                    printf("Deletion cancelled.\n");
                }
            } 
            else {
                printf("Found multiple contacts with same mail ID:\n");
                for (int k = 0; k < size; k++) {
                    int ind = rep[k];
                    printf("%d -> %s %s %s\n", ind,
                           addressbook->contact_details[ind].Name,
                           addressbook->contact_details[ind].Mobile_number,
                           addressbook->contact_details[ind].Mail_ID);
                }

                int j;
                printf("Enter the index of the contact to delete: ");
                scanf("%d", &j);

                int flag = 0;
                for (int k = 0; k < size; k++) {
                    if (j == rep[k]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag) {
                    for (int i = j; i < addressbook->contact_count - 1; i++) {
                        addressbook->contact_details[i] = addressbook->contact_details[i + 1];
                    }
                    addressbook->contact_count--;
                    printf("Contact deleted successfully.\n");
                } else {
                    printf("Invalid index. Try again.\n");
                }
            }
            break;
        }

        default: {
            printf("Invalid option\n");
            return;
        }
    }
}

//Display contacts but it will show in terminal
void list_contacts(AddressBook *addressbook)
{
    Contacts temp;
    if(addressbook->contact_count==0){
    printf("total Number of contacts are : %d",addressbook->contact_count);
    return;
    }

    for(int i=0;i<addressbook->contact_count-1;i++){
        for(int j=0;j<addressbook->contact_count-i-1;j++){
            int cmp=0;
            cmp=strcmp(addressbook->contact_details[j].Name,addressbook->contact_details[j+1].Name);
            if(cmp>0){
                temp=addressbook->contact_details[j];
                addressbook->contact_details[j]=addressbook->contact_details[j+1];
                addressbook->contact_details[j+1]=temp;
            }
        }
    }

    //Print all the contacts
    printf("Total Number of contacts are : %d\n",addressbook->contact_count);       //Total number of address count
    printf("------------------------------------------------------------------------------\n");
    printf("%-20s %-20s %-30s\n", "Name", "Mobile Number", "Mail ID");
    printf("------------------------------------------------------------------------------");
    for(int i=0;i<addressbook->contact_count;i++){
    printf("\n%-20s",addressbook->contact_details[i].Name);     //Based on their spaces it will print
    printf("%-20s",addressbook->contact_details[i].Mobile_number);     
    printf("%-30s",addressbook->contact_details[i].Mail_ID);
    }
    printf("\n-----------------------------------------------------------------------------");
}