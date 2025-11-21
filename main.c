#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
typedef struct block{
    int index;
    long long nonce;
    char data[100];
    long long prev_hash;
    long long current_hash;
    struct block* prev;
}block;   
long long hash_fn(int i, long long n, char d[100], long long p)
{
    long long hash_val = 0;

    char text[200] = {0};
    char temp[50];
    sprintf(temp, "%d", i);
    strcat(text,temp);
    sprintf(temp, "%lld", n);
    strcat(text, temp);
    strcat(text,d);
    sprintf(temp, "%lld", p);
    strcat(text, temp);
    int len = strlen(text);
    for(int j = 0; j<len; j++)
    {
        hash_val = hash_val*31 + text[j];
    }
    return hash_val%10000000000000000;         //to return a max 16 digit hash_val
}
void mine(struct block* temp)
{
    //provided the block has index, data and prev hash. we obtain its nonce and current hash by mining.
    temp->nonce = 0;
    long long first_four = 0;
    while(first_four!=1111)
    {
        temp->nonce ++;
        temp->current_hash = hash_fn(temp->index, temp->nonce, temp->data, temp->prev_hash);
        first_four = temp->current_hash / 1000000000000LL;
    }
}
block* genesis_block_creation()
{
    block* Genesis_block = malloc(sizeof(block));
    Genesis_block->index = 0;
    strcpy(Genesis_block->data, "empty");
    Genesis_block->prev_hash = 0;
    Genesis_block->prev = NULL;
    mine(Genesis_block);
    return Genesis_block;
}
block* create_block(char user_input[100], block* prev_block)
{
    block* new_block = malloc(sizeof(block));
    new_block->index = prev_block->index + 1;
    strcpy(new_block->data, user_input);
    new_block->prev_hash = prev_block->current_hash;
    new_block->prev = prev_block;
    mine(new_block);
    prev_block = new_block;
    return prev_block;
}
void print_block(block* temp)
{
    printf("--------------------------------------------\n");
    printf("| index     = %-30d|\n", temp->index);
    printf("| nonce     = %-30lld|\n", temp->nonce);
    printf("| data      = %-30s|\n", temp->data);
    printf("| previous  = %-30lld|\n", temp->prev_hash);
    printf("| current   = %-30lld|\n", temp->current_hash);
    printf("--------------------------------------------\n");
}

int verify_bal(block* temp, char person[40])
{
    if(strcmp(person, "bank")==0)
    {
        return INT_MAX;
    }
    int bal = 0;
    char sender[40];
    char receiver[40];
    int amount;
    while(temp->prev != NULL)
    {
        sscanf(temp->data, "%s sent %s %d", sender, receiver,&amount);
        if(strcmp(receiver, person) == 0)
        {
            bal += amount;
        }
        else if(strcmp(sender, person)==0)
        {
            bal -= amount;
        }
        temp = temp->prev;
    }
    return bal;
}
block* create_prev_chain(block* p)
{
    FILE *f = fopen("data.txt", "r");
    char buffer[255];
    if(f==NULL)
    {
        return p;
    }
    else
    {
        while(fgets(buffer, 255, f) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = 0;
            p = create_block(buffer, p);
        }
    }
    fclose(f);
    return p;
}
void write_to_file(char data[100])
{
    FILE *f = fopen("data.txt", "a");
    fprintf(f,"%s\n",data);
    fclose(f);
}
char correct_input(char ent)
{
    if(ent==121)
    {
        return ent-32;
    }
    else if(ent==110)
    {
        return ent-32;
    }
    return ent;
}
void free_blockchain(block* head)
{
    block* temp;
    while(head!=NULL)
    {
        temp = head;
        head = head->prev;
        free(temp);
    }
}

typedef struct{
    char name[40];
    char password[40];
}registeration;



int enter_data(registeration *r) {
    char buffer[256];

    FILE *fp = fopen("data.csv", "a+"); 
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }
    fseek(fp, 0, SEEK_SET);
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {

        fprintf(fp, "Name,Password\n");
    }


    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%s,%s", r->name, r->password);

    fclose(fp);
    return 0;
}

int retrieve_data(char name1[],char password1[]){
    FILE *fp = fopen("data.csv", "r");
    if (!fp) {
        perror("Failed to open file");
        return 10;
    }

    char buffer[256];
    int a=0;

    fgets(buffer, sizeof(buffer), fp);

    registeration r;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (sscanf(buffer, "%39[^,],%39[^,]", r.name, r.password) == 2) {
            if (strcmp(r.name,name1)==0){
                a=1;
            if (strcmp(r.password,password1)==0){
                a=2;
            }break;
        }
        }}
    fclose(fp);
    return a;
}

registeration reg(){
    registeration regis;

    printf("Welcome new user!!");
    printf("Enter the username: ");
    scanf("%s",regis.name);
    printf("Enter the password(private key): ");
    scanf("%s",regis.password);
    enter_data(&regis);
    printf("New Account Registered\n");
}
char* login(char* name2){
    char name1[40];
    char name3[40];
    char password2[40];
    int q;
    printf("Login into your account\n");
    printf("Enter your username: ");
    scanf("%s",name1);
    strcpy(name2,name1);
    strcpy(name3,name1);
    printf("Enter the password: ");
    scanf("%s",password2);
    q=retrieve_data(name3,password2);
    if (q==0){
        printf("User not found\n");
        return " ";
    }else if(q==1){
        printf("Incorrect password\n");
        return " ";
    }else{
        printf("Welcome!!\n");
        return name2;
    }
}

int main()
{   
    int cur;
    char name2[40];
    int choice;
    printf("Do you want to 1.Register\n2.Login\n(1/2):");
    scanf("%d",&choice);
    if (choice==1){
        reg();
    }else if (choice==2){
        //while(1){
            strcpy(name2,login(name2));
            //if (strcmp(name2," ")==0){
                //continue;
           // }else{
           //     break;
           // }
       // }
    }
    printf("Welcome %s to main menu!!",name2);
    while(1){
    int n;
    block* p = genesis_block_creation();
    p = create_prev_chain(p);
    printf("Choose the options\n1.Deposit money in the account\n2.Money Transfer\n3.Check Balance\n4.View blockchain\n5.Exit\n:");
    scanf("%d",&n);
    if (n==1){
        printf("%s",name2);
        int dep_amt;
        printf("Amount to be deposited: ");
        scanf("%d", &dep_amt);
        char t[100];
        sprintf(t, "bank sent %s %d", name2, dep_amt);
        p = create_block(t,p);
        print_block(p);
        write_to_file(t);
    }else if(n==2){
        printf("Enter the amount: ");
        int amt;
        scanf("%d", &amt);
        printf("Enter receiver's name: ");
        char rname[40];
        scanf("%s", rname);
        char inp[100];
        sprintf(inp, "%s sent %s %d", name2, rname, amt);
        if(verify_bal(p, name2)>=amt)
        {
            p = create_block(inp, p);
            write_to_file(inp);
            print_block(p);
        }
        else if(verify_bal(p,name2)==0)
        {
            printf("Current balance is 0");
        }
        else
        {
            printf("Get your guap up before sending the $\n");
        }
    }else if (n==3){
        int bal;
        bal=verify_bal(p,name2);
        printf("Your balance is:%d",bal);
    }else if(n==4){
        block* s = p;
        while (s->prev != NULL){
        print_block(s);
        printf("                     |\n                     |\n                     v\n");

        s = s->prev;
        }
    }else if(n==5){
        return 0;
    }else{
        printf("Enter correct input");
}
  
}
}