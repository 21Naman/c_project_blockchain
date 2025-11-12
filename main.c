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
    char temp[50] = '\0';
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
    int first_four = 0;
    while(first_four!=1111)
    {
        temp->nonce ++;
        temp->current_hash = hash_fn(temp->index, temp->nonce, temp->data, temp->prev_hash);
        first_four = temp->current_hash / 1000000000000;
    }
    return;
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
int main()
{
    
}