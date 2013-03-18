#ifndef  __CODE_TO_HTML_H
#define  __CODE_TO_HTML_H

#include "define.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

static int   linenum = 1;

static double times = 0.0; 

void  z_exit();

bool  exist(char * file_name);

char* get_span_label(KIND kind);

void  write_comment(char * comment, FILE * h_file);
void  write_number(char * number, FILE * h_file);
void  write_char(char chars, FILE * h_file);
void  write_string(char* string, FILE * h_file);
void  write_float(char * number, FILE * h_file);
void  write_processor(char * processor, FILE * h_file);
void  write_identifier(char * identifier, FILE * h_file);
void  write_reserved(char * reserved, FILE * h_file);
void  write_symbol(char  symbol, FILE * h_file);
void  writeline_num(int num, FILE * h_file);

void  check_alpha(char * line, int * i, FILE * h_file);
void  check_digit(char * line, int * i, FILE * h_file);
void  check_others(char * line, int * i, FILE * h_file, FILE * s_file);

void  writeline(char * line, FILE * h_file, FILE * s_file);

void  write_header(char * html_file);
void  write_code(char *source_file, char * html_file);
void  write_tailer(char * html_file);

void  print_trans_info(char * source_file, char * html_file);

void  code_to_html(char * source_file, char * html_file);

#endif
