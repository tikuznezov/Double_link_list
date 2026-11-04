#ifndef TERM_COLORS_H
#define TERM_COLORS_H

/* Reset all attributes (default color and style) */
#define DEF_COL     "\033[0m"

/* ---------- Regular foreground colors ---------- */
#define PBLACK      "\033[0;30m"  // black text
#define PRED        "\033[0;31m"  // red text
#define PGREEN      "\033[0;32m"  // green text
#define PYELLOW     "\033[0;33m"  // yellow text
#define PBLUE       "\033[0;34m"  // blue text
#define PMAGENTA    "\033[0;35m"  // magenta text
#define PCYAN       "\033[0;36m"  // cyan text
#define PWHITE      "\033[0;37m"  // white text

/* ---------- Bold foreground colors ---------- */
#define PBBLACK     "\033[1;30m"  // bold black text
#define PBRED       "\033[1;31m"  // bold red text
#define PBGREEN     "\033[1;32m"  // bold green text
#define PBYELLOW    "\033[1;33m"  // bold yellow text
#define PBBLUE      "\033[1;34m"  // bold blue text
#define PBMAGENTA   "\033[1;35m"  // bold magenta text
#define PBCYAN      "\033[1;36m"  // bold cyan text
#define PBWHITE     "\033[1;37m"  // bold white text

/* ---------- Bright (high intensity) foreground colors ---------- */
#define PHBLACK     "\033[0;90m"  // bright black (gray) text
#define PHRED       "\033[0;91m"  // bright red text
#define PHGREEN     "\033[0;92m"  // bright green text
#define PHYELLOW    "\033[0;93m"  // bright yellow text
#define PHBLUE      "\033[0;94m"  // bright blue text
#define PHMAGENTA   "\033[0;95m"  // bright magenta text
#define PHCYAN      "\033[0;96m"  // bright cyan text
#define PHWHITE     "\033[0;97m"  // bright white text

/* ---------- Bold bright foreground colors ---------- */
#define PBHBLACK    "\033[1;90m"  // bold bright black (gray) text
#define PBHRED      "\033[1;91m"  // bold bright red text
#define PBHGREEN    "\033[1;92m"  // bold bright green text
#define PBHYELLOW   "\033[1;93m"  // bold bright yellow text
#define PBHBLUE     "\033[1;94m"  // bold bright blue text
#define PBHMAGENTA  "\033[1;95m"  // bold bright magenta text
#define PBHCYAN     "\033[1;96m"  // bold bright cyan text
#define PBHWHITE    "\033[1;97m"  // bold bright white text

/* ---------- Underlined foreground colors ---------- */
#define PUBLACK     "\033[4;30m"  // underlined black text
#define PURED       "\033[4;31m"  // underlined red text
#define PUGREEN     "\033[4;32m"  // underlined green text
#define PUYELLOW    "\033[4;33m"  // underlined yellow text
#define PUBLUE      "\033[4;34m"  // underlined blue text
#define PUMAGENTA   "\033[4;35m"  // underlined magenta text
#define PUCYAN      "\033[4;36m"  // underlined cyan text
#define PUWHITE     "\033[4;37m"  // underlined white text

/* ---------- Background colors ---------- */
#define BBLACK      "\033[40m"    // black background
#define BRED        "\033[41m"    // red background
#define BGREEN      "\033[42m"    // green background
#define BYELLOW     "\033[43m"    // yellow background
#define BBLUE       "\033[44m"    // blue background
#define BMAGENTA    "\033[45m"    // magenta background
#define BCYAN       "\033[46m"    // cyan background
#define BWHITE      "\033[47m"    // white background

/* ---------- Bright (high intensity) background colors ---------- */
#define BHBLACK     "\033[100m"   // bright black (gray) background
#define BHRED       "\033[101m"   // bright red background
#define BHGREEN     "\033[102m"   // bright green background
#define BHYELLOW    "\033[103m"   // bright yellow background
#define BHBLUE      "\033[104m"   // bright blue background
#define BHMAGENTA   "\033[105m"   // bright magenta background
#define BHCYAN      "\033[106m"   // bright cyan background
#define BHWHITE     "\033[107m"   // bright white background

