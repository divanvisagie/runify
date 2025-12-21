#include "younger.h"

// Basic Younger Futhark: single character mappings only
static const TokenPair younger_basic[] = {
    {"a", "ᛅ"}, {"b", "ᛒ"}, {"c", "ᚴ"}, {"d", "ᛏ"}, {"e", "ᛁ"},
    {"f", "ᚠ"}, {"g", "ᚴ"}, {"h", "ᚼ"}, {"i", "ᛁ"}, {"j", "ᛡ"},
    {"k", "ᚴ"}, {"l", "ᛚ"}, {"m", "ᛘ"}, {"n", "ᚾ"}, {"o", "ᚬ"},
    {"p", "ᛒ"}, {"r", "ᚱ"}, {"s", "ᛋ"}, {"t", "ᛏ"}, {"u", "ᚢ"},
    {"v", "ᚢ"}, {"w", "ᚢ"}, {"y", "ᛡ"}, {"z", "ᛋ"}, {"q", "ᚴ"},
    {"æ", "ᛅ"}, {"þ", "ᚦ"}, {"ð", "ᚦ"}, {"ŋ", "ᚴ"}, {"ʀ", "ᛦ"},
    {NULL, NULL}};

// Phonetic Younger Futhark: multi-character mappings
static const TokenPair younger_phonetic[] = {
    {"th", "ᚦ"},  {"ng", "ᚴ"},  {"ing", "ᚴ"}, {"nk", "ᚴ"},
    {"ch", "ᚴ"},  {"chr", "ᚼ"}, {"chl", "ᚼ"}, {"chj", "ᚼ"},
    {"chw", "ᚼ"}, {"x", "ᚴᛋ"}, {"cc", "ᚴᛋ"}, {"ij", "ᛁ"},
    {"ei", "ᛁ"},  {"eau", "ᚬ"}, {"ø", "ᚬ"},   {"å", "ᚭᚭ"},
    {NULL, NULL}};

// Full Younger Futhark (basic + phonetic combined)
static const TokenPair younger_combined[] = {
    {"a", "ᛅ"},   {"b", "ᛒ"},   {"c", "ᚴ"},  {"d", "ᛏ"},   {"e", "ᛁ"},
    {"f", "ᚠ"},   {"g", "ᚴ"},   {"h", "ᚼ"},  {"i", "ᛁ"},   {"j", "ᛡ"},
    {"k", "ᚴ"},   {"l", "ᛚ"},   {"m", "ᛘ"},  {"n", "ᚾ"},   {"o", "ᚬ"},
    {"p", "ᛒ"},   {"r", "ᚱ"},   {"s", "ᛋ"},  {"t", "ᛏ"},   {"u", "ᚢ"},
    {"v", "ᚢ"},   {"w", "ᚢ"},   {"y", "ᛡ"},  {"z", "ᛋ"},   {"æ", "ᛅ"},
    {"þ", "ᚦ"},   {"ð", "ᚦ"},   {"ŋ", "ᚴ"},  {"x", "ᚴᛋ"},  {"ch", "ᚴ"},
    {"ij", "ᛁ"},  {"cc", "ᚴᛋ"}, {"th", "ᚦ"}, {"eau", "ᚬ"}, {"chr", "ᚼ"},
    {"ing", "ᚴ"}, {"chl", "ᚼ"}, {"ng", "ᚴ"}, {"chj", "ᚼ"}, {"nk", "ᚴ"},
    {"chw", "ᚼ"}, {"ei", "ᛁ"},  {"ø", "ᚬ"},  {"å", "ᚭᚭ"},  {"q", "ᚴ"},
    {"ʀ", "ᛦ"},   {NULL, NULL}};

const FutharkSystem younger_futhark = {
    .name = "younger",
    .display_name = "Younger Futhark",
    .basic_pairs = younger_basic,
    .phonetic_pairs = younger_phonetic,
    .combined_pairs = younger_combined,
};

void younger_futhark_register(void) {
  futhark_registry_register(&younger_futhark);
}
