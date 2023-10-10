/**
 * @file keyfilter.c
 *
 * @author  Spac Petr <xspacpe00@stud.fit.vutbr.cz>
 *
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE 102 // 100 characters + \0 + \n
#define MAX_WORD 100 // 100 characters

/**
 * @brief Determine if new letter is inside of enabled_letters
 *
 * @param letter array in which we search for in the provided array
 * @param letters array of current enabled letters
 * @param letters_count size of the letters array
 * @return 0 or 1 if letter is in the provided array of letters
 */
int is_letter_duplicit(char letter, char letters[], int letters_count) {
  for (int i = 0; i < letters_count; i++) {
    if (letters[i] == letter) {
      return 1;
    }
  }
  return 0;
}

/**
 * @param letters array of current enabled letters
 * @param letters_count size of the letters array
 */
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

/**
 * @param buffer array of letters to capitalize
 */
void capitalize_word(char *buffer) {
  for (int i = 0; buffer[i] != '\n'; i++) {
    buffer[i] = toupper(buffer[i]);
  }
}

/**
 * @brief Validates user input
 *
 * @param input input provided by user
 * @return 1 (valid) or 0 (not valid)
 */
int is_valid_input(char *input) {
  if (strlen(input) > MAX_WORD) {
    printf("100 characters is max!\n");
    return 0;
  }

  for (int i = 0; input[i] != '\0'; i++) {
    if (!isalpha(input[i])) {
      printf("You can use only characters from alphabet!\n");
      return 0;
    }
  }
  return 1;
}

int main(int argc, char *argv[]) {
  char user_search[MAX_LINE];
  int user_search_length = 0;
  char enabled_letters[MAX_LINE];
  int enabled_letters_count = 0;

  int prefix_matches = 0;
  char last_match[MAX_LINE];

  if (argc == 2) {
    if (is_valid_input(argv[1])) {
      strcpy(user_search, argv[1]);
      user_search_length = strlen(argv[1]);
    } else {
      return 1;
    }
  }

  char buf[MAX_LINE];
  while (fgets(buf, sizeof buf, stdin) != NULL) {
    // Case insensitive word
    capitalize_word(buf);

    // No argument, we care only about first letters
    if (argc == 1) {
      // Check for duplicity
      if (!is_letter_duplicit(buf[0], enabled_letters, enabled_letters_count)) {
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

      // Is prefix equal to user search?
      if (equal_letters == user_search_length) {
        if (!is_letter_duplicit(buf[user_search_length], enabled_letters,
                                enabled_letters_count)) {

          // Save the next letter after prefix
          // if prefix is whole address, we do not want \n (c c c c \n \0)
          if ((int)strlen(buf) - 1 != user_search_length) {
            enabled_letters[enabled_letters_count] = buf[user_search_length];
            enabled_letters_count += 1;
          }
        }

        prefix_matches += 1;
        // Save matched word
        strcpy(last_match, buf);
      }
    } else {
      printf("Wrong number of arguments!\n");
      return 1;
    }
  }

  if (prefix_matches == 1) {
    printf("Found: %s", last_match);
    return 0;
  } else if (argc != 2 || prefix_matches > 1) {
    printf("Enable: ");
    print_ordered_letters(enabled_letters, enabled_letters_count);
    printf("\n");
    return 0;
  } else if (argc == 2 && prefix_matches == 0) {
    printf("Not found\n");
    return 0;
  }

  return 0;
}
