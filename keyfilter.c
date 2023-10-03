#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ADDRESSES 42
#define MAX_CHAR 100

bool isDuplicit(char letter, char letters[], int letters_count);

int main(int argc, char *argv[]) {

  char user_search[MAX_CHAR];
  // char *addresses[MAX_ADDRESSES];
  char letters[MAX_CHAR];

  if (argc == 2) {
    // TODO: Maybe some input validation?
    strcpy(user_search, argv[1]);
    printf("User input %s %lu", user_search, strlen(argv[1]));
  }

  char buf[MAX_CHAR]; // 99 charachters + eol per line
  int word_count = 0;
  int used_letter_count = 0;
  while (fgets(buf, sizeof buf, stdin) != NULL) {

    // Loop throught word
    printf("word: %s", buf);
    for (int i = 0; buf[i] != '\n'; i++) {
      printf("%c %i\n", buf[i], i);

      buf[i] = toupper(buf[i]); // We do not care abou size

      // We do not have any input
      if (argc != 2) {
        // Chech for duplicity
        if (!isDuplicit(toupper(buf[i]), letters, used_letter_count)) {
          letters[used_letter_count] = buf[i];
          // letters[used_letter_count + 1] = '\0'; MAYBE???
          used_letter_count += 1;
          printf("letter saved: %c %d\n", letters[word_count],
                 used_letter_count);
        }
        break;
      } else if (argc == 2) {

        if (buf[i] != user_search[i]) {
          printf("not found %c\n", user_search[i]);
          letters[used_letter_count] = buf[i];
          used_letter_count += 1;
          break;
        }
      }
    }
    // if argv[1] letter after that
    // else save first letter
    word_count += 1;
  }

  // Sort all letters here
  printf("word count %d letter: %d\n", word_count, used_letter_count);
  for (int j = 0; j < used_letter_count; j++) {
    printf("Letter: %c\n", letters[j]);
  }

  return 0;
}

bool isDuplicit(char letter, char letters[], int letters_count) {
  for (int i = 0; i < letters_count; i++) {
    // printf("check duplicity: %c, %c\n", letter, letters[i]);
    if (letters[i] == letter) {
      printf("Match do not save\n");
      return true;
    }
  }
  return false;
}
