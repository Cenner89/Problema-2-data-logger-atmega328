$ErrorActionPreference = "Stop"

$projectRoot = Split-Path -Parent $PSScriptRoot
$srcDir = Join-Path $projectRoot "src"
$buildDir = Join-Path $projectRoot "build"
$xc8 = "C:\Program Files\Microchip\xc8\v3.10\bin\xc8-cc.exe"
$objcopy = "C:\Program Files\Microchip\xc8\v3.10\bin\avr-objcopy.exe"
$dfp = "C:\Program Files\Microchip\MPLABX\v6.30\packs\Microchip\ATmega_DFP\3.5.296\xc8"

if (-not (Test-Path $xc8)) {
    throw "XC8 nao encontrado em: $xc8"
}

if (-not (Test-Path $objcopy)) {
    throw "avr-objcopy nao encontrado em: $objcopy"
}

if (-not (Test-Path $dfp)) {
    throw "ATmega_DFP nao encontrado em: $dfp"
}

New-Item -ItemType Directory -Force -Path $buildDir | Out-Null

$sources = Get-ChildItem -Path $srcDir -Filter "*.c" | ForEach-Object { $_.FullName }
$output = Join-Path $buildDir "problema2.elf"
$hex = Join-Path $buildDir "problema2.hex"

$args = @(
    "-mcpu=atmega328p",
    "-mdfp=$dfp",
    "-std=c99",
    "-Wall",
    "-O1",
    "-I", $srcDir,
    "-o", $output
) + $sources

& $xc8 @args

if ($LASTEXITCODE -ne 0) {
    throw "Build falhou."
}

& $objcopy -O ihex -R .eeprom $output $hex

if ($LASTEXITCODE -ne 0) {
    throw "Geracao do HEX falhou."
}

Write-Host "Build concluido com sucesso."
Write-Host "ELF: $output"
Write-Host "HEX: $hex"
