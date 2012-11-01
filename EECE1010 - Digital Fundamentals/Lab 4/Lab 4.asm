;**************************************************************
;* This stationery is serves as the framework for a           *
;* user application. For a more comprehensive program that    *
;* demonstrates the more advanced functionality of this       *
;* processor, please see the demonstration applications       *
;* located in the examples subdirectory of the                *
;* Metrowerks Codewarrior for the HC08 Program directory      *
;**************************************************************

; export symbols
            XDEF Entry, main
            ; we use export 'Entry' as symbol. This allows us to
            ; reference 'Entry' either in the linker .prm file
            ; or from C/C++ later on

            XREF __SEG_END_SSTACK   ; symbol defined by the linker for the end of the stack

; include derivative specific macros
            INCLUDE 'MC9S08GB60.inc'

; variable/data section
MY_ZEROPAGE: SECTION  SHORT         ; Insert here your data definition



; code section
MyCode:     SECTION
main:
Entry:
            LDHX   #__SEG_END_SSTACK ; initialize the stack pointer
            TXS
            CLI                     ; enable interrupts
mainLoop:
DATA_PORT:	  EQU	$0100	; mem-mapped address where data comes from
STATUS_PORT:	EQU	$0101	; mem-mapped address where device tells
				                ; us if there is data ready
MSB:		      EQU	%10000000	; most significant bit as a bit-mask
STORE_PLACE:	EQU	$1000	    ; where to place data that is read
AVERAGE_PLACE EQU $1001
COUNT:        EQU $1005
LOAD  COUNT,  7

loop:
	LOAD	STATUS_PORT, A	; read from the device’s status register
	LOAD	#MSB, B		      ; need a high-order bit reference value
	AND	B, A		          ; check if the bit is ON in the status
	BEQ	loop		          ; if not, try again …
	LOAD	DATA_PORT, A	  ; read the data and …
	LOAD STORE_PLACE, B
	ADD B,A
	STOR A, STORE_PLACE
	LOAD  X, STORE_PLACE
	ADD X, A
	STOR	A, STORE_PLACE	;  store it where needed

	STOR COUNT, C
	DEC C
	AND C, 0
	STOR C, COUNT
  BEQ	loop		          ; If we've gotten to our eighth run
                        ; continue, otherwise loop again
  
  ; We've gotten to eight
  ; Time to average our input 
  LOAD STORE_PLACE, A
  DIV 8,  A
  STOR A, AVERAGE_PLACE
  ; Now we've got our input average in A  
  
  ; Don't forget to reset our counter
  LOAD 0, A
  STOR A, COUNT
  
  
	JMP	loop		          ; wait for more data to be ready
