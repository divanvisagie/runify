#include <stdio.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "src/futharks/futhark.h"

// Helper to get phonetic (combined) mapper
static TokenMapper* token_mapper_elder_new(void) {
  return token_mapper_for_system("elder", true);
}

static TokenMapper* token_mapper_younger_new(void) {
  return token_mapper_for_system("younger", true);
}

static TokenMapper* token_mapper_elder_basic_new(void) {
  return token_mapper_for_system("elder", false);
}

static TokenMapper* token_mapper_younger_basic_new(void) {
  return token_mapper_for_system("younger", false);
}

// =============================================================================
// Elder Futhark Basic Tests (30 mappings)
// =============================================================================

static void test_elder_basic_all_mappings(void **state) {
  TokenMapper* mapper = token_mapper_elder_basic_new();
  assert_non_null(mapper);

  // All 30 basic Elder Futhark mappings
  const char* latin[] = {
    "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
    "k", "l", "m", "n", "o", "p", "r", "s", "t", "u",
    "v", "w", "y", "z", "q", "æ", "þ", "ð", "ŋ", "ï"
  };
  const char* runes[] = {
    "ᚨ", "ᛒ", "ᚲ", "ᛞ", "ᛖ", "ᚠ", "ᚷ", "ᚺ", "ᛁ", "ᛃ",
    "ᚲ", "ᛚ", "ᛗ", "ᚾ", "ᛟ", "ᛈ", "ᚱ", "ᛋ", "ᛏ", "ᚢ",
    "ᚠ", "ᚹ", "ᛃ", "ᛉ", "ᚲ", "ᛇ", "ᚦ", "ᚦ", "ᛜ", "ᛇ"
  };

  for (int i = 0; i < 30; i++) {
    char* actual = to_fut(mapper, latin[i]);
    assert_string_equal(runes[i], actual);
    free(actual);
  }

  token_mapper_free(mapper);
}

// =============================================================================
// Elder Futhark Phonetic Tests (16 mappings)
// =============================================================================

static void test_elder_phonetic_all_mappings(void **state) {
  TokenMapper* mapper = token_mapper_elder_new();
  assert_non_null(mapper);

  // All 16 phonetic Elder Futhark mappings
  const char* latin[] = {
    "th", "ng", "ing", "nk",
    "ch", "chr", "chl", "chj",
    "chw", "x", "cc", "ij",
    "ei", "eau", "ø", "å"
  };
  const char* runes[] = {
    "ᚦ", "ᛜ", "ᛜ", "ᛜᚲ",
    "ᚷ", "ᚺᚱ", "ᚺᛚ", "ᚺᛃ",
    "ᚺᚹ", "ᚲᛋ", "ᚲᛋ", "ᛖ",
    "ᛋ", "ᛟ", "ᛟᛖ", "ᚨᚨ"
  };

  for (int i = 0; i < 16; i++) {
    char* actual = to_fut(mapper, latin[i]);
    assert_string_equal(runes[i], actual);
    free(actual);
  }

  token_mapper_free(mapper);
}

// =============================================================================
// Younger Futhark Basic Tests (30 mappings)
// =============================================================================

static void test_younger_basic_all_mappings(void **state) {
  TokenMapper* mapper = token_mapper_younger_basic_new();
  assert_non_null(mapper);

  // All 30 basic Younger Futhark mappings
  const char* latin[] = {
    "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
    "k", "l", "m", "n", "o", "p", "r", "s", "t", "u",
    "v", "w", "y", "z", "q", "æ", "þ", "ð", "ŋ", "ʀ"
  };
  const char* runes[] = {
    "ᛅ", "ᛒ", "ᚴ", "ᛏ", "ᛁ", "ᚠ", "ᚴ", "ᚼ", "ᛁ", "ᛡ",
    "ᚴ", "ᛚ", "ᛘ", "ᚾ", "ᚬ", "ᛒ", "ᚱ", "ᛋ", "ᛏ", "ᚢ",
    "ᚢ", "ᚢ", "ᛡ", "ᛋ", "ᚴ", "ᛅ", "ᚦ", "ᚦ", "ᚴ", "ᛦ"
  };

  for (int i = 0; i < 30; i++) {
    char* actual = to_fut(mapper, latin[i]);
    assert_string_equal(runes[i], actual);
    free(actual);
  }

  token_mapper_free(mapper);
}

// =============================================================================
// Younger Futhark Phonetic Tests (16 mappings)
// =============================================================================

