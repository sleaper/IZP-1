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
  int user_search_length = 0;
  char enabled_letters[MAX_CHAR];
  int enable_letters_count = 0;
  int matches = 0;
  char last_match[MAX_CHAR];

  if (argc == 2) {
    // TODO: Maybe some input validation?
    strcpy(user_search, argv[1]);
    user_search_length = strlen(argv[1]);
    printf("User input %s %lu\n", user_search, strlen(argv[1]));
  }

  char buf[MAX_CHAR]; // 99 charachters + eol per line
  while (fgets(buf, sizeof buf, stdin) != NULL) {

    printf("word: %s", buf);
    // No argument, we care only about first letters
    if (argc != 2) {
      // Chech for duplicity
      if (!isDuplicit(buf[0], enabled_letters, enable_letters_count)) {
        enabled_letters[enable_letters_count] = buf[0];
        enable_letters_count += 1;
        printf("letter saved: %d\n", enable_letters_count);
      }
    } else if (argc == 2) {

      int equal_letters = 0;
      for (int i = 0; i < user_search_length; i++) {
        user_search[i] = toupper(user_search[i]);
        buf[i] = toupper(buf[i]);
        printf("Comparing %c, %c equal: %d\n", user_search[i], buf[i],
               equal_letters);

        if (user_search[i] == buf[i]) {
          printf("Equals!!\n");
          equal_letters += 1;
        } else {
          break;
        }
      }

      printf("IS MATCH? equal_letters %d, search_length %d\n", equal_letters,
             user_search_length);
      if (equal_letters == user_search_length) {
        enabled_letters[enable_letters_count] = buf[user_search_length];
        enable_letters_count += 1;
        matches += 1;
        strcpy(last_match, buf);
      }
    }
  }

  printf("STATUS: matches: %d\n", matches);
  if (matches == 1) {
    printf("Found: ");
    // print here final word
  } else if (matches > 1) {
    printf("Enable: ");
    // Sort all letters here
    for (int j = 0; j < enable_letters_count; j++) {
      printf("%c", enabled_letters[j]);
    }
    printf("\n");

  } else if (matches == 0) {
    printf("Not found\n");
    return 0;
  }

  return 0;
}

// DO not use bool
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
