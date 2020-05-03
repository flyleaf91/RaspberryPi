all:
	dtc -O dtb -o rpi-pn532.dtbo rpi-pn532-overlay.dts

clean:
	rm rpi-pn532.dtbo

install:
	sudo cp rpi-pn532.dtbo /boot/overlays/
