#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <windows.h>
#include <windef.h>
#include <winnt.h>
#include <winbase.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>
#include <processthreadsapi.h>

int main(int argc, char *argv[]) 
{
    char char_choice[3];
    int int_choice = 0;
    
    STARTUPINFO si;
    STARTUPINFO siWindow;
    PROCESS_INFORMATION pi;
    DWORD exitCode = 9999;
    
    siWindow.dwX = xPlacement;
    siWindow.dwY = yPlacement;
    siWindow.dwFillAttribute = colorController;
    
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
    
    char* sysDrive = getenv("SystemDrive"); // C
    char* sysRoot = getenv("SystemRoot"); // C:\Windows
    char* programFiles = getenv("ProgramFiles"); // C:\Windows\ProgramFiles
    char* homeDrive = getenv("HomeDrive"); // C:\Windows\ProgramFiles\HomeDrive
    
    static char *colorController = _putenv("dwFillAttribute=BACKGROUND_RED| FOREGROUND_RED| FOREGROUND_GREEN");
    static int *xPlacement = _putenv("dwX=0");
    static int *yPlacement = _putenv("dwY=0");
    
    
    
    do
    {
        printf("Please make a choice from the following list./n");
        printf("   0: Quit/n");
        printf("   1: Run Notepad/n")
        printf("  *2: Run CMD Shell/n");
        printf("  #3: Run NS LookUp/n");
        printf("   4: Run Character Map/n");
        printf("   5: Run WordPad/n");
        printf("Enter your choice now: "/n);
        
        scanf("%s", char_choice);
        int_choice = atoi(char_choice);
        
        switch(int_choice)
        {
            case 1:
                sprintf(buffer, "%s:\%s\%s\%s\%s", sysDrive, sysRoot, programFiles, homeDrive, "notepad.exe");
                
                if(!CreateProcessA(
                    &buffer, 
                    NULL,
                    NULL,
                    NULL,
                    FALSE,
                    O,
                    NULL,
                    NULL,
                    &si,
                    &pi );
                )
                {
                    printError();
                }
                    
                printf("Started program 1 with PID = %d/n/n", pi.dwProccessID);
                break;
            
            case 2:
                SETX PROMPT Speak Up:$g;
                start "What is you command?";
                
                sprintf(buffer, "%s:\%s\%s\%s\%s", sysDrive, sysRoot, programFiles, homeDrive, "cmd.exe");
                
                if(!CreateProcess(
                    &buffer,
                    argv[1],
                    NULL,
                    NULL,
                    FALSE,
                    CREATE_NEW_CONSOLE,
                    NULL,
                    NULL,
                    &siWindow,
                    &pi );
                )
                {
                    printError();
                }
                
                printf("Started program 2 with PID = %d/n", pi.dwProcessID);
                printf("   waiting for program to terminate..."/n)
                
                WaitForSingleObject(pi.hProcess, INFINITE);
                int value = GetExitCodeProcess(pi.hProcess, &lpExitCode);
                
                // Get Exit Code
                if(!GetExitCodeProcess(pi.hProcess, &exitCode))
                {
                    printError();
                }
                
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
                 
                printf("   program 2 exited with return value %d/n/n", value)
                break;
            
            case 3:
                sprintf(buffer, "%s:\%s\%s\%s\%s", sysDrive, sysRoot, programFiles, homeDrive, "charmap.exe");
                
                do
                {
                    if(!CreateProcessA(
                        &buffer,
                        NULL,
                        NULL,
                        NULL,
                        FALSE,
                        0,
                        NULL,
                        NULL,
                        &si,
                        &pi );
                    )
                    {
                        printError();
                    }
                    printf("Started program 3 with PID = %d/n/n", pi.dwProcessID);
                
                    WaitForSingleObject(pi.hProcess, INFINITE);
                }while(argv[1] != "exit")
                
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
                break;
                
            case 4:
                sprintf(buffer, "%s:\%s\%s\%s\%s", sysDrive, sysRoot, programFiles, homeDrive, "charmap.exe");
                
                if(!CreateProcessA(
                    &buffer,
                    NULL,
                    NULL,
                    NULL,
                    FALSE,
                    0,
                    NULL,
                    NULL,
                    &si,
                    &pi );
                )
                {
                    printError();
                }
                    
                printf("Started program 4 with PID = %d/n/n", pi.dwProcessID);
                break;
            
            case 5:
                sprintf(buffer, "%s:\%s\%s\%s\%s", sysDrive, sysRoot, programFiles, homeDrive, "wordpad.exe");
            
                if(!CreateProcessA(
                    &buffer,
                    NULL,
                    NULL,
                    NULL,
                    FALSE,
                    0,
                    NULL,
                    NULL,
                    &si,
                    &pi );
                )
                {
                    printError();
                }
                    
                printf("Started program 5 with PID = %d/n/n", pi.dwProcessID);
                break;
            
            default:printf("Please enter a valid selection from the list."/n);
                break;
            
        }while(int_choice != 0);
    }

    return 0;
}

void printError(char* functionName)
{
   LPVOID lpMsgBuf;
   int error_no;
   error_no = GetLastError();
   FormatMessage(
         FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
         NULL,
         error_no,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
         (LPTSTR) &lpMsgBuf,
         0,
         NULL
   );
   // Display the string.
   fprintf(stderr, "\n%s failed on error %d: ", functionName, error_no);
   fprintf(stderr, (char*)lpMsgBuf);
   // Free the buffer.
   LocalFree( lpMsgBuf );
   //ExitProcess(1);  // terminate the program
}
