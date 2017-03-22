#!/bin/bash
/usr/local/bin/qemu-system-x86_64 -enable-kvm -M pc-0.12 -m 1024 -smp 2 -drive format=raw,file=ubuntu.img -net user,hostfwd=tcp::10022-:22 -net nic -vnc 127.0.0.1:0 -nographic -monitor /dev/null &
