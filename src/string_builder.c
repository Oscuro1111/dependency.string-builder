#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/string_builder.h"

String *allocate_string(uint32_t reserve) {
  uint32_t length;

  String *string;

  if (reserve == 0 || reserve < 0) {
    length = 256;
  } else if (reserve > 0) {
    length = reserve;
  }

  string = (String *)malloc(sizeof(String));

  if (string == NULL) {

    fprintf(stderr, "Unable to allocate memory.");
    return NULL;
  }

  string->length = length;
  string->current = 0;
  string->str = (char *)malloc(sizeof(char) * length);

  if (string->str == NULL) {
    fprintf(stderr, "Unable to allocate memory.");
    free(string);
    return NULL;
  }
  return string;
}

void free_string(String *string) {

  if (string != NULL) {
    if (string->str != NULL) {
      free(string->str);
    }

    free(string);
  }
}

int insert_string(String **string, char *str) {
  if (str == NULL) {
    return -1;
  }

  uint32_t len = strlen(str);

  if (len >= ((*string)->length) - ((*string)->current)) {

    String *temp = (*string);

    *string = allocate_string((temp->length + len) * 2);

    if (*string == NULL) {
      fprintf(stderr, "Unable to allocate memory for new insertion\n");
      return -1;
    }

    memcpy((*string)->str, temp->str, temp->current);

    memcpy((*string)->str + temp->current, str, len);

    (*string)->current = temp->current + len;
    (*string)->length = (temp->length + len) * 2;

    (*string)->str[(*string)->current] = '\0';

    free_string(temp);
    return 0;
  }

  memcpy((*string)->str + (*string)->current, str, len);

  (*string)->current += len;

  (*string)->str[(*string)->current] = '\0';

  return 0;
}
