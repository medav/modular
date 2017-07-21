# 1 Modular Overview
## 1.1 Broad Philosophy
Modular is desinged to be a cross-platform, cross-license, MIT licensed framework for developing modular C/C++ applications. Modular Modules are dynamic libraries (DLLs on Windows, Shared Objects on Linux, etc...) that adhere to the Modular API specification. Modular features a core capable of facilitating module load, startup, execution and inter-module interfacing. It also features a robust engineering system written in Python designed to make building Modular applications easy as cake.

## 1.2 Anatomy of a Modular Module
A module is a binary that contains implementations of a few required functions:

`ModuleLoad()` is responsible for constructing a dispatch table of the rest of the required functions. It is the only function required to be an exported symbol from a library (E.g. `__declspec(dllexport)` in a Windows DLL).

`ModuleInit()` is responsible for performing any initialization (such as protocol installation) specific to the module. This runs before ModuleStart is called on any other module.

`ModuleStart()` is responsible for performing any additional startup for the module. It runs after ModuleInit is called for every module so is allowed to make cross-module references such as protocol lookup.


# 2 Modular Core
## 2.1 Overview
The Modular Core is the minimalistic, cross-platform startup executable that serves as an entry point for an application. The built executable is named `modular.exe` but in deployment is intended to be renamed to match the deployed application name.

## 2.2 Startup Sequence
Modular Core starts an application with the following steps:

1. Start the global Modular Services
2. Search for module binaries
3. Load binaries and call `ModuleLoad()`
4. Call `ModuleInit()` on all modules
5. Call `ModuleStart()` on all modules
6. Hand-off execution to user specified startup module

Steps 4 and 5 are split to allow for a two-stage startup sequence. It is intended that all protocols (described later) are installed during `ModuleInit()` so other modules can lookup and acquire references to protocols during `ModuleStart()`.

## 2.3 Startup Modules
There are special types of modules called `Startup Modules`. These modules provide an additional function called `ModuleMain()` in their dispatch structure. The modular core assumes if this is non-null then the module can be used for handoff. A user running the application can select the desired startup module through the first argument on the command-line.

# 3 Modular Engineering System (ES)
## 3.1 Overview
The engineering system for Modular is written in Python 3. Note that no non-standard Python packages are used for the engineering system, so getting started with building a Modular application should be easy.

## 3.2 Building
The engineering system is equipped to build on Windows, Mac, and Linux platforms with native tools. It achieves this through the use of Python with extensions designed for each of these environments.

How a module is built is described in a special file called `build.json`. This file contains metadata such as:

* Name of target
* Type of target (executable, static, dynamic)
* Source files to build, with the ability to specifiy different sources for different platforms
* Configurable output directory for binaries
* List of additional include paths (relative to workspace root)

Additional **implicit** include directories are:

* The `core/public` folder
* `objects/` and `protocols/` found in all package directories

Modular build can be invoked with a simple `python build.py`.



# 4 Protocols
## 4.1 Overview
Protocols are interfaces global to the application that are provided implementations by a module. Protocol declarations should be placed in a package's `protocol/` folder, making it visible to any Module in any package. Protocol declarations are pure abstract sub-classes of the Protocol base class provided in `core/public/protocol.h`.

A module can provide a protocol by providing a private implementation of a protocol declared in any package's `protocols/` folder then installing an instance of that implementation using the modular services provided during ModuleInit().

## 4.2 Type Naming Convention
Modular adhere's to a all lowercase, 'dashed' convention. With the exception of extremely common [*] acronyms or abbreviations, no abbreviations or acronyms are used. No trailing '-protocol' is used in a protocol's type name.

[*] '*Extremely common*' is subject to interpretation.

Examples of compliant protocol names:
~~~
debug
hello-world
i-like-turtles
~~~

Examples of non-compliant protocol names:
~~~
Debug
helloWorld
obscure-acronym-name-oan
i-use-abbrev-names
~~~

## 4.3 Multiple Protocols of Same Type
Multiple protocols of the same type can be provided by one or more modules. Protocols of the same type are differentiated by user defined charactaristics and carry no distinction to the modular core services. 

Client code can lookup a protocol with a given type using the modular services. It can decide whether or not to take the first instance matching the desired protocol type or choose to further search the returned list of results.

## 4.4 Protocols as Services
Protocols can be used to provide service style functionality. For example, consider an application that needs some method of sending and receiving messages with a remote process. A protocol called `message-passing` could be declared, providing the service of sending and receiving messages. Further, multiple modules could provide this protocol with different backing mechanisms such as a pipe, socket, or mpi. 

## 4.5 Protocols as Factories
Protocols can also (and are intended to) be used as object factories. Public object delarations (described in another section) contain no implementation and constructor details. A module can provide a method for creating backing implementations through a protocol serving as a factory for that particular object type. Note that protocols used as factories carry no distinction from other protocols.

Nameing:

Abbvreviations used:
Impl - Implementation
Num - Number of
Func - Function typedef suffix