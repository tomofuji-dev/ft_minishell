# minishell

Our own shell like bash, 42 project with [ykosaka](https://github.com/yunixuma)

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
