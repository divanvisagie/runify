#include <glib.h>

typedef struct {
  GHashTable *map;
} TokenMapper;

TokenMapper *token_mapper_elder_new();
TokenMapper *token_mapper_younger_new();

char *replace_in_string_with(const char *input, const char *search,
                             const char *replace);

char *to_fut(TokenMapper *map, const char *input);
