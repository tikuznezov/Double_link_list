#ifndef _LIST_H
#define _LIST_H

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

enum LIST_ERR_TYPES
{
    INDEX_IS_NOT_IN_LIST = 'L' + 'i' + 's' + 't', // "random" number error code
    LIST_DOES_NOT_EXIST,
    LIST_OVERFLOW,
    ADD_OUT_OF_LIST_INDEXES,
    LIST_LOOP,
    NOT_FIND_FREE_INDEX,
    ADD_ELEMENT_AFTER_NOT_LIST_INDEX,
    ADD_ELEMENT_BEFORE_NOT_LIST_INDEX,
    CANT_GET_MEMORY_TO_EXPAND_LIST,
    DELETE_ELEMENT_OUT_OF_LIST_INDEXES,
    DELETE_FREE_ELEMENT,
    CANT_GET_MEMORY_TO_CREATE_LIST,
};

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

// TODO free green color
// TODO подписывать poison в GraphViz

// FIXME zero links to head and tail
// Functions
//-------------------------------------------------------------------------------------------

// Sys functions
int     ListConstructor         (List * const list, size_t size);
int     ListDestructor          (List * list);
int     VerifyListDef           (const List * const list, const char *func_name);
int     PrintDLList             (const List * const list);
int     PrintListLikeArray      (const List * const list);
int     DomainExpansion         (List * list);
// Change elements
int     ListAddAfter            (List * const list, const list_element_t argument, const size_t index_in_array);
int     ListAddBefore           (List * const list, const list_element_t argument, const size_t index_in_array);
int     ListAddHead             (List * const list, const list_element_t argument);
int     ListAddTail             (List * const list, const list_element_t argument);
int     ListDel                 (List * const list, size_t del_index_in_list);
size_t  FindFreeCell            (const List * const list);
size_t  ListFinderByIndex       (const List * const list, size_t index);


// GraphVis
void PicToHTML(FILE *html_output, const char *picture_name);
void CloseHTML(FILE *html_output);
FILE *InitHTML(const char *file_name);
void CompPng(const char *name);

#endif