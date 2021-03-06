 [![Stories in Ready](https://badge.waffle.io/thpatch/thcrap.svg?label=ready&title=Ready)](http://waffle.io/thpatch/thcrap)
Touhou Community Reliant Automatic Patcher
------------------------------------------

### Description ###

Basically, this is an almost-generic, easily expandable and customizable framework to patch Windows applications in memory, specifically tailored towards the translation of Japanese games.

It is mainly developed to facilitate self-updating, multilingual translation of the [Touhou Project](http://en.wikipedia.org/wiki/Touhou_Project) games on [Touhou Patch Center](http://thpatch.net/), but can theoretically be used for just about any other patch for these games, without going through that site.

#### Main features of the base engine #####

* Easy **DLL injection** of the main engine and plug-ins into the target process.

* **Full propagation to child processes**. This allows the usage of other third-party patches which also use DLL injection, together with thcrap. (Yes, this was developed mainly for vpatch.)

* Uses **JSON for all patch configuration data**, making the patches themselves open-source by design. By recursively merging JSON objects, this gives us...

* **Patch stacking** - apply any number of patches at the same time, sorted by a priority list. Supports wildcard-based blacklisting of files in certain patches through the run configuration.

* Automatically adds **transparent Unicode filename support** via Win32 API wrappers to target processes using the Win32 ANSI functions, without the need for programs like [AppLocale](http://en.wikipedia.org/wiki/AppLocale).

* Patches can support **multiple builds and versions** of a single program, identified by a combination of SHA-256 hashes and .EXE file sizes.

* **Binary hacks** for arbitrary in-memory modifications of the original program (mostly used for custom assembly).

* **Breakpoints** to call custom DLL functions at any instruction of the original code. These functions can read and modify the current CPU register state.

 * **File breakpoints** to replace data files in memory with replacements from patches.

* Wildcard-based **file format patching hooks** called on file replacements - can apply patches to data files according to a (stackable!) JSON description.

* ... and all that without any significant impact on performance. ☺

### Modules included ###

* `win32_utf8`: A UTF-8 wrapper library around the Win32 API calls we require. This is a stand-alone project and can (and should) be freely used in other applications, too.
* `thcrap`: The main patch engine.
* `thcrap_loader`: A command-line loader to call the injection functions of `thcrap` on a newly created process.
* `thcrap_configure`: A rather cheap command-line patch configuration utility. Will eventually be replaced with a GUI tool.
* `thcrap_tsa`: A thcrap plug-in containing patch hooks for games using the STG engine by Team Shanghai Alice.
* `thcrap_update`: A thcrap plug-in containing updating functionality for patches.

### Building ###

A ready-made Visual Studio build configuration, covering all modules and their dependencies, is provided as part of this repository. [Visual Studio Community 2013](https://www.visualstudio.com/products/visual-studio-community-vs) is recommended for builidng, as the build configuration references the Visual Studio 2013 platform toolset with Windows XP targeting support by default. However, the project should generally build under every version since Visual C++ 2010 Express after changing the `<PlatformToolset>` value in `Base.props`. For a list of all platform toolsets available on your system, open the `Properties` dialog for any included project and refer to the drop-down menu at *Configuration Properties → General → Platform Toolset*.

Before compile the code, make sure that you've pulled all Git submodules together with this repo:

		git clone --recursive https://github.com/thpatch/thcrap.git

Then, open `thcrap.sln`, choose Debug or Release from the drop-down menu in the toolbar (or the Configuration Manager) and run *Build → Build Solution* from the main menu.

You can also build from the command line by running the Visual Studio tool environment batch file (`vcvarsall.bat`), then run

		msbuild /m /p:Configuration=Debug

or

		msbuild /m /p:Configuration=Release
		
in the thcrap directory.

#### Dependencies ####

All required third-party libraries for the C code are included as Git submodules. These are:

* [Jansson](http://www.digip.org/jansson/), required for every module apart from `win32_utf8`.

* [libpng](http://www.libpng.org/pub/png/libpng.html) **(>= 1.6.0)**, required by `thcrap_tsa` for image patching.

* [zlib](http://zlib.net/), required by `thcrap_update` for CRC32 verification. It's required by `libpng` anyway, though.

The scripts in the `scripts` directory are written in [Python 3](http://python.org/). Some of them require further third-party libraries not included in this repository:

* [PyCrypto](https://www.dlitz.net/software/pycrypto/) is required by `release_sign.py`.