/* ---------- Text styles ---------- */
#define PBOLD       "\033[1m"     // bold text
#define PDIM        "\033[2m"     // dim (faint) text
#define PITALIC     "\033[3m"     // italic text (terminal-dependent)
#define PUNDERLINE  "\033[4m"     // underlined text
#define PBLINK      "\033[5m"     // blinking text (terminal-dependent)
#define PREVERSE    "\033[7m"     // reversed foreground/background
#define PHIDDEN     "\033[8m"     // hidden text
#define PSTRIKE     "\033[9m"     // strikethrough text (terminal-dependent)

/* ---------- 256-color mode helpers ---------- */
#define PCOLOR256(n) "\033[38;5;" #n "m"  // text color from 256-color palette (n = 0..255)
#define BCOLOR256(n) "\033[48;5;" #n "m"  // background color from 256-color palette (n = 0..255)

/* ---------- 24-bit true color helpers ---------- */
#define PRGB(r, g, b) "\033[38;2;" #r ";" #g ";" #b "m"  // text true color (r, g, b = 0..255)
#define BRGB(r, g, b) "\033[48;2;" #r ";" #g ";" #b "m"  // background true color (r, g, b = 0..255)

/* ---------- Combined: regular text on regular background (e.g. BLACK_ON_WHITE) ---------- */
#define BLACK_ON_RED                     "\033[30;41m"  // black text on red background
#define BLACK_ON_GREEN                   "\033[30;42m"  // black text on green background
#define BLACK_ON_YELLOW                  "\033[30;43m"  // black text on yellow background
#define BLACK_ON_BLUE                    "\033[30;44m"  // black text on blue background
#define BLACK_ON_MAGENTA                 "\033[30;45m"  // black text on magenta background
#define BLACK_ON_CYAN                    "\033[30;46m"  // black text on cyan background
#define BLACK_ON_WHITE                   "\033[30;47m"  // black text on white background
#define RED_ON_BLACK                     "\033[31;40m"  // red text on black background
#define RED_ON_GREEN                     "\033[31;42m"  // red text on green background
#define RED_ON_YELLOW                    "\033[31;43m"  // red text on yellow background
#define RED_ON_BLUE                      "\033[31;44m"  // red text on blue background
#define RED_ON_MAGENTA                   "\033[31;45m"  // red text on magenta background
#define RED_ON_CYAN                      "\033[31;46m"  // red text on cyan background
#define RED_ON_WHITE                     "\033[31;47m"  // red text on white background
#define GREEN_ON_BLACK                   "\033[32;40m"  // green text on black background
#define GREEN_ON_RED                     "\033[32;41m"  // green text on red background
#define GREEN_ON_YELLOW                  "\033[32;43m"  // green text on yellow background
#define GREEN_ON_BLUE                    "\033[32;44m"  // green text on blue background
#define GREEN_ON_MAGENTA                 "\033[32;45m"  // green text on magenta background
#define GREEN_ON_CYAN                    "\033[32;46m"  // green text on cyan background
#define GREEN_ON_WHITE                   "\033[32;47m"  // green text on white background
#define YELLOW_ON_BLACK                  "\033[33;40m"  // yellow text on black background
#define YELLOW_ON_RED                    "\033[33;41m"  // yellow text on red background
#define YELLOW_ON_GREEN                  "\033[33;42m"  // yellow text on green background
#define YELLOW_ON_BLUE                   "\033[33;44m"  // yellow text on blue background
#define YELLOW_ON_MAGENTA                "\033[33;45m"  // yellow text on magenta background
#define YELLOW_ON_CYAN                   "\033[33;46m"  // yellow text on cyan background
#define YELLOW_ON_WHITE                  "\033[33;47m"  // yellow text on white background
#define BLUE_ON_BLACK                    "\033[34;40m"  // blue text on black background
#define BLUE_ON_RED                      "\033[34;41m"  // blue text on red background
#define BLUE_ON_GREEN                    "\033[34;42m"  // blue text on green background
#define BLUE_ON_YELLOW                   "\033[34;43m"  // blue text on yellow background
#define BLUE_ON_MAGENTA                  "\033[34;45m"  // blue text on magenta background
#define BLUE_ON_CYAN                     "\033[34;46m"  // blue text on cyan background
#define BLUE_ON_WHITE                    "\033[34;47m"  // blue text on white background
#define MAGENTA_ON_BLACK                 "\033[35;40m"  // magenta text on black background
#define MAGENTA_ON_RED                   "\033[35;41m"  // magenta text on red background
#define MAGENTA_ON_GREEN                 "\033[35;42m"  // magenta text on green background
#define MAGENTA_ON_YELLOW                "\033[35;43m"  // magenta text on yellow background
#define MAGENTA_ON_BLUE                  "\033[35;44m"  // magenta text on blue background
#define MAGENTA_ON_CYAN                  "\033[35;46m"  // magenta text on cyan background
#define MAGENTA_ON_WHITE                 "\033[35;47m"  // magenta text on white background
#define CYAN_ON_BLACK                    "\033[36;40m"  // cyan text on black background
#define CYAN_ON_RED                      "\033[36;41m"  // cyan text on red background
#define CYAN_ON_GREEN                    "\033[36;42m"  // cyan text on green background
#define CYAN_ON_YELLOW                   "\033[36;43m"  // cyan text on yellow background
#define CYAN_ON_BLUE                     "\033[36;44m"  // cyan text on blue background
#define CYAN_ON_MAGENTA                  "\033[36;45m"  // cyan text on magenta background
#define CYAN_ON_WHITE                    "\033[36;47m"  // cyan text on white background
#define WHITE_ON_BLACK                   "\033[37;40m"  // white text on black background
#define WHITE_ON_RED                     "\033[37;41m"  // white text on red background
#define WHITE_ON_GREEN                   "\033[37;42m"  // white text on green background
#define WHITE_ON_YELLOW                  "\033[37;43m"  // white text on yellow background
#define WHITE_ON_BLUE                    "\033[37;44m"  // white text on blue background
#define WHITE_ON_MAGENTA                 "\033[37;45m"  // white text on magenta background
#define WHITE_ON_CYAN                    "\033[37;46m"  // white text on cyan background

