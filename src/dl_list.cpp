#include "list.h"

#define VerifyList(List_p) VerifyListDef(List_p, __FUNCTION__);
#include "list_gv.cpp"

// Functions
//-------------------------------------------------------------------------------------------

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
        printf("| %5zu | [%5zu] | %4zd | "         PR_LIST_EL       " | %4zd |\n", \
                list_index, i, list->data[i].prev, list->data[i].var, list->data[i].next);
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
    // PR_FST;
    assert(func_name);

    // HTML log fuction start
    HTML_HEADER(list_html_output, 3, "Start list verifying... Called by \"%s\".", func_name);

    if (list == NULL)
    {
        printf("--> List doesn't exist! (&list == NULL)!\n");
        return LIST_DOES_NOT_EXIST;
    }

    if (list->data == NULL)
    {
        HTML_PR(list_html_output, "* List was deleted. (data is NULL pointer)\n");
        return 0;
    }

    size_t iter_count = 0;
    size_t index = list->head;
    while ((index < list->size) && (iter_count < list->size))
    {
        iter_count++;
        index = list->data[index].next;
        if (index == 0) break;
    }
    if (iter_count >= list->size)
    {
        HTML_PR(list_html_output, PRED "List loop!\n" DEF_COL);
    }

    #ifdef _DEBUG
        HTML_PR(list_html_output, "Called by \"%s\".\n\n", func_name);

        HTML_PR(list_html_output, "List data:\n");
        HTML_PR(list_html_output, "Head = %zu;  <br>Tail = %zu;  <br>Free = %zd;  <br>Size = %zu;  <br>", list->head, list->tail, list->free, list->size);

        // PrintDLList(list);
        // PrintListLikeArray(list);

        PrintDLListGV(list);
        CompPng("ListVerify");
    #endif

    HTML_HEADER(list_html_output, 4, "Verifying completed. Called by \"%s\".", func_name);
    // PR_FED;
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
        HTML_PR(list_html_output, "--> List overflow!\n");
        return LIST_OVERFLOW;
    }

    return free_index;
}


size_t ListFinderByIndex    (const List * const list, size_t index)
{
    VerifyList(list);
    assert(list);
    assert(list->data);

    if (list->head == 0) return -1;

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
            HTML_PR(list_html_output, "--> Index is not in list!\n");
            return INDEX_IS_NOT_IN_LIST;
        }
    }
    if (index != index_in_list)
    {
        HTML_PR(list_html_output, "--> Try to add element out of list!\n");
        return ADD_OUT_OF_LIST_INDEXES;
    }
    if (repeat_count >= list->size)
    {
        HTML_PR(list_html_output, "--> List loop!\n");
        return LIST_LOOP;
    }
    HTML_PR(list_html_output, PYELLOW "Found index array[%zu] == list[%zu].\n" DEF_COL, index_finder, index_in_list);
    return index_finder;
}


int ListAddAfter            (List * const list, const list_element_t arg, const size_t paste_index)
{
    VerifyList(list);
    assert(list);
    assert(list->data);

    if (paste_index >= list->size)
    {
        printf("Try to add element after out of range index!");
        return ADD_OUT_OF_LIST_INDEXES;
    }

    if (list->free == FREE_ELEMENT_NOT_FOUND)
    {
        if (DomainExpansion(list) != 0)
        {
            printf("--> Could not find free index! (index = %zu)\n", paste_index);
            return NOT_FIND_FREE_INDEX;
        }
    }

    if (list->data[paste_index].prev == -1)
    {
        printf("--> Add index is free cell, this element out of list!\n");
        return ADD_ELEMENT_AFTER_NOT_LIST_INDEX;
    }
// add to the midle
    HTML_PR(list_html_output, "* Find paste after [%zu];\n", paste_index);

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

    if (paste_index == list->tail)
        list->tail = list->free;
    if (paste_index == 0)
        list->head = list->free;

    // new free index
    list->free = next_free_index;

    VerifyList(list);


    return 0;
}

