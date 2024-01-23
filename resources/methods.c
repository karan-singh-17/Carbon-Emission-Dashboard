#include <Windows.h>
#include <stdio.h>
#ifdef _WIN64
#define GetTickCountFunc GetTickCount64
#else
#define GetTickCountFunc GetTickCount
#endif


#define MAX_BUFFER_SIZE 256

__declspec(dllexport) int isCharging()
{
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};

    HANDLE hReadPipe, hWritePipe;
    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
    {
        perror("CreatePipe");
        exit(EXIT_FAILURE);
    }

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    si.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = hWritePipe;
    si.hStdError = hWritePipe;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;

    const char *command = "powershell -NonInteractive -NoProfile (Get-CimInstance -ClassName CIM_Battery).BatteryStatus";

    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        perror("CreateProcess");
        CloseHandle(hReadPipe);
        CloseHandle(hWritePipe);
        exit(EXIT_FAILURE);
    }

    CloseHandle(hWritePipe);

    char buffer[128];
    DWORD bytesRead;
    if (!ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL))
    {
        perror("ReadFile");
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        exit(EXIT_FAILURE);
    }

    buffer[bytesRead] = '\0';

    CloseHandle(hReadPipe);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    int batteryStatus = atoi(buffer);

    return (batteryStatus == 2);
}

