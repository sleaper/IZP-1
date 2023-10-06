/// @file keyfilter.c
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAR 102 // 100 characters + \0 + \n

/**
 * @brief Determine if new letter is inside of enabled_letters
 *
 * @param letter, which we search for in the provided array
 * @param letters, array of current enabled letters
 * @param letters_count, size of the letters array
 * @return 1 if letter is in the provided array of letters, otherwise 0
 */
int isDuplicit(char letter, char letters[], int letters_count) {
  for (int i = 0; i < letters_count; i++) {
    if (letters[i] == letter) {
      return 1;
    }
  }
  return 0;
}

void print_ordered_letters(char letters[], int letters_count) {
  // Simple bubble sort
  for (int i = 0; i < letters_count; i++) {
    for (int j = 0; j < letters_count - 1; j++) {
      if (letters[j] > letters[j + 1]) {
        char tmp = letters[j];
        letters[j] = letters[j + 1];
        letters[j + 1] = tmp;
      }
    }
  }

  for (int i = 0; i < letters_count; i++) {
    printf("%c", letters[i]);
  }

  return;
}

void capitalizeWord(char *buffer) {
  for (int i = 0; buffer[i] != '\n'; i++) {
    buffer[i] = toupper(buffer[i]);
  }
}

int main(int argc, char *argv[]) {
  char user_search[MAX_CHAR];
  int user_search_length = 0;
  char enabled_letters[MAX_CHAR];
  int enabled_letters_count = 0;

  int prefix_matches = 0;
  char last_match[MAX_CHAR];

  if (argc == 2) {
    // TODO: Maybe some input validation?
    strcpy(user_search, argv[1]);
    user_search_length = strlen(argv[1]);
    // printf("User input %s %lu\n", user_search, strlen(argv[1]));
  }

  char buf[MAX_CHAR];
  while (fgets(buf, sizeof buf, stdin) != NULL) {

    // Case insesitive word
    capitalizeWord(buf);

    // No argument, we care only about first letters
    if (argc == 1) {
      // Chech for duplicity
      if (!isDuplicit(buf[0], enabled_letters, enabled_letters_count)) {
        enabled_letters[enabled_letters_count] = buf[0];
        enabled_letters_count += 1;
      }
    } else if (argc == 2) {

      int equal_letters = 0;
      for (int i = 0; i < user_search_length; i++) {
        // Case insensitive user search
        user_search[i] = toupper(user_search[i]);

        if (user_search[i] == buf[i]) {
          equal_letters += 1;
        } else {
          break;
        }
      }

      if (equal_letters == user_search_length) {
        if (!isDuplicit(buf[user_search_length], enabled_letters,
                        enabled_letters_count)) {

          // Save the next letter after prefix
          enabled_letters[enabled_letters_count] = buf[user_search_length];
          enabled_letters_count += 1;
        }

        prefix_matches += 1;
        // Save matched word
        strcpy(last_match, buf);
      }
    } else {
      printf("Wrong number of arguments!");
      return 1;
    }
  }

  if (prefix_matches == 1) {
    printf("Found: %s", last_match);
    return 0;
  } else if (argc != 2 || prefix_matches > 1) {
    printf("Enable: ");
    print_ordered_letters(enabled_letters, enabled_letters_count);
    return 0;
  } else if (argc == 2 && prefix_matches == 0) {
    printf("Not found\n");
    return 0;
  }

  return 0;
}
