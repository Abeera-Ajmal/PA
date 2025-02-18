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

    KeyChain *first_key = (KeyChain *)keyMalloc(type, units);
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

    int index_of_keychain = 0;
    KeyChain *origin_keychain = origin;
    while (origin_keychain->next != NULL)
    {
        index_of_keychain++;
        origin_keychain = origin_keychain->next;
    }
    new_key_chain->index = index_of_keychain;
    origin_keychain = origin;
    while (origin_keychain->next != NULL)
    {
        origin_keychain = origin_keychain->next;
    }
    origin_keychain->next = new_key_chain;

    free(origin_keychain);
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
        temp_key_chain->index = new_index;
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

    keyStoreData(getKey(key_chain), data);
}

void keyChainAccessData(KeyChain *key_chain, void *dest)
{
    if (key_chain == NULL || dest == NULL)
    {
        return;
    }

    keyAccessData(key_chain->key, dest, key_chain->type, key_chain->units);
}

KeyChain *findKeyChain(KeyChain *origin, int index)
{
    KeyChain *source = origin;
    while (source != NULL)
    {
        if (source->index == index)
        {
            return source;
        }
        source = source->next;
    }
    return NULL;
}

void keyChainMoveData(KeyChain *src, KeyChain *dest)
{
    if (src == NULL || dest == NULL)
    {
        return;
    }

    dest->key = src->key;
    dest->type = src->type;
    dest->index = src->index;
    dest->units = src->units;
    dest->next = src->next;

    if (src->key != NULL && src->key != NULL)
    {
        dest->key = keyMalloc(src->type, src->units);
        if (dest->key != NULL)
        {
            keyStoreData(dest->key, src->key);
        }
    }
}

KeyChain *getNext(KeyChain *key_chain)
{
    if (key_chain == NULL)
    {
        return NULL;
    }
    return key_chain->next;
}

KeyChain *getPrevious(KeyChain *key_chain, KeyChain *origin)
{
    if (key_chain == NULL || origin == NULL)
    {
        return NULL;
    }

    while (origin != NULL)
    {
        if (origin->next == key_chain)
        {
            return origin;
        }
        origin = origin->next;
    }

    return NULL;
}

void keyChainClearData(KeyChain *origin)
{
    if (origin == NULL)
    {
        return;
    }

    KeyChain *current = origin;
    while (current != NULL)
    {
        current->next = NULL;
        current = current->next;
    }
}

void keyChainCompleteRelease(KeyChain *origin)
{
    KeyChain *current_key_chain = origin;
    KeyChain *next_key_chain;

    while (current_key_chain != NULL)
    {
        next_key_chain = current_key_chain->next;

        if (current_key_chain->key != NULL)
        {
            keyFree(current_key_chain->key);
        }

        free(current_key_chain);

        current_key_chain = next_key_chain;
    }
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