#include <ctype.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "default.h"

const char *latin_tokens[] = {
    "f",  "u",   "þ",  "a",  "r",   "k",   "c",   "g",   "w",  "h",
    "n",  "i",   "j",  "y",  "æ",   "ï",   "p",   "z",   "s",  "t",
    "b",  "e",   "m",  "l",  "ŋ",   "o",   "d",   "v",   "ð",  "x",
    "ch", "ij",  "cc", "th", "eau", "chr", "ing", "chl", "ng", "chj",
    "nk", "chw", "ei", "ø",  "å",   "q",   NULL};

const char *elder_futhark_tokens[] = {
    "ᚠ", "ᚢ",  "ᚦ", "ᚨ",  "ᚱ",  "ᚲ",  "ᚲ", "ᚷ",  "ᚹ",  "ᚺ", "ᚾ", "ᛁ",
    "ᛃ", "ᛃ",  "ᛇ", "ᛇ",  "ᛈ",  "ᛉ",  "ᛋ", "ᛏ",  "ᛒ",  "ᛖ", "ᛗ", "ᛚ",
    "ᛜ", "ᛟ",  "ᛞ", "ᚠ",  "ᚦ",  "ᚲᛋ", "ᚷ", "ᛖ",  "ᚲᛋ", "ᚦ", "ᛟ", "ᚺᚱ",
    "ᛜ", "ᚺᛚ", "ᛜ", "ᚺᛃ", "ᛜᚲ", "ᚺᚹ", "ᛋ", "ᛟᛖ", "ᚨᚨ", "ᚲ", NULL};

const char *younger_futhark_tokens[] = {
    "ᚠ", "ᚢ",  "ᚦ", "ᛅ",  "ᚱ",  "ᚴ",  "ᚵ", "ᚷ",  "ᚹ",  "ᚺ", "ᚾ", "ᛁ",
    "ᛡ", "ᛡ",  "ᛇ", "ᛇ",  "ᛈ",  "ᛉ",  "ᛋ", "ᛏ",  "ᛒ",  "ᛖ", "ᛗ", "ᛚ",
    "ᛜ", "ᛟ",  "ᛞ", "ᚠ",  "ᚦ",  "ᚴᛋ", "ᚷ", "ᛖ",  "ᚴᛋ", "ᚦ", "ᛟ", "ᚺᚱ",
    "ᛜ", "ᚺᛚ", "ᛜ", "ᚺᛡ", "ᛜᚴ", "ᚺᚹ", "ᛋ", "ᛟᛖ", "ᚭᚭ", "ᚴ", NULL};

TokenMapper *token_mapper_elder_new() {
  GHashTable *token_map;

  token_map = g_hash_table_new(g_str_hash, g_str_equal);
  if (!token_map) {
    return NULL;
  }

  for (int i = 0; latin_tokens[i] != NULL; i++) {
    g_hash_table_insert(token_map, (gpointer)latin_tokens[i],
                        (gpointer)elder_futhark_tokens[i]);
  }

  TokenMapper *token_mapper = malloc(sizeof(TokenMapper));
  if (!token_mapper) {
    // Handle error if memory allocation fails
    g_hash_table_destroy(token_map);
    return NULL;
  }
  token_mapper->map = token_map;
  return token_mapper;
}

TokenMapper *token_mapper_younger_new() {
  GHashTable *token_map;

  token_map = g_hash_table_new(g_str_hash, g_str_equal);
  if (!token_map) {
    return NULL;
  }

  for (int i = 0; latin_tokens[i] != NULL; i++) {
    g_hash_table_insert(token_map, (gpointer)latin_tokens[i],
                        (gpointer)younger_futhark_tokens[i]);
  }

  TokenMapper *token_mapper = malloc(sizeof(TokenMapper));
  if (!token_mapper) {
    // Handle error if memory allocation fails
    g_hash_table_destroy(token_map);
    return NULL;
  }
  token_mapper->map = token_map;
  return token_mapper;
}

/* This function is used to transliterate a string from Latin characters to
 * Elder Futhark characters. */
char *to_fut(TokenMapper *map, char *input) {
  size_t len = strlen(input);
  char *fut_str = malloc((len * 4) + 1); // 4 because of utf8 expansion
  if (!fut_str) {
    perror("Error allocating memory for output string");
    return NULL;
  }
  fut_str[0] = '\0';

  char *p = input;
  int token_index = 0;
  char *token = malloc(len + 1);
  if (!token) {
    perror("Error allocating memory for token");
    return NULL;
  }

  do {
    if (*p == ' ') {
      strcat(fut_str, " ");
      token[0] = '\0';
      token_index = 0;
      p++;
      continue;
    }

    char c = tolower(*p);
    token[token_index] = c;
    token[token_index + 1] = '\0';

    // if the char is not in the map at all, we dump it and
    // just use the char that is there
    if (!g_hash_table_contains(map->map, token)) {
      strcat(fut_str, token);
      token[0] = '\0';
      token_index = 0;
      p++;
      continue;
    }

    p++;
    token_index++;

    // token next is the token plus one extra char
    char *token_next = malloc(len + 1);
    strcpy(token_next, token);
    token_next[token_index] = tolower(*p);
    token_next[token_index + 1] = '\0';

    if ((g_hash_table_contains(map->map, token) &&
         !g_hash_table_contains(map->map, token_next)) ||
        // if the token and next token are the same, we have hit the end of the
        // input string
        (strcmp(token, token_next) == 0)) {
      char *futhark = g_hash_table_lookup(map->map, token);
      strcat(fut_str, futhark);
      token[token_index] = '\0';
      token[0] = '\0';
      token_index = 0;
    }
  } while (*p != '\0');
  
  free(token);
  return fut_str;
}
