### USB Keyboard Kernel Module

This is a USB keyboard kernel module, and stand-alone Makefile. When loaded, it simply prints to the kernel debug log level
"Hello World".

The module is automatically loaded when any keyboard is plugged in.

The Makefile builds the kernel module against the source of the currently-running kernel and is also able to accept an arbitrary
kernel sources directory from an environment variable.
