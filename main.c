/*Se quiere crear una red Token Ring formada por N procesos, donde el valor de n se pasa como un 
argumento en la línea de comando (opción -n).
Cada proceso en el anillo se enlaza de forma unidireccional con su antecesor y su sucesor mediante 
un pipe. 
El proceso que crea el anillo genera un único carácter ('T') que hará de testigo.
Este testigo recorrerá el anillo indefinidamente de la siguiente forma:
cada proceso en el anillo espera la recepción del testigo;
cuando un proceso recibe el testigo lo conserva durante 5 segundos;
una vez transcurridos los 5 segundos, lo envía al siguiente proceso en el anillo.
Cada proceso debe mostrar:
Al recibir el testigo, el mensaje: “—-> Soy el proceso con PID <su_pid>  y recibí el testigo 
<testigo>, el cual tendré por 5 segundos”
Al pasar el testigo, el mensaje:  “<—- Soy el proceso con PID <su_pid>  y acabo de enviar el testigo 
<testigo>”
Donde:
<su_pid> debe sustituirse por el PID del proceso
<testigo> debe sustituirse por el caracter que recibe el proceso mediante el pipe. 
No se puede imprimir directamente el caracter 'T'. */

//Edgar Garcia A01021730
//En colaboacion con Rafael Diaz
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void proteccion(int, char);
void abandono(int, char);

int main(int argc, char const *argv[])
{
    int children = 0;
    if(argc > 1){
        children = atoi(argv[1]);
    } else{
        printf("Ingrese el número de procesos secundarios para ejecutar la próxima vez.\n");
        return -1;
    }
    // Procesos
    pid_t pid;
    int tuberia[2*children];
    // De esta forma se hacen pipes los espacios
    for (int i = 0; i < children; i++) {
        pipe(&tuberia[2*i]);
    } 
    // Generando T (testigo)
    char testigo = 'T';
    // Declarando char input
    char input;
    int i = 1;
    while (i <= children){
        pid = fork();
        if (pid == 0){
            //Hijos
            close(tuberia[(i*2 - 1)]);
            proteccion(tuberia[(i*2 - 1)], testigo);
            close(tuberia[(i*2)]);
            abandono(tuberia[(i*2)], testigo); 
        }else if (pid == -1){
            // Error al crear hijo
            printf("Hubo un error al crear proceso hijo. Numero de procesos hijos creados hasta ahora: %d\n", i + 1);
            break;
        }else{
            // Si es el primer proceso, el padre de todos
            if (i == 1){
                // Cerramos la primera tuberia
                close(tuberia[0]);
                write(tuberia[1], &testigo, sizeof(char));
                printf("Soy el proceso padre con PID = %d y envío '%c'\n", pid, testigo);
            }
            // Por cada hijo nuevo hacemos un break
            break;
        }
        i++;
    }
    // Cada padre espera a su hijo
    waitpid(pid, NULL, 0);
    return 0;
}
void proteccion(int tuberia, char input){
        read(tuberia, &input, sizeof(char));
        printf("—-> Soy el proceso con PID %d  y recibí el testigo '%c', el cual tendré por 5 segundos\n", getpid(), input);
        // Espera el 5 segundos
        sleep(5);
}

void abandono(int tuberia, char input){
    // Escribiendo en siguiente tuberia
        write(tuberia, &input, sizeof(char));
        printf("<—- Soy el proceso con PID %d y acabo de enviar el testigo '%c'\n", getpid(), input);
}