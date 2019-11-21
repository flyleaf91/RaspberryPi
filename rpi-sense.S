/*
 * rpi-sense.S - Atmel assembly routines for LED framebuffer scan-out
 *
 * Copyright (c) 2015 Raspberry Pi Foundation
 *
 * Author: Serge Schneider <serge@raspberrypi.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *	* Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the distribution.
 *	* Neither the name of Raspberry Pi nor the
 *	  names of its contributors may be used to endorse or promote products
 *	  derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <avr/io.h>
#include <util/twi.h>

/**
 * 1. 数据手册通用寄存器描述：《4.5 General Purpose Register File》
 * 2. 下面LINE/PARAM/PWM/I2C_OFF的值都是直接赋寄存器地址值，也就是后面直接用地址索引进行赋值；
 */
LINE	= 24
PARAM	= 24
PWM	= 25	;			// 0x3F (0x5F) SREG
I2C_OFF	= 26	; XL			// X-register Low Byte

.equiv I2C_WAI	, 0xf0
.equiv I2C_VER	, 0xf1
.equiv I2C_KEYS	, 0xf2
.equiv I2C_EE_WP, 0xf3
.equiv I2C_ID	, 's'
.equiv VERSION	, 0

; PORTB
.equiv EE_WP	, PB0					// EEPROM写保护引脚
.equiv KEYS_INT	, PB6					// 按键中断
.equiv FRAME_INT, PB7					// 帧中断

; PORTC
.equiv LED_SDO	, PC0					// LED2472G SDO
.equiv LED_CLKR	, PC1					// LED2472G CLK
.equiv LED_LE	, PC2					// Latch enable LED2472G
.equiv LED_SDI	, PC3					// LED2472G SDI
.equiv SDA	, PC4					// GPIO I2C SDA
.equiv SCL	, PC5					// GPIO I2C SCL
.equiv LED_OE_N	, PC7					// enable LED2472G R/G/B output

.macro CLOCK_OUT
	SBI	_SFR_IO_ADDR(PORTC), LED_CLKR		// set LED2472G CLK to 1, low to high
	CBI	_SFR_IO_ADDR(PORTC), LED_CLKR		// clear LED2472G CLK to 0, high to low
.endm

.macro COL_OUT reg
	CP	PWM, \reg				// compare PWM register and \reg
	BRSH	lclear\reg				// if same or high, then jump to lclear\reg
	SBI	_SFR_IO_ADDR(PORTC), LED_SDI		// set LED2472G data bit 1
	RJMP	ldone\reg				// jump to ldone\reg
lclear\reg:
	CBI	_SFR_IO_ADDR(PORTC), LED_SDI		// clear LED2472G data bit 0
ldone\reg:
	CLOCK_OUT					// set LED2472G CLK, make data valid
.endm

.global draw_loop
.global delay
.global read_data
.global write_data
.global TWI_vect

.extern pixels
.extern id
.extern key
.extern i2c_reg

.section .text
.func draw_loop
draw_loop:
Lframe_loop:
	CBI	_SFR_IO_ADDR(PORTC), FRAME_INT		// set FRAME_INT to 0, tell raspberry pi start a frame
	LDI	YL, lo8(pixels)				// get pixels address lower byte
	LDI	YH, hi8(pixels)				// get pixels address higher byte
	LDI	LINE, 0xFE				// columns enable
Lline_loop:
	OUT	_SFR_IO_ADDR(PORTD), LINE
	LDI	PWM, 0
	// 0 ~ 23 = 24 bit
	LD	r0, Y+					// +: automatically incremented after the load or store operation
	LD	r1, Y+
	LD	r2, Y+
	LD	r3, Y+
	LD	r4, Y+
	LD	r5, Y+
	LD	r6, Y+
	LD	r7, Y+
	LD	r8, Y+
	LD	r9, Y+
	LD	r10, Y+
	LD	r11, Y+
	LD	r12, Y+
	LD	r13, Y+
	LD	r14, Y+
	LD	r15, Y+
	LD	r16, Y+
	LD	r17, Y+
	LD	r18, Y+
	LD	r19, Y+
	LD	r20, Y+
	LD	r21, Y+
	LD	r22, Y+
	LD	r23, Y+
