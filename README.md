## Minishell

Minishell is a project developed by students at 42 school, which aims to create a simple shell program similar to the Unix command-line interpreter (shell). The project focuses on implementing various features and functionalities commonly found in a shell, such as executing commands, managing processes, handling signals, and implementing built-in shell commands.

### Tests

**1-** Creates the image in docker, it must be run only once:
`docker build -t gtest .`

**2-** Create container:
`docker run -v .:/minishell -it gtest`

**3-** Execute the tests:
`make runTests`

### Features

- Command execution: Minishell allows users to execute commands by typing them into the shell prompt. It supports executing both built-in shell commands and external commands available in the system.
- Environment variables: Users can set and manipulate environment variables within the shell. Minishell provides functionality to manage and use environment variables effectively.
- Redirection and piping: Minishell supports input/output redirection and command piping, allowing users to redirect input or output from/to files and chain multiple commands together.
- Signal handling: The shell handles various signals, such as SIGINT (interrupt signal) and SIGQUIT (quit signal), providing a smooth user experience.
- Error handling: Minishell provides informative error messages and handles errors gracefully to ensure a robust and user-friendly shell experience.
