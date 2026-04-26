CC = gcc
CFLAGS = -Wall -I. -fPIC -I/usr/include/tirpc
LDLIBS = -ltirpc -lnsl -lpthread

all: clavesRPC_server cliente1 cliente2

# Archivos de soporte RPC
clavesRPC.h: clavesRPC.x
	rpcgen -NM clavesRPC.x

# Biblioteca claves
libclaves.so: claves.c claves.h
	$(CC) $(CFLAGS) -shared -o libclaves.so claves.c -lpthread

# Biblioteca proxy
libproxyclaves.so: proxy-rpc.c clavesRPC.h
	$(CC) $(CFLAGS) -shared -o libproxyclaves.so proxy-rpc.c clavesRPC_clnt.c clavesRPC_xdr.c

# Servidor
clavesRPC_server: clavesRPC.h libclaves.so clavesRPC_server.c
	$(CC) $(CFLAGS) clavesRPC_server.c clavesRPC_svc.c clavesRPC_xdr.c -o clavesRPC_server -L. -lclaves -Wl,-rpath=. $(LDLIBS)

# Clientes
cliente1: app-cliente-1.c libproxyclaves.so
	$(CC) $(CFLAGS) app-cliente-1.c -o cliente1 -L. -lproxyclaves -Wl,-rpath=. $(LDLIBS)

cliente2: app-cliente-2.c libproxyclaves.so
	$(CC) $(CFLAGS) app-cliente-2.c -o cliente2 -L. -lproxyclaves -Wl,-rpath=. $(LDLIBS)

clean:
	rm -f *.o *.so clavesRPC_server cliente1 cliente2 clavesRPC.h clavesRPC_clnt.c clavesRPC_svc.c clavesRPC_xdr.c Makefile.clavesRPC