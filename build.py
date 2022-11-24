import os

loaded_files = set()

def search_include(code):
    begin = code.find("#include")
    if begin == -1: return None
    end = code.find("\n", begin)

    delim = '""'
    name_begin = code.find(delim[0], begin, end)
    if name_begin == -1:
        delim = '<>'
        name_begin = code.find(delim[0], begin, end)
    name_end = code.find(delim[1], name_begin+1, end)
    filename = code[name_begin+1:name_end]
    
    return filename, begin, end

def load_source(filename):
    if filename in loaded_files:
        print(f"[!] Error: {filename} is already loaded!")
        exit()
    else:
        loaded_files.add(filename)
    
    with open(filename, 'r') as infile:
        code = infile.read()
    
    # recursively load included files
    while (got := search_include(code)) is not None:
        child, begin, end = got
        code = code[:begin] + load_source(child) + code[end:]

    return code

dotnet = load_source("main.c")

with open("exe-template/EXE.bt", 'r') as infile:
    template = infile.read()

os.makedirs("build", exist_ok=True)
with open("build/EXE.bt", 'w') as ofile:
    ofile.write(template)
    ofile.write("\n")
    ofile.write(dotnet)
