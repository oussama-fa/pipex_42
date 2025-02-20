# Pipex 🚀 - 42 School Project - 1337 KH

![42 Project Badge](https://img.shields.io/badge/1337-Project-blue?style=for-the-badge&logo=42)

---

## Overview

`pipex` is a program that mimics the behavior of the shell's `pipe` (|) and redirection (<, >). It takes an input file, two commands, and an output file, and executes the commands in a `pipe`line, redirecting the output of the first command to the input of the second command.

This project emphasizes `process management`, `file handling`, `pipes`, and `error handling`
---

## Screenshots 🖼️

<div align="center">
  <img src="125.png" alt="125" width="500"/>
</div>


---

## Features

- **Pipe functionality**: Simulates the shell's `pipe` (|) behavior.
- **Input/output redirection**: Supports file `redirection` (< and >).
- **Command execution**: Executes shell commands using `execve`.
- **Error handling**: Handles invalid commands, files, and system errors gracefully.
- **Memory management**: Leak-free (tested with valgrind).

---

## How It Works

The program takes four arguments:

1. Input file: The file to read input from.

2. Command 1: The first command to execute.

3. Command 2: The second command to execute.

4. Output file: The file to write the final output to.

---

## Installation

1. Clone the repository:
```bash
git clone https://github.com/oussama-fa/pipex_42.git
cd pipex_42
```

2. Compile the game:

- ``Mandatory`` :

```bash
make
```

- ``Bonus`` :

```bash
make bonus
```

3. Run with a map file:

- Mendatory :
```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```
- Bonus :

```bash
./pipex_bonus input.txt "grep hello" "ls" "cat" "cat" "wc -l" output.txt
```

---

## Technical Details

- Built with: C

- System calls: fork, pipe, dup2, execve, waitpid

- Error handling: Handles invalid commands, files, and system errors.

- Memory management: Leak-free (tested with valgrind).

- Code style: Adheres to 42 School's Norminette guidelines.

### Bonus Features:

- Support for multiple pipes: Handles more than two commands in a pipeline.

- Here Document: Supports << for inline input.

- Error handling: Improved error messages and handling.

---


## Author
*Oussama FARAH*

- 📱 **Instagram**: [@oussama._.farah](https://www.instagram.com/oussama._.farah/)
- ✉️ **Email**: [oussama05farah@gmail.com](mailto:oussama05farah@gmail.com)

---

<div align="center"> <h2>Enjoy piping! 🚀</h2> </div> 
