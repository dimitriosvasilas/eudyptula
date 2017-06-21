This is Task 09 of the Eudyptula Challenge
------------------------------------------

Nice job with debugfs.  That is a handy thing to remember when wanting
to print out some debugging information.  Never use /proc/ that is only
for processes, use debugfs instead.

Along with debugfs, sysfs is a common place to put information that
needs to move from the user to the kernel.  So let us focus on sysfs for
this task.

The tasks this time:

  - Take the code you wrote in task 08, and move it to sysfs.  Put the
    "eudyptula" directory under the /sys/kernel/ location in sysfs.
  - fix up the permissions of the files to not allow world writable
    values, but only be able to be written to by root.
  - Provide some "proof" this works.

That's it!  Simple, right?  No, you are right, it's more complex; sysfs
is complicated.  I'd recommend reading Documentation/kobject.txt as a
primer on how to use kobjects and sysfs.