Lpwm_loop:
	// 输出SDI 24bit数据
	COL_OUT	r0
	COL_OUT	r1
	COL_OUT	r2
	COL_OUT	r3
	COL_OUT	r4
	COL_OUT	r5
	COL_OUT	r6
	COL_OUT	r7
	COL_OUT	r8
	COL_OUT	r9
	COL_OUT	r10
	COL_OUT	r11
	COL_OUT	r12
	COL_OUT	r13
	COL_OUT	r14
	COL_OUT	r15
	COL_OUT	r16
	COL_OUT	r17
	COL_OUT	r18
	COL_OUT	r19
	COL_OUT	r20
	COL_OUT	r21
	SBI	_SFR_IO_ADDR(PORTC), LED_LE			// data保持，2个bit的LE时间
	COL_OUT	r22
	COL_OUT	r23
	CBI	_SFR_IO_ADDR(PORTC), LED_LE
	INC	PWM						// 0b100000 = 32 = 0x20
	SBRS	PWM, 6						// 如果第6 bit是1，那么忽略下一条指令
	RJMP	Lpwm_loop					// 如上解释，跳转到Lpwm_loop
	ROL	LINE						// 逻辑右移
	BRCC	lframeend					// 8 bit循环到了，一帧结束
	INC	LINE						// 前面已经是ROL LINE了，这里没搞懂为什么要+1
	RJMP	Lline_loop
lframeend:
	SBI	_SFR_IO_ADDR(PORTB), FRAME_INT			// 结束帧中断
	CBI	_SFR_IO_ADDR(PORTD), 7		; Clear PORTD   // PORTD的低3位在案件检测中用不到，清零
	SBI	_SFR_IO_ADDR(PORTB), LED_OE_N	; Scan		// 关闭LED2472G R/G/B输出
	LDI	PARAM, 0xF8
	OUT	_SFR_IO_ADDR(PORTD), PARAM
	COM	PARAM						// 补码
	; OUT	_SFR_IO_ADDR(DDRD), PARAM
	LDS	PWM, keys					// 将keys中的数据暂存到PWM中
	IN	PARAM, _SFR_IO_ADDR(PIND)			// 获取PORTD的值
	COM	PARAM						// 补码
	LSR	PARAM						// 逻辑右移3位
	LSR	PARAM
	LSR	PARAM
	STS	keys, PARAM					// 将当前的按键数据存储到keys中
	CPSE	PARAM, PWM					// 比较当前的按键状态和上一次的按键状态
	SBI     _SFR_IO_ADDR(PORTB), KEYS_INT			// 设置中断引脚
	LDI	PARAM, 0xFF
	; OUT	_SFR_IO_ADDR(DDRD), PARAM			// 按键检测结束
	COM	PARAM						// PARM值取反
	OUT	_SFR_IO_ADDR(PORTD), PARAM			// PORTD = 0x00
	CBI	_SFR_IO_ADDR(PORTB), LED_OE_N	; /Scan		// 使能LED2472G R/G/B输出
	RJMP	Lframe_loop
	RET							// 返回调用
.endfunc

.func delay
delay:
	PUSH	r19								// 入栈R19
	PUSH	r20								// 入栈R20
	IN	r20, _SFR_IO_ADDR(TCNT0)	; start = TCNT0;		// 保存延时初始计数器值到R20
lloop:
	IN	r19, _SFR_IO_ADDR(TCNT0)	; do {				// 读取当前计数器到R19
	SUB	r19, r20			; diff = TCNT0 - start;		// R19 - R20 -> R19
	CP	r19, LINE			; } while (diff < ticks);	// compare R19 R24
	BRLO	lloop								// Branch if Lower (Unsigned), 小于就跳转到lloop
	POP	r20								// 大于等于出栈R20
	POP	r19								// 出栈R19
	RET									// 返回调用
 .endfunc

.func write_data
; r20-23 DATA
; r24 TYPE
write_data:
	PUSH	r18											// 入栈R18
	;PUSH	r20
	PUSH	r21											// 入栈R21
	PUSH	r22											// 入栈R22
	PUSH	r23											// 入栈R23
	PUSH	r24											// 入栈R24
	LDI	r18, 24	;										// R18赋值24
1:						; do {
	SBRS	r23, 0				; 	if (data&1)					// if R23第0 bit是1，忽略下一条指令
	RJMP	2f
	SBI	_SFR_IO_ADDR(PORTC), LED_SDI	; 		set LED_SDI;				// 设置LED2472G SDI引脚为1
	RJMP	3f
2:						; 	else
	CBI	_SFR_IO_ADDR(PORTC), LED_SDI	;		clr LED_SDI;				// 设置LED2472G SDI引脚为0
3:
	ASR	r23				; 	data <<= 1;					// R23左移一位
	ROR	r22											// R22
	ROR	r21											// R21
	;ROR	r20								; Don't need?
	CP	r24, r18			; 	if (type == i)					// R24和R18比较
	BRNE	4f											// 如果不相等就跳转
	SBI	_SFR_IO_ADDR(PORTC), LED_LE	; 		set LDE_LE;				// 如果相等就是使能LE，也就是锁存当前数据
4:
	CLOCK_OUT											// LED2472G的CLOCK引脚处理一下
	DEC	r18				; 	i--;						// R18 - 1 -> R18
	BRNE	1b				; } while (i!=0);
	CBI	_SFR_IO_ADDR(PORTC), LED_LE	; 		clr LDE_LE				// 清LE
	POP	r24											// 出栈R24
	POP	r23											// 出栈R23
	POP	r22											// 出栈R22
	POP	r21											// 出栈R21
	;POP	r20
	POP	r18											// 出栈R18
	RET
