#define _CRT_SECURE_NO_WARNINGS 1

#ifndef __COMMENT_CONVERT_H__
#define __COMMENT_CONVERT_H__

#include <stdio.h>
#include <stdlib.h>

enum STATE
{
    NUL_STATE,//无状态
    C_STATE,  //c状态
    CPP_STATE,//c++状态
    END_STATE //结束状态
};
void DoNulState(FILE *pfIn, FILE *pfOut, enum STATE *s);
void DoCState(FILE *pfIn, FILE *pfOut, enum STATE *s);
void DoCppState(FILE *pfIn, FILE *pfOut, enum STATE *s);
void DoComment(FILE *pfIn, FILE *pfOut);

#endif //__COMMENT_CONVERT_H__
