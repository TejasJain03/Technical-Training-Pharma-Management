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
    struct Medicine med;
    FILE *fp, *temp;

    fp = fopen("medicine.txt", "rb");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter medicine name to delete: ");
    scanf("%s", name);

    int found = 0; 

    temp = fopen("temp.txt", "wb");
    if (temp == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return;
    }

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

    if (!found)
    {
        printf("Medicine not found\n");
    }
    else
    {
        if (remove("medicine.txt") != 0)
        {
            printf("Error deleting original file.\n");
        }
        if (rename("temp.txt", "medicine.txt") != 0)
        {
            printf("Error renaming temporary file.\n");
        }
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

float searchInvoice(char medicine[], int quantity, float sum)
{
    FILE *fp;
    struct Medicine med;
    int found = 0;
    fp = fopen("medicine.txt", "r+");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&med, sizeof(struct Medicine), 1, fp))
    {
        if (strcmp(med.name, medicine) == 0)
        {
            found = 1;
            if (quantity <= med.quantity)
            {
                float total = quantity * med.price;
                printf("\n%-20s%-20d%-20.2f%.2f\n", medicine, quantity, med.price, total);
                return total;
            }
            else
            {
                printf("\n(%s)=>Required Quantity not available in Stock \n", medicine);
                return 0;
            }
            break;
        }
    }

    if (!found)
    {
        printf("\n(%s)=>Out of Stock \n", medicine);
        return 0;
    }

    fclose(fp);
}

void checkAndShowInvoice()
{
    int num;

    printf("Enter the number of medicines you want: ");
    scanf("%d", &num);
    char medicines[num][100];
    int quantity[num];

    for (int i = 0; i < num; i++)
    {
        printf("Enter medicine name: ");
        scanf("%s", medicines[i]);
        printf("Enter quantity: ");
        scanf("%d", &quantity[i]);
    }

    printf("\n************************************************************************\n");
    printf("                      INVOICE                           \n");
    printf("***************************************************************************\n");
    printf("%-20s%-20s%-20s%s\n", "Medicine", "Quantity", "Price", "Total");
    printf("***************************************************************************\n");

    float totalSum = 0, sum;
    for (int i = 0; i < num; i++)
    {
        sum = searchInvoice(medicines[i], quantity[i], totalSum);
        totalSum = sum + totalSum;
    }
    printf("\n*****************************************************************************\n");
    printf("%40s%.2f", "Total Amount=", totalSum);
    printf("\n*****************************************************************************\n");
    printf("                   Invoice generated successfully.            \n");
    printf("*****************************************************************************\n");
}

int login(char username[], char password[])
{
    char adminUsername[] = "admin";
    char adminPassword[] = "admin123";
    char userUsername[] = "user";
    char userPassword[] = "user123";
    if (strcmp(username, adminUsername) == 0 && strcmp(password, adminPassword) == 0)
    {
        return 1;
    }
    else if (strcmp(username, userUsername) == 0 && strcmp(password, userPassword) == 0)
    {
        return 2;
    }

    return 0;
}

void admin()
{
    int choice;
    while (1)
    {
        printf("\n***********************************************************\n");
        printf("\nPharma Management System\n");
        printf("\n***********************************************************\n");
        printf("\n Welcome ADMIN \n");
        printf("\n***********************************************************\n");
        printf("1. Add new stock\n");
        printf("2. Delete existing stock\n");
        printf("3. Alter price and update existing medicine\n");
        printf("4. Show\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addStock();
            break;
        case 2:
            deleteStock();
            break;
        case 3:
            alterPrice();
            break;
        case 4:
            showStock();
            break;
        case 5:
            exit(0);
        default:
            printf("INVALID CHOICE!!!");
            break;
        }
    }
}

void user()
{
    int choice;
    while (1)
    {
        printf("\n***********************************************************\n");
        printf("\nPharma Management System\n");
        printf("\n***********************************************************\n");
        printf("\n Welcome USER \n");
        printf("\n***********************************************************\n");
        printf("1. Check and download invoice\n");
        printf("2. Show\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            checkAndShowInvoice();
            break;
        case 2:
            showStock();
            break;
        case 3:
            exit(0);
        default:
            printf("INVALID CHOICE!!!");
            break;
        }
    }
}

int main()
{
    int userlogin;
    char username[50], userPassword[50];
    printf("\n***********************************************************\n");
    printf("\n\t\t\t WELCOME\n ");
    printf("\n***********************************************************\n");
    while (1)
    {
        printf("\n *****Please Login*****");
        printf("\nEnter Username:");
        scanf("%s", username);
        printf("\nṇEnter Password:");
        scanf("%s", userPassword);
        userlogin = login(username, userPassword);
        switch (userlogin)
        {
        case 1:
            admin();
            break;
        case 2:
            user();
            break;
        default:
            printf("INVALID CREDENTIALS!!!! PLEASE TRY AGAIN");
            break;
        }
    }
    return 0;
}