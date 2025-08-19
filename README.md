# hsh — Simple Shell

`hsh` is a minimalist command-line interpreter written in C, developed as part of the **Simple Shell** project at Holberton School. It mimics the behavior of `/bin/sh`, allowing users to execute Unix commands interactively or via scripts.

---

## 🚀 Features

- Command execution using `fork()` and `execvp()`
- Interactive input handling with `getline()`
- Advanced tokenization with support for quotes and shell operators (`|`, `>`, `&&`, etc.)
- Built-in `exit` command to quit the shell
- Built-in `env` command to display environment variables
- Error messages formatted to match `/bin/sh` output

---

## 🧪 Example Usage

```bash
./hsh
myshell$ echo "Hello World"
Hello World
myshell$ ls -l
myshell$ exit


🛠️ Compilation 

To compile the shell : 
gcc -Wall -Wextra -Werror -pedantic *.c -o hsh

📁 Project Structure

File	Purpose
main.c	Main shell loop
smart_tokenize.c	Tokenizes input with quote/operator support
main.h	Header for tokenizer
builtins.c	Handles built-in commands (exit, env)
README.md	Project documentation

📚 Built-in Commands
Command	Description
exit	Exits the shell
env	Prints environment variables
🧠 Architecture Overview
Input Handling The shell reads user input using getline() and removes the trailing newline.

Tokenization Input is parsed using smart_tokenize(), which handles quoted strings and shell operators.

Command Execution The shell forks a child process and uses execvp() to execute external commands.

Built-in Commands Commands like exit and env are handled internally without forking.

Error Handling Errors are printed to stderr using perror() or custom messages that match /bin/sh format.

🧪 Testing
You can test your shell by comparing its output to /bin/sh:

bash
echo "ls -l" | ./hsh
echo "ls -l" | /bin/sh
Both should produce identical results.

📜 License
This project is intended for educational purposes and is not licensed for commercial use.

