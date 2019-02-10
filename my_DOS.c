#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

char buffer[80], command[80], arg1[20], arg2[20];
int b_index;

// Function prototypes -----------------------------------------------------------------------------------------------------------------------
void startup(void);
void extract_command(void);
void get_argument(int index);
void interpreter(void);
void display_help(void);
void get_current_directory(char *);
void show_version(void);
void getarg(int);
void listdir(const char *, int);

// driver main function ----------------------------------------------------------------------------------------------------------------------
int main()
{
        char current_directory[80];
        startup();
        system("clear");
        while (1)
        {
                get_current_directory(current_directory);
                printf("C:\\%s> ", current_directory);
                fgets(buffer, 80, stdin);
                extract_command();
                interpreter();
        }
}

// Function definitions -----------------------------------------------------------------------------------------------------------------------

void get_current_directory(char *pwd)
{
        int index, index2 = 0;
        char directory[80];
        getcwd(directory, sizeof directory);
        index = strlen("/home/rohan/");
        while (directory[index] != '\0')
        {
                if (directory[index] == '/')
                        pwd[index2] = '\\';
                else
                        pwd[index2] = directory[index];
                index2++;
                index++;
        }
        pwd[index2] = '\0';
}

void startup()
{
        printf("Running startup script ...\n");
        sleep(1);
        printf("Invoking bash shell(sh) interpreter ...\n");
        sleep(1);
        printf("Mounting \\home\\prashant as local C: drive ...\n");
        sleep(1);
        printf("Loading DOS session ...\n");
        sleep(1);
}
void extract_command()
{
        b_index = 0;
        int index = 0, c_index = 0;
        while (buffer[index] == ' ')
                index++;
        while (buffer[index] != ' ')
        {
                if (buffer[index] == '\n')
                        break;
                command[c_index] = buffer[index];
                index++;
                c_index++;
        }
        b_index = index;
        command[c_index] = '\0';
}
void interpreter()
{
        char temp[80];
        if (!strcmp(command, "cls") || !strcmp(command, "CLS") || !strcmp(command, "cLs") || !strcmp(command, "clS") || !strcmp(command, "Cls") || !strcmp(command, "CLs") || !strcmp(command, "cLS") || !strcmp(command, "ClS"))
                system("clear");

        else if (!strcmp(command, "exit") || !strcmp(command, "EXIT") || !strcmp(command, "Exit") || !strcmp(command, "eXit") || !strcmp(command, "exIt") ||
                 !strcmp(command, "EXit") || !strcmp(command, "exIT") || !strcmp(command, "ExiT"))
                exit(0);

        else if (!strcmp(command, "help") || !strcmp(command, "HELP") || !strcmp(command, "Help") || !strcmp(command, "HElp") || !strcmp(command, "heLP") || !strcmp(command, "helP") ||
                 !strcmp(command, "HeLp"))
                display_help();

        else if (!strcmp(command, "\0"))
        {
        }

        else if (!strcmp(command, "DIR") || !strcmp(command, "dir") || !strcmp(command, "Dir") || !strcmp(command, "dIr") || !strcmp(command, "diR") || !strcmp(command, "DIr") ||
                 !strcmp(command, "dIR") || !strcmp(command, "DiR"))
                system("ls");

        else if (!strcmp(command, "pause") || !strcmp(command, "Pause") || !strcmp(command, "pAuse") || !strcmp(command, "paUse") || !strcmp(command, "pauSe") ||
                 !strcmp(command, "pausE") || !strcmp(command, "PAuse") || !strcmp(command, "pAUse") || !strcmp(command, "paUSe") || !strcmp(command, "pauSE") ||
                 !strcmp(command, "PAUse") || !strcmp(command, "pAUSe") || !strcmp(command, "paUSE") || !strcmp(command, "PAUSE"))
                getchar();

        else if (!strcmp(command, "ver") || !strcmp(command, "VER") || !strcmp(command, "Ver") || !strcmp(command, "vEr") || !strcmp(command, "veR") ||
                 !strcmp(command, "VEr") || !strcmp(command, "vER") || !strcmp(command, "VeR"))
                show_version();

        else if (!strcmp(command, "PATH") || !strcmp(command, "path") || !strcmp(command, "Path") || !strcmp(command, "PAth") || !strcmp(command, "paTH") || !strcmp(command, "PatH") ||
                 !strcmp(command, "PATh") || !strcmp(command, "pATH") || !strcmp(command, "PaTH"))
                system("echo $PATH");

        else if (!strcmp(command, "type") || !strcmp(command, "TYPE") || !strcmp(command, "Type") || !strcmp(command, "tYpe") || !strcmp(command, "tyPe") || !strcmp(command, "typE") ||
                 !strcmp(command, "TYpe") || !strcmp(command, "tYPe") || !strcmp(command, "tYpE") || !strcmp(command, "TYPe") || !strcmp(command, "tYPE") || !strcmp(command, "TyPE"))
        {
                getarg(1);
                sprintf(temp, "more %s", arg1);
                system(temp);
        }

        else if (!strcmp(command, "ECHO") || !strcmp(command, "echo") || !strcmp(command, "Echo") || !strcmp(command, "ECho") || !strcmp(command, "eCHo") || !strcmp(command, "ecHO") ||
                 !strcmp(command, "ECHo") || !strcmp(command, "eCHO") || !strcmp(command, "EcHO"))
        {
                getarg(3);
                if (!strcmp(arg1, "\0"))
                        printf("Echo is ON\n");
                else
                {
                        sprintf(temp, "echo %s", arg1);
                        system(temp);
                }
        }

        else if (!strcmp(command, "cd") || !strcmp(command, "CD") || !strcmp(command, "Cd") || !strcmp(command, "cD"))
        {
        change_directory:
                getarg(1);
                if (strcmp(arg1, "\0"))
                {
                        chdir(arg1);
                }
        }

        else if (!strcmp(command, "REN") || !strcmp(command, "ren") || !strcmp(command, "Ren") || !strcmp(command, "rEn") || !strcmp(command, "reN") || !strcmp(command, "REn") ||
                 !strcmp(command, "rEN"))
        {
                getarg(1);
                getarg(2);
                if (strcmp(arg1, "\0") && strcmp(arg2, "\0"))
                {
                        sprintf(temp, "mv %s %s", arg1, arg2);
                        system(temp);
                }
                else
                        printf("usage : command <source> <target>\n");
        }

        else if (!strcmp(command, "ERASE") || !strcmp(command, "erase") || !strcmp(command, "Erase") || !strcmp(command, "eRase") || !strcmp(command, "erAse") ||
                 !strcmp(command, "eraSe") || !strcmp(command, "ERase") || !strcmp(command, "eRAse") || !strcmp(command, "eraSE") || !strcmp(command, "ErasE") ||
                 !strcmp(command, "erAsE") || !strcmp(command, "eRaSe") || !strcmp(command, "EraSe"))
        {
                getarg(1);
                getarg(2);
                if (strcmp(arg2, "\0"))
                {
                        sprintf(temp, "rm %s", arg2);
                        system(temp);
                }
                if (strcmp(arg1, "\0"))
                {
                        sprintf(temp, "rm %s", arg1);
                        system(temp);
                }
                else
                        printf("usage : command <files> ...\n");
        }

        else if (!strcmp(command, "MD") || !strcmp(command, "md") || !strcmp(command, "Md") || !strcmp(command, "mD"))
        {
        make_directory:
                getarg(1);
                if (strcmp(arg1, "\0"))
                {
                        sprintf(temp, "mkdir %s", arg1);
                        system(temp);
                }
                else
                        printf("error : missing operand\n");
        }

        else if (!strcmp(command, "TREE") || !strcmp(command, "tree") || !strcmp(command, "Tree") || !strcmp(command, "tRee") ||
                 !strcmp(command, "trEe") || !strcmp(command, "treE") || !strcmp(command, "TRee") || !strcmp(command, "tREe") ||
                 !strcmp(command, "TreE") || !strcmp(command, "TREe") || !strcmp(command, "tREE"))
                listdir(".", 0);

        else if (!strcmp(command, "RD") || !strcmp(command, "rd") || !strcmp(command, "Rd") || !strcmp(command, "rD"))
        {
        remove_directory:
                getarg(1);
                sprintf(temp, "rmdir  %s", arg1);
                system(temp);
        }

        else if (!strcmp(command, "RMDIR") || !strcmp(command, "rmdir"))
                goto remove_directory;

        else if (!strcmp(command, "chdir") || !strcmp(command, "CHDIR"))
                goto change_directory;

        else if (!strcmp(command, "mkdir") || !strcmp(command, "MKDIR"))
                goto make_directory;

        else if (!strcmp(command, "attrib") || !strcmp(command, "ATTRIB"))
        {
        }

        else if (!strcmp(command, "copy") || !strcmp(command, "COPY") || !strcmp(command, "Copy") || !strcmp(command, "COpy") || !strcmp(command, "cOPy") ||
                 !strcmp(command, "CopY") || !strcmp(command, "copY") || !strcmp(command, "coPy:"))
        {
                getarg(1);
                getarg(2);
                if (strcmp(arg1, "\0") && strcmp(arg2, "\0"))
                {
                        sprintf(temp, "cp %s %s", arg1, arg2);
                        system(temp);
                }
                else
                        printf("usage : copy <source> <target>\n");
        }

        else if (!strcmp(command, "IPCONFIG") || !strcmp(command, "ipconfig") || !strcmp(command, "IPconfig") || !strcmp(command, "ipCONFIG"))
                system("ifconfig -a");

        else if (!strcmp(command, "ping") || !strcmp(command, "PING") || !strcmp(command, "Ping") || !strcmp(command, "pIng") || !strcmp(command, "piNg"))
        {
                getarg(1);
                sprintf(temp, "ping %s", arg1);
                system(temp);
        }

        else
                printf("Illegal command : %s\n", command);
}

