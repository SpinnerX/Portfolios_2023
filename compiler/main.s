.global main
main:
	PUSH {LR}
	PUSH {R4-R12}

	MOV R0, #0
	MOV R1, #0
	MOV R2, #0
	MOV R3, #0
	MOV R4, #0
	MOV R5, #0
	MOV R6, #0
	MOV R7, #0
	MOV R8, #0
	MOV R9, #0
	MOV R10, #0
	MOV R11, #0
	MOV R12, #0
line_5:
	//  THIS IS A COMMENT
line_10:
	MOV R9, #0
line_11:
	MOV R4, #5
line_12:
	MOV R10, #1
line_20:
	CMP R9, R4
	BGT line_100
line_25:
	LDR R0, =line_25_string
	bl print_string
line_30:
	MOV R0, R9
	bl print_number
line_40:
	MOV R9, R9
	ADD R9, R10
line_50:
	BAL line_20
line_100:
	BAL quit

quit:
	MOV R0, #42
	POP {R4-R12}
	POP {PC}
.data
line_25_string: .asciz "X = "

