import json
import os
import subprocess

core_public_dir = os.getcwd() + '/core/public'

type_extensions = {
    'executable': 'exe',
    'dynamic': 'dll'
}

def Compile(srcfile, objdir, flags):
    args = ['cl', '/nologo', '/EHsc'] + flags + ['/c', srcfile, '/Fo:obj\\']
    # print(args)
    proc = subprocess.Popen(args)
    
    objfile = srcfile.replace('.cpp', '.obj')
    objfile = objfile.replace('.c', '.obj')
    objfile = objfile.replace(os.path.dirname(srcfile), 'obj')
    
    return proc, objfile

def Link(config, objs):
    flags = []
    if config['target-type'] == 'dynamic':
        flags.append('/DLL')

    args = ['link', '/nologo'] + flags + objs + ['/out:' + config['bin-dir'] + '/' + config['target-name'] + '.' + type_extensions[config['target-type']]]
    # print(args)
    subprocess.Popen(args).wait()

def AddInclude(flags, incdir):
    flags.append('/I' + incdir)

def BuildDirectory(dir_full_path):
    curdir = os.getcwd()
    os.chdir(dir_full_path)

    with open('build.json') as f:
        config = json.load(f)

    print('-'*20 + config['target-name'] + '-'*20)

    objs = []
    procs = []
    flags = []

    AddInclude(flags, 'include')
    AddInclude(flags, 'public')
    AddInclude(flags, core_public_dir)

    sources = config['sources']['any'] + config['sources']['win']
    
    for srcfile in sources:
        proc, objfile = Compile(srcfile, 'obj', flags)
        procs.append(proc)
        objs.append(objfile)

    for proc in procs:
        proc.wait()

    Link(config, objs)

    os.chdir(curdir)

BuildDirectory('core')
BuildDirectory('modules/modular-pkg/hello-world')