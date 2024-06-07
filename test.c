#include <stdio.h>
// Including setjmp.h because it's required indirectly by CMocka for certain
// macros/longjmp operations.
#include <setjmp.h>
#include <cmocka.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "default.h"

static void test_to_futhark(void **state) {
  TokenMapper* tokenMapper = token_mapper_new();
  assert_non_null(tokenMapper);
  char* actual = to_fut(tokenMapper, "futhark");
  assert_string_equal("ᚠᚢᚦᚨᚱᚲ", actual);
  
  free(tokenMapper);
}

static void test_map_loaded_correctly(void **state) {
  TokenMapper* tokenMapper = token_mapper_new();
  assert_non_null(tokenMapper);
  
  assert_non_null(tokenMapper->map);
  char* actual = g_hash_table_lookup(tokenMapper->map, "f");
  assert_string_equal("ᚠ", actual);

  free(tokenMapper);
}

// Group all test cases together
int main(int argc, char *argv[]) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_map_loaded_correctly),
      cmocka_unit_test(test_to_futhark),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
