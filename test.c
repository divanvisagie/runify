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

// Test reverse translation (runes to Latin)
// Note: reverse mapping uses first Latin char for each rune
// (ᚦ→þ not th, ᚲ→c not k, since "c" appears before "k" in pairs)
static void test_from_elder_futhark(void **state) {
  TokenMapper* tokenMapper = token_mapper_elder_new();
  assert_non_null(tokenMapper);

  char* actual = from_fut(tokenMapper, "ᚺᛖᛚᛚᛟ");
  assert_string_equal("hello", actual);

  // ᚠᚢᚦᚨᚱᚲ reverses to "fuþarc" (þ not th, c not k)
  char* actual2 = from_fut(tokenMapper, "ᚠᚢᚦᚨᚱᚲ");
  assert_string_equal("fuþarc", actual2);
}

// Test reverse translation with Younger Futhark
// Note: in Younger Futhark, both 'e' and 'i' map to ᛁ
// Reverse picks 'e' since it appears first in the pairs
static void test_from_younger_futhark(void **state) {
  TokenMapper* tokenMapper = token_mapper_younger_new();
  assert_non_null(tokenMapper);

  // ᛅᛁᚠᚢᚱ reverses to "aefur" (ᛁ→e since e appears before i)
  char* actual = from_fut(tokenMapper, "ᛅᛁᚠᚢᚱ");
  assert_string_equal("aefur", actual);
}

// Test basic (non-phonetic) mapper
static void test_elder_basic_no_phonetic(void **state) {
  TokenMapper* tokenMapper = token_mapper_elder_basic_new();
  assert_non_null(tokenMapper);

  // With basic mapper, "th" should become ᛏᚺ (two runes), not ᚦ (one rune)
  char* actual = to_fut(tokenMapper, "th");
  assert_string_equal("ᛏᚺ", actual);
}

// Test roundtrip (Latin -> Runes -> Latin)
static void test_roundtrip_elder(void **state) {
  TokenMapper* tokenMapper = token_mapper_elder_new();
  assert_non_null(tokenMapper);

  // Simple words should roundtrip
  char* runes = to_fut(tokenMapper, "hello");
  char* back = from_fut(tokenMapper, runes);
  assert_string_equal("hello", back);
}

// Group all test cases together
int main(int argc, char *argv[]) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_map_loaded_correctly),
      cmocka_unit_test(test_to_younger_futhark),
      cmocka_unit_test(test_non_supported_token),
      cmocka_unit_test(test_to_elder_futhark),
      cmocka_unit_test(test_test_full_elder_futhark),
      cmocka_unit_test(test_from_elder_futhark),
      cmocka_unit_test(test_from_younger_futhark),
      cmocka_unit_test(test_elder_basic_no_phonetic),
      cmocka_unit_test(test_roundtrip_elder),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
