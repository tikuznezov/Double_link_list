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

// #define _DEBUG
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
    // size_t el_count;
};

enum List_errors {
    FREE_ELEMENT_NOT_FOUND = -1
};

// Functions
//-------------------------------------------------------------------------------------------

int     VerifyListDef           (const List * const list, const char *func_name);
int     PrintDLList             (const List * const list);
int     PrintListLikeArray      (const List * const list);
int     InitList                (List * const list);
int     ListAdd                 (List * const list, const list_element_t arg, const size_t index);
int     ListDel                 (List * const list, size_t del_index_in_list);
int     ListDestructor          (List *list);
size_t  FindFreeCell            (const List * const list);
size_t  ListFinderByIndex       (const List * const list, size_t index);


#define VerifyList(List_p) VerifyListDef(List_p, __FUNCTION__);

// MAIN
//-------------------------------------------------------------------------------------------

int main(void)
{
    List list = {};
    InitList(&list);

    for (int i = 0; i <= 6; i++)
        ListAdd(&list, 100 + i, i);

    // ListAdd(&list, 99, 0);
    // ListAdd(&list, 105, 1);
    // ListAdd(&list, 125, list.tail);
    // ListAdd(&list, 67, 0);

    ListDel(&list, 2);
    ListDel(&list, 0);
    ListDel(&list, 2);
    ListDel(&list, 0);
    ListDel(&list, 0);
    ListDel(&list, 0);
    ListDel(&list, 0);
    ListDel(&list, 0);
    ListDel(&list, 0);
    PrintDLList(&list);

    // ListAdd(&list, 1000, 5);

    VerifyList(&list);
    ListDestructor(&list);
    printf("After delete list:\n");
    VerifyList(&list);
    return 0;
}


// Functions
//-------------------------------------------------------------------------------------------


int PrintDLList             (const List * const list)
{
    assert(list);
    assert(list->data);

    printf("\nList:\n");
    printf("/------------------------------------------\\\n");
    printf("| Index | Array i | Prev | Variable | Next |\n");
    size_t repeat_count = 0;
    size_t i = list->head;
    for (size_t list_index = 0; i < list->size; list_index++)
    {
        printf("|------------------------------------------|\n");
        printf("| %5zu | [%5zu] | %4zd | " PR_LIST_EL " | %4zd |\n", list_index, i, list->data[i].prev, list->data[i].var, list->data[i].next);
        i = list->data[i].next;
        repeat_count++;
        if ((repeat_count >= list->size) || (i == 0))
        {
            printf("|------------------------------------------|\n");
            printf("|     --> Break printing on " PYELLOW "%3zu" DEF_COL " index.     |\n", i);
            printf("|         List length = <" PYELLOW "%6zu" DEF_COL ">           |\n", repeat_count);
            break;
        }
    }
    printf("\\-------|----------------------------------/\n");

    printf(DEF_COL);
    return 0;
}


int PrintListLikeArray      (const List * const list)
{
    assert(list);
    assert(list->data);

    printf("\nList like arrays:\n");
    printf("/--------------------------------\\\n");
    printf("| Index | Prev | Variable | Next |\n");
    for (size_t i = 0; i < list->size; i++)
    {
        printf("|--------------------------------|\n");
        printf("| %5zu | %4zd | " PR_LIST_EL " | %4zd |\n", i, list->data[i].prev, list->data[i].var, list->data[i].next);
    }
    printf("\\--------------------------------/\n");

    return 0;
}


int VerifyListDef           (const List * const list, const char *func_name)
{
    PR_FST;
    assert(func_name);

    if (list == NULL)
    {
        printf("--> List doesn't exist! (&list == NULL)!\n");
        return 1; // FIXME err code
    }

    if (list->data == NULL)
    {
        printf("* List was deleted. (data is NULL pointer)\n");
        return 0;
    }

    #ifdef _DEBUG
        printf("Called by \"" PYELLOW "%s" DEF_COL "\".\n\n", func_name);

        printf("List data:\n");
        printf("Head = %zu;  \nTail = %zu;  \nFree = %zd;  \nSize = %zu;  \n", list->head, list->tail, list->free, list->size);

        PrintDLList(list);
        PrintListLikeArray(list);
    #endif


    PR_FED;
    return 0;
}


size_t FindFreeCell         (const List * const list)
{
    VerifyList(list);
    assert(list);
    assert(list->data);

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


size_t ListFinderByIndex    (const List * const list, size_t index)
{
    VerifyList(list);
    assert(list);
    assert(list->data);

    size_t index_finder  = list->head;
    size_t index_in_list = 0;
    size_t repeat_count = 0;
    while ((index_in_list != index) && (repeat_count++ < list->size))
    {
        if (list->data[index_finder].next != -1)
        {
            index_finder = list->data[index_finder].next;
            index_in_list++;
        }
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
    PR(PYELLOW "Found index array[%zu] == list[%zu].\n" DEF_COL, index_finder, index_in_list);
    return index_finder;
}


int ListAdd                 (List * const list, const list_element_t arg, const size_t index)
{
    VerifyList(list);
    assert(list);
    assert(list->data);

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
        size_t index_finder = -1;
        index_finder = ListFinderByIndex(list, index);

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


int ListDel                 (List * const list, size_t del_index_in_list)
{
    VerifyList(list);
    assert(list);
    assert(list->data);

    if ((del_index_in_list >= 0) && (del_index_in_list < list->size))
    {
        // find element to add
        size_t del_index = -1;
        del_index = ListFinderByIndex(list, del_index_in_list);

        if ((list->data[del_index].next == -1) || (list->data[del_index].next == -1))
        {
            printf(PRED "--> Try to delete void element.\n" DEF_COL);
            return -1; // FIXME err code
        }
        // Delete list element
        else
        {
            size_t prev = list->data[del_index].prev;
            size_t next = list->data[del_index].next;

            // link prev to next
            list->data[prev].next = next;
            list->data[next].prev = prev;

            if (list->head == del_index)
                list->head = list->data[del_index].next;
            if (list->tail == del_index)
                list->tail = list->data[del_index].prev;

            list->data[del_index].next = -1;
            list->data[del_index].prev = -1;
            list->data[del_index].var  = POISON;
            VerifyList(list);
        }
    }
    // Index out of range
    else
    {
        printf("--> Try to delete element out of list indexes!\n");
        return -1; // FIXME err code
    }
    return 0;
}


int InitList                (List * const list)
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
    // list->el_count = 0;

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


int ListDestructor          (List *list)
{
    PR_FST;
    VerifyList(list);
    assert(list);
    assert(list->data);

    PR("* Freeing list data array...\n");
    free(list->data);
    PR("* List->data successfully freed.\n");

    // *list = {.data = NULL, .el_count = 0, .free = 0, .head = 0, .size = 0, .tail = 0};
    *list = {};

    PR_FED;
    return 0;
}