static void test_younger_phonetic_all_mappings(void **state) {
  TokenMapper* mapper = token_mapper_younger_new();
  assert_non_null(mapper);

  // All 16 phonetic Younger Futhark mappings
  const char* latin[] = {
    "th", "ng", "ing", "nk",
    "ch", "chr", "chl", "chj",
    "chw", "x", "cc", "ij",
    "ei", "eau", "ø", "å"
  };
  const char* runes[] = {
    "ᚦ", "ᚴ", "ᚴ", "ᚴ",
    "ᚴ", "ᚼ", "ᚼ", "ᚼ",
    "ᚼ", "ᚴᛋ", "ᚴᛋ", "ᛁ",
    "ᛁ", "ᚬ", "ᚬ", "ᚭᚭ"
  };

  for (int i = 0; i < 16; i++) {
    char* actual = to_fut(mapper, latin[i]);
    assert_string_equal(runes[i], actual);
    free(actual);
  }

  token_mapper_free(mapper);
}

// =============================================================================
// Integration / Word Tests
// =============================================================================

static void test_elder_word_futhark(void **state) {
  TokenMapper* mapper = token_mapper_elder_new();
  assert_non_null(mapper);

  char* actual = to_fut(mapper, "futhark");
  assert_string_equal("ᚠᚢᚦᚨᚱᚲ", actual);
  free(actual);

  token_mapper_free(mapper);
}

static void test_elder_word_hello_world(void **state) {
  TokenMapper* mapper = token_mapper_elder_new();
  assert_non_null(mapper);

  char* actual = to_fut(mapper, "hello world");
  assert_string_equal("ᚺᛖᛚᛚᛟ ᚹᛟᚱᛚᛞ", actual);
  free(actual);

  token_mapper_free(mapper);
}

static void test_younger_word_aifur(void **state) {
  TokenMapper* mapper = token_mapper_younger_new();
  assert_non_null(mapper);

  char* actual = to_fut(mapper, "aifur");
  assert_string_equal("ᛅᛁᚠᚢᚱ", actual);
  free(actual);

  token_mapper_free(mapper);
}

static void test_non_supported_tokens_preserved(void **state) {
  TokenMapper* mapper = token_mapper_elder_new();
  assert_non_null(mapper);

  char* actual = to_fut(mapper, "futhark!\n");
  assert_string_equal("ᚠᚢᚦᚨᚱᚲ!\n", actual);
  free(actual);

  token_mapper_free(mapper);
}

// =============================================================================
// Phonetic vs Non-Phonetic Mode Tests
// =============================================================================

static void test_elder_phonetic_th_combined(void **state) {
  TokenMapper* mapper = token_mapper_elder_new();
  assert_non_null(mapper);

  // Phonetic mode: "th" becomes single rune ᚦ
  char* actual = to_fut(mapper, "th");
  assert_string_equal("ᚦ", actual);
  free(actual);

  token_mapper_free(mapper);
}

static void test_elder_basic_th_separate(void **state) {
  TokenMapper* mapper = token_mapper_elder_basic_new();
  assert_non_null(mapper);

  // Non-phonetic mode: "th" becomes two runes ᛏᚺ
  char* actual = to_fut(mapper, "th");
  assert_string_equal("ᛏᚺ", actual);
  free(actual);

  token_mapper_free(mapper);
}

static void test_younger_phonetic_ng_combined(void **state) {
  TokenMapper* mapper = token_mapper_younger_new();
  assert_non_null(mapper);

  // Phonetic mode: "ng" becomes ᚴ
  char* actual = to_fut(mapper, "ng");
  assert_string_equal("ᚴ", actual);
  free(actual);

  token_mapper_free(mapper);
}

static void test_younger_basic_ng_separate(void **state) {
  TokenMapper* mapper = token_mapper_younger_basic_new();
  assert_non_null(mapper);

  // Non-phonetic mode: "ng" becomes two runes ᚾᚴ
  char* actual = to_fut(mapper, "ng");
  assert_string_equal("ᚾᚴ", actual);
  free(actual);

  token_mapper_free(mapper);
}

// =============================================================================
// Main
// =============================================================================

int main(int argc, char *argv[]) {
  futhark_registry_init();

  const struct CMUnitTest tests[] = {
      // Full coverage tests
      cmocka_unit_test(test_elder_basic_all_mappings),
      cmocka_unit_test(test_elder_phonetic_all_mappings),
      cmocka_unit_test(test_younger_basic_all_mappings),
      cmocka_unit_test(test_younger_phonetic_all_mappings),

      // Word integration tests
      cmocka_unit_test(test_elder_word_futhark),
      cmocka_unit_test(test_elder_word_hello_world),
      cmocka_unit_test(test_younger_word_aifur),
      cmocka_unit_test(test_non_supported_tokens_preserved),

      // Phonetic vs non-phonetic mode
      cmocka_unit_test(test_elder_phonetic_th_combined),
      cmocka_unit_test(test_elder_basic_th_separate),
      cmocka_unit_test(test_younger_phonetic_ng_combined),
      cmocka_unit_test(test_younger_basic_ng_separate),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
