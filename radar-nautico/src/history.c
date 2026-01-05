#include <stdlib.h>

#include "history.h"
#include "util.h"

BaseDados *history_append(BaseDados *head, const Frame *frame_copy) {
    BaseDados *node = NULL;
    BaseDados *tail = NULL;

    if (frame_copy == NULL) {
        return head;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return head;
    }

    node->frame.numero = frame_copy->numero;
    node->frame.entidades = entidade_clone_list(frame_copy->entidades);
    if (frame_copy->entidades != NULL && node->frame.entidades == NULL) {
        free(node);
        return head;
    }
    node->next = NULL;

    if (head == NULL) {
        return node;
    }

    tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;

    return head;
}

Frame *history_get_frame(BaseDados *head, int index) {
    int i = 0;
    BaseDados *iter = head;

    while (iter != NULL) {
        if (i == index) {
            return &iter->frame;
        }
        iter = iter->next;
        i++;
    }

    return NULL;
}

void history_free_from(BaseDados *node) {
    while (node != NULL) {
        BaseDados *next = node->next;
        entidade_free_list(node->frame.entidades);
        free(node);
        node = next;
    }
}

void history_free_all(BaseDados *head) {
    history_free_from(head);
}
