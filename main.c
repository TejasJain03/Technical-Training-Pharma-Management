#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Medicine
{
    char name[100];
    int quantity;
    float price;
};

void addStock()
{
    struct Medicine med;
    FILE *fp;

    fp = fopen("medicine.txt", "a+");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    printf("Enter medicine name: ");
    scanf("%s", med.name);

    printf("Enter quantity: ");
    scanf("%d", &med.quantity);

    printf("Enter price: ");
    scanf("%f", &med.price);

    fwrite(&med, sizeof(struct Medicine), 1, fp);

    printf("Stock added successfully.\n");
    fclose(fp);
}

void showStock()
{
    struct Medicine med;
    FILE *fptr;
    fptr = fopen("medicine.txt", "r+");
    printf("\n");
    printf("\n*****************************************************************************************\n");
    printf("\nMEDICINE NAME\t\t\t\t\tQUANTITY\t\tPRICE \n");
    printf("\n*****************************************************************************************\n");
    while (fread(&med, sizeof(med), 1, fptr) == 1)
    {
        printf("\n%-30s\t\t%12d\t\t\t%.2f\n", med.name, med.quantity, med.price);
    }
    printf("\n*****************************************************************************************\n");
}
void deleteStock()
{
    char name[100];
    int found = 0;
    struct Medicine med;
    FILE *fp, *temp;
    fp = fopen("medicine.txt", "r+");
    temp = fopen("temp.txt", "w+");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    printf("Enter medicine name to delete: ");
    scanf("%s", name);
    while (fread(&med, sizeof(struct Medicine), 1, fp))
    {
        if (strcmp(med.name, name) != 0)
        {
            fwrite(&med, sizeof(struct Medicine), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (remove("medicine.txt") == 0)
    {
        if (rename("temp.txt", "medicine.txt") == 0)
        {
            printf("Stock deleted successfully.\n");
        }
    }
    if (!found)
    {
        printf("Medicine not found");
    }
}

void alterPrice()
{
    char name[100];
    float newPrice;
    int found = 0;
    struct Medicine med;
    FILE *fp, *temp;

    fp = fopen("medicine.txt", "r+");
    temp = fopen("temp.txt", "w+");

    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    printf("Enter medicine name to alter price: ");
    scanf("%s", name);

    while (fread(&med, sizeof(struct Medicine), 1, fp))
    {
        if (strcmp(med.name, name) == 0)
        {
            printf("Enter new price: ");
            scanf("%f", &newPrice);
            med.price = newPrice;
            fwrite(&med, sizeof(struct Medicine), 1, temp);
            found = 1;
        }
        else
        {
            fwrite(&med, sizeof(struct Medicine), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (remove("medicine.txt") == 0)
    {
        if (rename("temp.txt", "medicine.txt") == 0)
        {
            printf("Price altered successfully.\n");
        }
    }

    if (!found)
    {
        printf("Medicine not found.\n");
    }
}

void checkAndShowInvoice()
{
    char name[100];
    int quantity;
    float price, total = 0;
    struct Medicine med;
    FILE *fp;

    fp = fopen("medicine.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter medicine name: ");
    scanf("%s", name);

    while (fread(&med, sizeof(struct Medicine), 1, fp))
    {
        if (strcmp(med.name, name) == 0)
        {
            printf("Enter quantity: ");
            scanf("%d", &quantity);

            if (quantity <= med.quantity)
            {
                total = quantity * med.price;
                printf("\n***********************************************************\n");
                printf("                      INVOICE                           \n");
                printf("\n***********************************************************\n");
                printf("\t\tMedicine: \t%s\n", name);
                printf("\t\tQuantity: \t%d\n", quantity);
                printf("\t\tPrice: \t%10.2f\n", med.price);
                printf("\t\tTotal: \t%10.2f\n", total);
                printf("\n***********************************************************\n");
                printf("                   Invoice generated successfully.            \n");
                printf("\n***********************************************************\n");

            }
            else
            {
                printf("\n*********** Quantity exceeded *****************\n");
            }
            break;
        }
        else
        {
            printf("\n *********** Medicine Not Stock *******************\n");
            break;
        }
    }

    fclose(fp);
}

int main()
{
    int choice;
    printf("\n***********************************************************\n");
    printf("\n\t\t\t WELCOME\n ");
    printf("\n***********************************************************\n");

    while (1)
    {
        printf("\n***********************************************************\n");
        printf("\nPharma Management System\n");
        printf("\n***********************************************************\n");
        printf("1. Add new stock\n");
        printf("2. Delete existing stock\n");
        printf("3. Alter price and update existing medicine\n");
        printf("4. Check and download invoice\n");
        printf("5. Show\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system('cls');
            addStock();
            break;
        case 2:
            system('cls');
            deleteStock();
            break;
        case 3:
            system('cls');
            alterPrice();
            break;
        case 4:
            system('cls');
            checkAndShowInvoice();
            break;
        case 5:
            system('cls');
            printf("********** STOCK DATA **************");
            showStock();
            break;
        case 6:
            system('cls');
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}