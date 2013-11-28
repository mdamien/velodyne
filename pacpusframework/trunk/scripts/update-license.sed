:writefromstart
0,/%pacpus:license{/ {
    p           # print line
    $b exit     # exit if the license not found (branch to exit if on on the last line)
}

# put license file after the line with %pacpus:license{
/%pacpus:license{/ {
    r ../LICENSE-header.txt
}

:writetillend
/%pacpus:license}/,$ {
    p           # print line
}

:exit
