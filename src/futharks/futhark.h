#ifndef FUTHARK_H
#define FUTHARK_H

#include <glib.h>
#include <stdbool.h>

// Token pair for mapping latin to futhark runes
typedef struct {
  const char *latin;
  const char *futhark;
} TokenPair;

// Token mapper with bidirectional lookup
typedef struct {
  GHashTable *map;
  GHashTable *reverse_map;
} TokenMapper;

// Futhark system definition - allows registering new futhark variants
typedef struct {
  const char *name;
  const char *display_name;
  const TokenPair *basic_pairs;
  const TokenPair *phonetic_pairs;
  const TokenPair *combined_pairs;
} FutharkSystem;

// Registry functions
void futhark_registry_init(void);
void futhark_registry_register(const FutharkSystem *system);
const FutharkSystem *futhark_registry_get(const char *name);
void futhark_registry_list(void (*callback)(const FutharkSystem *system, void *userdata), void *userdata);
bool futhark_registry_is_valid(const char *name);

// Token mapper functions
TokenMapper *token_mapper_new(const TokenPair *pairs);
TokenMapper *token_mapper_for_system(const char *system_name, bool phonetic);
void token_mapper_free(TokenMapper *mapper);

// Conversion functions
char *to_fut(TokenMapper *map, const char *input);
char *from_fut(TokenMapper *map, const char *input);

#endif // FUTHARK_H
