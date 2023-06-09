#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// DOB struct
typedef struct DOB
{
    int date;
    int month;
    int year;
} DOB;

// structure for account
typedef struct Account
{
    char first_name[20];
    char last_name[20];
    DOB dob; // structure of dob
    unsigned long acc_num;
    char pass[20];
    float balance;
} account;

// to achieve delay
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

// generate random 4 digit number
int accNumGen()
{
    srand(time(0));
    int num = rand() % (9999 - 1000 + 1) + 1000;
    printf("Your account number is %d\n\n", num);
    return num;
}

// using the account
void useAcc(account *ptr)
{
    while (1)
    {
        account *tmp_ptr = malloc(sizeof(account)); // temporary pointer to store account
        FILE *fptr = NULL;                          // pointer to open the data file
        FILE *fptr2 = NULL;                         // ponter to open a temporary file
        float amt;
        system("cls");
        printf("Welcome %s %s\n", ptr->first_name, ptr->last_name);
        printf("Account No.: %d\n", ptr->acc_num);
        printf("DOB: %d/%d/%d\n", ptr->dob.date, ptr->dob.month, ptr->dob.year);
        printf("Current Balance: %.2f\n", ptr->balance);
        printf("\n\n1.Withdraw\n2.Deposit\n3.Close Account\n4.Logout\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            fptr = fopen("BankData.dat", "rb");       // rb because we just need to read it
            fptr2 = fopen("BankDataTemp.dat", "wb+"); // need writing in temp file
            printf("Enter amount: ");
            scanf("%f", &amt);
            if (amt > ptr->balance) // cant withdraw more than available
            {
                printf("Insufficient balance!!!");
                delay(1);
                continue;
            }
            ptr->balance = ptr->balance - amt; // updating the balance in ptr
            // write the updated data in new file
            while (fread(tmp_ptr, sizeof(*tmp_ptr), 1, fptr))
            {
                if (tmp_ptr->acc_num != ptr->acc_num) // write the data of other accounts as it was
                {
                    fwrite(tmp_ptr, sizeof(*tmp_ptr), 1, fptr2);
                }
                else // writing the data with updated balance which is stored in ptr
                {
                    fwrite(ptr, sizeof(*ptr), 1, fptr2);
                }
            }
            // close files before deleting or renaming
            fclose(fptr);
            fclose(fptr2);
            // replace the data of the file with new data
            remove("BankData.dat");                     // delete the data file
            rename("BankDataTemp.dat", "BankData.dat"); // rename the file containg the updated data
            break;
        case 2:
            fptr = fopen("BankData.dat", "rb");       // rb because we just need to read it
            fptr2 = fopen("BankDataTemp.dat", "wb+"); // need writing in temp file
            printf("Enter amount: ");
            scanf("%f", &amt);
            ptr->balance = ptr->balance + amt; // updating the balance in ptr
            // write the updated data in new file
            while (fread(tmp_ptr, sizeof(*tmp_ptr), 1, fptr))
            {
                if (tmp_ptr->acc_num != ptr->acc_num) // write the data of other accounts as it was
                {
                    fwrite(tmp_ptr, sizeof(*tmp_ptr), 1, fptr2);
                }
                else // writing the data with updated balance which is stored in ptr
                {
                    fwrite(ptr, sizeof(*ptr), 1, fptr2);
                }
            }
            // close files before deleting or renaming
            fclose(fptr);
            fclose(fptr2);
            // replace the data of the file with new data
            remove("BankData.dat");                     // delete the data file
            rename("BankDataTemp.dat", "BankData.dat"); // rename the file containg the updated data
            break;
        case 3:
            fptr = fopen("BankData.dat", "rb");       // rb because we just need to read it
            fptr2 = fopen("BankDataTemp.dat", "wb+"); // need writing in temp file
            printf("WARNING!!!\nYour account will be deleted forever.\n");
            // get password to confirm deletion
            printf("Please enter password to confirm: ");
            char pass[20];
            fflush(stdin);
            fgets(pass, 20, stdin);
            pass[strlen(pass) - 1] = '\0';
            if (strcmp(ptr->pass, pass) == 0) // check if password is correct
            {
                printf("Deleting account...\n");
                // deleting the account
                while (fread(tmp_ptr, sizeof(*tmp_ptr), 1, fptr)) // read through the data file
                {
                    if (tmp_ptr->acc_num != ptr->acc_num) // write all data int temp file except the account to be deleted
                    {
                        fwrite(tmp_ptr, sizeof(*tmp_ptr), 1, fptr2);
                    }
                }
                // close files before deleting and renaming
                fclose(fptr);
                fclose(fptr2);
                // replacing main file with temp file
                remove("BankData.dat");                     // delete the original file
                rename("BankDataTemp.dat", "BankData.dat"); // rename the temp file with the original file name
                delay(1);
                printf("Account successfully deleted\n");
                printf("Redirecting to homepage...");
                delay(1);
                return; // back to homepage
            }
            else // if password incorrect logout
            {
                printf("Invalid password. Logging out...\n");
                delay(1);
                return; // back to homepage
            }
            break;
        case 4:
            system("cls");
            printf("Logging out...");
            delay(1);
            return; // back to homepage
            break;
        default:
            printf("Invalid choice!!!Try again!!!\n");
            delay(1);
            continue; // back to the login screen
        }
    }
}

