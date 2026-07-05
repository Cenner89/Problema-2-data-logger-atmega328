$ErrorActionPreference = "Stop"

$projectRoot = Split-Path -Parent $PSScriptRoot
$node = "C:\Users\wguar\.cache\codex-runtimes\codex-primary-runtime\dependencies\node\bin\node.exe"

powershell -ExecutionPolicy Bypass -File (Join-Path $PSScriptRoot "build.ps1")

if (Test-Path $node) {
    & $node (Join-Path $PSScriptRoot "test-filter.js")
} else {
    node (Join-Path $PSScriptRoot "test-filter.js")
}

Write-Host "Todos os testes passaram."
