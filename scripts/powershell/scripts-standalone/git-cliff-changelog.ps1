param
(
    [String]$Template,
    [String]$OutputFilename="CHANGELOG.md"
)
if( $null -eq $Template )
{
    write-host( "No template provided, using git-cliff default." )
}
else
{
    write-host( "Template: $Template" )
}

if( $null -eq $OutputFilename )
{
    write-host( "No output filename provided, using default (CHANGELOG.md)." )
    $OutputFilename = "CHANGELOG.md"
}
else
{
    write-host( "Output Filename Parameter: $OutputFilename" )
}

$generationCommand = "git-cliff -c $Template -o $OutputFilename"
Invoke-Expression $generationCommand