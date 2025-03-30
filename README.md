# grish(a) - An AoT Themed Shell

> A Tribute to AoT.

**grish(a)** is a custom-made, AoT-themed Unix shell written in **C**, designed for fun, personal learning, and a bit of flair. It supports:

- Bash-like commands
- Built-in commands like `cd`, `exit`, and more
- Custom AoT-themed commands like `eren`, `yeager`, `shifter`, `titan`, `paradis`
- Two extra special commands - `rumbling` and `scouts`. No spoilers, have fun using them ;) 

--

## Project Structure

```bash
grisha-shell/
├── src/
│   ├── main.c              # Entry point
│   ├── shell.c             # Shell loop and core logic
│   ├── parser.c            # Command parsing logic
│   ├── executor.c          # Command execution logic
│   ├── builtins.c          # Built-in command functions (including AoT-themed)
│   ├── utils.c             # Helper functions (e.g., trimming, prompt, banner)
├── include/
│   ├── shell.h
│   ├── parser.h
│   ├── executor.h
│   ├── builtins.h
│   ├── utils.h
├── Makefile
├── README.md
├── .gitignore
└── LICENSE
```

**Note:** since this shell uses Unix-specific headers, it will likely not run on Windows. I haven'tt tested it on Windows or macOS.

## Build Instructions

    # in cwd, production
    make
    # or debug
    make debug

## Run

    ./grisha

