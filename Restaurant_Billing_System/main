#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DISCOUNT 0.05
#define CGST 0.05
#define SGST 0.025

typedef struct item
{
    char item[20];
    float price;
    int quantity;
} item;

typedef struct order
{
    char name[50];
    char date[20];
    char time[20];
    int numOfItems;
    item itm[50];
} order;

void generateBillHeader(char *name, char *date, char *time)
{
    printf("\t\t ABC RESTAURENT\n");
    printf("\t\t----------------\n");
    printf("Date: ");
    printf("%s\t", date);
    printf("Time: ");
    printf("%s\t\n", time);
    printf("Invoice to: ");
    printf("%s\n", name);
    printf("---------------------------------------\n");
    printf("Items\t\tQty\t\tTotal\t\t\n");
    printf("---------------------------------------\n\n");
}

void generateBillBody(char *item, int quantity, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", quantity);
    printf("%.2f\t\t", price * quantity);
    printf("\n");
}

void generateBillFooter(float total)
{
    printf("\n---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f\n", total);
    float discount = total * DISCOUNT;
    printf("Discount @%.1f%%\t\t\t%.2f\n", DISCOUNT * 100, total * 0.1);
    printf("\t\t\t\t-------\n");
    float net = total - discount;
    printf("Net Total\t\t\t%.2f\n", net);
    float cgst = CGST * net;
    float sgst = SGST * net;
    printf("CGST @%.1f%%\t\t\t%.2f\n", CGST * 100, cgst);
    printf("SGST @%.1f%%\t\t\t%.2f\n", SGST * 100, sgst);
    float grandTotal = net + cgst + sgst;
    printf("---------------------------------------\n");
    printf("Grand Total\t\t\t%.2f\n", grandTotal);
    printf("Net Payable\t\t\t%.2f\n", floor(grandTotal));
    printf("---------------------------------------\n");
    printf("Thank you for shopping with us!!!\n");
    printf("Hoping to see you again!!!\n");
}

int main()
{
    int choice;
    order ord;
    char saveBill = 'y', contFlag = 'y';
    FILE *fp;
    // dashboard
    while (contFlag == 'y')
    {
        system("cls");
        printf("\t============ABC RESTAURENT============");
        printf("\n\n");
        printf("Please select required operation:\t");
        printf("\n");
        printf("1.Generate Invoice\n");
        printf("2.Show all invoices\n");
        printf("3.Search Invoice\n");
        printf("4.Exit\n");
        printf("\n");
        printf("Your choice:\t");
        scanf("%d", &choice);
        fflush(stdin);
        int flag = 0;
        switch (choice)
        {
        case 1:
            system("cls");
            printf("\nPlease enter the name of the customer:\t");
            fgets(ord.name, 50, stdin);
            ord.name[strlen(ord.name) - 1] = '\0';
            strcpy(ord.date, __DATE__);
            strcpy(ord.time, __TIME__);
            printf("Enter number of items:\t");
            scanf("%d", &ord.numOfItems);
            fflush(stdin);
            printf("\n");
            for (int i = 0; i < ord.numOfItems; i++)
            {
                printf("Please enter item %d:\t", i + 1);
                fgets(ord.itm[i].item, 20, stdin);
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = '\0';
                printf("Please enter the unit price:\t");
                scanf("%f", &ord.itm[i].price);
                printf("Please enter the quantity:\t");
                scanf("%d", &ord.itm[i].quantity);
                fflush(stdin);
                printf("\n");
            }
            float total = 0;
            generateBillHeader(ord.name, ord.date, ord.time);
            for (int i = 0; i < ord.numOfItems; i++)
            {
                generateBillBody(ord.itm[i].item, ord.itm[i].quantity, ord.itm[i].price);
                total += ord.itm[i].price * ord.itm[i].quantity;
            }
            generateBillFooter(total);

            printf("\nDo you want to save the invoice(y/n):\t");
            scanf("%c", &saveBill);

            if (saveBill == 'y')
            {
                fp = fopen("RestaurantBill.dat", "ab+");
                fwrite(&ord, sizeof(ord), 1, fp);
                if (fwrite != 0)
                {
                    printf("Sucessfully saved!!!\n");
                }
                else
                {
                    printf("Error saving!!!");
                }
                fclose(fp);
            }
            break;

        case 2:
            system("cls");
            fp = fopen("RestaurantBill.dat", "rb");
            printf("\n\n\t****Your previous Invoices****\n\n");
            while (fread(&ord, sizeof(ord), 1, fp))
            {
                generateBillHeader(ord.name, ord.date, ord.time);
                float total = 0;
                for (int i = 0; i < ord.numOfItems; i++)
                {
                    generateBillBody(ord.itm[i].item, ord.itm[i].quantity, ord.itm[i].price);
                    total += ord.itm[i].price * ord.itm[i].quantity;
                }
                generateBillFooter(total);
                printf("\n\n");
            }
            fclose(fp);
            break;

        case 3:
            fp = fopen("RestaurantBill.dat", "rb");
            printf("\nEnter name of Customer:\t");
            fflush(stdin);
            char name[50];
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = '\0';
            system("cls");
            printf("\n\n\t****Invoice of %s****\n\n", name);
            while (fread(&ord, sizeof(ord), 1, fp))
            {
                if (!strcmp(name, ord.name))
                {
                    flag = 1;
                    generateBillHeader(ord.name, ord.date, ord.time);
                    float total = 0;
                    for (int i = 0; i < ord.numOfItems; i++)
                    {
                        generateBillBody(ord.itm[i].item, ord.itm[i].quantity, ord.itm[i].price);
                        total += ord.itm[i].price * ord.itm[i].quantity;
                    }
                    generateBillFooter(total);
                    printf("\n\n");
                }
            }
            if (!flag)
            {
                printf("Not found\n");
            }
            fclose(fp);
            break;

        case 4:
            exit(0);
            break;

        default:
            printf("Invalid choice!!!\n");
            break;
        }

        printf("\nDo you want to perform another operation(y/n): ");
        fflush(stdin);
        contFlag = getchar();
        
    }
    return 0;
}
