#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 1000
#define USERNAME_LENGTH 20
#define HASH_KEY 0x5A3C9F2E  // Simple hash key for password transformation

// Simple password hashing functions


struct login {
    char username[USERNAME_LENGTH];
    int password;
    int salt;
    
} users[MAX_USERS];
struct computer
{
  char product_name[20];
  int price;

}cust2[100];
struct cart
{
  char product_name[20];
  int price;

  int password;


}cust3[100];

int user_count = 0;
int num=0;
int cart_no=0;
int read_no=0;
int login_no=0;
int user=0;
int user_no=0;

void searchproduct(struct computer x[]);
void read_login();
void menu();
void menu2(const char *msg);
void main_stuff();
void create_account();
void login();
void product(int z);
void cart();
void write(struct cart x);
void read_cart();
void print_cart();
void user_menu(const char *username);
void write2(struct login x);
void write_cart();
void del_cart(int z);
void checkout();

int main() {
    srand(time(NULL));
    
    while (1) {
        main_stuff();
    }
    return 0;
}
int generate_salt(){
    
    return rand() % 1000000;

}
int hash_password(int password, int salt) {
    return (password ^ HASH_KEY) + salt;
}
void menu() {
    system("clear");
    printf("*************************************************\n");
    printf("***************|AYMAN HARDWARES|*****************\n");
    printf("*************************************************\n");
    printf("* PRESS|  OPTIONS                               *\n");
    printf("*   1  |  Create Account                        *\n");
    printf("*   2  |  Login to Account                      *\n");
    printf("*   3  |  Terminate Program                     *\n");
    printf("*************************************************\n");
}

void main_stuff() {
    int option;
    menu();
    if (scanf("%d", &option) != 1) {
        getchar(); 
        menu2("Invalid Input");
        return;
    }
    getchar();

    if (option == 1) {
        create_account();
    } else if (option == 2) {
        login();
    } else if (option == 3) {
        printf("Terminating Program...\n");
        exit(0);
    } else {
        menu2("Invalid Input");
    }
}


void create_account() {
   read_login();
    if (user_count >= MAX_USERS) {
        menu2("User limit reached. Cannot create more accounts.");
        return;
    }

    char username[USERNAME_LENGTH];
    int password;

    printf("Enter username: ");
    fgets(username, USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password (numeric): ");
    scanf("%d", &password);
    getchar();

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            menu2("Username already exists. Try a different one.");
            return;
        }
    }
    
    struct login new_user;
    strcpy(new_user.username, username);
    new_user.salt = generate_salt();
    new_user.password = hash_password(password, new_user.salt);

    users[user_count] = new_user;
    user_count++;

    write2(new_user);

    menu2("Account created successfully!");
}

void login()
 {
    read_login();

    char username[USERNAME_LENGTH];
    int password;

    printf("Enter username: ");
    fgets(username, USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; 

    printf("Enter password (numeric): ");
    scanf("%d", &password);




    getchar();

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && users[i].password == hash_password(password, users[i].salt))
         {
            user_no=i;
            user_menu(username);

            return;
        }
    }
    menu2("Invalid username or password. Try again.");
    getchar();
}

void user_menu(const char *username) {
    while (1) {
        system("clear");
        printf("*************************************************\n");
        printf("***************|AYMAN HARDWARES|*****************\n");
        printf("*************************************************\n");
        printf("* Welcome, %s                                   *\n", username);
        printf("* PRESS|  OPTIONS                               *\n");
        printf("*   1  |  Search products                       *\n");
        printf("*   2  |  View product                          *\n");
        printf("*   3  |  View Cart                             *\n");
        printf("*   4  |  Delete Cart                           *\n");
        printf("*   5  |  Check Out                             *\n");
        printf("*   6  |  Log Out                               *\n");
        printf("*   7  |  Terminate Program                     *\n");
        printf("*************************************************\n");

        int option;
        if (scanf("%d", &option) != 1) {
            getchar(); // Clear invalid input
            menu2("Invalid Input");
            continue;
        }
        getchar();

        if (option == 1) {
        searchproduct(cust2);
            printf("Press Enter to continue...");
            getchar();
        }
        else if (option == 2) {
            product(users[user_no].password);
           printf("Press Enter to continue...");
            getchar();
        }
        else if (option == 3)
        {
            int temp;
            read_cart();
            print_cart();
            printf("Press Enter to continue...");
            getchar();
        }
        else if (option == 4)
        {
            int item_no;
            print_cart();
            printf("Enter the cart number of the item to delete: ");
            scanf("%d", &item_no);
            getchar();
            del_cart(item_no);
            printf("Press Enter to continue...");
            getchar();
        }
        else if (option == 5)

        {
            system("clear");
            checkout();
            printf("Press Enter to continue...");
            getchar();



        }
        else if (option == 6) {
            printf("Logging out...\n");
            return;
        }
        else if (option == 7) {
            printf("Terminating...\n");
            exit(0);
        }
        else
        {
            menu2("Invalid Input");
        }
    }
}



