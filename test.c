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

static void test_to_elder_futhark(void **state) {
  TokenMapper* tokenMapper = token_mapper_elder_new();
  assert_non_null(tokenMapper);
  char* actual = to_fut(tokenMapper, "futhark");
  assert_string_equal("ᚠᚢᚦᚨᚱᚲ", actual);

  char* actual2 = to_fut(tokenMapper, "hello world");
  assert_string_equal("ᚺᛖᛚᛚᛟ ᚹᛟᚱᛚᛞ", actual2);
  
  free(tokenMapper);
}

static void test_non_supported_token(void **state) {
  TokenMapper* tokenMapper = token_mapper_elder_new();
  assert_non_null(tokenMapper);
  char* actual = to_fut(tokenMapper, "futhark!");
  assert_string_equal("ᚠᚢᚦᚨᚱᚲ!", actual);
  
  free(tokenMapper);
}

static void test_to_younger_futhark(void **state) {
  TokenMapper* tokenMapper = token_mapper_younger_new();
  assert_non_null(tokenMapper);
  char* actual = to_fut(tokenMapper, "aifur");
  assert_string_equal("ᛅᛁᚠᚢᚱ", actual);
  
  free(tokenMapper);
}

static void test_map_loaded_correctly(void **state) {
  TokenMapper* tokenMapper = token_mapper_elder_new();
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
      cmocka_unit_test(test_to_younger_futhark),
      cmocka_unit_test(test_non_supported_token),
      cmocka_unit_test(test_to_elder_futhark),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
