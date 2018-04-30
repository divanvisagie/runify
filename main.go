package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

/*
LongerFirst - Sorting type that sorts an array of strings by putting
the longest strings first
*/
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
