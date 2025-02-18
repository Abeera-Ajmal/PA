#include "../include/key.h"

typedef struct KeyChain
{
    Key *key;
    DataType type;
    int units;
    int index;
    struct KeyChain *next;

} KeyChain;

KeyChain *initializeKeyChain(DataType type, int units, void *data)
{
    if (units == 0)
    {
        return NULL;
    }

    KeyChain *first_key = malloc(sizeof(KeyChain));
    if (first_key == NULL)
    {
        return NULL;
    }

    first_key->key = initializeKey(type, units, data);
    if (first_key->key == NULL)
    {
        free(first_key);
        return NULL;
    }

    first_key->type = type;
    first_key->units = units;
    first_key->index = 0;
    first_key->next = NULL;

    return first_key;
}

KeyChain *keyChainMalloc(DataType type, int units, KeyChain *origin)
{
    if (units == 0)
    {
        return NULL;
    }

    KeyChain *new_key_chain = (KeyChain *)malloc(sizeof(KeyChain));
    if (new_key_chain == NULL)
    {
        return NULL;
    }

    new_key_chain->units = units;
    new_key_chain->type = type;
    new_key_chain->next = NULL;

    if (origin == NULL)
    {
        new_key_chain->index = 0;
        return new_key_chain;
    }

    KeyChain *origin_keychain = origin;
    int index_of_keychain = 0;

    while (origin_keychain->next != NULL)
    {
        origin_keychain = origin_keychain->next;
        index_of_keychain++;
    }

    new_key_chain->index = index_of_keychain + 1;
    origin_keychain->next = new_key_chain;

    return new_key_chain;
}

void keyChainFree(KeyChain *key_chain, KeyChain *origin)
{

    if (key_chain == NULL)
    {
        return;
    }

    if (key_chain->key != NULL)
    {
        keyFree(key_chain->key);
    }

    if (origin == key_chain)
    {
        origin = key_chain->next;
    }
    else
    {
        KeyChain *temp_key_chain = origin;
        while (temp_key_chain != NULL && temp_key_chain->next != key_chain)
        {
            temp_key_chain = temp_key_chain->next;
        }

        if (temp_key_chain != NULL)
        {
            temp_key_chain->next = key_chain->next;
        }
    }

    KeyChain *temp_key_chain = origin;
    int new_index = 0;
    while (temp_key_chain != NULL)
    {
        temp_key_chain->index = new_index++;
        temp_key_chain = temp_key_chain->next;
    }

    free(temp_key_chain);
    free(key_chain);
}

void keyChainStoreData(KeyChain *key_chain, void *data)
{
    if (key_chain == NULL || data == NULL)
    {
        return;
    }

    keyStoreData(key_chain->key, data);
}

void keyChainAccessData(KeyChain *key_chain, void *dest)
{
    if (key_chain == NULL)
    {
        return;
    }

    keyAccessData(key_chain->key, dest, key_chain->type, key_chain->units);
}

KeyChain *findKeyChain(KeyChain *origin, int index)
{
}

void keyChainMoveData(KeyChain *src, KeyChain *dest)
{
}

KeyChain *getNext(KeyChain *key_chain)
{
}

KeyChain *getPrevious(KeyChain *key_chain, KeyChain *origin)
{
}

void keyChainClearData(KeyChain *origin)
{
}

void keyChainCompleteRelease(KeyChain *origin)
{
}

/*
------------------------------------------------------------------------------
DO NOT EDIT THE FUNCTIONS BELOW - TESTING PURPOSES
*/

Key *getKey(KeyChain *key_chain)
{
    return key_chain->key;
}

DataType getType(KeyChain *key_chain)
{
    return key_chain->type;
}

int getUnits(KeyChain *key_chain)
{
    return key_chain->units;
}

int getIndex(KeyChain *key_chain)
{
    return key_chain->index;
}