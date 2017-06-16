### Misc Char Device Driver
This is a misc char device driver.
- The misc device is created with a dynamic minor number.
- It implements read and write functions.
- It appears in /dev/miscd.
- When the character device node is read from, the string "afa9c09dcaae" is returned to the caller.
- When the character device node is written to, the data is checked, and if matches the string "afa9c09dcaae",
then a correct write return value is returned. Otherwise, an "invalid value" error value is returned.