__declspec(dllexport) void best_efficiency()
{
    char command[200];
    sprintf(command, "powershell -NonInteractive -NoProfile -Command \"powercfg /s a1841308-3541-4fab-bc81-f71556f20b4a\"");

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    si.dwFlags |= STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;

    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        perror("CreateProcess");
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

__declspec(dllexport) void dark_mode()
{
    char command[256];

    const char *scriptPath = "resources/darkness.ps1";
    sprintf(command, "powershell -NonInteractive -NoProfile -ExecutionPolicy Bypass -File \"%s\"", scriptPath);

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    si.dwFlags |= STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;

    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        perror("CreateProcess");
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

__declspec(dllexport) void sleep_mode()
{
    char command[256];

    const char *scriptPath = "resources/sleep.ps1";
    sprintf(command, "powershell -NonInteractive -NoProfile -ExecutionPolicy Bypass -File \"%s\"", scriptPath);

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    si.dwFlags |= STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;

    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        perror("CreateProcess");
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

__declspec(dllexport) void screen_off()
{
    char command[256];

    const char *scriptPath = "resources/screen_off.ps1";
    sprintf(command, "powershell -NonInteractive -NoProfile -ExecutionPolicy Bypass -File \"%s\"", scriptPath);

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    si.dwFlags |= STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;

    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        perror("CreateProcess");
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

__declspec(dllexport) void screensaver_off()
{
    char command[256];

    const char *scriptPath = "resources/screensaver.ps1";
    sprintf(command, "powershell -NonInteractive -NoProfile -ExecutionPolicy Bypass -File \"%s\"", scriptPath);

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    si.dwFlags |= STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;

    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        perror("CreateProcess");
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

__declspec(dllexport) void setBrightness(int level)
{
    char command[200];
    sprintf(command, "powershell -NonInteractive -NoProfile -Command \"$brightness = %d; (Get-WmiObject -Namespace root/WMI -Class WmiMonitorBrightnessMethods).WmiSetBrightness(1, $brightness)\"", level);

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    si.dwFlags |= STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;

    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        perror("CreateProcess");
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

__declspec(dllexport) void switchToPowerSavingMode()
{
    setBrightness(20);

    const char *powerSavingCommands[] = {
        "powershell -Command \"powercfg /change standby-timeout-ac 0\"",
        "powershell -Command \"powercfg /change monitor-timeout-ac 0\"",
        "powershell -Command \"powercfg /change standby-timeout-dc 0\"",
        "powershell -Command \"powercfg /change monitor-timeout-dc 0\""};

    for (int i = 0; i < sizeof(powerSavingCommands) / sizeof(powerSavingCommands[0]); ++i)
    {
        SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};

        HANDLE hReadPipe, hWritePipe;
        if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
        {
            perror("CreatePipe");
            exit(EXIT_FAILURE);
        }

        STARTUPINFO si = {sizeof(STARTUPINFO)};
        si.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
        si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
        si.hStdOutput = hWritePipe;
        si.hStdError = hWritePipe;
        si.wShowWindow = SW_HIDE;

        PROCESS_INFORMATION pi;

        if (!CreateProcess(NULL, (LPSTR)powerSavingCommands[i], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
        {
            perror("CreateProcess");
            CloseHandle(hReadPipe);
            CloseHandle(hWritePipe);
            exit(EXIT_FAILURE);
        }

        CloseHandle(hWritePipe);

        WaitForSingleObject(pi.hProcess, INFINITE);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        CloseHandle(hReadPipe);
    }
}

__declspec(dllexport) int batteryLevel()
{
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};

    HANDLE hReadPipe, hWritePipe;
    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
    {
        perror("CreatePipe");
        exit(EXIT_FAILURE);
    }

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    si.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = hWritePipe;
    si.hStdError = hWritePipe;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;

    const char *command = "powershell -NonInteractive -NoProfile (Get-CimInstance -ClassName CIM_Battery).EstimatedChargeRemaining";

    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        perror("CreateProcess");
        CloseHandle(hReadPipe);
        CloseHandle(hWritePipe);
        exit(EXIT_FAILURE);
    }

    CloseHandle(hWritePipe);

    char buffer[128];
    DWORD bytesRead;
    if (!ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL))
    {
        perror("ReadFile");
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        exit(EXIT_FAILURE);
    }

    buffer[bytesRead] = '\0';

    CloseHandle(hReadPipe);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    int batteryLevel = atoi(buffer);

    return batteryLevel;
}

__declspec(dllexport) void cpu_usage()
{

    char command[256];
    const char *scriptPath = "resources/better_cpu.ps1";
    sprintf(command, "powershell -NonInteractive -NoProfile -ExecutionPolicy Bypass -File \"%s\"", scriptPath);

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    si.dwFlags |= STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;

    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        perror("CreateProcess");
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

__declspec(dllexport) void memory_usage()
{

    char command[256];
    const char *scriptPath ="resources/memory_usage.ps1";
    sprintf(command, "powershell -NonInteractive -NoProfile -ExecutionPolicy Bypass -File \"%s\"", scriptPath);

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    si.dwFlags |= STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;

    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        perror("CreateProcess");
        exit(EXIT_FAILURE);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

__declspec(dllexport) int last_booted()
{
    ULONGLONG uptime = GetTickCountFunc();
    int uptimeHours = (int)(uptime / (1000 * 60 * 60));
    return uptimeHours;
}

__declspec(dllexport) double idletime()
{
    LASTINPUTINFO lii;
    lii.cbSize = sizeof(LASTINPUTINFO);

    if (GetLastInputInfo(&lii))
    {
        DWORD idleTimeMillis = GetTickCount() - lii.dwTime;

        double idleTimeHours = idleTimeMillis / (1000.0 * 60.0);
        idleTimeHours = (int)(idleTimeHours * 100 + 0.5) / 100.0;

        return idleTimeHours;
    }
    return -1;
}

__declspec(dllexport) void opentaskmanager()
{
    ShellExecute(NULL, "open", "taskmgr.exe", NULL, NULL, SW_SHOWNORMAL);
    return;
}

__declspec(dllexport) int getBatteryDischargeRate()
{

    SECURITY_ATTRIBUTES saAttr;
    HANDLE hChildStdoutRd, hChildStdoutWr;
    PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;
    DWORD dwRead;
    CHAR chBuf[4096];
    BOOL bSuccess;

    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0))
    {
        return -1; 
    }

    SetHandleInformation(hChildStdoutRd, HANDLE_FLAG_INHERIT, 0);

    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = hChildStdoutWr;
    siStartInfo.hStdOutput = hChildStdoutWr;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    bSuccess = CreateProcess(NULL,
                             "powershell.exe gwmi -Class batterystatus -Namespace root\\wmi",
                             NULL,
                             NULL,
                             TRUE,
                             CREATE_NO_WINDOW,
                             NULL,
                             NULL,
                             &siStartInfo,
                             &piProcInfo);

    if (!bSuccess)
    {
        CloseHandle(hChildStdoutRd);
        CloseHandle(hChildStdoutWr);
        return -1; 
    }

    CloseHandle(hChildStdoutWr);

    DWORD bytesRead = 0;
    while (ReadFile(hChildStdoutRd, chBuf + bytesRead, sizeof(chBuf) - bytesRead, &dwRead, NULL) && dwRead != 0)
    {
        bytesRead += dwRead;
    }

    CloseHandle(hChildStdoutRd);

    WaitForSingleObject(piProcInfo.hProcess, INFINITE);

    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);

    if (bytesRead == 0)
    {
        return -1; 
    }

    char *line = strstr(chBuf, "DischargeRate");
    if (line != NULL)
    {
        int dischargeRate;
        if (sscanf(line, "%*[^0-9]%d", &dischargeRate) == 1)
        {
            return dischargeRate;
        }
    }
    return -1;
}

__declspec(dllexport) int getBatteryChargeRate()
{

    SECURITY_ATTRIBUTES saAttr;
    HANDLE hChildStdoutRd, hChildStdoutWr;
    PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;
    DWORD dwRead;
    CHAR chBuf[4096];
    BOOL bSuccess;
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = hChildStdoutWr;
    siStartInfo.hStdOutput = hChildStdoutWr;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
    siStartInfo.wShowWindow = SW_HIDE;

    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0))
    {
        return -1; 
    }

    SetHandleInformation(hChildStdoutRd, HANDLE_FLAG_INHERIT, 0);

    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = hChildStdoutWr;
    siStartInfo.hStdOutput = hChildStdoutWr;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    bSuccess = CreateProcess(NULL,
                             "powershell.exe gwmi -Class batterystatus -Namespace root\\wmi",
                             NULL,
                             NULL,
                             TRUE,
                             CREATE_NO_WINDOW,
                             NULL,
                             NULL,
                             &siStartInfo,
                             &piProcInfo);

    if (!bSuccess)
    {
        CloseHandle(hChildStdoutRd);
        CloseHandle(hChildStdoutWr);
        return -1; 
    }

    CloseHandle(hChildStdoutWr);

    DWORD bytesRead = 0;
    while (ReadFile(hChildStdoutRd, chBuf + bytesRead, sizeof(chBuf) - bytesRead, &dwRead, NULL) && dwRead != 0)
    {
        bytesRead += dwRead;
    }

    CloseHandle(hChildStdoutRd);

    WaitForSingleObject(piProcInfo.hProcess, INFINITE);

    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);

    if (bytesRead == 0)
    {
        return -1; 
    }


    char *line = strstr(chBuf, "ChargeRate");
    if (line != NULL)
    {
        int ChargeRate;
        if (sscanf(line, "%*[^0-9]%d", &ChargeRate) == 1)
        {
            return ChargeRate;
        }
    }
    return -1;
}

