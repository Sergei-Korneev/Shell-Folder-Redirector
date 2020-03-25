#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"

#include <cstdlib>
#include <windows.h>
#include <shlobj.h>
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <stdlib.h>
#include <knownfolders.h>
using namespace std;

#define WINVER 0x0600

HINSTANCE hInst;
//
//BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    switch(uMsg)
//    {
//    case WM_INITDIALOG:
//    {
//       // SetDlgItemText(hwndDlg,CTEXT , ("Type in text"));
//
//    }
//    return TRUE;
//
//    case WM_CLOSE:
//    {
//        EndDialog(hwndDlg, 0);
//    }
//    return TRUE;
//
//    case WM_COMMAND:
//    {
//        switch(LOWORD(wParam))
//        {
//        }
//    }
//    return TRUE;
//    }
//    return FALSE;
//}

#define _countof(a) (sizeof(a)/sizeof(*(a)))











typedef std::codecvt<wchar_t , char , mbstate_t> null_wcodecvt_base;

class null_wcodecvt : public null_wcodecvt_base
{
public:
    explicit null_wcodecvt(size_t refs = 0) : null_wcodecvt_base(refs) {}

protected:
    virtual result do_out(mbstate_t&,
                          const wchar_t* from,
                          const wchar_t* from_end,
                          const wchar_t*& from_next,
                          char* to,
                          char* to_end,
                          char*& to_next) const
    {
        size_t len = (from_end - from) * sizeof(wchar_t);
        memcpy(to, from, len);
        from_next = from_end;
        to_next = to + len;
        return ok;
    }

    virtual result do_in(mbstate_t&,
                         const char* from,
                         const char* from_end,
                         const char*& from_next,
                         wchar_t* to,
                         wchar_t* to_end,
                         wchar_t*& to_next) const
    {
        size_t len = (from_end - from);
        memcpy(to, from, len);
        from_next = from_end;
        to_next = to + (len / sizeof(wchar_t));
        return ok;
    }

    virtual result do_unshift(mbstate_t&, char* to, char*,
                              char*& to_next) const
    {
        to_next = to;
        return noconv;
    }

    virtual int do_length(mbstate_t&, const char* from,
                          const char* end, size_t max) const
    {
        return (int)((max < (size_t)(end - from)) ? max : (end - from));
    }

    virtual bool do_always_noconv() const throw()
    {
        return true;
    }

    virtual int do_encoding() const throw()
    {
        return sizeof(wchar_t);
    }

    virtual int do_max_length() const throw()
    {
        return sizeof(wchar_t);
    }
};


std::wostream& wendl(std::wostream& out)
{
    out.put(L'\r');
    out.put(L'\n');
    out.flush();
    return out;
}


std::wfstream& wendl(std::wfstream& out)
{
    out.put(L'\r');
    out.put(L'\n');
    out.flush();
    return out;
}





string delspace(string line){

	int length = line.length();
	for (int i = 0; i < length; i++) {
		if (line[i] == ' ')
		{
			line.erase(i, 1);
			length--;
			i--;
		}
	}
	return line;
}



struct paths{
	WCHAR  fullpath[2048];
	LPWSTR pszBuffer = fullpath;
	DWORD  dwMaxChars = _countof(fullpath);
	wstring directory;
	wstring disk;
	wstring file;
};


