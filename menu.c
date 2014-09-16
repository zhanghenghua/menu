/**************************************************************************************************/
/*  Copyright (C)2014 ZhangHenghua                                                                */
/*                                                                                                */
/*  FILE NAME             :  menu.c                                                               */
/*  PRINCIPAL AUTHOR      :  ZhangHenghua                                                         */
/*  SUBSYSTEM NAME        :  menu                                                                 */
/*  MODULE NAME           :  menu                                                                 */
/*  LANGUAGE              :  C                                                                    */
/*  TARGET ENVIRONMENT    :  ANY                                                                  */
/*  DATE OF FIRST RELEASE :  2014/09/10                                                           */
/*  DESCRIPTION           :  This is a menu program                                               */
/**************************************************************************************************/

/*
 * Revision log:
 *
 * Created by ZhangHenghua, 2014/09/10
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DESC_MAX_SIZE   1024
#define CMD_MAX_SIZE    128

int Help();
int Add();
int Exit();

typedef struct CmdNode
{
    char   *cmd;
    char   *cmdDesc;
    int    (*handler)();
    struct CmdNode  *next;
}tCmdNode;

tCmdNode head[] =
{
    {"help", "this is help cmd", Help, &head[1] },
    {"version", "menu program v1.0", NULL, &head[2] },
    {"add", "add a new cmd", Add, &head[3] },
    {"exit", "exit the cmd line", Exit, NULL }
};

tCmdNode *p = head;
tCmdNode *r = &head[3];

int main(void)
{
    printf("Command List: \n");
    while(p != NULL)
    {
        printf("%s --- %s \n", p->cmd, p->cmdDesc);
        p = p->next;
    }
    while(1)
    {
        int findFlag = 0;
        char cmdInput[CMD_MAX_SIZE];
        printf("Input a command : ");
        scanf("%s", cmdInput);
        p = head;
        while(p != NULL)
        {
            if(strcmp(p->cmd, cmdInput) == 0)
            {
                if(p->handler != NULL)
                {
                    p->handler();
                }
                else
                {
                    printf("%s --- %s \n", p->cmd, p->cmdDesc);
                }
                findFlag = 1;
                break;
            }
            p = p->next;
        }
        if(findFlag == 0)
        {
            printf("Command not find! \n");
        }
    }
    return 0;
}

int Help()
{
    p = head;
    while(p != NULL)
    {
        printf("%s --- %s \n", p->cmd, p->cmdDesc);
        p = p->next;
    }
    return 0;
}
int Add()
{
    int   existFlag = 0;
    char  *newCmd  = (char *)malloc(CMD_MAX_SIZE * sizeof(char));
    char  *newDesc = (char *)malloc(DESC_MAX_SIZE * sizeof(char));
    
    tCmdNode *cmdNode = (tCmdNode *)malloc(sizeof(tCmdNode));
    
    if(!cmdNode)
    {
        exit(0);
    }
    printf("Input cmd name : \n");
    scanf("%s", newCmd);
    printf("Input cmd description : \n");
    scanf("%s", newDesc);

    p = head;
    while(p != NULL)
    {
        if(strcmp(p->cmd, newCmd) == 0)
        {
            existFlag = 1;
            break;
        }
        p = p->next;
    }

    if(existFlag == 1)
    {
        free(cmdNode);
        printf("The cmd already exist! \n");
    }
    else
    {
        cmdNode->cmd = newCmd;
        cmdNode->cmdDesc = newDesc;
        cmdNode->handler = NULL;
        cmdNode->next = NULL;
        r->next = cmdNode;
        r = cmdNode;
    }
    return 0;
}
int Exit()
{
    exit(0);
}

