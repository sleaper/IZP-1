#include <stdio.h>
#include <stdlib.h>

#define MAX_ADDRESSES 42
#define MAX_CHAR 100

int main(int argc, char *argv[]) {

  printf("test %d %s\n", argc, argv[0]);

  char *user_search = "";
  // char *addresses[MAX_ADDRESSES];
  char letters[MAX_ADDRESSES];

  if (argc == 2) {
    // TODO: Maybe some input validation?
    printf("So you want to search somethign huh %s \n", user_search);
    user_search = argv[1];
  }

  // 99 charachters + eol per line
  char buf[MAX_CHAR];
  while (fgets(buf, sizeof buf, stdin) != NULL) {
    //
    // Loop throught word
    printf("word: %s", buf);
    for (int i = 0; buf[i] != '\n'; i++) {
      printf("%c %i\n", buf[i], i);

      if (!user_search && i == 0) {
        letters[i] = buf[i];
      } else {
      }
    }
    // printf("\n");
    // if argv[1] letter after that
    // else save first letter
  }

  return 0;
}
