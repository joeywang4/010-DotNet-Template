# 010 Editor .NET PE Template

A [010 Editor](https://www.sweetscape.com/010editor/) template for Windows managed executable files. (PE files with Common Language Runtime (CLR) data)

## Features
This template can parse:
- CLR header
- Stream headers
- Stream data
- Metadata tables

## Install
Download the built template file from [release page](https://github.com/joeywang4/010-DotNet-Template/releases).

OR

1. Run `build.py` to generate the template file
2. Copy `build/EXE.bt` to your 010 Editor's templates repository (usually at `~/Documents/SweetScape/010 Templates/Repository`)
3. Load a .NET exe file

## Development
TLDR: Remember to add `#include "new-file.c"` to an existing file when a new file is created.

For the ease of developement, the definitions of headers/stream data/MD tables are separated to different files, some in `main.c` and others in the `src/` folder. However, 010 Editor requires a single template file, so `build.py` is needed to combine all these files together. 

To link the files, `build.py` searches for `#include "child.c"` in `main.c` and recursively includes the children files into `main.c`. Finally, it combines the content inside `main.c` and the original EXE file template located at `exe-template/EXE.bt` to produce a single template file `build/EXE.bt`.

PRs are welcome!

## TODO List
- Managed Resource
- Parsing uncompressed MD stream (`#-`)
- Parsing CIL
- Parsing types

## References
- Lidin, Serge. Inside Microsoft. net il assembler. Microsoft Press, 2002.
