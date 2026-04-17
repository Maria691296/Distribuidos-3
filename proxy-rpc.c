#include "claves.h"
#include "clavesRPC.h"
#include <rpc/rpc.h>


/* Variable para el cliente */
static CLIENT *clnt = NULL;

/* Función interna para obtener el cliente RPC usando la IP de entorno */
static int init_rpc() {
    if (clnt != NULL) return 0; // Ya inicializado

    char *ip = getenv("IP_TUPLAS");
    if (ip == NULL) return -1;

    clnt = clnt_create(ip, CLAVES_RPC, CLAVES_VER, "tcp");
    if (clnt == NULL) return -1; // Error de sistema RPC 
    
    return 0;
}

int destroy(void) {
    if (init_rpc() != 0){
        return -1;
    }

    int *result;
    char *dummy;

    /* Llamada al stub */
    result = destroy_1((void *)&dummy, clnt);

    if (result == NULL) {
        return -1;
    }

    return *result;

}

int set_value(char *key, char *value1, int N_value2, float *V_value2, struct Paquete value3) {
    if (init_rpc() != 0){
        return -1;
    }

    struct params args; // El struct definido en clavesRPC.x
    int *result;

    /* Copiamos los datos locales a la estructura RPC */
    args.key = key;
    args.value1 = value1;
    args.N_value2 = N_value2;
    
    /* Para los arrays variables, rpcgen crea campos _len y _val */
    args.V_value2.V_value2_len = N_value2;
    args.V_value2.V_value2_val = V_value2;
    
    /* Copiamos el paquete */
    args.value3.x = value3.x;
    args.value3.y = value3.y;
    args.value3.z = value3.z;

    /* Llamada al stub */
    result = set_value_1(&args, clnt);

    if (result == NULL){
        return -1; // Error en la comunicación RPC 
    }

    return *result;
}

int get_value(char *key, char *value1, int *N_value2, float *V_value2, struct Paquete *value3) {
    if (init_rpc() != 0){
        return -1;
    }

    struct get_value_res *res;
    res = get_value_1(&key, clnt); // Enviamos solo la key 

    if (res == NULL){
        return -1;
    }
    
    if (res->result == 0) {
        /* Copiamos la respuesta del servidor a los parámetros de salida */
        strcpy(value1, res->value1);
        *N_value2 = res->N_value2;
        memcpy(V_value2, res->V_value2.V_value2_val, res->N_value2 * sizeof(float));
        
        value3->x = res->value3.x;
        value3->y = res->value3.y;
        value3->z = res->value3.z;
    }

    /* Llamada al stub */
    result = modify_value_1(&args, clnt);


    return res->result;
}

int modify_value(char *key, char *value1, int N_value2, float *V_value2, struct Paquete value3) {
    if (init_rpc() != 0){
        return -1;
    }

    struct params args; // El struct definido en clavesRPC.x
    int *result;

    /* Copiamos los datos locales a la estructura RPC */
    args.key = key;
    args.value1 = value1;
    args.N_value2 = N_value2;
    
    /* Para los arrays variables, rpcgen crea campos _len y _val */
    args.V_value2.V_value2_len = N_value2;
    args.V_value2.V_value2_val = V_value2;
    
    /* Copiamos el paquete */
    args.value3.x = value3.x;
    args.value3.y = value3.y;
    args.value3.z = value3.z;

    /* Llamamos al stub */
    result = modify_value_1(&args, clnt);

    if (result == NULL){
        return -1; // Error en la comunicación RPC 
    }

    return *result;

}

int delete_key(char *key) {
    if (init_rpc() != 0){
        return -1;
    }

    int *result;

    result = get_value_1(&key, clnt); // Enviamos solo la key

    if (result == NULL){
        return -1; // Error en la comunicación RPC 
    }

    return *result;

}

int exist(char *key) {
    if (init_rpc() != 0){
        return -1;
    }

    int *result;

    result = get_value_1(&key, clnt); // Enviamos solo la key

    if (result == NULL){
        return -1; // Error en la comunicación RPC 
    }

    return *result;

}
