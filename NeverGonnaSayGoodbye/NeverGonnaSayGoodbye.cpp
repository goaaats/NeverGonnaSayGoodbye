// NeverGonnaSayGoodbye.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <tlhelp32.h>
#include <string>
#include <chrono>
#include <thread>

DWORD get_process_by_name(std::string name)
{
   PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (std::wstring(std::begin(name), std::end(name)).compare( entry.szExeFile ) == 0)
            {  
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

                return entry.th32ProcessID;
            }
        }
    }

    CloseHandle(snapshot);

    return 0;
}

HWND rickWindow = nullptr;
std::string rickTitle("Rick Astley - Never Gonna Give You Up [HQ]");
int rickTime = 220;
//int rickTime = 2;

BOOL CALLBACK enumwindows(HWND hwnd,LPARAM lParam)
{
    char wnd_title[256];

      GetWindowTextA(hwnd, wnd_title,sizeof(wnd_title));


   if(wnd_title)
   {
     std::string t(wnd_title);
      if(t.find( rickTitle ) != std::string::npos)
    {
        rickWindow = hwnd;
        return FALSE;
    }
   }

    
    return TRUE;
}

typedef LONG (NTAPI *NtSuspendProcess)(IN HANDLE ProcessHandle);

void suspend(DWORD processId)
{
   if(processId != 0)
   {
      HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

    NtSuspendProcess pfnNtSuspendProcess = (NtSuspendProcess)GetProcAddress(
        GetModuleHandleA("ntdll"), "NtSuspendProcess");

    pfnNtSuspendProcess(processHandle);
    CloseHandle(processHandle);
   }
}

int main()
{
   std::time_t startTime = std::time(nullptr);
   int _ = system("start iexplore https://www.youtube.com/watch?v=DLzxrzFCyOs");

   while(true)
   {
      EnumWindows( enumwindows, 0 );

      if(rickWindow)
      {
         std::cout << "got em: " + std::to_string( (int)rickWindow ) << std::endl;
      break;
      }
   }

   while(true)
   {
      std::time_t nowTime = std::time(nullptr);

      if(IsWindow( rickWindow ))
      {
         char wnd_title[256];

         GetWindowTextA(rickWindow, wnd_title,sizeof(wnd_title));


         if( wnd_title )
         {
            std::string t( wnd_title );
            if( t.find( rickTitle ) != std::string::npos )
            {
               std::cout << "open: " + std::to_string( nowTime - startTime ) + "/" + std::to_string(rickTime) << std::endl;
               continue;
            }
         }
      }

      if((nowTime - startTime) > rickTime)
      {
         std::cout << "pass: " + std::to_string( nowTime - startTime ) + "/" + std::to_string(rickTime) << std::endl;
         Beep( 529, 130 );
         std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
         Beep( 529, 100 );
         std::this_thread::sleep_for( std::chrono::milliseconds( 30 ) );
         Beep( 529, 100 );
         std::this_thread::sleep_for( std::chrono::milliseconds( 300 ) );
         Beep( 420, 140 );
         std::this_thread::sleep_for( std::chrono::milliseconds( 300 ) );
         Beep( 466, 100 );
         std::this_thread::sleep_for( std::chrono::milliseconds( 300 ) );
         Beep( 529, 160 );
         std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
         Beep( 466, 100 );
         std::this_thread::sleep_for( std::chrono::milliseconds( 30 ) );
         Beep( 529, 900 );
         return 0;
      }

      std::cout << "ded: " + std::to_string( nowTime - startTime ) + "/" + std::to_string(rickTime) << std::endl;

      _ = system("start iexplore https://www.youtube.com/watch?v=2NLAUARFWrc");

      suspend( get_process_by_name( "explorer.exe" ) );
      suspend( get_process_by_name( "taskmgr.exe" ) );
      suspend( get_process_by_name( "chrome.exe" ) );
      suspend( get_process_by_name( "firefox.exe" ) );
      suspend( get_process_by_name( "steam.exe" ) );
      suspend( get_process_by_name( "notepad.exe" ) );
      suspend( get_process_by_name( "vlc.exe" ) );
      return 0;
   }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
