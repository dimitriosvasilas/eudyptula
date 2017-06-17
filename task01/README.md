This is Task 01 of the Eudyptula Challenge
------------------------------------------

Write a Linux kernel module, and stand-alone Makefile, that when loaded
prints to the kernel debug log level, "Hello World!"  Be sure to make
the module able to be unloaded as well.

The Makefile should be able to build the kernel module against the
source of the currently-running kernel as well as being able to accept
an arbitrary kernel sources directory from an environment variable.
