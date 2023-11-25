#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include "DatosConexion.h"

#define TAM_CADENA 100

#define QUERY_INSERTAR_PACIENTE "INSERT INTO paciente(codigo_historia_clinica, nombre_paciente, apellido_paciente, telefono,  sexo, ciudad, documento_identidad) VALUES(?,?,?,?,?,?,?)"
#define QUERY_ACTUALIZAR_PACIENTE "UPDATE paciente SET telefono = ? WHERE codigo_historia_clinica = ?"
#define QUERY_ELIMINAR_PACIENTE "DELETE FROM paciente WHERE codigo_historia_clinica = ?"
#define QUERY_MOSTRAR_PACIENTE "SELECT * FROM paciente"

#define QUERY_INSERTAR_MEDICO "INSERT INTO medico(codigo_medico, nombre, apellido, especialidad,  tarjeta_profesional) VALUES(?,?,?,?,?)"
#define QUERY_ACTUALIZAR_MEDICO "UPDATE medico SET  tarjeta_profesional = ? WHERE codigo_medico = ?"
#define QUERY_ELIMINAR_MEDICO "DELETE FROM medico WHERE codigo_medico = ?"
#define QUERY_MOSTRAR_MEDICO "SELECT * FROM medico"

#define QUERY_INSERTAR_INGRESO "INSERT INTO ingreso(codigo_ingreso, codigo_historia_clinica, codigo_medico, fecha_ingreso,no_piso,no_cama,diagnostico,costo_tratamiento) VALUES(?,?,?,?,?,?,?,?)"
#define QUERY_ACTUALIZAR_INGRESO "UPDATE ingreso SET no_cama = ? WHERE codigo_ingreso = ?"
#define QUERY_ELIMINAR_INGRESO "DELETE FROM ingreso WHERE codigo_ingreso = ?"
#define QUERY_MOSTRAR_INGRESO "SELECT * FROM ingreso"

void mostrarTabla(MYSQL *conexion, char *consulta) {
    int error, filas, columnas, i, j;
    MYSQL_RES *res_ptr;
    MYSQL_FIELD *campo;
    MYSQL_ROW res_fila;

    error = mysql_query(conexion, consulta);

    if (!error) {
        res_ptr = mysql_store_result(conexion);

        if (res_ptr) {
            filas = mysql_num_rows(res_ptr);
            columnas = mysql_num_fields(res_ptr);

            while (campo = mysql_fetch_field(res_ptr)) {
                printf("%-15s", campo->name);
            }
            printf("\n");

            for (i = 1; i <= filas; i++) {
                res_fila = mysql_fetch_row(res_ptr);

                for (j = 0; j < columnas; j++) {
                    printf("%-15s", res_fila[j]);
                }
                printf("\n");
            }
        } else {
            printf("Error al obtener resultado\n");
        }
    } else {
        printf("Ocurrió un error al ejecutar la consulta SQL\n");
    }
}