/* ---------- Combined: bright text on regular background (e.g. BRIGHT_RED_ON_BLACK) ---------- */
#define BRIGHT_BLACK_ON_BLACK            "\033[90;40m"  // bright black text on black background
#define BRIGHT_BLACK_ON_RED              "\033[90;41m"  // bright black text on red background
#define BRIGHT_BLACK_ON_GREEN            "\033[90;42m"  // bright black text on green background
#define BRIGHT_BLACK_ON_YELLOW           "\033[90;43m"  // bright black text on yellow background
#define BRIGHT_BLACK_ON_BLUE             "\033[90;44m"  // bright black text on blue background
#define BRIGHT_BLACK_ON_MAGENTA          "\033[90;45m"  // bright black text on magenta background
#define BRIGHT_BLACK_ON_CYAN             "\033[90;46m"  // bright black text on cyan background
#define BRIGHT_BLACK_ON_WHITE            "\033[90;47m"  // bright black text on white background
#define BRIGHT_RED_ON_BLACK              "\033[91;40m"  // bright red text on black background
#define BRIGHT_RED_ON_RED                "\033[91;41m"  // bright red text on red background
#define BRIGHT_RED_ON_GREEN              "\033[91;42m"  // bright red text on green background
#define BRIGHT_RED_ON_YELLOW             "\033[91;43m"  // bright red text on yellow background
#define BRIGHT_RED_ON_BLUE               "\033[91;44m"  // bright red text on blue background
#define BRIGHT_RED_ON_MAGENTA            "\033[91;45m"  // bright red text on magenta background
#define BRIGHT_RED_ON_CYAN               "\033[91;46m"  // bright red text on cyan background
#define BRIGHT_RED_ON_WHITE              "\033[91;47m"  // bright red text on white background
#define BRIGHT_GREEN_ON_BLACK            "\033[92;40m"  // bright green text on black background
#define BRIGHT_GREEN_ON_RED              "\033[92;41m"  // bright green text on red background
#define BRIGHT_GREEN_ON_GREEN            "\033[92;42m"  // bright green text on green background
#define BRIGHT_GREEN_ON_YELLOW           "\033[92;43m"  // bright green text on yellow background
#define BRIGHT_GREEN_ON_BLUE             "\033[92;44m"  // bright green text on blue background
#define BRIGHT_GREEN_ON_MAGENTA          "\033[92;45m"  // bright green text on magenta background
#define BRIGHT_GREEN_ON_CYAN             "\033[92;46m"  // bright green text on cyan background
#define BRIGHT_GREEN_ON_WHITE            "\033[92;47m"  // bright green text on white background
#define BRIGHT_YELLOW_ON_BLACK           "\033[93;40m"  // bright yellow text on black background
#define BRIGHT_YELLOW_ON_RED             "\033[93;41m"  // bright yellow text on red background
#define BRIGHT_YELLOW_ON_GREEN           "\033[93;42m"  // bright yellow text on green background
#define BRIGHT_YELLOW_ON_YELLOW          "\033[93;43m"  // bright yellow text on yellow background
#define BRIGHT_YELLOW_ON_BLUE            "\033[93;44m"  // bright yellow text on blue background
#define BRIGHT_YELLOW_ON_MAGENTA         "\033[93;45m"  // bright yellow text on magenta background
#define BRIGHT_YELLOW_ON_CYAN            "\033[93;46m"  // bright yellow text on cyan background
#define BRIGHT_YELLOW_ON_WHITE           "\033[93;47m"  // bright yellow text on white background
#define BRIGHT_BLUE_ON_BLACK             "\033[94;40m"  // bright blue text on black background
#define BRIGHT_BLUE_ON_RED               "\033[94;41m"  // bright blue text on red background
#define BRIGHT_BLUE_ON_GREEN             "\033[94;42m"  // bright blue text on green background
#define BRIGHT_BLUE_ON_YELLOW            "\033[94;43m"  // bright blue text on yellow background
#define BRIGHT_BLUE_ON_BLUE              "\033[94;44m"  // bright blue text on blue background
#define BRIGHT_BLUE_ON_MAGENTA           "\033[94;45m"  // bright blue text on magenta background
#define BRIGHT_BLUE_ON_CYAN              "\033[94;46m"  // bright blue text on cyan background
#define BRIGHT_BLUE_ON_WHITE             "\033[94;47m"  // bright blue text on white background
#define BRIGHT_MAGENTA_ON_BLACK          "\033[95;40m"  // bright magenta text on black background
#define BRIGHT_MAGENTA_ON_RED            "\033[95;41m"  // bright magenta text on red background
#define BRIGHT_MAGENTA_ON_GREEN          "\033[95;42m"  // bright magenta text on green background
#define BRIGHT_MAGENTA_ON_YELLOW         "\033[95;43m"  // bright magenta text on yellow background
#define BRIGHT_MAGENTA_ON_BLUE           "\033[95;44m"  // bright magenta text on blue background
#define BRIGHT_MAGENTA_ON_MAGENTA        "\033[95;45m"  // bright magenta text on magenta background
#define BRIGHT_MAGENTA_ON_CYAN           "\033[95;46m"  // bright magenta text on cyan background
#define BRIGHT_MAGENTA_ON_WHITE          "\033[95;47m"  // bright magenta text on white background
#define BRIGHT_CYAN_ON_BLACK             "\033[96;40m"  // bright cyan text on black background
#define BRIGHT_CYAN_ON_RED               "\033[96;41m"  // bright cyan text on red background
#define BRIGHT_CYAN_ON_GREEN             "\033[96;42m"  // bright cyan text on green background
#define BRIGHT_CYAN_ON_YELLOW            "\033[96;43m"  // bright cyan text on yellow background
#define BRIGHT_CYAN_ON_BLUE              "\033[96;44m"  // bright cyan text on blue background
#define BRIGHT_CYAN_ON_MAGENTA           "\033[96;45m"  // bright cyan text on magenta background
#define BRIGHT_CYAN_ON_CYAN              "\033[96;46m"  // bright cyan text on cyan background
#define BRIGHT_CYAN_ON_WHITE             "\033[96;47m"  // bright cyan text on white background
#define BRIGHT_WHITE_ON_BLACK            "\033[97;40m"  // bright white text on black background
#define BRIGHT_WHITE_ON_RED              "\033[97;41m"  // bright white text on red background
#define BRIGHT_WHITE_ON_GREEN            "\033[97;42m"  // bright white text on green background
#define BRIGHT_WHITE_ON_YELLOW           "\033[97;43m"  // bright white text on yellow background
#define BRIGHT_WHITE_ON_BLUE             "\033[97;44m"  // bright white text on blue background
#define BRIGHT_WHITE_ON_MAGENTA          "\033[97;45m"  // bright white text on magenta background
#define BRIGHT_WHITE_ON_CYAN             "\033[97;46m"  // bright white text on cyan background
#define BRIGHT_WHITE_ON_WHITE            "\033[97;47m"  // bright white text on white background

