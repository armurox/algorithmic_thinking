#include <stdio.h>
#include <stdlib.h>

int is_identical(int *s1, int *s2);
int right_identical(int *s1, int *s2);
int left_identical(int *s1, int *s2);

#define SIZE 100000

typedef struct node
{
    int *snowflake_;
    struct node *next;
}node;

int main()
{
    // Construct hash table
    node **hash_table = calloc(SIZE, sizeof(node*));
    if (hash_table == NULL)
    {
        printf("Memory overflow\n");
        return 1;
    }
    int case_num;
    scanf("%d", &case_num);
    for (int i = 0; i < case_num; i++)
    {
        int sum = 0;
        node *snowflake = malloc(sizeof(node));
        // Free hash table if not able to allocate memory successfully
        if (snowflake == NULL)
        {
            for (int j = 0; j < SIZE; j++)
            {
                node *tmp;
                node *curr = hash_table[j];
                while (curr != NULL)
                {
                    tmp = curr;
                    curr = curr -> next;
                    free(tmp);
                }
            }
            free(hash_table);
        }

        snowflake -> snowflake_ = malloc(sizeof(int) * 6);
        if ((snowflake -> snowflake_) == NULL)
        {
            for (int j = 0; j < SIZE; j++)
            {
                node *tmp;
                node *curr = hash_table[j];
                while (curr != NULL)
                {
                    tmp = curr;
                    curr = curr -> next;
                    free(tmp);
                }
            }
            free(hash_table);
            free(snowflake);
        }

        for (int j = 0; j < 6; j++)
        {
            scanf("%d", snowflake -> snowflake_ + j);
            sum += (snowflake -> snowflake_)[j];
        }
        snowflake -> next = NULL;

        sum %= SIZE;
        // Index into hash table
        node *start = hash_table[sum];
        for (node *curr = start; curr != NULL; curr = curr -> next)
        {
            if (is_identical(curr -> snowflake_, snowflake -> snowflake_))
            {
                printf("Twin snowflakes found\n");
                // Free everything
                for (int j = 0; j < SIZE; j++)
                {
                    node *tmp;
                    node *pointer = hash_table[j];
                    while (pointer != NULL)
                    {
                        tmp = pointer;
                        pointer = pointer -> next;
                        free(tmp -> snowflake_);
                        free(tmp);
                    }
                }
                free(hash_table);
                free(snowflake -> snowflake_);
                free(snowflake);
                return 0;
            }
        }

        snowflake -> next = start;
        hash_table[sum] = snowflake;
        // free(snowflake);

    }

    printf("No two snowflake are identical\n");
    // Free hash table
    for (int j = 0; j < SIZE; j++)
    {
        node *tmp;
        node *curr = hash_table[j];
        while (curr != NULL)
        {
            tmp = curr;
            curr = curr -> next;
            free(tmp -> snowflake_);
            free(tmp);
        }
    }
    free(hash_table);
}


















// Compare two snowflakes
int is_identical(int *s1, int *s2)
{
    int identical = 1;

    // Compare right
    identical = right_identical(s1, s2);
    // printf("%d\n", identical);

    // Compare left
    if (identical == 0)
    {
        identical = left_identical(s1, s2);
    }

    return identical;
}

int right_identical(int *s1, int *s2)
{
    int offset = 0;
    int valid = 1;
    int count = 0;
    while (offset < 6)
    {
        valid = 1;
        count = 0;
        int index;
        for (int i = offset; count < 6; count++)
        {
            // printf("running..\n");
            if (i < offset)
            {
                index = 6 + i - (offset);
            }

            else
            {
                index = i - offset;
            }

            if (s1[index] != s2[i])
            {
                valid = 0;
                // printf("%d %d\n", s1[i - offset], s2[i]);
                break;
            }
            i = (i + 1) % 6;
        }
        if (valid)
        {
            break;
        }
        offset++;
    }

    return valid;
}

int left_identical(int *s1, int *s2)
{
    int offset = 5;
    int valid = 1;
    int count = 0;
    while (offset > -1)
    {
        valid = 1;
        count = 0;
        int index;
        for (int i = offset; count < 6; count++)
        {
            // printf("running..\n");
            if (i > offset)
            {
                index = 6 - (i - offset);
            }

            else
            {
                index = offset - i;
            }

            if (s1[index] != s2[i])
            {
                valid = 0;
                // printf("%d %d\n", s1[i - offset], s2[i]);
                break;
            }
            i--;
            if (i < 0)
            {
                i = 5;
            }
        }
        if (valid)
        {
            break;
        }
        offset--;
    }

    return valid;
}
