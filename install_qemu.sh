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

		cd ${HOME}		
		wget http://download.qemu-project.org/qemu-${QEMU_VERS}.tar.xz
		tar xvJf qemu-${QEMU_VERS}.tar.xz
		cd qemu-${QEMU_VERS}
		./configure --enable-kvm --disable-rdma --target-list=x86_64-softmmu
		make
		sudo make install
	fi	
fi