/* ---------- Combined: regular text on bright background (e.g. BLACK_ON_BRIGHT_WHITE) ---------- */
#define BLACK_ON_BRIGHT_BLACK            "\033[30;100m"  // black text on bright black background
#define BLACK_ON_BRIGHT_RED              "\033[30;101m"  // black text on bright red background
#define BLACK_ON_BRIGHT_GREEN            "\033[30;102m"  // black text on bright green background
#define BLACK_ON_BRIGHT_YELLOW           "\033[30;103m"  // black text on bright yellow background
#define BLACK_ON_BRIGHT_BLUE             "\033[30;104m"  // black text on bright blue background
#define BLACK_ON_BRIGHT_MAGENTA          "\033[30;105m"  // black text on bright magenta background
#define BLACK_ON_BRIGHT_CYAN             "\033[30;106m"  // black text on bright cyan background
#define BLACK_ON_BRIGHT_WHITE            "\033[30;107m"  // black text on bright white background
#define RED_ON_BRIGHT_BLACK              "\033[31;100m"  // red text on bright black background
#define RED_ON_BRIGHT_RED                "\033[31;101m"  // red text on bright red background
#define RED_ON_BRIGHT_GREEN              "\033[31;102m"  // red text on bright green background
#define RED_ON_BRIGHT_YELLOW             "\033[31;103m"  // red text on bright yellow background
#define RED_ON_BRIGHT_BLUE               "\033[31;104m"  // red text on bright blue background
#define RED_ON_BRIGHT_MAGENTA            "\033[31;105m"  // red text on bright magenta background
#define RED_ON_BRIGHT_CYAN               "\033[31;106m"  // red text on bright cyan background
#define RED_ON_BRIGHT_WHITE              "\033[31;107m"  // red text on bright white background
#define GREEN_ON_BRIGHT_BLACK            "\033[32;100m"  // green text on bright black background
#define GREEN_ON_BRIGHT_RED              "\033[32;101m"  // green text on bright red background
#define GREEN_ON_BRIGHT_GREEN            "\033[32;102m"  // green text on bright green background
#define GREEN_ON_BRIGHT_YELLOW           "\033[32;103m"  // green text on bright yellow background
#define GREEN_ON_BRIGHT_BLUE             "\033[32;104m"  // green text on bright blue background
#define GREEN_ON_BRIGHT_MAGENTA          "\033[32;105m"  // green text on bright magenta background
#define GREEN_ON_BRIGHT_CYAN             "\033[32;106m"  // green text on bright cyan background
#define GREEN_ON_BRIGHT_WHITE            "\033[32;107m"  // green text on bright white background
#define YELLOW_ON_BRIGHT_BLACK           "\033[33;100m"  // yellow text on bright black background
#define YELLOW_ON_BRIGHT_RED             "\033[33;101m"  // yellow text on bright red background
#define YELLOW_ON_BRIGHT_GREEN           "\033[33;102m"  // yellow text on bright green background
#define YELLOW_ON_BRIGHT_YELLOW          "\033[33;103m"  // yellow text on bright yellow background
#define YELLOW_ON_BRIGHT_BLUE            "\033[33;104m"  // yellow text on bright blue background
#define YELLOW_ON_BRIGHT_MAGENTA         "\033[33;105m"  // yellow text on bright magenta background
#define YELLOW_ON_BRIGHT_CYAN            "\033[33;106m"  // yellow text on bright cyan background
#define YELLOW_ON_BRIGHT_WHITE           "\033[33;107m"  // yellow text on bright white background
#define BLUE_ON_BRIGHT_BLACK             "\033[34;100m"  // blue text on bright black background
#define BLUE_ON_BRIGHT_RED               "\033[34;101m"  // blue text on bright red background
#define BLUE_ON_BRIGHT_GREEN             "\033[34;102m"  // blue text on bright green background
#define BLUE_ON_BRIGHT_YELLOW            "\033[34;103m"  // blue text on bright yellow background
#define BLUE_ON_BRIGHT_BLUE              "\033[34;104m"  // blue text on bright blue background
#define BLUE_ON_BRIGHT_MAGENTA           "\033[34;105m"  // blue text on bright magenta background
#define BLUE_ON_BRIGHT_CYAN              "\033[34;106m"  // blue text on bright cyan background
#define BLUE_ON_BRIGHT_WHITE             "\033[34;107m"  // blue text on bright white background
#define MAGENTA_ON_BRIGHT_BLACK          "\033[35;100m"  // magenta text on bright black background
#define MAGENTA_ON_BRIGHT_RED            "\033[35;101m"  // magenta text on bright red background
#define MAGENTA_ON_BRIGHT_GREEN          "\033[35;102m"  // magenta text on bright green background
#define MAGENTA_ON_BRIGHT_YELLOW         "\033[35;103m"  // magenta text on bright yellow background
#define MAGENTA_ON_BRIGHT_BLUE           "\033[35;104m"  // magenta text on bright blue background
#define MAGENTA_ON_BRIGHT_MAGENTA        "\033[35;105m"  // magenta text on bright magenta background
#define MAGENTA_ON_BRIGHT_CYAN           "\033[35;106m"  // magenta text on bright cyan background
#define MAGENTA_ON_BRIGHT_WHITE          "\033[35;107m"  // magenta text on bright white background
#define CYAN_ON_BRIGHT_BLACK             "\033[36;100m"  // cyan text on bright black background
#define CYAN_ON_BRIGHT_RED               "\033[36;101m"  // cyan text on bright red background
#define CYAN_ON_BRIGHT_GREEN             "\033[36;102m"  // cyan text on bright green background
#define CYAN_ON_BRIGHT_YELLOW            "\033[36;103m"  // cyan text on bright yellow background
#define CYAN_ON_BRIGHT_BLUE              "\033[36;104m"  // cyan text on bright blue background
#define CYAN_ON_BRIGHT_MAGENTA           "\033[36;105m"  // cyan text on bright magenta background
#define CYAN_ON_BRIGHT_CYAN              "\033[36;106m"  // cyan text on bright cyan background
#define CYAN_ON_BRIGHT_WHITE             "\033[36;107m"  // cyan text on bright white background
#define WHITE_ON_BRIGHT_BLACK            "\033[37;100m"  // white text on bright black background
#define WHITE_ON_BRIGHT_RED              "\033[37;101m"  // white text on bright red background
#define WHITE_ON_BRIGHT_GREEN            "\033[37;102m"  // white text on bright green background
#define WHITE_ON_BRIGHT_YELLOW           "\033[37;103m"  // white text on bright yellow background
#define WHITE_ON_BRIGHT_BLUE             "\033[37;104m"  // white text on bright blue background
#define WHITE_ON_BRIGHT_MAGENTA          "\033[37;105m"  // white text on bright magenta background
#define WHITE_ON_BRIGHT_CYAN             "\033[37;106m"  // white text on bright cyan background
#define WHITE_ON_BRIGHT_WHITE            "\033[37;107m"  // white text on bright white background

