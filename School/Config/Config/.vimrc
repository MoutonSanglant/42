let $USER = 'tdefresn'
let $MAIL = $USER . '@student.42.fr'


" Use Vim settings, rather than Vi settings.
" Must be first, because it changes other options as a side effect.
set nocompatible

" Allow backspacing over everything in insert mode
set backspace=indent,eol,start

syn on			" Syntaxic colors
set nu			" Show line numbers
set ruler		" Show the cursor position
set hlsearch	" Highlight found patterns
set colorcolumn=80	" Color line 80 (specific to 42's norm)
set shiftwidth=4
set softtabstop=4
set tabstop=4
set backupdir	=~/.vim/.backup//,.,/tmp
set directory	=~/.vim/.swp//,.,/tmp
set undodir	=~/vim/.undo//,.,/tmp

" If terminal emulates mouse, use it
if has('mouse')
	set mouse=a
endif

" Only do this part when compiled with support for autocommands.
if has ("autocmd")
	" language-dependant indenting
	filetype plugin indent on
else
	set autoindent	" Always set autoindenting on
endif

" Color for the max line length column
highlight ColorColumn ctermbg=grey guibg=grey
" Color for the line number column
highlight LineNr ctermfg=red ctermbg=DarkGrey guibg=#ffffff
" Color for the 42 header
highlight FtHeader ctermfg=yellow ctermbg=black guibg=black
" Color for the extra whitespace highlighting
highlight ExtraWhitespace ctermbg=red guibg=red
" highlight extra whitespace
" match ExtraWhitespace /\(^\t*\ \+\|[ \t]\_s\+\)/
match ExtraWhitespace /\(^\t*\ \+\|[ \t]\n\)/
" remove header highlighting
2match FtHeader /\(\_^\/\* .*\)\{0,1\}\n/

" Find the matching character under the cursor
" if it matches, ignore it
function g:MatchCursorCharacter (c, bs)
	let l:col = col('.') + 1
	let l:match = matchstr(getline('.'), '\%' . l:col . 'c.') == a:c
	if l:match
		if a:bs == '1'
			call feedkeys("\<Backspace>\<Right>")
		endif
		call feedkeys("\<Del>")
	endif
endfunction

" Remap ({['" characters in INSERT mode to auto-complete siblings if needed
inoremap ( ()<Esc>i
inoremap ) <Esc>:call g:MatchCursorCharacter(')', '0')<CR>i<Right>)
inoremap { {}<Esc>i
inoremap } <Esc>:call g:MatchCursorCharacter('}', '0')<CR>i<Right>}
inoremap [ []<Esc>i
inoremap ] <Esc>:call g:MatchCursorCharacter(']', '0')<CR>i<Right>]
inoremap " "<Esc>:call g:MatchCursorCharacter('"', '1')<CR>i<Right>"<Left>
inoremap ' '<Esc>:call g:MatchCursorCharacter("'", '1')<CR>i<Right>'<Left>

" Remap ({['" characters in VISUAL mode to put characters around selection
vnoremap ( <Esc>
vnoremap ) <Esc>
vnoremap { <Esc>
vnoremap } <Esc>
vnoremap [ <Esc>
vnoremap ] <Esc>
vnoremap " <Esc>
vnoremap ' <Esc>
