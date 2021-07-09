#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/myos.kernel isodir/boot/myos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
set timeout=60
set default=0

set menu_color_normal=blue/black
set menu_color_highlight=white/blue

function cpu_props {
	echo "GRUB's ability to analyse processors is limited, we can ask:"
	echo " * is it 64/32bit?"
	echo " * does it support Physical Address Extension (PAE)?"
	if cpuid -p; then
		pae_assessment="Yes"
	else
		pae_assessment="No"
	fi
    echo ""
	if cpuid -l; then
        echo "(O<"
        echo "(/)_ .: Processor: 64bit, PAE: $pae_assessment"
	else
        echo "(O<"
        echo "(/)_ .: Processor: 32bit, PAE: $pae_assessment"
	fi
}

menuentry "DaggerOS" {
	multiboot /boot/myos.kernel
}

menuentry "Tell Me About This Machine's Processor" {
	cpu_props
	echo $"Press escape to return to the main menu"
	sleep --interruptible 9999
}

menuentry "Reboot" {
    reboot
}

menuentry "Shut Down" {
	halt
}
EOF
grub-mkrescue -o dagger.iso isodir
