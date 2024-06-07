#include <ctype.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "default.h"

const char *latinTokens[] = {
    "f",  "u",   "þ",  "a",  "r",   "k",   "c",   "g",   "w",  "h",
    "n",  "i",   "j",  "y",  "æ",   "ï",   "p",   "z",   "s",  "t",
    "b",  "e",   "m",  "l",  "ŋ",   "o",   "d",   "v",   "ð",  "x",
    "ch", "ij",  "cc", "th", "eau", "chr", "ing", "chl", "ng", "chj",
    "nk", "chw", "ei", "ø",  "å",   "q",   NULL};
const char *elderFutharkTokens[] = {
    "ᚠ", "ᚢ",  "ᚦ", "ᚨ",  "ᚱ",  "ᚲ",  "ᚲ", "ᚷ",  "ᚹ",  "ᚺ", "ᚾ", "ᛁ",
    "ᛃ", "ᛃ",  "ᛇ", "ᛇ",  "ᛈ",  "ᛉ",  "ᛋ", "ᛏ",  "ᛒ",  "ᛖ", "ᛗ", "ᛚ",
    "ᛜ", "ᛟ",  "ᛞ", "ᚠ",  "ᚦ",  "ᚲᛋ", "ᚷ", "ᛖ",  "ᚲᛋ", "ᚦ", "ᛟ", "ᚺᚱ",
    "ᛜ", "ᚺᛚ", "ᛜ", "ᚺᛃ", "ᛜᚲ", "ᚺᚹ", "ᛋ", "ᛟᛖ", "ᚨᚨ", "ᚲ", NULL};

TokenMapper *token_mapper_new() {
  GHashTable *latinToFutharkMap;

  latinToFutharkMap = g_hash_table_new(g_str_hash, g_str_equal);
  if (!latinToFutharkMap) {
    return NULL;
  }

  for (int i = 0; latinTokens[i] != NULL; i++) {
    g_hash_table_insert(latinToFutharkMap, (gpointer)latinTokens[i],
                        (gpointer)elderFutharkTokens[i]);
  }

  TokenMapper *tokenMapper = malloc(sizeof(TokenMapper));
  if (!tokenMapper) {
    // Handle error if memory allocation fails
    g_hash_table_destroy(latinToFutharkMap);
    return NULL;
  }
  tokenMapper->map = latinToFutharkMap;
  return tokenMapper;
}

/* This function is used to transliterate a string from Latin characters to
 * Elder Futhark characters. */
char *to_fut(TokenMapper *map, char *str) {
  size_t len = strlen(str);
  char *fut_str =
      malloc(len * 2 + 1); // Allocate more space for potential expansions
  fut_str[0] = '\0';       // Initialize to an empty string

  char *p = str;
  int token_index = 0;
  char *token = malloc(len + 1);

  do {
    if (*p == '\0') {
      strcat(fut_str, "\0");
      return fut_str;
    }
    if (*p == ' ') {
      strcat(fut_str, " ");
    } else {
      if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
        char c = tolower(*p);
        token[token_index] = c;
        token[token_index + 1] = '\0';

        if (g_hash_table_contains(map->map, token)) {
          const char *futhark = g_hash_table_lookup(map->map, token);
          size_t len = strlen(futhark);
          strncat(fut_str, futhark, len);

          token_index = -1;
          token[0] = '\0';
        }
      } else {
        // if the current character is not a letter, add the character to the
        // futhark string
        strncat(fut_str, p, 1);

        // reset token
        token_index = 0;
        token[0] = '\0';
      }
    }
    p++;
    token_index++;
  } while (*p != '\0');

  return fut_str;
}
