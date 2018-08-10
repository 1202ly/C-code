#define _CRT_SECURE_NO_WARNINGS 1
#include"commentconvert.h"
void DoNulState(FILE*pfIn, FILE*pfOut, enum STATE* s)
{
    int first = 0;
    first = fgetc(pfIn);
    switch (first)
    {
    case'/':
    {
               int second;
               second = fgetc(pfIn);
               switch (second)
               {
               case'*':
                   fputc('/', pfOut);
                   fputc('/', pfOut);
                   *s = C_STATE;
                   break;
               case'/':
                   fputc(first, pfOut);
                   fputc(second, pfOut);
                   *s = CPP_STATE;
                   break;
               default:
                   fputc(first, pfOut);
                   fputc(second, pfOut);
                   break;
               }
               break;
    }
    case EOF:
        *s = END_STATE;
        break;
    default:
        fputc(first, pfOut);
        break;
    }
}

void DoCState(FILE *pfIn, FILE *pfOut, enum STATE *s)
{
    int first = 0;
    first = fgetc(pfIn);
    switch (first)
    {
    case'\n':
        fputc(first, pfOut);
        fputc('/', pfOut);
        fputc('/', pfOut);
        break;
    case'*':
    {
               int second = fgetc(pfIn);
               switch (second)
               {
               case'/':
               {
                          *s = NUL_STATE;
                          int third = fgetc(pfIn);
                          switch (third)
                          {
                          case'\n':
                              fputc(third, pfOut);
                              break;
                          case'/':
                              ungetc(third, pfIn);
                              fputc('\n', pfOut);
                              break;
                          default:
                              fputc('\n', pfOut);
                              fputc(third, pfOut);
                          }
               }
                   break;
               case'*':
                   fputc(second, pfOut);
                   ungetc(second,pfIn);
                   break;
               default:
                   fputc(first, pfOut);
                   fputc(second, pfOut);
                   break;
               }
       break;
    }
    case EOF:
        *s = END_STATE;
        break;
    default:
        fputc(first, pfOut);
        break;  
    }
}
void DoCppState(FILE *pfIn, FILE *pfOut, enum STATE *s)
{
    int first = 0;
    first = fgetc(pfIn);
    switch (first)
    {
    case'\n':
        fputc(first, pfOut);
        *s = NUL_STATE;
        break;
    case EOF:
        *s = END_STATE;
        break;
    default:
        fputc(first, pfOut);
        break;
    }
}
void DoComment(FILE*pfIn, FILE*pfOut, enum STATE* s)
{
    enum STATE state = NUL_STATE;
    while (state != END_STATE)
    {
        switch (state)
        {
        case NUL_STATE:
            DoNulState(pfIn, pfOut, &state);
            break;
        case C_STATE:
            DoCState(pfIn, pfOut, &state);
            break;
        case CPP_STATE:
            DoCppState(pfIn, pfOut, &state);
            break;
        default:
            break;
        }
    }
}
