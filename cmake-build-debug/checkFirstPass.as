;no operands (with or without space or tab)
.dh
.asciz
.entry

;unrecognized
.dd $2
command $2

;insructions
.asciz abc123
.asciz "abc123
.db a
.db 128
.db -129
.dh 32768
.dh -32769
.dw 2147483648
.dw -2147483649
.db ,1
.db 2,
.db 1,,2
.db ++1
    .dhhhdfgdfgdsfgsdfgsdgfsdfgsdfgdsgsdfgsdgdsgfdsfgsdfgsdfg 1,2,3,4
adddddddddddddddddddddddddddddddddddddddddddddd $2, $3, $5
something: addiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii $4, $2, LABEL
somethingElse: .ascizzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz "acdfdsfaf"
some:add$1,$2,$3
    .db 1 2, 3
    .dw, 1, 2, 3
entry: .entry h
this line is gonna be so long that it will surpass the 80 characters limit and give out an error message regarding its length
someOne: .extern dodo

;labels
LABEL:
LABEL$: add
1LABEL: add
LABELLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL: add
add:
label: add
label: add