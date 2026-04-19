#include <stdlib.h>
#include <string.h>

#include "clavesRPC.h"
#include "claves.h"


bool_t destroy_1_svc(int *result, struct svc_req *rqstp) {
    *result = destroy();
    return TRUE;
}

bool_t set_value_1_svc(struct params args, int *result,  struct svc_req *rqstp) {
    /* Creamos la estructura Paquete y le pasamos los valores */
    struct Paquete p = {args.value3.x, args.value3.y, args.value3.z};

    /* Llamamos a set_value */
    *result = set_value(args.key, args.value1, args.N_value2, args.V_value2.float_array_val, p);

    return TRUE;
}

bool_t get_value_1_svc(char *key, struct get_value_res *res,  struct svc_req *rqstp) {
    /* Declaramos nuestros datos */
    char v1[256]; int n2; float v2[32]; struct Paquete v3;

    /* Guardamos en result el resultado de llamar a la función */
    res->result = get_value(key, v1, &n2, v2, &v3);
    if (res->result == 0) {
        /* Si hubo éxito, guardamos los valores obtenidos */
        res->value1 = strdup(v1);
        res->N_value2 = n2;
        res->V_value2.float_array_len = n2;
        res->V_value2.float_array_val = malloc(n2 * sizeof(float));

        /* Bucle para almacenar los float */
        for (int i = 0; i < n2; i++){
                res->V_value2.float_array_val[i] = v2[i];
            }
        
        /* Almacenamos los valores de las variables del struct Paquete */
        res->value3.x = v3.x; 
        res->value3.y = v3.y; 
        res->value3.z = v3.z;

    } else {
        /* Si no se encontró, asignamos valores nulos */
        res->value1 = "";
        res->V_value2.float_array_len = 0;
        res->V_value2.float_array_val = NULL;
    }

    return TRUE;
}

bool_t modify_value_1_svc(struct params args, int *result,  struct svc_req *rqstp) {
    /* Creamos la estructura Paquete y le pasamos los valores */
    struct Paquete p = {args.value3.x, args.value3.y, args.value3.z};

    /* Llamamos a modify_value */
    *result = modify_value(args.key, args.value1, args.N_value2, args.V_value2.float_array_val, p);
    return TRUE;
}

bool_t delete_key_1_svc(char *key, int *result,  struct svc_req *rqstp) {
    *result = delete_key(key);
    return TRUE;
}

bool_t exist_1_svc(char *key, int *result, struct svc_req *rqstp) {
    *result = exist(key);
    return TRUE;
}

int claves_rpc_1_freeresult(SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result) {
    xdr_free(xdr_result, result);
    return 1;
}