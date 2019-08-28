$projectName = "QtSerialCommands"

# Current path
$fullPath = $MyInvocation.MyCommand.Path
$currentPath = $fullPath.Substring(0,$fullPath.LastIndexOf("\"))
$projectPath = "$currentPath\$projectName"

rmdir -Force -Recurse "$currentPath\_Include"
rmdir -Force -Recurse "$currentPath\_Lib"
mkdir "$currentPath\_Include"
mkdir "$currentPath\_Lib"

cd "$currentPath\_Include"

Get-ChildItem $projectPath -Filter *.h | 
Foreach-Object {
    $content = Get-Content $_.FullName

	$content | ForEach-Object { $_ -replace " QTSERIALCOMMANDS_EXPORT", "" } | ForEach-Object { $_ -replace '#include "qtserialcommands_global.h"', "" } | Set-Content ($_.BaseName + '.h')
}

Copy-Item "$currentPath\x64\Release\$projectName.lib" "$currentPath\_Lib\$projectName.lib"
$debugPath = "$currentPath\_Lib\$projectName" + "d.lib"
Copy-Item "$currentPath\x64\Debug\$projectName.lib" $debugPath


pause