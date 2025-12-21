#include "futhark.h"
#include "elder.h"
#include "younger.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Simple linked list for registered futharks
typedef struct FutharkNode {
  const FutharkSystem *system;
  struct FutharkNode *next;
} FutharkNode;

static FutharkNode *registry_head = NULL;
static bool registry_initialized = false;

void futhark_registry_register(const FutharkSystem *system) {
  FutharkNode *node = malloc(sizeof(FutharkNode));
  node->system = system;
  node->next = registry_head;
  registry_head = node;
}

const FutharkSystem *futhark_registry_get(const char *name) {
  for (FutharkNode *node = registry_head; node != NULL; node = node->next) {
    if (strcmp(node->system->name, name) == 0) {
      return node->system;
    }
  }
  return NULL;
}

void futhark_registry_list(void (*callback)(const FutharkSystem *system, void *userdata), void *userdata) {
  for (FutharkNode *node = registry_head; node != NULL; node = node->next) {
    callback(node->system, userdata);
  }
}

bool futhark_registry_is_valid(const char *name) {
  return futhark_registry_get(name) != NULL;
}

void futhark_registry_init(void) {
  if (registry_initialized) {
    return;
  }

  // Register all built-in futharks
  elder_futhark_register();
  younger_futhark_register();

  registry_initialized = true;
}

// Token mapper implementation
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

TokenMapper *token_mapper_for_system(const char *system_name, bool phonetic) {
  const FutharkSystem *system = futhark_registry_get(system_name);
  if (!system) {
    return NULL;
  }

  // Use combined pairs if phonetic, basic pairs otherwise
  const TokenPair *pairs = phonetic ? system->combined_pairs : system->basic_pairs;
  return token_mapper_new(pairs);
}

void token_mapper_free(TokenMapper *mapper) {
  if (mapper) {
    if (mapper->map) {
      g_hash_table_destroy(mapper->map);
    }
    if (mapper->reverse_map) {
      g_hash_table_destroy(mapper->reverse_map);
    }
    free(mapper);
  }
}

// String replacement helper
static void replace_string(char *str, const char *search, const char *replace) {
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

typedef struct {
  const char *key;
  const char *value;
} KVP;

static int compare_strings_by_length(const void *a, const void *b) {
  KVP *kvp_a = (KVP *)a;
  KVP *kvp_b = (KVP *)b;
  return strlen(kvp_a->key) - strlen(kvp_b->key);
}

char *to_fut(TokenMapper *map, const char *input) {
  char *output = malloc(strlen(input) * 4);
  strcpy(output, input);

  // Lowercase the output string since it needs to map against lower case keys
  for (size_t i = 0; i < strlen(output); i++) {
    output[i] = tolower(output[i]);
  }

  KVP *kvps = malloc(sizeof(KVP) * g_hash_table_size(map->map));
  size_t kvp_count = 0;

  // Create an ordered list of the key value pairs that makes sure the longest
  // keys are first
  GHashTableIter iter;
  gpointer key, value;
  g_hash_table_iter_init(&iter, map->map);
  while (g_hash_table_iter_next(&iter, &key, &value)) {
    kvps[kvp_count].key = (const char *)key;
    kvps[kvp_count].value = (const char *)value;
    kvp_count++;
  }

  // Sort kvp longest to shortest keys
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