// Help Global variables ----------------------------------------------------------------------
char *help[] = {
    "A short list of the most often used commands :",
    "<DIR    >  Directory View.",
    "<CD     >  Displays/changes the current directory.",
    "<CLS    >  Clear screen.",
    "<DEL    >  Removes one or more files.",
    "<EXIT   >  Exit from the shell ",
    "<MD     >  Make directory ",
    "<RD     >  Remove directory ",
    "<REN    >  Renames one or more files ",
    "<TYPE   >  Display the contents of a text file ",
    "<VER    >  View and set the reported DOS version",
    "<ECHO   >  Display messages and enable/disable command echoing",
    "<RENAME >  Renames one or more files",
    "<PAUSE  >  Waits for 1 keystroke to continue. ",
    "<ERASE  >  Removes one or more files.",
    "<PATH   >  to know standard path variables",
    "<MKDIR  >  Create directory",
    "<RMDIR  >  Delete directory",
    "<CHDIR  >  Change directory",
    "<ATTRIB >  Does noting , provided for compatibility",
    "<COPY   >  Copy files ",
    "<IPCONFIG> Configure a network interface",
    "<PING    > Send ICMP ECHO_REQUESTS to network hosts",
    0};
// Help display functions ------------------------------------------------------------------------
void display_help()
{
        int index;
        for (index = 0; help[index]; index++)
                puts(help[index]);
}

