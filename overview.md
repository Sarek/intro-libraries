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

# Part 6: Magic

* Constructor and Destructor
