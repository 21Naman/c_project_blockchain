#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
    printf("----------------------------------------\n");
    printf("| index = %d                           |\n", temp->index);
    printf("| nonce = %lld                         |\n", temp->nonce);
    printf("| data = %s                            |\n", temp->data);
    printf("| previous = %lld                      |\n", temp->prev_hash);
    printf("| Current =  %lld                      |\n", temp->current_hash);
    printf("----------------------------------------\n");
}
int verify_bal(block* temp, char person[40])
{
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
int main()
{
    printf("DO YOU WANT TO SEND THE GUAP{(Y/N): ");
    char ent;
    scanf(" %c", &ent);
    block* p = genesis_block_creation();
    while(ent=='Y')
    {
        printf("Enter sender: ");
        char name[40];
        scanf("%s", name);
        printf("Enter amount: ");
        int amt;
        scanf("%d", &amt);
        printf("Enter receiver: ");
        char rname[40];
        scanf("%s", rname);
        char inp[100];
        sprintf(inp, "%s sent %s %d", name, rname, amt);
        if(verify_bal(p, name)>=amt)
        {
            p = create_block(inp, p);
            print_block(p);
        }
        else if(verify_bal(inp,p)==0)
        {
            printf("current balance is 0");
        }
        else
        {
            printf("Get your guap up before sending the $\n");
        }
        printf("DO YOU WANT TO TRANSFER MORE MONEY(Y/N): ");
        scanf(" %c", &ent);
    }
    if(ent=='N')
    {
        char entry;
        printf("DO YOU WANT TO DEPOSIT MONEY(Y/N): ");
        scanf(" %c",&entry);
        if(entry=='Y')
        {
            int dep_amt;
            char depositor[40];
            printf("name of depositer: ");
            scanf("%s", depositor);
            printf("amount to be deposited: ");
            scanf("%d", &dep_amt);
            char t[20];
            sprintf(t, "bank sent %s %d", depositor, &dep_amt);
            p = create_block(t,p);
        }
        else if(entry=='N')
        {
            printf("bye\n");
        }
    }
    else
    {
        printf("Invalid input\n");
    }
    return 0;
}