void show_version()
{
        printf("DOSbox version -9.78 ,Reported DOS version -10\n");
        printf("Programmed by : Rohan kumar\n");
}
void getarg(int flag)
{
        int c_index = 0;
        while (buffer[b_index] == ' ')
                b_index++;
        if (flag != 3)
        {
                while (buffer[b_index] != ' ')
                {
                        if (buffer[b_index] == '\n')
                                break;
                        if (flag == 1)
                                arg1[c_index] = buffer[b_index];
                        else if (flag == 2)
                                arg2[c_index] = buffer[b_index];
                        c_index++;
                        b_index++;
                }
        }
        else
        {
                while (buffer[b_index] != '\n')
                {
                        arg1[c_index] = buffer[b_index];
                        c_index++;
                        b_index++;
                }
        }
        if (flag == 1)
                arg1[c_index] = '\0';
        else if (flag == 2)
                arg2[c_index] = '\0';
        else if (flag == 3)
                arg1[c_index] = '\0';
}
void listdir(const char *name, int level)
{
        DIR *dir;
        struct dirent *entry;
        if (!(dir = opendir(name)))
                return;
        if (!(entry = readdir(dir)))
                return;
        do
        {
                if (entry->d_type == DT_DIR)
                {
                        char path[1024];
                        int len = snprintf(path, sizeof(path) - 1, "%s/%s", name, entry->d_name);
                        path[len] = 0;
                        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                                continue;
                        printf("%*s[%s]\n", level * 2, "", entry->d_name);
                        listdir(path, level + 1);
                }
                else
                        printf("%*s- %s\n", level * 2, "", entry->d_name);
        } while (entry = readdir(dir));
        closedir(dir);
}
