#ifndef  __DEFINE_H
#define  __DEFINE_H

#include <stdio.h>

#define  COPYRIGHT  "<!--This file is created by code-to-html builder.-->"

#define  HTML_HEADER  "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n" \
                      "<html>\n<head>\n<title>\n" 
                      
#define  HTML_META      "\n</title>\n<meta name=\"generator\" content=\"code-to-html\" />\n"

/*
 * comment     :  style for comment.
 * number      :  style for number as int/long/short number.
 * char        :  style for character.
 * string      :  style for string.
 * float       :  style for float/double number.
 * processor   :  style for processors.
 * identifier  :  style for identifier.
 * reserved    :  style for reserved words.
 * symbol      :  style for symbols.
 * linenum     :  style for line numbers.
 */
#define HTML_STYLE  "<style type=\"text/css\">\n<!--" \
                    "body {color: #000000; background-color: #000000; " \
                    "border: 2px solid Gray; margin: 20px 100px 20px 100px;}\n" \
                    ".comment {color: #00FF00; }\n" \
                    ".number {color: #FF6600;}\n" \
                    ".char {color: #00FF00;}\n" \
                    ".string {color: #00FF00;}\n" \
                    ".processor {color: #FFFFFF;}\n" \
                    ".identifier {color: #FFFFFF;}\n" \
                    ".reserved {color: #00FF00;}\n" \
                    ".symbol {color: #FFFF00;}\n" \
                    ".linenum {color: #FF0000;}\n" \
                    ".other {color: #FFFFFF;}\n"\
                    "-->\n</style>\n</head>\n<body>\n<pre>\n<code>\n"

#define  HTML_TAILER "\n</code></pre>\n</body>\n</html>"

#define  LINE_LEN_MAX    1024

typedef enum KIND {COMMENT = 1, NUMBER, CHAR, STRING, PROCESSOR, IDENTIFIER, RESERVED, SYMBOL, LINENUM, OTHER}  KIND;

typedef  struct
{
   char * sign;
   KIND   kind;
} SIGNS;

static SIGNS  comments[] = 
{
  {.sign = "/*",  .kind = COMMENT },
  {.sign = "*/",  .kind = COMMENT },
  {.sign = "//",  .kind = COMMENT },
  {.sign = NULL,  .kind = 0 }
};

static SIGNS  processors[] = 
{
  {.sign = "#",  .kind = PROCESSOR },
  {.sign = NULL, .kind = 0 }
};

static SIGNS  reserveds[] = 
{
   {.sign = "auto",      .kind = RESERVED },
   {.sign = "break",     .kind = RESERVED },
   {.sign = "case",      .kind = RESERVED },
   {.sign = "char",      .kind = RESERVED },
   {.sign = "const",     .kind = RESERVED },
   {.sign = "continue",  .kind = RESERVED },
   {.sign = "default",   .kind = RESERVED },
   {.sign = "do",        .kind = RESERVED },
   {.sign = "double",    .kind = RESERVED },
   {.sign = "else",      .kind = RESERVED },
   {.sign = "enum",      .kind = RESERVED },
   {.sign = "extern",    .kind = RESERVED },
   {.sign = "float",     .kind = RESERVED },
   {.sign = "for",       .kind = RESERVED },
   {.sign = "goto",      .kind = RESERVED },
   {.sign = "if",        .kind = RESERVED },
   {.sign = "inline",    .kind = RESERVED },
   {.sign = "int",       .kind = RESERVED },
   {.sign = "long",      .kind = RESERVED },
   {.sign = "register",  .kind = RESERVED },
   {.sign = "restrict",  .kind = RESERVED },
   {.sign = "return",    .kind = RESERVED },
   {.sign = "short",     .kind = RESERVED },
   {.sign = "signed",    .kind = RESERVED },
   {.sign = "sizeof",    .kind = RESERVED },
   {.sign = "static",    .kind = RESERVED },
   {.sign = "struct",    .kind = RESERVED },
   {.sign = "switch",    .kind = RESERVED },
   {.sign = "typedef",   .kind = RESERVED },
   {.sign = "union",     .kind = RESERVED },
   {.sign = "unsigned",  .kind = RESERVED },
   {.sign = "void",      .kind = RESERVED },
   {.sign = "volatile",  .kind = RESERVED },
   {.sign = "while",     .kind = RESERVED },
   {.sign = NULL,        .kind = 0 }
};

static struct 
{
   char  sign;
   KIND  kind;
}   symbols[] = 
{
  {.sign = '+',  .kind = SYMBOL },
  {.sign = '-',  .kind = SYMBOL },
  {.sign = '*',  .kind = SYMBOL },
  {.sign = '/',  .kind = SYMBOL },
  {.sign = '%',  .kind = SYMBOL },
  {.sign = '.',  .kind = SYMBOL },
  {.sign = '{',  .kind = SYMBOL },
  {.sign = '}',  .kind = SYMBOL },
  {.sign = '[',  .kind = SYMBOL },
  {.sign = ']',  .kind = SYMBOL },
  {.sign = '(',  .kind = SYMBOL },
  {.sign = ')',  .kind = SYMBOL },
  {.sign = '>',  .kind = SYMBOL },
  {.sign = '<',  .kind = SYMBOL },
  {.sign = '=',  .kind = SYMBOL },
  {.sign = '!',  .kind = SYMBOL },
  {.sign = '&',  .kind = SYMBOL },
  {.sign = '|',  .kind = SYMBOL },
  {.sign = '^',  .kind = SYMBOL },
  {.sign = '~',  .kind = SYMBOL },
  {.sign = ',',  .kind = SYMBOL },
  {.sign = ';',  .kind = SYMBOL },
  {.sign = '?',  .kind = SYMBOL },
  {.sign = ':',  .kind = SYMBOL },
  {.sign = '\0', .kind = 0 }
};


typedef  struct
{
   KIND   kind;
   char*  span;
} styles;

static styles  spans[] = 
{ 
   {.kind = COMMENT,     .span = "<span class=\"comment\">"},
   {.kind = NUMBER,      .span = "<span class=\"number\">"},
   {.kind = CHAR,        .span = "<span class=\"char\">"},
   {.kind = STRING,      .span = "<span class=\"string\">"},
   {.kind = PROCESSOR,   .span = "<span class=\"processor\">"},
   {.kind = IDENTIFIER, .span = "<span class=\"identifier\">"},
   {.kind = RESERVED,    .span = "<span class=\"reserved\">"},
   {.kind = SYMBOL,      .span = "<span class=\"symbol\">"},
   {.kind = LINENUM,     .span = "<span class=\"linenum\">"},
   {.kind = OTHER,       .span = "<span class=\"other\">"},
   {.kind = 0,           .span = NULL}
};

#endif
