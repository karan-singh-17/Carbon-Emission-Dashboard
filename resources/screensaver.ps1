Add-Type @"
    using System;
    using System.Runtime.InteropServices;
    public class User32 {
        [DllImport("user32.dll", SetLastError = true)]
        public static extern bool SystemParametersInfo(int uiAction, int uiParam, ref int pvParam, int fWinIni);
        public const int SPI_SETSCREENSAVEACTIVE = 0x0011;
    }
"@

$disableScreenSaver = 0
[User32]::SystemParametersInfo([User32]::SPI_SETSCREENSAVEACTIVE, 0, [ref]$disableScreenSaver, 3)

Write-Host "Screen saver disabled."
