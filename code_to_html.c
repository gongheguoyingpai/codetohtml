#include "code_to_html.h"

void z_exit()
{ 
   system("pause");
   exit(1);
}

bool  exist(char *file_name)
{
    FILE*  file = NULL;
    file = fopen(file_name, "r");
    
    if (file == NULL)
    {
        return false;
    }
    else
    {
        fclose(file);
        return true;
    }
}

char * get_span_label(KIND kind)
{
     int  i = 0;
     
     while ((spans[i]).span != NULL)
     {
        if ((spans[i]).kind == kind)
        {
           return (spans[i]).span;
        }
        ++i;
     }
     
     return NULL;
}

void  write_comment(char * comment, FILE * h_file)
{
    char * span_label = get_span_label(COMMENT);
    
    if(span_label != NULL)
    {
        fprintf(h_file, "%s %s </span>", span_label, comment);
    }
    else
    {
        fputs("", h_file);
    }
}

void  write_number(char * number, FILE * h_file)
{
    char * span_label = get_span_label(NUMBER);
    
    if(NULL != span_label)
    {
        fprintf(h_file, "%s%s</span>", span_label, number);
    }
    else
    {
        fputs("", h_file);
    }
}

void  write_char(char chars, FILE * h_file)
{
    char * span_label = get_span_label(CHAR);
    
    if (span_label != NULL)
    {
        fprintf(h_file, "%s%c%c%c</span>", span_label, '\'', chars, '\'');
    }
    else
    {
        fputs("", h_file);
    }
}

void  write_string(char* string, FILE * h_file)
{
    char * span_label = get_span_label(STRING);
    
    if (span_label != NULL)
    {
       fprintf(h_file, "%s%s</span>", span_label, string);
    }
    else
    {
        fputs("", h_file);
    }
}

void  write_processor(char * processor, FILE * h_file)
{
    char * span_label = get_span_label(PROCESSOR);
    
    if (span_label != NULL)
    {
        fprintf(h_file, "%s", span_label);
        int  i = 0;
        while('\0' != processor[i])
        {
            if('<' != processor[i] && '>' != processor[i])
            {
                fprintf(h_file, "%c", processor[i]);
            }
            else
            {
                if('<' == processor[i])
                {
                  fprintf(h_file, "%s", "&lt");
                } 
                else
                {
                  fprintf(h_file, "%s", "&gt");
                }
            }
            ++i;
        }
    }
    else
    {
        fputs("", h_file);
    }
} 

void  write_identifier(char * identifier, FILE * h_file)
{
    char * span_label = get_span_label(IDENTIFIER);
    
    if(NULL != span_label)
    {
       fprintf(h_file, "%s%s</span>", span_label, identifier);
    }
    else
    {
       fputs("", h_file);
    }
}

void  write_reserved(char * reserved, FILE * h_file)
{
    char * span_label = get_span_label(RESERVED);
    
    if(NULL != span_label)
    {
       fprintf(h_file, "%s%s</span>", span_label, reserved);
    }
    else
    {
        fputs("", h_file);
    }
}

void  write_symbol(char symbol, FILE * h_file)
{
     char * span_label = get_span_label(SYMBOL);
     
     if(span_label != NULL)
     {
        fprintf(h_file, "%s%c</span>", span_label, symbol);
     }
     else
     {
         fputs("", h_file);
     }
}

void  writeline_num(int number, FILE * h_file)
{
     char  * span_label = get_span_label(LINENUM);
     
     if (span_label != NULL)
     {
         fputs(span_label, h_file);
         fprintf(h_file, "%6d</span>  ", number);
     }
     else
     {
         fputs("", h_file);
     }
         
} 

void  check_alpha(char * line, int * i, FILE * h_file)
{
    char  temp[LINE_LEN_MAX] = "";
    int   j = 0;
    
    while (isdigit(line[*i]) || isalpha(line[*i]) || line[*i] == '_')
    {
        temp[j] = line[*i];
        ++j;
        ++(*i);
    }
    --(*i);   /*因为在while内多加１ 这里要减去*/
    temp[j] = '\0';
    
    j = 0;
   
    while ((reserveds[j]).sign != NULL)
    {
        if (0 == strcmp(temp, (reserveds[j]).sign))
        {
            write_reserved(temp, h_file);
            return;
        }
        ++j;
    }
    
    write_identifier(temp, h_file);
}

void  check_digit(char * line, int * i, FILE * h_file)
{
     int  j = 0;
     char temp[LINE_LEN_MAX] = "";
     
     while (isdigit(line[*i]) || isspace(line[*i]) || '.' == line[*i])
     {
         if ('.' == line[*i])
         {
             if ((*i < 1 && isdigit(line[*i + 1])) || (isdigit(line[*i - 1]) || isdigit(line[*i + 1])))
             {
                temp[j] = line[*i];
             }
         } 
         else
         {
             temp[j] = line[*i];
         }
         ++j;
         ++(*i);
     }
     --(*i);
     temp[j] = '\0';
     write_number(temp, h_file);
}

void  comment_line(char * line, FILE * h_file)
{
     line[strlen(line) - 1] = '\0';
     writeline_num(++linenum, h_file);
     write_comment(line, h_file);
}

