# 📝 Text Toolkit
## Project Overview
This is program is used to let you filter, transform, and summarize the contents of any plain‑text file.
It demonstrates robust file‑I/O, dynamic memory management, and plug‑and‑play “operations” implemented with function pointers and configuration structs.

## 🔑 Features
| Menu Option | Capability | Process |
|------------|------------|---------|
| 1 · Filter lines | Keep lines that do _not_ contain a user‑supplied keyword | Two‑tier loop + `keyCheck()` to drop matches |
| 2 · Transform lines | U → convert every line to uppercase<br>R → reverse each line | Action dispatched through `TransformConfig` |
| 3 · Summarize lines | • total line count<br>• frequency of a target word (case‑insensitive)<br>• average line length | Uses helper `countKeyword()` & on‑the‑fly stats |
| 4 · Exit | Quit safely, freeing all heap memory | `freeLines()` cleans up |
                                                                              |

Every processed result is immediately written to the output file you specify.

## 🛠️ Build & Run
Windows User: 
1. Download VS Code and C/C++ Extension in VS Code.
2. Download MinGW. Link: https://sourceforge.net/projects/mingw/
3. In Terminal, type `gcc main.c operation.c fileProcessing.c -o text-toolkit.exe` for compile the program and build the executable.
4. In Terminal, type `.\text-toolkit.exe` to run the program.

Mac User:
1. Open Terminal, type `xcode-select --install` to install the Command Line Tools.
2. In Terminal, type `gcc main.c operation.c fileProcessing.c -o text-toolkit` for compile the prgram and build the executable.
3. Lastly, type `./text-toolkit` to run the program.


## ✨ Implementation Highlights
- Loose coupling via function pointers

    - `typedef char **(*funcPtr)(char **, int, void *, int *);`  
    - allows new operations to drop in without touching main.c.

- Memory‑safe patterns
All heap allocations checked; buffers sized with strlen + 1; interactive input trimmed with newline guards.

- Cross‑platform build flags
-Wall -Wextra -std=c11 keeps the code standards‑compliant and warning‑free.

- Clear separation of concerns

    - I/O layer: fileProcessing.*

    - Domain logic: operations.*

    - UI + flow control: main.c


