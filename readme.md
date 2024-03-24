[Example](https://pbrochard.github.io/colorforth-pbr/wasm/colorforth.html)

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
code...;|code....;|code...;| ...FREE...  |quotation...;|string...0|array...|var|var|dhere|EndOfHeap
^        ^         ^        ^           ^ ^             ^          ^        ^   ^   |
|        |         |        |           | |             |          |        |   |   |
|        |         |        \-> here    \-+-------------+----------+--------+---+---/
|        |         \-> entry            | |             |          |        |   |
|        \-> entry                      | \-> quotation |          \-> var  |   \-> var
\-> entry                               |               \-> string          \-> var
                                        \-> dhere
```
