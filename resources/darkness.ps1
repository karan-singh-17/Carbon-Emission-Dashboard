$registryPatha = "HKCU:\SOFTWARE\Microsoft\Windows\CurrentVersion\Themes\Personalize"
$registryNamea = "AppsUseLightTheme"
$registryPathb = "HKCU:\SOFTWARE\Microsoft\Windows\CurrentVersion\Themes\Personalize"
$registryNameb = "SystemUsesLightTheme"

Set-ItemProperty -Path $registryPatha -Name $registryNamea -Value 0
Set-ItemProperty -Path $registryPathb -Name $registryNameb -Value 0

Stop-Process -Name explorer -Force
