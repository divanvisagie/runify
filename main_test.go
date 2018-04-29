package main

import "testing"
import "github.com/stretchr/testify/assert"

func TestWords(t *testing.T) {
	assert.Equal(t, "ᚠᚢᚦᚨᚱᚲ", translate("Futhark"))
	assert.Equal(t, "ᚠᚢᚦᚨᚱᚲ", translate("futhark"))
	assert.Equal(t, "ᛇᛋᛁᚱ", translate("Æsir"))
}

func TestLatinAlphabet(t *testing.T) {
	assert.Equal(t, "ᚨ", translate("A"))
	assert.Equal(t, "ᛒ", translate("B"))
	assert.Equal(t, "ᚲ", translate("C"))
	assert.Equal(t, "ᛞ", translate("D"))
	assert.Equal(t, "ᛖ", translate("E"))
	assert.Equal(t, "ᚠ", translate("F"))
	assert.Equal(t, "ᚷ", translate("G"))
	assert.Equal(t, "ᚺ", translate("H"))
	assert.Equal(t, "ᛁ", translate("I"))
	assert.Equal(t, "ᛃ", translate("J"))
	assert.Equal(t, "ᚲ", translate("K"))
	assert.Equal(t, "ᛚ", translate("L"))
	assert.Equal(t, "ᛗ", translate("M"))
	assert.Equal(t, "ᚾ", translate("N"))
	assert.Equal(t, "ᛟ", translate("O"))
	assert.Equal(t, "ᛈ", translate("P"))
	assert.Equal(t, "ᚲ", translate("Q"))
	assert.Equal(t, "ᚱ", translate("R"))
	assert.Equal(t, "ᛋ", translate("S"))
	assert.Equal(t, "ᛏ", translate("T"))
	assert.Equal(t, "ᚢ", translate("U"))
	assert.Equal(t, "ᚠ", translate("V"))
	assert.Equal(t, "ᚹ", translate("W"))
	assert.Equal(t, "ᚲᛋ", translate("X"))
	assert.Equal(t, "ᛃ", translate("Y"))
	assert.Equal(t, "ᛉ", translate("z"))

}
