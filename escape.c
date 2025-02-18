#include "../include/navigator.h"
#include "../include/keychain.h"
#include "../include/locator.h"
#include "../include/key.h"

typedef struct KeyChain{
    Key* key;
    DataType type;
    int units;
    int index;
    struct KeyChain* next;

} KeyChain;

typedef struct Locator {
    char* identifier;
    uintptr_t address;

} Locator;


void completeDeallocation(VaultNavigator** v_ptr){
    
}

int isFragmented(KeyChain* origin){
    
}

void printLocator(Locator* map) {
        
}


// ---------------- Instructions for Test cases --------------//

/*
You can create an int main() function below to test your escape.c.
To test escape.c, navigate to the src directory in the terminal. You can do this by "cd src".

Then run the following command:

gcc escape.c key.c keychain.c navigator.c locator.c -o test

And then:

./test

Delete your int main() afterwards, or comment it out because it will not let you test other files.
*/
