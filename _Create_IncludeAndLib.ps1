$projectName = "QtSerialCommands"

$fullPath = $MyInvocation.MyCommand.Path
$projectPath = $fullPath.Substring(0,$fullPath.LastIndexOf("\"))

rmdir -Force -Recurse "$projectPath\_Include"
rmdir -Force -Recurse "$projectPath\_Lib"
mkdir "$projectPath\_Include"
mkdir "$projectPath\_Lib"

cd "$projectPath\_Include"

Get-ChildItem $projectPath -Filter *.h | 
Foreach-Object {
    $content = Get-Content $_.FullName

	$content | ForEach-Object { $_ -replace " QTSERIALCOMMANDS_EXPORT", "" } | ForEach-Object { $_ -replace '#include "qtserialcommands_global.h"', "" } | Set-Content ($_.BaseName + '.h')
}

Copy-Item "$projectPath\x64\Release\$projectName.lib" "$projectPath\_Lib\$projectName.lib"
$debugPath = "$projectPath\_Lib\$projectName" + "d.lib"
Copy-Item "$projectPath\x64\Debug\$projectName.lib" $debugPath


pause