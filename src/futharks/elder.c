#include "elder.h"

// Basic Elder Futhark: single character mappings only
static const TokenPair elder_basic[] = {
    {"a", "ᚨ"}, {"b", "ᛒ"}, {"c", "ᚲ"}, {"d", "ᛞ"}, {"e", "ᛖ"},
    {"f", "ᚠ"}, {"g", "ᚷ"}, {"h", "ᚺ"}, {"i", "ᛁ"}, {"j", "ᛃ"},
    {"k", "ᚲ"}, {"l", "ᛚ"}, {"m", "ᛗ"}, {"n", "ᚾ"}, {"o", "ᛟ"},
    {"p", "ᛈ"}, {"r", "ᚱ"}, {"s", "ᛋ"}, {"t", "ᛏ"}, {"u", "ᚢ"},
    {"v", "ᚠ"}, {"w", "ᚹ"}, {"y", "ᛃ"}, {"z", "ᛉ"}, {"q", "ᚲ"},
    {"æ", "ᛇ"}, {"þ", "ᚦ"}, {"ð", "ᚦ"}, {"ŋ", "ᛜ"}, {"ï", "ᛇ"},
    {NULL, NULL}};

// Phonetic Elder Futhark: multi-character mappings
static const TokenPair elder_phonetic[] = {
    {"th", "ᚦ"},   {"ng", "ᛜ"},   {"ing", "ᛜ"},  {"nk", "ᛜᚲ"},
    {"ch", "ᚷ"},   {"chr", "ᚺᚱ"}, {"chl", "ᚺᛚ"}, {"chj", "ᚺᛃ"},
    {"chw", "ᚺᚹ"}, {"x", "ᚲᛋ"},   {"cc", "ᚲᛋ"},  {"ij", "ᛖ"},
    {"ei", "ᛋ"},   {"eau", "ᛟ"},  {"ø", "ᛟᛖ"},   {"å", "ᚨᚨ"},
    {NULL, NULL}};

// Full Elder Futhark (basic + phonetic combined)
static const TokenPair elder_combined[] = {
    {"a", "ᚨ"},    {"b", "ᛒ"},    {"c", "ᚲ"},  {"d", "ᛞ"},    {"e", "ᛖ"},
    {"f", "ᚠ"},    {"g", "ᚷ"},    {"h", "ᚺ"},  {"i", "ᛁ"},    {"j", "ᛃ"},
    {"k", "ᚲ"},    {"l", "ᛚ"},    {"m", "ᛗ"},  {"n", "ᚾ"},    {"o", "ᛟ"},
    {"p", "ᛈ"},    {"r", "ᚱ"},    {"s", "ᛋ"},  {"t", "ᛏ"},    {"u", "ᚢ"},
    {"v", "ᚠ"},    {"w", "ᚹ"},    {"y", "ᛃ"},  {"z", "ᛉ"},    {"æ", "ᛇ"},
    {"þ", "ᚦ"},    {"ð", "ᚦ"},    {"ŋ", "ᛜ"},  {"x", "ᚲᛋ"},   {"ch", "ᚷ"},
    {"ij", "ᛖ"},   {"cc", "ᚲᛋ"},  {"th", "ᚦ"}, {"eau", "ᛟ"},  {"chr", "ᚺᚱ"},
    {"ing", "ᛜ"},  {"chl", "ᚺᛚ"}, {"ng", "ᛜ"}, {"chj", "ᚺᛃ"}, {"nk", "ᛜᚲ"},
    {"chw", "ᚺᚹ"}, {"ei", "ᛋ"},   {"ø", "ᛟᛖ"}, {"å", "ᚨᚨ"},   {"q", "ᚲ"},
    {"ï", "ᛇ"},    {NULL, NULL}};

const FutharkSystem elder_futhark = {
    .name = "elder",
    .display_name = "Elder Futhark",
    .basic_pairs = elder_basic,
    .phonetic_pairs = elder_phonetic,
    .combined_pairs = elder_combined,
};

void elder_futhark_register(void) {
  futhark_registry_register(&elder_futhark);
}
