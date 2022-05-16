#Main
#Write-Output "Tarile disponibile: "
#Write-Output "Culoare random: " 
#$culori | Get-Random -Count

#Intro
$scriptDir = if (-not $PSScriptRoot) {Split-Path -Parent (Convert-Path ([environment]::GetCommandLineArgs()[0]))} else {$PSScriptRoot}
$array1 = Get-Content $scriptDir\tari.txt | Sort-Object {Get-Random}
$array2 = Get-Content $scriptDir\culori.txt | Sort-Object {Get-Random}


ForEach ($line in $array1){
    "{0} - {1}" -f $line, $array2[$array1.IndexOf($line)]
}