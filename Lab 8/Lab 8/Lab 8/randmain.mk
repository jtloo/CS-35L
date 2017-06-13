randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) randlibhw.c -fpic -c -shared randlibhw.so

randlibsw.so: randlibsw.c
	$(CC) $(CFLAGS) randlibsw.c -fpic -c -shared randlibsw.so

randmain: randmain.o randcpuid.o
	$(CC) $(CFLAGS) randmain.o randcpuid.o -ldl -Wl -rpath=${PWD} -o randmain