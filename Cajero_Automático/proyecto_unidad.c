#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
//variables globales
int tarjetas = 3;
int intentos = 3;
int retiro_limite = 500;
int billete_c1  = 20;
int billete_c2   = 10;
int billete_c3 = 5;
//prototipos
void inicializarCuentas(int numTarjetas[], int pines[], double saldos[], int n);
int  validarPin(int pines[], int pos, int maxIntentos);
void mostrarMenu(void);
void consultarSaldo(double saldos[], int pos);
void depositar(double saldos[], int pos);
void retirarDinero(double saldos[], int pos, int limite);
int  generadorDeBilletes(int monto, int *c20, int *c10, int *c5, int d20, int d10, int d5);
void animacionEspera(void);
void limpiarPantalla(void);
void pausar(void);
//funcion principal
int main(void)
{
    srand((unsigned int)time(NULL));

    int numTarjetas[3];
    int pines[3];
    double saldos[3];
    int continuar = 1;

    inicializarCuentas(numTarjetas, pines, saldos, tarjetas);
    int numTarjeta, pos, opcion;

    do {
        limpiarPantalla();
        printf("CAJERO AUTOMATICO\n");
        printf("Ingrese el numero de tarjeta (0 para salir): ");
        scanf("%d", &numTarjeta);

        if (numTarjeta == 0) {
            printf("\nGracias por usar el cajero. Hasta luego.\n");
            continuar = 0; // Finaliza el bucle principal
        } else {
            // Buscar la tarjeta
            pos = -1;
            for (int i = 0; i < tarjetas; i++) {
                if (numTarjetas[i] == numTarjeta) {
                    pos = i;
                }
            }
            if (pos == -1) {
                printf("\nTarjeta no reconocida.\n");
                Sleep(1500);
            } else {
                if (!validarPin(pines, pos, intentos))
                    {
                        printf("\nDemasiados intentos fallidos. Tarjeta bloqueada.\n");
                        Sleep(1500);
                    } else
                    {
                    opcion = 0;
                    do {
                        limpiarPantalla();
                        mostrarMenu();
                        printf("Seleccione una opcion: ");
                        scanf("%d", &opcion);

                        switch (opcion)
                        {
                            case 1:
                                consultarSaldo(saldos, pos);
                            break;
                            case 2:
                                retirarDinero(saldos, pos, retiro_limite);
                            break;
                            case 3:
                                depositar(saldos, pos);
                            break;
                            case 4:
                                printf("\nRetire su tarjeta. Hasta pronto.\n");
                                Sleep(1500);
                                break;
                            default:
                                printf("\nOpcion invalida.\n");
                                Sleep(1000);
                        }

                        if (opcion != 4) {
                            Sleep(4000);
                        }
                    } while (opcion != 4);
                }
            }
        }
    } while (continuar == 1);

    return 0;
}
void inicializarCuentas(int numTarjetas[], int pines[], double saldos[], int n)
{
    int numeros[]  = {1111, 2222, 3333};
    int pinesIni[] = {1234, 4321, 1212};
    double saldosIni[] = {1500.0, 850.0, 3200.0};

    for (int i = 0; i < n; i++) {
        numTarjetas[i] = numeros[i];
        pines[i] = pinesIni[i];
        saldos[i] = saldosIni[i];
    }
}
int validarPin(int pines[], int pos, int maxIntentos)
{
    int pinIngresado;
    int intentos = 0;

    while (intentos < maxIntentos) {
        printf("Ingrese su NIP: ");
        scanf("%d", &pinIngresado);

        if (pinIngresado == pines[pos]) {
            printf("\nNIP correcto.\n");
            Sleep(800);
            return 1;
        } else {
            intentos++;
            printf("NIP incorrecto. Intentos restantes: %d\n", maxIntentos - intentos);
        }
    }
    return 0;
}
void mostrarMenu(void)
{
    printf(" MENU PRINCIPAL \n");
    printf("1. Consultar saldo\n");
    printf("2. Retirar dinero\n");
    printf("3. Depositar dinero\n");
    printf("4. Salir\n");
    printf(".......................\n");
}
void consultarSaldo(double saldos[], int pos)
{
    printf("\nSu saldo actual es: $%.2f\n", saldos[pos]);
}
void depositar(double saldos[], int pos)
{
    double monto;

    printf("\nIngrese el monto a depositar: $");
    scanf("%lf", &monto);

    if (monto <= 0)
    {
        printf("Monto invalido.\n");
        return;
    }

    saldos[pos]= saldos[pos] + monto;
    limpiarPantalla();
    animacionEspera();
    printf("Deposito exitoso. Nuevo saldo: $%d\n", (int)saldos[pos]);
}

void retirarDinero(double saldos[], int pos, int limite)
{
    int monto;
    int c20 = 0, c10 = 0, c5 = 0;

    printf("\nIngrese el monto a retirar (multiplo de $5): $");
    scanf("%d", &monto);

    if (monto <= 0) {
        printf("Monto invalido.\n");
        return;
    }

    if (monto % 5 != 0) {
        printf("El monto debe ser multiplo de $5.\n");
        return;
    }

    if (monto > limite) {
        printf("El monto excede el limite maximo de retiro ($%d).\n", limite);
        return;
    }

    if (monto > saldos[pos]) {
        printf("Saldo insuficiente. Su saldo es: $%d\n", (int)saldos[pos]);
        return;
    }

    animacionEspera();

    generadorDeBilletes(monto, &c20, &c10, &c5, billete_c1, billete_c2, billete_c3);

    saldos[pos]=saldos[pos]-monto;

    printf("\nMonto retirado: $%d\n", monto);
    printf("Billetes de $20: %d\n", c20);
    printf("Billetes de $10: %d\n", c10);
    printf("Billetes de $5 : %d\n", c5);
    printf("Saldo restante:  $%d\n", (int)saldos[pos]);
    printf("Retire su dinero y su recibo.\n");
}

int generadorDeBilletes(int monto, int *c20, int *c10, int *c5, int d20, int d10, int d5)
{
    int restante = monto;

    *c20 = restante / d20;
    restante = restante % d20;

    *c10 = restante / d10;
    restante = restante % d10;

    *c5 = restante / d5;
    restante = restante % d5;

    return monto;
}
void animacionEspera(void)
{
    int i, j;
    for(i = 0; i < 5; i++) {
        limpiarPantalla();
        printf("Un momento por favor");
        for(j = 0; j < 3; j++) {
            printf(".");
            Beep(880, 200);
            Sleep(800);
        }
    }
    limpiarPantalla();
}

void pausar(void)
{
    printf("\nPresione cualquier tecla para continuar...");
    getch();
}

void limpiarPantalla(void)
    {
        system("cls");
    }
