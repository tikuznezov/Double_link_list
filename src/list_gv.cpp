#ifndef _LIST_GV
#define _LIST_GV

#include "list.h"

// GraphViz
//-------------------------------------------------------------------------------------------

FILE *gv = NULL;

#define fp(string, ...)  fprintf(gv, string, ## __VA_ARGS__);

#define PrintDLListGV(list_p) PrintDLListGV_DEF(list_p, __LINE__)

void CreateDataLinks(const List * const list)
{
    size_t iter_count = 0;
    for (size_t list_index = list->head; list_index < list->size; list_index = list->data[list_index].next)
    {
        size_t next = list->data[list_index].next;
        size_t prev = list->data[list_index].prev;

        // correct link
        if ((list_index == list->data[next].prev) && (list_index != list->data[list_index].next))
        {
            fp("n%zu -> n%zu [constraint=false, dir=both];", list_index, next);
        }
        // link to next error
        if (list_index != list->data[next].prev)
        {
            fp("n%zu -> n%zu [constraint=false, color = red];\n", list_index, next);
        }
        // link to prev error
        if (list_index != list->data[prev].next)
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
}

void CreateFreeLinks(const List * const list)
{
    size_t iter_count = 0;
    if (list->free != ((size_t)-1))
    {
        for (size_t list_index = list->free; list_index < list->size; list_index = list->data[list_index].next)
        {
            size_t next = list->data[list_index].next;


            fp("n%zu -> n%zu [constraint=false, color = \"#3fc236\", style = bold];", list_index, next);
            fp("n%zu [fillcolor = gray]\n", list_index);
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
        fp("n%-5zu [label=\"END FREE\", fillcolor = \"#00a527\"];\n", (size_t)-1);
        // one line free and end of free
        fp("free:w -> n%zu:e [style=invis, weight=100];\n", (size_t)-1);

        fp("free:e -> n%zd:n [color = \"#00a527\", style = bold];\n", list->free);
    }
}

void CreateHeadTailLinks(const List * const list)
{
    fp("head [label = \"HEAD\", fillcolor = orange];\n");
    fp("tail [label = \"TAIL\", fillcolor = orange];\n");
    // one line head and tail
    fp("head -> tail [style=invis, weight=100, dir = both];\n");

    fp("head -> n%zd:n [color = orange];\n", list->head);
    // fp("rank = same; head; n%zd", list->head);
    fp("tail -> n%zd:n [color = orange];\n", list->tail);
    // fp("rank = same; tail; n%zd", list->tail);
}

void CreateBlocks(const List * const list)
{
    for (size_t i = 0; i < list->size; i++)
    {
        fp("n%-5zu [label=\"Array index %5zu.| Arg = " PR_LIST_EL " |{ Prev = %5zd | Next = %5zd}\"];\n", i, i, list->data[i].var, list->data[i].prev, list->data[i].next);
    }
    for (size_t i = 1; i < list->size; i++)
    {
        fp("n%zu -> n%zu [style=invis, weight=100];\n", i-1, i);
    }
}

int PrintDLListGV_DEF(const List * const list, const int name)
{
    assert(list);
    extern FILE *gv;
    gv = fopen("DL_list.gv", "w");

    // graph info
    fp("\n\ndigraph %d {\n", name);
    fp("rankdir=LR; splines=ortho; nodesep = 1; bgcolor=\"#FFFFFF\";");
    fp("node [shape = Mrecord, style = filled, fillcolor = \"#626ae0\", fontcolor = \"#ffffff\", fontname=\"Helvetica-Bold\"];");

    // create blocks, set to line
    CreateBlocks(list);

    // create data links
    CreateDataLinks(list);

    // create free links
    CreateFreeLinks(list);

    // create head and tail
    CreateHeadTailLinks(list);

    fp("}");

    return 0;
}

const int SYS_COMMAND_LENGTH = 100;
FILE *list_html_output = NULL;

void CompPng(const char *name)
{
    static size_t comp_pic_number = 1;
    if (gv)
    {
        fclose(gv);
        gv = NULL;
        char sys_com[SYS_COMMAND_LENGTH];
        snprintf(sys_com, SYS_COMMAND_LENGTH, "dot -Tsvg DL_list.gv -o pictures/%s_%zu.svg", name, comp_pic_number);
        system(sys_com);
        snprintf(sys_com, SYS_COMMAND_LENGTH, "pictures/%s_%zu.svg", name, comp_pic_number);
        comp_pic_number++;
        if (list_html_output != NULL)
        {
            // #define HTML_HEADER(html_output, lvl, text, ...) fprintf(html_output, "<h%d> " text "</h%d>", lvl, ## __VA_ARGS__, lvl);
            HTML_HEADER(list_html_output, 6, "%s", sys_com);
            PicToHTML(list_html_output, sys_com);
            // PR(PRED "Writing <%s> to HTML...\n" DEF_COL, sys_com);
        }
    }
}


#endif