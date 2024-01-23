$processes = Get-Process | Where-Object { $_.SessionId -ne 0 } | Select-Object ProcessName, CPU

$totalCPU = ($processes | Measure-Object -Property CPU -Sum).Sum

$cpuUsage = @{}

foreach ($process in $processes) {
    $processName = $process.ProcessName
    $cpu = $process.CPU

    if ($cpuUsage.ContainsKey($processName)) {
        $cpuUsage[$processName]["TotalCPU"] += $cpu
    } else {
        $cpuUsage[$processName] = @{
            TotalCPU = $cpu
        }
    }
}

$sortedResultsCPU = foreach ($processName in $cpuUsage.Keys) {
    $averageCPU = $cpuUsage[$processName]["TotalCPU"]
    $percentageCPU = $averageCPU / $totalCPU

    [PSCustomObject]@{
        ProcessName = $processName
        PercentageCPU = $percentageCPU
    }
}

$sortedResultsCPU = $sortedResultsCPU | Sort-Object -Property PercentageCPU -Descending

$sortedResultsCPU = $sortedResultsCPU | Where-Object { $_.ProcessName -notin (Get-Service | Select-Object -ExpandProperty DisplayName) }

$csvFilePath = "resources\cpu_data.csv"
$sortedResultsCPU | Select-Object ProcessName, @{Name='PercentageCPU'; Expression={"{0:P2}" -f $_.PercentageCPU}} | Export-Csv -Path $csvFilePath -NoTypeInformation

