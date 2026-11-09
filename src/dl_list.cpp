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

#define _DEBUG
#include "log.cpp"
#include "term_colors.h"

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


// FIXME zero links to head and tail
// Functions
//-------------------------------------------------------------------------------------------

// Sys functions
int     InitList                (List * const list, size_t size);
int     ListDestructor          (List * list);
int     VerifyListDef           (const List * const list, const char *func_name);
int     PrintDLList             (const List * const list);
int     PrintListLikeArray      (const List * const list);
// Change elements
int     ListAddAfter            (List * const list, const list_element_t argument, const size_t index_in_array);
int     ListAddBefore           (List * const list, const list_element_t argument, const size_t index_in_array);
int     ListAddHead             (List * const list, const list_element_t argument);
int     ListAddTail             (List * const list, const list_element_t argument);
int     ListDel                 (List * const list, size_t del_index_in_list);
size_t  FindFreeCell            (const List * const list);
size_t  ListFinderByIndex       (const List * const list, size_t index);


#define VerifyList(List_p) VerifyListDef(List_p, __FUNCTION__);


// GraphViz
//-------------------------------------------------------------------------------------------

FILE *gv = NULL;

#define fp(string, ...)  fprintf(gv, string, ## __VA_ARGS__);

#define PrintDLListGV(list_p) PrintDLListGV_DEF(list_p, __LINE__)

int PrintDLListGV_DEF(const List * const list, const int name)
{
    VerifyList(list);
    #ifndef _GV
        #define _GV
        extern FILE *gv;
        gv = fopen("DL_list.gv", "w");
    #endif

    // graph info
    fp("\n\ndigraph %d {\n", name);
    fp("rankdir=LR; splines=ortho; nodesep = 1; bgcolor=\"#FFFFFF\";");
    fp("node [shape = Mrecord, style = filled, fillcolor = \"#626ae0\", fontcolor = \"#ffffff\", fontname=\"Helvetica-Bold\"];");

    // create blocks
    for (size_t i = 0; i < list->size; i++)
    {
        fp("n%-5zu [label=\"Array index %5zu.| .arg = " PR_LIST_EL " |{ .prev = %5zd | .next = %5zd}\"];\n", i, i, list->data[i].var, list->data[i].prev, list->data[i].next);
    }
    // set to line
    for (size_t i = 1; i < list->size; i++)
    {
        fp("n%zu -> n%zu [style=invis, weight=100];\n", i-1, i);
    }

    // create data links
    size_t iter_count = 0;
    for (size_t list_index = list->head; list_index < list->size; list_index = list->data[list_index].next)
    {
        size_t next = list->data[list_index].next;
        size_t prev = list->data[list_index].prev;

        // correct link
        if (list_index == list->data[next].prev)
        {
            fp("n%zu -> n%zu [constraint=false, dir=both];", list_index, next);
        }
        // link to next error
        else if (list_index != list->data[next].prev)
        {
            fp("n%zu -> n%zu [constraint=false, color = red];\n", list_index, next);
        }
        // link to prev error
        else if (list_index != list->data[prev].next)
        {
            fp("n%zu -> n%zu [constraint=false, color = red];\n", prev, list_index);
        }
        // end of links
        if ((list_index == 0) || (list_index == -1))
        {
            break;
        }
        // loop
        if (++iter_count > list->size)
        {
            printf("--> List loop!\n"); // FIXME err code
            break;
        }
    }

    // create free links
    if (list->free != ((size_t)-1))
    {
        iter_count = 0;
        for (size_t list_index = list->free; list_index < list->size; list_index = list->data[list_index].next)
        {
            size_t next = list->data[list_index].next;


            fp("n%zu -> n%zu [constraint=false, color = \"#3fc236\", style = bold];", list_index, next);

            // end of links
            if ((list_index == 0) || (list_index == -1))
            {
                break;
            }
            // loop
            if (++iter_count > list->size)
            {
                printf("--> List loop!\n"); // FIXME err code
                break;
            }
        }
        fp("free [label = \"FREE\", fillcolor = \"#00a527\"];\n");
        fp("free:e -> n%zd:n;\n", list->free);
    }


    // create head and tail
    fp("head [label = \"HEAD\", fillcolor = orange];\n");
    fp("tail [label = \"TAIL\", fillcolor = orange];\n");

    fp("head:e -> n%zd:n;\n", list->head);
    fp("tail:e -> n%zd:n;\n", list->tail);
    fp("}");

    return 0;
}

