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

menuentry "System shutdown" {
	echo "System shutting down..."
	halt
}

menuentry "System restart" {
	echo "System rebooting..."
	reboot
}

if [ ${grub_platform} == "efi" ]; then
	menuentry "Firmware setup" {
		fwsetup
	}
fi
EOF
grub-mkrescue -o dagger.iso isodir