/* ---------- Combined: bright text on bright background (e.g. BRIGHT_BLACK_ON_BRIGHT_WHITE) ---------- */
#define BRIGHT_BLACK_ON_BRIGHT_RED       "\033[90;101m"  // bright black text on bright red background
#define BRIGHT_BLACK_ON_BRIGHT_GREEN     "\033[90;102m"  // bright black text on bright green background
#define BRIGHT_BLACK_ON_BRIGHT_YELLOW    "\033[90;103m"  // bright black text on bright yellow background
#define BRIGHT_BLACK_ON_BRIGHT_BLUE      "\033[90;104m"  // bright black text on bright blue background
#define BRIGHT_BLACK_ON_BRIGHT_MAGENTA   "\033[90;105m"  // bright black text on bright magenta background
#define BRIGHT_BLACK_ON_BRIGHT_CYAN      "\033[90;106m"  // bright black text on bright cyan background
#define BRIGHT_BLACK_ON_BRIGHT_WHITE     "\033[90;107m"  // bright black text on bright white background
#define BRIGHT_RED_ON_BRIGHT_BLACK       "\033[91;100m"  // bright red text on bright black background
#define BRIGHT_RED_ON_BRIGHT_GREEN       "\033[91;102m"  // bright red text on bright green background
#define BRIGHT_RED_ON_BRIGHT_YELLOW      "\033[91;103m"  // bright red text on bright yellow background
#define BRIGHT_RED_ON_BRIGHT_BLUE        "\033[91;104m"  // bright red text on bright blue background
#define BRIGHT_RED_ON_BRIGHT_MAGENTA     "\033[91;105m"  // bright red text on bright magenta background
#define BRIGHT_RED_ON_BRIGHT_CYAN        "\033[91;106m"  // bright red text on bright cyan background
#define BRIGHT_RED_ON_BRIGHT_WHITE       "\033[91;107m"  // bright red text on bright white background
#define BRIGHT_GREEN_ON_BRIGHT_BLACK     "\033[92;100m"  // bright green text on bright black background
#define BRIGHT_GREEN_ON_BRIGHT_RED       "\033[92;101m"  // bright green text on bright red background
#define BRIGHT_GREEN_ON_BRIGHT_YELLOW    "\033[92;103m"  // bright green text on bright yellow background
#define BRIGHT_GREEN_ON_BRIGHT_BLUE      "\033[92;104m"  // bright green text on bright blue background
#define BRIGHT_GREEN_ON_BRIGHT_MAGENTA   "\033[92;105m"  // bright green text on bright magenta background
#define BRIGHT_GREEN_ON_BRIGHT_CYAN      "\033[92;106m"  // bright green text on bright cyan background
#define BRIGHT_GREEN_ON_BRIGHT_WHITE     "\033[92;107m"  // bright green text on bright white background
#define BRIGHT_YELLOW_ON_BRIGHT_BLACK    "\033[93;100m"  // bright yellow text on bright black background
#define BRIGHT_YELLOW_ON_BRIGHT_RED      "\033[93;101m"  // bright yellow text on bright red background
#define BRIGHT_YELLOW_ON_BRIGHT_GREEN    "\033[93;102m"  // bright yellow text on bright green background
#define BRIGHT_YELLOW_ON_BRIGHT_BLUE     "\033[93;104m"  // bright yellow text on bright blue background
#define BRIGHT_YELLOW_ON_BRIGHT_MAGENTA  "\033[93;105m"  // bright yellow text on bright magenta background
#define BRIGHT_YELLOW_ON_BRIGHT_CYAN     "\033[93;106m"  // bright yellow text on bright cyan background
#define BRIGHT_YELLOW_ON_BRIGHT_WHITE    "\033[93;107m"  // bright yellow text on bright white background
#define BRIGHT_BLUE_ON_BRIGHT_BLACK      "\033[94;100m"  // bright blue text on bright black background
#define BRIGHT_BLUE_ON_BRIGHT_RED        "\033[94;101m"  // bright blue text on bright red background
#define BRIGHT_BLUE_ON_BRIGHT_GREEN      "\033[94;102m"  // bright blue text on bright green background
#define BRIGHT_BLUE_ON_BRIGHT_YELLOW     "\033[94;103m"  // bright blue text on bright yellow background
#define BRIGHT_BLUE_ON_BRIGHT_MAGENTA    "\033[94;105m"  // bright blue text on bright magenta background
#define BRIGHT_BLUE_ON_BRIGHT_CYAN       "\033[94;106m"  // bright blue text on bright cyan background
#define BRIGHT_BLUE_ON_BRIGHT_WHITE      "\033[94;107m"  // bright blue text on bright white background
#define BRIGHT_MAGENTA_ON_BRIGHT_BLACK   "\033[95;100m"  // bright magenta text on bright black background
#define BRIGHT_MAGENTA_ON_BRIGHT_RED     "\033[95;101m"  // bright magenta text on bright red background
#define BRIGHT_MAGENTA_ON_BRIGHT_GREEN   "\033[95;102m"  // bright magenta text on bright green background
#define BRIGHT_MAGENTA_ON_BRIGHT_YELLOW  "\033[95;103m"  // bright magenta text on bright yellow background
#define BRIGHT_MAGENTA_ON_BRIGHT_BLUE    "\033[95;104m"  // bright magenta text on bright blue background
#define BRIGHT_MAGENTA_ON_BRIGHT_CYAN    "\033[95;106m"  // bright magenta text on bright cyan background
#define BRIGHT_MAGENTA_ON_BRIGHT_WHITE   "\033[95;107m"  // bright magenta text on bright white background
#define BRIGHT_CYAN_ON_BRIGHT_BLACK      "\033[96;100m"  // bright cyan text on bright black background
#define BRIGHT_CYAN_ON_BRIGHT_RED        "\033[96;101m"  // bright cyan text on bright red background
#define BRIGHT_CYAN_ON_BRIGHT_GREEN      "\033[96;102m"  // bright cyan text on bright green background
#define BRIGHT_CYAN_ON_BRIGHT_YELLOW     "\033[96;103m"  // bright cyan text on bright yellow background
#define BRIGHT_CYAN_ON_BRIGHT_BLUE       "\033[96;104m"  // bright cyan text on bright blue background
#define BRIGHT_CYAN_ON_BRIGHT_MAGENTA    "\033[96;105m"  // bright cyan text on bright magenta background
#define BRIGHT_CYAN_ON_BRIGHT_WHITE      "\033[96;107m"  // bright cyan text on bright white background
#define BRIGHT_WHITE_ON_BRIGHT_BLACK     "\033[97;100m"  // bright white text on bright black background
#define BRIGHT_WHITE_ON_BRIGHT_RED       "\033[97;101m"  // bright white text on bright red background
#define BRIGHT_WHITE_ON_BRIGHT_GREEN     "\033[97;102m"  // bright white text on bright green background
#define BRIGHT_WHITE_ON_BRIGHT_YELLOW    "\033[97;103m"  // bright white text on bright yellow background
#define BRIGHT_WHITE_ON_BRIGHT_BLUE      "\033[97;104m"  // bright white text on bright blue background
#define BRIGHT_WHITE_ON_BRIGHT_MAGENTA   "\033[97;105m"  // bright white text on bright magenta background
#define BRIGHT_WHITE_ON_BRIGHT_CYAN      "\033[97;106m"  // bright white text on bright cyan background

#endif /* TERM_COLORS_H */