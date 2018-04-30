package main

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

	"th":  thurisaz,
	"eau": othala,
	"chr": hagalaz + raido,
	"ing": ingwaz,
	"chl": hagalaz + laguz,
	"ng":  ingwaz,
	"chj": hagalaz + jera,
	"nk":  ingwaz + kaunan,
	"chw": hagalaz + wunjo,
	"ei":  sowilo,
	"ø":   othala + ehwaz,
	"å":   ansuz + ansuz,

	"q": kaunan,
}
