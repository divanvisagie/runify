#include <glib.h>

typedef struct {
  GHashTable *map;
} TokenMapper;
TokenMapper *token_mapper_elder_new();
TokenMapper *token_mapper_younger_new();
char *to_fut(TokenMapper *map, char *str);
