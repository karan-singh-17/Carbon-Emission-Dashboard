$processes = Get-Process | Where-Object { $_.SessionId -ne 0 } | Select-Object ProcessName, WorkingSet

$totalMemory = ($processes | Measure-Object -Property WorkingSet -Sum).Sum

$memoryUsage = @{}

foreach ($process in $processes) {
    $processName = $process.ProcessName
    $memory = $process.WorkingSet

    if ($memoryUsage.ContainsKey($processName)) {
        $memoryUsage[$processName]["TotalMemory"] += $memory
    } else {
        $memoryUsage[$processName] = @{
            TotalMemory = $memory
        }
    }
}

$sortedResultsMemory = foreach ($processName in $memoryUsage.Keys) {
    $averageMemory = $memoryUsage[$processName]["TotalMemory"]
    $percentageMemory = $averageMemory / $totalMemory

    [PSCustomObject]@{
        ProcessName = $processName
        PercentageMemory = $percentageMemory
    }
}

$sortedResultsMemory = $sortedResultsMemory | Sort-Object -Property PercentageMemory -Descending

$sortedResultsMemory = $sortedResultsMemory | Where-Object { $_.ProcessName -notin (Get-Service | Select-Object -ExpandProperty DisplayName) }

$csvMemoryFilePath = "resources\memory_usage.csv"
$sortedResultsMemory | Select-Object ProcessName, @{Name='PercentageMemory'; Expression={"{0:P2}" -f $_.PercentageMemory}} | Export-Csv -Path $csvMemoryFilePath -NoTypeInformation