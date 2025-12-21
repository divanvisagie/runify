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

// Basic Elder Futhark: single character mappings only
const TokenPair elder_futhark_basic[] = {
    {"a", "ᚨ"}, {"b", "ᛒ"}, {"c", "ᚲ"}, {"d", "ᛞ"}, {"e", "ᛖ"},
    {"f", "ᚠ"}, {"g", "ᚷ"}, {"h", "ᚺ"}, {"i", "ᛁ"}, {"j", "ᛃ"},
    {"k", "ᚲ"}, {"l", "ᛚ"}, {"m", "ᛗ"}, {"n", "ᚾ"}, {"o", "ᛟ"},
    {"p", "ᛈ"}, {"r", "ᚱ"}, {"s", "ᛋ"}, {"t", "ᛏ"}, {"u", "ᚢ"},
    {"v", "ᚠ"}, {"w", "ᚹ"}, {"y", "ᛃ"}, {"z", "ᛉ"}, {"q", "ᚲ"},
    {"æ", "ᛇ"}, {"þ", "ᚦ"}, {"ð", "ᚦ"}, {"ŋ", "ᛜ"}, {"ï", "ᛇ"},
    {NULL, NULL}};

// Phonetic Elder Futhark: multi-character mappings
const TokenPair elder_futhark_phonetic[] = {
    {"th", "ᚦ"},   {"ng", "ᛜ"},   {"ing", "ᛜ"},  {"nk", "ᛜᚲ"},
    {"ch", "ᚷ"},   {"chr", "ᚺᚱ"}, {"chl", "ᚺᛚ"}, {"chj", "ᚺᛃ"},
    {"chw", "ᚺᚹ"}, {"x", "ᚲᛋ"},   {"cc", "ᚲᛋ"},  {"ij", "ᛖ"},
    {"ei", "ᛋ"},   {"eau", "ᛟ"},  {"ø", "ᛟᛖ"},   {"å", "ᚨᚨ"},
    {NULL, NULL}};

// Full Elder Futhark (basic + phonetic combined for backwards compat)
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

// Basic Younger Futhark
const TokenPair younger_futhark_basic[] = {
    {"a", "ᛅ"}, {"b", "ᛒ"}, {"c", "ᚴ"}, {"d", "ᛏ"}, {"e", "ᛁ"},
    {"f", "ᚠ"}, {"g", "ᚴ"}, {"h", "ᚼ"}, {"i", "ᛁ"}, {"j", "ᛡ"},
    {"k", "ᚴ"}, {"l", "ᛚ"}, {"m", "ᛘ"}, {"n", "ᚾ"}, {"o", "ᚬ"},
    {"p", "ᛒ"}, {"r", "ᚱ"}, {"s", "ᛋ"}, {"t", "ᛏ"}, {"u", "ᚢ"},
    {"v", "ᚢ"}, {"w", "ᚢ"}, {"y", "ᛡ"}, {"z", "ᛋ"}, {"q", "ᚴ"},
    {"æ", "ᛅ"}, {"þ", "ᚦ"}, {"ð", "ᚦ"}, {"ŋ", "ᚴ"}, {"ʀ", "ᛦ"},
    {NULL, NULL}};

// Phonetic Younger Futhark
const TokenPair younger_futhark_phonetic[] = {
    {"th", "ᚦ"},  {"ng", "ᚴ"},  {"ing", "ᚴ"}, {"nk", "ᚴ"},
    {"ch", "ᚴ"},  {"chr", "ᚼ"}, {"chl", "ᚼ"}, {"chj", "ᚼ"},
    {"chw", "ᚼ"}, {"x", "ᚴᛋ"}, {"cc", "ᚴᛋ"}, {"ij", "ᛁ"},
    {"ei", "ᛁ"},  {"eau", "ᚬ"}, {"ø", "ᚬ"},   {"å", "ᚭᚭ"},
    {NULL, NULL}};

