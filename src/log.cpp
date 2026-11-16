#ifndef _LOG
#define _LOG

#include <stdio.h>
#include "term_colors.h"

void ClearTerm(void);

// WRITE LOG
//---------------------------------------------------------------------------------------------------------------------

#ifdef _DEBUG
    // const char *LOG_FILE_NAME = "LOG.log";
    // FILE *const log_file = fopen(LOG_FILE_NAME, "w");

    #define LOG(name, ...)  fprintf(log_file, name, ## __VA_ARGS__);
    #define LOG_FUNC_INFO   LOG("\n[INFO] [%s:%d] (%s) --> started...\n", file_name, line_num, __FUNCTION__)
    #define END_FUNC_LOG    LOG("[INFO] (%s) --> completed.\n\n", __FUNCTION__)
    #define CRUSH_FUNC_LOG  LOG("[WARN] (%s) --> CRUSHED!!!\n\n", __FUNCTION__)
#else
    #define LOG(name, ...)
    #define LOG_FUNC_INFO
    #define END_FUNC_LOG
    #define CRUSH_FUNC_LOG
#endif

// PRINTING
//---------------------------------------------------------------------------------------------------------------------

#ifdef _DEBUG
    #define PAUSE ClearTerm();
    #define PR(name, ...)                                                                               \
        printf(name, ## __VA_ARGS__)
    #define PR_FST                                                                                      \
        printf("----------------------------------------------------------------------------------\n"); \
        printf("- RUN %s:\n\n", __FUNCTION__)
    #define PR_FED                                                                                      \
        printf("\n- END %s;\n", __FUNCTION__); ClearTerm();                                             \
        printf("----------------------------------------------------------------------------------\n")
#else
    #define PAUSE
    #define PR(name, ...)
    #define PR_FST
    #define PR_FED
#endif

//---------------------------------------------------------------------------------------------------------------------

// clear stdin
void ClearTerm(void)
{
    int symbol = 0;
    while ((symbol != EOF) && (symbol != '\n'))
        {symbol = getchar();}
}

// HTML
//---------------------------------------------------------------------------------------------------------------------

#define HTML_HEADER(html_output, lvl, text, ...) fprintf(html_output, "<h%d> " text, lvl, ## __VA_ARGS__); \
                                                 fprintf(html_output, " <br></h%d>\n", lvl)

#define HTML_PR(html_output, text, ...)          fprintf(html_output, "<p> " text " <p>", ## __VA_ARGS__)

FILE *InitHTML(const char *file_name)
{
    assert(file_name);

    // open file
    FILE *html_output = fopen(file_name, "w");
    if (html_output == NULL)
    {
        perror("HTML file wasn't opened.");
        return NULL;
    }

    // time to mark created file
    time_t current_time = {};
    assert(time(&current_time));

    // file parameters
    fprintf(html_output, "<!DOCTYPE html>\n <html lang=\"ru\">\n <head>\n  \
                          <meta charset=\"UTF-8\">\n <title> %s (%s) </title>\n </head>\n <body>\n", file_name, ctime(&current_time));

    // first header with file name and time
    HTML_HEADER(html_output, 1, "%s (%s)\n", file_name, ctime(&current_time));

    return html_output;
}

void CloseHTML(FILE *html_output)
{
    assert(html_output);

    fprintf(html_output, "\n</body>\n</html>");
    fclose(html_output);
}

void PicToHTML(FILE *html_output, const char *picture_name)
{
    assert(html_output);
    assert(picture_name);

    if (html_output)
    {
        fprintf(html_output, "<img src=\"%s\" alt=\"%s\" width=\"900\">\n", picture_name, picture_name);
    }

}

//---------------------------------------------------------------------------------------------------------------------



#endif