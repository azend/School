

moveLEDsRight:
	PSH	A
	LDA	DATA_PORT
	SHR	A
	STA	DATA_PORT
	PUL	A
	RTS

moveLEDsLeft:
	PSH	A
	LDA	DATA_PORT
	SHL	A
	STA	DATA_PORT
	PUL	A
	RTS

flashLEDs:
	PSH	A
	
	; 1st Blink
	LDA #%00001111
	STA DATA_PORT	
	JSR delay
	
	LDA #%00000000
	STA DATA_PORT	
	JSR delay

	; 2nd Blink
	LDA #%00001111
	STA DATA_PORT	
	JSR delay
	
	LDA #%00000000
	STA DATA_PORT	
	JSR delay
	
	; 3rd Blink
	LDA #%00001111
	STA DATA_PORT	
	JSR delay
	
	LDA #%00000000
	STA DATA_PORT	
	JSR delay

	; 4th Blink
	LDA #%00001111
	STA DATA_PORT	
	JSR delay
	
	LDA #%00000000
	STA DATA_PORT	
	JSR delay

	; 5th Blink
	LDA #%00001111
	STA DATA_PORT	
	JSR delay
	
	LDA #%00000000
	STA DATA_PORT	
	JSR delay

	PUL	A

	RTS


