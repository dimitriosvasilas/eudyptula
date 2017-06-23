sudo umount /sys/kernel/debug/
sudo mount -t debugfs none /sys/kernel/debug/ -o users
ls -la /sys/kernel/debug/eudyptula/
cat /sys/kernel/debug/eudyptula/jiffies
cat /sys/kernel/debug/eudyptula/jiffies
cat /sys/kernel/debug/eudyptula/id
sudo sh -c "echo 'afa9c09dcaad' > /sys/kernel/debug/eudyptula/id"
sudo sh -c "echo 'afa9c09dcaae' > /sys/kernel/debug/eudyptula/id"
echo $?
sudo sh -c "echo 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx' > /sys/kernel/debug/eudyptula/foo"
cat /sys/kernel/debug/eudyptula/foo

