#include     <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include      <time.h>
#include      <math.h>
#include   <stdbool.h>
#include    <assert.h>
#include  <sys/stat.h>
#include    <unistd.h>
#include     <fcntl.h>
#include <sys/types.h>
#include     <ctype.h>
#include    <stdarg.h>

#define _PRT
#include "log.cpp"
#include "term_colors.h"

const size_t LIST_LENGTH = 10;

typedef int list_element_t;
#define PR_LIST_EL "%8d"
const list_element_t POISON = 67676767;

struct List_element
{
    size_t prev;
    list_element_t var;
    size_t next;
};

struct List
{
    List_element *data;
    size_t head;
    size_t tail;
    size_t size;
    size_t free;
    size_t el_count;
};

// Functions
//-------------------------------------------------------------------------------------------

int PrintDLList(const List * const list)
{
    return 0;
}


int VerifyList(const List * const list)
{
    assert(list);
    PR_FST;

    PR("List data:\n");
    PR("Head = %zu;  \nTail = %zu;  \nFree = %zd;  \nSize = %zu;  \n", list->head, list->tail, list->free, list->size);

    PR("\nList like arrays:\n");
    PR("/--------------------------------\\\n");
    PR("| Index | Prev | Variable | Next |\n");
    for (size_t i = 0; i < list->size; i++)
    {
        PR("|--------------------------------|\n");
        PR("| %5zu | %4zd | " PR_LIST_EL " | %4zd |\n", i, list->data[i].prev, list->data[i].var, list->data[i].next);
    }
    PR("\\--------------------------------/\n");


    PR("\nList in correct order:\n");
    PR("/--------------------------------\\\n");
    PR("| Index | Prev | Variable | Next |\n");
    size_t repeat_count = 0;
    for (size_t i = list->head; i < list->size; i)
    {
        PR("|--------------------------------|\n");
        PR("| %5zu | %4zd | " PR_LIST_EL " | %4zd |\n", i, list->data[i].prev, list->data[i].var, list->data[i].next);
        i = list->data[i].next;
        repeat_count++;
        if ((repeat_count >= list->size) || (i == 0))
        {
            PR("|--------------------------------|\n");
            PR("|--> Break printing on %3zu index.|\n", i);
            break;
        }
    }
    PR("\\--------------------------------/\n");

    PR(DEF_COL);
    PR_FED;
    return 0;
}

// COMP
size_t FindFreeCell(const List * const list)
{
    size_t free_index = -1;

    for (size_t i = 1; i < list->size; i++)
    {
        if (list->data[i].next == -1)
        {
            free_index = i;
            break;
        }
    }
    if (free_index == -1)
    {
        PR("--> List overflow!\n");
        return -1; // FIXME err code
    }

    return free_index;
}

enum List_errors {
    FREE_ELEMENT_NOT_FOUND = -1
};

// COMP
int ListAdd(List * const list, const list_element_t arg, const size_t index)
{
    // find free cell
    list->free = FREE_ELEMENT_NOT_FOUND;
    list->free = FindFreeCell(list);
    if (list->free == FREE_ELEMENT_NOT_FOUND)
    {
        printf("--> Could not find free index!\n");
        return -1; // FIXME err_code
    }


// add to tail or head
    if ((index == 0) || (index == list->tail))
    {
        if (index == 0)
        {
            PR("\n* Write new head element.\n");
            PR("\tOld head = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->head].prev, list->data[list->head].var, list->data[list->head].next);
            // get new element
            // new element links to 0, next
            list->data[list->free] = {.prev = 0, .var = arg, .next = list->head};
            PR("\tNew head = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->free].prev, list->data[list->free].var, list->data[list->free].next);

            // old head links to new
            if (list->head != 0)
            {
                list->data[list->head].prev = list->free;
            }
            PR("\tOld head = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->head].prev, list->data[list->head].var, list->data[list->head].next);

            // new head index
            list->head = list->free;

            VerifyList(list);
        }
        if (index == list->tail)
        {
            PR("\n* Write new tail element.\n");
            PR("\tOld tail = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->tail].prev, list->data[list->tail].var, list->data[list->tail].next);

            // get new element
            // new element links to prev, 0
            list->data[list->free] = {.prev = list->tail, .var = arg, .next = 0};
            PR("\tNew tail = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->free].prev, list->data[list->free].var, list->data[list->free].next);

            // old links to new
            if (list->tail != 0)
            {
                list->data[list->tail].next = list->free;
            }
            PR("\tOld tail = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->tail].prev, list->data[list->tail].var, list->data[list->tail].next);

            // new tail index
            list->tail = list->free;

            VerifyList(list);
        }
    }
// add to the midle
    else
    {
        // find element to add
        size_t index_finder = list->head;
        size_t repeat_count = 0;
        while ((index_finder != index) && (repeat_count++ < list->size))
        {
            if (list->data[index_finder].next != -1)
                index_finder = list->data[index_finder].next;
            else
            {
                PR("--> Index is not in list!\n");
                return -1; // FIXME err code
            }
        }
        if (repeat_count >= list->size)
        {
            PR("--> List loop!\n");
            return 1; // FIXME err code
        }
        PR("* Find paste element [%zu];\n", index_finder);

        // Write data to next of find element

        // remember next index in new element
        list->data[list->free].next = list->data[index_finder].next;

        // prev of next element is new
        list->data[list->data[index_finder].next].prev = list->free;

        // next of paste element is new
        list->data[index_finder].next = list->free;

        // prev index is new element
        list->data[list->free].prev = index_finder;

        // write arg in new element
        list->data[list->free].var = arg;

        list->free = -1; // FIXME

        VerifyList(list);
    }

    return 0;
}

// TODO
int ListDel(list_element_t)
{
    return 0;
}

// COMP
int InitList(List *list)
{
    PR_FST;

    list->data = (List_element *) calloc(LIST_LENGTH, sizeof(List_element));
    if (list->data == NULL)
    {
        perror("--> InitList was crushed");
        return -1; // FIXME err code
    }

    list->size = LIST_LENGTH;
    list->head = 0;
    list->tail = 0;
    list->free = 0;
    list->el_count = 0;

    list->data[0] = {.prev = 0, .var = POISON, .next = 0};
    for (size_t i = 1; i < list->size; i++)
    {
        list->data[i].next = -1;
        list->data[i].prev = -1;
        list->data[i].var  = POISON;
    }

    VerifyList(list);

    PR_FED;
    return 0;
}


// MAIN
//-------------------------------------------------------------------------------------------

int main(void)
{
    List list = {};
    InitList(&list);

    for (int i = 0; i <= 2; i++)
        ListAdd(&list, 100 + i*10 + 1, i);


    for (int i = 0; i <= 2; i++)
        ListAdd(&list, 100 + i*10 + 2, i+1);

    // ListAdd(&list, 99, 0);
    // ListAdd(&list, 105, 1);
    // ListAdd(&list, 125, list.tail);
    // ListAdd(&list, 67, 0);


    // ListAdd(&list, 1000, 5);

    VerifyList(&list);
    return 0;
}

