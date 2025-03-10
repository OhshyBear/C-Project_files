/* 
Trevor Huddleston
1717354
A data encryption program using the Caesar Cipher to encrypt data.
*/


#include <stdio.h>
#include <string.h> // strlen()

/* Encrypt the first "length" characters of plaintext using Caesar Cipher encryption with the specified "key" value. 
   - Modify the plaintext parameter. 
   - Only apply the encryption on letters. 
   - Preserve the case of letters (uppercase to uppercase, and lowercase to lowercase).
   - Assume length <= the number of characters in plaintext
*/
void caesar_encrypt(char plaintext[], int length, int key);




/* Decrypt the first "length" characters of ciphertext that have been encrypted using Caesar encryption with the specified "key" value. 
   - Modify the ciphertext parameter. 
   - Only letters have been encrypted. 
   - Preserve the case of letters (uppercase to uppercase, and lowercase to lowercase).
   - Assume length <= the number of characters in ciphertext
*/
void caesar_decrypt(char ciphertext[], int length, int key);



/********************************/

int main(void) {
  int key = 10;
  char text[] = "No problem";
  
  caesar_encrypt(text, strlen(text), key);
  printf("After encryption: %s\n", text); // should be: Xy zbylvow.

  // ADD CODE #3: call caesar_decrypt() to decrypt var "text" and 
  //              print out the result.
  caesar_decrypt(text, strlen(text), key);
  printf("After encryption: %s\n", text); // should be: No problem.

}

/********************************/

// ADD CODE #1: function definition of caesar_encrypt()
void caesar_encrypt(char plaintext[], int length, int key){
    for (int i = 0; i < length; i++){
        char ch = plaintext[i];
        if (ch >= 'a' && ch <= 'z'){ // checks for lower case
            plaintext[i] = (ch - 'a' + key) % 26 + 'a'; /* 
            breaks the letter to a number and adds the key to that number, 
            then modulo it to ensure wrap around, 
            then convert it back to a letter
            */ 
        } else if (ch >= 'A' && ch <= 'Z'){
            plaintext[i] = (ch - 'A' + key) % 26 + 'A';
        }
    }
}

// ADD CODE #2: function definition of caesar_decrypt()
void caesar_decrypt(char ciphertext[], int length, int key){
    for (int i = 0; i < length; i++){
        char ch = ciphertext[i]; 
        if (ch >= 'a' && ch <= 'z'){
            ciphertext[i] = (ch - 'a' - key + 26) % 26 + 'a';
        } else if (ch >= 'A' && ch <= 'Z'){
            ciphertext[i] = (ch - 'A' - key + 26) % 26 + 'A';
        }
    }
}