#include <libseis.h>

/* This function will not be exported and is not
 * directly callable by users of this library.
 */
int internal_function() {
    return 0;
}

int lib_func() {
    return internal_function();
}