int ListAddHead             (List * const list, const list_element_t arg)
{
    VerifyList(list);
    if (list->free == FREE_ELEMENT_NOT_FOUND)
    {
        if (DomainExpansion(list) != 0)
        {
            printf("--> List overflow!\n");
            return -1;
        }
    }
    // new head index
    size_t new_head = list->free;
    // new free index
    list->free = list->data[list->free].next;

    HTML_PR(list_html_output, "\n* Write new head element.\n");
    HTML_PR(list_html_output, "\tOld head = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->head].prev, list->data[list->head].var, list->data[list->head].next);

    // new element links to 0, next
    list->data[new_head] = {.prev = 0, .var = arg, .next = list->head};
    HTML_PR(list_html_output, "\tNew head = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[new_head].prev, list->data[new_head].var, list->data[new_head].next);

    // old head links to new
    list->data[list->head].prev = new_head;
    list->data[0].next          = new_head;
    HTML_PR(list_html_output, "\tOld head = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->head].prev, list->data[list->head].var, list->data[list->head].next);

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

    if (list->free == FREE_ELEMENT_NOT_FOUND)
    {
        if (DomainExpansion(list) != 0)
        {
            printf("--> List overflow!\n");
            return -1;
        }
    }

    // new tail index
    size_t new_tail = list->free;
    // new free index
    list->free = list->data[list->free].next;

    HTML_PR(list_html_output, "\n* Write new tail element.\n");
    HTML_PR(list_html_output, "\tOld tail = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->tail].prev, list->data[list->tail].var, list->data[list->tail].next);

    // get new element
    // new element links to prev, 0
    list->data[new_tail] = {.prev = list->tail, .var = arg, .next = 0};
    HTML_PR(list_html_output, "\tNew tail = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[new_tail].prev, list->data[new_tail].var, list->data[new_tail].next);

    // old tail links to new
    list->data[list->tail].next = new_tail;
    list->data[0].prev          = new_tail;
    HTML_PR(list_html_output, "\tOld tail = {.prev = %zx, .var = " PR_LIST_EL ", .next = %zx}\n", list->data[list->tail].prev, list->data[list->tail].var, list->data[list->tail].next);

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
    if ((index == 0) || (index >= list->size)) 
    {
        printf("Try to add element before out of range index!\n");
        return ADD_ELEMENT_BEFORE_NOT_LIST_INDEX;
    }
    return ListAddAfter(list, arg, list->data[index].prev);
}

int ListDel                 (List * const list, size_t del_index)
{
    VerifyList(list);
    assert(list);
    assert(list->data);

    if ((del_index <= 0) || (del_index >= list->size))
    {
        printf("--> Try to delete element out of list indexes!\n");
        return DELETE_ELEMENT_OUT_OF_LIST_INDEXES;
    }

    // Index out of range
    if ((list->data[del_index].prev == -1) || (del_index == 0))
    {
        printf(PRED "--> Try to delete void element.\n" DEF_COL);
        return DELETE_FREE_ELEMENT;
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
        list->data[del_index].prev = -1;
        list->free = del_index;

        // TODO ONDEBUG
        #ifdef _DEBUG
        list->data[del_index].var  = POISON;
        #endif

        VerifyList(list);
    }

    VerifyList(list);
    return 0;
}

int ListConstructor         (List * const list, size_t size)
{
    // PR_FST;

    // Add space to NULL element
    size++;

    list->data = (List_element *) calloc(size, sizeof(List_element));
    if (list->data == NULL)
    {
        perror("--> InitList was crushed");
        return CANT_GET_MEMORY_TO_CREATE_LIST;
    }

    list->size = size;
    list->head = 0;
    list->tail = 0;
    list->free = 1;

    for (size_t i = 1; i < size; i++)
    {
        list->data[i].next = i+1;
        list->data[i].prev = -1;
    }
    list->data[size-1].next = -1;

    list->data[0] = {};

    VerifyList(list);

    // PR_FED;
    return 0;
}

int ListDestructor          (List *list)
{
    // PR_FST;
    VerifyList(list);
    assert(list);
    assert(list->data);

    HTML_PR(list_html_output, "* Freeing list data array...\n");
    free(list->data);
    HTML_PR(list_html_output, "* List->data successfully freed.\n");

    // *list = {.data = NULL, .el_count = 0, .free = 0, .head = 0, .size = 0, .tail = 0};
    *list = {};
    list = NULL;

    // PR_FED;
    return 0;
}

int DomainExpansion         (List * list)
{
    VerifyList(list);
    assert(list);
    assert(list->data);

    float exp_coef = 2;
    size_t new_size = (size_t) (list->size * exp_coef);

    List_element *new_address = (List_element *) realloc(list->data, new_size * sizeof(List_element));
    if (new_address == NULL)
    {
        perror("Domain expansion unsuccessful.");
        return CANT_GET_MEMORY_TO_EXPAND_LIST;
    }
    list->data = new_address;

    size_t old_end_index = list->size-1;
    // init new cells, avoid last element
    for (size_t i = old_end_index + 1; i < new_size - 1; i++)
    {
        list->data[i] = {.prev = (size_t)(-1), .var = 0, .next = i+1};
    }
    list->data[new_size-1] = {.prev = (size_t)(-1), .var = 0, .next = list->free};
    list->free = old_end_index + 1;
    list->size = new_size;

    VerifyList(list);
    return 0;
}



// int PrintDLListGV_DEF_V1(const List * const list, const int name)
// {
//             VerifyList(list);
//             #ifndef _GV
//                 #define _GV
//                 extern FILE *gv;
//                 gv = fopen("DL_list.gv", "w");
//             #endif
//
//             // graph info
//             fp("\n\ndigraph %d {\n", name);
//             fp("node [shape = box, shape = Mrecord]; bgcolor = white; rankdir=LR;\n");
//     // print zero
//     {
//         fp("\t%zu  [label = \"                          \
//             List element %zu  |                             \
//             array index [%zu] |                             \
//             previous = %zu    |                             \
//             argument = " PR_LIST_EL " |                     \
//             next = %zd\"];\n",                              \
//             NULL,                                           \
//             NULL,                                           \
//             NULL,                                           \
//             list->data[0].prev,                             \
//             list->data[0].var,                              \
//             list->data[0].next  );
//     }
//     // print head
//     fp("\thead [label = \"head\", style=filled, color = orange];\n");
//     fp("\thead -> %zu\n", list->head);
//     // print tail
//     fp("\ttail [label = \"tail\", style=filled, color = orange];\n");
//     fp("\ttail -> %zu\n", list->tail);
//
//     // list elements
//     size_t array_index = list->head;
//     for (size_t list_index = 1; array_index < list->size; list_index++)
//     {
//         // fp("{rank=same; %zu; %zu;}\n", array_index, list->data[array_index].next);
//         // print node
//         {
//             fp("\t%zu  [label = \"                          \
//                 List element %zu  |                             \
//                 array index [%zu] |                             \
//                 previous = %zu    |                             \
//                 argument = " PR_LIST_EL " |                     \
//                 next = %zd\"                                    \
//                 style = filled, fillcolor = \"#7dff97\", color = \"#3fb950\", fontcolor = \"#000000\", rank = same; 0; %zu];\n",               \
//                 array_index,                                    \
//                 list_index,                                     \
//                 array_index,                                    \
//                 list->data[array_index].prev,                   \
//                 list->data[array_index].var,                    \
//                 list->data[array_index].next,                   \
//                 array_index);
//         }
//         // link to next
//         fp("\t%zu -> %zu [label = \"next\", color = red];\n", array_index, list->data[array_index].next);
//         // link to prev
//         fp("\t%zu -> %zu [label = \"prev\", color = blue];\n", array_index, list->data[array_index].prev);
//
//
//         // go to next index
//         array_index = list->data[array_index].next;
//
//         // check array borders and link to zero
//         if ((list_index > list->size) || (array_index == 0))
//             break;
//     }
//
//     // free elements
//     size_t free_i = list->free;
//     for (size_t list_index = 0; free_i < list->size; list_index++)
//     {
//         // print free node
//         {
//             fp("\t%zd  [label = \"                          \
//                 Free element %zu  |                             \
//                 array index [%zu] |                             \
//                 previous = %zu    |                             \
//                 argument = " PR_LIST_EL " |                     \
//                 next = %zd\",                                   \
//                 style = filled, fillcolor = \"#84a7f8\"    color = \"#5d5da4\"    fontcolor = \"#000000\"];\n",               \
//                 free_i,                                         \
//                 list_index,                                     \
//                 free_i,                                         \
//                 list->data[free_i].prev,                        \
//                 list->data[free_i].var,                         \
//                 list->data[free_i].next  );
//         }
//         // link to next
//         fp("\t%zd -> %zd [label = \"next free\", color = darkgreen];\n", free_i, list->data[free_i].next);
//
//         // go to next free index
//         free_i = list->data[free_i].next;
//         if((free_i == -1) || (free_i == 0))
//             break;
//     }
//
//     fp("}");
//
//     return 0;
// }


