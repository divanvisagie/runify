#include <ctype.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "default.h"

typedef struct {
  const char *latin;
  const char *futhark;
} TokenPair;

const TokenPair elder_futhark_pairs[] = {
    {"a", "ᚨ"},    {"b", "ᛒ"},    {"c", "ᚲ"},  {"d", "ᛞ"},    {"e", "ᛖ"},
    {"f", "ᚠ"},    {"g", "ᚷ"},    {"h", "ᚺ"},  {"i", "ᛁ"},    {"j", "ᛃ"},
    {"k", "ᚲ"},    {"l", "ᛚ"},    {"m", "ᛗ"},  {"n", "ᚾ"},    {"o", "ᛟ"},
    {"p", "ᛈ"},    {"r", "ᚱ"},    {"s", "ᛋ"},  {"t", "ᛏ"},    {"u", "ᚢ"},
    {"v", "ᚠ"},    {"w", "ᚹ"},    {"y", "ᛃ"},  {"z", "ᛉ"},    {"æ", "ᛇ"},
    {"þ", "ᚦ"},    {"ð", "ᚦ"},    {"ŋ", "ᛜ"},  {"x", "ᚲᛋ"},   {"ch", "ᚷ"},
    {"ij", "ᛖ"},   {"cc", "ᚲᛋ"},  {"th", "ᚦ"}, {"eau", "ᛟ"},  {"chr", "ᚺᚱ"},
    {"ing", "ᛜ"},  {"chl", "ᚺᛚ"}, {"ng", "ᛜ"}, {"chj", "ᚺᛃ"}, {"nk", "ᛜᚲ"},
    {"chw", "ᚺᚹ"}, {"ei", "ᛋ"},   {"ø", "ᛟᛖ"}, {"å", "ᚨᚨ"},   {"q", "ᚲ"},
    {"ï", "ᛇ"},    {NULL, NULL}};

const TokenPair younger_futhark_pairs[] = {
    {"a", "ᛅ"},   {"b", "ᛒ"},   {"c", "ᚴ"},  {"d", "ᛏ"},   {"e", "ᛁ"},
    {"f", "ᚠ"},   {"g", "ᚴ"},   {"h", "ᚼ"},  {"i", "ᛁ"},   {"j", "ᛡ"},
    {"k", "ᚴ"},   {"l", "ᛚ"},   {"m", "ᛘ"},  {"n", "ᚾ"},   {"o", "ᚬ"},
    {"p", "ᛒ"},   {"r", "ᚱ"},   {"s", "ᛋ"},  {"t", "ᛏ"},   {"u", "ᚢ"},
    {"v", "ᚢ"},   {"w", "ᚢ"},   {"y", "ᛡ"},  {"z", "ᛋ"},   {"æ", "ᛅ"},
    {"þ", "ᚦ"},   {"ð", "ᚦ"},   {"ŋ", "ᚴ"},  {"x", "ᚴᛋ"},  {"ch", "ᚴ"},
    {"ij", "ᛁ"},  {"cc", "ᚴᛋ"}, {"th", "ᚦ"}, {"eau", "ᚬ"}, {"chr", "ᚼ/ᚽ"},
    {"ing", "ᚴ"}, {"chl", "ᚼ"}, {"ng", "ᚴ"}, {"chj", "ᚼ"}, {"nk", "ᚴ"},
    {"chw", "ᚼ"}, {"ei", "ᛁ"},  {"ø", "ᚬ"},  {"å", "ᚭᚭ"},  {"q", "ᚴ"},
    {"ʀ", "ᛦ"},   {NULL, NULL}};

TokenMapper *token_mapper_new(const TokenPair *pairs) {
  GHashTable *token_map = g_hash_table_new(g_str_hash, g_str_equal);
  if (!token_map) {
    return NULL;
  }

  for (int i = 0; pairs[i].latin != NULL; i++) {
    g_hash_table_insert(token_map, (gpointer)pairs[i].latin,
                        (gpointer)pairs[i].futhark);
  }

  TokenMapper *token_mapper = malloc(sizeof(TokenMapper));
  if (!token_mapper) {
    g_hash_table_destroy(token_map);
    return NULL;
  }
  token_mapper->map = token_map;
  return token_mapper;
}

TokenMapper *token_mapper_elder_new() {
  return token_mapper_new(elder_futhark_pairs);
}

TokenMapper *token_mapper_younger_new() {
  return token_mapper_new(younger_futhark_pairs);
}

void replace_string(char *str, const char *search, const char *replace) {
  char *pos;
  int search_len = strlen(search);
  int replace_len = strlen(replace);

  pos = strstr(str, search);

  while (pos != NULL) {
    memmove(pos + replace_len, pos + search_len, strlen(pos + search_len) + 1);
    memcpy(pos, replace, replace_len);
    pos = strstr(pos + replace_len, search);
  }
}

typedef struct KVP {
  const char *key;
  const char *value;
} KVP;

static int compare_strings_by_length(const void *a, const void *b) {
  // convert to kvp
  KVP *kvp_a = (KVP *)a;
  KVP *kvp_b = (KVP *)a;
  return strlen(kvp_a->key) - strlen(kvp_b->key);
}

char *to_fut(TokenMapper *map, const char *input) {
  char *output = malloc(strlen(input) * 4);
  strcpy(output, input);
  
  // we lowercase the output string since it needs to map against lower case keys
  for (size_t i = 0; i < strlen(output); i++) {
    output[i] = tolower(output[i]);
  }

  KVP *kvps = malloc(sizeof(KVP) * g_hash_table_size(map->map));
  size_t kvp_count = 0;

  // create an ordered list of the key value pairs that makes sure the longest
  // keys are first
  GHashTableIter iter;
  gpointer key, value;
  g_hash_table_iter_init(&iter, map->map);
  while (g_hash_table_iter_next(&iter, &key, &value)) {
    kvps[kvp_count].key = (const char *)key;
    kvps[kvp_count].value = (const char *)value;
    kvp_count++;
  }

  //sort kvp longest to shortest keys
  qsort(kvps, kvp_count, sizeof(KVP), compare_strings_by_length);

  while (kvp_count--) {
    replace_string(output, kvps[kvp_count].key, kvps[kvp_count].value);
  }

  free(kvps);

  return output;
}
