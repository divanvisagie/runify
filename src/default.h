#include <glib.h>

typedef struct {
  GHashTable *map;
} TokenMapper;
TokenMapper *token_mapper_new();
char *to_fut(TokenMapper *map, char *str);
