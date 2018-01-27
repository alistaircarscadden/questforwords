# Quest For Words

Quest For Words is a program designed to locate specific words within infinite strings.

To get the tool run `git clone https://github.com/tejedu/questforwords.git` and compile `questforwords.c` into an executable. With gcc you may use the command `gcc questforwords.c -o qfw`.
Run the tool with `./qfw WORD 10000` or `./qfw f 10000 a_file.txt`. In the first example WORD will be searched against as many seeds as it takes, up to a length of 10K. In the second, the same except every word in a_file.txt will be searched.

## What?

Okay, so what is an infinite string?

You can generate an infinite string of characters with the following code:
```C
srand(1);
while(1) {
	printf("%c", rand() % 26 + 'A');
}
```

Now, let's say you want to find a word in the infinite string. That's what this tool is for. You give it a word, and it will tell you which seed contains that word within a certain character limit. So, if you want to find WHACK in the first 10K characters of an infinite string, the program would tell you this:
```
$ ./qfw WHACK 10000
WORD                     SEED    INDEX
WHACK                     827      844
```
This means that in the string seeded with 827, the word WHACK appears starting at the 844th character.

```
$ ./qfw f 1000000 words.txt
WORD                     SEED    INDEX
THEY                        1   960821
PAINT                       5   636248
THE                         1   998382
MOON                        1   666549
TODAY                      18   940893
SOME                        1   482222
BRAND                      24    67505
NEW                         1   993749
FUTURE                    779   212084
COLOR                       9    59111
```