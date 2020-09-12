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
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>