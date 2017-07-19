import json
import os
import subprocess

rootdir = os.getcwd()

include_dirs = [os.getcwd() + '/core/public']

for package in os.listdir('modules'):
    protocol_dir = rootdir + '/modules/' + package + '/protocols'
    if os.path.exists(protocol_dir):
        include_dirs.append(protocol_dir)

    interface_dir = rootdir + '/modules/' + package + '/interfaces'
    if os.path.exists(interface_dir):
        include_dirs.append(interface_dir)

type_extensions = {
    'executable': 'exe',
    'dynamic': 'dll'
}

def Compile(srcfile, objdir, flags):
    args = ['cl', '/nologo', '/EHsc', '/FS', '/Zi'] + flags + ['/c', srcfile, '/Fo:obj\\']
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

    target_name = config['bin-dir'] + '/' + config['target-name'] + '.' + type_extensions[config['target-type']]
    pdb_name = config['bin-dir'] + '/' + config['target-name'] + '.pdb'

    args = ['link', '/nologo'] + flags + objs + ['/debug', '/pdb:' + pdb_name] + ['/out:' + target_name]
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
    
    for include_dir in include_dirs:
        AddInclude(flags, include_dir)

    for incdir in config['includes']:
        AddInclude(flags, rootdir + '/' + incdir)

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
BuildDirectory('modules/modular-pkg/logger')