int PrintDLListGV_DEF_V1(const List * const list, const int name)
{
            VerifyList(list);
            #ifndef _GV
                #define _GV
                extern FILE *gv;
                gv = fopen("DL_list.gv", "w");
            #endif

            // graph info
            fp("\n\ndigraph %d {\n", name);
            fp("node [shape = box, shape = Mrecord]; bgcolor = white; rankdir=LR;\n");
    // print zero
    {
        fp("\t%zu  [label = \"                          \
            List element %zu  |                             \
            array index [%zu] |                             \
            previous = %zu    |                             \
            argument = " PR_LIST_EL " |                     \
            next = %zd\"];\n",                              \
            NULL,                                           \
            NULL,                                           \
            NULL,                                           \
            list->data[0].prev,                             \
            list->data[0].var,                              \
            list->data[0].next  );
    }
    // print head
    fp("\thead [label = \"head\", style=filled, color = orange];\n");
    fp("\thead -> %zu\n", list->head);
    // print tail
    fp("\ttail [label = \"tail\", style=filled, color = orange];\n");
    fp("\ttail -> %zu\n", list->tail);

    // list elements
    size_t array_index = list->head;
    for (size_t list_index = 1; array_index < list->size; list_index++)
    {
        // fp("{rank=same; %zu; %zu;}\n", array_index, list->data[array_index].next);
        // print node
        {
            fp("\t%zu  [label = \"                          \
                List element %zu  |                             \
                array index [%zu] |                             \
                previous = %zu    |                             \
                argument = " PR_LIST_EL " |                     \
                next = %zd\"                                    \
                style = filled, fillcolor = \"#7dff97\", color = \"#3fb950\", fontcolor = \"#000000\", rank = same; 0; %zu];\n",               \
                array_index,                                    \
                list_index,                                     \
                array_index,                                    \
                list->data[array_index].prev,                   \
                list->data[array_index].var,                    \
                list->data[array_index].next,                   \
                array_index);
        }
        // link to next
        fp("\t%zu -> %zu [label = \"next\", color = red];\n", array_index, list->data[array_index].next);
        // link to prev
        fp("\t%zu -> %zu [label = \"prev\", color = blue];\n", array_index, list->data[array_index].prev);


        // go to next index
        array_index = list->data[array_index].next;

        // check array borders and link to zero
        if ((list_index > list->size) || (array_index == 0))
            break;
    }

    // free elements
    size_t free_i = list->free;
    for (size_t list_index = 0; free_i < list->size; list_index++)
    {
        // print free node
        {
            fp("\t%zd  [label = \"                          \
                Free element %zu  |                             \
                array index [%zu] |                             \
                previous = %zu    |                             \
                argument = " PR_LIST_EL " |                     \
                next = %zd\",                                   \
                style = filled, fillcolor = \"#84a7f8\"    color = \"#5d5da4\"    fontcolor = \"#000000\"];\n",               \
                free_i,                                         \
                list_index,                                     \
                free_i,                                         \
                list->data[free_i].prev,                        \
                list->data[free_i].var,                         \
                list->data[free_i].next  );
        }
        // link to next
        fp("\t%zd -> %zd [label = \"next free\", color = darkgreen];\n", free_i, list->data[free_i].next);

        // go to next free index
        free_i = list->data[free_i].next;
        if((free_i == -1) || (free_i == 0))
            break;
    }

    fp("}");

    return 0;
}

const int SYS_COMMAND_LENGTH = 100;
void CompPng(const char *name)
{
    #ifdef _GV
        #undef _GV
        extern FILE *gv;
        fclose(gv);
        gv = NULL;
        char sys_com[SYS_COMMAND_LENGTH];
        snprintf(sys_com, SYS_COMMAND_LENGTH, "dot -Tpng DL_list.gv -o %s.png", name);
        system(sys_com);
    #endif
}

// MAIN
//-------------------------------------------------------------------------------------------