// login
void login()
{
    system("cls");
    FILE *fptr = fopen("BankData.dat", "rb"); // open file containing accounts
    account *ptr = malloc(sizeof(account));
    int num;
    fflush(stdin);
    printf("Enter account no. : ");
    scanf("%d", &num);
    int flag = 0;
    while (fread(ptr, sizeof(*ptr), 1, fptr)) // search through file for acc no.
    {
        if (ptr->acc_num == num) // if acc no. is found
        {
            flag = 1;
            char pass[20];
            fflush(stdin);
            // check password
            printf("Enter password: ");
            fgets(pass, 20, stdin);
            pass[strlen(pass) - 1] = '\0';
            if (strcmp(pass, ptr->pass) == 0) // if password is correct
            {
                printf("Login Successfull!!!Redirecting...");
                fclose(fptr); // close file before calling so that can open again in the other function
                delay(1);
                useAcc(ptr); // use the account
                break;
            }
            else
            {
                printf("Wrong password!!! Returning to home screen..."); // return to homepage if password incorrect
                delay(1);
            }
        }
    }
    if (!flag) // if account was not found
    {
        printf("Account not found!!! Returning to home page...");
        delay(1);
    }
    fclose(fptr);
}

// create new account
void newAccount()
{
    account *ptr = malloc(sizeof(account)); // pointer for new acc
    FILE *fptr = NULL;                      // file to open the file containg data
    fflush(stdin);
    // get details
    printf("Enter first name: ");
    fgets(ptr->first_name, 20, stdin);
    ptr->first_name[strlen(ptr->first_name) - 1] = '\0';
    printf("Enter last name: ");
    fgets(ptr->last_name, 20, stdin);
    ptr->last_name[strlen(ptr->last_name) - 1] = '\0';
    system("cls");
    //get dob
    printf("DATE OF BIRTH\n");
    printf("Please enter date DD: ");
    scanf("%d", &ptr->dob.date);
    printf("Please Enter month MM: ");
    scanf("%d", &ptr->dob.month);
    printf("Please enter year YYYY: ");
    scanf("%d", &ptr->dob.year);
    system("cls");
    ptr->balance = 0; // default balance 0
    printf("\nThank you for creating an account with us.\n");
    int num = accNumGen(); // generate 4 digit acc num
    ptr->acc_num = num;
    // create password
    printf("Please create a password: ");
    fflush(stdin);
    fgets(ptr->pass, 20, stdin);
    ptr->pass[strlen(ptr->pass) - 1] = '\0';
    fptr = fopen("BankData.dat", "ab+"); // ab so as to retain previous data
    fwrite(ptr, sizeof(*ptr), 1, fptr);  // add the new acc
    system("cls");
    fclose(fptr);
}

int main()
{
    int choice;
    while (1)
    {
        system("cls");
        // homepage
        printf("\t\t****WELCOME TO APNA BANK*****\n\n");
        printf("1.Login\n");
        printf("2.Create Account\n");
        printf("3.Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        system("cls");
        switch (choice)
        {
        case 1:
            login();
            break;
        case 2:
            newAccount();
            break;
        case 3:
            exit(0);
        default:
            printf("\nInvalid Choice. Please try again\n");
            delay(1);
            continue;
        }
    }

    return 0;
}
