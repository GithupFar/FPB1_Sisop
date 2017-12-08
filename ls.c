/*header file*/
#include "includes.h"

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

/* ****************************************************************************
 *   Function: List
 * Desciption: list the file
 *  Arguments: char *path
  
 * ****************************************************************************/
int List(char *path)
{
    struct stat st;
    char temp[100];

    if (path == NULL)      //if path is NULL, get current file directory
    {  
        path = temp;  
        getcwd(path, 100);   
    }  
    if (lstat(path, &st))  //open the inode of file
    {
        err_ret("Error: %s not exist.\n", path);
    }
    if (S_ISDIR(st.st_mode)) //check whether it is directory or a regular file
    {  
        ListDir(path); 
    }  
    else if (S_ISREG(st.st_mode))    //if is regular file, then print the file name
    {  
        Print(path);  
    }  
    else
    {  
        printf("Not a regular file or directory, can't be listed.\n");  
    }  
    return 0;
}


/* ****************************************************************************
 *   Function: ListDir
 * Desciption: list the directory
 *  Arguments: char *path
  
 * ****************************************************************************/
int ListDir(char *path)
{
    DIR *dp;
    struct dirent *dirp; 
    struct stat st;
    void *buf;
    pFile pInfo = NULL;
    PListNode pHead,pNode,cur;

    if (!(pHead = InitList())) 
    {
        err_sys("init list failed!");
    }
    if ((dp = opendir(path)) == NULL)
    {
        err_sys("can't open %s\n", path);
    }
    chdir(path);                   //cd the path 
   
    while ((dirp = readdir(dp)) != NULL)
    {
        if (((strcmp(dirp->d_name, ".")) == 0)
         || ((strcmp(dirp->d_name, "..")) == 0)
         || (dirp->d_name[0] == '.'))
        {
            continue; //hmm
        }

        else
        {
            Print(dirp->d_name); 
        }
        
    }
    printf("\n");

    if (closedir(dp))
    {
       err_sys("can't close the directory %s\n", path);
    }
    DeleteList(pHead);
    return 0; 
}

/* ****************************************************************************
 *   Function: Print
 * Desciption: print file
 *  Arguments: char *path
  
 * ****************************************************************************/
int Print(char *path)
{
    struct stat st;
    char *fileName = NULL;
    char time[64];

    if (lstat(path, &st))  //open the inode of file
    {
        err_ret("Error: %s is not exist.\n", path);
    }
    if ((fileName = strrchr(path, '/')) != NULL)  //delete the directory, then get the file name 
    {  
        fileName++;  
    } 
    else
    {
        fileName = path;
    }
    else
    {
        printf("%s\t", fileName);
    }

    return 0;
}

/* ****************************************************************************
 *   Function: PrintNode
 * Desciption: print list node
 *  Arguments: PListNode pHead
  
 * ****************************************************************************/
void PrintNode(void *file)
{
    printf("%s\t", ((pFile)file)->name);
    printf("%10ld\t%10ld\n", ((pFile)file)->size, ((pFile)file)->time);
}

/* ****************************************************************************
 *   Function: CompareString
 * Desciption: 
 *  Arguments: PListNode pHead
 *
 *  **************************************************************************/
int CompareString(void *file1, void *file2)
{
    return (strcmp(((pFile)file1)->name, ((pFile)file2)->name));

}


/* ****************************************************************************
 *   Function: CompareSize
 * Desciption: 
 *  Arguments: void *file1, void *file2
 *
 *  **************************************************************************/
int CompareSize(void *file1, void *file2)
{
    if ((((pFile)file1)->size) < (((pFile)file2)->size))
    {
        return -1;
    }
    else  if ((((pFile)file1)->size) > (((pFile)file2)->size))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* ****************************************************************************
 *   Function: CompareTime
 * Desciption: 
 *  Arguments: void *file1, void *file2
 *
 *  **************************************************************************/
int CompareTime(void *file1, void *file2)
{
    if ((((pFile)file1)->time) < (((pFile)file2)->time))
    {
        return -1;
    }
    else if ((((pFile)file1)->time) > (((pFile)file2)->time))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/* ****************************************************************************
 *   Function: main
 * Desciption: 
 *  Arguments: int argc, char *argv[]
  
 * ****************************************************************************/

int main (int argc, char *argv[])
{
    //GetOptions(argc, argv);
    //List(argv[optind]);
    int i;

  if(argc < 2){
    List(".");
    exit();
  }
  for(i=1; i<argc; i++)
    List(argv[i]);
  exit();
}