int main(void)
{
    List list = {};
    InitList(&list, 10);

    ListAddTail(&list, 80);
    ListAddTail(&list, 90);
    PrintDLListGV(&list);
    CompPng("pic1");

    ListAddHead(&list, 40);
    ListAddHead(&list, 30);
    PrintDLListGV(&list);
    CompPng("pic2");

    ListDel(&list, list.tail);
    PrintDLListGV(&list);
    CompPng("pic3");

    ListDel(&list, 3);
    PrintDLListGV(&list);
    CompPng("pic4");

    // for (int i = 0; i <= 15; i++)
    //     ListAddAfter(&list, 100 + i, i);

    // ListAddBefore(&list, 52, 1);

    // PrintDLListGV(&list);
    // CompPng("pic1");
    // PrintListLikeArray(&list);
    // PrintDLList(&list);

    // ListDel(&list, 2);
    // ListAddAfter(&list, 52, 4);
    // ListAddAfter(&list, 67, 8);

    // PrintDLListGV(&list);
    // CompPng("pic2");
    // PrintListLikeArray(&list);
    // PrintDLList(&list);


    // // ListAddAfter(&list, 1000, 5);

    // VerifyList(&list);
    // ListDestructor(&list);
    // // printf("After delete list:\n");
    // VerifyList(&list);
    return 0;
}


// Functions
//-------------------------------------------------------------------------------------------

// TODO next free index like next index
// TODO add before this element

int PrintDLList             (/* FILE * stream, */const List * const list)
{
    assert(list);
    assert(list->data);

    // TODO
    // fprintf(stream, ".....");
    // stderr

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
            printf("|     --> Break printing on " PYELLOW "%3zd" DEF_COL " index.     |\n", i);
            printf("|         List length = <" PYELLOW "%6zu" DEF_COL ">           |\n", repeat_count);
            break;
        }
    }
    printf("\\------------------------------------------/\n");

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

    // for (size_t i = 1; i < list->size; i++)
    // {
    //     if (list->data[i].next == -1)
    //     {
    //         free_index = i;
    //         break;
    //     }
    // }

    free_index = list->free;

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
    while ((index_in_list != index) && (repeat_count++ < list->size) && (list->data[index_finder].next != 0))
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
    if (index != index_in_list)
    {
        printf("--> Try to add element out of list!\n");
        return -1; // FIXME err code
    }
    if (repeat_count >= list->size)
    {
        PR("--> List loop!\n");
        return 1; // FIXME err code
    }
    PR(PYELLOW "Found index array[%zu] == list[%zu].\n" DEF_COL, index_finder, index_in_list);
    return index_finder;
}


// TODO индекс должен указывать на ячейку массива, а не логический индекс в списке
int ListAddAfter            (List * const list, const list_element_t arg, const size_t paste_index)
{
    VerifyList(list);
    assert(list);
    assert(list->data);

    if (list->free == FREE_ELEMENT_NOT_FOUND)
    {
        printf("--> Could not find free index! (index = %zu)\n", paste_index);
        return -1; // FIXME err_code
    }

// add to the midle
    PR("* Find paste after [%zu];\n", paste_index);

    // Write data to next of find element

    // remember next free element
    size_t next_free_index = list->data[list->free].next;

    // remember next index in new element
    list->data[list->free].next = list->data[paste_index].next;

    // prev of next element is new
    list->data[list->data[paste_index].next].prev = list->free;

    // next of paste element is new
    list->data[paste_index].next = list->free;

    // prev index is new element
    list->data[list->free].prev = paste_index;

    // write arg in new element
    list->data[list->free].var = arg;

    // new free index
    list->free = next_free_index;

    VerifyList(list);


    return 0;
}

