// Solucion laboratorio 2
// Integrantes:
// Israel Velez Gonzalez
// Juan Esteban Ortiz

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <comando>\n", argv[0]);
        return 1;
    }

    struct timeval start, end;
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error al hacer fork");
        return 1;
    }

    if (pid == 0) { // Proceso hijo
        // Ejecutar el comando
        execvp(argv[1], &argv[1]);
        // Si execvp falla
        perror("Error al ejecutar el comando");
        exit(1);
    } else { // Proceso padre
        // Obtener el tiempo antes de que el hijo ejecute el comando
        gettimeofday(&start, NULL);
        
        // Esperar a que el proceso hijo termine
        wait(NULL);

        // Obtener el tiempo después de que el hijo termina
        gettimeofday(&end, NULL);

        // Calcular el tiempo transcurrido
        double elapsed = (end.tv_sec - start.tv_sec) + 
                         (end.tv_usec - start.tv_usec) / 1000000.0;

        printf("Elapsed time: %.5f seconds\n", elapsed);
    }

    return 0;
}