.endfunc

.func read_data
; r22-25 RETURN
; r24 TYPE
read_data:
	PUSH	r18
	PUSH	r19
	;PUSH	r20
	PUSH	r21
	PUSH	r22
	PUSH	r23
	PUSH	r24
	LDI	r18, 24	;
1:						; do {
	IN	r19, _SFR_IO_ADDR(PORTC)	; ret |= PINC&1;
	ANDI	r19, LED_SDI


	SBRS	r23, 0				; 	if (data&1)
	RJMP	2f
	SBI	_SFR_IO_ADDR(PORTC), LED_SDI	; 		set LED_SDI;
	RJMP	3f
2:						; 	else
	CBI	_SFR_IO_ADDR(PORTC), LED_SDI	;		clr LED_SDI;
3:
	ASR	r23				; 	data <<= 1;
	ROR	r22
	ROR	r21
	;ROR	r20								; Don't need?


	CP	r24, r18			; 	if (type == i)
	BRNE	4f
	SBI	_SFR_IO_ADDR(PORTC), LED_LE	; 		set LDE_LE;
4:
	CLOCK_OUT
	DEC	r18				; 	i--;
	BRNE	1b				; } while (i!=0);
	CBI	_SFR_IO_ADDR(PORTC), LED_LE	; 		clr LDE_LE
	POP	r24
	POP	r23
	POP	r22
	POP	r21
	;POP	r20
	POP	r19
	POP	r18
	RET
.endfunc

;TODO: Add reads and NACK bad addresses.
;PARAM (r24) - TWSR
;PWM (r25) - SREG
;DI2C/XL (r26) - Address
;Table 15-4. Status Codes for Slave Receiver Mode
;Table 15-5. Status Codes for Slave Transmitter Mode
;
;|address+W|offset|data...|
;|TW_SR_SLA_ACK|TW_SR_DATA_ACK|TW_SR_DATA_ACK...|
;|address+W|offset|address+R|data...|
;|TW_SR_SLA_ACK|TW_SR_DATA_ACK|TW_ST_SLA_ACK|TW_ST_DATA_ACK...|
.func TWI_vect
TWI_vect:
	PUSH	PARAM
	PUSH	PWM
	PUSH	YL
	PUSH	YH
	PUSH	I2C_OFF
	IN	PWM, _SFR_IO_ADDR(SREG)								// SREG – Status Register，// 将SREG写入PWM
	LDS	PARAM, TWSR									// Two Wire Interface(TWI) Status Register
	ANDI	PARAM, 0xF8									// 和立即数逻辑与，Bits 7:3 – TWS: TWI Status
	LDS	I2C_OFF, i2c_reg								// Load Direct from data space
	CPI	PARAM, TW_ST_SLA_ACK		; Slave Receive ACK Address			// SLA+R received, ACK returned
	BREQ	ltsend										// 地址匹配正常并且收到读操作处理跳转
	CPI	PARAM, TW_SR_DATA_ACK		; Slave Receive Data				// data received, ACK returned
	BREQ	lreceive									// 收到一个字节数据，并且已经给master反馈了ACK之后的处理跳转
	CPI	PARAM, TW_SR_SLA_ACK		; Slave Receive ACK Address			// SLA+W received, ACK returned
	BREQ	lrack										// 地址匹配正常并且收到写操作处理跳转
	CPI	PARAM, TW_ST_DATA_ACK		; Slave Transmit Data				// data transmitted, ACK received
	BREQ	ltsend										//
	CPI	PARAM, TW_ST_DATA_NACK								// data transmitted, NACK received
	BREQ	ltdnack
	LDI	PARAM,  (1<<TWEA) | (1<<TWEN) | (1<<TWIE) | (1<<TWINT) ;ELSE			// 清除中断标志
	RJMP	ldone
lreceive:
	LDS	PARAM, TWDR			; Data						// 收到数据，第一次应该是应该是给i2c_reg
	CPI	I2C_OFF, 193			; if address<=192				// 根据前面设置的i2c_reg，来设置pixels
	BRLO	lrspixel
	CPI	I2C_OFF, 0xff			; if address==0xff				// 设置i2c_reg
	BREQ	lrsreg
	CPI	I2C_OFF, I2C_EE_WP								// 这里是修改EEPROM写保护引脚
	BREQ	lree
	; NACK here
	RJMP	lrdone				; else...
