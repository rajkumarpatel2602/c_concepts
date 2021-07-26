#ifndef __NOTIF_CHAIN_
#define __NOTIF_CHAIN_

#include <stddef.h>
#include "utils.h"
#include "gluethread/glthread.h"

#define MAX_NOTIFY_KEY_SIZE      64
#define NFC_NAME_SIZE            64

typedef (void ) (* nfc_app_cb)(void *, size_t)

typedef struct notif_chain_ele_t{
    char key[MAX_NOTIFY_KEY_SIZE];
    size_t key_size;
    bool_t is_key_set;
    nfc_app_cb app_cb;
    glthread_t glue;
}notif_chain_ele_t;

GLTHREAD_TO_STRUCT(gluethread_glue_to_notif_chain_elem,
        notif_chain_ele_t, glue);

typedef struct notif_chain_t{
    char nfc_name[NFC_NAME_SIZE];
    glthread_t notif_chain_head;
}notif_chain_t;

void
nfc_register_notif_chain(notif_chain_t *nfc,
        notif_chain_ele_t *nfce);

void
nfc_invoke_notif_chain(notif_chain_t *nfc,
        void *arg, size_t arg_size,
        char *key, size_t key_size);

#endif /* ifdef ends here */
