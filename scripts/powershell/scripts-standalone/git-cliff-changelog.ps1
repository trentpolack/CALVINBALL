param($template, $outputFilename )
if( $null -eq $template )
{
    write-host( "No template provided, using git-cliff default." )
}
else
{
    write-host( "Template: $template" )
}

if( $null -eq $outputFilename )
{
    write-host( "No output filename provided, using default (CHANGELOG.md)." )
    $outputFilename = "CHANGELOG.md"
}
else
{
    write-host( "Output Filename Parameter: $outputFilename" )
}

$generationCommand = "git-cliff -c $template -o $outputFilename"
Invoke-Expression $generationCommand