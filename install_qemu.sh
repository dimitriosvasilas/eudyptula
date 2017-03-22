#!/bin/bash
sudo apt-get install gcc make vim socat bzip2
sudo apt-get install zlib1g-dev libglib2.0-dev xtightvncviewer
sudo apt-get install autoconf libtool flex bison
sudo apt-get install libncurses5-dev
if grep -q "vmx" /proc/cpuinfo ; then
	if ! lsmod | grep -q "kvm_*" ; then
		sudo modprobe kvm_intel
	fi
	if lsmod | grep -q "kvm_*" ; then
		sudo groupadd -f kvm
		sudo usermod -aG kvm $USER
		echo KERNEL==\"kvm\", GROUP=\"kvm\" | sudo tee /etc/udev/rules.d/40-permissions.rules
		sudo modprobe -r kvm_intel
		sudo modprobe -r kvm
		sudo modprobe kvm_intel
		
		wget http://download.qemu-project.org/qemu-2.8.0.tar.xz
		tar xvJf qemu-2.8.0.tar.xz
		cd qemu-2.8.0
		./configure --enable-kvm
		make
		sudo make install 
	fi
	
fi