__declspec(dllexport) int running_apps()
{

    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};

    HANDLE hReadPipe, hWritePipe;
    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
    {
        perror("CreatePipe");
        exit(EXIT_FAILURE);
    }

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    si.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = hWritePipe;
    si.hStdError = hWritePipe;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;

    const char *command = "powershell -NonInteractive -NoProfile (Get-Process | Where-Object { $_.MainWindowTitle -ne '' }).Count";

    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        perror("CreateProcess");
        CloseHandle(hReadPipe);
        CloseHandle(hWritePipe);
        exit(EXIT_FAILURE);
    }

    CloseHandle(hWritePipe);

    char buffer[128];
    DWORD bytesRead;
    if (!ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL))
    {
        perror("ReadFile");
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        exit(EXIT_FAILURE);
    }

    buffer[bytesRead] = '\0';

    CloseHandle(hReadPipe);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    int running = atoi(buffer);

    return running;
}

__declspec(dllexport) int start_apps()
{
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};

    HANDLE hReadPipe, hWritePipe;
    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
    {
        perror("CreatePipe");
        exit(EXIT_FAILURE);
    }

    STARTUPINFO si = {sizeof(STARTUPINFO)};
    si.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = hWritePipe;
    si.hStdError = hWritePipe;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;

    const char *command = "powershell -NonInteractive -NoProfile $registryPath = 'HKCU:\\Software\\Microsoft\\Windows\\CurrentVersion\\Run'; (Get-Item -LiteralPath $registryPath).Property.Count";

    // Create the process
    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        perror("CreateProcess");
        CloseHandle(hReadPipe);
        CloseHandle(hWritePipe);
        exit(EXIT_FAILURE);
    }

    CloseHandle(hWritePipe);

    char buffer[128];
    DWORD bytesRead;
    if (!ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL))
    {
        perror("ReadFile");
        CloseHandle(hReadPipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        exit(EXIT_FAILURE);
    }

    buffer[bytesRead] = '\0';

    CloseHandle(hReadPipe);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    int start_ups = atoi(buffer);

    return start_ups;
}
