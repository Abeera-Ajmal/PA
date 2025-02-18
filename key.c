#include "../include/datatype.h"

typedef struct Key
{
    void *locker;
    int key_size;

} Key;

int getSize(DataType type)
{

    if (type == BLACK)
    {
        return sizeof(int);
    }
    else if (type == GREEN)
    {
        return sizeof(float);
    }
    else if (type == RED)
    {
        return sizeof(char);
    }
    else if (type == BLUE)
    {
        return sizeof(double);
    }
    else
    {
        return 0;
    }
}

// ---------------------------------------------------------------------------------------------------

Key *initializeKey(DataType type, int units, void *data)
{
    if (units == 0)
    { // handling this case
        return NULL;
    }

    int size = getSize(type);                    // we are using this to find the size
    Key *first_key = (Key *)malloc(sizeof(Key)); // creating the first key
    if (first_key == NULL)
    {
        return NULL;
    }

    first_key->locker = malloc(size * units); // filling members of the first key
    if (first_key->locker == NULL)
    {
        free(first_key);
        return NULL;
    }
    first_key->key_size = units * size;

    if (data == NULL)
    {
        return first_key;
    }

    // Note: you can use memcpy() directly but this is to show you how it works

    char *source = (char *)data; // making our own memcpy() function
    char *destination = (char *)first_key->locker;
    for (int i = 0; i < (units * size); i++)
    {
        destination[i] = source[i];
    }

    return first_key;
}

Key *keyMalloc(DataType type, int units)
{
    if (units == 0)
    {
        return NULL;
    }

    int size = getSize(type);
    Key *new_key = (Key *)malloc(sizeof(Key));
    if (new_key == NULL)
    {
        return NULL;
    }

    new_key->locker = calloc(units, size);
    if (new_key->locker == NULL)
    {
        free(new_key);
        return NULL;
    }

    new_key->key_size = units * size;
    return new_key;
}

void keyFree(Key *key)
{
    free(key->locker);
    key->locker = NULL;
    key->key_size = 0;
    free(key);
}

void keyStoreData(Key *key, void *data)
{
    if (key == NULL || data == NULL)
    {
        return;
    }
    char *source = (char *)data; // making our own memcpy() function
    char *destination = (char *)key->locker;
    for (int i = 0; i < key->key_size; i++)
    {
        destination[i] = source[i];
    }
}

void keyAccessData(Key *key, void *dest, DataType type, int units)
{
    if (key == NULL || dest == NULL)
    {
        return;
    }
    int size = getSize(type);
    char *source = (char *)key->locker; // making our own memcpy() function
    char *destination = (char *)dest;
    for (int i = 0; i < (size * units); i++)
    {
        destination[i] = source[i];
    }
}

/*
------------------------------------------------------------------------------
DO NOT EDIT THE FUNCTIONS BELOW - TESTING PURPOSES
*/

int getKeySize(Key *key)
{
    return key->key_size;
}

void *getLocker(Key *key)
{
    return key->locker;
}