void  check_others(char * line, int * i, FILE * h_file, FILE * s_file)
{
    int   j = 0;
    char  temp[LINE_LEN_MAX] = "";
    
    switch(line[*i])
    {
       case '#':
            write_processor(line, h_file);
            *i = strlen(line);
            break;
            
       case '/':
            ++(*i);
            if ('*' == line[*i])
            {
                *i = strlen(line);
                write_comment(line, h_file);
                
                if (!strstr(line, "*/"))
                {
                    fprintf(h_file, "\n");
                    while (fgets(line, LINE_LEN_MAX, s_file) && !strstr(line, "*/"))
                    {
                        comment_line(line, h_file);
                        fprintf(h_file, "\n");
                    }
                    if (line != NULL && strstr(line, "*/"))
                    {
                        comment_line(line, h_file);
                    }
                }
            }
            else if ('/' == line[*i])
            {
                 *i = strlen(line);
                 write_comment(line, h_file);
            }
            else
            {
                 write_symbol('/', h_file);
            }
            break;
       
       case  '\"':
             for (j = 0; j < strlen(line); ++j, ++(*i))
             {
                 temp[j] = line[*i];
                 if ('\"' == temp[j] && j != 0)
                 {
                    break;
                 }
             } 
             temp[++j] = '\0';
             write_string(temp, h_file);
             break;
             
       case  '\'':
             write_char(line[++(*i)], h_file);
             ++(*i);
             break;
             
       case  '+': 
       case  '-':
       case  '*': 
       case  '%':  
       case  '.':
       case  '{': 
       case  '}': 
       case  '[':  
       case  ']':  
       case  '(':
       case  ')': 
       case  '>': 
       case  '<':  
       case  '=':  
       case  '!':
       case  '&': 
       case  '|': 
       case  '^':  
       case  '~':  
       case  ',':
       case  ';': 
       case  '?': 
       case  ':':
             while ('\0' != (symbols[j]).sign)
             {
                if ((symbols[j]).sign == line[*i])
                {
                     break;
                }
                ++j;
             }
             write_symbol((symbols[j]).sign, h_file);
             break;
             
       default:
             break;
       
    }
}

void  writeline(char * line, FILE * h_file, FILE * s_file)
{
    int  i = 0;
    int  len =  strlen(line);
    
    for (; i < len; ++i)
    {
       if (!isspace(line[i]) && !iscntrl(line[i]))
       {
           if (isalpha(line[i]) || '_' == line[i])
           {
               check_alpha(line, &i, h_file);
           }
           else if (isdigit(line[i]) || '.' == line[i])
           {
               check_digit(line, &i, h_file);
           }
           else
           {
               check_others(line, &i, h_file, s_file);
           } 
       }
       else
       {
           fprintf(h_file, "%c", line[i]);
       }
    }
}

/*
 * 写入文件的头部部分  包括<html> <head> <title> <style> <pre> <code> 
 * <body> 等几个主要标签及其相关的参数. 
 */
void  write_header(char * html_file)
{
    FILE * file = fopen(html_file, "w");
     
    if (file != NULL)
    {
        fprintf(file, "%s%s%s%s", HTML_HEADER, html_file, HTML_META, HTML_STYLE); 
        fclose(file);
    }
    else
    {
        fprintf(stderr, "%s\n", "文件写入时出现错误");
        z_exit();
    }
}

/*
 * 解析源文件中的代码 并将代码逐行进行转换 实现对代码的加工 
 * 并将之输入到目标文件中。 
 */
void  write_code(char * source_file, char * html_file)
{
   FILE * s_file = fopen(source_file, "r");
   
   if (s_file != NULL)
   {
       char   line[LINE_LEN_MAX] = "";
       
       FILE * h_file = fopen(html_file, "a");
       
       if (h_file != NULL)
       {  
          while (fgets(line, LINE_LEN_MAX, s_file))
          {
               line[strlen(line) - 1] = '\0';
               writeline_num(linenum, h_file);
               writeline(line, h_file, s_file);
               fprintf(h_file, "\n");
               ++linenum;
          }
          
          fclose(s_file);
          fclose(h_file);
       }
       else
       {
           fclose(s_file);
           fprintf(stderr, "%s\n", "文件写入错误");
           z_exit(); 
       }
   }
   else
   {
       fprintf(stderr, "%s\n", "代码文件打开失败");
       z_exit();
   }
}

/*
 * 写入html文件的尾部部分 包括<pre> <code> <body> <html> 
 * 的结尾标签 
 */ 
void  write_tailer(char * html_file)
{
    FILE * file = fopen(html_file, "a");
    
    if (file != NULL)
    {
        fputs(HTML_TAILER, file);
        fclose(file);
    }
    else
    {
        fprintf(stderr, "%s\n", "文件写入时出现错误");
        z_exit();
    }
}

void  print_trans_info(char * source_file, char * html_file)
{
    fprintf(stderr, "完成由代码文件 %s  到  %s 的转换\n\n"
           "共转换 %6d 行.\n共用时 %.2lf 秒.\n", source_file,
           html_file, linenum, times); 
}

void  code_to_html(char * source_file, char *html_file)
{
    if (exist(source_file) == true)
    {
       if (exist(html_file) == false)
       {
          write_header(html_file);
          clock_t   begin = clock();
          write_code(source_file, html_file);
          clock_t   end = clock();
          times = (end - begin) * 1.0 / CLOCKS_PER_SEC;
          write_tailer(html_file);
          print_trans_info(source_file, html_file);
       }
       else
       {
           fprintf(stderr, "%s\n", "指定的目标文件已存在");
           z_exit();
       }
    }
    else
    {
      fprintf(stderr, "%s\n", "指定的代码文件不存在");
      z_exit();
    }
}
