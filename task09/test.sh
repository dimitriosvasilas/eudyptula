ls -la /sys/kernel/eudyptula/
cat /sys/kernel/eudyptula/jiffies
cat /sys/kernel/eudyptula/jiffies
cat /sys/kernel/eudyptula/id
echo "asdf" > /sys/kernel/eudyptula/id
echo "afa9c09dcaae" > /sys/kernel/eudyptula/id
echo $?
sudo sh -c "echo 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx' > /sys/kernel/eudyptula/foo"
cat /sys/kernel/eudyptula/foo

sudo su -

python -c 'print "A"*4095' > /sys/kernel/eudyptula/foo
python -c 'print "A"*5000' > /sys/kernel/eudyptula/foo
