/* Antes de comenzar vamos a definir los diferentes paquetes necesarios */

/* Estructura paquete */
struct p_paquete {
   int x ;
   int y ;
   int z ;
} ;

/* Definimos el array de float */
typedef float float_array<32>;

/* Estructura para poder pasar los parámetros correctamente */
struct params {
    string key<255>;
    string value1<255>;  
    int N_value2; 
    float_array V_value2; 
    struct p_paquete value3;
};

/* Estructura para devolver la respuesta de get_value */
struct get_value_res {
    int result;             /* El resultado es 0 o -1 */
    string value1<255>;  
    int N_value2; 
    float_array V_value2; 
    struct p_paquete value3;
};

/* Programa para crear los stubs */
program CLAVES_RPC {
    version CLAVES_VER {
        int DESTROY(void) = 1;
        
        int SET_VALUE(struct params) = 2;
        
        struct get_value_res GET_VALUE(string key<256>) = 3;
        
        int MODIFY_VALUE(struct params) = 4;
        
        int DELETE_KEY(string key<256>) = 5;
        
        int EXIST(string key<256>) = 6;
    } = 1;
} = 99;