// Full Younger Futhark (backwards compat)
const TokenPair younger_futhark_pairs[] = {
    {"a", "ᛅ"},   {"b", "ᛒ"},   {"c", "ᚴ"},  {"d", "ᛏ"},   {"e", "ᛁ"},
    {"f", "ᚠ"},   {"g", "ᚴ"},   {"h", "ᚼ"},  {"i", "ᛁ"},   {"j", "ᛡ"},
    {"k", "ᚴ"},   {"l", "ᛚ"},   {"m", "ᛘ"},  {"n", "ᚾ"},   {"o", "ᚬ"},
    {"p", "ᛒ"},   {"r", "ᚱ"},   {"s", "ᛋ"},  {"t", "ᛏ"},   {"u", "ᚢ"},
    {"v", "ᚢ"},   {"w", "ᚢ"},   {"y", "ᛡ"},  {"z", "ᛋ"},   {"æ", "ᛅ"},
    {"þ", "ᚦ"},   {"ð", "ᚦ"},   {"ŋ", "ᚴ"},  {"x", "ᚴᛋ"},  {"ch", "ᚴ"},
    {"ij", "ᛁ"},  {"cc", "ᚴᛋ"}, {"th", "ᚦ"}, {"eau", "ᚬ"}, {"chr", "ᚼ"},
    {"ing", "ᚴ"}, {"chl", "ᚼ"}, {"ng", "ᚴ"}, {"chj", "ᚼ"}, {"nk", "ᚴ"},
    {"chw", "ᚼ"}, {"ei", "ᛁ"},  {"ø", "ᚬ"},  {"å", "ᚭᚭ"},  {"q", "ᚴ"},
    {"ʀ", "ᛦ"},   {NULL, NULL}};

TokenMapper *token_mapper_new(const TokenPair *pairs) {
  GHashTable *token_map = g_hash_table_new(g_str_hash, g_str_equal);
  GHashTable *reverse_map = g_hash_table_new(g_str_hash, g_str_equal);
  if (!token_map || !reverse_map) {
    return NULL;
  }

  for (int i = 0; pairs[i].latin != NULL; i++) {
    g_hash_table_insert(token_map, (gpointer)pairs[i].latin,
                        (gpointer)pairs[i].futhark);
    // For reverse mapping, only insert if not already present
    // (first latin value wins for ambiguous runes like ᚲ -> k, not c or q)
    if (!g_hash_table_contains(reverse_map, pairs[i].futhark)) {
      g_hash_table_insert(reverse_map, (gpointer)pairs[i].futhark,
                          (gpointer)pairs[i].latin);
    }
  }

  TokenMapper *token_mapper = malloc(sizeof(TokenMapper));
  if (!token_mapper) {
    g_hash_table_destroy(token_map);
    g_hash_table_destroy(reverse_map);
    return NULL;
  }
  token_mapper->map = token_map;
  token_mapper->reverse_map = reverse_map;
  return token_mapper;
}

TokenMapper *token_mapper_elder_new() {
  return token_mapper_new(elder_futhark_pairs);
}

TokenMapper *token_mapper_younger_new() {
  return token_mapper_new(younger_futhark_pairs);
}

TokenMapper *token_mapper_elder_basic_new() {
  return token_mapper_new(elder_futhark_basic);
}

TokenMapper *token_mapper_younger_basic_new() {
  return token_mapper_new(younger_futhark_basic);
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

char *from_fut(TokenMapper *map, const char *input) {
  // Allocate enough space - runes are multi-byte but latin is single byte
  char *output = malloc(strlen(input) + 1);
  strcpy(output, input);

  KVP *kvps = malloc(sizeof(KVP) * g_hash_table_size(map->reverse_map));
  size_t kvp_count = 0;

  // Build list of rune->latin pairs, sorted by rune length (longest first)
  GHashTableIter iter;
  gpointer key, value;
  g_hash_table_iter_init(&iter, map->reverse_map);
  while (g_hash_table_iter_next(&iter, &key, &value)) {
    kvps[kvp_count].key = (const char *)key;
    kvps[kvp_count].value = (const char *)value;
    kvp_count++;
  }

  // Sort by key length (longest first) to handle composite runes first
  qsort(kvps, kvp_count, sizeof(KVP), compare_strings_by_length);

  while (kvp_count--) {
    replace_string(output, kvps[kvp_count].key, kvps[kvp_count].value);
  }

  free(kvps);

  return output;
}