void menu2(const char *msg)
{
    system("clear");
    printf("*************************************************\n");
    printf("***************|AYMAN HARDWARES|*****************\n");
    printf("*************************************************\n");
    printf("*                                               *\n");
    printf("    %s    \n", msg);
    printf("*                                               *\n");
    printf("*************************************************\n");
    printf("Press Enter to continue...");
    getchar();
}
void write2(struct login x)
{
    FILE *fp;
    fp=fopen("User.dat","a");

    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    fwrite(&x,sizeof(struct login), 1, fp);
    fclose(fp);

}
void read_login()
{
    FILE *fp;
    fp=fopen("User.dat","r");

    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    user_count=fread(users,sizeof(struct login),MAX_USERS, fp);
    fclose(fp);

}




void read()
{
    FILE *file;
    file = fopen ("list.dat","r");

    if (file == NULL)
    {
        fprintf(stderr, "\nError opening list.dat\n\n");
        exit (1);
    }

    int i,j;

    num = fread (cust2, sizeof(struct computer), 100, file);

    fclose(file);



}
void add_cart(int z)
{
    if (z < 0 || z >= 100 || cart_no >= 100) {
        printf("Invalid product number or cart full.\n");
        return;
    }
    
    strcpy(cust3[cart_no].product_name,cust2[z].product_name);
    cust3[cart_no].price=cust2[z].price;
    cust3[cart_no].password=users[user_no].password;

    write_cart();
    cart_no++;



}
void del_cart(int z)
{
    if (z >= 0 && z < cart_no)
        {
            for (int i = z; i < cart_no - 1; i++)
            {

                strcpy(cust3[i].product_name, cust3[i + 1].product_name);
                cust3[i].price = cust3[i + 1].price;
                cust3[i].password = cust3[i + 1].password;
            }

        cart_no--;
        printf("Item removed from cart.\n");
        FILE *fp = fopen("data.dat", "w");
        if (fp == NULL) {
            perror("Error opening file");
            return;
        }
        for (int i = 0; i < cart_no; i++)
        {
            fprintf(fp, "%s %d %d\n", cust3[i].product_name, cust3[i].price, cust3[i].password);
        }
        fclose(fp);
        }
        else
        {
            printf("Invalid cart number.\n");
        }
}
void read_cart() {

    struct cart n[100];
    FILE *fp;
    fp = fopen("data.dat", "r");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    int i = 0;
    cart_no=0;

    while(fscanf(fp, "%s %d %d", n[i].product_name, &n[i].price, &n[i].password)==3)
    {

        if(n[i].password==users[user_no].password)
        {
            strcpy(cust3[i].product_name,n[i].product_name);
            cust3[i].price=n[i].price;
            cust3[i].password=n[i].password;
            i++;
            cart_no++;


        }


    }



    fclose(fp);
}
void write_cart()
{

    FILE *fp;
    fp=fopen("data.dat","a");

    int i,sum;
    sum=0;

    fprintf(fp,"%s %d %d\n",cust3[cart_no].product_name,cust3[cart_no].price,users[user_no].password);
    fclose(fp);

    }




void print_cart()
{
    int i,sum;
    sum=0;
    system("clear");
         printf("*************************************************\n");
         printf("***************|AYMAN HARDWARES|*****************\n");
         printf("*************************************************\n");
         printf("||         Current Cart:\n");
         printf("||                                              \n");
    for(i=0;i<cart_no;i++)
    {
        if(cust3[i].price!=0)
        {printf("||%d|-cart no:%d, Product name:%s, Price:%d     \n",i+1,i,cust3[i].product_name,cust3[i].price);
        sum+=cust3[i].price;


        }

    }
         printf("||                                              \n");
         printf("||         Total Cost:%d                        \n",sum);
         printf("---------------------------------------------\n");


}


