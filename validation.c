#include <stdio.h>
#include <string.h>
#include <ctype.h>
//Validation whether matches all requirements
int validate_name(char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!((name[i] >= 'a' && name[i] <= 'z')||(name[i] >= 'A' && name[i] <= 'Z')||(name[i] == ' ')))   // allow spaces
        {
            printf("Its Invalid name must contain only alphabets");
            return 0;                                    //it run infinitely unless we give the valid name
        }
    }
    return 1;           //returns when only it has only we give valid name
}


//Validating Number as per addressbook
int validate_number(char *mobile_number) {
    int len = strlen(mobile_number);
    if (len != 10) return 0;  // must be 10 digits

    if (!(mobile_number[0] >= '6' && mobile_number[0] <= '9'))
        return 0;  // first digit should always start from 6 to 9 only

    for (int i = 0; i < 10; i++) {
        if (!(mobile_number[i] >= '0' && mobile_number[i] <= '9'))
            return 0;  // all digits check
    }
    return 1;
}

//More validations whether it matches all requirements
int validate_mailid(char *mail_id) {
    int mail_len = strlen(mail_id);

    // convert to lowercase
    for (int i = 0; i < mail_len; i++) {
        mail_id[i] = tolower(mail_id[i]);
    }

    // must start with a lowercase letter
    if (!(mail_id[0] >= 'a' && mail_id[0] <= 'z')) {
        printf("Mail must start with a lowercase letter\n");
        return 0;
    }

    int index_of_at = -1, index_of_dot = -1;
    int num_ats = 0, num_dots_after_at = 0;

    for (int i = 0; i < mail_len; i++) {
        char ch = mail_id[i];

        // reject spaces explicitly
        if (ch == ' ') {
            printf("Email must not contain spaces\n");
            return 0;
        }

        // allow only letters, digits, @, ., _, -
        if (!(isalnum(ch) || ch == '@' || ch == '.' || ch == '_' || ch == '-')) {
            printf("Mail contains invalid character '%c'\n", ch);
            return 0; // invalid character
        }

        if (ch == '@') {
            index_of_at = i;
            num_ats++;
        }

        if (ch == '.') {
            index_of_dot = i;
            if (index_of_at != -1 && i > index_of_at) {
                num_dots_after_at++;
            }
        }
    }
    //it checks for exactly only @ if doesn't match it print 
    if (num_ats != 1) {
        printf("Email must contain exactly one '@'\n");
        return 0;
    }
    //checks for whether dot 
    if (index_of_dot == -1 || index_of_dot <= index_of_at + 1) {
        printf("Email must contain a '.' after '@'\n");
        return 0;
    }
    //checks it shoulkd check for . 
    if (index_of_dot >= mail_len - 1) {
        printf("Email must have characters after the last '.'\n");
        return 0;
    }
    //it checks it should have only one 2 and .
    if (num_dots_after_at != 1) {
        printf("Email must contain only one '.' after '@'.\n");
        return 0;
    }

    // must end with ".com"
    if (mail_len < 4 || strcmp(mail_id + mail_len - 4, ".com") != 0) {
        printf("Email must end with '.com'.\n");
        return 0;
    }

    return 1; // valid email
}






