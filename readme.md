### Discontinued

This C version is discontinued.
Do not expect too many more commits.
A complete rewrite from scratch in assembly continues at https://git.sr.ht/~hocwp/painterForth

[WebAssembly port](https://pbrochard.github.io/colorforth-pbr/wasm/colorforth.html)

![](doc/99-bottles-color.png?raw=true) ![](doc/99-bottles-prefix-color.png?raw=true) ![](doc/99-bottles-nocolor.png?raw=true)

![](doc/lib.png?raw=true)

### Minimal version
![](doc/screenshot-minimal.png?raw=true)

### 2 + 2 = 5 joke
[![asciicast](https://asciinema.org/a/4Pj6f2zWerSnvbOEDZOoDFH38.svg)](https://asciinema.org/a/4Pj6f2zWerSnvbOEDZOoDFH38)

### Building

- Base version

```
make colorforth-base
```

- Full version with `src/lib.cf` included

```
make
```

### Heap layout

```
&heap
|                                                                                       &dhere
|                                                                                       |
v                                                                                       v
code...;|code....;|code...;| ...FREE...  |quotation...;|len.string...0|array...|var|var|dhere|
^        ^         ^        ^           ^ ^             ^              ^        ^   ^   |     ^
|        |         |        |           | |             |              |        |   |   |     |
|        |         |        \-> here    \-+-------------+--------------+--------+---+---/     |
|        |         \-> entry            | |             |              |        |   |         |
|        \-> entry                      | \-> quotation |              \-> var  |   \-> var   |
\-> entry                               |               \-> string              \-> var       |
                                        \-> dhere                                             |
                                                                                End of Heap <-/
```
