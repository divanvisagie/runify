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
  
}

static void test_non_supported_token(void **state) {
  TokenMapper* tokenMapper = token_mapper_elder_new();
  assert_non_null(tokenMapper);
  char* actual = to_fut(tokenMapper, "futhark!\n");
  assert_string_equal("ᚠᚢᚦᚨᚱᚲ!\n", actual);
  
}

static void test_to_younger_futhark(void **state) {
  TokenMapper* tokenMapper = token_mapper_younger_new();
  assert_non_null(tokenMapper);
  char* actual = to_fut(tokenMapper, "aifur");
  assert_string_equal("ᛅᛁᚠᚢᚱ", actual);
  
  // free(tokenMapper);
}

static void test_map_loaded_correctly(void **state) {
  TokenMapper* tokenMapper = token_mapper_elder_new();
  assert_non_null(tokenMapper);
  
  assert_non_null(tokenMapper->map);
  char* actual = g_hash_table_lookup(tokenMapper->map, "f");
  assert_string_equal("ᚠ", actual);

  // free(tokenMapper);
}

// [ᚠ]	ᚢ	ᚦ	ᚨ	ᚱ	ᚲ	ᚷ	[ᚹ]	ᚺ	ᚾ	ᛁ	ᛃ	ᛈ	ᛇ	ᛉ	ᛊ	ᛏ	ᛒ	ᛖ	ᛗ	ᛚ	ᛜ	ᛞ	ᛟ
// [f]	u	þ	a	r	k	g	[w]	h	n	i	j	p	ï	z	s	t	b	e	m	l	ŋ	d	o
static void test_test_full_elder_futhark(void **state) {
  TokenMapper* tokenMapper = token_mapper_elder_new();
  assert_non_null(tokenMapper);

  char* full_futhark_latin[] = {
    "f", "u", "th", "a", "r", "k" , "g"
  };

  char* full_futhark[] = {
    "ᚠ", "ᚢ", "ᚦ", "ᚨ", "ᚱ", "ᚲ", "ᚷ"
  };

  for (int i = 0; i < 3; i++) {
    char* actual = to_fut(tokenMapper, full_futhark_latin[i]);
    assert_string_equal(full_futhark[i], actual);
  }

}

static void test_string_replacer(void **state) {
  char* actual = replace_in_string_with("futhark", "f", "M");
  assert_string_equal("Muthark", actual);
  free(actual);
}

// Group all test cases together
int main(int argc, char *argv[]) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_map_loaded_correctly),
      cmocka_unit_test(test_to_younger_futhark),
      cmocka_unit_test(test_non_supported_token),
      cmocka_unit_test(test_to_elder_futhark),
      cmocka_unit_test(test_test_full_elder_futhark),
      cmocka_unit_test(test_string_replacer),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
