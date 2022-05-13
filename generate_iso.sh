#!/usr/bin/env sh
mkdir -pv isodir/boot/grub
cp -v src/kernel/spark.bin isodir/boot/spark.bin
ls isodir/boot
echo 'set timeout=0
set default=0
menuentry "spark++" {
	multiboot /boot/spark.bin
}' > isodir/boot/grub/grub.cfg
grub-mkrescue -o spark.iso isodir
rm -rfv isodir
