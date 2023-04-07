#include <string.h>
#include "sqlite3.h"
#include "md5.h"
#include "gestorBD.h"

sqlite3 *abrirConexion()
{
    sqlite3 *db;
    char *archivo = "BaseDatos.db";
    sqlite3_open(archivo, &db);
    return db;
}


/*
Funcion para crear usuarios en la base de datos
Input
    usuraio: Nombre de usuario
    pass: Contraseña sin hashear
Output
    1: El usuario se ha insertado correctamente
    -1: Error en el prepared statement
    -2: Error en el insert
*/
int insertarUsuario(char *usuario, char *pass)
{
    uint8_t hashPass[16];
    md5String(pass, hashPass);

    sqlite3 *db = abrirConexion();
    sqlite3_stmt *preparedstmt;
    char *query = "INSERT INTO Usuarios(usuario,password) VALUES (?,?);";

    if (sqlite3_prepare(db, query, -1, &preparedstmt, 0) != SQLITE_OK)
    {
        printf("Error en el prepared statement : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }
    sqlite3_bind_text(preparedstmt,1,usuario, strlen(usuario) + 1, 0);
    sqlite3_bind_text(preparedstmt,2,hashPass, strlen(hashPass) + 1, 0);
    if (sqlite3_step(preparedstmt) != SQLITE_DONE)
    {
        printf("Error al ejecutar el insert : %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(preparedstmt);
        sqlite3_close(db);
        return -2;
    }
    sqlite3_finalize(preparedstmt);
    sqlite3_close(db);
    return 1;
}

/*
Funcion para comprobar si un usuario existe en la base de datos. Si existe, comprueba si la contraseña coincida
Input
    usuraio: Nombre de usuario
    pass: Contraseña sin hashear
Output
    Numero positvo: El log in es correcto. El valor del número es el ID del usuario
    -1: Error en el prepared statement
    -2: No existe el usuario
    -3: No coincide la contraseña
*/
int logIn(char *usuario, char *pass)
{
    sqlite3 *db = abrirConexion();
    sqlite3_stmt *preparedstmt;
    char *query = sqlite3_mprintf("SELECT id,password FROM usuarios WHERE usuario='%s';", usuario);
    if (sqlite3_prepare(db, query, -1, &preparedstmt, 0) != SQLITE_OK)
    {
        printf("Error en el prepared statement : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }
    if (sqlite3_step(preparedstmt) != SQLITE_ROW)
    {
        printf("No se ha encontrado ningun usuario con el usuario %s \n", usuario);
        sqlite3_finalize(preparedstmt);
        sqlite3_close(db);
        return -2;
    }
    uint8_t hashPass[16];
    md5String(pass, hashPass);
    printf("%s - %s\n",(char *)hashPass,sqlite3_column_text(preparedstmt,1));
    if(strcmp(hashPass,sqlite3_column_text(preparedstmt,1))==0){
        sqlite3_finalize(preparedstmt);
        sqlite3_close(db);
        return sqlite3_column_int(preparedstmt,0);
    }
    sqlite3_finalize(preparedstmt);
    sqlite3_close(db);
    return -3;
}

/*
Se borra el usuio con la ID pasada en el argumento
Input
    userID: ID del usuario a borrar
Output
    1: Usuario borrado correctamente
    -1: Error en el prepared statement
    -2: No existe el usuario
*/
int deleteUser(int userID){
    sqlite3 *db = abrirConexion();
    sqlite3_stmt *preparedstmt;
    char *query = sqlite3_mprintf("DELETE FROM usuarios WHERE id=%d;", userID);
    if (sqlite3_prepare(db, query, -1, &preparedstmt, 0) != SQLITE_OK)
    {
        printf("Error en el prepared statement : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }
    if (sqlite3_step(preparedstmt) != SQLITE_DONE)
    {
        printf("Error al ejecutar el insert : %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(preparedstmt);
        sqlite3_close(db);
        return -2;
    }
    sqlite3_finalize(preparedstmt);
    sqlite3_close(db);
    return 1;
}
