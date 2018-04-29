package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

const (
	fehu     = "ᚠ"
	uruz     = "ᚢ"
	thurisaz = "ᚦ"
	ansuz    = "ᚨ"
	raido    = "ᚱ"
	kaunan   = "ᚲ"
	gebo     = "ᚷ"
	wunjo    = "ᚹ"
	hagalaz  = "ᚺ"
	naudiz   = "ᚾ"
	isaz     = "ᛁ"
	jera     = "ᛃ"
	eihwaz   = "ᛇ"
	perth    = "ᛈ"
	algiz    = "ᛉ"
	sowilo   = "ᛋ"
	tiwaz    = "ᛏ"
	berkanan = "ᛒ"
	ehwaz    = "ᛖ"
	mannaz   = "ᛗ"
	laguz    = "ᛚ"
	ingwaz   = "ᛜ"
	othala   = "ᛟ"
	dagaz    = "ᛞ"
)

var futharkMap = map[string]string{
	"f": fehu,
	"u": uruz,
	"þ": thurisaz,
	"a": ansuz,
	"r": raido,
	"k": kaunan,
	"c": kaunan,
	"g": gebo,
	"w": wunjo,
	"h": hagalaz,
	"n": naudiz,
	"i": isaz,
	"j": jera,
	"y": jera,
	"æ": eihwaz,
	"ï": eihwaz,
	"p": perth,
	"z": algiz,
	"s": sowilo,
	"t": tiwaz,
	"b": berkanan,
	"e": ehwaz,
	"m": mannaz,
	"l": laguz,
	"ŋ": ingwaz,
	"o": othala,
	"d": dagaz,
	"v": fehu,
	"ð": thurisaz,
	"x": kaunan + sowilo,

	"ch": gebo,
	"ij": ehwaz,
	"cc": kaunan + sowilo,

	"q": kaunan,
}

type LongerFirst []string

func (a LongerFirst) Len() int {
	return len(a)
}

func (a LongerFirst) Less(i, j int) bool {
	return len(a[i]) > len(a[j])
}

func (a LongerFirst) Swap(i, j int) {
	a[i], a[j] = a[j], a[i]
}

func supportedLetters() []string {
	keys := make([]string, len(futharkMap))
	for k := range futharkMap {
		keys = append(keys, k)
	}
	sort.Sort(LongerFirst(keys))
	return keys
}

func translate(inputString string) string {
	var result = strings.ToLower(inputString)
	var supportedLetters = supportedLetters()
	for _, letter := range supportedLetters {
		result = strings.Replace(result, letter, futharkMap[letter], -1)
	}
	return result
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		var toConvert = scanner.Text()
		var translated = translate(toConvert)
		fmt.Println(translated)
	}

}
