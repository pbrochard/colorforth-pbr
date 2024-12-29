" Vim syntax file
" Language: colorforth-pbr (PBR variant)
" Maintainer: Philippe Brochard
" Latest Revision: 1 may 2024

" Place this file in ~/.vim/syntax/colorforth-pbr
" Add this in ~/.vimrc
" au BufRead,BufNewFile *.cf set filetype=colorforth-pbr

if exists("b:current_syntax")
  finish
endif

syn match prefixDefine ":" conceal
syn match prefixCompile "\^" conceal
syn match prefixExecute "\~" conceal
syn match prefixTick "'" conceal
syn match prefixTickEntry "`" conceal

syn match colorForthComment "\~\\.*$"
syn region colorForthBlockComment   start="(" end=")" fold contains=colorForthBlockComment

syn region colorForthDefine start=":" end=" " contains=ALL
syn region colorForthString start=/[cs]+\?"/ end=/"/
syn region colorForthTick start="'" end="[:~('`^]" contains=ALL
syn region colorForthTickEntry start="`" end="[:~('`^]" contains=ALL
syn region colorForthCompile start="\^" end="[:~('`\\]" contains=ALL
syn region colorForthExecute start="\~" end="[:^('`\\]" contains=ALL


let b:current_syntax = "colorforth-pbr"

hi prefixDefine ctermfg=Red
hi prefixCompile ctermfg=Green
hi prefixExecute ctermfg=Yellow
hi prefixTick ctermfg=Cyan
hi prefixTickEntry ctermfg=43

hi colorForthComment ctermfg=White
hi colorForthBlockComment ctermfg=White

hi colorForthDefine ctermfg=Red
hi colorForthCompile ctermfg=Green
hi colorForthExecute ctermfg=Yellow
hi colorForthTick ctermfg=Cyan
hi colorForthTickEntry ctermfg=43
hi colorForthString ctermfg=Magenta

command HidePrefix set conceallevel=3
command ShowPrefix set conceallevel=0

HidePrefix