int conectar(MYSQL **conexion);
int menu();
int main(int argc, char *argv[]){
int error_conexion, id, id_res, columnas;
unsigned long length[7];
int codigo_ingreso, codigo_historia_clinica,codigo_medico ;

char nombre_paciente[TAM_CADENA],apellido_paciente[TAM_CADENA],
telefono[TAM_CADENA],documento_identidad[TAM_CADENA], sexo[TAM_CADENA],
 ciudad[TAM_CADENA], nombre[TAM_CADENA], apellido[TAM_CADENA], 
 especialidad[TAM_CADENA], fecha_ingreso[TAM_CADENA],  
 diagnostico[TAM_CADENA],tarjeta_profesional[TAM_CADENA], 
 no_piso[TAM_CADENA], no_cama[TAM_CADENA], costo_tratamiento[TAM_CADENA];

bool is_null[7], error[7]; 
   
    MYSQL *conexion;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[7];
	MYSQL_RES *res_ptr;
	MYSQL_FIELD *campo;
    error_conexion = conectar(&conexion);

int op, op2, op3;
    if (!error_conexion) {
    	stmt = mysql_stmt_init(conexion);
    	if(stmt){
    		    switch (menu()) {
        case 1: // PACIENTE
        
            do {
                //int op;
                printf("\n--- Operaciones en la tabla 'paciente' ---\n");
                printf("1- Insertar\n");
                printf("2- Actualizar\n");
                printf("3- Eliminar\n");
                printf("4- Mostrar\n");
                printf("5- Salir\n");
                printf("Ingrese opcion: ");
                scanf("%d", &op);
				
                switch (op) {
                    		case 1: //INSERTAR
					if(!mysql_stmt_prepare(stmt, QUERY_INSERTAR_PACIENTE, strlen(QUERY_INSERTAR_PACIENTE))){
						memset(bind, 0, sizeof (bind));
						bind[0].buffer_type = MYSQL_TYPE_LONG;
						bind[0].buffer = (int *) &codigo_historia_clinica;
						bind[0].is_null = 0;
						bind[0].length = 0;
						
						bind[1].buffer_type = MYSQL_TYPE_STRING;
						bind[1].buffer = (char *) nombre_paciente;
						bind[1].buffer_length = TAM_CADENA;
						bind[1].is_null = 0;
						bind[1].length = &length[1];
						
						bind[2].buffer_type = MYSQL_TYPE_STRING;
						bind[2].buffer = (char *) apellido_paciente;
						bind[2].buffer_length = TAM_CADENA;
						bind[2].is_null=0;
						bind[2].length = &length[2];
												
						bind[3].buffer_type = MYSQL_TYPE_STRING;
						bind[3].buffer = (char *) &telefono;
						bind[3].buffer_length = TAM_CADENA;
						bind[3].is_null=0;
						bind[3].length = &length[3];
												
						bind[4].buffer_type = MYSQL_TYPE_STRING;
						bind[4].buffer = (char *) sexo;
						bind[4].buffer_length = TAM_CADENA;
						bind[4]. is_null = 0;
						bind[4]. length = &length[4];
						
						bind[5].buffer_type = MYSQL_TYPE_STRING;
						bind[5].buffer = (char *) ciudad;
						bind[5].buffer_length = TAM_CADENA;
						bind[5]. is_null = 0;
						bind[5]. length = &length[5];
						
						bind[6].buffer_type = MYSQL_TYPE_STRING;
						bind[6].buffer = (char *) documento_identidad;
						bind[6].buffer_length = TAM_CADENA;
						bind[6]. is_null = 0;
						bind[6]. length = &length[6];
						
						if (!mysql_stmt_bind_param(stmt, bind)){
							printf("Ingrese nombre: "); scanf("%s", &nombre_paciente);
							length[1] = strlen(nombre_paciente);
							printf("Ingrese apellido: "); scanf("%s", &apellido_paciente);
							length[2] = strlen(apellido_paciente);
					     	printf("Ingrese telefono: "); scanf("%s", &telefono);
							length[3] = strlen(telefono);
							printf("Ingrese sexo (M/F): "); scanf("%s", &sexo);
							length[4] = strlen(sexo);
							printf("Ingrese nombre de la ciudad: "); scanf("%s", &ciudad);
							length[5] = strlen(ciudad);
							printf("Ingrese documento_identidad: "); scanf("%s", &documento_identidad);
							length[6] = strlen(documento_identidad);
							if(!mysql_stmt_execute(stmt)){
								if(mysql_stmt_affected_rows(stmt) > 0)
										printf("Registro Insertado exitosamente\n");
								else
										printf("Error al insertar registro\n");
								mysql_stmt_close(stmt);
							}
						}
						else
							printf("Error al asociar los parametros a la sentencia preparada. \n");
					}else
						printf("Error al preparar la sentencia. \n");
					break;
				case 2://ACTUALIZAR
					if (!mysql_stmt_prepare(stmt, QUERY_ACTUALIZAR_PACIENTE, strlen (QUERY_ACTUALIZAR_PACIENTE))){
						memset(bind, 0, sizeof(bind));
						bind[0].buffer_type = MYSQL_TYPE_STRING;
						bind[0].buffer = (char *) telefono;
						bind[0].buffer_length = TAM_CADENA;
						bind[0].is_null = 0;
						bind[0].length = &length[0];						
						bind[1].buffer_type = MYSQL_TYPE_LONG;
						bind[1].buffer = (int *) &codigo_historia_clinica;
						bind[1].is_null = 0;
						bind[1].length = 0;
						if (!mysql_stmt_bind_param(stmt, bind)){
							printf("Ingrese codigo_historia_clinica: "); scanf("%d", &codigo_historia_clinica);
							printf("Ingrese telefono: "); scanf("%s", &telefono);
							length[0] = strlen(telefono);
							if(!mysql_stmt_execute(stmt)){
								if (mysql_stmt_affected_rows(stmt) > 0)
									printf("Registro actualizado exitosamente\n");
								else
									printf("Error al actualizar registro\n");
								mysql_stmt_close(stmt); 
							}
						}
						else
							printf("Error al asociar los parametros a la sentencia preparada.\n");
				}
				else
					printf("Error al preparar la sentencia. \n");
				break;	    
					case 3://eliminar
						if(!mysql_stmt_prepare(stmt, QUERY_ELIMINAR_PACIENTE, strlen(QUERY_ELIMINAR_PACIENTE) )){
							memset (bind, 0, sizeof(bind));
							bind[0].buffer_type = MYSQL_TYPE_LONG;
							bind[0].buffer = (int *) &codigo_historia_clinica;
							bind[0].is_null = 0;
							bind[0].length = 0;
							if (!mysql_stmt_bind_param(stmt, bind)){
								printf("Ingrese codigo_historia_clinica: "); scanf("%d", &codigo_historia_clinica);
								if(!mysql_stmt_execute(stmt)){
									if (mysql_stmt_affected_rows(stmt) > 0)
										printf("Registro eliminado exitosamente\n");
									else
										printf("Error al eliminar registro\n");
									mysql_stmt_close(stmt); 
							}
					}
					else
						printf("Error al asociar los parametros a la sentencia preparada. \n");
                }else
						printf("Error al preparar la sentencia. \n");
				break;
						
                    case 4:
                        // Mostrar tabla paciente
                   mostrarTabla(conexion, QUERY_MOSTRAR_PACIENTE);	
						                                                               
                    case 5:					                                                               
                        break; // Salir del submenú
                    default:
                        printf("Opcion incorrecta\n");
                         
                }
               
            }  while (op != 5);  
	
    
    return menu();

        case 2: // MEDICO
            do {
            	
                printf("\n--- Operaciones en la tabla 'medico' ---\n");
                printf("1- Insertar\n");
                printf("2- Actualizar\n");
                printf("3- Eliminar\n");
                printf("4- Mostrar\n");
                printf("5- Salir\n");
                printf("Ingrese opcion: ");
                scanf("%d", &op2);
		
                switch (op2) {
                    		case 1: //INSERTAR
					if(!mysql_stmt_prepare(stmt, QUERY_INSERTAR_MEDICO, strlen(QUERY_INSERTAR_MEDICO))){
						memset(bind, 0, sizeof (bind));
						bind[0].buffer_type = MYSQL_TYPE_LONG;
						bind[0].buffer = (int *) &codigo_medico;
						bind[0].is_null = 0;
						bind[0].length = 0;
						
						bind[1].buffer_type = MYSQL_TYPE_STRING;
						bind[1].buffer = (char *) nombre;
						bind[1].buffer_length = TAM_CADENA;
						bind[1].is_null = 0;
						bind[1].length = &length[1];
						
						bind[2].buffer_type = MYSQL_TYPE_STRING;
						bind[2].buffer = (char *) apellido;
						bind[2].buffer_length = TAM_CADENA;
						bind[2].is_null=0;
						bind[2].length = &length[2];
												
						bind[3].buffer_type = MYSQL_TYPE_STRING;
						bind[3].buffer = (char *) &especialidad;
						bind[3].buffer_length = TAM_CADENA;
						bind[3].is_null=0;
						bind[3].length = &length[3];
												
						bind[4].buffer_type = MYSQL_TYPE_STRING;
						bind[4].buffer = (char *) tarjeta_profesional;
						bind[4].buffer_length = TAM_CADENA;
						bind[4]. is_null = 0;
						bind[4]. length = &length[4];
					
						
						if (!mysql_stmt_bind_param(stmt, bind)){
							printf("Ingrese nombre: "); scanf("%s", &nombre);
							length[1] = strlen(nombre);
							printf("Ingrese apellido: "); scanf("%s", &apellido);
							length[2] = strlen(apellido);
					     	printf("Ingrese especialidad: "); scanf("%s", &especialidad);
							length[3] = strlen(especialidad);
							printf("Ingrese tarjeta profesional: "); scanf("%s", &tarjeta_profesional);
							length[4] = strlen(tarjeta_profesional);
					
							if(!mysql_stmt_execute(stmt)){
								if(mysql_stmt_affected_rows(stmt) > 0)
										printf("Registro Insertado exitosamente\n");
								else
										printf("Error al insertar registro\n");
								mysql_stmt_close(stmt);
							}
						}
						else
							printf("Error al asociar los parametros a la sentencia preparada. \n");
					}else
						printf("Error al preparar la sentencia. \n");
					break;
				case 2://ACTUALIZAR
					if (!mysql_stmt_prepare(stmt, QUERY_ACTUALIZAR_MEDICO, strlen (QUERY_ACTUALIZAR_MEDICO))){
						memset(bind, 0, sizeof(bind));
						bind[0].buffer_type = MYSQL_TYPE_STRING;
						bind[0].buffer = (char *) tarjeta_profesional;
						bind[0].buffer_length = TAM_CADENA;
						bind[0].is_null = 0;
						bind[0].length = &length[0];						
						bind[1].buffer_type = MYSQL_TYPE_LONG;
						bind[1].buffer = (int *) &codigo_medico;
						bind[1].is_null = 0;
						bind[1].length = 0;
						if (!mysql_stmt_bind_param(stmt, bind)){
							printf("Ingrese codigo medico: "); scanf("%d", &codigo_medico);
							printf("Ingrese tarjeta profesional: "); scanf("%s", &tarjeta_profesional);
							length[0] = strlen(tarjeta_profesional);
							if(!mysql_stmt_execute(stmt)){
								if (mysql_stmt_affected_rows(stmt) > 0)
									printf("Registro actualizado exitosamente\n");
								else
									printf("Error al actualizar registro\n");
								mysql_stmt_close(stmt); 
							}
						}
						else
							printf("Error al asociar los parametros a la sentencia preparada.\n");
				}
				else
					printf("Error al preparar la sentencia. \n");
				break;	    
					case 3://eliminar
						if(!mysql_stmt_prepare(stmt, QUERY_ELIMINAR_MEDICO, strlen(QUERY_ELIMINAR_MEDICO) )){
							memset (bind, 0, sizeof(bind));
							bind[0].buffer_type = MYSQL_TYPE_LONG;
							bind[0].buffer = (int *) &codigo_medico;
							bind[0].is_null = 0;
							bind[0].length = 0;
							if (!mysql_stmt_bind_param(stmt, bind)){
								printf("Ingrese codigo medico: "); scanf("%d", &  codigo_medico);
								if(!mysql_stmt_execute(stmt)){
									if (mysql_stmt_affected_rows(stmt) > 0)
										printf("Registro eliminado exitosamente\n");
									else
										printf("Error al eliminar registro\n");
									mysql_stmt_close(stmt); 
							}
					}
					else
						printf("Error al asociar los parametros a la sentencia preparada. \n");
                }else
						printf("Error al preparar la sentencia. \n");
				break;
						
                    case 4:
                        // Mostrar tabla paciente
                        mostrarTabla(conexion, QUERY_MOSTRAR_MEDICO);
                        break;
                    case 5:
                        break; // Salir del submenú
                    default:
                        printf("Opcion incorrecta\n");
                         
                }
            } 
			while (op2 != 5);  
	
					

    
    return menu();

        case 3: // INGRESO
            do {
            	
                printf("\n--- Operaciones en la tabla 'ingreso' ---\n");
                printf("1- Insertar\n");
                printf("2- Actualizar\n");
                printf("3- Eliminar\n");
                printf("4- Mostrar\n");
                printf("5- Salir\n");
                printf("Ingrese opcion: ");
                scanf("%d", &op3);

                switch (op3) {
                    		case 1: //INSERTAR
					if(!mysql_stmt_prepare(stmt, QUERY_INSERTAR_INGRESO, strlen(QUERY_INSERTAR_INGRESO))){
						memset(bind, 0, sizeof (bind));
						bind[0].buffer_type = MYSQL_TYPE_LONG;
						bind[0].buffer = (int *) &codigo_ingreso;
						bind[0].is_null = 0;
						bind[0].length = 0;
						
						bind[1].buffer_type = MYSQL_TYPE_STRING;
						bind[1].buffer = (char *)  fecha_ingreso;
						bind[1].buffer_length = TAM_CADENA;
						bind[1].is_null = 0;
						bind[1].length = &length[1];
						
						bind[2].buffer_type = MYSQL_TYPE_STRING;
						bind[2].buffer = (char *) no_piso;
						bind[2].buffer_length = TAM_CADENA;
						bind[2].is_null=0;
						bind[2].length = &length[2];
												
						bind[3].buffer_type = MYSQL_TYPE_STRING;
						bind[3].buffer = (char *) no_cama;
						bind[3].buffer_length = TAM_CADENA;
						bind[3].is_null=0;
						bind[3].length = &length[3];
												
						bind[4].buffer_type = MYSQL_TYPE_STRING;
						bind[4].buffer = (char *) diagnostico;
						bind[4].buffer_length = TAM_CADENA;
						bind[4]. is_null = 0;
						bind[4]. length = &length[4];
						
						bind[5].buffer_type = MYSQL_TYPE_STRING;
						bind[5].buffer = (char *) costo_tratamiento;
						bind[5].buffer_length = TAM_CADENA;
						bind[5]. is_null = 0;
						bind[5]. length = &length[5];
						
						
						if (!mysql_stmt_bind_param(stmt, bind)){
							printf("Ingrese fecha de ingreso: "); scanf("%s", &fecha_ingreso);
							length[1] = strlen(fecha_ingreso);
							printf("Ingrese Numero de piso: "); scanf("%s", &no_piso);
							length[2] = strlen(no_piso);
					     	printf("Ingrese Numero de cama: "); scanf("%s", &no_cama);
							length[3] = strlen(no_cama);
							printf("Ingrese sexo (M/F): "); scanf("%s", &sexo);
							length[4] = strlen(sexo);
							printf("Ingrese nombre de diagnostico: "); scanf("%s", &diagnostico);
							length[5] = strlen(diagnostico);
							printf("Ingrese Costo del tratamiento: "); scanf("%s", &costo_tratamiento);
							length[6] = strlen(costo_tratamiento);
							
							if(!mysql_stmt_execute(stmt)){
								if(mysql_stmt_affected_rows(stmt) > 0)
										printf("Registro Insertado exitosamente\n");
								else
										printf("Error al insertar registro\n");
								mysql_stmt_close(stmt);
							}
						}
						else
							printf("Error al asociar los parametros a la sentencia preparada. \n");
					}else
						printf("Error al preparar la sentencia. \n");
					break;
				case 2://ACTUALIZAR
					if (!mysql_stmt_prepare(stmt, QUERY_ACTUALIZAR_INGRESO, strlen (QUERY_ACTUALIZAR_INGRESO))){
						memset(bind, 0, sizeof(bind));
						bind[0].buffer_type = MYSQL_TYPE_STRING;
						bind[0].buffer = (char *) no_cama;
						bind[0].buffer_length = TAM_CADENA;
						bind[0].is_null = 0;
						bind[0].length = &length[0];						
						bind[1].buffer_type = MYSQL_TYPE_LONG;
						bind[1].buffer = (int *) &codigo_historia_clinica;
						bind[1].is_null = 0;
						bind[1].length = 0;
						if (!mysql_stmt_bind_param(stmt, bind)){
							printf("Ingrese codigo_historia_clinica: "); scanf("%d", &codigo_historia_clinica);
							printf("Ingrese numero de cama: "); scanf("%s", &no_cama);
							length[0] = strlen(no_cama);
							if(!mysql_stmt_execute(stmt)){
								if (mysql_stmt_affected_rows(stmt) > 0)
									printf("Registro actualizado exitosamente\n");
								else
									printf("Error al actualizar registro\n");
								mysql_stmt_close(stmt); 
							}
						}
						else
							printf("Error al asociar los parametros a la sentencia preparada.\n");
				}
				else
					printf("Error al preparar la sentencia. \n");
				break;	    
					case 3://eliminar
						if(!mysql_stmt_prepare(stmt, QUERY_ELIMINAR_INGRESO, strlen(QUERY_ELIMINAR_INGRESO) )){
							memset (bind, 0, sizeof(bind));
							bind[0].buffer_type = MYSQL_TYPE_LONG;
							bind[0].buffer = (int *) &codigo_historia_clinica;
							bind[0].is_null = 0;
							bind[0].length = 0;
							if (!mysql_stmt_bind_param(stmt, bind)){
								printf("Ingrese codigo_historia_clinica: "); scanf("%d", &codigo_historia_clinica);
								if(!mysql_stmt_execute(stmt)){
									if (mysql_stmt_affected_rows(stmt) > 0)
										printf("Registro eliminado exitosamente\n");
									else
										printf("Error al eliminar registro\n");
									mysql_stmt_close(stmt); 
							}
					}
					else
						printf("Error al asociar los parametros a la sentencia preparada. \n");
                }else
						printf("Error al preparar la sentencia. \n");
				break;
						
                    case 4:
                        // Mostrar tabla ingreso
                        mostrarTabla(conexion, QUERY_MOSTRAR_INGRESO);
                        break;
                    case 5:
                        break; // Salir del submenú
                    default:
                        printf("Opcion incorrecta\n");
                         
                }
            } while (op3 != 5);  
	
   return menu();
}

   
} 
 	
}
}
int conectar(MYSQL **conexion) {
    int error;
    *conexion = mysql_init(NULL);

    if (mysql_real_connect(*conexion, HOST, USERNAME, PASSWORD, DATABASE, PORT, NULL, 0) != NULL) {
        printf("Se establecio la conexion con la base de datos\n");
        error = 0;
    } else {
        printf("Error al conectarse con la base de datos\n");
        error = 1;
    }

    return error;
}

int menu() {
    int opc;
    printf("\n---MENU PRINCIPAL---\n");
      printf("Porfavor escoja la tabla que desea modificar\n");
    printf("1- Paciente \n");
    printf("2- Medico\n");
    printf("3- Ingreso\n");
    printf("4- Salir\n");
    printf("Ingrese opcion: ");
    scanf("%d", &opc);
    return opc;
}
