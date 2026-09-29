#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

struct Producto {
    int id;
    char nombre[30];
    float precio;
    int subasta;
    char categoria[20];
};

int main(void)
{
    struct Producto inventario[20] =
    {
        {1, "Celular", 450.00, 2, "Tecnologia"},
        {2, "Laptop", 800.00, 1, "Tecnologia"},
        {3, "Audifonos", 75.00, 2, "Tecnologia"},
        {4, "Saco", 120.00, 1, "Moda"},
        {5, "Zapatos", 90.00, 2, "Moda"},
        {6, "Gafas", 45.00, 2, "Moda"},
        {7, "Balon", 25.00, 2, "Deportes"},
        {8, "Bicicleta", 350.00, 1, "Deportes"},
        {9, "Raqueta", 110.00, 2, "Deportes"}
    };

    int productosTotales = 9;
    int opcionM;
    int i, j;

    do
    {
        system("cls");
        printf("\neBay\n");
        printf("1. Ver productos disponibles\n");
        printf("2. Subastar producto\n");
        printf("3. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcionM);
        getchar();

        if (opcionM == 1)
        {
            system("cls");
            printf("\nProductos Disponibles: \n");
            printf("%-4s | %-15s | %-10s | %-12s | %-15s\n", "ID", "Nombre", "Precio", "Tipo", "Categoria");

            for (i = 0; i < productosTotales; i++)
            {
                char tipo[15];
                if(inventario[i].subasta == 1) {
                    strcpy(tipo, "Subasta");
                } else {
                    strcpy(tipo, "Precio Fijo");
                }

                printf("%-4d | %-15s | $%-9.2f | %-12s | %-15s\n",
                inventario[i].id, inventario[i].nombre, inventario[i].precio, tipo, inventario[i].categoria);
            }

            printf("\nPresione cualquier tecla para volver al menú...");
            getch();
            system("cls");

        }
        else if (opcionM == 2)
        {
            system("cls");
            if (productosTotales >= 20) {
                printf("\nInventario lleno, no se pueden agregar más productos.\n");
            } else {
                struct Producto nuevo;
                int opcionCat;

                nuevo.id = productosTotales + 1;

                printf("Nombre: ");
                fgets(nuevo.nombre, 30, stdin);
                nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0';

                printf("Precio: ");
                scanf("%f", &nuevo.precio);
                getchar();

                printf("1. Subasta / 2. Precio Fijo: ");
                scanf("%d", &nuevo.subasta);
                getchar();

                printf("Categoria (1.Tecnologia, 2.Moda, 3.Deportes): ");
                scanf("%d", &opcionCat);
                getchar();

                do {
                    printf("Categoria (1.Tecnologia, 2.Moda, 3.Deportes): ");
                    scanf("%d", &opcionCat);
                    getchar();

                    if (opcionCat < 1 || opcionCat > 3) {
                        printf("Opción inválida. Intente de nuevo.\n");
                    }
                } while(opcionCat < 1 || opcionCat > 3);

                if (opcionCat == 1) {
                    strcpy(nuevo.categoria, "Tecnologia");
                } else if (opcionCat == 2) {
                    strcpy(nuevo.categoria, "Moda");
                } else {
                    strcpy(nuevo.categoria, "Deportes");
                }
                for(int k = 0; k < 2; k++) {
                    system("cls");
                    printf("Procesando y publicando artículo, un momento por favor");
                    for(j = 0; j < 3; j++) {
                        printf(".");
                        Beep(880, 200);
                        Sleep(400);
                    }
                }

                inventario[productosTotales] = nuevo;
                productosTotales++;

                system("cls");
                printf("\n¡Artículo publicado con éxito!\n");
                printf("ID del nuevo producto: %d!\n", nuevo.id);
            }

            printf("\nPresione cualquier tecla para continuar...");
            system("pause > nul");
        }
        else if (opcionM == 3)
        {
            system("cls");
            printf("\nGracias por usar eBay. ¡Hasta pronto!\n");
            Sleep(1500);
        }
        else
        {
            printf("Opción no válida.\n");
            Sleep(1000);
        }

    } while (opcionM != 3);

    return 0;
}
