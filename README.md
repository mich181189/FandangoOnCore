FandangoOnCore
==============

Make crashes more spectacular!

In this version, upon loading it picks a random pointer and writes random data for 1kb. In the VM I tested this on, it locks up reliably.

In the future, the idea is to have it callable from user mode code to allow any application to take down the system

Thus making crashes MUCH more spectacular.


...Yeah, don't run this!