lree:
	SBI	_SFR_IO_ADDR(PORTB), EE_WP							// 将EEPROM写保护引脚置1
	CPSE	PARAM, 0									// 如果相等，就忽略下一条指令
	CBI	_SFR_IO_ADDR(PORTB), EE_WP							// 将EEPROM写保护引脚置0
	RJMP	lrdone
lrsreg:
	STS	i2c_reg, PARAM			; address = DATA				// 将当前的偏移数据存放在i2c_reg中
	RJMP	lrdone
lrspixel:
	LDI	YL, lo8(pixels)									// 获取pixels的低位基地址
	LDI	YH, hi8(pixels)									// 获取pixels的高位基地址
	ADD	YL, I2C_OFF									// 基地址+偏移得到实际地址
	INC	I2C_OFF										// 偏移自加1，实现连续存储的时候地址和数据一一对应
	STS	i2c_reg, I2C_OFF								// 存储当前的偏移，如果是连续传数据的话，实现连续数据偏移得以保存
	CLR	I2C_OFF										// 这条指令和下一条指令组合处理前面加法可能产生的进位
	ADC	YH, I2C_OFF
	ST	Y, PARAM									// 将当前数据存储到需要修改的地址空间中
lrdone:
	LDI	PARAM,  (1<<TWEA) | (1<<TWEN) | (1<<TWIE) | (1<<TWINT)
ldone:
	STS	TWCR, PARAM									// 清中断
	OUT	_SFR_IO_ADDR(SREG), PWM								// 将PWM写入SREG
	POP	I2C_OFF
	POP	YH
	POP	YL
	POP	PWM
	POP	PARAM
	RETI
lrack:												// 收到写寄存器地址，先复位i2c_reg寄存器的值
	LDI	PARAM, 0xff		; Address = 0xff					// 这里特别需要注意，接下来接受的第一个字节的时候i2c_reg是0xff，正好配合lreceive中的0xff判断
	STS	i2c_reg, PARAM
	LDI	PARAM,  (1<<TWEA) | (1<<TWEN) | (1<<TWIE) | (1<<TWINT)
	RJMP	ldone
ltdnack:
	RJMP	ltdone
ltsend:												// 根据当前的I2C_OFF，也就是i2c_reg来确定处理哪个跳转分支
	CPI     I2C_OFF, 193                    ; if address<=192
        BRLO    ltspixel									// 获取pixels内容
        CPI     I2C_OFF, I2C_KEYS
        BREQ    ltskeys										// 获取按键值
        CPI     I2C_OFF, I2C_WAI                ; if address==I2C_WAI
        BREQ    ltswai										// 获取设备ID
        CPI     I2C_OFF, I2C_EE_WP
        BREQ    ltsee										// 获取EEPROM保护位状态
	CPI     I2C_OFF, I2C_VER
        BREQ    ltsver										// 获取软件版本
	LDI	PARAM, 0xff									// 其他的返回0xff
	STS	TWDR, PARAM
	RJMP	ltdone
ltswai:
        LDI     PARAM, I2C_ID
        STS     TWDR, PARAM
        RJMP    ltdone
ltsver:
        LDI     PARAM, VERSION
        STS     TWDR, PARAM
        RJMP    ltdone
ltskeys:
        CBI     _SFR_IO_ADDR(PORTB), KEYS_INT
        LDS	PARAM, keys
        STS     TWDR, PARAM
	RJMP    ltdone
ltsee:
        LDI     PARAM, 0
        SBIS    _SFR_IO_ADDR(PORTB), EE_WP
        LDI     PARAM, 1
        STS     TWDR, PARAM
        RJMP    ltdone
ltspixel:
        LDI     YL, lo8(pixels)									// 获取pixels的低位基地址
        LDI     YH, hi8(pixels)									// 获取pixels的高位基地址
        ADD     YL, I2C_OFF									// 低位基地址+偏移
        INC     I2C_OFF										// 偏移+1
        STS     i2c_reg, I2C_OFF								// 保存偏移
        CLR     I2C_OFF										// 清零偏移
        ADC     YH, I2C_OFF									// 处理前面可能的带进位加法
        LD      I2C_OFF, Y									// 将数据取出
        STS     TWDR, I2C_OFF									// 将数据写入TWDR
ltdone:
	LDI	PARAM,  (1<<TWEA) | (1<<TWEN) | (1<<TWIE) | (1<<TWINT)
	RJMP	ldone
.endfunc
