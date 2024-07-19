[WebAssembly port](https://pbrochard.github.io/colorforth-pbr/wasm/colorforth.html)

![](doc/99-bottles-color.png?raw=true) ![](doc/99-bottles-prefix-color.png?raw=true) ![](doc/99-bottles-nocolor.png?raw=true)

![](doc/screenshot.png?raw=true)
![](doc/screenshot-colorize.png?raw=true)

### Minimal version
![](doc/screenshot-minimal.png?raw=true)

### 2 + 2 = 5 joke
[![asciicast](https://asciinema.org/a/442906.svg)](https://asciinema.org/a/442906)

### Heap layout

```
&heap
|                                                                                  &dhere
|                                                                                    |
v                                                                                    v
code...;|code....;|code...;| ...FREE...  |quotation...;|string...0|array...|var|var|dhere|
^        ^         ^        ^           ^ ^             ^          ^        ^   ^   |     ^
|        |         |        |           | |             |          |        |   |   |     |
|        |         |        \-> here    \-+-------------+----------+--------+---+---/     |
|        |         \-> entry            | |             |          |        |   |         |
|        \-> entry                      | \-> quotation |          \-> var  |   \-> var   |
\-> entry                               |               \-> string          \-> var       |
                                        \-> dhere                                         |
                                                                            End of Heap <-/
```
