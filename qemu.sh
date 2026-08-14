#!/bin/bash
echo "Running iso.h"
set -e
. ./iso.sh

echo "About to lauch QEMU"
while getopts "d","n" opts; do
    case $opts in
    d) 
        echo "Set up for GDB"
        qemu-system-$(./target-triplet-to-arch.sh $HOST) -s -S -cdrom zenos.iso
        exit 1
        ;;
    n)  echo "Set up with No Reboot"
        qemu-system-x86_64 -d int -no-reboot -no-shutdown -cpu qemu64 -cdrom zenos.iso
        ;;
    ?)
        echo "No Selection"
        exit 1
        ;;
    esac

done
echo "Running Default"
#qemu-system-$(./target-triplet-to-arch.sh $HOST) -s -S -cdrom zenos.iso
#qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom zenos.iso
qemu-system-x86_64 -cpu qemu64 -cdrom zenos.iso
