#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>

#define _DATE_ "02-11-2022"

struct items
{
    char item[20];
    float price ;
    int qty;
};

struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

///function for generate bills
void generateBillHeader(char name[50], char date[30])
{
    printf("\n\n");
    printf("\t    MR-Restaurant  ");
    printf("\n\t  -----------------  ");
    printf("\n Date:%s",date);
    printf("\n Invoice To: %s ", name);
    printf("\n");
    printf("--------------------------------------\n ");
    printf("Items \t\t");
    printf("Qty \t\t");
    printf("Total \t\t");
    printf("\n--------------------------------------");
    printf("\n\n ");

}
void generateBillBody(char item[30], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t",qty * price);
    printf("\n ");
}



void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis ;
    float vat = 0.15 * netTotal, grandTotal = netTotal + vat;
    printf("-------------------------------------- \n");
    printf(" Sub Total \t\t\t %.2f",total);
    printf("\n Discount(10%s) \t\t\t %.2f","%",dis);
    printf("\n--------------------------------------\n");
    printf("\n Net Total\t\t\t %.2f", netTotal);
    printf("\n VAT(15%s)\t\t\t %.2f", "%", vat);
    printf("\n--------------------------------------");
    printf("\n Grand Total \t\t\t %.2f", grandTotal);
    printf("\n--------------------------------------\n");

}

int main()
{
    float total ;
    int opt,n;
    struct orders ord ;
    struct orders order ;
    char saveBill = 'y',contFlag = 'y';
    char name[50];
    FILE * fp;

    ///dashboard
    while(contFlag == 'y')
    {
        float total = 0;
        int invoiceFound = 0;
        printf("\n");
        printf("\t==============MR-Restaurant==============");
        printf("\n   1. Generate Invoice");
        printf("\n   2. Show All Invoice");
        printf("\n   3. Search Invoice");
        printf("\n   4. Exit");

        printf("\n\n Please select your preferred operation:\t");
        scanf("%d",&opt);
        printf("\n You have chosen %d",opt);

        fgetc(stdin);
        switch(opt)
        {
        case 1:
            //system("clear");
            printf("\n Please enter the name of the customer: \t");
            fgets(ord.customer, 50,stdin);
            ord.customer[strlen(ord.customer)-1] = 0;
            strcpy(ord.date,_DATE_);
            printf("\n Please enter the number of items: \t");
            scanf("%d",&n);
            ord.numOfItems = n ;

            for(int i=0; i<n; i++)
            {
                fgetc(stdin);
                printf("\n\n Please enter the name: \t");
                fgets(ord.itm[i].item,20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                printf("\n Please enter the quantity: \t");
                scanf("%d",&ord.itm[i].qty);
                printf("\n Please enter the unit price: \t");
                scanf("%f",&ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }
            generateBillHeader(ord.customer,ord.date);
            for(int i=0; i<ord.numOfItems; i++)
            {
                generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            }
            generateBillFooter(total);
            printf("\n Do you want to save the invoice[y/n]: \t");
            scanf("\%s",&saveBill);

            if(saveBill == 'y')
            {
                fp = fopen("RestaurantBill.dat","w");
                if (fp == NULL)
                {
                    fprintf(stderr, "\nError opened file\n");
                    exit (1);
                }
                //fwrite(&ord,sizeof(struct orders),1,fp);
                if (fwrite(&ord,sizeof(struct orders),1,fp) == 1)
                //if(fwrite != 0 )
                    printf("\n Successfully Saved");
                else
                    printf("\n Error Saving");
                fclose(fp);
            }
            break;

        case 2:
            //system("clear");
            fp = fopen("RestaurantBill.dat","r");
            printf("\n ********Your Previous Invoices*******\n");

            while(fread(&order,sizeof(struct orders),1,fp))
            {
                float tot = 0;
                generateBillHeader(order.customer,order.date);
                for(int i=0; i<order.numOfItems; i++)
                {
                    generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    tot+=order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
            }
            fclose(fp);
            break;

        case 3:
            printf("\t Enter the name of customer:\t");
            //fgetc(stdin);
            fgets(name,50,stdin);
            name[strlen(name)-1]=0;

            //system("clear");
            fp = fopen("RestaurantBill.dat","r");
            printf("\n ********Invoices of %s *******\n",name);

            while(fread(&order,sizeof(struct orders),1,fp))
            {
                float tot = 0;
                if(!strcmp(order.customer,name))
                {
                    generateBillHeader(order.customer,order.date);
                    for(int i=0; i<order.numOfItems; i++)
                    {
                        generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                        tot+=order.itm[i].qty * order.itm[i].price;
                    }
                }
                generateBillFooter(tot);
                invoiceFound = 1;
            }
            if(!invoiceFound)
            {
                printf("Sorry the invoice for %s doesn't exists",name);
            }
            fclose(fp);
            break;

        case 4:
            printf("\n\t\t Bye Bye :)\n\n");
            exit(0);
            break;

        default:
            printf("Sorry invalid option");
            break;
        }
        printf("\n Do you want to perform another operation? [y/n]: \t");
        scanf("%s",&contFlag);
    }
    printf("\n\t\t Bye Bye :)\n\n");
    printf("\n\n");

    return 0;
}
