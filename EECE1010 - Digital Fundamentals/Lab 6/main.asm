;**************************************************************
;* This stationery is serves as the framework for a           *
;* user application. For a more comprehensive program that    *
;* demonstrates the more advanced functionality of this       *
;* processor, please see the demonstration applications       *
;* located in the examples subdirectory of the                *
;* Metrowerks Codewarrior for the HC08 Program directory      *
;**************************************************************

; export symbols
		XDEF Entry, mainLoop, IOSetup, delay, delayTimerSetup, delayTimerLoop, getNum, moveLEDsRight, moveLEDsLeft, playerGuessOver, playerGuessUnder, playerGuessRight, flashLEDs
		; we use export 'Entry' as symbol. This allows us to
		; reference 'Entry' either in the linker .prm file
		; or from C/C++ later on

		XREF __SEG_END_SSTACK   ; symbol defined by the linker for the end of the stack

; include derivative specific macros
		INCLUDE 'MC9S08GB60.inc'

; variable/data section
MY_ZEROPAGE: SECTION  SHORT         ; Insert here your data definition


TIMER_STATUS	EQU	$30
TIMER_COUNTER_HIGH	EQU	$82
TIMER_COUNTER_LOW	EQU	$83
TIMER_MODULUS_HIGH	EQU	$33
TIMER_MODULUS_LOW	EQU	$34
LOCK_COMBINATION	EQU	$1000
USER_GUESS_COMBINATION	EQU	$1020



; code section
MyCode:     SECTION
main:
Entry:
	LDHX   #__SEG_END_SSTACK  ; initialize the stack pointer
	TXS
	CLI                       ; enable interrupts
			
IOSetup:
	CLRA			  ; special instruction to load a ZERO value into A

	LDA #$FF		; enable pull-up (all bits have pull up enabled)
	STA $43			; configure PORT F data direction (all bits OUTPUT)



mainLoop:
	LDA USER_GUESS_COMBINATION
	CMPA LOCK_COMBINATION 
	BEQ label1
	BLO label2
	JSR playerGuessOver
	BRA mainLoop
label1:
	JSR	playerGuessRight
	BRA mainLoop
	
label2:
	JSR playerGuessUnder
	BRA mainLoop

playerGuessRight:

	JSR flashLEDs
	RTS
	
playerGuessUnder:
  
	JSR moveLEDsRight
	RTS
	
playerGuessOver:
	JSR moveLEDsLeft
	RTS

moveLEDsRight:

	LDA #%1111
	SHR $40
	JSR delay
	SHR $40
	JSR delay
	SHR $40
	JSR delay
	SHR $40
	JSR delay
	LDA #%1111
	STA
	CLRA
	RTS
    
			
moveLEDsLeft:

	LDA #%1111
	SHL $40
	JSR delay
	SHL $40
	JSR delay
	SHL $40
	JSR delay
	SHL $40
	JSR delay
	LDA #%1111
	STA
	CLRA
	RTS      
	
	
flashLEDs:

	LDA #%1111
	JSR delay
	LDA #%0000
	JSR delay
	LDA #%1111
	JSR delay
	LDA #%0000
	JSR delay
	LDA #%1111
	JSR delay
	LDA #%0000
	JSR delay
	LDA #%1111
	JSR delay
	LDA #%0000
	JSR delay
	STA
	CLRA
	RTS
			
delay:
