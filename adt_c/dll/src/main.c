#include "dll.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    //testing 
    dll* list = create_dll();
    
    add_first(list, 10);
    add_last(list, 20);
    add(list, 30);
    
    Node* first = get_first(list);
    if (first) {
        add_after(list, 15, first);
    }
    
    print_dll(list);   
    
    rm_first(list);
    rm_last(list);
    
    print_dll(list);   
    
    free_dll(list);
    return 0;
}