int ListAddHead             (List * const list, const list_element_t arg)
{
    VerifyList(list);
    // new head index
    size_t new_head = list->free;
    // new free index
    list->free = list->data[list->free].next;

    PR("\n* Write new head element.\n");
    PR("\tOld head = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->head].prev, list->data[list->head].var, list->data[list->head].next);

    // new element links to 0, next
    list->data[new_head] = {.prev = 0, .var = arg, .next = list->head};
    PR("\tNew head = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[new_head].prev, list->data[new_head].var, list->data[new_head].next);

    // old head links to new
    list->data[list->head].prev = new_head;
    list->data[0].next          = new_head;
    PR("\tOld head = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->head].prev, list->data[list->head].var, list->data[list->head].next);

    if (list->data[new_head].next == 0)
    {
        list->tail = new_head;
    }
    // new head index
    list->head = new_head;

    VerifyList(list);
    return 0;
}

int ListAddTail             (List * const list, const list_element_t arg)
{
    VerifyList(list);

    // new tail index
    size_t new_tail = list->free;
    // new free index
    list->free = list->data[list->free].next;

    PR("\n* Write new tail element.\n");
    PR("\tOld tail = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->tail].prev, list->data[list->tail].var, list->data[list->tail].next);

    // get new element
    // new element links to prev, 0
    list->data[new_tail] = {.prev = list->tail, .var = arg, .next = 0};
    PR("\tNew tail = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[new_tail].prev, list->data[new_tail].var, list->data[new_tail].next);

    // old tail links to new
    list->data[list->tail].next = new_tail;
    list->data[0].prev          = new_tail;
    PR("\tOld tail = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->tail].prev, list->data[list->tail].var, list->data[list->tail].next);

    if (list->data[new_tail].prev == 0)
    {
        list->head = new_tail;
    }
    // new tail index
    list->tail = new_tail;

    // VerifyList(list);
    return 0;
}

int ListAddBefore           (List * const list, const list_element_t arg, const size_t index)
{
    return ListAddAfter(list, arg, index-1);
}

int ListDel                 (List * const list, size_t del_index)
{
    VerifyList(list);
    assert(list);
    assert(list->data);

    if ((del_index > 0) && (del_index < list->size))
    {
        if ((list->data[del_index].prev == -1) || (del_index == 0))
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
            if ((list->data[prev].next != 0) && (list->data[next].prev != 0))
                list->data[prev].next = next;
            list->data[next].prev = prev;

            if (list->head == del_index)
                list->head = list->data[del_index].next;
            if (list->tail == del_index)
                list->tail = list->data[del_index].prev;


            list->data[del_index].next = list->free;
            list->free = del_index;

            #ifdef _DEBUG
                list->data[del_index].prev = -1;
                list->data[del_index].var  = POISON;
            #endif

            VerifyList(list);
        }
    }
    // Index out of range
    else
    {
        printf("--> Try to delete element out of list indexes!\n");
        return -1; // FIXME err code
    }
    VerifyList(list);
    return 0;
}

int InitList                (List * const list, size_t size)
{
    PR_FST;

    // Add space to NULL element
    size++;

    list->data = (List_element *) calloc(size, sizeof(List_element));
    if (list->data == NULL)
    {
        perror("--> InitList was crushed");
        return -1; // FIXME err code
    }

    list->size = size;
    list->head = 0;
    list->tail = 0;
    list->free = 1;
    // list->el_count = 0;

    for (size_t i = 1; i < size; i++)
    {
        list->data[i].next = i+1;
    }
    list->data[size-1].next = -1;

    #ifdef _DEBUG
    list->data[0] = {.prev = 0, .var = POISON, .next = 0};
    // for (size_t i = 1; i < list->size; i++)
    // {
    //     list->data[i].next = -1;
    //     list->data[i].prev = -1;
    //     list->data[i].var  = POISON;
    // }
    #endif

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
    list = NULL;

    PR_FED;
    return 0;
}

int DomainExpansion         (List * list)
{
    VerifyList(list);
    assert(list);
    assert(list->data);

    size_t exp_coef = 2;

    List_element *new_address = (List_element *) realloc(list->data, list->size * exp_coef * sizeof(List_element));
    if (new_address == NULL)
    {
        perror("Domain expansion unsuccessful.");
        return -1; // FIXME
    }
    list->data = new_address;

    for (size_t i = list->size; i < list->size*exp_coef-1; i++)
    {
        list->data[i].next = i+1;
    }
    list->data[list->size*exp_coef-1].next = list->free;
    list->free = list->data[list->size].next;
    list->size *= exp_coef;
    
    return 0;
}



