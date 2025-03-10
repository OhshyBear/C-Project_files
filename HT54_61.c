/* 
Trevor Huddleston
1717354
The following program is a contact menu for adding, and displaying contacts. If the contact has already been created it will not add the same contact a second time. 
*/

#include <stdio.h>  // printf, scanf
#include <stdlib.h> // malloc, realloc, free, exit, NULL
#include <string.h> // strlen, strcpy

/* display menu on screen */
void display_menu(void);

/* Prints size number of strings, one per line. */
void print_contacts(char *strlist[], int size);

/* Add one more contact to the contact list */
char **add_contact(char **strlist, int *psize);

/* free up space allocated to dynamic string array strlist */
void free_str_arr(char *strlist[], int size);

// ADD CODE #3-1: declaration of search_str()
int search_str(char **strlist, int size, const char *name);

//--------------------------

int main(void) {
  char **contacts = NULL; // store a list of contacts (just names at this point)
  int size = 0;           // track the number of contacts in the list

  int choice = -1;
  do {
    display_menu();

    char **result = NULL; // store the returned result of add_contact()
    scanf("%d", &choice);
    switch (choice) {
    case 0:
      puts("End the system. Bye!");
      break;
    case 1:
      result = add_contact(contacts, &size);
      if (result == NULL) {
        free_str_arr(contacts, size); // free up heap space
        exit(1);
      } else {
        contacts = result;
      }
      break;
    case 2:
      print_contacts(contacts, size);
      break;
    default:
      puts("Invalid choice. Try again.");
    }
  } while (choice != 0);

  free_str_arr(contacts, size); // free up heap space
} // end main()

//--------------------------

/* display menu on screen */
void display_menu(void) {
  char *menu_strs[] = {"\n=========================\n",
                       "Contact Management System\n",
                       "\n",
                       "1. Add a new contact\n",
                       "2. Display contacts\n",
                       "3. Search for a contact\n",
                       "4. Delete a contact\n",
                       "0. Exit\n",
                       "Enter your choice (0~4): "};

  int length =
      sizeof(menu_strs) / sizeof(char *); // number of strings in menu_strs

  for (int i = 0; i < length; i++) {
    printf("%s", menu_strs[i]);
  }
}

//--------------------------

char **add_contact(char **strlist, int *psize) {
  // strlist is a string array
  // strlist[i] is a string, 0<= i < *psize

  // 1. Input a new contact.
  char name[100];
  printf("Enter one contact (LastName, FirstName): ");
  fgetc(stdin); // consume '\n' at the end of line

  if (1 != scanf("%[^\n]s", name)) {
    printf("Error: contact input failed.\n");
    return NULL; // failed to input a name string
  }

  // ADD CODE #3-3: call search_str() to check if the name is already in the
  if (search_str(strlist, *psize, name)) {
      printf("Contact \"%s\" already exists.\n", name);
      return strlist; // No need to add duplicate
    }

  //== END ADD CODE #3-3


  
  // ADD CODE #1
  // 2. Resize the dynamic string array to add one more spot.
  int count = *psize + 1; // new size
    char **new_strlist = NULL;
    new_strlist = (char **)realloc(strlist, count * sizeof(char *));
    if (new_strlist == NULL) { // reallocation failed
      puts("Error reallocating memory.");
      return NULL;
    }
  
  // 3.1 allocate space for the new contact  */
  char *new_contact = (char *)malloc((strlen(name) + 1) * sizeof(char));
    if (new_contact == NULL) { // allocation failed
      puts("Error allocating memory for new contact.");
      return NULL;
    }

  
  // 3.2 now add the new contact
  new_strlist[count - 1] = new_contact;
  strcpy(new_contact, name);

  (*psize)++; // increment the size
  printf("Contact \"%s\" has been added.\n", name);

  // 4. Return the newly allocated array on success */
  return new_strlist;
  

  return NULL; // fake return. delete it
}

//--------------------------

/* Prints size number of strings, one per line. */
void print_contacts(char *strlist[], int size) {
  printf("You have %d contacts: [\n", size);
  for (int i = 0; i < size; i++) {
    printf("%s\n", strlist[i]);
  }
  printf("]\n");
}

//--------------------------

/* free up space allocated to dynamic string array strlist */
void free_str_arr(char *strlist[], int size) {
  // ADD CODE #2
  for (int i = 0; i < size; i++) {
    free(strlist[i]); // free each string
    strlist[i] = NULL;
  }
  free(strlist); // free the array of pointers
  strlist = NULL;
}




//--------------------------

// ADD CODE #3-2: definition of search_str()
int search_str(char **strlist, int size, const char *name) {
  for (int i = 0; i < size; i++) {
    if (strcmp(strlist[i], name) == 0) {
      return 1; // found
    }
  }
  return 0; // not found
}