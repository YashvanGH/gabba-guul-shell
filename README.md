# Gabba Guul Shell 🐚

A minimal shell written in C that demonstrates the fundamentals of Unix process control, signals, and command execution.  

This project is designed as a learning exercise in **C programming** and **operating systems concepts**, focusing on how real shells like `bash` or `zsh` work under the hood.

---

## ✨ Features
- Prompt-based **command execution**
- **Built-in commands**:
  - `cd` &rarr; change directory  
  - `pwd` &rarr; print current working directory
  - `ls` &rarr; lists the files in the current directory
  - `echo` &rarr; print arguments to stdout  
  - `exit` &rarr; exit the shell
- Execution of **external programs** via `fork()` + `execvp()`
- **Error handling** with correct POSIX-style exit codes:
  - `127` &rarr; command not found  
  - `126` &rarr; command found but not executable
- **Signal handling**:
  - Parent shell ignores `SIGINT` (Ctrl-C) so it doesn’t terminate
  - Child processes restore default `SIGINT` so Ctrl-C kills them
- Clean process waiting using `waitpid()` and decoding with `WIFEXITED`, `WEXITSTATUS` and `WIFSIGNALED`

---

## 🛠️ How It Works

### Process flow
1. **Shell loop** reads user input.  
2. **Parse** the command into `argv[]`.  
3. **Dispatch**:
   - If it’s a built-in &rarr; run directly in the parent.  
   - Otherwise → `fork()` a child.  
4. **Child**:
   - Reset signals (e.g. `SIGINT` → `SIG_DFL`).  
   - Apply redirections.  
   - Run command via `execvp()`.  
5. **Parent**:
   - Calls `waitpid()` to collect child status.  
   - Prints errors / continues loop.

### Signals
- `SIGINT` (Ctrl-C):
  - Parent &rarr; ignored (`SIG_IGN`).  
  - Child &rarr; restored to default (`SIG_DFL`).  
- This matches real shell behavior.

---

## 🚀 Getting Started

### Build
```bash
make all
./gabba_guul
```

### Delete Executables
```bash
make clean
