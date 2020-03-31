#include "adeba.h"
#include "xor.h"

bool IsCorrectTargetArchitecture(HANDLE hProc)
{
	BOOL bTarget = FALSE;
	if (!IsWow64Process(hProc, &bTarget))
	{
		//printf("Nao pode confirmar a arquitetura alvo: 0x%X\n", GetLastError());
		return false;
	}

	BOOL bHost = FALSE;
	IsWow64Process(GetCurrentProcess(), &bHost);

	return (bTarget == bHost);
}

int main(int argc, char* argv[]) {
	char* szDllFile = argv[1];
	//char szProc[] = "csgo.exe";
	char szProc[] = "*:.&g,1,"; //"csgo.exe"

	if (argc != 2) {
		printf("Argumento invalido\n");
		system("PAUSE");
		return 0;
	}
	PROCESSENTRY32 PE32{ 0 };
	PE32.dwSize = sizeof(PE32);

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE) {
		DWORD Err = GetLastError();
		//printf("Falhou o snap: 0x%X\n", Err);
		system("PAUSE");
		return 0;
	}

	DWORD PID = 0;
	BOOL bRet = Process32First(hSnap, &PE32);
	while (bRet) {
		if (!strcmp(Decrypt(szProc).c_str(), PE32.szExeFile)) {
			PID = PE32.th32ProcessID;
			break;
		}
		bRet = Process32Next(hSnap, &PE32);
	}

	CloseHandle(hSnap);

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	/*if (!hProc)
	{
		DWORD Err = GetLastError();
		printf("Falha ao abrir processo: 0x%X\n", Err);
		system("PAUSE");
		return 0;
	}

	if (!IsCorrectTargetArchitecture(hProc))
	{
		printf("Processo alvo invalido\n");
		CloseHandle(hProc);
		system("PAUSE");
		return 0;
	}*/
	
	if (!hProc || !IsCorrectTargetArchitecture(hProc) || !ManualMap(hProc, szDllFile)) {
		CloseHandle(hProc);
		printf("Falhou\n");
		system("PAUSE");
		return 0;
	}

	CloseHandle(hProc);
		
	return 0;
}