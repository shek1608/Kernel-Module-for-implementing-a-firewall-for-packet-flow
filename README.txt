Linux Distribution - Linux Firewall 3.13.0-24-generic #46-Ubuntu SMP Thu Apr 10 19:11:08 UTC 2014 x86_64 x86_64 x86_64 GNU/Linux

Steps for kernel module:

1) Copy the hw6_firewall.c and Makefile into your local machine.

2) Login as the root user into the node to be used as firewall.

3) Copy the file from local machine to a directory in the firewall.

4)Run the command 'make' to build the kernel module.

5) Insert the kernel module into your kernel using the command, 'insmod hw6_firewall.ko'

6) To remove the kernel module, run 'rmmod hw6_firewall'.
	