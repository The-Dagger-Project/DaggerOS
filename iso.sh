#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/myos.kernel isodir/boot/myos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "DaggerOS" {
	multiboot /boot/myos.kernel
}

menuentry "System Shutdown" {
	echo "System shutting down..."
	halt
}

menuentry "System Restart" {
	echo "System rebooting..."
	reboot
}
EOF
grub-mkrescue -o dagger.iso isodir
