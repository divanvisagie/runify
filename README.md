# ᚱᚢᚾᛁᚠᛃ (runify)

## Description

Converts text between Latin characters and Futhark runes. Supports both Elder Futhark (24 runes) and Younger Futhark (16 runes) systems.

![ScreenShot 1](docs/1.png)

You can even pipe it through lolcat for color
![ScreenShot 2](docs/2.png)

## Features

- **Multiple rune systems**: Elder Futhark and Younger Futhark
- **Phonetic mode**: Automatically converts digraphs like "th" → ᚦ, "ng" → ᛜ
- **Non-phonetic mode**: Letter-by-letter conversion when needed

## Usage

```sh
# Latin to Elder Futhark
echo "hello world" | runify -s elder
# Output: ᚺᛖᛚᛚᛟ ᚹᛟᚱᛚᛞ

# Younger Futhark (default)
echo "viking" | runify
# Output: ᚢᛁᚴᛁᚾᚴ

# Phonetic mode (default) - digraphs become single runes
echo "thing" | runify -s elder
# Output: ᚦᛁᛜ (th and ng as single runes)

# Non-phonetic mode - each letter becomes its own rune
echo "thing" | runify -s elder --no-phonetic
# Output: ᛏᚺᛁᚾᚷ (t-h-i-n-g as separate runes)
```

## Options

```
-h, --help              Display help and exit
-v, --version           Display version and exit
-l, --list              List available rune systems
-s, --system=SYSTEM     Specify rune system (elder, younger)
-p, --phonetic          Enable phonetic mode (default)
    --no-phonetic       Disable phonetic mode
```

## Installation

### From Binary

Download Latest Binary for your platform [here](https://github.com/divanvisagie/runify/releases)

### Install via homebrew
If you don't have the tap, add it with:
```sh
brew tap divanvisagie/homebrew-tap
```

Then simply
```sh
brew install runify
```

# Rune mappings

| Latin Character | Elder Futhark       | Younger Futhark                   |
|-----------------|---------------------|-----------------------------------|
| a               | ᚨ                   | ᛅ/ᛆ (a, æ, e)                     |
| b               | ᛒ                   | ᛒ (b, p)                          |
| c               | ᚲ                   | ᚴ (k, g, ŋ)                       |
| d               | ᛞ                   | ᛏ/ᛐ (t, d)                        |
| e               | ᛖ                   | ᛁ (i, e)                          |
| f               | ᚠ                   | ᚠ (f/v)                           |
| g               | ᚷ                   | ᚴ (k, g, ŋ)                       |
| h               | ᚺ                   | ᚼ/ᚽ (h)                           |
| i               | ᛁ                   | ᛁ (i, e)                          |
| j               | ᛃ                   | ᛡ (j, y)                          |
| k               | ᚲ                   | ᚴ (k, g, ŋ)                       |
| l               | ᛚ                   | ᛚ (l)                             |
| m               | ᛗ                   | ᛘ (m)                             |
| n               | ᚾ                   | ᚾ/ᚿ (n)                           |
| o               | ᛟ                   | ᚬ (ą, o, æ)                       |
| p               | ᛈ                   | ᛒ (b, p)                          |
| r               | ᚱ                   | ᚱ (r)                             |
| s               | ᛋ                   | ᛋ/ᛌ (s)                           |
| t               | ᛏ                   | ᛏ/ᛐ (t, d)                        |
| u               | ᚢ                   | ᚢ (u/v/w, y, o, ø)                |
| v               | ᚠ (same as f)       | ᚢ (u/v/w, y, o, ø)                |
| w               | ᚹ                   | ᚢ (u/v/w, y, o, ø)                |
| y               | ᛃ (same as j)       | ᛡ (j, y)                          |
| z               | ᛉ                   | ᛋ/ᛌ (s)                           |
| æ               | ᛇ                   | ᛅ/ᛆ (a, æ, e)                     |
| þ               | ᚦ                   | ᚦ (þ, ð)                          |
| ð               | ᚦ (same as þ)       | ᚦ (þ, ð)                          |
| ŋ               | ᛜ                   | ᚴ (k, g, ŋ)                       |
| þ               | ᚦ                   | ᚦ (þ, ð)                          |
| ð               | ᚦ (same as þ)       | ᚦ (þ, ð)                          |
| x               | ᚲᛋ                  | ᚴᛋ (x)                            |
| ch              | ᚷ                   | ᚷ (ch)                            |
| ij              | ᛖ                   | ᛖ (ij)                            |
| cc              | ᚲᛋ                  | ᚴᛋ (cc)                           |
| th              | ᚦ                   | ᚦ (th)                            |
| eau             | ᛟ                   | ᛟ (eau)                           |
| chr             | ᚺᚱ                  | ᚺᚱ (chr)                          |
| ing             | ᛜ                   | ᛜ (ing)                           |
| chl             | ᚺᛚ                  | ᚺᛚ (chl)                          |
| ng              | ᛜ                   | ᛜ (ng)                            |
| chj             | ᚺᛃ                  | ᚺᛡ (chj)                          |
| nk              | ᛜᚲ                  | ᛜᚴ (nk)                           |
| chw             | ᚺᚹ                  | ᚺᚹ (chw)                          |
| ei              | ᛋ                   | ᛋ (ei)                            |
| ø               | ᛟᛖ                  | ᛟᛖ (ø)                            |
| å               | ᚨᚨ                  | ᚭᚭ (å)                            |
| q               | ᚲ                   | ᚴ (q)                             |
| ʀ               |                     | ᛦ (ʀ)                             |

