
### Debugfs Device Driver

This is a debugfs device driver.
- It creates a debugfs subdirectory called "dfsd". In that directory, is create the virtual file called "id". This "id" file operates like the [misc char device](https://github.com/dimitriosvasilas/kernel-programming-challenge/tree/master/misc_char_driver).
- It creates another file called "jiffies", which is to be read-only by any user, and when read, returns the current value of the jiffies kernel timer.
debugfs
 - Finally, the device driver creates a debugfs file called "foo". This file is writable only by root, but readable by anyone. 
 When writing to it, the value is stored (up to 1 page of data).  When read, the stored value is returned.
