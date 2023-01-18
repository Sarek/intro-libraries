# Fun with Shared Libraries

# Part 1: Dynamic vs. Static Linking

* Two demo programs, one statically linked, the other dynamically.
* Show library output from `readelf`
 * We can see we dynamically link against `libc.so` and `libm.so`
 * The static one does not have that
* Also show `ldd` output
 * What about `linux-vdso.so.1`
 * Execute multiple times: Objects are loaded at different addresses
   * ASLR
   * -no-pie turns off ASLR
     * Does not work when linking against dynamic libraries, still loaded at
       random locations
     * But look at `aslrcheck` executables!
* Explain program execution
 * Dynamic Loader
   * Loads executable
   * Loads dynamically linked objects
   * Updates/maintains PLT/GOT

# Part 2: Creating libraries

* Creating a static library vs. a shared library
* What is -fPIC?
* Why do we need RPATH?
  * Show usage of `chrpath`
  * Show RPATH with `readelf`
* Symbols
  * Show symbols in dynamically linked executable: Offsets are missing
  * In static executable those offsets are present
  * They are resolved at runtime by the dynamic loader

# Part 3: Symbol Resolution in Programs

* Two libraries with the same symbol, but different outputs
* Link order matters, both for static and dynamic linking!

# Part 3b: C++ Name Mangling

* Two functions with same name, but different parameters
* Show in `readelf` or `nm`
* Show how this does not work in C -- compiler error

# Part 4: Overriding library functions at link time

* -Wl,-wrap
* This only works with static libraries, not with shared libraries
* All the necessary symbols have to be linked together in one go.

# Part 5: Dynamic symbol table and lookups

* We have a library providing the foo function
* We can access it, even from C++
* We can't use `std::function` to get around the function pointer notation (at least I can't)
* As this is C++, let's look at the ldd output: We can see we now not only link against `libc.so`,
  but also `libstdc++.so` --> The C++ standard library!
* `libgcc_s.so` is the GCC low-level runtime library, mainly used for arithmetic
  operations the target processor cannot perform directly, and also for exception
  handling.

# Part 6: Preloading

* LD_PRELOAD
* We need to take care to initialize iostreams
* We are effectively loading our own library as the first one, even before `libc.so`.
* This results in our symbols being the first to be looked up in the PLT
* We can override everything! muahahaha
 * Except we can't.
 * LD_PRELOAD only works if RUID == EUID. This can be demonstrated with our `exec` binary. It will output the EUID.
 * Execute `exec` with `libmemleak.so` preloaded. We see memory allocations.
 * Do `sudo chown nobody:nobody exec` and `sudo chmod u+s exec`
 * Show that it is now setuid nobody with `stat exec`
 * Execute it again with `libmemleak.so` preloaded. No memory allocations can be seen.
* Why do we see any output at all on `exec`?
 * The C runtime reserves 1024 bytes for internal usage on startup
 * The C++ runtime reserves 72704 bytes for internal use.
 * As far as I know this is mainly necessary for I/O.
 * But why do we even see the C++ memory usage? This is a pure C program?
  * But the library links against libstdc++ and also has the C++ initialization routines
  * But, this is also a topic for my other talk "Life before main"

# Part 7: Magic

* Constructor and Destructor
* These are special attributes to gcc and clang
* You can define as many constructors and destructors as you want, also in libraries
* Constructors get executed before `main`, destructors after `main` has returned
* There is no specific order, but you may give priority hints to the compiler
* This also works with preloading!

* Side quiz in `exec`:
 * How much memory will be allocated for the data structures?

# Part 8: Symbold Versioning

* We have two `libfoo`, one version 1, the other version 2
* They both have map files that denote which symbols should be available in which version
* We update `foo`, so there are two incompatible versions
* To facilitate this, in v2, we don't call either just foo, and instead introduce some assembly magic that creates artifical symbols mapped to our function definitions
 * Exactly one needs to be denoted with double @. This will be the default version used when linking against this library.
* We can also introduce new functions that are only available in the new version
* When linking this together, we need to supply the map files
* The linker will then create versioned symbols, see `nm` output --> this is exactly what glibc does
* When normally linking, we don't see anything
* But now imagine we have a normal Linux distribution where only binary packages are installed and we update our library. Instead of needing to build each application depending on it again, we can just update the lib by introducing a new major version for our symbol, and applications can continue to use the old implementation
 * Show with LD_LIBRARY_PATH and `exec_flex_v1`
 * We can't downgrade to an older version, obviously (show with LD_LIBRARY_PATH and `exec_flex_v2`)

