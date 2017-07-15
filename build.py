import json
import os
import subprocess

def Compile(srcfile, objdir, flags):
    args = ['cl', '/EHsc'] + flags + ['/c', srcfile, '/Fo:obj\\']
    print(args)
    subprocess.Popen(args)
    
    objfile = srcfile.replace('.cpp', '.obj')
    objfile = objfile.replace('.c', '.obj')
    objfile = objfile.replace(os.path.dirname(srcfile), 'obj')
    
    return objfile

def Link(config, objs):
    args = ['link'] + objs + ['/out:' + config['bin-dir'] + '/' + config['target-name']]
    print(args)
    subprocess.Popen(args)

def AddInclude(flags, incdir):
    flags.append('/I:' + incdir)

def BuildDirectory(dir_full_path):
    curdir = os.getcwd()
    os.chdir(dir_full_path)

    with open("build.json") as f:
        config = json.load(f)

    objs = []
    flags = []

    sources = config['sources']['any'] + config['sources']['win']
    
    for srcfile in sources:
        objs.append(Compile(srcfile, 'obj', flags))

    Link(config, objs)

    os.chdir(curdir)

BuildDirectory('core')