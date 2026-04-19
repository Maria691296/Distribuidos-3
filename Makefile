CC = gcc
CFLAGS = -Wall -I. -fPIC -I/usr/include/tirpc
LDLIBS = -ltirpc -lnsl -lpthread

all: servidor_rpc cliente1 cliente2

# Archivos de soporte RPC
clavesRPC.h: clavesRPC.x
	rpcgen -aNM clavesRPC.x

# Biblioteca claves
libclaves.so: claves.c claves.h
	$(CC) $(CFLAGS) -shared -o libclaves.so claves.c

# Biblioteca proxy
libproxyclaves.so: proxy-rpc.c clavesRPC.h
	$(CC) $(CFLAGS) -shared -o libproxyclaves.so proxy-rpc.c clavesRPC_clnt.c clavesRPC_xdr.c

# Servidor
servidor_rpc: clavesRPC.h libclaves.so servidor.c
	$(CC) $(CFLAGS) servidor.c clavesRPC_svc.c clavesRPC_xdr.c -o servidor_rpc -L. -lclaves -Wl,-rpath=. $(LDLIBS)

# Clientes
cliente1: app-cliente-1.c libproxyclaves.so
	$(CC) $(CFLAGS) app-cliente-1.c -o cliente1 -L. -lproxyclaves -Wl,-rpath=. $(LDLIBS)

cliente2: app-cliente-2.c libproxyclaves.so
	$(CC) $(CFLAGS) app-cliente-2.c -o cliente2 -L. -lproxyclaves -Wl,-rpath=. $(LDLIBS)

clean:
	rm -f *.o *.so servidor_rpc cliente1 cliente2 clavesRPC.h clavesRPC_clnt.c clavesRPC_svc.c clavesRPC_xdr.c clavesRPC_server.c clavesRPC_client.c Makefile.clavesRPC