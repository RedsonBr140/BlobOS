println:
	pusha
	mov ah, 0xE		; Print a char.

.loop:
	lodsb			; Load SI into AL.
	cmp AL, 0		; Reached end?
	je .done		; If so, end printing.
	int 0x10		; Interruption 10h.
	jmp .loop		; Recursion.


.done:
	popa
	ret			; Return to start.

