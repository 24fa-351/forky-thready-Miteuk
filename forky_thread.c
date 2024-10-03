#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


// FUNCTION to Create Processes
void create_process(int id){
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char cmd[256];
    snprintf(cmd, sizeof(cmd),"cmd.exe /C echo Child process %d, PID: %lu", id, GetCurrentProcessId());

    if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
        printf("Create Process failed (%d).\n", GetLastError());
        return;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
// Main -> 1,2,3,4,5,6,7
void pattern1(int num_things){
   for(int ix = 0; ix < num_things; ix++){
    create_process(ix + 1);
   }
}

// Main -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7
void pattern2(int num_things){
    for(int iy = 0; iy < num_things; iy++){
        create_process(iy + 1);
        Sleep(100);
    }
}

void pattern3(int num_things){
    for(int iy = 0; iy < num_things; iy++){
        create_process(iy + 1);
        Sleep(100);
    }
}

int main(int argc, char *argv[]) {

    int num_things = atoi(argv[1]);
    int pattern = atoi(argv[2]);

    if(pattern == 1){
        pattern1(num_things);
    }
    else if(pattern == 2){
        pattern2(num_things);
    }
    else if(pattern == 3){
        pattern3(num_things);
    }

    return 0;
}