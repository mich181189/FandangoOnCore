obj-m += fandango.o

all:
	make -C /lib/modules/3.0.0-19-generic/build M=$(PWD) modules

clean:
	make -C /lib/modules/3.0.0-19-generic/build M=$(PWD) clean
