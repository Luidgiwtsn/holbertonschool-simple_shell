# simple_shell — Simple Shell

`simple_shell` is a minimalist command-line interpreter written in C, developed as part of the **Simple Shell** project at Holberton School. It mimics the behavior of `/bin/sh`, allowing users to execute Unix commands interactively.

---

## 🚀 Features

- Command execution using `fork()` and `execve()`
- Interactive input handling with `getline()`
- PATH environment variable support for command lookup
- Built-in `exit` command to quit the shell
- Built-in `cd` command for directory navigation
- Error messages formatted with line numbers for debugging
- Support for both interactive and non-interactive modes

---

## 🧪 Example Usage

```bash
$ ./simple_shell
$ echo "Hello World"
Hello World
$ ls -l
total 32
-rwxr-xr-x 1 user user 8760 Aug 20 10:30 simple_shell
-rw-r--r-- 1 user user 1024 Aug 20 10:29 main.c
$ cd /tmp
$ pwd
/tmp
$ cd
$ exit
$
```

---

## 🛠️ Compilation

To compile the shell:
```bash
gcc -Wall -Wextra -Werror -pedantic *.c -o simple_shell
```

---

## 📁 Project Structure

Basé sur les fichiers fournis :

| File | Purpose |
|------|---------|
| `main.h` | Header file with function prototypes and includes |
| `AUTHORS` | List of project contributors |
| Code files containing: ||
| - `main()` | Main shell loop and command execution |
| - `_getenv()` | Custom getenv implementation |
| - `find_in_path()` | PATH directory search functionality |
| - `free_args()` | Memory management for argument arrays |
| - `read_and_clean_line()` | Input handling and line processing |
| - `split_line()` | Command line tokenization |
| - `execve_hsh()` | Command execution with error handling |

---

## 📚 Built-in Commands

| Command | Description |
|---------|-------------|
| `exit` | Exits the shell |
| `cd [directory]` | Changes current directory (defaults to HOME) |

---

## 🧠 Architecture Overview

**Input Handling**  
The shell reads user input using `getline()` and removes the trailing newline.

**Tokenization**  
Input is parsed using `split_line()`, which tokenizes commands and arguments.

**Command Execution**  
- Built-in commands are handled internally without forking
- External commands are executed by forking a child process and using `execve()`
- Commands are searched in PATH directories if not found as absolute/relative paths

**Error Handling**  
Errors are printed to stderr with line numbers and formatted messages that help with debugging.

---

## 🧪 Testing

You can test your shell by comparing its behavior to standard shells:

```bash
# Test basic commands
echo "ls -l" | ./simple_shell
echo "pwd" | ./simple_shell

# Test built-in commands
echo -e "cd /tmp\npwd\nexit" | ./simple_shell

# Test error handling
echo "nonexistent_command" | ./simple_shell
```

---

## 📋 Requirements

- All files are compiled on Ubuntu 20.04 LTS
- Code follows Betty coding style
- No memory leaks
- Maximum 5 functions per file
- All function prototypes included in `main.h`

---

## 👥 Authors

- **Luidgi Watson** - <11499@holbertonstudents.com>
- **Thomas Decourt** - <11483@holbertonstudents.com>

---

## 📜 License

This project is intended for educational purposes and is not licensed for commercial use.