void checkout()
{
    while(1)
            {
                int z;
                read_cart();
                print_cart();
                printf("Press 0 to checkout and 1 to return to previous menu\n");
                if (scanf("%d",&z) != 1) {
                    getchar(); // Clear invalid input
                    printf("Invalid Input. Press enter to try again\n");
                    getchar();
                    continue;
                }
                getchar();
                if(z==0)
                {
                    system("cls");
                printf("Thank you for shopping at Ayman Hardwares!!\n Have a nice day!\n");

                exit(0);

                }
                else if(z==1)
                    return;
                else
                {   system("cls");
                    printf("Invalid Input. Press enter to try again");
                    return;
                }
        }
}
void searchproduct(struct computer x[])
{   system("clear");
    read();
    printf("*************************************************\n");
    printf("***************|AYMAN HARDWARES|*****************\n");
    printf("*************************************************\n");
    printf("Enter search(use '-' instead of space):\n");
    int found=0;
    char search[20];
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = 0;
    int j;


    for(int i=0;i<100;i++)
    {
        if(strcmp(cust2[i].product_name,search)==0)

        {
            system("clear");
            printf("*************************************************\n");
            printf("***************|AYMAN HARDWARES|*****************\n");
            printf("*************************************************\n");
            printf("Product Found. Enter 1 to add to cart.0 to exit\n");
            if (scanf("%d",&j) != 1) {
                getchar(); // Clear invalid input
                printf("Invalid Input\n");
                getchar();
                return;
            }
            getchar();
            if(j==1)
                add_cart(i);
            else if(j==0)
                return;
            else
            {
                printf("Invalid Input");
            getchar();
            }


            found++;
        }
    }




    if(found==0)
    {
        printf("Product Unavailable\n");
    }

}
void product(int z)
{
    read();

    while (1) {
        system("clear");
        printf("*************************************************\n");
        printf("***************|AYMAN HARDWARES|*****************\n");
        printf("*************************************************\n");

        printf("* PRESS|  OPTIONS                               *\n");
        printf("*   1  |  GPU                                   *\n");
        printf("*   2  |  CPU                                   *\n");
        printf("*   3  |  Monitor                               *\n");
        printf("*   4  |  Peripherals                           *\n");
        printf("*   5  |  Storage                               *\n");
        printf("*   6  |  RAM                                   *\n");
        printf("*   7  |  Back                                  *\n");
        printf("*   8  |  Terminate                             *\n");
        printf("*************************************************\n");

        int temp,i,j,y;

        scanf("%d",&temp);
        getchar();

        if(temp==1)
        {
            system("clear");

            for(i=0; i<num; i++)
                {
                for(j=0;j<20;j++)
                    {
                        if((cust2[i].product_name[j]=='r')&&(cust2[i].product_name[j+1]=='t')&&(cust2[i].product_name[j+2]=='x')&&(cust2[i].price!=0))
                            {
                                    printf ("Product no:%d Name: %s Price:%d\n",i,cust2[i].product_name, cust2[i].price);
                                    break;
                            }
                    }

                }
                printf(" Enter product no to add to cart or enter 1000 to continue...\n");
                while(1)
                {
                    scanf("%d",&y);
                    getchar();

                    if(y<100)
                    {
                    add_cart(y);

                    printf("Added to cart\nAdd more items:\n");


                    }
                    else if(y==1000)
                    break;
                    else if(y>=100)
                    printf("Invalid Input");

                }
            printf("\n");
            printf("Current Cart:\n");

            read_cart();
            print_cart();



            getchar();
        }
        else if(temp==2)
        {
            system("clear");

            for(i=0; i<num; i++)
                {
                for(j=0;j<20;j++)
                    {
                        if(((cust2[i].product_name[j]=='r')&&(cust2[i].product_name[j+1]=='y')||(cust2[i].product_name[j]=='i')&&(cust2[i].product_name[j+1]=='n')&&(cust2[i].product_name[j+2]=='t'))&&(cust2[i].price!=0))
                            {
                                    printf ("Product no:%d Name: %s Price:%d\n",i,cust2[i].product_name, cust2[i].price);
                                    break;
                            }
                    }

                }
                printf(" Enter product no to add to cart or enter 1000 to continue...\n");
                while(1)
                {
                    scanf("%d",&y);
                    getchar();

                    if(y<100)
                    {
                    add_cart(y);

                    printf("Added to cart\nAdd more items:\n");


                    }
                    else if(y==1000)
                    break;
                    else if(y>=100)
                    printf("Invalid Input");

                }
            printf("\n");
            printf("Current Cart:\n");

            read_cart();
            print_cart();



            getchar();
        }
        if(temp==3)
        {
            system("clear");

            for(i=0; i<num; i++)
                {
                for(j=0;j<20;j++)
                    {
                        if((cust2[i].product_name[j]=='s')&&(cust2[i].product_name[j+1]=='a')&&(cust2[i].product_name[j+2]=='m')&&(cust2[i].price!=0))
                            {
                                    printf ("Product no:%d Name: %s Price:%d\n",i,cust2[i].product_name, cust2[i].price);
                                    break;
                            }
                    }

                }
                printf(" Enter product no to add to cart or enter 1000 to continue...\n");
                while(1)
                {
                    scanf("%d",&y);
                    getchar();

                    if(y<100)
                    {
                    add_cart(y);
                    printf("Added to cart\nAdd more items:\n");


                    }
                    else if(y==1000)
                    break;
                    else if(y>=100)
                    printf("Invalid Input");

                }
                printf("\n");
            printf("Current Cart:\n");
                read_cart();
            print_cart();


            getchar();
        }
        if(temp==4)
        {
            system("clear");

            for(i=0; i<num; i++)
                {
                for(j=0;j<20;j++)
                    {
                        if((cust2[i].product_name[j]=='m')&&(cust2[i].product_name[j+1]=='o')&&(cust2[i].product_name[j+2]=='u')&&(cust2[i].price!=0)||(cust2[i].product_name[j]=='k')&&(cust2[i].product_name[j+1]=='e'))
                            {
                                    printf ("Product no:%d Name: %s Price:%d\n",i,cust2[i].product_name, cust2[i].price);
                                    break;
                            }
                    }

                }
                printf(" Enter product no to add to cart or enter 1000 to continue...\n");
                while(1)
                {
                    scanf("%d",&y);
                    getchar();

                    if(y<100)
                    {
                    add_cart(y);
                    printf("Added to cart\nAdd more items:\n");


                    }
                    else if(y==1000)
                    break;
                    else if(y>=100)
                    printf("Invalid Input");

                }
                printf("\n");
            printf("Current Cart:\n");
            read_cart();
            print_cart();


            getchar();
        }
        if(temp==5)
        {

            system("clear");

            for(i=0; i<num; i++)
                {
                for(j=0;j<20;j++)
                    {
                       if((cust2[i].product_name[j]=='s')&&(cust2[i].product_name[j+1]=='s')&&(cust2[i].product_name[j+2]=='d')&&(cust2[i].price!=0)||(cust2[i].product_name[j]=='h')&&(cust2[i].product_name[j+1]=='d')&&(cust2[i].product_name[j+2]=='d'))
                            {
                                    printf ("Product no:%d Name: %s Price:%d\n",i,cust2[i].product_name, cust2[i].price);
                                    break;
                            }
                    }

                }
                printf(" Enter product no to add to cart or enter 1000 to continue...\n");
                while(1)
                {
                    scanf("%d",&y);
                    getchar();

                    if(y<100)
                    {
                    add_cart(y);
                    printf("Added to cart\nAdd more items:\n");


                    }
                    else if(y==1000)
                    break;
                    else if(y>=100)
                    printf("Invalid Input");

                }
                printf("\n");
            printf("Current Cart:\n");
                read_cart();
            print_cart();



            getchar();
        }
        if(temp==6)
        {
            system("clear");

            for(i=0; i<num; i++)
                {
                for(j=0;j<20;j++)
                    {
                        if((cust2[i].product_name[j]=='r')&&(cust2[i].product_name[j+1]=='a')&&(cust2[i].product_name[j+2]=='m')&&(cust2[i].price!=0))
                            {
                                    printf ("Product no:%d Name: %s Price:%d\n",i,cust2[i].product_name, cust2[i].price);
                                    break;
                            }
                    }

                }
                printf(" Enter product no to add to cart or enter 1000 to continue...\n");
                while(1)
                {
                    scanf("%d",&y);
                    getchar();

                    if(y<100)
                    {
                    add_cart(y);
                    printf("Added to cart\nAdd more items:\n");


                    }
                    else if(y==1000)
                    break;
                    else if(y>=100)
                    printf("Invalid Input");

                }
                printf("\n");
            printf("Current Cart:\n");
                read_cart();
            print_cart();


            getchar();
        }
         else if(temp==7)
         {
             return;
         }
         else if(temp==8)
         {
             exit(8);

         }

        else
            printf("Invalid input");

        }

}