paths  SplitFilenameCustom(paths *paths1)
{

	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL)
	{

		GetModuleFileNameW(hModule, paths1->fullpath , paths1->dwMaxChars);


		size_t found;
               wstring line5  = (wstring)(paths1->pszBuffer);



               found= line5.find_last_of(L"/\\");
               paths1->directory = wstring(line5.begin(),line5.begin()+found);

                found=line5.find_first_of(L"/\\");
		paths1->disk = wstring(line5.begin(),line5.begin()+found);

		found = line5.find_last_of(L"/\\");
		paths1->file = wstring(line5.begin() + found+1, line5.end());

		return *paths1;

	}
	else
	{

	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------------

  int write_config()
{

wchar_t UTF_BOM = 0xfeff;
paths o;
	SplitFilenameCustom(&o);
	LPCWSTR swdir = o.directory.c_str();
	SetCurrentDirectoryW(swdir);
 	fstream file2;
        wstring tt=(o.directory+(L"\\")+(o.file)+(L"_current_.txt"));
        DeleteFileW(tt.c_str());



null_wcodecvt wcodec(1);
    std::locale wloc(std::locale::classic(), &wcodec);
    // сообщаем файлу, что он должен использовать этот конвертер,
    // а не стандартный. обязательно делаем это _до_ открытия файла
    file2.imbue(wloc);




        wchar_t uu;
          for(int i = 0; i < tt.length(); ++i)  uu += wchar_t( tt[i] );
          char* wide_string = new char[ tt.length() + 1 ];
std::copy( tt.begin(), tt.end(), wide_string );
wide_string[ tt.length() ] = 0;
 	file2.open(wide_string, ios_base::out );//|std::ios::binary|std::ios::app);





CHAR  fullpath[2048] = { 0 };
		LPSTR path2 = fullpath;

WCHAR  fullpathw[2048] = { 0 };
		LPWSTR pathw = fullpathw;
int msgboxID;
    int ii=0;

WCHAR  mmm[2048]= { 0 };
LPWSTR path7 = mmm;
 wchar_t *str= new wchar_t[sizeof(ii)];
  char *str2= new char[sizeof(ii)];
   wchar_t tr;
wcscat(path7, L"Shell Folders [SHGetFolderPath]:\n\n");
    	while (ii != 100) {
			if (SHGetFolderPathA(NULL, ii, NULL, 0, path2) == S_OK&&SHGetFolderPathW(NULL, ii, NULL, 0, pathw) == S_OK)
			{
//file2.write(path2,strlen(path2));
//fflush(stdout);

                _itow(ii,str,10);
                wcscat(path7, str);
                wcscat(path7, L"  ");
                wcscat(path7, pathw);
                wcscat(path7, L"\n");

//file2.write(path2,strlen(path2));
//file2.write(path2,strlen("\\n"));
//_setmode(_fileno(stdout),0x00020000);
 _itoa(ii,str2,10);
file2<<str2<<"::"<<path2<<"\0"<<"\n";

//  tr = 0x000d;
 //  file2<<tr;
 //  tr=0x000a;
 //  file2<<tr;

			}
			 ii++;

	//LPWSTR concatted = concatted_stdstr.c_str();

}

file2.flush();
file2.close();

  delete str;
			 msgboxID = MessageBoxW(
        NULL,
        path7,
        L"Shell Folder Redirector 1.3",
        MB_ICONINFORMATION| MB_OK
    );

    if (msgboxID == IDYES)
    {
        // TODO: add code
    }




  return msgboxID;

}


//DllImport( "Shell32.dll", CharSet = CharSet.Unicode, EntryPoint = "#232" ) ;
//private static extern int SHSetFolderPath( int csidl, IntPtr hToken, uint flags, string path );

typedef int (__stdcall *f_funci)( int     csidl,    HANDLE  hToken, DWORD   dwFlags, LPCWSTR pszPath);
typedef int (__stdcall *f_funci2)(GUID   csidl, DWORD   dwFlags,    HANDLE  hToken, PWSTR pszPath);


//-----------------------------------------------------------------------------------------------------------------------------------------
 int apply_config(wchar_t *fpath){

paths o;
	SplitFilenameCustom(&o);
	LPCWSTR swdir = o.directory.c_str();
	SetCurrentDirectoryW(swdir);

 	//wstring tt=(o.directory+(L"\\")+(o.file)+(L"_current_.txt"));
wstring tt=fpath;

	string line;

	fstream file;

	 wchar_t uu;
          for(int i = 0; i < tt.length(); ++i)  uu += wchar_t( tt[i] );
          char* wide_string = new char[ tt.length() + 1 ];
std::copy( tt.begin(), tt.end(), wide_string );
wide_string[ tt.length() ] = 0;

//MessageBoxW(NULL, tt.c_str(), L"Error", MB_OK);

ifstream my_file(wide_string);
if (my_file){my_file.close();}
 else{ MessageBoxW(NULL, L"Unable to open config file.", L"Shell Folder Redirector 1.3", MB_OK);
return 0;

 };


	file.open(wide_string, ios_base::in );


	//wfstream file(".\\itembuilds.txt");
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	//file.open("Y:\\MYDOCS\\Visual Studio 2013\\Projects\\Shell Folders\\Release\\itembuilds.txt");


	int count = 1;
	while (!0)
	{

		try
		{
			getline(file, line);


			//cout << "next line is .. " << line << endl << endl;


			string line2 = line;
			line = delspace(line);
			////wstring stemp = std::wstring(line.begin(), line.end());
			////LPCWSTR sw = stemp.c_str();
			////cout << sw;

			////int ii = 33;
			////string srch = "123";

			////size_t found = line.find(srch.append(to_string(ii)));

			////if (found != string::npos) { cout << found << endl; }


			size_t found;
			string line3, line4;

			found = line2.find("::")+1;
			if (found != string::npos) {

				line3.append(line2.begin() + found + 1, line2.end());
				line4.append(line2.begin(), line2.begin() + found-1);
			line4 = delspace(line4);


//
//MessageBox(
//        NULL,
//        line3.c_str(),
//        "Shell Folder Redirector 1.0 [Sergei Korneev 2016]",
//        MB_ICONINFORMATION| MB_OK
//    );

				//cout << "tree:" << line3 << line4 << endl;




				int _cnt = atoi(line4.c_str());



			//	cout << "node:" << tt << endl;
		//if (SHGetFolderPathW(NULL, tt, NULL, 0, path2) == S_OK)
				//{
//				//_setmode(_fileno(stdout), _O_U16TEXT);
//
//MessageBox(
//        NULL,
//        line4.c_str(),
//        "Shell Folder Redirector 1.0 [Sergei Korneev 2016]",
//        MB_ICONINFORMATION| MB_OK
//    );


				wstring str1 = wstring(line3.begin(), line3.end());

				LPCWSTR sw = str1.c_str();


DWORD attribs = ::GetFileAttributesW(sw);
//GUID IDD_SomeId = { 0x4bd8d571, 0x6d19, 0x48d3, 0xbe, 0x97, 0x42, 0x22, 0x20, 0x08, 0x0e, 0x43 };

  if (attribs != 0xffffffff && (attribs & FILE_ATTRIBUTE_DIRECTORY)) {

HMODULE lib = LoadLibrary("Shell32.dll");
if (lib) {
f_funci funci = (f_funci)GetProcAddress(lib, "SHSetFolderPathW");
 if (funci) {
funci(_cnt, NULL, NULL, sw);


WCHAR  fullpathw[2048] = { 0 };
LPWSTR pathw = fullpathw;

HKEY hKey;


if (_cnt==39){
 SHGetFolderPathW(NULL, _cnt, NULL, 0, pathw);
if (RegOpenKeyExW(HKEY_CURRENT_USER,L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders", NULL, KEY_ALL_ACCESS, &hKey)==ERROR_SUCCESS)
{
//win 10 mymictures
RegSetValueExW(hKey,L"{0DDD015D-B06C-45D5-8C4C-F59713854639}", NULL, REG_EXPAND_SZ,(LPBYTE) &fullpathw,  sizeof(fullpathw));
RegCloseKey(hKey);

}

}

if (_cnt==14){
 SHGetFolderPathW(NULL, _cnt, NULL, 0, pathw);
if (RegOpenKeyExW(HKEY_CURRENT_USER,L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders", NULL, KEY_ALL_ACCESS, &hKey)==ERROR_SUCCESS)
{
//win 10 myvideo
RegSetValueExW(hKey,L"{35286A68-3C57-41A1-BBB1-0EAE73D76C95}", NULL, REG_EXPAND_SZ,(LPBYTE) &fullpathw,  sizeof(fullpathw));
RegCloseKey(hKey);

}

}



if (_cnt==13){

//win 10 mymusic
 SHGetFolderPathW(NULL, _cnt, NULL, 0, pathw);
if (RegOpenKeyExW(HKEY_CURRENT_USER,L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders", NULL, KEY_ALL_ACCESS, &hKey)==ERROR_SUCCESS)
{
RegSetValueExW(hKey,L"{A0C69A99-21C8-4671-8703-7934162FCF1D}", NULL, REG_EXPAND_SZ,(LPBYTE) &fullpathw, sizeof(fullpathw));
RegCloseKey(hKey);
}
}



if (_cnt==5){

SHGetFolderPathW(NULL, _cnt, NULL, 0, pathw);
if (RegOpenKeyExW(HKEY_CURRENT_USER,L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders", NULL, KEY_ALL_ACCESS, &hKey)==ERROR_SUCCESS)
{
//win 10 mydocs
RegSetValueExW(hKey,L"{F42EE2D3-909F-4907-8871-4C22FC0BF756}", NULL, REG_EXPAND_SZ,(LPBYTE) &fullpathw,  sizeof(fullpathw));
RegCloseKey(hKey);

}
}



if (_cnt==0||_cnt==16) {


funci(16, NULL, NULL, sw);funci(0, NULL, NULL, sw);


        }

 }

//f_funci2 funci2 = (f_funci2)GetProcAddress(lib, "SHSetKnownFolderPath");
// if (funci2) {
//funci2(IDD_SomeId, NULL, NULL, L"c:\\2");
//if (_cnt==0||_cnt==16) {funci2(16, NULL, NULL, sw);funci2(0, NULL, NULL, sw);}
//MessageBoxW(NULL,L"b", L"Error", MB_ICONERROR);


 //}




}
  }


			// Let's refresh the explorer:
				LPITEMIDLIST pidl;
				SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl);

				SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, pidl, 0);
SendMessage(HWND_BROADCAST,  WM_SETTINGCHANGE, 0, 0);
SendMessage(HWND_BROADCAST,  WM_CHANGEUISTATE, 0, 0);

SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM) TEXT(L"Environment"), SMTO_ABORTIFHUNG, 5000, NULL);
//
//SHChangeNotify(
//           LONG    wEventId,
//           UINT    uFlags,
//  _In_opt_ LPCVOID dwItem1,
//  _In_opt_ LPCVOID dwItem2
//);
//
//
//HRESULT SHParseDisplayName(
//  _In_      LPCWSTR          pszName,
//  _In_opt_  IBindCtx         *pbc,
//  _Out_     PIDLIST_ABSOLUTE *ppidl,
//  _In_      SFGAOF           sfgaoIn,
//  _Out_opt_ SFGAOF           *psfgaoOut
//);
//
//     int iAttribute;
//     IntPtr oldPidl;
//     IntPtr newPidl;
//     SHParseDisplayName(OldDesktop, NULL, out oldPidl, 0, out iAttribute);
//     SHParseDisplayName(NewDesktop,NULL, out newPidl, 0, out iAttribute);
//     SHChangeNotify(0x00020000, 0x1000, oldPidl, newPidl);


			}





		}
		catch (std::ifstream::failure e)
		{
			cout << "An exception occurred. Exception Nr. " << e.what()<<'\n';
			cin.get();
			break;
		}

	}
	file.close();



 }




//-------------------------------------------------------------------------------------

void Help(){
 MessageBoxW(
        NULL,
        L"Shell Folder Redirector 1.3 [Sergei Korneev 2016]\nThis utility is designed to change paths to shell folders, e.g. 'My Documents' etc. in batch by configuration file.   \nUse: \nprogram.exe save - save current config and show paths.\nprogram.exe apply <configfile> - apply config file.",
        L"Shell Folder Redirector 1.3",
        MB_ICONINFORMATION| MB_OK
    );
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //hInst=hInstance;
   // InitCommonControls();
    //return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);

//SetDlgItemText(CTEXT , ("Type in text"));
  // SetDlgItemText( hInst, , "87987" );
//write_config();


 DWORD dwVersion = 0;
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0;
    DWORD dwBuild = 0;

    dwVersion = GetVersion();

    // Get the Windows version.

    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    // Get the build number.3

    if (dwVersion < 0x80000000)
        dwBuild = (DWORD)(HIWORD(dwVersion));


         wchar_t *str= new wchar_t[sizeof(dwMajorVersion)];
 _itow(dwMajorVersion,str,10);
if (dwMajorVersion<6){
        MessageBoxW(NULL,L"At this time program tested for Windows NT6 only, Windows XP or lower is not supported, sorry.", L"Error", MB_ICONERROR);

         return 11;
};

  LPWSTR *szArgList;
    int argCount;

     szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount);
     if (argCount <2)
     {

        Help();
        return 0;
     }

     if (szArgList == NULL)
     {
         MessageBoxW(NULL, L"Unable to parse command line", L"Error", MB_OK);

         return 10;
     }

     for(int i = 1; i < argCount; i++)
     {
       //

        if(wcsstr(szArgList[i], L"save"))
        {
            write_config();
             return 0;
        }

        if(wcsstr(szArgList[i], L"apply")&&argCount ==3&&i == 1 )
        {

            apply_config(szArgList[i+1]);
            //MessageBoxW(NULL, szArgList[i], L"Arglist contents", MB_OK);


             return 0;

        }


     }
 Help();
     LocalFree(szArgList);

//write_config();

}
