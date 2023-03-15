# minishell

Our own shell like bash, 42 project with [ykosaka](https://github.com/yunixuma)

<img width="618" alt="image" src="https://user-images.githubusercontent.com/101627898/225336570-69cbba0f-41e6-430c-a6dc-7ffb8ef64e25.png">

### How to use

```
make && ./minishell
```

### Available options

- Minishell runs executable by **absolute / relative path** (based on environment variable ``$PATH``).

- It has a **working history**.

- ``'``, ``"``, and dollars like ``$PATH``, ``$?`` are interpreted same as bash.

- We implemented **redirections** ``>``, ``<``, ``>>``, ``<<`` as well as **pipes** ``|``.

- **Signal** ``Ctrl-C``, ``Ctrl-D``, ``Ctrl-\`` are handled like in bash.

- A few cmds are executed as **"built-in"**, without calling executable. We re-coded them directly: ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit``.
