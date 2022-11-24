import os

with open("main.c", 'r') as infile:
    dotnet = infile.read()

with open("exe-template/EXE.bt", 'r') as infile:
    template = infile.read()

os.makedirs("build", exist_ok=True)
with open("build/EXE.bt", 'w') as ofile:
    ofile.write(template)
    ofile.write("\n")
    ofile.write(dotnet)
