#include <glib.h>
#include <stdbool.h>

typedef struct {
  GHashTable *map;
  GHashTable *reverse_map;
} TokenMapper;

TokenMapper *token_mapper_elder_new();
TokenMapper *token_mapper_younger_new();
TokenMapper *token_mapper_elder_basic_new();
TokenMapper *token_mapper_younger_basic_new();

char *to_fut(TokenMapper *map, const char *input);
char *from_fut(TokenMapper *map, const char *input);
