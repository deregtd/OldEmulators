	.586p
	model flat
	ifndef	??version
	?debug	macro
	endm
	endif
	?debug	S "6502.cpp"
	?debug	T "6502.cpp"
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
_DATA	segment dword public use32 'DATA'
_DATA	ends
_BSS	segment dword public use32 'BSS'
_BSS	ends
DGROUP	group	_BSS,_DATA
_DATA	segment dword public use32 'DATA'
_addressmode	label	byte
	db	3
	db	9
	db	13
	db	13
	db	3
	db	2
	db	2
	db	13
	db	3
	db	0
	db	3
	db	13
	db	13
	db	1
	db	1
	db	13
	db	11
	db	10
	db	13
	db	13
	db	13
	db	7
	db	7
	db	13
	db	3
	db	6
	db	3
	db	13
	db	13
	db	5
	db	5
	db	13
	db	1
	db	9
	db	13
	db	13
	db	2
	db	2
	db	2
	db	13
	db	3
	db	0
	db	3
	db	13
	db	1
	db	1
	db	1
	db	13
	db	11
	db	10
	db	13
	db	13
	db	13
	db	7
	db	7
	db	13
	db	3
	db	6
	db	13
	db	13
	db	13
	db	5
	db	5
	db	13
	db	3
	db	9
	db	13
	db	13
	db	13
	db	2
	db	2
	db	13
	db	3
	db	0
	db	3
	db	13
	db	1
	db	1
	db	1
	db	13
	db	11
	db	10
	db	13
	db	13
	db	3
	db	7
	db	7
	db	13
	db	3
	db	6
	db	13
	db	13
	db	13
	db	5
	db	5
	db	13
	db	3
	db	9
	db	13
	db	13
	db	13
	db	2
	db	2
	db	13
	db	3
	db	0
	db	3
	db	13
	db	4
	db	1
	db	1
	db	13
	db	11
	db	10
	db	13
	db	13
	db	13
	db	7
	db	7
	db	13
	db	3
	db	6
	db	13
	db	13
	db	13
	db	5
	db	5
	db	13
	db	13
	db	9
	db	13
	db	13
	db	2
	db	2
	db	2
	db	13
	db	3
	db	0
	db	3
	db	13
	db	1
	db	1
	db	1
	db	13
	db	11
	db	10
	db	13
	db	13
	db	7
	db	7
	db	8
	db	13
	db	3
	db	6
	db	3
	db	13
	db	13
	db	5
	db	13
	db	13
	db	0
	db	9
	db	0
	db	13
	db	2
	db	2
	db	2
	db	13
	db	3
	db	0
	db	3
	db	13
	db	1
	db	1
	db	1
	db	13
	db	11
	db	10
	db	13
	db	13
	db	7
	db	7
	db	8
	db	13
	db	3
	db	6
	db	3
	db	13
	db	5
	db	5
	db	6
	db	13
	db	0
	db	9
	db	13
	db	13
	db	2
	db	2
	db	2
	db	13
	db	3
	db	0
	db	3
	db	13
	db	1
	db	1
	db	1
	db	13
	db	11
	db	10
	db	13
	db	13
	db	13
	db	7
	db	7
	db	13
	db	3
	db	6
	db	13
	db	13
	db	13
	db	5
	db	5
	db	13
	db	0
	db	9
	db	13
	db	13
	db	2
	db	2
	db	2
	db	13
	db	3
	db	0
	db	3
	db	13
	db	1
	db	1
	db	1
	db	13
	db	11
	db	10
	db	13
	db	13
	db	13
	db	7
	db	7
	db	13
	db	3
	db	6
	db	13
	db	13
	db	13
	db	5
	db	5
	db	13
_instruc	label	byte
	db	10
	db	34
	db	60
	db	60
	db	60
	db	34
	db	2
	db	60
	db	36
	db	34
	db	56
	db	60
	db	60
	db	34
	db	2
	db	60
	db	9
	db	34
	db	60
	db	60
	db	60
	db	34
	db	2
	db	60
	db	13
	db	34
	db	60
	db	60
	db	60
	db	34
	db	2
	db	60
	db	28
	db	1
	db	60
	db	60
	db	6
	db	1
	db	39
	db	60
	db	38
	db	1
	db	58
	db	60
	db	6
	db	1
	db	39
	db	60
	db	7
	db	1
	db	60
	db	60
	db	60
	db	1
	db	39
	db	60
	db	44
	db	1
	db	60
	db	60
	db	60
	db	1
	db	39
	db	60
	db	41
	db	23
	db	60
	db	60
	db	60
	db	23
	db	32
	db	60
	db	35
	db	23
	db	57
	db	60
	db	27
	db	23
	db	32
	db	60
	db	11
	db	23
	db	60
	db	60
	db	60
	db	23
	db	32
	db	60
	db	15
	db	23
	db	60
	db	60
	db	60
	db	23
	db	32
	db	60
	db	42
	db	0
	db	60
	db	60
	db	60
	db	0
	db	40
	db	60
	db	37
	db	0
	db	59
	db	60
	db	27
	db	0
	db	40
	db	60
	db	12
	db	0
	db	60
	db	60
	db	60
	db	0
	db	40
	db	60
	db	46
	db	0
	db	60
	db	60
	db	60
	db	0
	db	40
	db	60
	db	60
	db	47
	db	60
	db	60
	db	49
	db	47
	db	48
	db	60
	db	22
	db	47
	db	53
	db	60
	db	49
	db	47
	db	48
	db	60
	db	3
	db	47
	db	60
	db	60
	db	49
	db	47
	db	48
	db	60
	db	55
	db	47
	db	54
	db	60
	db	60
	db	47
	db	60
	db	60
	db	31
	db	29
	db	30
	db	60
	db	31
	db	29
	db	30
	db	60
	db	51
	db	29
	db	50
	db	60
	db	31
	db	29
	db	30
	db	60
	db	4
	db	29
	db	60
	db	60
	db	31
	db	29
	db	30
	db	60
	db	16
	db	29
	db	52
	db	60
	db	31
	db	29
	db	30
	db	60
	db	19
	db	17
	db	60
	db	60
	db	19
	db	17
	db	20
	db	60
	db	26
	db	17
	db	21
	db	60
	db	19
	db	17
	db	20
	db	60
	db	8
	db	17
	db	60
	db	60
	db	60
	db	17
	db	20
	db	60
	db	14
	db	17
	db	60
	db	60
	db	60
	db	17
	db	20
	db	60
	db	18
	db	43
	db	60
	db	60
	db	18
	db	43
	db	24
	db	60
	db	25
	db	43
	db	33
	db	60
	db	18
	db	43
	db	24
	db	60
	db	5
	db	43
	db	60
	db	60
	db	60
	db	43
	db	24
	db	60
	db	45
	db	43
	db	60
	db	60
	db	60
	db	43
	db	24
	db	60
_ticks	label	byte
	db	7
	db	6
	db	0
	db	0
	db	2
	db	3
	db	5
	db	0
	db	3
	db	2
	db	2
	db	0
	db	0
	db	4
	db	6
	db	0
	db	3
	db	5
	db	0
	db	0
	db	0
	db	4
	db	6
	db	0
	db	2
	db	4
	db	2
	db	0
	db	0
	db	4
	db	7
	db	0
	db	6
	db	6
	db	0
	db	0
	db	3
	db	3
	db	5
	db	0
	db	4
	db	2
	db	2
	db	0
	db	4
	db	4
	db	6
	db	0
	db	3
	db	5
	db	0
	db	0
	db	0
	db	4
	db	6
	db	0
	db	2
	db	4
	db	2
	db	0
	db	0
	db	4
	db	7
	db	0
	db	6
	db	6
	db	0
	db	0
	db	0
	db	3
	db	5
	db	0
	db	3
	db	2
	db	2
	db	0
	db	3
	db	4
	db	6
	db	0
	db	3
	db	5
	db	0
	db	0
	db	0
	db	4
	db	6
	db	0
	db	2
	db	4
	db	0
	db	0
	db	0
	db	4
	db	7
	db	0
	db	6
	db	6
	db	0
	db	0
	db	0
	db	3
	db	5
	db	0
	db	4
	db	2
	db	2
	db	0
	db	5
	db	4
	db	6
	db	0
	db	3
	db	5
	db	0
	db	0
	db	0
	db	4
	db	6
	db	0
	db	2
	db	4
	db	0
	db	0
	db	0
	db	4
	db	7
	db	0
	db	0
	db	6
	db	0
	db	0
	db	3
	db	3
	db	3
	db	0
	db	2
	db	2
	db	2
	db	0
	db	4
	db	4
	db	4
	db	0
	db	3
	db	5
	db	0
	db	0
	db	4
	db	4
	db	4
	db	0
	db	2
	db	4
	db	2
	db	0
	db	0
	db	4
	db	0
	db	0
	db	2
	db	6
	db	2
	db	0
	db	3
	db	3
	db	3
	db	0
	db	2
	db	2
	db	2
	db	0
	db	4
	db	4
	db	4
	db	0
	db	3
	db	5
	db	0
	db	0
	db	4
	db	4
	db	4
	db	0
	db	2
	db	4
	db	2
	db	0
	db	4
	db	4
	db	4
	db	0
	db	2
	db	6
	db	0
	db	0
	db	3
	db	3
	db	5
	db	0
	db	2
	db	2
	db	2
	db	0
	db	4
	db	4
	db	6
	db	0
	db	3
	db	5
	db	0
	db	0
	db	0
	db	4
	db	6
	db	0
	db	2
	db	4
	db	0
	db	0
	db	0
	db	4
	db	7
	db	0
	db	2
	db	6
	db	0
	db	0
	db	3
	db	3
	db	5
	db	0
	db	2
	db	2
	db	2
	db	0
	db	4
	db	4
	db	6
	db	0
	db	3
	db	5
	db	0
	db	0
	db	0
	db	4
	db	6
	db	0
	db	2
	db	4
	db	0
	db	0
	db	0
	db	4
	db	7
	db	0
_bytes	label	byte
	db	1
	db	2
	db	1
	db	1
	db	1
	db	2
	db	2
	db	1
	db	1
	db	2
	db	1
	db	1
	db	1
	db	3
	db	3
	db	1
	db	2
	db	2
	db	1
	db	1
	db	1
	db	2
	db	2
	db	1
	db	1
	db	3
	db	1
	db	1
	db	1
	db	3
	db	3
	db	1
	db	3
	db	2
	db	1
	db	1
	db	2
	db	2
	db	2
	db	1
	db	1
	db	2
	db	1
	db	1
	db	3
	db	3
	db	3
	db	1
	db	2
	db	2
	db	1
	db	1
	db	1
	db	2
	db	2
	db	1
	db	1
	db	3
	db	1
	db	1
	db	1
	db	3
	db	3
	db	1
	db	1
	db	2
	db	1
	db	1
	db	1
	db	2
	db	2
	db	1
	db	1
	db	2
	db	1
	db	1
	db	3
	db	3
	db	3
	db	1
	db	2
	db	2
	db	1
	db	1
	db	1
	db	2
	db	2
	db	1
	db	1
	db	3
	db	1
	db	1
	db	1
	db	3
	db	3
	db	1
	db	1
	db	2
	db	1
	db	1
	db	1
	db	2
	db	2
	db	1
	db	1
	db	2
	db	1
	db	1
	db	3
	db	3
	db	3
	db	1
	db	2
	db	2
	db	1
	db	1
	db	1
	db	2
	db	2
	db	1
	db	1
	db	3
	db	1
	db	1
	db	1
	db	3
	db	3
	db	1
	db	1
	db	2
	db	1
	db	1
	db	2
	db	2
	db	2
	db	1
	db	1
	db	2
	db	1
	db	1
	db	3
	db	3
	db	3
	db	1
	db	2
	db	2
	db	1
	db	1
	db	2
	db	2
	db	2
	db	1
	db	1
	db	3
	db	1
	db	1
	db	1
	db	3
	db	1
	db	1
	db	2
	db	2
	db	2
	db	1
	db	2
	db	2
	db	2
	db	1
	db	1
	db	2
	db	1
	db	1
	db	3
	db	3
	db	3
	db	1
	db	2
	db	2
	db	1
	db	1
	db	2
	db	2
	db	2
	db	1
	db	1
	db	3
	db	1
	db	1
	db	3
	db	3
	db	3
	db	1
	db	2
	db	2
	db	1
	db	1
	db	2
	db	2
	db	2
	db	1
	db	1
	db	2
	db	1
	db	1
	db	3
	db	3
	db	3
	db	1
	db	2
	db	2
	db	1
	db	1
	db	1
	db	2
	db	2
	db	1
	db	1
	db	3
	db	1
	db	1
	db	1
	db	3
	db	3
	db	1
	db	2
	db	2
	db	1
	db	1
	db	2
	db	2
	db	2
	db	1
	db	1
	db	2
	db	1
	db	1
	db	3
	db	3
	db	3
	db	1
	db	2
	db	2
	db	1
	db	1
	db	1
	db	2
	db	2
	db	1
	db	1
	db	3
	db	1
	db	1
	db	1
	db	3
	db	3
	db	1
	align	4
_Mn	label	byte
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	align	4
_RegInfoLow	label	byte
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	align	4
_RegInfoHigh	label	byte
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	align	4
_MapperInfo	label	byte
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
	db	4	dup(?)
_DATA	ends
_BSS	segment dword public use32 'BSS'
_tmp	label	byte
	db	1	dup(?)
_tmpBYTE	label	byte
	db	1	dup(?)
	align	2
_tmpLBYTE	label	word
	db	2	dup(?)
	align	2
_tmpshortint	label	word
	db	2	dup(?)
_tmpbool	label	byte
	db	1	dup(?)
_DebuggingTrace	label	byte
	db	1	dup(?)
_DebuggingRegs	label	byte
	db	1	dup(?)
_HaltOnNMI	label	byte
	db	1	dup(?)
_HaltOnBadOp	label	byte
	db	1	dup(?)
_tmpframes	label	byte
	db	1	dup(?)
	align	4
_GGCodeNum	label	dword
	db	4	dup(?)
	align	2
_GGCode	label	byte
	db	300	dup(?)
_A	label	byte
	db	1	dup(?)
_X	label	byte
	db	1	dup(?)
_Y	label	byte
	db	1	dup(?)
_SP	label	byte
	db	1	dup(?)
	align	4
_PC	label	dword
	db	4	dup(?)
	align	4
_TU	label	dword
	db	4	dup(?)
_ClockticksSm	label	byte
	db	1	dup(?)
_TU2	label	byte
	db	1	dup(?)
_NMIonVBlank	label	byte
	db	1	dup(?)
_NMIonSprHit	label	byte
	db	1	dup(?)
_SSize	label	byte
	db	1	dup(?)
_BkPTA	label	byte
	db	1	dup(?)
_SpPTA	label	byte
	db	1	dup(?)
_PPUAdrI	label	byte
	db	1	dup(?)
_SprVis	label	byte
	db	1	dup(?)
_BGVis	label	byte
	db	1	dup(?)
_SprClip	label	byte
	db	1	dup(?)
_BGClip	label	byte
	db	1	dup(?)
_DispType	label	byte
	db	1	dup(?)
_VBlankOcc	label	byte
	db	1	dup(?)
_Spr0Occ	label	byte
	db	1	dup(?)
_ScLnSprCnt	label	byte
	db	1	dup(?)
_VRAMWrFlg	label	byte
	db	1	dup(?)
_VFirstRead	label	byte
	db	1	dup(?)
_SFirstRead	label	byte
	db	1	dup(?)
_CPURunning	label	byte
	db	1	dup(?)
_TUMode	label	byte
	db	1	dup(?)
_BSS	ends
_DATA	segment dword public use32 'DATA'
	align	2
_NTabAdr	label	word
	dw	8192
_DATA	ends
_BSS	segment dword public use32 'BSS'
_SpecialAccessR	label	byte
	db	65535	dup(?)
_SpecialAccessW	label	byte
	db	65535	dup(?)
_BSS	ends
_DATA	segment dword public use32 'DATA'
_P	label	byte
	db	32
_DATA	ends
_BSS	segment dword public use32 'BSS'
	align	4
_Mem	label	byte
	db	1964676	dup(?)
_PALMode	label	byte
	db	1	dup(?)
	align	2
_LineRate	label	word
	db	2	dup(?)
	align	2
_LineTotal	label	word
	db	2	dup(?)
	align	2
_ScanLine	label	word
	db	2	dup(?)
	align	2
_VBScanLine	label	word
	db	2	dup(?)
	align	2
_MaxScanLine	label	word
	db	2	dup(?)
	align	2
_MHBValue	label	word
	db	2	dup(?)
	align	2
_ScanLineFake	label	word
	db	2	dup(?)
_LineTicksInt	label	byte
	db	1	dup(?)
	align	4
_CPUSpeed	label	dword
	db	4	dup(?)
_VBlanking	label	byte
	db	1	dup(?)
_FakeSLUsing	label	byte
	db	1	dup(?)
	align	4
_VBSec	label	dword
	db	4	dup(?)
	align	2
_YMax	label	word
	db	2	dup(?)
	align	2
_Joy	label	byte
	db	64	dup(?)
	align	4
_PulseChan	label	byte
	db	32	dup(?)
	align	2
_TriChan	label	byte
	db	4	dup(?)
_NoiseChan	label	byte
	db	1	dup(?)
	align	4
_DCMChan	label	byte
	db	4220	dup(?)
	align	4
_SRAMFileWr	label	dword
	db	4	dup(?)
	align	4
_SRAMFileRd	label	dword
	db	4	dup(?)
_ROMTrainer	label	byte
	db	1	dup(?)
_MMC1	label	byte
	db	10	dup(?)
_MMC3	label	byte
	db	6	dup(?)
_M22in1	label	byte
	db	2	dup(?)
	align	2
_M16	label	byte
	db	4	dup(?)
	align	2
_M17	label	byte
	db	4	dup(?)
_M90	label	byte
	db	5	dup(?)
_M24	label	byte
	db	4	dup(?)
	align	4
_LastClockVal	label	byte
	db	8	dup(?)
_BSS	ends
_TEXT	segment dword public use32 'CODE'
	align	4
@NewCPUMode$qs	proc	near
?live1@0:
@1:
	push      ebp
	mov       ebp,esp
	push      ecx
	mov       eax,dword ptr [ebp+8]
?live1@16: ; EAX = NTSCMode
	test      ax,ax
	sete      dl
	and       edx,1
	mov       byte ptr [_PALMode],dl
	cmp       ax,1
	jne       short @2
?live1@48: ; 
	mov       dword ptr [_CPUSpeed],1239054948
	mov       dword ptr [_VBSec],60
	mov       word ptr [_YMax],224
	mov       word ptr [_LineRate],15720
	mov       word ptr [_VBScanLine],240
	mov       word ptr [_MaxScanLine],262
	jmp       short @3
@2:
	test      ax,ax
	jne       short @4
	mov       dword ptr [_CPUSpeed],1238924347
	mov       dword ptr [_VBSec],50
	mov       word ptr [_YMax],240
	mov       word ptr [_LineRate],15600
	mov       word ptr [_VBScanLine],240
	mov       word ptr [_MaxScanLine],312
@4:
@3:
	movsx     eax,word ptr [_LineRate]
	mov       dword ptr [ebp-4],eax
	fild      dword ptr [ebp-4]
	fdivr     dword ptr [_CPUSpeed]
	call      __ftol
	mov       byte ptr [_LineTicksInt],al
	mov       eax,dword ptr [_VBSec]
	cdq
	push      edx
	push      eax
	mov       eax,dword ptr [_ClockFreq]
	mov       edx,dword ptr [_ClockFreq+4]
	call      __lldiv
	mov       dword ptr [_ClockFreqVblank],eax
@5:
	pop       ecx
	pop       ebp
	ret 
@NewCPUMode$qs	endp
	align	4
@Setup$qp11Forms@TForm7tagRECTp14Stdctrls@TMemot3	proc	near
?live1@304:
@6:
	push      ebp
	mov       ebp,esp
	push      esi
	mov       esi,dword ptr [ebp+8]
?live1@320: ; ESI = tf
	mov       byte ptr [_Joy+55],-84
	mov       eax,offset _Joy
	call      @@JoypadSt@UpdateSig$qqrv
	mov       byte ptr [_DebuggingTrace],0
	mov       byte ptr [_DebuggingRegs],0
	mov       eax,offset _Mem
	call      @@MemSt@SetupPointers$qqrv
@7:
	xor       ecx,ecx
	mov       edx,offset _SpecialAccessW
	mov       eax,offset _SpecialAccessR
?live1@416: ; EAX = @temp0, EDX = @temp1, ECX = i, ESI = tf
@8:
	mov       byte ptr [eax],0
	mov       byte ptr [edx],0
@10:
	inc       ecx
	inc       edx
	inc       eax
	cmp       ecx,65536
	jl        short @8
?live1@464: ; ESI = tf
@12:
	mov       ecx,8192
	mov       edx,offset _SpecialAccessW+8192
	mov       eax,offset _SpecialAccessR+8192
?live1@480: ; EAX = @temp2, EDX = @temp3, ECX = i, ESI = tf
@13:
	mov       byte ptr [eax],0
	mov       byte ptr [edx],1
@15:
	inc       ecx
	inc       edx
	inc       eax
	cmp       ecx,8200
	jl        short @13
?live1@528: ; ESI = tf
@17:
	mov       ecx,16384
	mov       edx,offset _SpecialAccessW+16384
	mov       eax,offset _SpecialAccessR+16384
?live1@544: ; EAX = @temp4, EDX = @temp5, ECX = i, ESI = tf
@18:
	mov       byte ptr [eax],0
	mov       byte ptr [edx],1
@20:
	inc       ecx
	inc       edx
	inc       eax
	cmp       ecx,16408
	jl        short @18
?live1@592: ; ESI = tf
	mov       byte ptr [_SpecialAccessR+8194],1
	mov       byte ptr [_SpecialAccessR+8196],1
	mov       byte ptr [_SpecialAccessR+8199],1
	mov       byte ptr [_SpecialAccessR+16405],1
	mov       byte ptr [_SpecialAccessR+16406],1
	mov       byte ptr [_SpecialAccessR+16407],1
	mov       byte ptr [_SpecialAccessW+8194],0
@22:
	mov       ecx,24576
	mov       edx,offset _SpecialAccessW+24576
	mov       eax,offset _SpecialAccessR+24576
?live1@720: ; EAX = @temp6, EDX = @temp7, ECX = i, ESI = tf
@23:
	mov       byte ptr [eax],1
	mov       byte ptr [edx],1
@25:
	inc       ecx
	inc       edx
	inc       eax
	cmp       ecx,32768
	jl        short @23
?live1@768: ; ESI = tf
@27:
	mov       ecx,32768
	mov       edx,offset _SpecialAccessW+32768
	mov       eax,offset _SpecialAccessR+32768
?live1@784: ; EAX = @temp8, EDX = @temp9, ECX = i, ESI = tf
@28:
	mov       byte ptr [eax],0
	mov       byte ptr [edx],1
@30:
	inc       ecx
	inc       edx
	inc       eax
	cmp       ecx,65536
	jl        short @28
?live1@832: ; ESI = tf
@32:
	mov       edx,17148
	mov       eax,offset _SpecialAccessW+17148
?live1@848: ; EAX = @temp10, EDX = i, ESI = tf
@33:
	mov       byte ptr [eax],1
@35:
	inc       edx
	inc       eax
	cmp       edx,17151
	jle       short @33
?live1@880: ; ESI = tf
@37:
	mov       edx,17665
	mov       eax,offset _SpecialAccessW+17665
?live1@896: ; EAX = @temp11, EDX = i, ESI = tf
@38:
	mov       byte ptr [eax],1
@40:
	inc       edx
	inc       eax
	cmp       edx,17671
	jle       short @38
?live1@928: ; ESI = tf
@42:
	mov       edx,17680
	mov       eax,offset _SpecialAccessW+17680
?live1@944: ; EAX = @temp12, EDX = i, ESI = tf
@43:
	mov       byte ptr [eax],1
@45:
	inc       edx
	inc       eax
	cmp       edx,17687
	jle       short @43
?live1@976: ; ESI = tf
	mov       edx,dword ptr [ebp+32]
	push      edx
	mov       ecx,dword ptr [ebp+28]
	push      ecx
	push      dword ptr [ebp+24]
	push      dword ptr [ebp+20]
	push      dword ptr [ebp+16]
	push      dword ptr [ebp+12]
	push      esi
	call      @VideoSetup$qp11Forms@TForm7tagRECTp14Stdctrls@TMemot3
	add       esp,28
	mov       eax,esi
	call      @AudioSetup$qqrp11Forms@TForm
?live1@1008: ; 
@47:
	pop       esi
	pop       ebp
	ret 
@Setup$qp11Forms@TForm7tagRECTp14Stdctrls@TMemot3	endp
	align	4
@Shutdown$qqrv	proc	near
?live1@1024:
@48:
	mov       byte ptr [_CPURunning],0
	cmp       byte ptr [_Mem+1964670],0
	je        short @49
	push      0
	push      0
	mov       eax,dword ptr [_SRAMFileWr]
	push      eax
	call      _fseek
	add       esp,12
	mov       edx,dword ptr [_SRAMFileWr]
	push      edx
	push      1
	push      8192
	mov       ecx,dword ptr [_Mem+98304]
	push      ecx
	call      _fwrite
	add       esp,16
	mov       eax,dword ptr [_SRAMFileRd]
	push      eax
	call      _fclose
	pop       ecx
	mov       edx,dword ptr [_SRAMFileWr]
	push      edx
	call      _fclose
	pop       ecx
@49:
	call      @VideoShutdown$qqrv
	call      @AudioShutdown$qqrv
@50:
	ret 
@Shutdown$qqrv	endp
	align	4
@exec6502$qqrv	proc	near
?live1@1152:
@51:
	jmp       @53
	jmp       @56
@55:
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        short @57
?live1@1184: ; EAX = @temp3
	mov       edx,eax
	and       eax,24576
	shr       eax,13
	and       edx,8191
	movsx     ecx,word ptr [_Mem+391766+2*eax]
	shl       ecx,13
	lea       eax,dword ptr [ecx+_Mem]
	mov       al,byte ptr [eax+edx+391806]
	jmp       short @58
?live1@1200: ; 
@57:
	mov       edx,dword ptr [_PC]
	mov       ecx,dword ptr [_Mem+4*edx]
	mov       al,byte ptr [ecx]
?live1@1216: ; EAX = opcode
@58:
	mov       edx,eax
	sub       dl,1
	jae       short @59
	or        byte ptr [_P],16
	xor       edx,edx
	mov       cx,word ptr [_PC]
	dec       ecx
	mov       word ptr [_tmpLBYTE],cx
	movzx     ecx,cx
	mov       dl,byte ptr [_SP]
	sar       ecx,8
	mov       byte ptr [edx+_Mem+264192],cl
	mov       cl,byte ptr [_tmpLBYTE]
	mov       byte ptr [edx+_Mem+264191],cl
	mov       cl,byte ptr [_P]
	mov       byte ptr [edx+_Mem+264190],cl
	xor       ecx,ecx
	sub       byte ptr [_SP],3
	or        byte ptr [_P],4
	movsx     edx,word ptr [_Mem+391772]
	shl       edx,13
	mov       cl,byte ptr [edx+_Mem+399997]
	movzx     edx,byte ptr [edx+_Mem+399996]
	shl       ecx,8
	or        cx,dx
	movzx     edx,cx
	mov       dword ptr [_PC],edx
@59:
@62:
	and       eax,255
	mov       cl,byte ptr [eax+_ticks]
	sub       byte ptr [_ClockticksSm],cl
?live1@1344: ; 
@56:
	mov       al,byte ptr [_ClockticksSm]
	test      al,al
	jg        @55
	call      @HBlank$qv
@53:
	mov       dl,byte ptr [_CPURunning]
	test      dl,dl
	jne       short @56
@63:
	ret 
@exec6502$qqrv	endp
	align	4
@run6502$qqrv	proc	near
?live1@1408:
@64:
	push      ebx
	push      esi
	jmp       @66
	jmp       short @69
@68:
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        short @70
?live1@1440: ; EAX = @temp3
	mov       edx,eax
	and       eax,24576
	shr       eax,13
	and       edx,8191
	movsx     ecx,word ptr [_Mem+391766+2*eax]
	shl       ecx,13
	lea       eax,dword ptr [ecx+_Mem]
	mov       bl,byte ptr [eax+edx+391806]
	jmp       short @71
?live1@1456: ; 
@70:
	mov       eax,dword ptr [_PC]
	mov       edx,dword ptr [_Mem+4*eax]
	mov       bl,byte ptr [edx]
?live1@1472: ; EBX = opcode
@71:
	mov       esi,ebx
	and       esi,255
	mov       al,byte ptr [esi+_addressmode]
	call      @Addrmode$qqruc
?live1@1488: ; EBX = opcode, ESI = @temp1
	xor       edx,edx
	mov       dl,byte ptr [esi+_bytes]
	add       dword ptr [_PC],edx
	mov       al,byte ptr [esi+_instruc]
	call      @ExecOp$qqruc
	mov       dl,byte ptr [esi+_ticks]
	sub       byte ptr [_ClockticksSm],dl
?live1@1536: ; 
@69:
	mov       cl,byte ptr [_ClockticksSm]
	test      cl,cl
	jg        @68
	call      @HBlank$qv
@66:
	mov       al,byte ptr [_CPURunning]
	test      al,al
	jne       short @69
@72:
	pop       esi
	pop       ebx
	ret 
@run6502$qqrv	endp
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@_$DCCB$@HBlank$qv	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-8
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-12
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-16
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-20
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-24
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-28
	dd	0
	align	4
@_$ECTDB$@HBlank$qv	label	dword
	dd	0
	dd	-64
	dw	0
	dw	5
	dd	0
	dd	@_$DCCB$@HBlank$qv
_DATA	ends
_TEXT	segment dword public use32 'CODE'
	align	4
@HBlank$qv	proc	near
?live1@1600:
@73:
	push      ebp
	mov       ebp,esp
	add       esp,-76
	mov       eax,offset @_$ECTDB$@HBlank$qv
	push      ebx
	push      esi
	push      edi
	call      @__InitExceptBlockLDTC
	inc       word ptr [_ScanLine]
	mov       dl,byte ptr [_FakeSLUsing]
	test      dl,dl
	je        short @74
	inc       word ptr [_ScanLineFake]
	jmp       short @75
@74:
	mov       cx,word ptr [_ScanLine]
	mov       word ptr [_ScanLineFake],cx
@75:
	mov       al,byte ptr [_LineTicksInt]
	mov       byte ptr [_ClockticksSm],al
	mov       dl,byte ptr [_Mem+391757]
	cmp       dl,4
	jne       short @76
	mov       cl,byte ptr [_VBlanking]
	test      cl,cl
	jne       short @77
	mov       al,byte ptr [_BGVis]
	test      al,al
	je        short @77
	dec       byte ptr [_MMC3+1]
@77:
	mov       dl,byte ptr [_MMC3+1]
	test      dl,dl
	jne       @79
	mov       cl,byte ptr [_MMC3+3]
	test      cl,cl
	je        short @80
	call      @irq6502$qqrv
@80:
	mov       byte ptr [_MMC3+1],-1
	jmp       @79
@76:
	mov       al,byte ptr [_Mem+391757]
	cmp       al,16
	jne       short @81
	mov       dl,byte ptr [_M16+2]
	test      dl,dl
	je        @79
	dec       word ptr [_M16]
	cmp       word ptr [_M16],0
	jne       @79
	call      @irq6502$qqrv
	jmp       @79
@81:
	mov       cl,byte ptr [_Mem+391757]
	cmp       cl,17
	jne       short @84
	mov       al,byte ptr [_M17+2]
	test      al,al
	je        short @79
	inc       word ptr [_M17]
	cmp       word ptr [_M17],-1
	jne       short @79
	call      @irq6502$qqrv
	jmp       short @79
@84:
	mov       dl,byte ptr [_Mem+391757]
	cmp       dl,24
	jne       short @87
	mov       cl,byte ptr [_M24+3]
	test      cl,cl
	je        short @79
	inc       byte ptr [_M24+2]
	mov       al,byte ptr [_M24+2]
	cmp       al,-1
	jne       short @79
	call      @irq6502$qqrv
	jmp       short @79
@87:
	mov       dl,byte ptr [_Mem+391757]
	cmp       dl,90
	jne       short @90
	mov       cl,byte ptr [_M90+2]
	test      cl,cl
	je        short @91
	dec       byte ptr [_M90+3]
	mov       al,byte ptr [_M90+3]
	test      al,al
	jne       short @92
	call      @irq6502$qqrv
	mov       byte ptr [_M90+2],0
@92:
@91:
@90:
@79:
	mov       dx,word ptr [_ScanLine]
	cmp       dx,word ptr [_MaxScanLine]
	jne       short @93
	mov       byte ptr [_Spr0Occ],0
	mov       byte ptr [_VBlanking],0
	mov       word ptr [_ScanLine],0
	mov       cl,byte ptr [_SavingState]
	test      cl,cl
	je        short @94
	mov       byte ptr [_SavingState],0
	call      @SaveState$qv
@94:
	call      @PrepTileline$qv
@93:
	mov       al,byte ptr [_VBlanking]
	test      al,al
	jne       @97
	cmp       word ptr [_ScanLine],240
	jge       @97
	call      @DrawScanline$qv
@98:
	mov       al,byte ptr [_SSize]
	shl       eax,3
	inc       eax
?live1@2192: ; EAX = SSizeNew
	mov       dl,byte ptr [_Spr0Occ]
	test      dl,dl
	jne       @101
	xor       ecx,ecx
	mov       cl,byte ptr [_Mem+391493]
	inc       ecx
	movsx     edx,word ptr [_ScanLine]
	cmp       ecx,edx
	jg        @101
	xor       ecx,ecx
	mov       cl,byte ptr [_Mem+391493]
	and       eax,255
	add       ecx,eax
	add       ecx,9
	movsx     eax,word ptr [_ScanLine]
	cmp       ecx,eax
	jle       @101
?live1@2208: ; 
@102:
	mov       dl,byte ptr [_Mem+391495]
?live1@2224: ; EDX = @temp20
	mov       al,byte ptr [_Mem+391493]
?live1@2240: ; 
	test      dl,64
	setne     cl
?live1@2256: ; EAX = ydiff, EDX = @temp20
	movsx     ebx,byte ptr [_SSize]
?live1@2272: ; 
	and       ecx,1
?live1@2288: ; EDX = @temp20
	inc       eax
?live1@2304: ; 
	mov       byte ptr [ebp-65],cl
?live1@2320: ; EDX = @temp20
	push      eax
	pop       ecx
	mov       al,byte ptr [_ScanLine]
	sub       al,cl
?live1@2336: ; EAX = ydiff, EDX = @temp20
	xor       ecx,ecx
	mov       cl,byte ptr [_Mem+391494]
	sub       cx,bx
	test      al,8
	setne     bl
	and       ebx,1
	add       cx,bx
	shl       ecx,4
	mov       word ptr [ebp-68],cx
	test      dl,-128
	je        short @103
	and       eax,255
	and       ax,7
	mov       dx,7
	sub       dx,ax
	or        word ptr [ebp-68],dx
	jmp       short @104
?live1@2368: ; EAX = ydiff
@103:
	and       al,7
	xor       ecx,ecx
	mov       cl,al
	or        word ptr [ebp-68],cx
?live1@2384: ; 
@104:
@105:
	movsx     edx,word ptr [ebp-68]
	xor       eax,eax
	lea       ebx,dword ptr [edx+_Mem]
	movsx     edx,byte ptr [ebp-65]
	lea       esi,dword ptr [_bitnumsp+8*edx]
?live1@2400: ; EBX = @temp0, ESI = @temp1, EAX = xx
@106:
@108:
	movsx     edi,byte ptr [_SpPTA]
	movsx     edx,word ptr [ebp-68]
	shl       edi,12
	or        edx,8
	lea       ecx,dword ptr [edi+_Mem]
	mov       dl,byte ptr [ecx+edx+379168]
	mov       cl,byte ptr [esi]
	and       dl,cl
	mov       cl,byte ptr [ebx+edi+379168]
	setne     dl
	and       edx,1
	add       edx,edx
	and       cl,byte ptr [esi]
	setne     cl
	and       ecx,1
	or        dl,cl
?live1@2416: ; EBX = @temp0, ESI = @temp1, EAX = xx, EDX = col
	test      dl,dl
	je        short @109
?live1@2432: ; EBX = @temp0, ESI = @temp1, EAX = xx
	mov       byte ptr [_Spr0Occ],1
@109:
@110:
@111:
	inc       eax
	inc       esi
	cmp       al,8
	jb        short @106
?live1@2464: ; 
@113:
@101:
@114:
@97:
	mov       ax,word ptr [_ScanLine]
	cmp       ax,word ptr [_VBScanLine]
	jne       @116
	mov       eax,dword ptr [@Forms@Application]
	call      @Forms@TApplication@ProcessMessages$qqrv
	mov       dl,byte ptr [_FakeSLUsing]
	test      dl,dl
	je        short @117
	mov       byte ptr [_FakeSLUsing],0
@117:
@118:
	xor       edi,edi
	mov       esi,offset _SNDChannels+10
	mov       ebx,offset _PulseChan+15
?live1@2528: ; EBX = @temp0, ESI = @temp1, EDI = i
@119:
	mov       al,byte ptr [ebx]
	test      al,al
	je        @121
	mov       dl,byte ptr [ebx-13]
	test      dl,dl
	jbe       short @122
	mov       cl,byte ptr [ebx-3]
	test      cl,cl
	jne       short @123
	fld       dword ptr [ebx-11]
	fcomp     dword ptr [@124]
	fnstsw ax
	sahf
	jbe       short @123
	fld       dword ptr [ebx-7]
	fsubr     dword ptr [ebx-11]
	fstp      dword ptr [ebx-11]
@123:
	mov       dl,byte ptr [ebx-3]
	cmp       dl,1
	jne       short @125
	fld       dword ptr [ebx-11]
	fcomp     dword ptr [@124+4]
	fnstsw ax
	sahf
	jae       short @125
	fld       dword ptr [ebx-7]
	fadd      dword ptr [ebx-11]
	fstp      dword ptr [ebx-11]
@125:
	fld       dword ptr [ebx-11]
	call      __ftol
	mov       byte ptr [esi],al
	dec       byte ptr [ebx-13]
	jmp       short @126
@122:
	mov       dl,byte ptr [ebx-1]
	test      dl,dl
	je        short @127
	mov       cl,byte ptr [ebx-3]
	test      cl,cl
	jne       short @128
	fld       dword ptr [ebx-11]
	fcomp     dword ptr [@124]
	fnstsw ax
	sahf
	jbe       short @128
	fld       dword ptr [ebx-7]
	fsubr     dword ptr [ebx-11]
	fstp      dword ptr [ebx-11]
@128:
	mov       dl,byte ptr [ebx-3]
	cmp       dl,1
	jne       short @129
	fld       dword ptr [ebx-11]
	fcomp     dword ptr [@124+4]
	fnstsw ax
	sahf
	jae       short @129
	fld       dword ptr [ebx-7]
	fadd      dword ptr [ebx-11]
	fstp      dword ptr [ebx-11]
@129:
	fld       dword ptr [ebx-11]
	call      __ftol
	mov       byte ptr [esi],al
	jmp       short @126
@127:
	mov       byte ptr [esi],0
	jmp       short @126
@121:
	mov       byte ptr [esi],0
@126:
@130:
	inc       edi
	add       esi,20
	add       ebx,16
	cmp       edi,2
	jl        @119
?live1@2736: ; 
	inc       byte ptr [_tmpframes]
	xor       edx,edx
	mov       dl,byte ptr [_tmpframes]
	mov       ecx,dword ptr [_VBSec]
	sar       ecx,1
	cmp       edx,ecx
	jl        @132
@133:
	lea       eax,dword ptr [ebp-76]
	push      eax
	call      QueryPerformanceCounter
	mov       eax,dword ptr [ebp-76]
?live1@2800: ; ECX = tmpval2
	mov       esi,dword ptr [_VBSec]
?live1@2816: ; 
	mov       ecx,eax
	mov       eax,dword ptr [_LastClockVal]
?live1@2832: ; ECX = tmpval2
	mov       edx,esi
?live1@2848: ; 
	sub       ecx,eax
?live1@2864: ; ECX = tmpval2
	sar       edx,1
	mov       eax,dword ptr [_ClockFreq]
	imul      edx
	cdq
	idiv      ecx
	mov       ebx,eax
	mov       dword ptr [_FPSnum],ebx
?live1@2880: ; EBX = @temp25, ESI = @temp26
	mov       al,byte ptr [_Autoframeskip]
	test      al,al
	je        short @134
	mov       edx,esi
	add       edx,8
	cmp       ebx,edx
	jle       short @135
	dec       dword ptr [_frameskip]
@135:
	add       esi,-8
	cmp       ebx,esi
	jge       short @136
	inc       dword ptr [_frameskip]
?live1@2928: ; 
@136:
	mov       ecx,dword ptr [_frameskip]
	dec       ecx
	jge       short @137
	mov       dword ptr [_frameskip],1
@137:
	mov       eax,dword ptr [_frameskip]
	mov       edx,dword ptr [_Autoframeskipmax]
	cmp       eax,edx
	jle       short @138
	xor       ecx,ecx
	mov       cl,byte ptr [_Autoframeskipmax]
	mov       dword ptr [_frameskip],ecx
@138:
@134:
	mov       eax,dword ptr [_StartFrm]
	mov       eax,dword ptr [eax+548]
	mov       dx,word ptr [_frameskip]
	call      @Comctrls@TCustomUpDown@SetPosition$qqrs
	mov       word ptr [ebp-48],8
	lea       eax,dword ptr [ebp-8]
	mov       edx,dword ptr [_FPSnum]
	call      @System@AnsiString@$bctr$qqri
	push      eax
	inc       dword ptr [ebp-36]
	mov       edx,offset s@+1186
	lea       eax,dword ptr [ebp-4]
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-36]
	xor       ecx,ecx
	mov       dword ptr [ebp-12],ecx
	lea       ecx,dword ptr [ebp-12]
	inc       dword ptr [ebp-36]
	pop       edx
	call      @System@AnsiString@$badd$xqqrrx17System@AnsiString
	lea       eax,dword ptr [ebp-12]
	push      eax
	mov       edx,offset s@+1201
	lea       eax,dword ptr [ebp-16]
	call      @System@AnsiString@$bctr$qqrpxc
	mov       edx,eax
	inc       dword ptr [ebp-36]
	xor       eax,eax
	mov       dword ptr [ebp-20],eax
	lea       ecx,dword ptr [ebp-20]
	inc       dword ptr [ebp-36]
	pop       eax
	call      @System@AnsiString@$badd$xqqrrx17System@AnsiString
	lea       edx,dword ptr [ebp-20]
	push      edx
	lea       eax,dword ptr [ebp-24]
	mov       edx,dword ptr [_frameskip]
	call      @System@AnsiString@$bctr$qqri
	mov       edx,eax
	inc       dword ptr [ebp-36]
	xor       eax,eax
	mov       dword ptr [ebp-28],eax
	lea       ecx,dword ptr [ebp-28]
	inc       dword ptr [ebp-36]
	pop       eax
	call      @System@AnsiString@$badd$xqqrrx17System@AnsiString
	lea       edx,dword ptr [ebp-28]
	mov       eax,dword ptr [_StartFrm]
	mov       edx,dword ptr [edx]
	call      @Controls@TControl@SetText$qqrx17System@AnsiString
	dec       dword ptr [ebp-36]
	lea       eax,dword ptr [ebp-28]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-36]
	lea       eax,dword ptr [ebp-24]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-36]
	lea       eax,dword ptr [ebp-20]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-36]
	lea       eax,dword ptr [ebp-16]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-36]
	lea       eax,dword ptr [ebp-12]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-36]
	lea       eax,dword ptr [ebp-8]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-36]
	lea       eax,dword ptr [ebp-4]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	push      offset _LastClockVal
	call      QueryPerformanceCounter
	mov       byte ptr [_tmpframes],0
@139:
@132:
	mov       cl,byte ptr [_Joy+1]
	cmp       cl,2
	jne       @141
	mov       ax,word ptr [_Joy+58]
	test      ax,ax
	jl        short @143
	cmp       ax,256
	jg        short @143
	cmp       word ptr [_Joy+60],0
	jl        short @143
	mov       dx,word ptr [_Joy+60]
	cmp       dx,word ptr [_YMax]
	jle       short @142
@143:
	mov       byte ptr [_Joy+57],0
	jmp       @144
@142:
	mov       byte ptr [_Joy+57],0
	mov       word ptr [_tmpLBYTE],0
	jmp       short @146
?live1@3120: ; EAX = @temp10
@145:
@147:
	movzx     edx,ax
?live1@3136: ; EAX = SprX, EDX = SprY
	xor       ebx,ebx
?live1@3152: ; EAX = SprX, EDX = @temp11
	mov       cl,byte ptr [edx+_Mem+391493]
?live1@3168: ; EAX = @temp10
	mov       al,byte ptr [edx+_Mem+391496]
?live1@3184: ; EAX = SprX, EDX = @temp11
	inc       ecx
	mov       edx,ecx
?live1@3200: ; EAX = SprX, EDX = SprY
	mov       bl,al
	movsx     ecx,word ptr [_Joy+58]
	cmp       ebx,ecx
	jg        short @148
	add       ebx,7
	cmp       ecx,ebx
	jg        short @148
	movsx     eax,word ptr [_Joy+60]
	xor       ecx,ecx
	mov       cl,dl
	cmp       eax,ecx
	jl        short @148
	movsx     eax,word ptr [_Joy+60]
	and       edx,255
	add       edx,7
	cmp       eax,edx
	jg        short @148
?live1@3216: ; 
	mov       byte ptr [_Joy+57],1
@148:
	add       word ptr [_tmpLBYTE],4
@149:
@146:
	mov       ax,word ptr [_tmpLBYTE]
	cmp       ax,256
	jae       short @150
	mov       dl,byte ptr [_Joy+57]
	test      dl,dl
	je        short @145
@150:
@144:
@141:
	inc       dword ptr [_FPSnum]
	call      @FinishTileline$qv
	mov       cl,byte ptr [_NMIonVBlank]
	test      cl,cl
	je        short @151
	call      @nmi6502$qqrv
@151:
	mov       byte ptr [_VBlanking],1
	mov       byte ptr [_VBlankOcc],1
@116:
	mov       eax,dword ptr [ebp-64]
	mov       dword ptr fs:[0],eax
@152:
	pop       edi
	pop       esi
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
	align 4        
@124:
	db        0,0,0,0,0,0,112,65
@HBlank$qv	endp
	align	4
@nmi6502$qqrv	proc	near
?live1@3376:
@153:
	mov       dx,word ptr [_PC]
	xor       eax,eax
	dec       edx
	movzx     ecx,dx
	mov       word ptr [_tmpLBYTE],dx
	mov       al,byte ptr [_SP]
	sar       ecx,8
	mov       byte ptr [eax+_Mem+264192],cl
	mov       dl,byte ptr [_tmpLBYTE]
	mov       byte ptr [eax+_Mem+264191],dl
	xor       edx,edx
	mov       cl,byte ptr [_P]
	mov       byte ptr [eax+_Mem+264190],cl
	sub       byte ptr [_SP],3
	or        byte ptr [_P],4
	movsx     eax,word ptr [_Mem+391772]
	shl       eax,13
	mov       dl,byte ptr [eax+_Mem+399993]
	movzx     eax,byte ptr [eax+_Mem+399992]
	shl       edx,8
	or        dx,ax
	movzx     ecx,dx
	mov       dword ptr [_PC],ecx
	mov       al,byte ptr [_HaltOnNMI]
	test      al,al
	je        short @154
	mov       byte ptr [_DebuggingTrace],1
	mov       byte ptr [_DebuggingRegs],1
	mov       byte ptr [_CPURunning],0
@154:
@155:
	ret 
@nmi6502$qqrv	endp
	align	4
@irq6502$qqrv	proc	near
?live1@3536:
@156:
	mov       cl,byte ptr [_P]
	test      cl,4
	jne       short @158
?live1@3552: ; ECX = @temp2
	mov       dx,word ptr [_PC]
	xor       eax,eax
	dec       edx
	mov       word ptr [_tmpLBYTE],dx
	movzx     edx,dx
	mov       al,byte ptr [_SP]
	sar       edx,8
	mov       byte ptr [eax+_Mem+264192],dl
	mov       dl,byte ptr [_tmpLBYTE]
	mov       byte ptr [eax+_Mem+264191],dl
	mov       byte ptr [eax+_Mem+264190],cl
	sub       byte ptr [_SP],3
?live1@3568: ; 
	or        byte ptr [_P],4
	movsx     eax,word ptr [_Mem+391772]
	shl       eax,13
	xor       ecx,ecx
	mov       cl,byte ptr [eax+_Mem+399997]
	movzx     eax,byte ptr [eax+_Mem+399996]
	shl       ecx,8
	or        cx,ax
	movzx     edx,cx
	mov       dword ptr [_PC],edx
@159:
@158:
	ret 
@irq6502$qqrv	endp
	align	4
@HardBoot$qv	proc	near
?live1@3616:
@160:
@161:
	xor       edx,edx
	mov       eax,offset _Mem+391774
@162:
	mov       word ptr [eax],99
@164:
	inc       edx
	add       eax,2
	cmp       edx,8
	jl        short @162
@166:
	xor       edx,edx
	mov       eax,offset _Mem+391790
@167:
	mov       word ptr [eax],99
@169:
	inc       edx
	add       eax,2
	cmp       edx,8
	jl        short @167
@171:
	xor       edx,edx
	mov       eax,offset _Mem+391766
@172:
	mov       word ptr [eax],99
@174:
	inc       edx
	add       eax,2
	cmp       edx,4
	jl        short @172
	mov       cl,byte ptr [_Mem+391757]
	sub       cl,-26
	jne       @176
	xor       eax,eax
	mov       al,byte ptr [_M22in1]
	cmp       eax,4
	ja        short @179
	jmp       dword ptr [@186+4*eax]
@186:
	dd        @185
	dd        @184
	dd        @183
	dd        @182
	dd        @181
@185:
	mov       byte ptr [_M22in1+1],1
	mov       byte ptr [_M22in1],1
	jmp       short @187
@184:
	mov       byte ptr [_M22in1+1],0
	mov       byte ptr [_M22in1],2
	jmp       short @187
@183:
	mov       byte ptr [_M22in1+1],1
	mov       byte ptr [_M22in1],3
	jmp       short @187
@182:
	mov       byte ptr [_M22in1+1],0
	mov       byte ptr [_M22in1],4
	jmp       short @187
@181:
	mov       byte ptr [_M22in1+1],0
	mov       byte ptr [_M22in1],0
@179:
@187:
	mov       dl,byte ptr [_M22in1+1]
	test      dl,dl
	je        short @188
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       word ptr [_Mem+391770],14
	mov       word ptr [_Mem+391772],15
	jmp       short @189
@188:
	mov       word ptr [_Mem+391766],16
	mov       word ptr [_Mem+391768],17
	mov       word ptr [_Mem+391770],78
	mov       word ptr [_Mem+391772],79
@176:
@189:
@190:
	xor       edx,edx
	mov       eax,offset _Mem
?live1@3888: ; EAX = @temp3, EDX = i
@191:
	mov       ecx,dword ptr [eax]
	mov       byte ptr [ecx],0
@193:
	inc       edx
	add       eax,4
	cmp       edx,16384
	jl        short @191
?live1@3920: ; 
@195:
	mov       edx,8192
	mov       eax,offset _Mem+346400
?live1@3936: ; EAX = @temp4, EDX = i
@196:
	mov       ecx,dword ptr [eax]
	mov       byte ptr [ecx],0
@198:
	inc       edx
	add       eax,4
	cmp       edx,16384
	jl        short @196
?live1@3968: ; 
	push      256
	push      0
	push      offset _Mem+391493
	call      _memset
	mov       byte ptr [_SP],-1
	mov       byte ptr [_P],32
	mov       byte ptr [_A],0
	mov       byte ptr [_X],0
	mov       byte ptr [_Y],0
	mov       byte ptr [_Mem+391750],0
	mov       word ptr [_Mem+391752],0
	and       word ptr [_Mem+391490],-16384
	mov       byte ptr [_Mem+391749],0
	mov       word ptr [_NTabAdr],8192
	add       esp,12
	mov       word ptr [_ScanLine],0
	mov       byte ptr [_NMIonVBlank],0
	mov       byte ptr [_NMIonSprHit],0
	mov       byte ptr [_SSize],0
	mov       byte ptr [_BkPTA],0
	mov       byte ptr [_SpPTA],0
	mov       byte ptr [_Spr0Occ],0
	mov       byte ptr [_VBlankOcc],0
	mov       byte ptr [_PPUAdrI],0
	mov       byte ptr [_SprVis],0
	mov       byte ptr [_BGVis],0
	mov       byte ptr [_SprClip],0
	mov       byte ptr [_BGClip],0
	mov       byte ptr [_DispType],0
	mov       byte ptr [_ScLnSprCnt],0
	mov       byte ptr [_VRAMWrFlg],0
	mov       byte ptr [_VFirstRead],0
	mov       byte ptr [_SFirstRead],0
	mov       byte ptr [_TUMode],0
	push      48
	mov       word ptr [_NTabAdr],8192
	mov       byte ptr [_MMC3],0
	mov       byte ptr [_MMC3+1],0
	mov       byte ptr [_MMC3+2],0
	mov       byte ptr [_MMC3+3],0
	mov       byte ptr [_MMC3+4],0
	mov       byte ptr [_MMC3+5],0
	mov       byte ptr [_MMC1],0
	mov       byte ptr [_MMC1+1],0
	mov       byte ptr [_MMC1+2],0
	mov       byte ptr [_MMC1+3],0
	mov       byte ptr [_MMC1+4],0
	mov       byte ptr [_MMC1+5],0
	mov       byte ptr [_MMC1+6],0
	mov       byte ptr [_MMC1+7],0
	mov       byte ptr [_MMC1+8],0
	mov       byte ptr [_MMC1+9],0
	push      0
	mov       al,byte ptr [_LineTicksInt]
	push      offset _Joy+2
	add       al,-7
	mov       byte ptr [_ClockticksSm],al
	mov       byte ptr [_Joy+50],0
	mov       byte ptr [_Joy+51],0
	mov       byte ptr [_Joy+52],0
	mov       byte ptr [_Joy+53],0
	call      _memset
	add       esp,12
	mov       byte ptr [_PulseChan+15],0
	mov       byte ptr [_PulseChan+31],0
	mov       byte ptr [_TriChan+3],0
	mov       byte ptr [_NoiseChan],0
	mov       byte ptr [_DCMChan+4216],0
	xor       edx,edx
	mov       dword ptr [_PulseChan+4],edx
	xor       ecx,ecx
	mov       dword ptr [_PulseChan+20],ecx
	mov       byte ptr [_PulseChan+2],0
	mov       byte ptr [_PulseChan+18],0
	mov       byte ptr [_PulseChan+14],0
	mov       byte ptr [_PulseChan+30],0
	call      @reset6502$qqrv
@200:
	ret 
@HardBoot$qv	endp
	align	4
@reset6502$qqrv	proc	near
?live1@4624:
@201:
	push      ebx
	xor       ebx,ebx
	xor       eax,eax
?live1@4656: ; EBX = DontSwapVRAM, EAX = DontSwapPRG
	xor       edx,edx
	mov       dl,byte ptr [_Mem+391757]
	cmp       edx,21
	jg        short @240
	je        @221
	cmp       edx,19
	ja        @202
	jmp       dword ptr [@241+4*edx]
@241:
	dd        @239
	dd        @238
	dd        @237
	dd        @236
	dd        @235
	dd        @234
	dd        @233
	dd        @232
	dd        @231
	dd        @230
	dd        @229
	dd        @228
	dd        @202
	dd        @227
	dd        @202
	dd        @226
	dd        @225
	dd        @224
	dd        @223
	dd        @222
@240:
	cmp       edx,66
	jg        short @242
	je        @212
	cmp       edx,33
	jg        short @243
	je        @216
	sub       edx,22
	je        @220
	dec       edx
	je        @219
	dec       edx
	je        @218
	sub       edx,8
	je        @217
	jmp       @202
@243:
	sub       edx,34
	je        @215
	sub       edx,30
	je        @214
	dec       edx
	je        @213
	jmp       @202
@242:
	cmp       edx,90
	jg        short @244
	je        @207
	sub       edx,68
	je        @211
	dec       edx
	je        @210
	sub       edx,2
	je        @209
	sub       edx,7
	je        @208
	jmp       @202
@244:
	sub       edx,91
	je        @206
	sub       edx,8
	je        @205
	sub       edx,131
	je        @204
	jmp       @202
@239:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-2
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391770],dx
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-1
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391772],dx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@238:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-2
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391770],dx
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-1
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391772],dx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@237:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-2
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391770],dx
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-1
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391772],dx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@236:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-2
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391770],dx
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-1
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391772],dx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@235:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-2
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391770],dx
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-1
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391772],dx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@234:
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	and       edx,255
	mov       word ptr [_Mem+391766],dx
	mov       word ptr [_Mem+391768],dx
	mov       cx,word ptr [_Mem+391766]
	mov       word ptr [_Mem+391770],cx
	mov       dx,word ptr [_Mem+391766]
	mov       word ptr [_Mem+391772],dx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@233:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       word ptr [_Mem+391770],2
	mov       word ptr [_Mem+391772],3
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@232:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       word ptr [_Mem+391770],2
	mov       word ptr [_Mem+391772],3
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@231:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       word ptr [_Mem+391770],2
	mov       word ptr [_Mem+391772],3
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@230:
	mov       word ptr [_Mem+391766],0
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-3
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391768],dx
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-2
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391770],dx
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-1
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391772],dx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@229:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-2
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391770],dx
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-1
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391772],dx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@228:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       word ptr [_Mem+391770],2
	mov       word ptr [_Mem+391772],3
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@227:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       word ptr [_Mem+391770],2
	mov       word ptr [_Mem+391772],3
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@226:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       word ptr [_Mem+391770],2
	mov       word ptr [_Mem+391772],3
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
?live1@6016: ; EAX = DontSwapPRG
@225:
	mov       word ptr [_Mem+391766],0
	xor       edx,edx
	mov       word ptr [_Mem+391768],1
	mov       bl,1
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-2
	mov       dl,cl
	mov       word ptr [_Mem+391770],dx
	mov       cl,byte ptr [_Mem+391758]
	add       cl,-1
	xor       edx,edx
	mov       dl,cl
	mov       word ptr [_Mem+391772],dx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
?live1@6144: ; EBX = DontSwapVRAM, EAX = DontSwapPRG
	jmp       @245
?live1@6160: ; EAX = DontSwapPRG
@224:
	mov       word ptr [_Mem+391766],0
	xor       ecx,ecx
	mov       word ptr [_Mem+391768],1
	mov       bl,1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
?live1@6288: ; EBX = DontSwapVRAM, EAX = DontSwapPRG
	jmp       @245
?live1@6304: ; EAX = DontSwapPRG
@223:
	mov       word ptr [_Mem+391766],0
	xor       ecx,ecx
	mov       word ptr [_Mem+391768],1
	mov       bl,1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
?live1@6432: ; EBX = DontSwapVRAM, EAX = DontSwapPRG
	jmp       @245
@222:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-8
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391790],cx
	mov       dl,byte ptr [_Mem+391790]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391792],cx
	mov       dl,byte ptr [_Mem+391790]
	add       dl,2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391794],cx
	mov       dl,byte ptr [_Mem+391790]
	add       dl,3
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391796],cx
	mov       dl,byte ptr [_Mem+391790]
	add       dl,4
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391798],cx
	mov       dl,byte ptr [_Mem+391790]
	add       dl,5
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391800],cx
	mov       dl,byte ptr [_Mem+391790]
	add       dl,6
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391802],cx
	mov       dl,byte ptr [_Mem+391790]
	add       dl,7
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391804],cx
	jmp       @245
?live1@6544: ; EAX = DontSwapPRG
@221:
	mov       word ptr [_Mem+391766],0
	xor       ecx,ecx
	mov       word ptr [_Mem+391768],1
	mov       bl,1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
?live1@6672: ; EBX = DontSwapVRAM, EAX = DontSwapPRG
	jmp       @245
@220:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
?live1@6784: ; EAX = DontSwapPRG
@219:
	mov       word ptr [_Mem+391766],0
	xor       ecx,ecx
	mov       word ptr [_Mem+391768],1
	mov       bl,1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
?live1@6912: ; EBX = DontSwapVRAM, EAX = DontSwapPRG
	jmp       @245
?live1@6928: ; EAX = DontSwapPRG
@218:
	mov       word ptr [_Mem+391766],0
	xor       ecx,ecx
	mov       word ptr [_Mem+391768],1
	mov       bl,1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
?live1@7008: ; EBX = DontSwapVRAM, EAX = DontSwapPRG
	jmp       @245
?live1@7024: ; EAX = DontSwapPRG
@217:
	mov       word ptr [_Mem+391766],0
	xor       ecx,ecx
	mov       word ptr [_Mem+391768],1
	mov       bl,1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
?live1@7152: ; EBX = DontSwapVRAM, EAX = DontSwapPRG
	jmp       @245
?live1@7168: ; EAX = DontSwapPRG
@216:
	mov       word ptr [_Mem+391766],0
	xor       ecx,ecx
	mov       word ptr [_Mem+391768],1
	mov       bl,1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
?live1@7296: ; EBX = DontSwapVRAM, EAX = DontSwapPRG
	jmp       @245
@215:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       word ptr [_Mem+391770],2
	mov       word ptr [_Mem+391772],3
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@214:
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	and       edx,255
	mov       word ptr [_Mem+391766],dx
?live1@7424: ; EBX = DontSwapVRAM, EAX = DontSwapPRG, EDX = @temp13
	mov       word ptr [_Mem+391770],dx
	mov       cx,word ptr [_Mem+391766]
	mov       word ptr [_Mem+391772],cx
?live1@7440: ; EBX = DontSwapVRAM, EAX = DontSwapPRG
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
?live1@7504: ; EAX = DontSwapPRG
@213:
	mov       word ptr [_Mem+391766],0
	xor       ecx,ecx
	mov       word ptr [_Mem+391768],1
	mov       bl,1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
?live1@7632: ; EBX = DontSwapVRAM, EAX = DontSwapPRG
	jmp       @245
@212:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       word ptr [_Mem+391770],2
	mov       word ptr [_Mem+391772],3
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@211:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@210:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       word ptr [_Mem+391770],2
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@209:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@208:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@207:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@206:
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391766],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391768],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       @245
@205:
	mov       word ptr [_Mem+391766],0
	mov       word ptr [_Mem+391768],1
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-1
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	mov       word ptr [_Mem+391790],0
	mov       word ptr [_Mem+391792],1
	mov       word ptr [_Mem+391794],2
	mov       word ptr [_Mem+391796],3
	mov       word ptr [_Mem+391798],4
	mov       word ptr [_Mem+391800],5
	mov       word ptr [_Mem+391802],6
	mov       word ptr [_Mem+391804],7
	jmp       short @245
?live1@8432: ; 
@204:
	mov       bl,1
?live1@8448: ; EBX = DontSwapVRAM
	mov       al,1
?live1@8464: ; EBX = DontSwapVRAM, EAX = DontSwapPRG
@202:
@245:
	test      al,al
	jne       short @246
?live1@8480: ; EBX = DontSwapVRAM
	call      @UpdateGGCodes$qqrv
@246:
	test      bl,bl
	jne       @247
?live1@8512: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @248
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@248:
@249:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @250
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@250:
@251:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @252
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@252:
@253:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @254
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@254:
@255:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @256
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@256:
@257:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @258
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@258:
@259:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @260
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@260:
@261:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @262
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@262:
@263:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
@247:
	movsx     eax,word ptr [_Mem+391772]
	shl       eax,13
	xor       edx,edx
	xor       ecx,ecx
	mov       cl,byte ptr [eax+_Mem+399994]
	mov       dl,byte ptr [eax+_Mem+399995]
	shl       edx,8
	or        dx,cx
	movzx     eax,dx
	mov       dword ptr [_PC],eax
	or        byte ptr [_P],4
	or        byte ptr [_P],8
@264:
	pop       ebx
	ret 
@reset6502$qqrv	endp
	align	4
@UpdateGGCodes$qqrv	proc	near
?live1@8592:
@265:
	push      ebx
@266:
	xor       edx,edx
	mov       eax,offset _GGCode
	jmp       short @268
?live1@8624: ; EAX = @temp0, EDX = i
@267:
	mov       cl,byte ptr [eax]
	test      cl,cl
	je        short @269
	movzx     ecx,word ptr [eax+2]
	mov       ecx,dword ptr [_Mem+4*ecx]
	mov       bl,byte ptr [ecx]
	cmp       bl,byte ptr [eax+5]
	jne       short @271
?live1@8656: ; EAX = @temp0, EDX = i, ECX = @temp2
	movzx     ebx,word ptr [eax+2]
	mov       bl,byte ptr [eax+4]
	mov       byte ptr [ecx],bl
?live1@8672: ; EAX = @temp0, EDX = i
	jmp       short @271
@269:
	movzx     ecx,word ptr [eax+2]
	mov       ecx,dword ptr [_Mem+4*ecx]
	mov       bl,byte ptr [eax+4]
	mov       byte ptr [ecx],bl
@271:
@272:
	inc       edx
	add       eax,6
@268:
	mov       ecx,dword ptr [_GGCodeNum]
	cmp       edx,ecx
	jl        short @267
?live1@8720: ; 
@274:
	pop       ebx
	ret 
@UpdateGGCodes$qqrv	endp
	align	4
@MemoryTUGet$qqrv	proc	near
?live1@8736:
@275:
	mov       edx,dword ptr [_TU]
	mov       cl,byte ptr [edx+_SpecialAccessR]
	test      cl,cl
	je        @276
?live1@8752: ; EAX = ToRet
@277:
	mov       edx,dword ptr [_TU]
	cmp       edx,16405
	jg        short @286
	je        @282
	sub       edx,8194
	je        short @285
	sub       edx,2
	je        short @284
	sub       edx,3
	je        short @283
	jmp       @278
@286:
	sub       edx,16406
	je        @281
	dec       edx
	je        @280
	jmp       @278
?live1@8768: ; 
@285:
	mov       al,byte ptr [_VBlankOcc]
	mov       cl,byte ptr [_Spr0Occ]
	shl       ecx,6
	mov       dl,byte ptr [_ScLnSprCnt]
	shl       eax,7
	or        al,cl
	mov       cl,byte ptr [_VRAMWrFlg]
	shl       edx,5
?live1@8784: ; EAX = ToRet
	mov       byte ptr [_VBlankOcc],0
?live1@8800: ; 
	shl       ecx,4
	or        al,dl
	or        al,cl
?live1@8816: ; EAX = ToRet
	mov       byte ptr [_Mem+391754],0
@311:
	ret 
?live1@8848: ; 
@284:
	xor       eax,eax
?live1@8864: ; EAX = ToRet
	mov       dl,byte ptr [_SFirstRead]
?live1@8880: ; 
	mov       al,byte ptr [_Mem+391749]
?live1@8896: ; EAX = ToRet
	test      dl,dl
?live1@8912: ; 
	mov       al,byte ptr [eax+_Mem+391493]
?live1@8928: ; EAX = ToRet
	jne       short @288
	inc       byte ptr [_Mem+391749]
	jmp       @287
@288:
	mov       byte ptr [_SFirstRead],0
@312:
	ret 
?live1@8960: ; 
@283:
	mov       ax,word ptr [_Mem+391490]
	mov       edx,eax
	and       dx,-16384
	and       ax,16383
	and       ax,16383
	or        dx,ax
	mov       word ptr [_Mem+391490],dx
	mov       eax,edx
	and       eax,16383
?live1@8976: ; EDX = @temp2, EAX = @temp3
	cmp       eax,16128
	jae       @291
	mov       cl,byte ptr [_VFirstRead]
	test      cl,cl
	jne       short @293
	mov       eax,dword ptr [_Mem+313632+4*eax]
	mov       al,byte ptr [eax]
?live1@9024: ; EAX = ToRet, EDX = @temp2
	mov       cl,byte ptr [_PPUAdrI]
	test      cl,cl
	je        short @294
	mov       ecx,edx
	and       cx,-16384
	add       dx,32
	and       dx,16383
	or        cx,dx
	mov       word ptr [_Mem+391490],cx
	jmp       short @295
@294:
	mov       dx,word ptr [_Mem+391490]
	mov       ecx,edx
	and       cx,-16384
	inc       edx
	and       dx,16383
	or        cx,dx
	mov       word ptr [_Mem+391490],cx
?live1@9040: ; EAX = ToRet
@295:
	mov       byte ptr [_Mem+391488],al
	jmp       @287
@293:
	mov       dx,word ptr [_Mem+391490]
?live1@9088: ; 
	mov       al,byte ptr [_Mem+391488]
?live1@9104: ; EAX = ToRet
	and       edx,16383
	mov       edx,dword ptr [_Mem+313632+4*edx]
	mov       cl,byte ptr [edx]
	mov       byte ptr [_Mem+391488],cl
	mov       byte ptr [_VFirstRead],0
	jmp       @287
?live1@9152: ; 
@291:
	mov       dx,word ptr [_Mem+391490]
	mov       eax,edx
	and       eax,16383
	mov       ecx,dword ptr [_Mem+313632+4*eax]
	mov       al,byte ptr [ecx]
?live1@9168: ; EAX = ToRet, EDX = @temp9
	mov       cl,byte ptr [_PPUAdrI]
	test      cl,cl
	je        short @297
	mov       ecx,edx
	and       cx,-16384
	add       dx,32
	and       dx,16383
	or        cx,dx
	mov       word ptr [_Mem+391490],cx
	jmp       @287
@297:
	mov       dx,word ptr [_Mem+391490]
	mov       ecx,edx
	and       cx,-16384
	inc       edx
	and       dx,16383
	or        cx,dx
	mov       word ptr [_Mem+391490],cx
?live1@9184: ; EAX = ToRet
@313:
	ret 
@282:
	mov       dl,byte ptr [_PulseChan+2]
	test      dl,dl
	je        short @299
	or        al,1
@299:
	mov       dl,byte ptr [_PulseChan+18]
	test      dl,dl
	je        short @300
	or        al,2
@300:
	mov       cl,byte ptr [_TriChan+3]
	test      cl,cl
	je        short @301
	or        al,4
@301:
	mov       dl,byte ptr [_NoiseChan]
	test      dl,dl
	je        short @302
	or        al,8
@302:
	mov       cl,byte ptr [_DCMChan+4216]
	test      cl,cl
	je        short @287
	or        al,16
@314:
	ret 
?live1@9296: ; 
@281:
	mov       eax,offset _Joy
	xor       edx,edx
	call      @@JoypadSt@Get$qqr4bool
?live1@9312: ; EAX = ToRet
@315:
	ret 
?live1@9328: ; 
@280:
	mov       eax,offset _Joy
	mov       dl,1
	call      @@JoypadSt@Get$qqr4bool
?live1@9344: ; EAX = ToRet
@316:
	ret 
?live1@9360: ; 
@278:
	mov       al,byte ptr [_Mem+1964670]
	test      al,al
	je        short @304
	mov       ecx,dword ptr [_TU]
	mov       eax,dword ptr [_Mem+4*ecx]
	mov       al,byte ptr [eax]
@317:
	ret 
@304:
	xor       eax,eax
@318:
	ret 
@306:
@319:
	ret 
@276:
	mov       eax,dword ptr [_TU]
	test      ah,-128
	je        short @308
?live1@9440: ; EAX = @temp0
	mov       edx,eax
	and       eax,24576
	shr       eax,13
	and       edx,8191
	movsx     ecx,word ptr [_Mem+391766+2*eax]
	shl       ecx,13
	lea       eax,dword ptr [ecx+_Mem+391806]
	mov       al,byte ptr [eax+edx]
@320:
	ret 
?live1@9456: ; 
@308:
	mov       edx,dword ptr [_TU]
	mov       ecx,dword ptr [_Mem+4*edx]
	mov       al,byte ptr [ecx]
@307:
@310:
@287:
	ret 
@MemoryTUGet$qqrv	endp
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@_$DCEB$@MemoryTUEquals$qqruc	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	0
	align	4
@_$ECTFB$@MemoryTUEquals$qqruc	label	dword
	dd	0
	dd	-40
	dw	0
	dw	5
	dd	0
	dd	@_$DCEB$@MemoryTUEquals$qqruc
_DATA	ends
_TEXT	segment dword public use32 'CODE'
	align	4
@MemoryTUEquals$qqruc	proc	near
?live1@9488:
@321:
	push      ebp
	mov       ebp,esp
	add       esp,-44
	push      ebx
	mov       ebx,eax
	mov       eax,offset @_$ECTFB$@MemoryTUEquals$qqruc
	call      @__InitExceptBlockLDTC
?live1@9504: ; EBX = ta
	mov       edx,dword ptr [_TU]
	mov       cl,byte ptr [edx+_SpecialAccessW]
	test      cl,cl
	je        @322
	mov       eax,dword ptr [_TU]
	cmp       eax,16392
	jg        short @356
	je        @340
	cmp       eax,16384
	jg        short @357
	je        @348
	add       eax,-8192
	cmp       eax,7
	ja        @323
	jmp       dword ptr [@358+4*eax]
@358:
	dd        @355
	dd        @354
	dd        @323
	dd        @353
	dd        @352
	dd        @351
	dd        @350
	dd        @349
@357:
	add       eax,-16385
	cmp       eax,6
	ja        @323
	jmp       dword ptr [@359+4*eax]
@359:
	dd        @347
	dd        @346
	dd        @345
	dd        @344
	dd        @343
	dd        @342
	dd        @341
@356:
	add       eax,-16393
	cmp       eax,14
	ja        @323
	jmp       dword ptr [@360+4*eax]
@360:
	dd        @339
	dd        @338
	dd        @337
	dd        @336
	dd        @335
	dd        @334
	dd        @333
	dd        @332
	dd        @331
	dd        @330
	dd        @329
	dd        @328
	dd        @327
	dd        @326
	dd        @325
@355:
	mov       eax,ebx
	test      al,-128
	setne     dl
	and       edx,1
?live1@9552: ; EBX = ta, EAX = @temp2
	test      al,32
	setne     cl
	and       ecx,1
	test      al,16
?live1@9584: ; EBX = ta
	mov       byte ptr [_NMIonVBlank],dl
?live1@9600: ; EBX = ta, EAX = @temp2
	mov       byte ptr [_SSize],cl
	setne     dl
	and       edx,1
	test      al,8
	setne     cl
	and       ecx,1
	test      al,4
	setne     al
	and       eax,1
	mov       byte ptr [_BkPTA],dl
	mov       byte ptr [_SpPTA],cl
	mov       byte ptr [_PPUAdrI],al
?live1@9712: ; EBX = ta
	test      bl,1
	setne     al
	xor       edx,edx
	and       eax,1
	mov       dl,bl
?live1@9728: ; 
	mov       ecx,dword ptr [ebp-40]
?live1@9744: ; EBX = ta
	and       dx,2
	add       ax,dx
	shl       eax,10
	or        ax,8192
	mov       word ptr [_NTabAdr],ax
?live1@9760: ; 
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@9776: ; EBX = ta
@354:
	mov       eax,ebx
	test      al,16
	setne     dl
	and       edx,1
?live1@9792: ; EBX = ta, EAX = @temp3
	test      al,8
	setne     cl
	and       ecx,1
	test      al,4
?live1@9824: ; EBX = ta
	mov       byte ptr [_SprVis],dl
?live1@9840: ; EBX = ta, EAX = @temp3
	mov       byte ptr [_BGVis],cl
	setne     dl
	and       edx,1
	test      al,2
	setne     cl
	and       ecx,1
	test      al,1
	setne     al
	mov       byte ptr [_SprClip],dl
	mov       byte ptr [_BGClip],cl
	and       eax,1
	mov       byte ptr [_DispType],al
?live1@9952: ; 
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@9968: ; EBX = ta
@353:
	mov       byte ptr [_Mem+391749],bl
?live1@9984: ; 
	mov       byte ptr [_SFirstRead],1
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@10016: ; EBX = ta
@352:
	xor       ecx,ecx
	mov       cl,byte ptr [_Mem+391749]
	mov       byte ptr [ecx+_Mem+391493],bl
?live1@10032: ; 
	inc       byte ptr [_Mem+391749]
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@10064: ; EBX = ta
@351:
	mov       dl,byte ptr [_Mem+391754]
	test      dl,dl
	jne       short @362
	mov       byte ptr [_Mem+391754],1
	mov       byte ptr [_Mem+391750],bl
?live1@10112: ; 
	jmp       short @363
?live1@10128: ; EBX = ta
@362:
	mov       byte ptr [_Mem+391754],0
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391752],ax
?live1@10160: ; EAX = @temp7
	cmp       ax,240
	jl        short @364
?live1@10176: ; 
	mov       word ptr [_Mem+391752],0
@364:
@363:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@10208: ; EBX = ta
@350:
	mov       cl,byte ptr [_Mem+391492]
	test      cl,cl
	jne       short @365
	mov       byte ptr [_Mem+391492],1
	and       bl,63
	mov       byte ptr [_Mem+391489],bl
?live1@10256: ; 
	jmp       @366
?live1@10272: ; EBX = ta
@365:
	mov       byte ptr [_Mem+391492],0
	xor       edx,edx
	mov       dl,byte ptr [_Mem+391489]
	xor       eax,eax
	shl       edx,8
	mov       al,bl
	or        dx,ax
	mov       cx,word ptr [_Mem+391490]
	and       cx,-16384
	and       dx,16383
	or        dx,cx
	mov       word ptr [_Mem+391490],dx
	mov       eax,edx
	and       eax,16383
?live1@10304: ; EAX = @temp4
	mov       byte ptr [_VFirstRead],1
	cmp       word ptr [_ScanLine],240
	jge       short @367
	mov       edx,eax
	mov       ecx,eax
	and       dx,3072
	and       ecx,992
	or        dx,8192
	mov       word ptr [_NTabAdr],dx
	mov       edx,eax
	and       edx,12288
	and       al,31
	shr       edx,12
	shr       ecx,2
	or        cx,dx
	mov       word ptr [_ScanLineFake],cx
	shl       eax,3
	mov       byte ptr [_Mem+391750],al
?live1@10480: ; 
	mov       word ptr [_Mem+391752],0
	mov       byte ptr [_FakeSLUsing],1
@367:
@366:
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@10528: ; EBX = ta
@349:
	mov       dx,word ptr [_Mem+391490]
	and       edx,16383
	and       edx,16383
	mov       ecx,dword ptr [_Mem+313632+4*edx]
	mov       byte ptr [ecx],bl
?live1@10544: ; 
	mov       al,byte ptr [_PPUAdrI]
	test      al,al
	je        short @368
	mov       ax,word ptr [_Mem+391490]
	mov       edx,eax
	and       dx,-16384
	add       ax,32
	and       ax,16383
	or        dx,ax
	mov       word ptr [_Mem+391490],dx
	jmp       short @369
@368:
	mov       ax,word ptr [_Mem+391490]
	mov       edx,eax
	and       dx,-16384
	inc       eax
	and       ax,16383
	or        dx,ax
	mov       word ptr [_Mem+391490],dx
@369:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@10576: ; EBX = ta
@348:
	xor       ecx,ecx
	mov       cl,bl
	mov       eax,ecx
	and       eax,192
	sar       eax,6
?live1@10592: ; EBX = ta, ECX = @temp11
	test      bl,32
	setne     dl
	and       edx,1
?live1@10608: ; EBX = ta
	mov       byte ptr [_SNDChannels+8],al
?live1@10624: ; EBX = ta, ECX = @temp11
	test      bl,16
	mov       byte ptr [_PulseChan+14],dl
	je        short @370
?live1@10672: ; EBX = ta
	and       bl,15
	xor       eax,eax
	mov       al,bl
	mov       dword ptr [ebp-44],eax
	fild      dword ptr [ebp-44]
	fstp      dword ptr [_PulseChan+4]
?live1@10688: ; 
	mov       byte ptr [_PulseChan+12],2
	jmp       short @371
?live1@10720: ; EBX = ta, ECX = @temp11
@370:
	and       ecx,15
	mov       eax,20
	sub       eax,ecx
	mov       dword ptr [_PulseChan+4],1094713344
	push      eax
	mov       eax,1
	pop       edx
	mov       ecx,edx
	cdq
	idiv      ecx
	mov       dword ptr [ebp-44],eax
	fild      dword ptr [ebp-44]
	fstp      dword ptr [_PulseChan+8]
?live1@10768: ; 
	mov       byte ptr [_PulseChan+12],0
@371:
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@347:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@10816: ; EBX = ta
@346:
	mov       ax,word ptr [_SNDChannels]
	xor       ecx,ecx
	mov       edx,eax
	mov       cl,bl
	and       edx,2047
	or        cx,1792
	or        dx,255
	and       dx,cx
	and       dx,2047
	and       ax,-2048
	or        dx,ax
?live1@10832: ; 
	mov       eax,dword ptr [ebp-40]
?live1@10848: ; EBX = ta
	mov       word ptr [_SNDChannels],dx
?live1@10864: ; 
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@10880: ; EBX = ta
@345:
	xor       edx,edx
	mov       dl,bl
	and       edx,248
	sar       edx,3
	mov       cl,byte ptr [edx+_LengthInfo]
	xor       edx,edx
	mov       byte ptr [_PulseChan+2],cl
	mov       dl,bl
	mov       ax,word ptr [_SNDChannels]
	and       dx,7
	mov       ecx,eax
	and       ecx,2047
	and       cx,255
	and       ax,-2048
	shl       edx,8
	or        dx,cx
	and       dx,2047
	or        dx,ax
?live1@10944: ; 
	mov       eax,dword ptr [ebp-40]
?live1@10960: ; EBX = ta
	mov       word ptr [_SNDChannels],dx
?live1@10976: ; 
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@10992: ; EBX = ta
@344:
	xor       ecx,ecx
	mov       cl,bl
	mov       edx,ecx
	and       edx,192
	sar       edx,6
?live1@11008: ; EBX = ta, ECX = @temp16
	test      bl,32
	setne     al
	and       eax,1
?live1@11024: ; EBX = ta
	mov       byte ptr [_SNDChannels+28],dl
?live1@11040: ; EBX = ta, ECX = @temp16
	test      bl,16
	mov       byte ptr [_PulseChan+30],al
	je        short @372
?live1@11088: ; EBX = ta
	and       bl,15
	xor       edx,edx
	mov       dl,bl
	mov       dword ptr [ebp-44],edx
	fild      dword ptr [ebp-44]
	fstp      dword ptr [_PulseChan+20]
?live1@11104: ; 
	mov       byte ptr [_PulseChan+28],2
	jmp       short @373
?live1@11136: ; EBX = ta, ECX = @temp16
@372:
	and       ecx,15
	mov       edx,20
	sub       edx,ecx
	mov       eax,1
	mov       ecx,edx
	mov       dword ptr [_PulseChan+20],1094713344
	cdq
	idiv      ecx
	mov       dword ptr [ebp-44],eax
	fild      dword ptr [ebp-44]
	fstp      dword ptr [_PulseChan+24]
?live1@11184: ; 
	mov       byte ptr [_PulseChan+28],0
@373:
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@343:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@11232: ; EBX = ta
@342:
	mov       ax,word ptr [_SNDChannels+20]
	xor       ecx,ecx
	mov       edx,eax
	mov       cl,bl
	and       edx,2047
	or        cx,1792
	or        dx,255
	and       dx,cx
	and       dx,2047
	and       ax,-2048
	or        dx,ax
?live1@11248: ; 
	mov       eax,dword ptr [ebp-40]
?live1@11264: ; EBX = ta
	mov       word ptr [_SNDChannels+20],dx
?live1@11280: ; 
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@11296: ; EBX = ta
@341:
	xor       edx,edx
	mov       dl,bl
	and       edx,248
	sar       edx,3
	mov       cl,byte ptr [edx+_LengthInfo]
	xor       edx,edx
	mov       byte ptr [_PulseChan+18],cl
	mov       dl,bl
	mov       ax,word ptr [_SNDChannels+20]
	and       dx,7
	mov       ecx,eax
	and       ecx,2047
	and       cx,255
	and       ax,-2048
	shl       edx,8
	or        dx,cx
	and       dx,2047
	or        dx,ax
?live1@11360: ; 
	mov       eax,dword ptr [ebp-40]
?live1@11376: ; EBX = ta
	mov       word ptr [_SNDChannels+20],dx
?live1@11392: ; 
	mov       dword ptr fs:[0],eax
	jmp       @361
@340:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
@339:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
@338:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
@337:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
@336:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
@335:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
@334:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
@333:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@11536: ; EBX = ta
@332:
	test      bl,64
	setne     dl
	and       edx,1
	test      bl,-128
	setne     al
	mov       byte ptr [_DCMChan+4215],dl
	xor       edx,edx
	mov       dl,bl
	and       eax,1
	and       edx,15
	mov       byte ptr [_DCMChan+4214],al
?live1@11648: ; 
	mov       eax,dword ptr [ebp-40]
?live1@11664: ; EBX = ta
	mov       cx,word ptr [_PlayDataRate+2*edx]
	mov       word ptr [_DCMChan+4212],cx
?live1@11680: ; 
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@11696: ; EBX = ta
@331:
	xor       edx,edx
?live1@11712: ; 
	mov       eax,dword ptr [ebp-40]
?live1@11728: ; EBX = ta
	mov       dl,bl
	and       edx,126
	sar       edx,1
	test      bl,1
	setne     cl
	and       ecx,1
	mov       byte ptr [_DCMChan+4210],dl
	mov       byte ptr [_DCMChan+4211],cl
?live1@11792: ; 
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@11808: ; EBX = ta
@330:
	xor       eax,eax
	mov       al,bl
	shl       eax,6
	or        ax,-16384
?live1@11824: ; EAX = @temp21
	movzx     ecx,ax
?live1@11840: ; EBX = ta
	mov       word ptr [_DCMChan+4208],ax
?live1@11856: ; EAX = @temp21
	movzx     edx,word ptr [_DCMChan+4200]
	sar       edx,3
	and       ecx,16383
	add       ecx,offset _Mem+297248
	push      edx
	push      ecx
	push      offset _DCMChan
	call      _memcpy
	add       esp,12
?live1@11872: ; 
	xor       eax,eax
	mov       dword ptr [_DCMChan+4204],eax
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@11904: ; EBX = ta
@329:
	xor       eax,eax
	mov       al,bl
	shl       eax,7
	or        ax,1
?live1@11920: ; EAX = @temp22
	movzx     edx,ax
?live1@11936: ; EBX = ta
	mov       word ptr [_DCMChan+4200],ax
?live1@11952: ; EAX = @temp22
	movzx     ecx,word ptr [_DCMChan+4208]
	sar       edx,3
	and       ecx,16383
	add       ecx,offset _Mem+297248
	push      edx
	push      ecx
	push      offset _DCMChan
	call      _memcpy
	add       esp,12
?live1@11968: ; 
	xor       eax,eax
	mov       dword ptr [_DCMChan+4204],eax
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@12000: ; EBX = ta
@328:
	push      256
	xor       ecx,ecx
	mov       cl,bl
	shl       ecx,8
	mov       eax,dword ptr [_Mem+4*ecx]
	push      eax
	push      offset _Mem+391493
	call      _memcpy
	add       esp,12
?live1@12016: ; 
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@12032: ; EBX = ta
@327:
	test      bl,1
	setne     cl
	and       ecx,1
	test      bl,2
	setne     al
	and       eax,1
	mov       byte ptr [_PulseChan+15],cl
	test      bl,4
	setne     dl
	and       edx,1
	mov       byte ptr [_PulseChan+31],al
	test      bl,8
	setne     cl
	and       ecx,1
	mov       byte ptr [_TriChan+3],dl
	test      bl,16
	setne     al
	and       eax,1
	mov       byte ptr [_NoiseChan],cl
	mov       byte ptr [_DCMChan+4216],al
?live1@12192: ; 
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@12208: ; EBX = ta
@326:
	test      bl,1
	setne     al
	and       eax,1
	mov       edx,eax
	mov       byte ptr [_Joy+52],dl
	test      dl,dl
	jne       short @374
	mov       byte ptr [_Joy+50],0
@374:
@375:
	mov       cl,byte ptr [_Mem+391757]
	cmp       cl,99
	jne       @376
	test      bl,4
	setne     al
	and       eax,1
	shl       eax,3
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391790],dx
?live1@12256: ; 
	mov       cl,byte ptr [_Mem+391790]
	inc       ecx
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391792],ax
	mov       dl,byte ptr [_Mem+391790]
	add       dl,2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391794],cx
	mov       al,byte ptr [_Mem+391790]
	add       al,3
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391796],dx
	mov       cl,byte ptr [_Mem+391790]
	add       cl,4
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391798],ax
	mov       dl,byte ptr [_Mem+391790]
	add       dl,5
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391800],cx
	mov       al,byte ptr [_Mem+391790]
	add       al,6
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391802],dx
	mov       cl,byte ptr [_Mem+391790]
	add       cl,7
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391804],ax
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @377
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@377:
@378:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @379
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@379:
@380:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @381
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@381:
@382:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @383
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@383:
@384:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @385
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@385:
@386:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @387
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@387:
@388:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @389
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@389:
@390:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @391
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@391:
@392:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
@376:
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@12352: ; EBX = ta
@325:
	test      bl,1
	setne     al
	and       eax,1
	mov       edx,eax
	mov       byte ptr [_Joy+53],dl
	test      dl,dl
	jne       short @393
	mov       byte ptr [_Joy+51],0
?live1@12368: ; 
@393:
@394:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@12384: ; EBX = ta
@323:
	mov       edx,dword ptr [_TU]
	and       edx,57344
	cmp       edx,24576
	jne       short @396
	mov       al,byte ptr [_Mem+1964670]
	test      al,al
	je        short @397
	mov       edx,dword ptr [_TU]
	mov       ecx,dword ptr [_Mem+4*edx]
	mov       byte ptr [ecx],bl
@397:
@398:
@396:
	xor       eax,eax
	mov       al,byte ptr [_Mem+391757]
	cmp       eax,16
	jg        short @422
	je        @411
	cmp       eax,15
	ja        @1590
	jmp       dword ptr [@423+4*eax]
@423:
	dd        @421
	dd        @420
	dd        @419
	dd        @418
	dd        @417
	dd        @1590
	dd        @1590
	dd        @416
	dd        @415
	dd        @1590
	dd        @1590
	dd        @414
	dd        @1590
	dd        @413
	dd        @1590
	dd        @412
@422:
	cmp       eax,66
	jg        short @424
	je        @405
	cmp       eax,24
	jg        short @425
	je        @408
	sub       eax,17
	je        @410
	sub       eax,6
	je        @409
	jmp       @1590
@425:
	sub       eax,34
	je        @407
	sub       eax,30
	je        @406
	jmp       @1590
@424:
	sub       eax,71
	je        @404
	sub       eax,19
	je        @403
	dec       eax
	je        @402
	sub       eax,139
	je        @401
	jmp       @1590
?live1@12448: ; 
@421:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@12464: ; EBX = ta
@420:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,32768
	jae       short @426
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@426:
	test      bl,-128
	je        short @427
	mov       byte ptr [_MMC1+1],0
	mov       byte ptr [_MMC1],0
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
@427:
	mov       cl,byte ptr [_MMC1+1]
	and       bl,1
	shl       bl,cl
	or        byte ptr [_MMC1],bl
?live1@12512: ; 
	inc       byte ptr [_MMC1+1]
	mov       al,byte ptr [_MMC1+1]
	cmp       al,5
	jne       short @428
	mov       edx,dword ptr [_TU]
	mov       eax,offset _MMC1
	and       edx,28672
	shr       edx,13
	call      @@MMC1St@UpdateReg$qqruc
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
@428:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@12592: ; EBX = ta
@419:
	mov       edx,dword ptr [_TU]
	cmp       edx,32768
	jae       short @429
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@429:
	add       ebx,ebx
	mov       dl,byte ptr [_Mem+391762]
	and       bl,dl
	xor       ecx,ecx
	mov       cl,bl
	mov       word ptr [_Mem+391766],cx
?live1@12624: ; 
	mov       al,byte ptr [_Mem+391766]
	inc       eax
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391768],dx
	call      @UpdateGGCodes$qqrv
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@12672: ; EBX = ta
@418:
	mov       edx,dword ptr [_TU]
	cmp       edx,32768
	jae       short @430
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@430:
	xor       eax,eax
	mov       al,bl
	and       ax,7
	shl       eax,3
	and       ax,word ptr [_Mem+391764]
	mov       word ptr [_tmpLBYTE],ax
?live1@12704: ; EAX = @temp25
	mov       word ptr [_Mem+391790],ax
	mov       edx,eax
	inc       edx
	mov       word ptr [_Mem+391792],dx
	mov       ecx,eax
	add       cx,2
	mov       word ptr [_Mem+391794],cx
	mov       edx,eax
	add       dx,3
	mov       word ptr [_Mem+391796],dx
	mov       ecx,eax
	add       cx,4
	mov       word ptr [_Mem+391798],cx
	mov       edx,eax
	add       dx,5
	mov       word ptr [_Mem+391800],dx
	mov       ecx,eax
	add       cx,6
	mov       word ptr [_Mem+391802],cx
	add       ax,7
	mov       word ptr [_Mem+391804],ax
?live1@12752: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @431
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@431:
@432:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @433
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@433:
@434:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @435
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@435:
@436:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @437
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@437:
@438:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @439
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@439:
@440:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @441
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@441:
@442:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @443
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@443:
@444:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @445
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@445:
@446:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@12784: ; EBX = ta
@417:
	mov       edx,dword ptr [_TU]
	cmp       edx,32768
	jae       short @447
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
@447:
	and       dword ptr [_TU],57345
	mov       edx,dword ptr [_TU]
	cmp       edx,32768
	jne       short @449
	mov       eax,ebx
	and       al,7
	test      bl,64
	setne     dl
	and       edx,1
	mov       byte ptr [_MMC3],al
	test      bl,-128
	setne     cl
	and       ecx,1
	mov       byte ptr [_MMC3+4],dl
	mov       byte ptr [_MMC3+5],cl
?live1@12928: ; 
	mov       al,byte ptr [_MMC3+4]
	test      al,al
	je        short @450
	mov       dl,byte ptr [_Mem+391758]
	add       dl,-2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391766],cx
	jmp       short @451
@450:
	mov       al,byte ptr [_Mem+391758]
	add       al,-2
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391770],dx
@451:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@13008: ; EBX = ta
@449:
	mov       edx,dword ptr [_TU]
	cmp       edx,32769
	jne       @452
	xor       eax,eax
	mov       al,byte ptr [_MMC3]
	cmp       eax,7
	ja        @453
	jmp       dword ptr [@463+4*eax]
@463:
	dd        @462
	dd        @461
	dd        @460
	dd        @459
	dd        @458
	dd        @457
	dd        @456
	dd        @455
@462:
	mov       dl,byte ptr [_MMC3+5]
	xor       ecx,ecx
	shl       edx,2
	mov       cl,bl
	mov       byte ptr [_tmpBYTE],dl
	xor       eax,eax
	and       cx,word ptr [_Mem+391764]
	mov       al,byte ptr [_tmpBYTE]
	and       cx,254
?live1@13136: ; 
	xor       edx,edx
?live1@13152: ; EBX = ta
	mov       word ptr [_Mem+391790+2*eax],cx
?live1@13168: ; 
	xor       eax,eax
	mov       dl,byte ptr [_tmpBYTE]
	mov       al,byte ptr [_tmpBYTE]
	mov       cx,word ptr [_Mem+391790+2*edx]
	inc       ecx
	mov       word ptr [_Mem+391792+2*eax],cx
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @464
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@464:
@465:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @466
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@466:
@467:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @468
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@468:
@469:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @470
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@470:
@471:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @472
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@472:
@473:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @474
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@474:
@475:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @476
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@476:
@477:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @478
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@478:
@479:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@13216: ; EBX = ta
@461:
	mov       dl,byte ptr [_MMC3+5]
	xor       eax,eax
	shl       edx,2
	mov       al,bl
	add       dl,2
?live1@13296: ; 
	xor       ecx,ecx
?live1@13312: ; EBX = ta
	mov       byte ptr [_tmpBYTE],dl
	xor       edx,edx
	and       ax,word ptr [_Mem+391764]
	mov       dl,byte ptr [_tmpBYTE]
	and       ax,254
	mov       word ptr [_Mem+391790+2*edx],ax
?live1@13344: ; 
	xor       edx,edx
	mov       cl,byte ptr [_tmpBYTE]
	mov       dl,byte ptr [_tmpBYTE]
	mov       ax,word ptr [_Mem+391790+2*ecx]
	inc       eax
	mov       word ptr [_Mem+391792+2*edx],ax
	mov       cx,word ptr [_Mem+391790]
	cmp       cx,word ptr [_Mem+391774]
	je        short @480
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@480:
@481:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @482
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@482:
@483:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @484
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@484:
@485:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @486
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@486:
@487:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @488
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@488:
@489:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @490
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@490:
@491:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @492
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@492:
@493:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @494
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@494:
@495:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@13392: ; EBX = ta
@460:
	xor       edx,edx
	mov       dl,bl
	and       dx,word ptr [_Mem+391764]
	movsx     ecx,byte ptr [_MMC3+5]
	shl       ecx,2
	xor       ecx,4
	mov       word ptr [_Mem+391790+2*ecx],dx
?live1@13408: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @496
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@496:
@497:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @498
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@498:
@499:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @500
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@500:
@501:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @502
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@502:
@503:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @504
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@504:
@505:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @506
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@506:
@507:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @508
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@508:
@509:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @510
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@510:
@511:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@13440: ; EBX = ta
@459:
	xor       ecx,ecx
	mov       cl,bl
	and       cx,word ptr [_Mem+391764]
	movsx     eax,byte ptr [_MMC3+5]
	shl       eax,2
	xor       eax,5
	mov       word ptr [_Mem+391790+2*eax],cx
?live1@13456: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @512
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@512:
@513:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @514
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@514:
@515:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @516
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@516:
@517:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @518
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@518:
@519:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @520
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@520:
@521:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @522
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@522:
@523:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @524
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@524:
@525:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @526
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@526:
@527:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@13488: ; EBX = ta
@458:
	xor       edx,edx
	mov       dl,bl
	and       dx,word ptr [_Mem+391764]
	movsx     eax,byte ptr [_MMC3+5]
	shl       eax,2
	xor       eax,6
	mov       word ptr [_Mem+391790+2*eax],dx
?live1@13504: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @528
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@528:
@529:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @530
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@530:
@531:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @532
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@532:
@533:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @534
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@534:
@535:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @536
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@536:
@537:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @538
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@538:
@539:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @540
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@540:
@541:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @542
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@542:
@543:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@13536: ; EBX = ta
@457:
	xor       edx,edx
	mov       dl,bl
	and       dx,word ptr [_Mem+391764]
	movsx     eax,byte ptr [_MMC3+5]
	shl       eax,2
	xor       eax,7
	mov       word ptr [_Mem+391790+2*eax],dx
?live1@13552: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @544
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@544:
@545:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @546
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@546:
@547:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @548
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@548:
@549:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @550
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@550:
@551:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @552
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@552:
@553:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @554
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@554:
@555:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @556
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@556:
@557:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @558
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@558:
@559:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@13584: ; EBX = ta
@456:
	mov       dl,byte ptr [_Mem+391762]
	xor       eax,eax
	and       bl,dl
	movsx     edx,byte ptr [_MMC3+4]
	add       edx,edx
	mov       al,bl
	mov       word ptr [_Mem+391766+2*edx],ax
?live1@13600: ; 
	call      @UpdateGGCodes$qqrv
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@13632: ; EBX = ta
@455:
	mov       dl,byte ptr [_Mem+391762]
	and       bl,dl
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391768],ax
?live1@13648: ; 
	call      @UpdateGGCodes$qqrv
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@13680: ; EBX = ta
@453:
@452:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,40960
	jne       short @561
	test      bl,1
	je        short @562
?live1@13712: ; 
	push      2
	push      2
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       short @563
@562:
	push      1
	push      0
	push      1
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
@563:
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@13776: ; EBX = ta
@561:
	mov       edx,dword ptr [_TU]
	cmp       edx,40961
	jne       short @564
	test      bl,-128
	setne     cl
	and       ecx,1
	mov       byte ptr [_Mem+1964670],cl
?live1@13808: ; 
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@13824: ; EBX = ta
@564:
	mov       edx,dword ptr [_TU]
	cmp       edx,49152
	jne       short @565
	mov       byte ptr [_MMC3+1],bl
?live1@13856: ; 
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@13872: ; EBX = ta
@565:
	mov       edx,dword ptr [_TU]
	cmp       edx,49153
	jne       short @566
	mov       byte ptr [_MMC3+2],bl
?live1@13904: ; 
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@566:
	mov       edx,dword ptr [_TU]
	cmp       edx,57344
	jne       short @567
	mov       byte ptr [_MMC3+3],0
	mov       cl,byte ptr [_MMC3+2]
	mov       byte ptr [_MMC3+1],cl
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@567:
	mov       edx,dword ptr [_TU]
	cmp       edx,57345
	jne       short @568
	mov       byte ptr [_MMC3+3],1
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
@568:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@14048: ; EBX = ta
@416:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,32768
	jae       short @569
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@569:
	mov       dl,byte ptr [_Mem+391762]
	and       bl,dl
	and       bl,15
	xor       ecx,ecx
	mov       cl,bl
	shl       ecx,2
	movsx     eax,word ptr [_Mem+391766]
	cmp       ecx,eax
	je        short @570
	mov       edx,ebx
	shl       edx,2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391766],cx
	mov       al,byte ptr [_Mem+391766]
	inc       eax
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391768],dx
	mov       cl,byte ptr [_Mem+391766]
	add       cl,2
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391770],ax
	mov       dl,byte ptr [_Mem+391766]
	add       dl,3
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	call      @UpdateGGCodes$qqrv
@570:
	mov       eax,ebx
	mov       ecx,ebx
	and       al,16
	test      al,al
	setne     dl
	and       edx,1
	and       cl,16
	test      cl,cl
	push      edx
	setne     al
	mov       edx,ebx
	and       eax,1
	and       dl,16
	push      eax
	test      dl,dl
	setne     cl
	and       ecx,1
	and       bl,16
	test      bl,bl
	push      ecx
	setne     al
	and       eax,1
	push      eax
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
?live1@14160: ; 
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@14176: ; EBX = ta
@415:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,32768
	jae       short @571
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@571:
	xor       edx,edx
	mov       dl,bl
	and       edx,248
	sar       edx,3
	add       edx,edx
	mov       cl,byte ptr [_Mem+391762]
	and       dl,cl
	xor       eax,eax
	mov       al,dl
	mov       word ptr [_Mem+391766],ax
	mov       dl,byte ptr [_Mem+391766]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391768],cx
	and       bl,7
	shl       ebx,3
	mov       al,byte ptr [_Mem+391764]
	and       bl,al
	xor       edx,edx
	mov       dl,bl
	mov       word ptr [_Mem+391790],dx
?live1@14240: ; 
	mov       cl,byte ptr [_Mem+391790]
	inc       ecx
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391792],ax
	mov       dl,byte ptr [_Mem+391790]
	add       dl,2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391794],cx
	mov       al,byte ptr [_Mem+391790]
	add       al,3
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391796],dx
	mov       cl,byte ptr [_Mem+391790]
	add       cl,4
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391798],ax
	mov       dl,byte ptr [_Mem+391790]
	add       dl,5
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391800],cx
	mov       al,byte ptr [_Mem+391790]
	add       al,6
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391802],dx
	mov       cl,byte ptr [_Mem+391790]
	add       cl,7
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391804],ax
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @572
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@572:
@573:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @574
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@574:
@575:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @576
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@576:
@577:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @578
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@578:
@579:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @580
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@580:
@581:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @582
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@582:
@583:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @584
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@584:
@585:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @586
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@586:
@587:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	call      @UpdateGGCodes$qqrv
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@14352: ; EBX = ta
@414:
	mov       edx,dword ptr [_TU]
	cmp       edx,32768
	jae       short @588
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@588:
	mov       edx,ebx
	mov       cl,byte ptr [_Mem+391762]
	and       dl,3
	xor       eax,eax
	shl       edx,2
	and       dl,cl
	xor       ecx,ecx
	mov       al,dl
	mov       word ptr [_Mem+391766],ax
	mov       dl,byte ptr [_Mem+391766]
	inc       edx
	mov       cl,dl
	xor       edx,edx
	mov       word ptr [_Mem+391768],cx
	mov       al,byte ptr [_Mem+391766]
	add       al,2
	mov       dl,al
	xor       eax,eax
	mov       word ptr [_Mem+391770],dx
	xor       edx,edx
	mov       cl,byte ptr [_Mem+391766]
	mov       dl,bl
	add       cl,3
	and       edx,240
	mov       al,cl
	mov       word ptr [_Mem+391772],ax
	xor       eax,eax
	sar       edx,4
	mov       cl,byte ptr [_Mem+391764]
	shl       edx,3
	and       dl,cl
?live1@14592: ; 
	xor       ecx,ecx
?live1@14608: ; EBX = ta
	mov       al,dl
	mov       word ptr [_Mem+391790],ax
?live1@14624: ; 
	mov       dl,byte ptr [_Mem+391790]
	inc       edx
	mov       cl,dl
	xor       edx,edx
	mov       word ptr [_Mem+391792],cx
	mov       al,byte ptr [_Mem+391790]
	add       al,2
	mov       dl,al
	xor       eax,eax
	mov       word ptr [_Mem+391794],dx
	mov       cl,byte ptr [_Mem+391790]
	add       cl,3
	mov       al,cl
	xor       ecx,ecx
	mov       word ptr [_Mem+391796],ax
	mov       dl,byte ptr [_Mem+391790]
	add       dl,4
	mov       cl,dl
	xor       edx,edx
	mov       word ptr [_Mem+391798],cx
	mov       al,byte ptr [_Mem+391790]
	add       al,5
	mov       dl,al
	xor       eax,eax
	mov       word ptr [_Mem+391800],dx
	mov       cl,byte ptr [_Mem+391790]
	add       cl,6
	mov       al,cl
	xor       ecx,ecx
	mov       word ptr [_Mem+391802],ax
	mov       dl,byte ptr [_Mem+391790]
	add       dl,7
	mov       cl,dl
	mov       word ptr [_Mem+391804],cx
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @589
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@589:
@590:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @591
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@591:
@592:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @593
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@593:
@594:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @595
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@595:
@596:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @597
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@597:
@598:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @599
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@599:
@600:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @601
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@601:
@602:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @603
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@603:
@604:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	call      @UpdateGGCodes$qqrv
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
@413:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,32768
	jae       short @605
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@605:
	mov       ecx,dword ptr [_TU]
	mov       edx,dword ptr [_TU]
	and       ecx,24576
	and       edx,8191
	shr       ecx,13
	movsx     eax,word ptr [_Mem+391766+2*ecx]
	shl       eax,13
	lea       ecx,dword ptr [eax+_Mem+391806]
?live1@14864: ; EBX = ta
	xor       eax,eax
?live1@14880: ; 
	mov       bl,byte ptr [ecx+edx]
	xor       ecx,ecx
?live1@14912: ; EBX = ta
	shl       ebx,2
	mov       al,bl
	mov       word ptr [_Mem+391798],ax
?live1@14928: ; 
	mov       dl,byte ptr [_Mem+391798]
	inc       edx
	mov       cl,dl
	xor       edx,edx
	mov       word ptr [_Mem+391800],cx
	mov       al,byte ptr [_Mem+391798]
	add       al,2
	mov       dl,al
	xor       eax,eax
	mov       word ptr [_Mem+391802],dx
	mov       cl,byte ptr [_Mem+391798]
	add       cl,3
	mov       al,cl
	mov       word ptr [_Mem+391804],ax
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @606
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@606:
@607:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @608
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@608:
@609:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @610
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@610:
@611:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @612
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@612:
@613:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @614
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@614:
@615:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @616
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@616:
@617:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @618
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@618:
@619:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @620
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@620:
@621:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@15072: ; EBX = ta
@412:
	mov       edx,dword ptr [_TU]
	cmp       edx,32768
	jae       short @622
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@622:
	mov       edx,dword ptr [_TU]
	sub       edx,32768
	je        short @628
	dec       edx
	je        @627
	dec       edx
	je        @626
	dec       edx
	je        @625
	jmp       @623
@628:
	mov       ecx,ebx
	and       cl,99
	add       ecx,ecx
	test      bl,-128
	mov       byte ptr [_tmpBYTE],cl
	je        short @629
	xor       eax,eax
	mov       al,byte ptr [_tmpBYTE]
	mov       word ptr [_Mem+391766],ax
	mov       dl,byte ptr [_tmpBYTE]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391768],cx
	mov       al,byte ptr [_tmpBYTE]
	add       al,3
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391770],dx
	mov       cl,byte ptr [_tmpBYTE]
	add       cl,2
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391772],ax
	jmp       short @630
@629:
	mov       dl,byte ptr [_tmpBYTE]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391766],cx
	xor       eax,eax
	mov       al,byte ptr [_tmpBYTE]
	mov       word ptr [_Mem+391768],ax
	mov       dl,byte ptr [_tmpBYTE]
	add       dl,2
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391770],cx
	mov       al,byte ptr [_tmpBYTE]
	add       al,3
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391772],dx
@630:
	test      bl,64
	je        short @631
?live1@15328: ; 
	push      2
	push      2
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @632
@631:
	push      1
	push      0
	push      1
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @632
?live1@15392: ; EBX = ta
@627:
	mov       ecx,ebx
	and       cl,99
	add       ecx,ecx
	test      bl,-128
	mov       byte ptr [_tmpBYTE],cl
	je        short @633
?live1@15456: ; 
	mov       al,byte ptr [_tmpBYTE]
	inc       eax
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391770],dx
	xor       ecx,ecx
	mov       cl,byte ptr [_tmpBYTE]
	mov       word ptr [_Mem+391772],cx
	jmp       @632
@633:
	xor       eax,eax
	mov       al,byte ptr [_tmpBYTE]
	mov       word ptr [_Mem+391770],ax
	mov       dl,byte ptr [_tmpBYTE]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	jmp       @632
?live1@15552: ; EBX = ta
@626:
	mov       eax,ebx
	and       al,99
	add       eax,eax
	mov       byte ptr [_tmpBYTE],al
	test      bl,-128
	setne     dl
	and       edx,1
	mov       cl,byte ptr [_tmpBYTE]
	add       dl,cl
	xor       eax,eax
	mov       al,dl
	mov       word ptr [_Mem+391766],ax
?live1@15584: ; 
	xor       edx,edx
	mov       dl,byte ptr [_Mem+391766]
	mov       word ptr [_Mem+391768],dx
	xor       ecx,ecx
	mov       cl,byte ptr [_Mem+391766]
	mov       word ptr [_Mem+391770],cx
	xor       eax,eax
	mov       al,byte ptr [_Mem+391766]
	mov       word ptr [_Mem+391772],ax
	jmp       @632
?live1@15648: ; EBX = ta
@625:
	mov       edx,ebx
	and       dl,99
	add       edx,edx
	test      bl,-128
	mov       byte ptr [_tmpBYTE],dl
	je        short @634
	mov       cl,byte ptr [_tmpBYTE]
	inc       ecx
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391770],ax
	xor       edx,edx
	mov       dl,byte ptr [_tmpBYTE]
	mov       word ptr [_Mem+391772],dx
	jmp       short @635
@634:
	xor       ecx,ecx
	mov       cl,byte ptr [_tmpBYTE]
	mov       word ptr [_Mem+391770],cx
	mov       al,byte ptr [_tmpBYTE]
	inc       eax
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391772],dx
@635:
	test      bl,64
	je        short @636
?live1@15808: ; 
	push      2
	push      2
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       short @632
@636:
	push      1
	push      0
	push      1
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
@623:
@632:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@15872: ; EBX = ta
@411:
	mov       edx,dword ptr [_TU]
	cmp       edx,24576
	jb        short @638
	mov       eax,dword ptr [_TU]
	cmp       eax,24589
	jbe       short @637
@638:
	mov       edx,dword ptr [_TU]
	cmp       edx,32752
	jb        short @639
	mov       ecx,dword ptr [_TU]
	cmp       ecx,32765
	jbe       short @637
@639:
	mov       eax,dword ptr [_TU]
	cmp       eax,32768
	jb        @641
	mov       edx,dword ptr [_TU]
	cmp       edx,32781
	ja        @641
@637:
	mov       cl,byte ptr [_TU]
	and       cl,15
	mov       byte ptr [_tmpBYTE],cl
	xor       eax,eax
	mov       al,byte ptr [_tmpBYTE]
	cmp       eax,13
	ja        @642
	jmp       dword ptr [@658+4*eax]
@658:
	dd        @657
	dd        @656
	dd        @655
	dd        @654
	dd        @653
	dd        @652
	dd        @651
	dd        @650
	dd        @649
	dd        @648
	dd        @647
	dd        @646
	dd        @645
	dd        @675
@657:
	xor       edx,edx
	mov       dl,bl
	mov       word ptr [_Mem+391790],dx
?live1@15936: ; 
	mov       cx,word ptr [_Mem+391790]
	cmp       cx,word ptr [_Mem+391774]
	je        short @659
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@659:
@660:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @661
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@661:
@662:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @663
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@663:
@664:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @665
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@665:
@666:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @667
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@667:
@668:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @669
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@669:
@670:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @671
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@671:
@672:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @673
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@673:
@674:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @675
?live1@15968: ; EBX = ta
@656:
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391792],ax
?live1@15984: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @676
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@676:
@677:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @678
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@678:
@679:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @680
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@680:
@681:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @682
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@682:
@683:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @684
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@684:
@685:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @686
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@686:
@687:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @688
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@688:
@689:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @690
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@690:
@691:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @675
?live1@16016: ; EBX = ta
@655:
	xor       ecx,ecx
	mov       cl,bl
	mov       word ptr [_Mem+391794],cx
?live1@16032: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @692
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@692:
@693:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @694
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@694:
@695:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @696
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@696:
@697:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @698
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@698:
@699:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @700
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@700:
@701:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @702
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@702:
@703:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @704
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@704:
@705:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @706
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@706:
@707:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @675
?live1@16064: ; EBX = ta
@654:
	xor       edx,edx
	mov       dl,bl
	mov       word ptr [_Mem+391796],dx
?live1@16080: ; 
	mov       cx,word ptr [_Mem+391790]
	cmp       cx,word ptr [_Mem+391774]
	je        short @708
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@708:
@709:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @710
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@710:
@711:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @712
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@712:
@713:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @714
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@714:
@715:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @716
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@716:
@717:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @718
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@718:
@719:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @720
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@720:
@721:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @722
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@722:
@723:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @675
?live1@16112: ; EBX = ta
@653:
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391798],ax
?live1@16128: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @724
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@724:
@725:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @726
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@726:
@727:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @728
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@728:
@729:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @730
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@730:
@731:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @732
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@732:
@733:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @734
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@734:
@735:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @736
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@736:
@737:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @738
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@738:
@739:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @675
?live1@16160: ; EBX = ta
@652:
	xor       ecx,ecx
	mov       cl,bl
	mov       word ptr [_Mem+391800],cx
?live1@16176: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @740
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@740:
@741:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @742
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@742:
@743:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @744
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@744:
@745:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @746
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@746:
@747:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @748
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@748:
@749:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @750
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@750:
@751:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @752
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@752:
@753:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @754
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@754:
@755:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @675
?live1@16208: ; EBX = ta
@651:
	xor       edx,edx
	mov       dl,bl
	mov       word ptr [_Mem+391802],dx
?live1@16224: ; 
	mov       cx,word ptr [_Mem+391790]
	cmp       cx,word ptr [_Mem+391774]
	je        short @756
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@756:
@757:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @758
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@758:
@759:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @760
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@760:
@761:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @762
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@762:
@763:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @764
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@764:
@765:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @766
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@766:
@767:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @768
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@768:
@769:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @770
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@770:
@771:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @675
?live1@16256: ; EBX = ta
@650:
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391804],ax
?live1@16272: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @772
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@772:
@773:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @774
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@774:
@775:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @776
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@776:
@777:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @778
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@778:
@779:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @780
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@780:
@781:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @782
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@782:
@783:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @784
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@784:
@785:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @786
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@786:
@787:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @675
?live1@16304: ; EBX = ta
@649:
	add       ebx,ebx
	mov       cl,byte ptr [_Mem+391762]
	and       bl,cl
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391766],ax
?live1@16320: ; 
	mov       dl,byte ptr [_Mem+391766]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391768],cx
	jmp       @675
?live1@16352: ; EBX = ta
@648:
	sub       bl,1
	jb        short @793
	je        short @792
	dec       bl
	je        short @791
	dec       bl
	je        short @790
	jmp       @675
?live1@16368: ; 
@793:
	push      2
	push      2
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @675
@792:
	push      1
	push      0
	push      1
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       short @675
@791:
	push      0
	push      0
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       short @675
@790:
	push      1
	push      1
	push      1
	push      1
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       short @675
@647:
	test      bl,1
	setne     al
	and       eax,1
	mov       byte ptr [_M16+2],al
	jmp       short @675
?live1@16528: ; EBX = ta
@646:
	and       word ptr [_M16],-256
	xor       edx,edx
	mov       dl,bl
	or        word ptr [_M16],dx
?live1@16560: ; 
	jmp       short @675
?live1@16576: ; EBX = ta
@645:
	and       word ptr [_M16],255
	xor       ecx,ecx
	mov       cl,bl
	shl       ecx,8
	or        word ptr [_M16],cx
?live1@16608: ; 
@642:
@675:
@641:
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@16624: ; EBX = ta
@410:
	mov       edx,dword ptr [_TU]
	cmp       edx,17671
	jg        short @813
	je        @804
	cmp       edx,17667
	jg        short @814
	je        @808
	sub       edx,17150
	je        short @812
	dec       edx
	je        @811
	sub       edx,514
	je        @810
	dec       edx
	je        @809
	jmp       @794
@814:
	sub       edx,17668
	je        @807
	dec       edx
	je        @806
	dec       edx
	je        @805
	jmp       @794
@813:
	add       edx,-17680
	cmp       edx,7
	ja        @794
	jmp       dword ptr [@815+4*edx]
@815:
	dd        @803
	dd        @802
	dd        @801
	dd        @800
	dd        @799
	dd        @798
	dd        @797
	dd        @796
@812:
	test      bl,16
	je        short @816
?live1@16656: ; 
	push      1
	push      1
	push      1
	push      1
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @817
@816:
	push      0
	push      0
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @817
?live1@16720: ; EBX = ta
@811:
	test      bl,16
	je        short @818
?live1@16736: ; 
	push      1
	push      0
	push      1
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @817
@818:
	push      2
	push      2
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @817
@810:
	mov       byte ptr [_M17+2],0
	jmp       @817
?live1@16832: ; EBX = ta
@809:
	and       word ptr [_M17],-256
	xor       ecx,ecx
	mov       cl,bl
	or        word ptr [_M17],cx
?live1@16864: ; 
	jmp       @817
?live1@16880: ; EBX = ta
@808:
	and       word ptr [_M17],255
	xor       eax,eax
	mov       al,bl
	shl       eax,8
	or        word ptr [_M17],ax
?live1@16912: ; 
	mov       byte ptr [_M17+2],1
	jmp       @817
?live1@16944: ; EBX = ta
@807:
	mov       dl,byte ptr [_Mem+391762]
	and       bl,dl
	xor       ecx,ecx
	mov       cl,bl
	mov       word ptr [_Mem+391766],cx
?live1@16960: ; 
	jmp       @817
?live1@16976: ; EBX = ta
@806:
	mov       al,byte ptr [_Mem+391762]
	and       bl,al
	xor       edx,edx
	mov       dl,bl
	mov       word ptr [_Mem+391768],dx
?live1@16992: ; 
	jmp       @817
?live1@17008: ; EBX = ta
@805:
	mov       cl,byte ptr [_Mem+391762]
	and       bl,cl
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391770],ax
?live1@17024: ; 
	jmp       @817
?live1@17040: ; EBX = ta
@804:
	mov       dl,byte ptr [_Mem+391762]
	and       bl,dl
	xor       ecx,ecx
	mov       cl,bl
	mov       word ptr [_Mem+391772],cx
?live1@17056: ; 
	jmp       @817
?live1@17072: ; EBX = ta
@803:
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391790],ax
?live1@17088: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @819
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@819:
@820:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @821
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@821:
@822:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @823
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@823:
@824:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @825
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@825:
@826:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @827
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@827:
@828:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @829
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@829:
@830:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @831
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@831:
@832:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @833
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@833:
@834:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @817
?live1@17120: ; EBX = ta
@802:
	xor       ecx,ecx
	mov       cl,bl
	mov       word ptr [_Mem+391792],cx
?live1@17136: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @835
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@835:
@836:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @837
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@837:
@838:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @839
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@839:
@840:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @841
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@841:
@842:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @843
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@843:
@844:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @845
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@845:
@846:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @847
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@847:
@848:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @849
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@849:
@850:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @817
?live1@17168: ; EBX = ta
@801:
	xor       edx,edx
	mov       dl,bl
	mov       word ptr [_Mem+391794],dx
?live1@17184: ; 
	mov       cx,word ptr [_Mem+391790]
	cmp       cx,word ptr [_Mem+391774]
	je        short @851
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@851:
@852:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @853
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@853:
@854:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @855
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@855:
@856:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @857
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@857:
@858:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @859
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@859:
@860:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @861
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@861:
@862:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @863
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@863:
@864:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @865
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@865:
@866:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @817
?live1@17216: ; EBX = ta
@800:
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391796],ax
?live1@17232: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @867
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@867:
@868:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @869
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@869:
@870:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @871
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@871:
@872:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @873
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@873:
@874:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @875
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@875:
@876:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @877
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@877:
@878:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @879
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@879:
@880:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @881
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@881:
@882:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @817
?live1@17264: ; EBX = ta
@799:
	xor       ecx,ecx
	mov       cl,bl
	mov       word ptr [_Mem+391798],cx
?live1@17280: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @883
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@883:
@884:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @885
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@885:
@886:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @887
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@887:
@888:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @889
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@889:
@890:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @891
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@891:
@892:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @893
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@893:
@894:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @895
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@895:
@896:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @897
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@897:
@898:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @817
?live1@17312: ; EBX = ta
@798:
	xor       edx,edx
	mov       dl,bl
	mov       word ptr [_Mem+391800],dx
?live1@17328: ; 
	mov       cx,word ptr [_Mem+391790]
	cmp       cx,word ptr [_Mem+391774]
	je        short @899
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@899:
@900:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @901
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@901:
@902:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @903
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@903:
@904:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @905
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@905:
@906:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @907
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@907:
@908:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @909
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@909:
@910:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @911
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@911:
@912:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @913
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@913:
@914:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @817
?live1@17360: ; EBX = ta
@797:
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391802],ax
?live1@17376: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @915
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@915:
@916:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @917
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@917:
@918:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @919
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@919:
@920:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @921
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@921:
@922:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @923
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@923:
@924:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @925
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@925:
@926:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @927
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@927:
@928:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @929
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@929:
@930:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @817
?live1@17408: ; EBX = ta
@796:
	xor       ecx,ecx
	mov       cl,bl
	mov       word ptr [_Mem+391804],cx
?live1@17424: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @931
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@931:
@932:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @933
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@933:
@934:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @935
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@935:
@936:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @937
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@937:
@938:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @939
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@939:
@940:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @941
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@941:
@942:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @943
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@943:
@944:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @945
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@945:
@946:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
@794:
@817:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@17456: ; EBX = ta
@409:
	mov       ecx,dword ptr [_TU]
	and       ecx,61440
	sub       ecx,32768
	je        short @951
	sub       ecx,4096
	je        short @950
	sub       ecx,4096
	je        @949
	jmp       @947
@951:
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391766],ax
?live1@17488: ; 
	jmp       @952
?live1@17504: ; EBX = ta
@950:
	sub       bl,1
	jb        short @958
	je        short @957
	dec       bl
	je        short @956
	dec       bl
	je        short @955
	jmp       @952
?live1@17520: ; 
@958:
	push      1
	push      0
	push      1
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @952
@957:
	push      2
	push      2
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @952
@956:
	push      1
	push      1
	push      1
	push      1
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @952
@955:
	push      0
	push      0
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @952
@949:
	xor       edx,edx
	mov       dl,bl
	mov       word ptr [_Mem+391768],dx
	jmp       @952
?live1@17680: ; EBX = ta
@947:
	mov       ecx,dword ptr [_TU]
	mov       eax,dword ptr [_TU]
	add       ecx,4096
	and       eax,2
	and       ecx,12288
	shr       eax,1
	shr       ecx,11
	or        cl,al
	mov       byte ptr [_tmp],cl
	test      byte ptr [_TU],1
	je        short @959
	xor       edx,edx
	xor       eax,eax
	mov       dl,byte ptr [_tmp]
	xor       ecx,ecx
	shl       ebx,4
	and       word ptr [_Mem+391790+2*edx],15
	mov       cl,bl
	mov       al,byte ptr [_tmp]
	or        word ptr [_Mem+391790+2*eax],cx
?live1@17808: ; 
	jmp       short @960
?live1@17824: ; EBX = ta
@959:
	xor       edx,edx
	xor       eax,eax
	mov       dl,byte ptr [_tmp]
	xor       ecx,ecx
	mov       cl,bl
	and       word ptr [_Mem+391790+2*edx],240
	mov       al,byte ptr [_tmp]
	or        word ptr [_Mem+391790+2*eax],cx
?live1@17920: ; 
@960:
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @961
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@961:
@962:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @963
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@963:
@964:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @965
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@965:
@966:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @967
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@967:
@968:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @969
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@969:
@970:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @971
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@971:
@972:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @973
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@973:
@974:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @975
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@975:
@976:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
@952:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@17952: ; EBX = ta
@408:
	mov       edx,dword ptr [_TU]
	cmp       edx,32768
	jae       short @977
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@977:
	mov       edx,dword ptr [_TU]
	cmp       edx,32768
	jne       short @978
	add       ebx,ebx
	mov       cl,byte ptr [_Mem+391762]
	and       bl,cl
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391766],ax
?live1@18000: ; 
	mov       dl,byte ptr [_Mem+391766]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391768],cx
	jmp       @979
@978:
	mov       eax,dword ptr [_TU]
	cmp       eax,45059
	jne       @980
?live1@18032: ; EBX = ta
	xor       edx,edx
	mov       dl,bl
	and       edx,12
	sub       edx,1
	jb        short @986
	sub       edx,3
	je        short @985
	sub       edx,4
	je        short @984
	sub       edx,4
	je        short @983
	jmp       @979
?live1@18048: ; 
@986:
	push      1
	push      0
	push      1
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @979
@985:
	push      2
	push      2
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @979
@984:
	push      0
	push      0
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @979
@983:
	push      1
	push      1
	push      1
	push      1
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       @979
@980:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,49152
	jne       short @987
?live1@18192: ; EBX = ta
	mov       al,byte ptr [_Mem+391762]
	and       bl,al
	xor       edx,edx
	mov       dl,bl
	mov       word ptr [_Mem+391770],dx
?live1@18208: ; 
	jmp       @979
@987:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,53248
	jne       @988
?live1@18224: ; EBX = ta
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391790],ax
?live1@18240: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @989
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@989:
@990:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @991
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@991:
@992:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @993
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@993:
@994:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @995
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@995:
@996:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @997
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@997:
@998:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @999
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@999:
@1000:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1001
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1001:
@1002:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1003
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1003:
@1004:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @979
@988:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,53249
	jne       @1005
?live1@18272: ; EBX = ta
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391792],ax
?live1@18288: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1006
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1006:
@1007:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1008
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1008:
@1009:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1010
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1010:
@1011:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1012
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1012:
@1013:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1014
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1014:
@1015:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1016
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1016:
@1017:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1018
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1018:
@1019:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1020
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1020:
@1021:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @979
@1005:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,53250
	jne       @1022
?live1@18320: ; EBX = ta
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391794],ax
?live1@18336: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1023
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1023:
@1024:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1025
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1025:
@1026:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1027
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1027:
@1028:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1029
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1029:
@1030:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1031
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1031:
@1032:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1033
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1033:
@1034:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1035
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1035:
@1036:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1037
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1037:
@1038:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @979
@1022:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,53251
	jne       @1039
?live1@18368: ; EBX = ta
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391796],ax
?live1@18384: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1040
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1040:
@1041:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1042
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1042:
@1043:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1044
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1044:
@1045:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1046
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1046:
@1047:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1048
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1048:
@1049:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1050
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1050:
@1051:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1052
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1052:
@1053:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1054
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1054:
@1055:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @979
@1039:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,57344
	jne       @1056
?live1@18416: ; EBX = ta
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391798],ax
?live1@18432: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1057
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1057:
@1058:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1059
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1059:
@1060:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1061
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1061:
@1062:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1063
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1063:
@1064:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1065
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1065:
@1066:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1067
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1067:
@1068:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1069
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1069:
@1070:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1071
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1071:
@1072:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @979
@1056:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,57345
	jne       @1073
?live1@18464: ; EBX = ta
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391800],ax
?live1@18480: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1074
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1074:
@1075:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1076
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1076:
@1077:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1078
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1078:
@1079:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1080
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1080:
@1081:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1082
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1082:
@1083:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1084
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1084:
@1085:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1086
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1086:
@1087:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1088
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1088:
@1089:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @979
@1073:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,57346
	jne       @1090
?live1@18512: ; EBX = ta
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391802],ax
?live1@18528: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1091
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1091:
@1092:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1093
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1093:
@1094:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1095
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1095:
@1096:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1097
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1097:
@1098:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1099
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1099:
@1100:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1101
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1101:
@1102:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1103
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1103:
@1104:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1105
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1105:
@1106:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @979
@1090:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,57347
	jne       @1107
?live1@18560: ; EBX = ta
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391804],ax
?live1@18576: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1108
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1108:
@1109:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1110
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1110:
@1111:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1112
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1112:
@1113:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1114
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1114:
@1115:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1116
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1116:
@1117:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1118
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1118:
@1119:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1120
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1120:
@1121:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1122
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1122:
@1123:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       short @979
@1107:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,61440
	jne       short @1124
?live1@18608: ; EBX = ta
	mov       byte ptr [_M24+1],bl
?live1@18624: ; 
	jmp       short @979
@1124:
	mov       eax,dword ptr [_TU]
	cmp       eax,61441
	jne       short @1125
?live1@18640: ; EBX = ta
	test      bl,2
	setne     dl
	and       edx,1
	and       bl,1
	mov       byte ptr [_M24+3],dl
	mov       byte ptr [_M24],bl
?live1@18704: ; 
	mov       cl,byte ptr [_M24+3]
	test      cl,cl
	je        short @979
	mov       al,byte ptr [_M24+1]
	mov       byte ptr [_M24+2],al
	jmp       short @979
@1125:
	mov       edx,dword ptr [_TU]
	cmp       edx,61442
	jne       short @1127
	mov       cl,byte ptr [_M24]
	test      cl,cl
	setne     al
	and       eax,1
	mov       byte ptr [_M24+3],al
@1127:
@979:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@18768: ; EBX = ta
@407:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,32765
	jae       short @1128
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@1128:
	mov       edx,dword ptr [_TU]
	cmp       edx,32765
	je        short @1130
	mov       ecx,dword ptr [_TU]
	cmp       ecx,32768
	jb        short @1129
@1130:
	mov       eax,ebx
	shl       eax,2
	mov       dl,byte ptr [_Mem+391762]
	and       al,dl
	xor       ecx,ecx
	mov       cl,al
	mov       word ptr [_Mem+391766],cx
	mov       al,byte ptr [_Mem+391766]
	inc       eax
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391768],dx
	call      @UpdateGGCodes$qqrv
@1129:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,32766
	jne       @1131
	mov       eax,ebx
	shl       eax,2
	mov       dl,byte ptr [_Mem+391764]
	and       al,dl
	xor       ecx,ecx
	mov       cl,al
	mov       word ptr [_Mem+391790],cx
	mov       al,byte ptr [_Mem+391790]
	inc       eax
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391792],dx
	mov       cl,byte ptr [_Mem+391790]
	add       cl,2
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391794],ax
	mov       dl,byte ptr [_Mem+391790]
	add       dl,3
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391796],cx
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @1132
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1132:
@1133:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @1134
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1134:
@1135:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @1136
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1136:
@1137:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @1138
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1138:
@1139:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @1140
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1140:
@1141:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @1142
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1142:
@1143:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @1144
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1144:
@1145:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @1146
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1146:
@1147:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
@1131:
	mov       edx,dword ptr [_TU]
	cmp       edx,32767
	jne       @1148
	shl       ebx,2
	mov       cl,byte ptr [_Mem+391764]
	and       bl,cl
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391798],ax
?live1@18960: ; 
	mov       dl,byte ptr [_Mem+391798]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391800],cx
	mov       al,byte ptr [_Mem+391798]
	add       al,2
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391802],dx
	mov       cl,byte ptr [_Mem+391798]
	add       cl,3
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391804],ax
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1149
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1149:
@1150:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1151
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1151:
@1152:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1153
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1153:
@1154:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1155
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1155:
@1156:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1157
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1157:
@1158:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1159
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1159:
@1160:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1161
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1161:
@1162:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1163
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1163:
@1164:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
@1148:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@19024: ; EBX = ta
@406:
	mov       edx,dword ptr [_TU]
	cmp       edx,32768
	jae       short @1165
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@1165:
	mov       edx,dword ptr [_TU]
	cmp       edx,32768
	jne       short @1166
	mov       ecx,ebx
	and       cl,15
	test      bl,64
	setne     al
	and       eax,1
	mov       byte ptr [_MMC3],cl
	test      bl,-128
	setne     dl
	and       edx,1
	mov       byte ptr [_MMC3+4],al
	mov       byte ptr [_MMC3+5],dl
?live1@19152: ; 
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@19168: ; EBX = ta
@1166:
	mov       edx,dword ptr [_TU]
	cmp       edx,32769
	jne       @1167
	xor       eax,eax
	mov       al,byte ptr [_MMC3]
	cmp       eax,15
	ja        @1168
	jmp       dword ptr [@1181+4*eax]
@1181:
	dd        @1180
	dd        @1179
	dd        @1178
	dd        @1177
	dd        @1176
	dd        @1175
	dd        @1174
	dd        @1173
	dd        @1172
	dd        @1171
	dd        @1168
	dd        @1168
	dd        @1168
	dd        @1168
	dd        @1168
	dd        @1170
@1180:
	mov       dl,byte ptr [_MMC3+5]
	xor       ecx,ecx
	shl       edx,2
	mov       cl,bl
	mov       byte ptr [_tmpBYTE],dl
	xor       eax,eax
	and       cx,word ptr [_Mem+391764]
	mov       al,byte ptr [_tmpBYTE]
	and       cx,254
?live1@19296: ; 
	xor       edx,edx
?live1@19312: ; EBX = ta
	mov       word ptr [_Mem+391790+2*eax],cx
?live1@19328: ; 
	xor       eax,eax
	mov       dl,byte ptr [_tmpBYTE]
	mov       al,byte ptr [_tmpBYTE]
	mov       cx,word ptr [_Mem+391790+2*edx]
	inc       ecx
	mov       word ptr [_Mem+391792+2*eax],cx
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1182
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1182:
@1183:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1184
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1184:
@1185:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1186
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1186:
@1187:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1188
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1188:
@1189:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1190
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1190:
@1191:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1192
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1192:
@1193:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1194
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1194:
@1195:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1196
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1196:
@1197:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@19376: ; EBX = ta
@1179:
	mov       dl,byte ptr [_MMC3+5]
	xor       eax,eax
	shl       edx,2
	mov       al,bl
	add       dl,2
?live1@19456: ; 
	xor       ecx,ecx
?live1@19472: ; EBX = ta
	mov       byte ptr [_tmpBYTE],dl
	xor       edx,edx
	and       ax,word ptr [_Mem+391764]
	mov       dl,byte ptr [_tmpBYTE]
	and       ax,254
	mov       word ptr [_Mem+391790+2*edx],ax
?live1@19504: ; 
	xor       edx,edx
	mov       cl,byte ptr [_tmpBYTE]
	mov       dl,byte ptr [_tmpBYTE]
	mov       ax,word ptr [_Mem+391790+2*ecx]
	inc       eax
	mov       word ptr [_Mem+391792+2*edx],ax
	mov       cx,word ptr [_Mem+391790]
	cmp       cx,word ptr [_Mem+391774]
	je        short @1198
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1198:
@1199:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @1200
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1200:
@1201:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @1202
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1202:
@1203:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @1204
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1204:
@1205:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @1206
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1206:
@1207:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @1208
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1208:
@1209:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @1210
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1210:
@1211:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @1212
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1212:
@1213:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@19552: ; EBX = ta
@1178:
	xor       edx,edx
	mov       dl,bl
	and       dx,word ptr [_Mem+391764]
	movsx     ecx,byte ptr [_MMC3+5]
	shl       ecx,2
	xor       ecx,4
	mov       word ptr [_Mem+391790+2*ecx],dx
?live1@19568: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @1214
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1214:
@1215:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @1216
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1216:
@1217:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @1218
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1218:
@1219:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @1220
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1220:
@1221:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @1222
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1222:
@1223:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @1224
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1224:
@1225:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @1226
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1226:
@1227:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @1228
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1228:
@1229:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@19600: ; EBX = ta
@1177:
	xor       ecx,ecx
	mov       cl,bl
	and       cx,word ptr [_Mem+391764]
	movsx     eax,byte ptr [_MMC3+5]
	shl       eax,2
	xor       eax,5
	mov       word ptr [_Mem+391790+2*eax],cx
?live1@19616: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1230
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1230:
@1231:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1232
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1232:
@1233:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1234
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1234:
@1235:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1236
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1236:
@1237:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1238
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1238:
@1239:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1240
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1240:
@1241:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1242
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1242:
@1243:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1244
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1244:
@1245:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@19648: ; EBX = ta
@1176:
	xor       edx,edx
	mov       dl,bl
	and       dx,word ptr [_Mem+391764]
	movsx     eax,byte ptr [_MMC3+5]
	shl       eax,2
	xor       eax,6
	mov       word ptr [_Mem+391790+2*eax],dx
?live1@19664: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1246
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1246:
@1247:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1248
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1248:
@1249:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1250
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1250:
@1251:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1252
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1252:
@1253:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1254
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1254:
@1255:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1256
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1256:
@1257:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1258
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1258:
@1259:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1260
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1260:
@1261:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@19696: ; EBX = ta
@1175:
	xor       edx,edx
	mov       dl,bl
	and       dx,word ptr [_Mem+391764]
	movsx     eax,byte ptr [_MMC3+5]
	shl       eax,2
	xor       eax,7
	mov       word ptr [_Mem+391790+2*eax],dx
?live1@19712: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1262
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1262:
@1263:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1264
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1264:
@1265:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1266
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1266:
@1267:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1268
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1268:
@1269:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1270
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1270:
@1271:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1272
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1272:
@1273:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1274
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1274:
@1275:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1276
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1276:
@1277:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@19744: ; EBX = ta
@1174:
	mov       dl,byte ptr [_Mem+391762]
	and       bl,dl
	xor       eax,eax
	movsx     edx,byte ptr [_MMC3+4]
	mov       al,bl
	mov       word ptr [_Mem+391766+2*edx],ax
?live1@19760: ; 
	call      @UpdateGGCodes$qqrv
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@19792: ; EBX = ta
@1173:
	mov       dl,byte ptr [_Mem+391762]
	and       bl,dl
	xor       eax,eax
	movsx     edx,byte ptr [_MMC3+4]
	mov       al,bl
	mov       word ptr [_Mem+391768+2*edx],ax
?live1@19808: ; 
	call      @UpdateGGCodes$qqrv
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
?live1@19840: ; EBX = ta
@1172:
	xor       edx,edx
	mov       dl,bl
	and       dx,word ptr [_Mem+391764]
	mov       word ptr [_Mem+391792],dx
?live1@19856: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @1278
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1278:
@1279:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @1280
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1280:
@1281:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @1282
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1282:
@1283:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @1284
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1284:
@1285:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @1286
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1286:
@1287:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @1288
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1288:
@1289:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @1290
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1290:
@1291:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @1292
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1292:
@1293:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@19888: ; EBX = ta
@1171:
	xor       ecx,ecx
	mov       cl,bl
	and       cx,word ptr [_Mem+391764]
	mov       word ptr [_Mem+391796],cx
?live1@19904: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @1294
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1294:
@1295:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @1296
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1296:
@1297:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @1298
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1298:
@1299:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @1300
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1300:
@1301:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @1302
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1302:
@1303:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @1304
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1304:
@1305:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @1306
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1306:
@1307:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @1308
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1308:
@1309:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@19936: ; EBX = ta
@1170:
	mov       cl,byte ptr [_MMC3+4]
	test      cl,cl
	je        short @1310
	mov       al,byte ptr [_Mem+391762]
	and       bl,al
	xor       edx,edx
	mov       dl,bl
	mov       word ptr [_Mem+391766],dx
?live1@19968: ; 
	jmp       short @1311
?live1@19984: ; EBX = ta
@1310:
	mov       cl,byte ptr [_Mem+391762]
	and       bl,cl
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391770],ax
?live1@20000: ; 
@1311:
	call      @UpdateGGCodes$qqrv
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@20032: ; EBX = ta
@1168:
@1167:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,40960
	jne       short @1313
	test      bl,1
	je        short @1314
?live1@20064: ; 
	push      2
	push      2
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       short @1315
@1314:
	push      1
	push      0
	push      1
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
@1315:
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@1313:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@20144: ; EBX = ta
@405:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,32768
	jae       short @1316
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@1316:
	xor       edx,edx
	mov       dl,bl
	and       edx,240
	sar       edx,2
	mov       cl,byte ptr [_Mem+391762]
	and       dl,cl
	xor       eax,eax
	mov       al,dl
	mov       word ptr [_Mem+391766],ax
	mov       dl,byte ptr [_Mem+391766]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391768],cx
	mov       al,byte ptr [_Mem+391766]
	add       al,2
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391770],dx
	mov       cl,byte ptr [_Mem+391766]
	add       cl,3
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391772],ax
	and       bl,15
	shl       ebx,3
	mov       dl,byte ptr [_Mem+391764]
	and       bl,dl
	xor       ecx,ecx
	mov       cl,bl
	mov       word ptr [_Mem+391790],cx
?live1@20224: ; 
	mov       al,byte ptr [_Mem+391790]
	inc       eax
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391792],dx
	mov       cl,byte ptr [_Mem+391790]
	add       cl,2
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391794],ax
	mov       dl,byte ptr [_Mem+391790]
	add       dl,3
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391796],cx
	mov       al,byte ptr [_Mem+391790]
	add       al,4
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391798],dx
	mov       cl,byte ptr [_Mem+391790]
	add       cl,5
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391800],ax
	mov       dl,byte ptr [_Mem+391790]
	add       dl,6
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391802],cx
	mov       al,byte ptr [_Mem+391790]
	add       al,7
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391804],dx
	mov       cx,word ptr [_Mem+391790]
	cmp       cx,word ptr [_Mem+391774]
	je        short @1317
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1317:
@1318:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @1319
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1319:
@1320:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @1321
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1321:
@1322:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @1323
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1323:
@1324:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @1325
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1325:
@1326:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @1327
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1327:
@1328:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @1329
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1329:
@1330:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @1331
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1331:
@1332:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	call      @UpdateGGCodes$qqrv
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@20336: ; EBX = ta
@404:
	mov       edx,dword ptr [_TU]
	cmp       edx,32768
	jae       short @1333
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
@1333:
	mov       edx,dword ptr [_TU]
	cmp       edx,49152
	jb        short @1334
	add       ebx,ebx
	mov       al,byte ptr [_Mem+391762]
	and       bl,al
	xor       edx,edx
	mov       dl,bl
	mov       word ptr [_Mem+391766],dx
?live1@20384: ; 
	mov       cl,byte ptr [_Mem+391766]
	inc       ecx
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391768],ax
	call      @UpdateGGCodes$qqrv
@1334:
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	mov       eax,edx
	jmp       @361
?live1@20432: ; EBX = ta
@403:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,32768
	jae       short @1335
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
@1335:
	mov       edx,dword ptr [_TU]
	and       edx,65532
	cmp       edx,32768
	jne       short @1336
	mov       cl,byte ptr [_Mem+391762]
	xor       eax,eax
	and       bl,cl
	mov       edx,dword ptr [_TU]
	and       edx,3
	mov       al,bl
	mov       word ptr [_Mem+391766+2*edx],ax
?live1@20480: ; 
	call      @UpdateGGCodes$qqrv
	jmp       @1337
@1336:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,36864
	jne       @1339
?live1@20512: ; EBX = ta
	mov       al,byte ptr [_M90]
	test      al,al
	jne       short @1340
	xor       edx,edx
	mov       dl,bl
	and       dx,127
	shl       edx,2
	mov       word ptr [_Mem+391790],dx
?live1@20544: ; 
	mov       cx,word ptr [_Mem+391790]
	inc       ecx
	mov       word ptr [_Mem+391792],cx
	mov       ax,word ptr [_Mem+391790]
	add       ax,2
	mov       word ptr [_Mem+391794],ax
	mov       dx,word ptr [_Mem+391790]
	add       dx,3
	mov       word ptr [_Mem+391796],dx
	jmp       short @1341
?live1@20608: ; EBX = ta
@1340:
	mov       cx,word ptr [_Mem+391790]
	xor       eax,eax
	and       cx,384
	mov       al,bl
	or        cx,ax
	mov       word ptr [_Mem+391790],cx
?live1@20624: ; 
@1341:
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1342
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1342:
@1343:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1344
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1344:
@1345:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1346
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1346:
@1347:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1348
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1348:
@1349:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1350
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1350:
@1351:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1352
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1352:
@1353:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1354
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1354:
@1355:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1356
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1356:
@1357:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @1337
@1339:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,36865
	jne       @1358
?live1@20656: ; EBX = ta
	mov       al,byte ptr [_M90]
	test      al,al
	jne       @1337
	mov       dx,word ptr [_Mem+391792]
	xor       ecx,ecx
	and       dx,384
	mov       cl,bl
	or        dx,cx
	mov       word ptr [_Mem+391792],dx
?live1@20688: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @1360
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1360:
@1361:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @1362
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1362:
@1363:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @1364
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1364:
@1365:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @1366
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1366:
@1367:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @1368
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1368:
@1369:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @1370
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1370:
@1371:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @1372
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1372:
@1373:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @1374
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1374:
@1375:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @1337
@1358:
	mov       edx,dword ptr [_TU]
	cmp       edx,36866
	jne       @1376
?live1@20720: ; EBX = ta
	mov       cl,byte ptr [_M90]
	test      cl,cl
	jne       @1337
	mov       ax,word ptr [_Mem+391794]
	xor       edx,edx
	and       ax,384
	mov       dl,bl
	or        ax,dx
	mov       word ptr [_Mem+391794],ax
?live1@20752: ; 
	mov       cx,word ptr [_Mem+391790]
	cmp       cx,word ptr [_Mem+391774]
	je        short @1378
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1378:
@1379:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @1380
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1380:
@1381:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @1382
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1382:
@1383:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @1384
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1384:
@1385:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @1386
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1386:
@1387:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @1388
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1388:
@1389:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @1390
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1390:
@1391:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @1392
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1392:
@1393:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @1337
@1376:
	mov       eax,dword ptr [_TU]
	cmp       eax,36867
	jne       @1394
?live1@20784: ; EBX = ta
	mov       dl,byte ptr [_M90]
	test      dl,dl
	jne       @1337
	mov       cx,word ptr [_Mem+391796]
	xor       eax,eax
	and       cx,384
	mov       al,bl
	or        cx,ax
	mov       word ptr [_Mem+391796],cx
?live1@20816: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1396
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1396:
@1397:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1398
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1398:
@1399:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1400
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1400:
@1401:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1402
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1402:
@1403:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1404
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1404:
@1405:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1406
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1406:
@1407:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1408
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1408:
@1409:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1410
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1410:
@1411:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @1337
@1394:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,36868
	jne       @1413
?live1@20848: ; EBX = ta
	mov       eax,offset _M90
	test      eax,eax
	jne       short @1414
	xor       edx,edx
	mov       dl,bl
	and       dx,127
	shl       edx,2
	mov       word ptr [_Mem+391798],dx
?live1@20880: ; 
	mov       cx,word ptr [_Mem+391798]
	inc       ecx
	mov       word ptr [_Mem+391800],cx
	mov       ax,word ptr [_Mem+391798]
	add       ax,2
	mov       word ptr [_Mem+391802],ax
	mov       dx,word ptr [_Mem+391798]
	add       dx,3
	mov       word ptr [_Mem+391804],dx
	jmp       short @1415
?live1@20944: ; EBX = ta
@1414:
	mov       cx,word ptr [_Mem+391798]
	xor       eax,eax
	and       cx,384
	mov       al,bl
	or        cx,ax
	mov       word ptr [_Mem+391798],cx
?live1@20960: ; 
@1415:
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1416
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1416:
@1417:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1418
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1418:
@1419:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1420
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1420:
@1421:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1422
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1422:
@1423:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1424
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1424:
@1425:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1426
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1426:
@1427:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1428
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1428:
@1429:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1430
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1430:
@1431:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @1337
@1413:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,36869
	jne       @1432
?live1@20992: ; EBX = ta
	mov       al,byte ptr [_M90+1]
	test      al,al
	jne       @1337
	mov       dx,word ptr [_Mem+391800]
	xor       ecx,ecx
	and       dx,384
	mov       cl,bl
	or        dx,cx
	mov       word ptr [_Mem+391800],dx
?live1@21024: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @1434
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1434:
@1435:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @1436
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1436:
@1437:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @1438
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1438:
@1439:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @1440
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1440:
@1441:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @1442
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1442:
@1443:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @1444
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1444:
@1445:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @1446
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1446:
@1447:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @1448
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1448:
@1449:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @1337
@1432:
	mov       edx,dword ptr [_TU]
	cmp       edx,36870
	jne       @1450
?live1@21056: ; EBX = ta
	mov       cl,byte ptr [_M90+1]
	test      cl,cl
	jne       @1337
	mov       ax,word ptr [_Mem+391802]
	xor       edx,edx
	and       ax,384
	mov       dl,bl
	or        ax,dx
	mov       word ptr [_Mem+391802],ax
?live1@21088: ; 
	mov       cx,word ptr [_Mem+391790]
	cmp       cx,word ptr [_Mem+391774]
	je        short @1452
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1452:
@1453:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @1454
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1454:
@1455:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @1456
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1456:
@1457:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @1458
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1458:
@1459:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @1460
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1460:
@1461:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @1462
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1462:
@1463:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @1464
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1464:
@1465:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @1466
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1466:
@1467:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @1337
@1450:
	mov       eax,dword ptr [_TU]
	cmp       eax,36871
	jne       @1468
?live1@21120: ; EBX = ta
	mov       dl,byte ptr [_M90+1]
	test      dl,dl
	jne       @1337
	mov       cx,word ptr [_Mem+391804]
	xor       eax,eax
	and       cx,384
	mov       al,bl
	or        cx,ax
	mov       word ptr [_Mem+391804],cx
?live1@21152: ; 
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1470
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1470:
@1471:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1472
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1472:
@1473:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1474
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1474:
@1475:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1476
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1476:
@1477:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1478
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1478:
@1479:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1480
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1480:
@1481:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1482
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1482:
@1483:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1484
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1484:
@1485:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @1337
@1468:
	mov       ecx,dword ptr [_TU]
	and       ecx,65528
	cmp       ecx,45056
	jne       @1486
?live1@21184: ; EBX = ta
	test      byte ptr [_TU],4
	setne     al
	and       eax,1
	mov       dl,byte ptr [eax+_M90]
	test      dl,dl
	jne       @1337
	mov       ecx,dword ptr [_TU]
	xor       edx,edx
	and       ecx,7
	mov       dl,bl
	and       dx,3
	mov       ax,word ptr [_Mem+391790+2*ecx]
	mov       ecx,dword ptr [_TU]
	and       ax,127
	and       ecx,7
	shl       edx,7
	or        ax,dx
	mov       word ptr [_Mem+391790+2*ecx],ax
?live1@21216: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @1488
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1488:
@1489:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @1490
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1490:
@1491:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @1492
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1492:
@1493:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @1494
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1494:
@1495:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @1496
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1496:
@1497:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @1498
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1498:
@1499:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @1500
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1500:
@1501:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @1502
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1502:
@1503:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       short @1337
@1486:
	mov       edx,dword ptr [_TU]
	cmp       edx,49152
	jne       short @1504
?live1@21248: ; EBX = ta
	mov       byte ptr [_M90+3],bl
?live1@21264: ; 
	jmp       short @1337
@1504:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,49153
	jne       short @1505
?live1@21280: ; EBX = ta
	mov       byte ptr [_M90+4],bl
?live1@21296: ; 
	jmp       short @1337
@1505:
	mov       eax,dword ptr [_TU]
	cmp       eax,49154
	jne       short @1506
	mov       byte ptr [_M90+2],0
	mov       dl,byte ptr [_M90+4]
	mov       byte ptr [_M90+3],dl
	jmp       short @1337
@1506:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,49155
	jne       short @1507
	mov       byte ptr [_M90+2],1
@1507:
@1337:
	mov       eax,dword ptr [ebp-40]
	mov       dword ptr fs:[0],eax
	jmp       @361
?live1@21392: ; EBX = ta
@402:
	mov       edx,dword ptr [_TU]
	cmp       edx,24576
	jae       short @1508
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @361
@1508:
	mov       edx,dword ptr [_TU]
	and       edx,61443
	cmp       edx,24576
	jne       @1509
	xor       eax,eax
	mov       al,bl
	add       eax,eax
	and       ax,word ptr [_Mem+391764]
	mov       word ptr [_Mem+391790],ax
?live1@21440: ; 
	mov       dx,word ptr [_Mem+391790]
	inc       edx
	mov       word ptr [_Mem+391792],dx
	mov       cx,word ptr [_Mem+391790]
	cmp       cx,word ptr [_Mem+391774]
	je        short @1510
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1510:
@1511:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @1512
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1512:
@1513:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @1514
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1514:
@1515:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @1516
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1516:
@1517:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @1518
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1518:
@1519:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @1520
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1520:
@1521:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @1522
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1522:
@1523:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @1524
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1524:
@1525:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @1526
@1509:
	mov       eax,dword ptr [_TU]
	and       eax,61443
	cmp       eax,24577
	jne       @1527
?live1@21488: ; EBX = ta
	xor       edx,edx
	mov       dl,bl
	add       edx,edx
	and       dx,word ptr [_Mem+391764]
	mov       word ptr [_Mem+391794],dx
?live1@21504: ; 
	mov       cx,word ptr [_Mem+391794]
	inc       ecx
	mov       word ptr [_Mem+391796],cx
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @1528
	movsx     edx,word ptr [_Mem+391790]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1528:
@1529:
	mov       cx,word ptr [_Mem+391792]
	cmp       cx,word ptr [_Mem+391776]
	je        short @1530
	movsx     eax,word ptr [_Mem+391792]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1530:
@1531:
	mov       dx,word ptr [_Mem+391794]
	cmp       dx,word ptr [_Mem+391778]
	je        short @1532
	movsx     ecx,word ptr [_Mem+391794]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1532:
@1533:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @1534
	movsx     edx,word ptr [_Mem+391796]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1534:
@1535:
	mov       cx,word ptr [_Mem+391798]
	cmp       cx,word ptr [_Mem+391782]
	je        short @1536
	movsx     eax,word ptr [_Mem+391798]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1536:
@1537:
	mov       dx,word ptr [_Mem+391800]
	cmp       dx,word ptr [_Mem+391784]
	je        short @1538
	movsx     ecx,word ptr [_Mem+391800]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1538:
@1539:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @1540
	movsx     edx,word ptr [_Mem+391802]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1540:
@1541:
	mov       cx,word ptr [_Mem+391804]
	cmp       cx,word ptr [_Mem+391788]
	je        short @1542
	movsx     eax,word ptr [_Mem+391804]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1542:
@1543:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @1526
@1527:
	mov       edx,dword ptr [_TU]
	and       edx,61443
	cmp       edx,24578
	jne       @1544
?live1@21552: ; EBX = ta
	xor       ecx,ecx
	mov       cl,bl
	add       ecx,ecx
	and       cx,word ptr [_Mem+391764]
	mov       word ptr [_Mem+391798],cx
?live1@21568: ; 
	mov       ax,word ptr [_Mem+391798]
	inc       eax
	mov       word ptr [_Mem+391800],ax
	mov       dx,word ptr [_Mem+391790]
	cmp       dx,word ptr [_Mem+391774]
	je        short @1545
	movsx     ecx,word ptr [_Mem+391790]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1545:
@1546:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @1547
	movsx     edx,word ptr [_Mem+391792]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1547:
@1548:
	mov       cx,word ptr [_Mem+391794]
	cmp       cx,word ptr [_Mem+391778]
	je        short @1549
	movsx     eax,word ptr [_Mem+391794]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1549:
@1550:
	mov       dx,word ptr [_Mem+391796]
	cmp       dx,word ptr [_Mem+391780]
	je        short @1551
	movsx     ecx,word ptr [_Mem+391796]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1551:
@1552:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @1553
	movsx     edx,word ptr [_Mem+391798]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1553:
@1554:
	mov       cx,word ptr [_Mem+391800]
	cmp       cx,word ptr [_Mem+391784]
	je        short @1555
	movsx     eax,word ptr [_Mem+391800]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1555:
@1556:
	mov       dx,word ptr [_Mem+391802]
	cmp       dx,word ptr [_Mem+391786]
	je        short @1557
	movsx     ecx,word ptr [_Mem+391802]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1557:
@1558:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @1559
	movsx     edx,word ptr [_Mem+391804]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1559:
@1560:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @1526
@1544:
	mov       ecx,dword ptr [_TU]
	and       ecx,61443
	cmp       ecx,24579
	jne       @1561
?live1@21616: ; EBX = ta
	xor       eax,eax
	mov       al,bl
	add       eax,eax
	and       ax,word ptr [_Mem+391764]
	mov       word ptr [_Mem+391802],ax
?live1@21632: ; 
	mov       dx,word ptr [_Mem+391802]
	inc       edx
	mov       word ptr [_Mem+391804],dx
	mov       cx,word ptr [_Mem+391790]
	cmp       cx,word ptr [_Mem+391774]
	je        short @1562
	movsx     eax,word ptr [_Mem+391790]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@1562:
@1563:
	mov       dx,word ptr [_Mem+391792]
	cmp       dx,word ptr [_Mem+391776]
	je        short @1564
	movsx     ecx,word ptr [_Mem+391792]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@1564:
@1565:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @1566
	movsx     edx,word ptr [_Mem+391794]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@1566:
@1567:
	mov       cx,word ptr [_Mem+391796]
	cmp       cx,word ptr [_Mem+391780]
	je        short @1568
	movsx     eax,word ptr [_Mem+391796]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@1568:
@1569:
	mov       dx,word ptr [_Mem+391798]
	cmp       dx,word ptr [_Mem+391782]
	je        short @1570
	movsx     ecx,word ptr [_Mem+391798]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@1570:
@1571:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @1572
	movsx     edx,word ptr [_Mem+391800]
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@1572:
@1573:
	mov       cx,word ptr [_Mem+391802]
	cmp       cx,word ptr [_Mem+391786]
	je        short @1574
	movsx     eax,word ptr [_Mem+391802]
	shl       eax,10
	push      1024
	add       eax,offset _Mem+1440382
	push      eax
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@1574:
@1575:
	mov       dx,word ptr [_Mem+391804]
	cmp       dx,word ptr [_Mem+391788]
	je        short @1576
	movsx     ecx,word ptr [_Mem+391804]
	shl       ecx,10
	push      1024
	add       ecx,offset _Mem+1440382
	push      ecx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@1576:
@1577:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	jmp       @1526
@1561:
	mov       eax,dword ptr [_TU]
	and       eax,61441
	cmp       eax,28672
	jne       short @1578
?live1@21680: ; EBX = ta
	xor       edx,edx
	mov       dl,bl
	mov       word ptr [_Mem+391766],dx
?live1@21696: ; 
	jmp       short @1526
@1578:
	mov       ecx,dword ptr [_TU]
	and       ecx,61441
	cmp       ecx,28673
	jne       short @1579
?live1@21712: ; EBX = ta
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391768],ax
?live1@21728: ; 
	jmp       short @1526
@1579:
	push      0
	xor       edx,edx
	mov       word ptr [ebp-24],8
	mov       dword ptr [ebp-4],edx
	mov       edx,4
	inc       dword ptr [ebp-12]
	lea       ecx,dword ptr [ebp-4]
	mov       eax,dword ptr [_TU]
	call      @Sysutils@IntToHex$qqrii
	mov       ecx,dword ptr [ebp-4]
	test      ecx,ecx
	je        short @1580
	mov       edx,dword ptr [ebp-4]
	jmp       short @1581
@1580:
	mov       edx,offset s@+1216
@1581:
	mov       ecx,offset s@+1210
	mov       eax,dword ptr [@Forms@Application]
	call      @Forms@TApplication@MessageBoxA$qqrpct1us
	dec       dword ptr [ebp-12]
	lea       eax,dword ptr [ebp-4]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
@1526:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
	jmp       @361
?live1@21776: ; EBX = ta
@401:
	mov       eax,dword ptr [_TU]
	cmp       eax,32768
	jae       short @1582
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	jmp       @361
@1582:
	mov       cl,byte ptr [_M22in1+1]
	test      cl,cl
	je        short @1583
	and       bl,7
	add       ebx,ebx
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391766],ax
?live1@21824: ; 
	mov       dl,byte ptr [_Mem+391766]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391768],cx
	jmp       @1584
?live1@21856: ; EBX = ta
@1583:
	test      bl,64
	je        short @1585
	push      1
	push      0
	push      1
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       short @1586
@1585:
	push      2
	push      2
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
@1586:
	test      bl,32
	je        short @1587
	and       bl,31
	add       ebx,ebx
	add       bl,16
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391766],ax
?live1@21952: ; 
	mov       dl,byte ptr [_Mem+391766]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391768],cx
	xor       eax,eax
	mov       al,byte ptr [_Mem+391766]
	mov       word ptr [_Mem+391770],ax
	mov       dl,byte ptr [_Mem+391766]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391772],cx
	jmp       short @1588
?live1@22016: ; EBX = ta
@1587:
	and       bl,30
	add       ebx,ebx
	add       bl,16
	xor       eax,eax
	mov       al,bl
	mov       word ptr [_Mem+391766],ax
?live1@22032: ; 
	mov       dl,byte ptr [_Mem+391766]
	inc       edx
	xor       ecx,ecx
	mov       cl,dl
	mov       word ptr [_Mem+391768],cx
	mov       al,byte ptr [_Mem+391766]
	add       al,2
	xor       edx,edx
	mov       dl,al
	mov       word ptr [_Mem+391770],dx
	mov       cl,byte ptr [_Mem+391766]
	add       cl,3
	xor       eax,eax
	mov       al,cl
	mov       word ptr [_Mem+391772],ax
@1588:
@1584:
	call      @UpdateGGCodes$qqrv
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	jmp       short @361
@322:
	mov       ecx,dword ptr [_TU]
	cmp       ecx,8192
	jae       short @1591
?live1@22128: ; EBX = ta
	mov       eax,dword ptr [_TU]
	mov       edx,dword ptr [_Mem+4*eax]
	mov       byte ptr [edx],bl
?live1@22144: ; 
@1591:
@1590:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
@1592:
@361:
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@MemoryTUEquals$qqruc	endp
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@_$DCGB$@Addrmode$qqruc	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-8
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-12
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-16
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-20
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-24
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-28
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-32
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-8
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-12
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-36
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-40
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-44
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-16
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-20
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-24
	dd	0
	align	4
@_$ECTHB$@Addrmode$qqruc	label	dword
	dd	0
	dd	-80
	dw	0
	dw	5
	dd	0
	dd	@_$DCGB$@Addrmode$qqruc
	dw	8
	dw	5
	dd	0
	dd	@_$DCGB$@Addrmode$qqruc+76
	dw	8
	dw	5
	dd	1
	dd	@_$DCGB$@Addrmode$qqruc+116
	dw	8
	dw	5
	dd	2
	dd	@_$DCGB$@Addrmode$qqruc+132
	dw	8
	dw	5
	dd	3
	dd	@_$DCGB$@Addrmode$qqruc+148
	dw	8
	dw	5
	dd	4
	dd	@_$DCGB$@Addrmode$qqruc+200
	dw	8
	dw	5
	dd	5
	dd	@_$DCGB$@Addrmode$qqruc+216
_DATA	ends
_TEXT	segment dword public use32 'CODE'
	align	4
@Addrmode$qqruc	proc	near
?live1@22176:
@1593:
	push      ebp
	mov       ebp,esp
	add       esp,-88
	push      ebx
	push      esi
	mov       byte ptr [ebp-81],al
	mov       eax,offset @_$ECTHB$@Addrmode$qqruc
	call      @__InitExceptBlockLDTC
	xor       edx,edx
	mov       dl,byte ptr [ebp-81]
	cmp       edx,13
	ja        @1594
	jmp       dword ptr [@1609+4*edx]
@1609:
	dd        @1608
	dd        @1607
	dd        @1606
	dd        @1610
	dd        @1604
	dd        @1603
	dd        @1602
	dd        @1601
	dd        @1600
	dd        @1599
	dd        @1598
	dd        @1597
	dd        @1594
	dd        @1596
	jmp       @1610
@1608:
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        short @1611
?live1@22240: ; EAX = @temp22
	mov       edx,dword ptr [_PC]
	inc       edx
	mov       ecx,edx
	and       edx,24576
	shr       edx,13
	and       ecx,8191
	movsx     eax,word ptr [_Mem+391766+2*edx]
	shl       eax,13
	lea       edx,dword ptr [eax+_Mem+391806]
	movzx     ecx,byte ptr [edx+ecx]
	mov       dword ptr [_TU],ecx
	jmp       short @1612
@1611:
	mov       eax,dword ptr [_Mem+4+4*eax]
	xor       edx,edx
	mov       dl,byte ptr [eax]
	mov       dword ptr [_TU],edx
?live1@22272: ; 
@1612:
	mov       byte ptr [_TUMode],0
	jmp       @1610
@1607:
	mov       edx,dword ptr [_PC]
	test      dh,-128
	je        short @1613
?live1@22320: ; EDX = @temp13
	mov       eax,edx
	inc       eax
	and       eax,24576
	shr       eax,13
	mov       byte ptr [_tmpBYTE],al
?live1@22336: ; EAX = @temp26, EDX = @temp27
	and       eax,255
?live1@22352: ; EAX = @temp26
	mov       dx,word ptr [_PC]
	inc       edx
	and       dx,8191
?live1@22368: ; EAX = @temp26, EDX = @temp27
	movzx     ecx,dx
?live1@22384: ; EAX = @temp26
	mov       word ptr [_tmpLBYTE],dx
?live1@22400: ; EAX = @temp26, EDX = @temp27
	movsx     eax,word ptr [_Mem+391766+2*eax]
	shl       eax,13
	lea       edx,dword ptr [eax+_Mem+391807]
	xor       eax,eax
	mov       al,byte ptr [edx+ecx]
	xor       edx,edx
	mov       dl,byte ptr [_tmpBYTE]
	shl       eax,8
	movsx     edx,word ptr [_Mem+391766+2*edx]
	shl       edx,13
	add       edx,offset _Mem+391806
	movzx     ecx,byte ptr [edx+ecx]
	or        ax,cx
	movzx     eax,ax
	mov       dword ptr [_TU],eax
?live1@22416: ; 
	jmp       short @1614
?live1@22432: ; EDX = @temp13
@1613:
	mov       eax,dword ptr [_Mem+8+4*edx]
	mov       edx,dword ptr [_Mem+4+4*edx]
	xor       ecx,ecx
	mov       cl,byte ptr [eax]
	xor       eax,eax
	shl       ecx,8
	mov       al,byte ptr [edx]
	or        cx,ax
	movzx     edx,cx
	mov       dword ptr [_TU],edx
?live1@22448: ; 
@1614:
	mov       byte ptr [_TUMode],1
	jmp       @1610
@1606:
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        short @1615
?live1@22496: ; EAX = @temp23
	mov       edx,dword ptr [_PC]
	inc       edx
	mov       ecx,edx
	and       edx,24576
	shr       edx,13
	and       ecx,8191
	movsx     eax,word ptr [_Mem+391766+2*edx]
	shl       eax,13
	lea       edx,dword ptr [eax+_Mem+391806]
	movzx     ecx,byte ptr [edx+ecx]
	mov       dword ptr [_TU],ecx
	jmp       short @1616
@1615:
	mov       eax,dword ptr [_Mem+4+4*eax]
	xor       edx,edx
	mov       dl,byte ptr [eax]
	mov       dword ptr [_TU],edx
?live1@22528: ; 
@1616:
	mov       byte ptr [_TUMode],1
	jmp       @1610
@1604:
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        @1617
?live1@22576: ; EAX = @temp14
	mov       edx,eax
	inc       edx
	and       edx,24576
	shr       edx,13
	mov       byte ptr [_tmpBYTE],dl
?live1@22592: ; EDX = @temp30
	and       edx,255
	mov       cx,word ptr [_PC]
	inc       ecx
	and       cx,8191
	mov       word ptr [_tmpLBYTE],cx
	movsx     ecx,word ptr [_Mem+391766+2*edx]
	movzx     eax,word ptr [_tmpLBYTE]
	shl       ecx,13
	lea       edx,dword ptr [ecx+_Mem+391806]
	mov       al,byte ptr [edx+eax]
	mov       byte ptr [_tmp],al
?live1@22640: ; 
	xor       eax,eax
	mov       al,byte ptr [_tmpBYTE]
	movzx     ecx,word ptr [_tmpLBYTE]
	movsx     edx,word ptr [_Mem+391766+2*eax]
	shl       edx,13
	lea       eax,dword ptr [edx+_Mem+391807]
	xor       edx,edx
	mov       dl,byte ptr [eax+ecx]
	xor       ecx,ecx
	shl       edx,8
	mov       cl,byte ptr [_tmp]
	or        dx,cx
	movzx     eax,dx
	mov       dword ptr [_TU],eax
	jmp       short @1618
?live1@22672: ; EAX = @temp14
@1617:
	mov       edx,dword ptr [_Mem+4+4*eax]
?live1@22688: ; EAX = @temp14, EDX = @temp24
	xor       ecx,ecx
?live1@22704: ; EAX = @temp14
	mov       dl,byte ptr [edx]
	mov       byte ptr [_tmp],dl
?live1@22720: ; EAX = @temp14, EDX = @temp24
	mov       eax,dword ptr [_Mem+8+4*eax]
	mov       cl,byte ptr [eax]
	xor       eax,eax
	shl       ecx,8
	mov       al,dl
	add       cx,ax
	movzx     edx,cx
	mov       dword ptr [_TU],edx
?live1@22736: ; 
@1618:
	test      byte ptr [_TU+1],-128
	je        @1619
	mov       ecx,dword ptr [_TU]
	and       ecx,24576
	shr       ecx,13
	mov       byte ptr [_tmpBYTE],cl
	xor       ecx,ecx
	mov       ax,word ptr [_TU]
	and       ax,8191
	mov       word ptr [_tmpLBYTE],ax
	movzx     eax,word ptr [_tmpLBYTE]
	mov       dl,byte ptr [_tmp]
	and       eax,7936
	inc       edx
	mov       cl,dl
	xor       edx,edx
	mov       dl,byte ptr [_tmpBYTE]
	or        ecx,eax
	movsx     eax,word ptr [_Mem+391766+2*edx]
	shl       eax,13
	lea       edx,dword ptr [eax+_Mem+391806]
	movzx     eax,word ptr [_tmpLBYTE]
	movzx     ecx,byte ptr [edx+ecx]
	xor       edx,edx
	mov       dl,byte ptr [_tmpBYTE]
	shl       ecx,8
	movsx     edx,word ptr [_Mem+391766+2*edx]
	shl       edx,13
	add       edx,offset _Mem+391806
	movzx     eax,byte ptr [edx+eax]
	or        cx,ax
	movzx     ecx,cx
	mov       dword ptr [_TU],ecx
	jmp       short @1620
@1619:
	mov       cx,word ptr [_TU]
	mov       al,byte ptr [_tmp]
	and       cx,-256
	inc       eax
	xor       edx,edx
	mov       dl,al
	movzx     eax,cx
	or        edx,eax
	mov       eax,dword ptr [_TU]
	xor       ecx,ecx
	mov       edx,dword ptr [_Mem+4*edx]
	mov       cl,byte ptr [edx]
	mov       edx,dword ptr [_Mem+4*eax]
	xor       eax,eax
	shl       ecx,8
	mov       al,byte ptr [edx]
	or        cx,ax
	movzx     edx,cx
	mov       dword ptr [_TU],edx
@1620:
	mov       byte ptr [_TUMode],1
	jmp       @1610
@1603:
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        @1621
?live1@22896: ; EAX = @temp15
	inc       eax
	and       eax,24576
	shr       eax,13
	mov       byte ptr [_tmpBYTE],al
?live1@22912: ; 
	xor       eax,eax
	mov       dx,word ptr [_PC]
	inc       edx
	and       dx,8191
	mov       word ptr [_tmpLBYTE],dx
	movzx     ecx,word ptr [_tmpLBYTE]
	mov       al,byte ptr [_tmpBYTE]
	movsx     edx,word ptr [_Mem+391766+2*eax]
	shl       edx,13
	lea       eax,dword ptr [edx+_Mem+391807]
	xor       edx,edx
	mov       dl,byte ptr [eax+ecx]
	xor       eax,eax
	mov       al,byte ptr [_tmpBYTE]
	movzx     ecx,word ptr [_tmpLBYTE]
	movsx     eax,word ptr [_Mem+391766+2*eax]
	shl       eax,13
	add       eax,offset _Mem+391806
	shl       edx,8
	movzx     ecx,byte ptr [eax+ecx]
	add       dx,cx
	xor       eax,eax
	mov       al,byte ptr [_X]
	add       dx,ax
	movzx     edx,dx
	mov       dword ptr [_TU],edx
	jmp       short @1622
?live1@22976: ; EAX = @temp15
@1621:
	mov       ecx,dword ptr [_Mem+8+4*eax]
	mov       eax,dword ptr [_Mem+4+4*eax]
	xor       edx,edx
	mov       dl,byte ptr [ecx]
	xor       ecx,ecx
	shl       edx,8
	mov       cl,byte ptr [eax]
	add       dx,cx
	xor       eax,eax
	mov       al,byte ptr [_X]
	add       dx,ax
	movzx     edx,dx
	mov       dword ptr [_TU],edx
?live1@22992: ; 
@1622:
	mov       byte ptr [_TUMode],1
	jmp       @1610
@1602:
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        @1623
?live1@23040: ; EAX = @temp16
	inc       eax
	and       eax,24576
	shr       eax,13
	mov       byte ptr [_tmpBYTE],al
?live1@23056: ; 
	xor       eax,eax
	mov       dx,word ptr [_PC]
	inc       edx
	and       dx,8191
	mov       word ptr [_tmpLBYTE],dx
	movzx     ecx,word ptr [_tmpLBYTE]
	mov       al,byte ptr [_tmpBYTE]
	movsx     edx,word ptr [_Mem+391766+2*eax]
	shl       edx,13
	lea       eax,dword ptr [edx+_Mem+391807]
	xor       edx,edx
	mov       dl,byte ptr [eax+ecx]
	xor       eax,eax
	mov       al,byte ptr [_tmpBYTE]
	movzx     ecx,word ptr [_tmpLBYTE]
	movsx     eax,word ptr [_Mem+391766+2*eax]
	shl       eax,13
	add       eax,offset _Mem+391806
	shl       edx,8
	movzx     ecx,byte ptr [eax+ecx]
	add       dx,cx
	xor       eax,eax
	mov       al,byte ptr [_Y]
	add       dx,ax
	movzx     edx,dx
	mov       dword ptr [_TU],edx
	jmp       short @1624
?live1@23120: ; EAX = @temp16
@1623:
	mov       ecx,dword ptr [_Mem+8+4*eax]
	mov       eax,dword ptr [_Mem+4+4*eax]
	xor       edx,edx
	mov       dl,byte ptr [ecx]
	xor       ecx,ecx
	shl       edx,8
	mov       cl,byte ptr [eax]
	add       dx,cx
	xor       eax,eax
	mov       al,byte ptr [_Y]
	add       dx,ax
	movzx     edx,dx
	mov       dword ptr [_TU],edx
?live1@23136: ; 
@1624:
	mov       byte ptr [_TUMode],1
	jmp       @1610
@1601:
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        short @1625
?live1@23184: ; EAX = @temp17
	mov       edx,eax
	and       eax,24576
	shr       eax,13
	inc       edx
	and       edx,8191
	movsx     ecx,word ptr [_Mem+391766+2*eax]
	shl       ecx,13
	lea       eax,dword ptr [ecx+_Mem+391806]
	mov       cl,byte ptr [_X]
	mov       dl,byte ptr [eax+edx]
	add       dl,cl
	xor       eax,eax
	mov       al,dl
	mov       dword ptr [_TU],eax
	jmp       short @1626
@1625:
	mov       edx,dword ptr [_Mem+4+4*eax]
	mov       cl,byte ptr [edx]
	mov       al,byte ptr [_X]
	add       cl,al
	xor       edx,edx
	mov       dl,cl
	mov       dword ptr [_TU],edx
?live1@23216: ; 
@1626:
	mov       byte ptr [_TUMode],1
	jmp       @1610
@1600:
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        short @1627
?live1@23264: ; EAX = @temp18
	mov       edx,eax
	and       eax,24576
	shr       eax,13
	inc       edx
	and       edx,8191
	movsx     ecx,word ptr [_Mem+391766+2*eax]
	shl       ecx,13
	lea       eax,dword ptr [ecx+_Mem+391806]
	mov       cl,byte ptr [_Y]
	mov       dl,byte ptr [eax+edx]
	add       dl,cl
	xor       eax,eax
	mov       al,dl
	mov       dword ptr [_TU],eax
	jmp       short @1628
@1627:
	mov       edx,dword ptr [_Mem+4+4*eax]
	mov       cl,byte ptr [edx]
	mov       al,byte ptr [_Y]
	add       cl,al
	xor       edx,edx
	mov       dl,cl
	mov       dword ptr [_TU],edx
?live1@23296: ; 
@1628:
	mov       byte ptr [_TUMode],1
	jmp       @1610
@1599:
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        short @1629
?live1@23344: ; EAX = @temp19
	mov       edx,eax
	and       eax,24576
	shr       eax,13
	inc       edx
	and       edx,8191
	movsx     ecx,word ptr [_Mem+391766+2*eax]
	shl       ecx,13
	lea       eax,dword ptr [ecx+_Mem+391806]
	mov       cl,byte ptr [_X]
	mov       dl,byte ptr [eax+edx]
	add       dl,cl
	xor       eax,eax
	mov       al,dl
	mov       dword ptr [_TU],eax
	jmp       short @1630
@1629:
	mov       edx,dword ptr [_Mem+4+4*eax]
	mov       cl,byte ptr [edx]
	mov       al,byte ptr [_X]
	add       cl,al
	xor       edx,edx
	mov       dl,cl
	mov       dword ptr [_TU],edx
?live1@23376: ; 
@1630:
	test      byte ptr [_TU+1],-128
	je        short @1631
	mov       ecx,dword ptr [_TU]
	and       ecx,24576
	shr       ecx,13
	mov       byte ptr [_tmpBYTE],cl
	xor       ecx,ecx
	mov       ax,word ptr [_TU]
	and       ax,8191
	mov       word ptr [_tmpLBYTE],ax
	movzx     edx,word ptr [_tmpLBYTE]
	mov       cl,byte ptr [_tmpBYTE]
	movsx     eax,word ptr [_Mem+391766+2*ecx]
	shl       eax,13
	lea       ecx,dword ptr [eax+_Mem+391807]
	movzx     eax,word ptr [_tmpLBYTE]
	movzx     edx,byte ptr [ecx+edx]
	xor       ecx,ecx
	mov       cl,byte ptr [_tmpBYTE]
	shl       edx,8
	movsx     ecx,word ptr [_Mem+391766+2*ecx]
	shl       ecx,13
	add       ecx,offset _Mem+391806
	movzx     eax,byte ptr [ecx+eax]
	or        dx,ax
	movzx     edx,dx
	mov       dword ptr [_TU],edx
	jmp       short @1632
@1631:
	mov       eax,dword ptr [_TU]
	xor       ecx,ecx
	mov       edx,dword ptr [_Mem+4+4*eax]
	mov       eax,dword ptr [_TU]
	mov       cl,byte ptr [edx]
	mov       edx,dword ptr [_Mem+4*eax]
	xor       eax,eax
	shl       ecx,8
	mov       al,byte ptr [edx]
	or        cx,ax
	movzx     edx,cx
	mov       dword ptr [_TU],edx
@1632:
	mov       byte ptr [_TUMode],1
	jmp       @1610
@1598:
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        short @1633
?live1@23536: ; EAX = @temp20
	mov       edx,eax
	and       eax,24576
	shr       eax,13
	inc       edx
	and       edx,8191
	movsx     ecx,word ptr [_Mem+391766+2*eax]
	shl       ecx,13
	lea       eax,dword ptr [ecx+_Mem+391806]
	movzx     edx,byte ptr [eax+edx]
	mov       dword ptr [_TU],edx
	jmp       short @1634
@1633:
	mov       ecx,dword ptr [_Mem+4+4*eax]
	xor       eax,eax
	mov       al,byte ptr [ecx]
	mov       dword ptr [_TU],eax
?live1@23568: ; 
@1634:
	test      byte ptr [_TU+1],-128
	je        @1635
	mov       edx,dword ptr [_TU]
	and       edx,24576
	shr       edx,13
	mov       byte ptr [_tmpBYTE],dl
	xor       edx,edx
	mov       cx,word ptr [_TU]
	and       cx,8191
	mov       word ptr [_tmpLBYTE],cx
	movzx     eax,word ptr [_tmpLBYTE]
	mov       dl,byte ptr [_tmpBYTE]
	movsx     ecx,word ptr [_Mem+391766+2*edx]
	shl       ecx,13
	lea       edx,dword ptr [ecx+_Mem+391807]
	movzx     ecx,word ptr [_tmpLBYTE]
	movzx     eax,byte ptr [edx+eax]
	xor       edx,edx
	mov       dl,byte ptr [_tmpBYTE]
	shl       eax,8
	movsx     edx,word ptr [_Mem+391766+2*edx]
	shl       edx,13
	add       edx,offset _Mem+391806
	movzx     ecx,byte ptr [edx+ecx]
	add       ax,cx
	xor       edx,edx
	mov       dl,byte ptr [_Y]
	add       ax,dx
	movzx     eax,ax
	mov       dword ptr [_TU],eax
	jmp       short @1636
@1635:
	mov       ecx,dword ptr [_TU]
	xor       edx,edx
	mov       eax,dword ptr [_Mem+4+4*ecx]
	mov       ecx,dword ptr [_TU]
	mov       dl,byte ptr [eax]
	mov       eax,dword ptr [_Mem+4*ecx]
	xor       ecx,ecx
	shl       edx,8
	mov       cl,byte ptr [eax]
	add       dx,cx
	xor       eax,eax
	mov       al,byte ptr [_Y]
	add       dx,ax
	movzx     edx,dx
	mov       dword ptr [_TU],edx
@1636:
	mov       byte ptr [_TUMode],1
	jmp       short @1610
@1597:
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        short @1637
?live1@23728: ; EAX = @temp21
	mov       edx,eax
	and       eax,24576
	shr       eax,13
	inc       edx
	and       edx,8191
	movsx     ecx,word ptr [_Mem+391766+2*eax]
	shl       ecx,13
	lea       eax,dword ptr [ecx+_Mem+391806]
	mov       dl,byte ptr [eax+edx]
	mov       byte ptr [_TU2],dl
	jmp       short @1610
@1637:
	mov       ecx,dword ptr [_Mem+4+4*eax]
	mov       al,byte ptr [ecx]
	mov       byte ptr [_TU2],al
?live1@23760: ; 
	jmp       short @1610
@1596:
	mov       dl,byte ptr [_HaltOnBadOp]
	test      dl,dl
	je        short @1638
	mov       byte ptr [_CPURunning],0
@1638:
	mov       eax,dword ptr [@Forms@Application]
	call      @Forms@TApplication@ProcessMessages$qqrv
	mov       dl,byte ptr [_DebuggingTrace]
	test      dl,dl
	jne       short @1610
	mov       eax,dword ptr [@Forms@Application]
	call      @Forms@TApplication@ProcessMessages$qqrv
@1594:
@1610:
	mov       dl,byte ptr [_DebuggingTrace]
	test      dl,dl
	jne       short @1640
	mov       ecx,dword ptr [ebp-80]
	mov       dword ptr fs:[0],ecx
	mov       eax,ecx
	jmp       @1641
@1640:
	mov       eax,dword ptr [@Forms@Application]
	call      @Forms@TApplication@ProcessMessages$qqrv
	mov       eax,dword ptr [_PC]
	test      ah,-128
	je        @1642
?live1@23888: ; EAX = @temp1
	mov       ecx,eax
	mov       edx,eax
	and       ecx,24576
	and       edx,8191
	shr       ecx,13
	movsx     ecx,word ptr [_Mem+391766+2*ecx]
	shl       ecx,13
	add       ecx,offset _Mem+391806
	mov       dl,byte ptr [ecx+edx]
	mov       byte ptr [ebp-82],dl
	mov       edx,dword ptr [_PC]
	inc       edx
	mov       ecx,edx
	and       edx,24576
	shr       edx,13
	and       ecx,8191
	movsx     edx,word ptr [_Mem+391766+2*edx]
	shl       edx,13
	add       edx,offset _Mem+391806
	mov       bl,byte ptr [edx+ecx]
?live1@23920: ; EAX = @temp1, EBX = NB
	mov       edx,dword ptr [_PC]
	add       edx,2
	mov       ecx,edx
	and       edx,24576
	shr       edx,13
	and       ecx,8191
	movsx     eax,word ptr [_Mem+391766+2*edx]
	shl       eax,13
	add       eax,offset _Mem+391806
	mov       dl,byte ptr [eax+ecx]
	mov       byte ptr [ebp-83],dl
?live1@23936: ; EBX = NB
	jmp       short @1643
?live1@23952: ; EAX = @temp1
@1642:
	mov       ecx,dword ptr [_PC]
	mov       edx,dword ptr [_Mem+4*ecx]
	mov       cl,byte ptr [edx]
	mov       byte ptr [ebp-82],cl
	mov       edx,dword ptr [_Mem+4+4*eax]
?live1@23984: ; EAX = @temp1, EBX = NB
	mov       eax,dword ptr [_Mem+8+4*eax]
?live1@24000: ; EAX = @temp1
	mov       bl,byte ptr [edx]
?live1@24016: ; EAX = @temp1, EBX = NB
	mov       dl,byte ptr [eax]
	mov       byte ptr [ebp-83],dl
?live1@24032: ; EBX = NB
@1643:
	mov       word ptr [ebp-64],20
	xor       ecx,ecx
	mov       dword ptr [ebp-28],ecx
	lea       ecx,dword ptr [ebp-28]
	inc       dword ptr [ebp-52]
	mov       edx,4
	mov       eax,dword ptr [_PC]
	call      @Sysutils@IntToHex$qqrii
	lea       eax,dword ptr [ebp-28]
	push      eax
	mov       edx,offset s@+1217
	lea       eax,dword ptr [ebp-32]
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-52]
	xor       ecx,ecx
	mov       dword ptr [ebp-4],ecx
	mov       edx,eax
	inc       dword ptr [ebp-52]
	lea       ecx,dword ptr [ebp-4]
	pop       eax
	call      @System@AnsiString@$badd$xqqrrx17System@AnsiString
	dec       dword ptr [ebp-52]
	lea       eax,dword ptr [ebp-32]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-52]
	lea       eax,dword ptr [ebp-28]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	mov       word ptr [ebp-64],8
	mov       word ptr [ebp-64],32
	xor       ecx,ecx
	mov       edx,2
	mov       dword ptr [ebp-8],ecx
	lea       ecx,dword ptr [ebp-8]
	inc       dword ptr [ebp-52]
	xor       eax,eax
	mov       al,byte ptr [ebp-82]
	call      @Sysutils@IntToHex$qqrii
	mov       word ptr [ebp-64],8
	mov       word ptr [ebp-64],44
	xor       eax,eax
	lea       ecx,dword ptr [ebp-12]
	mov       dword ptr [ebp-12],eax
	mov       edx,2
	inc       dword ptr [ebp-52]
	xor       eax,eax
	mov       al,bl
	call      @Sysutils@IntToHex$qqrii
	movsx     esi,bl
	mov       word ptr [ebp-64],8
	mov       eax,esi
	xor       ecx,ecx
	cdq
	mov       word ptr [ebp-64],56
	xor       eax,edx
	mov       dword ptr [ebp-44],ecx
	sub       eax,edx
	mov       edx,2
	inc       dword ptr [ebp-52]
	lea       ecx,dword ptr [ebp-44]
	call      @Sysutils@IntToHex$qqrii
	lea       eax,dword ptr [ebp-44]
	push      eax
	mov       byte ptr [ebp-84],0
	mov       byte ptr [ebp-85],0
	test      bl,-128
	je        short @1644
	mov       byte ptr [ebp-84],1
	mov       edx,offset s@+1222
	lea       eax,dword ptr [ebp-36]
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-52]
	jmp       short @1645
@1644:
	mov       byte ptr [ebp-85],1
	mov       edx,offset s@+1226
	lea       eax,dword ptr [ebp-40]
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-52]
@1645:
	xor       ecx,ecx
	mov       dword ptr [ebp-16],ecx
	lea       ecx,dword ptr [ebp-16]
	inc       dword ptr [ebp-52]
	pop       edx
	call      @System@AnsiString@$badd$xqqrrx17System@AnsiString
	dec       dword ptr [ebp-52]
	lea       eax,dword ptr [ebp-44]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	mov       al,byte ptr [ebp-85]
	test      al,al
	je        short @1647
	dec       dword ptr [ebp-52]
	lea       eax,dword ptr [ebp-40]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
@1647:
	mov       cl,byte ptr [ebp-84]
	test      cl,cl
	je        short @1649
	dec       dword ptr [ebp-52]
	lea       eax,dword ptr [ebp-36]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
@1649:
	mov       word ptr [ebp-64],8
?live1@24128: ; 
	mov       word ptr [ebp-64],68
	xor       ecx,ecx
	mov       edx,2
	mov       dword ptr [ebp-20],ecx
	lea       ecx,dword ptr [ebp-20]
	inc       dword ptr [ebp-52]
	xor       eax,eax
	mov       al,byte ptr [ebp-83]
	call      @Sysutils@IntToHex$qqrii
	mov       word ptr [ebp-64],8
	mov       word ptr [ebp-64],80
	xor       eax,eax
	xor       edx,edx
	mov       al,byte ptr [ebp-82]
	mov       dl,byte ptr [eax+_instruc]
	lea       eax,dword ptr [ebp-24]
	shl       edx,2
	add       edx,offset _Mn
	call      @System@AnsiString@$bctr$qqrrx17System@AnsiString
	inc       dword ptr [ebp-52]
	xor       edx,edx
	mov       word ptr [ebp-64],8
	mov       dl,byte ptr [ebp-81]
	cmp       edx,11
	ja        short @1665
	jmp       dword ptr [@1664+4*edx]
@1664:
	dd        @1665
	dd        @1665
	dd        @1665
	dd        @1665
	dd        @1665
	dd        @1665
	dd        @1665
	dd        @1665
	dd        @1665
	dd        @1665
	dd        @1665
	dd        @1665
@1665:
	dec       dword ptr [ebp-52]
	lea       eax,dword ptr [ebp-24]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-52]
	lea       eax,dword ptr [ebp-20]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-52]
	lea       eax,dword ptr [ebp-16]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-52]
	lea       eax,dword ptr [ebp-12]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-52]
	lea       eax,dword ptr [ebp-8]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-52]
	lea       eax,dword ptr [ebp-4]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	mov       ecx,dword ptr [ebp-80]
	mov       dword ptr fs:[0],ecx
@1666:
@1641:
	pop       esi
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@Addrmode$qqruc	endp
	align	4
@ExecOp$qqruc	proc	near
?live1@24240:
@1667:
	push      ebx
?live1@24256: ; EAX = opcode
	and       eax,255
	cmp       eax,59
	ja        @1741
	jmp       dword ptr [@1730+4*eax]
@1730:
	dd        @1729
	dd        @1728
	dd        @1727
	dd        @1726
	dd        @1725
	dd        @1724
	dd        @1723
	dd        @1722
	dd        @1721
	dd        @1720
	dd        @1719
	dd        @1718
	dd        @1717
	dd        @1716
	dd        @1715
	dd        @1714
	dd        @1713
	dd        @1712
	dd        @1711
	dd        @1710
	dd        @1709
	dd        @1708
	dd        @1707
	dd        @1706
	dd        @1705
	dd        @1704
	dd        @1703
	dd        @1702
	dd        @1701
	dd        @1700
	dd        @1699
	dd        @1698
	dd        @1697
	dd        @1741
	dd        @1695
	dd        @1694
	dd        @1693
	dd        @1692
	dd        @1691
	dd        @1690
	dd        @1689
	dd        @1688
	dd        @1687
	dd        @1686
	dd        @1685
	dd        @1684
	dd        @1683
	dd        @1682
	dd        @1681
	dd        @1680
	dd        @1679
	dd        @1678
	dd        @1677
	dd        @1676
	dd        @1675
	dd        @1674
	dd        @1673
	dd        @1672
	dd        @1671
	dd        @1670
?live1@24272: ; 
@1729:
	mov       dl,byte ptr [_TUMode]
	test      dl,dl
	je        short @1731
	call      @MemoryTUGet$qqrv
	mov       ebx,eax
	jmp       short @1732
@1731:
	mov       bl,byte ptr [_TU]
@1732:
	mov       byte ptr [_tmpBYTE],bl
?live1@24288: ; EBX = @temp3
	xor       eax,eax
	mov       al,byte ptr [_A]
	xor       edx,edx
	mov       dl,bl
	add       ax,dx
	xor       ecx,ecx
	mov       cl,byte ptr [_P]
	and       cx,1
	add       ax,cx
	mov       word ptr [_tmpshortint],ax
?live1@24304: ; EAX = @temp4
	cmp       ax,255
	jle       short @1733
	or        byte ptr [_P],1
	jmp       short @1734
@1733:
	and       byte ptr [_P],-2
?live1@24320: ; 
@1734:
	mov       al,byte ptr [_A]
	mov       cl,byte ptr [_tmpBYTE]
	mov       edx,eax
	xor       dl,cl
	mov       cl,byte ptr [_tmpshortint]
	not       dl
	xor       al,cl
	and       dl,al
	test      dl,-128
	je        short @1735
	or        byte ptr [_P],64
	jmp       short @1736
@1735:
	and       byte ptr [_P],-65
@1736:
	mov       al,byte ptr [_tmpshortint]
	mov       byte ptr [_A],al
?live1@24352: ; EAX = @temp6
	test      al,-128
	je        short @1737
	or        byte ptr [_P],-128
	jmp       short @1738
@1737:
	and       byte ptr [_P],127
@1738:
	mov       dl,byte ptr [_A]
	test      dl,dl
	je        short @1739
	and       byte ptr [_P],-3
	jmp       @1741
@1739:
	or        byte ptr [_P],2
?live1@24368: ; 
@1944:
	pop       ebx
	ret 
@1728:
	mov       al,byte ptr [_TUMode]
	test      al,al
	je        short @1742
	call      @MemoryTUGet$qqrv
	jmp       short @1743
@1742:
	mov       al,byte ptr [_TU]
@1743:
	and       byte ptr [_A],al
	test      byte ptr [_A],-128
	je        short @1744
	or        byte ptr [_P],-128
	jmp       short @1745
@1744:
	and       byte ptr [_P],127
@1745:
	mov       dl,byte ptr [_A]
	test      dl,dl
	je        short @1746
	and       byte ptr [_P],-3
	jmp       @1741
@1746:
	or        byte ptr [_P],2
@1945:
	pop       ebx
	ret 
@1727:
	call      @MemoryTUGet$qqrv
	mov       ebx,eax
?live1@24448: ; EBX = @temp7
	test      bl,-128
?live1@24464: ; 
	mov       byte ptr [_tmpBYTE],bl
?live1@24480: ; EBX = @temp7
	je        short @1748
	or        byte ptr [_P],1
	jmp       short @1749
@1748:
	and       byte ptr [_P],-2
?live1@24496: ; 
@1749:
	shl       byte ptr [_tmpBYTE],1
	test      byte ptr [_tmpBYTE],-128
	je        short @1750
	or        byte ptr [_P],-128
	jmp       short @1751
@1750:
	and       byte ptr [_P],127
@1751:
	mov       al,byte ptr [_tmpBYTE]
	test      al,al
	je        short @1752
	and       byte ptr [_P],-3
	jmp       short @1753
@1752:
	or        byte ptr [_P],2
@1753:
	mov       al,byte ptr [_tmpBYTE]
	call      @MemoryTUEquals$qqruc
@1946:
	pop       ebx
	ret 
@1673:
	test      byte ptr [_A],-128
	je        short @1754
	or        byte ptr [_P],1
	jmp       short @1755
@1754:
	and       byte ptr [_P],-2
@1755:
	shl       byte ptr [_A],1
	test      byte ptr [_A],-128
	je        short @1756
	or        byte ptr [_P],-128
	jmp       short @1757
@1756:
	and       byte ptr [_P],127
@1757:
	mov       dl,byte ptr [_A]
	test      dl,dl
	je        short @1758
	and       byte ptr [_P],-3
	jmp       @1741
@1758:
	or        byte ptr [_P],2
@1947:
	pop       ebx
	ret 
@1726:
	test      byte ptr [_P],1
	jne       @1741
	movsx     ecx,byte ptr [_TU2]
	add       dword ptr [_PC],ecx
@1948:
	pop       ebx
	ret 
@1725:
	test      byte ptr [_P],1
	je        @1741
	movsx     eax,byte ptr [_TU2]
	add       dword ptr [_PC],eax
@1949:
	pop       ebx
	ret 
@1724:
	test      byte ptr [_P],2
	je        @1741
	movsx     edx,byte ptr [_TU2]
	add       dword ptr [_PC],edx
@1950:
	pop       ebx
	ret 
@1723:
	call      @MemoryTUGet$qqrv
	mov       ebx,eax
?live1@24736: ; EBX = @temp8
	test      bl,64
?live1@24752: ; 
	mov       byte ptr [_tmpBYTE],bl
?live1@24768: ; EBX = @temp8
	je        short @1763
	or        byte ptr [_P],64
	jmp       short @1764
@1763:
	and       byte ptr [_P],-65
?live1@24784: ; 
@1764:
	test      byte ptr [_tmpBYTE],-128
	je        short @1765
	or        byte ptr [_P],-128
	jmp       short @1766
@1765:
	and       byte ptr [_P],127
@1766:
	mov       al,byte ptr [_A]
	and       byte ptr [_tmpBYTE],al
	mov       dl,byte ptr [_tmpBYTE]
	test      dl,dl
	je        short @1767
	and       byte ptr [_P],-3
	jmp       @1741
@1767:
	or        byte ptr [_P],2
@1951:
	pop       ebx
	ret 
@1722:
	test      byte ptr [_P],-128
	je        @1741
	movsx     ecx,byte ptr [_TU2]
	add       dword ptr [_PC],ecx
@1952:
	pop       ebx
	ret 
@1721:
	test      byte ptr [_P],2
	jne       @1741
	movsx     eax,byte ptr [_TU2]
	add       dword ptr [_PC],eax
@1953:
	pop       ebx
	ret 
@1720:
	test      byte ptr [_P],-128
	jne       @1741
	movsx     edx,byte ptr [_TU2]
	add       dword ptr [_PC],edx
@1954:
	pop       ebx
	ret 
@1719:
	or        byte ptr [_P],16
	xor       eax,eax
	mov       dx,word ptr [_PC]
	dec       edx
	movzx     ecx,dx
	mov       word ptr [_tmpLBYTE],dx
	mov       al,byte ptr [_SP]
	sar       ecx,8
	mov       byte ptr [eax+_Mem+264192],cl
	mov       dl,byte ptr [_tmpLBYTE]
	mov       byte ptr [eax+_Mem+264191],dl
	xor       edx,edx
	mov       cl,byte ptr [_P]
	mov       byte ptr [eax+_Mem+264190],cl
	sub       byte ptr [_SP],3
	or        byte ptr [_P],4
	movsx     eax,word ptr [_Mem+391772]
	shl       eax,13
	mov       dl,byte ptr [eax+_Mem+399997]
	movzx     eax,byte ptr [eax+_Mem+399996]
	shl       edx,8
	or        dx,ax
	movzx     ecx,dx
	mov       dword ptr [_PC],ecx
@1955:
	pop       ebx
	ret 
@1718:
	test      byte ptr [_P],64
	jne       @1741
	movsx     eax,byte ptr [_TU2]
	add       dword ptr [_PC],eax
@1956:
	pop       ebx
	ret 
@1717:
	test      byte ptr [_P],64
	je        @1741
	movsx     edx,byte ptr [_TU2]
	add       dword ptr [_PC],edx
@1957:
	pop       ebx
	ret 
@1716:
	and       byte ptr [_P],-2
@1958:
	pop       ebx
	ret 
@1715:
	and       byte ptr [_P],-9
@1959:
	pop       ebx
	ret 
@1714:
	and       byte ptr [_P],-5
@1960:
	pop       ebx
	ret 
@1713:
	and       byte ptr [_P],-65
@1961:
	pop       ebx
	ret 
@1712:
	mov       cl,byte ptr [_TUMode]
	test      cl,cl
	je        short @1774
	call      @MemoryTUGet$qqrv
	jmp       short @1775
@1774:
	mov       al,byte ptr [_TU]
@1775:
	xor       edx,edx
	xor       ebx,ebx
	mov       bl,byte ptr [_A]
	mov       dl,al
	sub       bx,dx
	mov       word ptr [_tmpshortint],bx
?live1@25264: ; EBX = @temp11
	test      bl,-128
	je        short @1776
	or        byte ptr [_P],-128
	jmp       short @1777
@1776:
	and       byte ptr [_P],127
@1777:
	cmp       word ptr [_tmpshortint],0
	je        short @1778
	and       byte ptr [_P],-3
	jmp       short @1779
@1778:
	or        byte ptr [_P],2
?live1@25280: ; 
@1779:
	cmp       word ptr [_tmpshortint],0
	jl        short @1780
	or        byte ptr [_P],1
	jmp       @1741
@1780:
	and       byte ptr [_P],-2
@1962:
	pop       ebx
	ret 
@1711:
	mov       al,byte ptr [_TUMode]
	test      al,al
	je        short @1782
	call      @MemoryTUGet$qqrv
	jmp       short @1783
@1782:
	mov       al,byte ptr [_TU]
@1783:
	xor       edx,edx
	xor       ebx,ebx
	mov       bl,byte ptr [_X]
	mov       dl,al
	sub       bx,dx
	mov       word ptr [_tmpshortint],bx
?live1@25328: ; EBX = @temp12
	test      bl,-128
	je        short @1784
	or        byte ptr [_P],-128
	jmp       short @1785
@1784:
	and       byte ptr [_P],127
@1785:
	cmp       word ptr [_tmpshortint],0
	je        short @1786
	and       byte ptr [_P],-3
	jmp       short @1787
@1786:
	or        byte ptr [_P],2
?live1@25344: ; 
@1787:
	cmp       word ptr [_tmpshortint],0
	jl        short @1788
	or        byte ptr [_P],1
	jmp       @1741
@1788:
	and       byte ptr [_P],-2
@1963:
	pop       ebx
	ret 
@1710:
	mov       al,byte ptr [_TUMode]
	test      al,al
	je        short @1790
	call      @MemoryTUGet$qqrv
	jmp       short @1791
@1790:
	mov       al,byte ptr [_TU]
@1791:
	xor       edx,edx
	xor       ebx,ebx
	mov       bl,byte ptr [_Y]
	mov       dl,al
	sub       bx,dx
	mov       word ptr [_tmpshortint],bx
?live1@25392: ; EBX = @temp13
	test      bl,-128
	je        short @1792
	or        byte ptr [_P],-128
	jmp       short @1793
@1792:
	and       byte ptr [_P],127
@1793:
	cmp       word ptr [_tmpshortint],0
	je        short @1794
	and       byte ptr [_P],-3
	jmp       short @1795
@1794:
	or        byte ptr [_P],2
?live1@25408: ; 
@1795:
	cmp       word ptr [_tmpshortint],0
	jl        short @1796
	or        byte ptr [_P],1
	jmp       @1741
@1796:
	and       byte ptr [_P],-2
@1964:
	pop       ebx
	ret 
@1709:
	call      @MemoryTUGet$qqrv
	mov       byte ptr [_tmpBYTE],al
	dec       byte ptr [_tmpBYTE]
	test      byte ptr [_tmpBYTE],-128
	je        short @1798
	or        byte ptr [_P],-128
	jmp       short @1799
@1798:
	and       byte ptr [_P],127
@1799:
	mov       al,byte ptr [_tmpBYTE]
	test      al,al
	je        short @1800
	and       byte ptr [_P],-3
	jmp       short @1801
@1800:
	or        byte ptr [_P],2
@1801:
	mov       al,byte ptr [_tmpBYTE]
	call      @MemoryTUEquals$qqruc
@1965:
	pop       ebx
	ret 
@1708:
	dec       byte ptr [_X]
	test      byte ptr [_X],-128
	je        short @1802
	or        byte ptr [_P],-128
	jmp       short @1803
@1802:
	and       byte ptr [_P],127
@1803:
	mov       dl,byte ptr [_X]
	test      dl,dl
	je        short @1804
	and       byte ptr [_P],-3
	jmp       @1741
@1804:
	or        byte ptr [_P],2
@1966:
	pop       ebx
	ret 
@1707:
	dec       byte ptr [_Y]
	test      byte ptr [_Y],-128
	je        short @1806
	or        byte ptr [_P],-128
	jmp       short @1807
@1806:
	and       byte ptr [_P],127
@1807:
	mov       cl,byte ptr [_Y]
	test      cl,cl
	je        short @1808
	and       byte ptr [_P],-3
	jmp       @1741
@1808:
	or        byte ptr [_P],2
@1967:
	pop       ebx
	ret 
@1706:
	mov       al,byte ptr [_TUMode]
	test      al,al
	je        short @1810
	call      @MemoryTUGet$qqrv
	jmp       short @1811
@1810:
	mov       al,byte ptr [_TU]
@1811:
	xor       byte ptr [_A],al
	test      byte ptr [_A],-128
	je        short @1812
	or        byte ptr [_P],-128
	jmp       short @1813
@1812:
	and       byte ptr [_P],127
@1813:
	mov       dl,byte ptr [_A]
	test      dl,dl
	je        short @1814
	and       byte ptr [_P],-3
	jmp       @1741
@1814:
	or        byte ptr [_P],2
@1968:
	pop       ebx
	ret 
@1705:
	call      @MemoryTUGet$qqrv
	mov       byte ptr [_tmpBYTE],al
	inc       byte ptr [_tmpBYTE]
	test      byte ptr [_tmpBYTE],-128
	je        short @1816
	or        byte ptr [_P],-128
	jmp       short @1817
@1816:
	and       byte ptr [_P],127
@1817:
	mov       cl,byte ptr [_tmpBYTE]
	test      cl,cl
	je        short @1818
	and       byte ptr [_P],-3
	jmp       short @1819
@1818:
	or        byte ptr [_P],2
@1819:
	mov       al,byte ptr [_tmpBYTE]
	call      @MemoryTUEquals$qqruc
@1969:
	pop       ebx
	ret 
@1704:
	inc       byte ptr [_X]
	test      byte ptr [_X],-128
	je        short @1820
	or        byte ptr [_P],-128
	jmp       short @1821
@1820:
	and       byte ptr [_P],127
@1821:
	mov       dl,byte ptr [_X]
	test      dl,dl
	je        short @1822
	and       byte ptr [_P],-3
	jmp       @1741
@1822:
	or        byte ptr [_P],2
@1970:
	pop       ebx
	ret 
@1703:
	inc       byte ptr [_Y]
	test      byte ptr [_Y],-128
	je        short @1824
	or        byte ptr [_P],-128
	jmp       short @1825
@1824:
	and       byte ptr [_P],127
@1825:
	mov       cl,byte ptr [_Y]
	test      cl,cl
	je        short @1826
	and       byte ptr [_P],-3
	jmp       @1741
@1826:
	or        byte ptr [_P],2
@1971:
	pop       ebx
	ret 
@1702:
	movzx     eax,word ptr [_TU]
	mov       dword ptr [_PC],eax
@1972:
	pop       ebx
	ret 
@1701:
	mov       ax,word ptr [_PC]
	xor       edx,edx
	dec       eax
	movzx     ecx,ax
	mov       word ptr [_tmpLBYTE],ax
	mov       dl,byte ptr [_SP]
	sar       ecx,8
	mov       byte ptr [edx+_Mem+264192],cl
	mov       al,byte ptr [_tmpLBYTE]
	mov       byte ptr [edx+_Mem+264191],al
	sub       byte ptr [_SP],2
	movzx     edx,word ptr [_TU]
	mov       dword ptr [_PC],edx
@1973:
	pop       ebx
	ret 
@1700:
	mov       cl,byte ptr [_TUMode]
	test      cl,cl
	je        short @1828
	call      @MemoryTUGet$qqrv
	mov       ebx,eax
	jmp       short @1829
@1828:
	mov       bl,byte ptr [_TU]
?live1@25936: ; EBX = @temp16
@1829:
	test      bl,-128
?live1@25952: ; 
	mov       byte ptr [_A],bl
?live1@25968: ; EBX = @temp16
	je        short @1830
	or        byte ptr [_P],-128
	jmp       short @1831
@1830:
	and       byte ptr [_P],127
@1831:
	mov       al,byte ptr [_A]
	test      al,al
	je        short @1832
	and       byte ptr [_P],-3
	jmp       @1741
@1832:
	or        byte ptr [_P],2
?live1@25984: ; 
@1974:
	pop       ebx
	ret 
@1699:
	mov       dl,byte ptr [_TUMode]
	test      dl,dl
	je        short @1834
	call      @MemoryTUGet$qqrv
	mov       ebx,eax
	jmp       short @1835
@1834:
	mov       bl,byte ptr [_TU]
?live1@26016: ; EBX = @temp17
@1835:
	test      bl,-128
?live1@26032: ; 
	mov       byte ptr [_X],bl
?live1@26048: ; EBX = @temp17
	je        short @1836
	or        byte ptr [_P],-128
	jmp       short @1837
@1836:
	and       byte ptr [_P],127
@1837:
	mov       al,byte ptr [_X]
	test      al,al
	je        short @1838
	and       byte ptr [_P],-3
	jmp       @1741
@1838:
	or        byte ptr [_P],2
?live1@26064: ; 
@1975:
	pop       ebx
	ret 
@1698:
	mov       dl,byte ptr [_TUMode]
	test      dl,dl
	je        short @1840
	call      @MemoryTUGet$qqrv
	mov       ebx,eax
	jmp       short @1841
@1840:
	mov       bl,byte ptr [_TU]
?live1@26096: ; EBX = @temp18
@1841:
	test      bl,-128
?live1@26112: ; 
	mov       byte ptr [_Y],bl
?live1@26128: ; EBX = @temp18
	je        short @1842
	or        byte ptr [_P],-128
	jmp       short @1843
@1842:
	and       byte ptr [_P],127
@1843:
	mov       al,byte ptr [_Y]
	test      al,al
	je        short @1844
	and       byte ptr [_P],-3
	jmp       @1741
@1844:
	or        byte ptr [_P],2
?live1@26144: ; 
@1976:
	pop       ebx
	ret 
@1697:
	call      @MemoryTUGet$qqrv
	mov       ebx,eax
?live1@26176: ; EBX = @temp19
	test      bl,1
?live1@26192: ; 
	mov       byte ptr [_tmpBYTE],bl
?live1@26208: ; EBX = @temp19
	je        short @1846
	or        byte ptr [_P],1
	jmp       short @1847
@1846:
	and       byte ptr [_P],-2
?live1@26224: ; 
@1847:
	shr       byte ptr [_tmpBYTE],1
	test      byte ptr [_tmpBYTE],-128
	je        short @1848
	or        byte ptr [_P],-128
	jmp       short @1849
@1848:
	and       byte ptr [_P],127
@1849:
	mov       al,byte ptr [_tmpBYTE]
	test      al,al
	je        short @1850
	and       byte ptr [_P],-3
	jmp       short @1851
@1850:
	or        byte ptr [_P],2
@1851:
	mov       al,byte ptr [_tmpBYTE]
	call      @MemoryTUEquals$qqruc
@1977:
	pop       ebx
	ret 
@1672:
	test      byte ptr [_A],1
	je        short @1852
	or        byte ptr [_P],1
	jmp       short @1853
@1852:
	and       byte ptr [_P],-2
@1853:
	shr       byte ptr [_A],1
	test      byte ptr [_A],-128
	je        short @1854
	or        byte ptr [_P],-128
	jmp       short @1855
@1854:
	and       byte ptr [_P],127
@1855:
	mov       dl,byte ptr [_A]
	test      dl,dl
	je        short @1856
	and       byte ptr [_P],-3
	jmp       @1741
@1856:
	or        byte ptr [_P],2
@1978:
	pop       ebx
	ret 
@1695:
	mov       cl,byte ptr [_TUMode]
	test      cl,cl
	je        short @1858
	call      @MemoryTUGet$qqrv
	jmp       short @1859
@1858:
	mov       al,byte ptr [_TU]
@1859:
	or        byte ptr [_A],al
	test      byte ptr [_A],-128
	je        short @1860
	or        byte ptr [_P],-128
	jmp       short @1861
@1860:
	and       byte ptr [_P],127
@1861:
	mov       dl,byte ptr [_A]
	test      dl,dl
	je        short @1862
	and       byte ptr [_P],-3
	jmp       @1741
@1862:
	or        byte ptr [_P],2
@1979:
	pop       ebx
	ret 
@1694:
	xor       ecx,ecx
	mov       cl,byte ptr [_SP]
	mov       al,byte ptr [_A]
	mov       byte ptr [ecx+_Mem+264192],al
	dec       byte ptr [_SP]
@1980:
	pop       ebx
	ret 
@1693:
	xor       edx,edx
	mov       dl,byte ptr [_SP]
	mov       cl,byte ptr [_P]
	mov       byte ptr [edx+_Mem+264192],cl
	dec       byte ptr [_SP]
@1981:
	pop       ebx
	ret 
@1692:
	inc       byte ptr [_SP]
	xor       eax,eax
	mov       al,byte ptr [_SP]
	mov       al,byte ptr [eax+_Mem+264192]
	mov       byte ptr [_A],al
?live1@26512: ; EAX = @temp20
	test      al,-128
	je        short @1864
	or        byte ptr [_P],-128
	jmp       short @1865
@1864:
	and       byte ptr [_P],127
@1865:
	mov       dl,byte ptr [_A]
	test      dl,dl
	je        short @1866
	and       byte ptr [_P],-3
	jmp       @1741
@1866:
	or        byte ptr [_P],2
?live1@26528: ; 
@1982:
	pop       ebx
	ret 
@1691:
	inc       byte ptr [_SP]
	xor       ecx,ecx
	mov       cl,byte ptr [_SP]
	mov       al,byte ptr [ecx+_Mem+264192]
	mov       byte ptr [_P],al
@1983:
	pop       ebx
	ret 
@1690:
	call      @MemoryTUGet$qqrv
	mov       ebx,eax
	mov       byte ptr [_tmpBYTE],bl
?live1@26592: ; EBX = @temp21
	test      byte ptr [_P],1
	je        short @1869
	test      bl,-128
	je        short @1870
	or        byte ptr [_P],1
	jmp       short @1871
@1870:
	and       byte ptr [_P],-2
?live1@26624: ; 
@1871:
	shl       byte ptr [_tmpBYTE],1
	or        byte ptr [_tmpBYTE],1
	jmp       short @1872
@1869:
	test      byte ptr [_tmpBYTE],-128
	je        short @1873
	or        byte ptr [_P],1
	jmp       short @1874
@1873:
	and       byte ptr [_P],-2
@1874:
	shl       byte ptr [_tmpBYTE],1
@1872:
	test      byte ptr [_tmpBYTE],-128
	je        short @1875
	or        byte ptr [_P],-128
	jmp       short @1876
@1875:
	and       byte ptr [_P],127
@1876:
	mov       al,byte ptr [_tmpBYTE]
	test      al,al
	je        short @1877
	and       byte ptr [_P],-3
	jmp       short @1878
@1877:
	or        byte ptr [_P],2
@1878:
	mov       al,byte ptr [_tmpBYTE]
	call      @MemoryTUEquals$qqruc
@1984:
	pop       ebx
	ret 
@1671:
	test      byte ptr [_P],1
	je        short @1880
	test      byte ptr [_A],-128
	je        short @1881
	or        byte ptr [_P],1
	jmp       short @1882
@1881:
	and       byte ptr [_P],-2
@1882:
	shl       byte ptr [_A],1
	or        byte ptr [_A],1
	jmp       short @1883
@1880:
	test      byte ptr [_A],-128
	je        short @1884
	or        byte ptr [_P],1
	jmp       short @1885
@1884:
	and       byte ptr [_P],-2
@1885:
	shl       byte ptr [_A],1
@1883:
	test      byte ptr [_A],-128
	je        short @1886
	or        byte ptr [_P],-128
	jmp       short @1887
@1886:
	and       byte ptr [_P],127
@1887:
	mov       dl,byte ptr [_A]
	test      dl,dl
	je        short @1888
	and       byte ptr [_P],-3
	jmp       @1741
@1888:
	or        byte ptr [_P],2
@1985:
	pop       ebx
	ret 
@1689:
	call      @MemoryTUGet$qqrv
	mov       ebx,eax
	mov       byte ptr [_tmpBYTE],bl
?live1@26912: ; EBX = @temp22
	test      byte ptr [_P],1
	je        short @1891
	test      bl,1
	je        short @1892
	or        byte ptr [_P],1
	jmp       short @1893
@1892:
	and       byte ptr [_P],-2
?live1@26944: ; 
@1893:
	shr       byte ptr [_tmpBYTE],1
	or        byte ptr [_tmpBYTE],-128
	jmp       short @1894
@1891:
	test      byte ptr [_tmpBYTE],1
	je        short @1895
	or        byte ptr [_P],1
	jmp       short @1896
@1895:
	and       byte ptr [_P],-2
@1896:
	shr       byte ptr [_tmpBYTE],1
@1894:
	test      byte ptr [_tmpBYTE],-128
	je        short @1897
	or        byte ptr [_P],-128
	jmp       short @1898
@1897:
	and       byte ptr [_P],127
@1898:
	mov       al,byte ptr [_tmpBYTE]
	test      al,al
	je        short @1899
	and       byte ptr [_P],-3
	jmp       short @1900
@1899:
	or        byte ptr [_P],2
@1900:
	mov       al,byte ptr [_tmpBYTE]
	call      @MemoryTUEquals$qqruc
@1986:
	pop       ebx
	ret 
@1670:
	test      byte ptr [_P],1
	je        short @1902
	test      byte ptr [_A],1
	je        short @1903
	or        byte ptr [_P],1
	jmp       short @1904
@1903:
	and       byte ptr [_P],-2
@1904:
	shr       byte ptr [_A],1
	or        byte ptr [_A],-128
	jmp       short @1905
@1902:
	test      byte ptr [_A],1
	je        short @1906
	or        byte ptr [_P],1
	jmp       short @1907
@1906:
	and       byte ptr [_P],-2
@1907:
	shr       byte ptr [_A],1
@1905:
	test      byte ptr [_A],-128
	je        short @1908
	or        byte ptr [_P],-128
	jmp       short @1909
@1908:
	and       byte ptr [_P],127
@1909:
	mov       dl,byte ptr [_A]
	test      dl,dl
	je        short @1910
	and       byte ptr [_P],-3
	jmp       @1741
@1910:
	or        byte ptr [_P],2
@1987:
	pop       ebx
	ret 
@1688:
	xor       eax,eax
	xor       edx,edx
	mov       al,byte ptr [_SP]
	xor       ecx,ecx
	mov       dl,byte ptr [eax+_Mem+264195]
	mov       cl,byte ptr [eax+_Mem+264194]
	shl       edx,8
	or        dx,cx
	inc       edx
	movzx     edx,dx
	mov       dword ptr [_PC],edx
	mov       al,byte ptr [eax+_Mem+264193]
	mov       byte ptr [_P],al
	add       byte ptr [_SP],3
@1988:
	pop       ebx
	ret 
@1687:
	xor       eax,eax
	xor       edx,edx
	mov       al,byte ptr [_SP]
	xor       ecx,ecx
	mov       dl,byte ptr [eax+_Mem+264194]
	mov       cl,byte ptr [eax+_Mem+264193]
	shl       edx,8
	or        dx,cx
	inc       edx
	movzx     eax,dx
	mov       dword ptr [_PC],eax
	add       byte ptr [_SP],2
@1989:
	pop       ebx
	ret 
@1686:
	mov       dl,byte ptr [_TUMode]
	test      dl,dl
	je        short @1912
	call      @MemoryTUGet$qqrv
	mov       ebx,eax
	jmp       short @1913
@1912:
	mov       bl,byte ptr [_TU]
@1913:
	mov       byte ptr [_tmpBYTE],bl
?live1@27296: ; EBX = @temp24
	xor       ecx,ecx
	mov       cl,byte ptr [_P]
	xor       eax,eax
	and       cx,1
	xor       edx,edx
	mov       dl,bl
	mov       al,byte ptr [_A]
	sub       ax,dx
	xor       cx,1
	sub       ax,cx
	mov       word ptr [_tmpshortint],ax
?live1@27312: ; EAX = @temp25
	test      ax,ax
	jge       short @1914
	and       byte ptr [_P],-2
	jmp       short @1915
@1914:
	or        byte ptr [_P],1
?live1@27328: ; 
@1915:
	mov       al,byte ptr [_A]
	mov       edx,eax
	mov       cl,byte ptr [_tmpBYTE]
	xor       dl,cl
	mov       cl,byte ptr [_tmpshortint]
	xor       al,cl
	and       dl,al
	test      dl,-128
	je        short @1916
	or        byte ptr [_P],64
	jmp       short @1917
@1916:
	and       byte ptr [_P],-65
@1917:
	mov       al,byte ptr [_tmpshortint]
	mov       byte ptr [_A],al
?live1@27360: ; EAX = @temp27
	test      al,-128
	je        short @1918
	or        byte ptr [_P],-128
	jmp       short @1919
@1918:
	and       byte ptr [_P],127
@1919:
	mov       dl,byte ptr [_A]
	test      dl,dl
	je        short @1920
	and       byte ptr [_P],-3
	jmp       @1741
@1920:
	or        byte ptr [_P],2
?live1@27376: ; 
@1990:
	pop       ebx
	ret 
@1685:
	or        byte ptr [_P],1
@1991:
	pop       ebx
	ret 
@1684:
	or        byte ptr [_P],8
@1992:
	pop       ebx
	ret 
@1683:
	or        byte ptr [_P],4
@1993:
	pop       ebx
	ret 
@1682:
	mov       al,byte ptr [_A]
	call      @MemoryTUEquals$qqruc
@1994:
	pop       ebx
	ret 
@1681:
	mov       al,byte ptr [_X]
	call      @MemoryTUEquals$qqruc
@1995:
	pop       ebx
	ret 
@1680:
	mov       al,byte ptr [_Y]
	call      @MemoryTUEquals$qqruc
@1996:
	pop       ebx
	ret 
@1679:
	mov       al,byte ptr [_A]
	mov       byte ptr [_X],al
?live1@27600: ; EAX = @temp28
	test      al,-128
	je        short @1922
	or        byte ptr [_P],-128
	jmp       short @1923
@1922:
	and       byte ptr [_P],127
@1923:
	mov       dl,byte ptr [_X]
	test      dl,dl
	je        short @1924
	and       byte ptr [_P],-3
	jmp       @1741
@1924:
	or        byte ptr [_P],2
?live1@27616: ; 
@1997:
	pop       ebx
	ret 
@1678:
	mov       al,byte ptr [_A]
	mov       byte ptr [_Y],al
?live1@27648: ; EAX = @temp29
	test      al,-128
	je        short @1926
	or        byte ptr [_P],-128
	jmp       short @1927
@1926:
	and       byte ptr [_P],127
@1927:
	mov       dl,byte ptr [_Y]
	test      dl,dl
	je        short @1928
	and       byte ptr [_P],-3
	jmp       @1741
@1928:
	or        byte ptr [_P],2
?live1@27664: ; 
@1998:
	pop       ebx
	ret 
@1677:
	mov       al,byte ptr [_SP]
	mov       byte ptr [_X],al
?live1@27696: ; EAX = @temp30
	test      al,-128
	je        short @1930
	or        byte ptr [_P],-128
	jmp       short @1931
@1930:
	and       byte ptr [_P],127
@1931:
	mov       dl,byte ptr [_X]
	test      dl,dl
	je        short @1932
	and       byte ptr [_P],-3
	jmp       @1741
@1932:
	or        byte ptr [_P],2
?live1@27712: ; 
@1999:
	pop       ebx
	ret 
@1676:
	mov       cl,byte ptr [_X]
	mov       byte ptr [_A],cl
	test      byte ptr [_A],-128
	je        short @1934
	or        byte ptr [_P],-128
	jmp       short @1935
@1934:
	and       byte ptr [_P],127
@1935:
	mov       al,byte ptr [_A]
	test      al,al
	je        short @1936
	and       byte ptr [_P],-3
	jmp       short @1741
@1936:
	or        byte ptr [_P],2
@2000:
	pop       ebx
	ret 
@1675:
	mov       dl,byte ptr [_X]
	mov       byte ptr [_SP],dl
@2001:
	pop       ebx
	ret 
@1674:
	mov       cl,byte ptr [_Y]
	mov       byte ptr [_A],cl
	test      byte ptr [_Y],-128
	je        short @1938
	or        byte ptr [_P],-128
	jmp       short @1939
@1938:
	and       byte ptr [_P],127
@1939:
	mov       al,byte ptr [_Y]
	test      al,al
	je        short @1940
	and       byte ptr [_P],-3
	jmp       short @1741
@1940:
	or        byte ptr [_P],2
@2002:
	pop       ebx
	ret 
@1943:
@1741:
	pop       ebx
	ret 
@ExecOp$qqruc	endp
	align	4
@ToBin$qqruc	proc	near
?live1@27872:
@2003:
	mov       edx,offset s@+1229
?live1@27888: ; EDX = tmpvar, EAX = tc
	test      al,1
	je        short @2004
	mov       byte ptr [edx+7],49
	jmp       short @2005
@2004:
	mov       byte ptr [edx+7],48
@2005:
	test      al,2
	je        short @2006
	mov       byte ptr [edx+6],49
	jmp       short @2007
@2006:
	mov       byte ptr [edx+6],48
@2007:
	test      al,4
	je        short @2008
	mov       byte ptr [edx+5],49
	jmp       short @2009
@2008:
	mov       byte ptr [edx+5],48
@2009:
	test      al,8
	je        short @2010
	mov       byte ptr [edx+4],49
	jmp       short @2011
@2010:
	mov       byte ptr [edx+4],48
@2011:
	test      al,16
	je        short @2012
	mov       byte ptr [edx+3],49
	jmp       short @2013
@2012:
	mov       byte ptr [edx+3],48
@2013:
	test      al,32
	je        short @2014
	mov       byte ptr [edx+2],49
	jmp       short @2015
@2014:
	mov       byte ptr [edx+2],48
@2015:
	test      al,64
	je        short @2016
	mov       byte ptr [edx+1],49
	jmp       short @2017
@2016:
	mov       byte ptr [edx+1],48
@2017:
	test      al,-128
	je        short @2018
	mov       byte ptr [edx],49
	jmp       short @2019
@2018:
	mov       byte ptr [edx],48
?live1@28016: ; EDX = tmpvar
@2019:
	mov       eax,edx
?live1@28032: ; 
@2021:
@2020:
	ret 
@ToBin$qqruc	endp
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@_$DCIB$@ToBinC$qucucuc	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-8
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-12
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	20
	dd	8
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	52
	dd	8
	dd	0
	align	4
@_$ECTJB$@ToBinC$qucucuc	label	dword
	dd	0
	dd	-48
	dw	0
	dw	5
	dd	0
	dd	@_$DCIB$@ToBinC$qucucuc+16
	dw	0
	dw	5
	dd	0
	dd	@_$DCIB$@ToBinC$qucucuc
	dw	20
	dw	5
	dd	1
	dd	@_$DCIB$@ToBinC$qucucuc+32
	dw	20
	dw	5
	dd	1
	dd	@_$DCIB$@ToBinC$qucucuc+48
	dw	20
	dw	5
	dd	1
	dd	@_$DCIB$@ToBinC$qucucuc+64
	dw	56
	dw	5
	dd	1
	dd	@_$DCIB$@ToBinC$qucucuc+80
_DATA	ends
_TEXT	segment dword public use32 'CODE'
	align	4
@ToBinC$qucucuc	proc	near
?live1@28048:
@2022:
	push      ebp
	mov       ebp,esp
	add       esp,-48
	mov       eax,offset @_$ECTJB$@ToBinC$qucucuc
	push      ebx
	push      esi
	mov       ebx,dword ptr [ebp+20]
	call      @__InitExceptBlockLDTC
?live1@28064: ; EBX = eb
	mov       word ptr [ebp-32],8
	xor       edx,edx
	mov       dword ptr [ebp-4],edx
	inc       dword ptr [ebp-20]
	mov       word ptr [ebp-32],20
@2023:
	movzx     esi,byte ptr [ebp+16]
	jmp       short @2025
?live1@28096: ; ESI = i, EBX = eb, EAX = @temp2
@2024:
	mov       ecx,eax
	mov       eax,1
	sub       ecx,esi
	xor       edx,edx
	shl       eax,cl
	mov       dl,byte ptr [ebp+12]
	and       eax,edx
	je        short @2026
	mov       word ptr [ebp-32],32
	mov       edx,offset s@+1238
	lea       eax,dword ptr [ebp-8]
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-20]
	lea       edx,dword ptr [ebp-8]
	lea       eax,dword ptr [ebp-4]
	call      @System@AnsiString@$brplu$qqrrx17System@AnsiString
	dec       dword ptr [ebp-20]
	lea       eax,dword ptr [ebp-8]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
	jmp       short @2027
@2026:
	mov       word ptr [ebp-32],44
	mov       edx,offset s@+1240
	lea       eax,dword ptr [ebp-12]
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-20]
	lea       edx,dword ptr [ebp-12]
	lea       eax,dword ptr [ebp-4]
	call      @System@AnsiString@$brplu$qqrrx17System@AnsiString
	dec       dword ptr [ebp-20]
	lea       eax,dword ptr [ebp-12]
	mov       edx,2
	call      @System@AnsiString@$bdtr$qqrv
?live1@28112: ; ESI = i, EBX = eb
@2027:
@2028:
	inc       esi
@2025:
	xor       eax,eax
	mov       al,bl
	cmp       esi,eax
	jle       @2024
?live1@28128: ; 
	mov       word ptr [ebp-32],56
	lea       edx,dword ptr [ebp-4]
	mov       eax,dword ptr [ebp+8]
	call      @System@AnsiString@$basg$qqrrx17System@AnsiString
	mov       eax,dword ptr [ebp+8]
	mov       edx,2
	mov       word ptr [ebp-32],68
	push      eax
	lea       eax,dword ptr [ebp-4]
	dec       dword ptr [ebp-20]
	call      @System@AnsiString@$bdtr$qqrv
	pop       eax
	mov       word ptr [ebp-32],56
	inc       dword ptr [ebp-20]
	mov       edx,dword ptr [ebp-48]
	mov       dword ptr fs:[0],edx
@2031:
@2030:
	pop       esi
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@ToBinC$qucucuc	endp
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@JoypadSt@UpdateSig$qqrv	segment virtual
	align	2
@@JoypadSt@UpdateSig$qqrv	proc	near
?live16385@0:
@2032:
	mov       dl,byte ptr [eax]
	sub       dl,1
	jae       short @2033
?live16385@16: ; EAX = this
	mov       byte ptr [eax+18],1
	mov       byte ptr [eax+19],0
	mov       byte ptr [eax+20],0
	mov       byte ptr [eax+21],0
@2033:
@2036:
	mov       cl,byte ptr [eax+1]
	sub       cl,1
	jb        short @2041
	je        short @2040
	dec       cl
	je        short @2039
@2044:
	ret 
@2041:
	mov       byte ptr [eax+42],0
	mov       byte ptr [eax+43],1
	mov       byte ptr [eax+44],0
	mov       byte ptr [eax+45],0
?live16385@64: ; 
@2045:
	ret 
?live16385@80: ; EAX = this
@2040:
	mov       byte ptr [eax+42],0
	mov       byte ptr [eax+43],0
	mov       byte ptr [eax+44],0
	mov       byte ptr [eax+45],0
?live16385@96: ; 
@2046:
	ret 
?live16385@112: ; EAX = this
@2039:
	mov       byte ptr [eax+42],0
	mov       byte ptr [eax+43],0
	mov       byte ptr [eax+44],0
	mov       byte ptr [eax+45],0
?live16385@128: ; 
@2037:
@2042:
@2043:
	ret 
@@JoypadSt@UpdateSig$qqrv	endp
@JoypadSt@UpdateSig$qqrv	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@MemSt@SetupPointers$qqrv	segment virtual
	align	2
@@MemSt@SetupPointers$qqrv	proc	near
?live16386@0:
@2047:
	push      ebx
	push      esi
	push      edi
	mov       ecx,eax
?live16386@16: ; ECX = this
@2048:
	xor       edx,edx
	mov       eax,ecx
?live16386@32: ; ECX = this, EAX = @temp2, EDX = i
@2049:
	lea       ebx,dword ptr [edx+ecx+262144]
	mov       dword ptr [eax],ebx
?live16386@48: ; ECX = this, EAX = @temp2, EDX = i, EBX = @temp10
	mov       dword ptr [eax+8192],ebx
	mov       dword ptr [eax+16384],ebx
	mov       dword ptr [eax+24576],ebx
?live16386@96: ; ECX = this, EAX = @temp2, EDX = i
@2051:
	inc       edx
	add       eax,4
	cmp       edx,2048
	jl        short @2049
?live16386@112: ; ECX = this
@2053:
	mov       edx,256
	lea       eax,dword ptr [ecx+1024]
?live16386@128: ; ECX = this, EAX = @temp3, EDX = i
@2054:
	mov       ebx,edx
	and       ebx,255
	add       ebx,ecx
	add       ebx,264192
	mov       dword ptr [eax],ebx
?live16386@144: ; ECX = this, EAX = @temp3, EDX = i, EBX = @temp11
	mov       dword ptr [eax+8192],ebx
	mov       dword ptr [eax+16384],ebx
	mov       dword ptr [eax+24576],ebx
?live16386@192: ; ECX = this, EAX = @temp3, EDX = i
@2056:
	inc       edx
	add       eax,4
	cmp       edx,512
	jl        short @2054
?live16386@208: ; ECX = this
@2058:
	mov       eax,8192
	lea       edx,dword ptr [ecx+32768]
?live16386@224: ; ECX = this, EAX = i, EDX = @temp20
@2059:
	mov       ebx,eax
	and       ebx,-2147483641
	jns       short @2061
	dec       ebx
	or        ebx,-8
	inc       ebx
@2061:
	add       ebx,ecx
	add       ebx,264448
	mov       dword ptr [edx],ebx
@2062:
	inc       eax
	add       edx,4
	cmp       eax,16384
	jl        short @2059
?live16386@256: ; ECX = this
@2064:
	mov       ebx,16384
	lea       esi,dword ptr [ecx+65536]
?live16386@272: ; ECX = this, EBX = i, ESI = @temp21
@2065:
	lea       eax,dword ptr [ebx-16384]
	mov       edi,24
	cdq
	idiv      edi
	add       edx,ecx
	add       edx,264456
	mov       dword ptr [esi],edx
@2067:
	inc       ebx
	add       esi,4
	cmp       ebx,24576
	jl        short @2065
?live16386@304: ; ECX = this
@2069:
	mov       eax,24576
	lea       edx,dword ptr [ecx+98304]
?live16386@320: ; ECX = this, EAX = i, EDX = @temp22
@2070:
	lea       ebx,dword ptr [eax+ecx+248096]
	mov       dword ptr [edx],ebx
@2072:
	inc       eax
	add       edx,4
	cmp       eax,32768
	jl        short @2070
?live16386@352: ; ECX = this
@2074:
	mov       eax,32768
	lea       edx,dword ptr [ecx+131072]
?live16386@368: ; ECX = this, EAX = i, EDX = @temp23
@2075:
	lea       ebx,dword ptr [eax+ecx+248096]
	mov       dword ptr [edx],ebx
@2077:
	inc       eax
	add       edx,4
	cmp       eax,49152
	jl        short @2075
?live16386@400: ; ECX = this
@2079:
	mov       eax,49152
	lea       edx,dword ptr [ecx+196608]
?live16386@416: ; ECX = this, EAX = i, EDX = @temp24
@2080:
	lea       ebx,dword ptr [eax+ecx+248096]
	mov       dword ptr [edx],ebx
@2082:
	inc       eax
	add       edx,4
	cmp       eax,65536
	jl        short @2080
?live16386@448: ; ECX = this
@2084:
	xor       eax,eax
	lea       edx,dword ptr [ecx+313632]
?live16386@464: ; ECX = this, EAX = i, EDX = @temp25
@2085:
	lea       ebx,dword ptr [eax+ecx]
	mov       esi,ebx
?live16386@480: ; ECX = this, EAX = i, EDX = @temp25, EBX = @temp27
	add       ebx,383264
?live16386@496: ; ECX = this, EAX = i, EDX = @temp25
	add       esi,379168
	mov       dword ptr [edx],esi
?live16386@512: ; ECX = this, EAX = i, EDX = @temp25, EBX = @temp27
	mov       esi,eax
	or        esi,4096
	mov       dword ptr [ecx+4*esi+313632],ebx
?live16386@528: ; ECX = this, EAX = i, EDX = @temp25
@2087:
	inc       eax
	add       edx,4
	cmp       eax,4096
	jl        short @2085
?live16386@544: ; ECX = this
@2089:
	xor       edx,edx
	lea       eax,dword ptr [ecx+346400]
?live16386@560: ; ECX = this, EAX = @temp4, EDX = i
@2090:
	lea       ebx,dword ptr [edx+ecx]
	mov       esi,ebx
	add       esi,387360
?live16386@576: ; ECX = this, EAX = @temp4, EDX = i, EBX = @temp28, ESI = @temp29
	;	
	add       ebx,388320
?live16386@592: ; ECX = this, EAX = @temp4, EDX = i
	mov       dword ptr [eax],esi
?live16386@608: ; ECX = this, EAX = @temp4, EDX = i, EBX = @temp28, ESI = @temp29
	;	
	mov       dword ptr [eax+4096],ebx
?live16386@624: ; ECX = this, EAX = @temp4, EDX = i
	lea       ebx,dword ptr [edx+ecx+388320]
?live16386@640: ; ECX = this, EAX = @temp4, EDX = i, ESI = @temp29
	mov       dword ptr [eax+8192],esi
?live16386@656: ; ECX = this, EAX = @temp4, EDX = i
	mov       dword ptr [eax+12288],ebx
@2092:
	inc       edx
	add       eax,4
	cmp       edx,960
	jl        short @2090
?live16386@688: ; ECX = this
@2094:
	mov       edx,960
	lea       eax,dword ptr [ecx+350240]
?live16386@704: ; ECX = this, EAX = @temp1, EDX = i
@2095:
	lea       ebx,dword ptr [edx+ecx]
	add       ebx,390240
	mov       dword ptr [eax],ebx
	lea       ebx,dword ptr [edx+ecx]
	add       ebx,390304
	mov       dword ptr [eax+4096],ebx
	lea       ebx,dword ptr [edx+ecx+390240]
	mov       dword ptr [eax+8192],ebx
	lea       ebx,dword ptr [edx+ecx+390304]
	mov       dword ptr [eax+12288],ebx
@2097:
	inc       edx
	add       eax,4
	cmp       edx,1024
	jl        short @2095
?live16386@784: ; ECX = this
@2099:
	mov       edx,12288
	lea       eax,dword ptr [ecx+346400]
?live16386@800: ; ECX = this, EAX = @temp1, EDX = i
@2100:
	mov       ebx,dword ptr [eax]
	mov       dword ptr [eax+16384],ebx
@2102:
	inc       edx
	add       eax,4
	cmp       edx,16128
	jl        short @2100
?live16386@832: ; ECX = this
@2104:
	mov       edx,16128
	lea       eax,dword ptr [ecx+378144]
?live16386@848: ; ECX = this, EAX = @temp1, EDX = i
@2105:
	mov       ebx,edx
	and       ebx,15
	add       ebx,ecx
	add       ebx,391456
	mov       dword ptr [eax],ebx
@2107:
	inc       edx
	add       eax,4
	cmp       edx,16144
	jl        short @2105
?live16386@880: ; ECX = this
@2109:
	mov       edx,16144
	lea       eax,dword ptr [ecx+378208]
?live16386@896: ; ECX = this, EAX = @temp1, EDX = i
@2110:
	mov       ebx,edx
	and       ebx,15
	add       ebx,ecx
	add       ebx,391472
	mov       dword ptr [eax],ebx
@2112:
	inc       edx
	add       eax,4
	cmp       edx,16160
	jl        short @2110
?live16386@928: ; ECX = this
	mov       eax,dword ptr [ecx+378144]
	mov       dword ptr [ecx+378208],eax
	mov       edx,dword ptr [ecx+378160]
	mov       dword ptr [ecx+378224],edx
	mov       eax,dword ptr [ecx+378176]
	mov       dword ptr [ecx+378240],eax
	mov       edx,dword ptr [ecx+378192]
	mov       dword ptr [ecx+378256],edx
@2114:
	mov       edx,16160
	lea       eax,dword ptr [ecx+378272]
?live16386@1008: ; ECX = this, EAX = @temp1, EDX = i
@2115:
	mov       ebx,edx
	and       ebx,16159
	mov       ebx,dword ptr [ecx+4*ebx+313632]
	mov       dword ptr [eax],ebx
@2117:
	inc       edx
	add       eax,4
	cmp       edx,16384
	jl        short @2115
?live16386@1040: ; 
@2119:
	pop       edi
	pop       esi
	pop       ebx
	ret 
@@MemSt@SetupPointers$qqrv	endp
@MemSt@SetupPointers$qqrv	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@JoypadSt@Get$qqr4bool	segment virtual
	align	2
@@JoypadSt@Get$qqr4bool	proc	near
?live16388@0:
@2120:
	push      ebx
	push      esi
	mov       esi,eax
?live16388@16: ; ESI = this, EDX = JN
	xor       ebx,ebx
?live16388@32: ; ESI = this, EBX = tmpb, EDX = JN
	test      dl,dl
	je        @2121
?live16388@48: ; ESI = this, EDX = JN
	mov       bl,64
?live16388@64: ; ESI = this, EBX = tmpb, EDX = JN
	mov       al,byte ptr [esi+1]
	sub       al,1
	jb        short @2126
	je        short @2125
	dec       al
	je        short @2124
	jmp       @2127
@2126:
	xor       ecx,ecx
	mov       al,byte ptr [esi+57]
	mov       cl,byte ptr [esi+51]
	shl       eax,3
	or        bl,byte ptr [esi+ecx+26]
	mov       cl,byte ptr [esi+56]
	or        bl,al
	xor       cl,1
	shl       ecx,4
	or        bl,cl
	jmp       @2127
@2125:
	mov       al,byte ptr [esi+51]
	cmp       al,8
	jae       short @2128
?live16388@240: ; ESI = this, EBX = tmpb, EDX = JN, EAX = @temp4
	xor       ecx,ecx
	mov       cl,al
	push      ecx
	mov       ecx,7
	pop       eax
	sub       ecx,eax
	mov       eax,1
	shl       eax,cl
	xor       ecx,ecx
	mov       cl,byte ptr [esi+55]
	and       eax,ecx
	setne     al
	and       eax,1
	xor       al,1
	add       eax,eax
	or        bl,al
	jmp       short @2127
@2128:
	xor       ecx,ecx
	mov       cl,al
	or        bl,byte ptr [esi+ecx+26]
?live16388@272: ; ESI = this, EBX = tmpb, EDX = JN
	jmp       short @2127
@2124:
	mov       al,byte ptr [esi+57]
	mov       cl,byte ptr [esi+56]
	shl       eax,3
	xor       cl,1
	shl       ecx,4
	or        bl,al
	or        bl,cl
	jmp       short @2127
@2121:
	mov       al,byte ptr [esi+1]
	cmp       al,1
	jne       short @2129
	mov       cl,byte ptr [esi+54]
	add       ecx,ecx
	or        bl,cl
@2129:
	mov       al,byte ptr [esi+62]
	shl       eax,5
	mov       byte ptr [esi+62],0
	mov       cl,byte ptr [esi]
	or        bl,al
	sub       cl,1
	jae       short @2130
	xor       eax,eax
	mov       cl,byte ptr [esi+57]
	mov       al,byte ptr [esi+50]
	shl       ecx,3
	or        bl,byte ptr [esi+eax+2]
	mov       al,byte ptr [esi+56]
	or        bl,cl
	xor       al,1
	shl       eax,4
	or        bl,al
@2130:
@2133:
@2127:
	movsx     eax,dl
	inc       byte ptr [esi+eax+50]
?live16388@640: ; ESI = this, EBX = tmpb, EDX = JN, EAX = @temp3
	mov       cl,byte ptr [esi+eax+50]
	cmp       cl,24
	jne       short @2134
	mov       byte ptr [esi+eax+50],0
?live16388@656: ; EBX = tmpb
@2134:
	mov       eax,ebx
?live16388@672: ; 
@2136:
@2135:
	pop       esi
	pop       ebx
	ret 
@@JoypadSt@Get$qqr4bool	endp
@JoypadSt@Get$qqr4bool	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@MMC1St@UpdateReg$qqruc	segment virtual
	align	2
@@MMC1St@UpdateReg$qqruc	proc	near
?live16389@0:
@2137:
	push      ebx
	mov       ebx,eax
?live16389@16: ; EBX = this, EDX = regnum
	xor       eax,eax
	mov       al,dl
	mov       cl,byte ptr [ebx]
	sub       dl,1
	mov       byte ptr [ebx+eax+2],cl
	mov       byte ptr [ebx+1],0
	mov       byte ptr [ebx],0
	jb        short @2143
	je        @2142
	dec       dl
	je        @2141
	dec       dl
	je        @2140
@2192:
	pop       ebx
	ret 
?live16389@96: ; EBX = this
@2143:
	xor       edx,edx
	mov       dl,byte ptr [ebx+2]
	and       edx,3
	sub       edx,1
	jb        short @2149
	je        short @2148
	dec       edx
	je        short @2147
	dec       edx
	je        short @2146
	jmp       short @2144
@2149:
	push      0
	push      0
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       short @2150
@2148:
	push      1
	push      1
	push      1
	push      1
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       short @2150
@2147:
	push      1
	push      0
	push      1
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
	jmp       short @2150
@2146:
	push      2
	push      2
	push      0
	push      0
	push      offset _Mem
	call      @@MemSt@UpdateNameTablePointers$qucucucuc
	add       esp,20
@2144:
@2150:
	test      byte ptr [ebx+2],4
	setne     al
	and       eax,1
	mov       byte ptr [ebx+6],al
	test      byte ptr [ebx+2],8
	setne     dl
	and       edx,1
	mov       byte ptr [ebx+7],dl
	test      byte ptr [ebx+2],16
	setne     cl
	and       ecx,1
	mov       byte ptr [ebx+8],cl
?live16389@224: ; 
@2193:
	pop       ebx
	ret 
?live16389@240: ; EBX = this
@2142:
	mov       al,byte ptr [ebx+8]
	test      al,al
	je        short @2152
	xor       eax,eax
	mov       al,byte ptr [ebx+3]
	and       ax,15
	shl       eax,2
	and       ax,word ptr [_Mem+391764]
?live16389@272: ; EBX = this, EAX = tpbt
	mov       word ptr [_Mem+391790],ax
	lea       edx,dword ptr [eax+1]
	mov       word ptr [_Mem+391792],dx
	lea       ecx,dword ptr [eax+2]
	mov       word ptr [_Mem+391794],cx
	add       eax,3
	mov       word ptr [_Mem+391796],ax
?live16389@304: ; EBX = this
	jmp       short @2153
@2152:
	xor       eax,eax
	mov       al,byte ptr [ebx+3]
	and       ax,15
	shl       eax,2
	and       ax,word ptr [_Mem+391764]
?live16389@336: ; EBX = this, EAX = tpbt
	mov       word ptr [_Mem+391790],ax
	lea       edx,dword ptr [eax+1]
	mov       word ptr [_Mem+391792],dx
	lea       ecx,dword ptr [eax+2]
	mov       word ptr [_Mem+391794],cx
	lea       edx,dword ptr [eax+3]
	mov       word ptr [_Mem+391796],dx
	lea       ecx,dword ptr [eax+4]
	mov       word ptr [_Mem+391798],cx
	lea       edx,dword ptr [eax+5]
	mov       word ptr [_Mem+391800],dx
	lea       ecx,dword ptr [eax+6]
	mov       word ptr [_Mem+391802],cx
	add       eax,7
	mov       word ptr [_Mem+391804],ax
?live16389@400: ; EBX = this
@2153:
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @2154
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@2154:
@2155:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @2156
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@2156:
@2157:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @2158
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@2158:
@2159:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @2160
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@2160:
@2161:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @2162
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@2162:
@2163:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @2164
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@2164:
@2165:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @2166
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@2166:
@2167:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @2168
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@2168:
@2169:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
	test      byte ptr [ebx+3],16
	setne     cl
	and       ecx,1
	mov       byte ptr [ebx+9],cl
?live16389@432: ; 
@2194:
	pop       ebx
	ret 
?live16389@448: ; EBX = this
@2141:
	mov       al,byte ptr [ebx+8]
	test      al,al
	je        @2151
	xor       eax,eax
	mov       al,byte ptr [ebx+4]
	and       ax,15
	shl       eax,2
	and       ax,word ptr [_Mem+391764]
?live16389@480: ; EAX = tpbt
	mov       word ptr [_Mem+391798],ax
	lea       edx,dword ptr [eax+1]
	mov       word ptr [_Mem+391800],dx
	lea       ecx,dword ptr [eax+2]
	mov       word ptr [_Mem+391802],cx
	add       eax,3
	mov       word ptr [_Mem+391804],ax
?live16389@512: ; 
	mov       ax,word ptr [_Mem+391790]
	cmp       ax,word ptr [_Mem+391774]
	je        short @2171
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+379168
	call      _memcpy
	add       esp,12
@2171:
@2172:
	mov       ax,word ptr [_Mem+391792]
	cmp       ax,word ptr [_Mem+391776]
	je        short @2173
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+380192
	call      _memcpy
	add       esp,12
@2173:
@2174:
	mov       ax,word ptr [_Mem+391794]
	cmp       ax,word ptr [_Mem+391778]
	je        short @2175
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+381216
	call      _memcpy
	add       esp,12
@2175:
@2176:
	mov       ax,word ptr [_Mem+391796]
	cmp       ax,word ptr [_Mem+391780]
	je        short @2177
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+382240
	call      _memcpy
	add       esp,12
@2177:
@2178:
	mov       ax,word ptr [_Mem+391798]
	cmp       ax,word ptr [_Mem+391782]
	je        short @2179
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+383264
	call      _memcpy
	add       esp,12
@2179:
@2180:
	mov       ax,word ptr [_Mem+391800]
	cmp       ax,word ptr [_Mem+391784]
	je        short @2181
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+384288
	call      _memcpy
	add       esp,12
@2181:
@2182:
	mov       ax,word ptr [_Mem+391802]
	cmp       ax,word ptr [_Mem+391786]
	je        short @2183
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+385312
	call      _memcpy
	add       esp,12
@2183:
@2184:
	mov       ax,word ptr [_Mem+391804]
	cmp       ax,word ptr [_Mem+391788]
	je        short @2185
	movsx     edx,ax
	shl       edx,10
	push      1024
	add       edx,offset _Mem+1440382
	push      edx
	push      offset _Mem+386336
	call      _memcpy
	add       esp,12
@2185:
@2186:
	push      8
	push      offset _Mem+391790
	push      offset _Mem+391774
	call      _memcpy
	add       esp,12
@2195:
	pop       ebx
	ret 
?live16389@544: ; EBX = this
@2140:
	mov       cl,byte ptr [ebx+7]
	test      cl,cl
	jne       short @2187
	mov       dl,byte ptr [ebx+9]
	mov       al,byte ptr [ebx+5]
	shl       edx,4
	and       al,15
	or        al,dl
	mov       cl,byte ptr [_Mem+391762]
	add       eax,eax
	and       al,cl
	and       eax,255
?live16389@576: ; EAX = tpbt
	mov       word ptr [_Mem+391766],ax
	lea       edx,dword ptr [eax+1]
	mov       word ptr [_Mem+391768],dx
	lea       ecx,dword ptr [eax+2]
	mov       word ptr [_Mem+391770],cx
	add       eax,3
	mov       word ptr [_Mem+391772],ax
?live16389@608: ; 
	jmp       short @2188
?live16389@624: ; EBX = this
@2187:
	mov       dl,byte ptr [ebx+9]
	mov       al,byte ptr [ebx+5]
	shl       edx,4
	and       al,15
	or        al,dl
	mov       cl,byte ptr [_Mem+391762]
	add       eax,eax
?live16389@640: ; EBX = this, EAX = tpbt
	mov       dl,byte ptr [ebx+6]
?live16389@656: ; EBX = this
	and       al,cl
	and       eax,255
?live16389@672: ; EBX = this, EAX = tpbt
	test      dl,dl
	je        short @2189
?live16389@688: ; EAX = tpbt
	mov       word ptr [_Mem+391766],ax
	inc       eax
	mov       word ptr [_Mem+391768],ax
?live16389@704: ; 
	jmp       short @2190
?live16389@720: ; EAX = tpbt
@2189:
	mov       word ptr [_Mem+391770],ax
	inc       eax
	mov       word ptr [_Mem+391772],ax
?live16389@736: ; 
@2190:
@2188:
	call      @UpdateGGCodes$qqrv
@2138:
@2191:
@2151:
	pop       ebx
	ret 
@@MMC1St@UpdateReg$qqruc	endp
@MMC1St@UpdateReg$qqruc	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@MemSt@UpdateNameTablePointers$qucucucuc	segment virtual
	align	2
@@MemSt@UpdateNameTablePointers$qucucucuc	proc	near
?live16390@0:
@2196:
	push      ebp
	mov       ebp,esp
	push      ebx
	push      esi
	mov       eax,dword ptr [ebp+8]
?live16390@16: ; EAX = this
	mov       dl,byte ptr [ebp+12]
	mov       byte ptr [eax+1964671],dl
	mov       cl,byte ptr [ebp+16]
	mov       byte ptr [eax+1964672],cl
	mov       dl,byte ptr [ebp+20]
	mov       byte ptr [eax+1964673],dl
	mov       cl,byte ptr [ebp+24]
	mov       byte ptr [eax+1964674],cl
@2197:
	xor       ecx,ecx
	lea       edx,dword ptr [eax+346400]
?live16390@48: ; EAX = this, EDX = @temp1, ECX = i
@2198:
	xor       ebx,ebx
	mov       bl,byte ptr [ebp+12]
	shl       ebx,6
	lea       ebx,dword ptr [ebx+2*ebx]
	lea       ebx,dword ptr [ebx+4*ebx]
	add       ebx,eax
	add       ebx,ecx
	add       ebx,387360
	mov       dword ptr [edx],ebx
	xor       ebx,ebx
	mov       bl,byte ptr [ebp+16]
	shl       ebx,6
	lea       ebx,dword ptr [ebx+2*ebx]
	lea       ebx,dword ptr [ebx+4*ebx]
	add       ebx,eax
	add       ebx,ecx
	add       ebx,387360
	mov       dword ptr [edx+4096],ebx
	xor       ebx,ebx
	mov       bl,byte ptr [ebp+20]
	shl       ebx,6
	lea       ebx,dword ptr [ebx+2*ebx]
	lea       ebx,dword ptr [ebx+4*ebx]
	add       ebx,eax
	add       ebx,ecx
	add       ebx,387360
	mov       dword ptr [edx+8192],ebx
	xor       ebx,ebx
	mov       bl,byte ptr [ebp+24]
	shl       ebx,6
	lea       ebx,dword ptr [ebx+2*ebx]
	lea       ebx,dword ptr [ebx+4*ebx]
	add       ebx,eax
	add       ebx,ecx
	add       ebx,387360
	mov       dword ptr [edx+12288],ebx
@2200:
	inc       ecx
	add       edx,4
	cmp       ecx,960
	jl        short @2198
?live16390@128: ; EAX = this
@2202:
	mov       ecx,960
	lea       edx,dword ptr [eax+350240]
?live16390@144: ; EAX = this, EDX = @temp2, ECX = i
@2203:
	movzx     esi,byte ptr [ebp+12]
	shl       esi,6
	mov       ebx,ecx
	and       ebx,63
	add       esi,eax
	add       esi,ebx
	add       esi,391200
	mov       dword ptr [edx],esi
?live16390@160: ; EAX = this, EDX = @temp2, ECX = i, EBX = @temp5
	movzx     esi,byte ptr [ebp+16]
	shl       esi,6
	add       esi,eax
	add       esi,ebx
	add       esi,391200
	mov       dword ptr [edx+4096],esi
	movzx     esi,byte ptr [ebp+20]
	shl       esi,6
	add       esi,eax
	add       esi,ebx
	add       esi,391200
	mov       dword ptr [edx+8192],esi
	movzx     esi,byte ptr [ebp+24]
	shl       esi,6
	add       esi,eax
	add       esi,ebx
	add       esi,391200
	mov       dword ptr [edx+12288],esi
?live16390@208: ; EAX = this, EDX = @temp2, ECX = i
@2205:
	inc       ecx
	add       edx,4
	cmp       ecx,1024
	jl        short @2203
?live16390@224: ; 
@2207:
	pop       esi
	pop       ebx
	pop       ebp
	ret 
@@MemSt@UpdateNameTablePointers$qucucucuc	endp
@MemSt@UpdateNameTablePointers$qucucucuc	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@System@%SmallString$iuc$255%@$basg$qqrrx28System@%SmallString$iuc$255%	segment virtual
	align	2
@@System@%SmallString$iuc$255%@$basg$qqrrx28System@%SmallString$iuc$255%	proc	near
?live16392@0:
@2208:
	push      ebx
	push      esi
?live16392@16: ; EAX = this, EDX = rhs
	cmp       edx,eax
	je        short @2215
	mov       cl,byte ptr [edx]
	mov       byte ptr [eax],cl
@2210:
	xor       esi,esi
	lea       ecx,dword ptr [eax+1]
	inc       edx
	jmp       short @2212
?live16392@64: ; EAX = this, EDX = @temp1, ECX = @temp2, ESI = i
@2211:
	mov       bl,byte ptr [edx]
	mov       byte ptr [ecx],bl
@2213:
	inc       esi
	inc       ecx
	inc       edx
@2212:
	xor       ebx,ebx
	mov       bl,byte ptr [eax]
	cmp       esi,ebx
	jl        short @2211
?live16392@96: ; 
@2216:
@2215:
	pop       esi
	pop       ebx
	ret 
@@System@%SmallString$iuc$255%@$basg$qqrrx28System@%SmallString$iuc$255%	endp
@System@%SmallString$iuc$255%@$basg$qqrrx28System@%SmallString$iuc$255%	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@System@@_$DCKB$@System@%SmallString$iuc$255%@$o17System@AnsiString$xqqrv	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	@@$xt$p17System@AnsiString
	dd	20
	dd	-8
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	52
	dd	-8
	dd	0
	align	4
@System@@_$ECTLB$@System@%SmallString$iuc$255%@$o17System@AnsiString$xqqrv	label	dword
	dd	0
	dd	-44
	dw	0
	dw	5
	dd	0
	dd	@System@@_$DCKB$@System@%SmallString$iuc$255%@$o17System@AnsiString$xqqrv
	dw	8
	dw	5
	dd	1
	dd	@System@@_$DCKB$@System@%SmallString$iuc$255%@$o17System@AnsiString$xqqrv+28
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@System@%SmallString$iuc$255%@$o17System@AnsiString$xqqrv	segment virtual
	align	2
@@System@%SmallString$iuc$255%@$o17System@AnsiString$xqqrv	proc	near
?live16393@0:
@2217:
	push      ebp
	mov       ebp,esp
	add       esp,-44
	push      ebx
	mov       dword ptr [ebp-8],edx
	mov       ebx,eax
	mov       eax,offset @System@@_$ECTLB$@System@%SmallString$iuc$255%@$o17System@AnsiString$xqqrv
	call      @__InitExceptBlockLDTC
?live16393@16: ; EBX = this
	mov       word ptr [ebp-28],8
	lea       edx,dword ptr [ebx+1]
	lea       eax,dword ptr [ebp-4]
	mov       cl,byte ptr [ebx]
	call      @System@AnsiString@$bctr$qqrpxcuc
	mov       edx,eax
	inc       dword ptr [ebp-16]
	mov       eax,dword ptr [ebp-8]
	call      @System@AnsiString@$basg$qqrrx17System@AnsiString
	mov       eax,dword ptr [ebp-8]
	mov       edx,2
	mov       word ptr [ebp-28],20
	push      eax
	lea       eax,dword ptr [ebp-4]
	dec       dword ptr [ebp-16]
	call      @System@AnsiString@$bdtr$qqrv
	pop       eax
	mov       word ptr [ebp-28],8
	inc       dword ptr [ebp-16]
	mov       edx,dword ptr [ebp-44]
	mov       dword ptr fs:[0],edx
?live16393@32: ; 
@2219:
@2218:
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@@System@%SmallString$iuc$255%@$o17System@AnsiString$xqqrv	endp
@System@%SmallString$iuc$255%@$o17System@AnsiString$xqqrv	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@System@%SmallString$iuc$31%@$basg$qqrrx27System@%SmallString$iuc$31%	segment virtual
	align	2
@@System@%SmallString$iuc$31%@$basg$qqrrx27System@%SmallString$iuc$31%	proc	near
?live16394@0:
@2220:
	push      ebx
	push      esi
?live16394@16: ; EAX = this, EDX = rhs
	cmp       edx,eax
	je        short @2227
	mov       cl,byte ptr [edx]
	mov       byte ptr [eax],cl
@2222:
	xor       esi,esi
	lea       ecx,dword ptr [eax+1]
	inc       edx
	jmp       short @2224
?live16394@64: ; EAX = this, EDX = @temp1, ECX = @temp2, ESI = i
@2223:
	mov       bl,byte ptr [edx]
	mov       byte ptr [ecx],bl
@2225:
	inc       esi
	inc       ecx
	inc       edx
@2224:
	xor       ebx,ebx
	mov       bl,byte ptr [eax]
	cmp       esi,ebx
	jl        short @2223
?live16394@96: ; 
@2228:
@2227:
	pop       esi
	pop       ebx
	ret 
@@System@%SmallString$iuc$31%@$basg$qqrrx27System@%SmallString$iuc$31%	endp
@System@%SmallString$iuc$31%@$basg$qqrrx27System@%SmallString$iuc$31%	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@System@@_$DCMB$@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	@@$xt$p17System@AnsiString
	dd	20
	dd	-8
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	52
	dd	-8
	dd	0
	align	4
@System@@_$ECTNB$@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv	label	dword
	dd	0
	dd	-44
	dw	0
	dw	5
	dd	0
	dd	@System@@_$DCMB$@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv
	dw	8
	dw	5
	dd	1
	dd	@System@@_$DCMB$@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv+28
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv	segment virtual
	align	2
@@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv	proc	near
?live16395@0:
@2229:
	push      ebp
	mov       ebp,esp
	add       esp,-44
	push      ebx
	mov       dword ptr [ebp-8],edx
	mov       ebx,eax
	mov       eax,offset @System@@_$ECTNB$@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv
	call      @__InitExceptBlockLDTC
?live16395@16: ; EBX = this
	mov       word ptr [ebp-28],8
	lea       edx,dword ptr [ebx+1]
	lea       eax,dword ptr [ebp-4]
	mov       cl,byte ptr [ebx]
	call      @System@AnsiString@$bctr$qqrpxcuc
	mov       edx,eax
	inc       dword ptr [ebp-16]
	mov       eax,dword ptr [ebp-8]
	call      @System@AnsiString@$basg$qqrrx17System@AnsiString
	mov       eax,dword ptr [ebp-8]
	mov       edx,2
	mov       word ptr [ebp-28],20
	push      eax
	lea       eax,dword ptr [ebp-4]
	dec       dword ptr [ebp-16]
	call      @System@AnsiString@$bdtr$qqrv
	pop       eax
	mov       word ptr [ebp-28],8
	inc       dword ptr [ebp-16]
	mov       edx,dword ptr [ebp-44]
	mov       dword ptr fs:[0],edx
?live16395@32: ; 
@2231:
@2230:
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv	endp
@System@%SmallString$iuc$31%@$o17System@AnsiString$xqqrv	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@System@%SmallString$iuc$64%@$basg$qqrrx27System@%SmallString$iuc$64%	segment virtual
	align	2
@@System@%SmallString$iuc$64%@$basg$qqrrx27System@%SmallString$iuc$64%	proc	near
?live16396@0:
@2232:
	push      ebx
	push      esi
?live16396@16: ; EAX = this, EDX = rhs
	cmp       edx,eax
	je        short @2239
	mov       cl,byte ptr [edx]
	mov       byte ptr [eax],cl
@2234:
	xor       esi,esi
	lea       ecx,dword ptr [eax+1]
	inc       edx
	jmp       short @2236
?live16396@64: ; EAX = this, EDX = @temp1, ECX = @temp2, ESI = i
@2235:
	mov       bl,byte ptr [edx]
	mov       byte ptr [ecx],bl
@2237:
	inc       esi
	inc       ecx
	inc       edx
@2236:
	xor       ebx,ebx
	mov       bl,byte ptr [eax]
	cmp       esi,ebx
	jl        short @2235
?live16396@96: ; 
@2240:
@2239:
	pop       esi
	pop       ebx
	ret 
@@System@%SmallString$iuc$64%@$basg$qqrrx27System@%SmallString$iuc$64%	endp
@System@%SmallString$iuc$64%@$basg$qqrrx27System@%SmallString$iuc$64%	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@System@@_$DCOB$@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	@@$xt$p17System@AnsiString
	dd	20
	dd	-8
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	52
	dd	-8
	dd	0
	align	4
@System@@_$ECTPB$@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	label	dword
	dd	0
	dd	-44
	dw	0
	dw	5
	dd	0
	dd	@System@@_$DCOB$@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv
	dw	8
	dw	5
	dd	1
	dd	@System@@_$DCOB$@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv+28
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	segment virtual
	align	2
@@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	proc	near
?live16397@0:
@2241:
	push      ebp
	mov       ebp,esp
	add       esp,-44
	push      ebx
	mov       dword ptr [ebp-8],edx
	mov       ebx,eax
	mov       eax,offset @System@@_$ECTPB$@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv
	call      @__InitExceptBlockLDTC
?live16397@16: ; EBX = this
	mov       word ptr [ebp-28],8
	lea       edx,dword ptr [ebx+1]
	lea       eax,dword ptr [ebp-4]
	mov       cl,byte ptr [ebx]
	call      @System@AnsiString@$bctr$qqrpxcuc
	mov       edx,eax
	inc       dword ptr [ebp-16]
	mov       eax,dword ptr [ebp-8]
	call      @System@AnsiString@$basg$qqrrx17System@AnsiString
	mov       eax,dword ptr [ebp-8]
	mov       edx,2
	mov       word ptr [ebp-28],20
	push      eax
	lea       eax,dword ptr [ebp-4]
	dec       dword ptr [ebp-16]
	call      @System@AnsiString@$bdtr$qqrv
	pop       eax
	mov       word ptr [ebp-28],8
	inc       dword ptr [ebp-16]
	mov       edx,dword ptr [ebp-44]
	mov       dword ptr fs:[0],edx
?live16397@32: ; 
@2243:
@2242:
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
_INIT_	segment word public use32 'INITDATA'
_INIT_	ends
@@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	endp
@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	ends
_TEXT	ends
_INIT_	segment word public use32 'INITDATA'
	db	0
	db	32
	dd	@_STCON0_$qv
_INIT_	ends
_TEXT	segment dword public use32 'CODE'
@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	segment virtual
@System@%SmallString$iuc$64%@$o17System@AnsiString$xqqrv	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@_$DCQB$@_STCON0_$qv	label	dword
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a61$17System@AnsiString
	dd	0
	dd	_Mn
	dd	@@$xt$a8$17System@AnsiString
	dd	0
	dd	_RegInfoLow
	dd	@@$xt$a8$17System@AnsiString
	dd	0
	dd	_RegInfoLow
	dd	@@$xt$a8$17System@AnsiString
	dd	0
	dd	_RegInfoLow
	dd	@@$xt$a8$17System@AnsiString
	dd	0
	dd	_RegInfoLow
	dd	@@$xt$a8$17System@AnsiString
	dd	0
	dd	_RegInfoLow
	dd	@@$xt$a8$17System@AnsiString
	dd	0
	dd	_RegInfoLow
	dd	@@$xt$a8$17System@AnsiString
	dd	0
	dd	_RegInfoLow
	dd	@@$xt$a8$17System@AnsiString
	dd	0
	dd	_RegInfoLow
	dd	@@$xt$a8$17System@AnsiString
	dd	0
	dd	_RegInfoLow
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a24$17System@AnsiString
	dd	0
	dd	_RegInfoHigh
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	@@$xt$a256$17System@AnsiString
	dd	0
	dd	_MapperInfo
	dd	0
	align	4
@_$ECTRB$@_STCON0_$qv	label	dword
	dd	0
	dd	-36
	dw	0
	dw	5
	dd	0
	dd	@_$DCQB$@_STCON0_$qv
_DATA	ends
_TEXT	segment dword public use32 'CODE'
	align	4
@_STCON0_$qv	proc	near
?live1@28160:
@2244:
	push      ebp
	mov       ebp,esp
	add       esp,-36
	mov       eax,offset @_$ECTRB$@_STCON0_$qv
	call      @__InitExceptBlockLDTC
	mov       word ptr [ebp-20],8
	mov       edx,offset s@
	mov       eax,offset _Mn
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+5
	mov       eax,offset _Mn+4
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+10
	mov       eax,offset _Mn+8
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+15
	mov       eax,offset _Mn+12
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+20
	mov       eax,offset _Mn+16
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+25
	mov       eax,offset _Mn+20
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+30
	mov       eax,offset _Mn+24
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+35
	mov       eax,offset _Mn+28
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+40
	mov       eax,offset _Mn+32
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+45
	mov       eax,offset _Mn+36
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+50
	mov       eax,offset _Mn+40
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+55
	mov       eax,offset _Mn+44
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+60
	mov       eax,offset _Mn+48
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+65
	mov       eax,offset _Mn+52
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+70
	mov       eax,offset _Mn+56
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+75
	mov       eax,offset _Mn+60
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+80
	mov       eax,offset _Mn+64
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+85
	mov       eax,offset _Mn+68
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+90
	mov       eax,offset _Mn+72
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+95
	mov       eax,offset _Mn+76
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+100
	mov       eax,offset _Mn+80
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+105
	mov       eax,offset _Mn+84
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+110
	mov       eax,offset _Mn+88
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+115
	mov       eax,offset _Mn+92
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+120
	mov       eax,offset _Mn+96
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+125
	mov       eax,offset _Mn+100
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+130
	mov       eax,offset _Mn+104
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+135
	mov       eax,offset _Mn+108
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+140
	mov       eax,offset _Mn+112
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+145
	mov       eax,offset _Mn+116
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+150
	mov       eax,offset _Mn+120
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+155
	mov       eax,offset _Mn+124
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+160
	mov       eax,offset _Mn+128
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+165
	mov       eax,offset _Mn+132
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+170
	mov       eax,offset _Mn+136
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+175
	mov       eax,offset _Mn+140
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+180
	mov       eax,offset _Mn+144
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+185
	mov       eax,offset _Mn+148
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+190
	mov       eax,offset _Mn+152
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+195
	mov       eax,offset _Mn+156
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+200
	mov       eax,offset _Mn+160
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+205
	mov       eax,offset _Mn+164
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+210
	mov       eax,offset _Mn+168
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+215
	mov       eax,offset _Mn+172
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+220
	mov       eax,offset _Mn+176
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+225
	mov       eax,offset _Mn+180
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+230
	mov       eax,offset _Mn+184
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+235
	mov       eax,offset _Mn+188
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+240
	mov       eax,offset _Mn+192
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+245
	mov       eax,offset _Mn+196
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+250
	mov       eax,offset _Mn+200
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+255
	mov       eax,offset _Mn+204
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+260
	mov       eax,offset _Mn+208
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+265
	mov       eax,offset _Mn+212
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+270
	mov       eax,offset _Mn+216
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+275
	mov       eax,offset _Mn+220
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+280
	mov       eax,offset _Mn+224
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+285
	mov       eax,offset _Mn+228
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+290
	mov       eax,offset _Mn+232
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+295
	mov       eax,offset _Mn+236
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+300
	mov       eax,offset _Mn+240
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+305
	mov       eax,offset _RegInfoLow
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+314
	mov       eax,offset _RegInfoLow+4
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+323
	mov       eax,offset _RegInfoLow+8
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+331
	mov       eax,offset _RegInfoLow+12
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+339
	mov       eax,offset _RegInfoLow+16
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+345
	mov       eax,offset _RegInfoLow+20
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+354
	mov       eax,offset _RegInfoLow+24
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+363
	mov       eax,offset _RegInfoLow+28
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+370
	mov       eax,offset _RegInfoHigh
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+379
	mov       eax,offset _RegInfoHigh+4
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+388
	mov       eax,offset _RegInfoHigh+8
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+397
	mov       eax,offset _RegInfoHigh+12
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+406
	mov       eax,offset _RegInfoHigh+16
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+415
	mov       eax,offset _RegInfoHigh+20
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+424
	mov       eax,offset _RegInfoHigh+24
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+433
	mov       eax,offset _RegInfoHigh+28
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+442
	mov       eax,offset _RegInfoHigh+32
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+450
	mov       eax,offset _RegInfoHigh+36
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+458
	mov       eax,offset _RegInfoHigh+40
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+466
	mov       eax,offset _RegInfoHigh+44
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+474
	mov       eax,offset _RegInfoHigh+48
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+482
	mov       eax,offset _RegInfoHigh+52
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+490
	mov       eax,offset _RegInfoHigh+56
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+498
	mov       eax,offset _RegInfoHigh+60
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+506
	mov       eax,offset _RegInfoHigh+64
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+515
	mov       eax,offset _RegInfoHigh+68
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+524
	mov       eax,offset _RegInfoHigh+72
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+533
	mov       eax,offset _RegInfoHigh+76
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+543
	mov       eax,offset _RegInfoHigh+80
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+550
	mov       eax,offset _RegInfoHigh+84
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+559
	mov       eax,offset _RegInfoHigh+88
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+567
	mov       eax,offset _RegInfoHigh+92
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+575
	mov       eax,offset _MapperInfo
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+585
	mov       eax,offset _MapperInfo+4
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+590
	mov       eax,offset _MapperInfo+8
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+596
	mov       eax,offset _MapperInfo+12
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+602
	mov       eax,offset _MapperInfo+16
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+607
	mov       eax,offset _MapperInfo+20
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+612
	mov       eax,offset _MapperInfo+24
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+622
	mov       eax,offset _MapperInfo+28
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+628
	mov       eax,offset _MapperInfo+32
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+638
	mov       eax,offset _MapperInfo+36
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+643
	mov       eax,offset _MapperInfo+40
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+648
	mov       eax,offset _MapperInfo+44
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+661
	mov       eax,offset _MapperInfo+48
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+662
	mov       eax,offset _MapperInfo+52
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+663
	mov       eax,offset _MapperInfo+56
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+664
	mov       eax,offset _MapperInfo+60
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+673
	mov       eax,offset _MapperInfo+64
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+680
	mov       eax,offset _MapperInfo+68
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+690
	mov       eax,offset _MapperInfo+72
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+704
	mov       eax,offset _MapperInfo+76
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+715
	mov       eax,offset _MapperInfo+80
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+716
	mov       eax,offset _MapperInfo+84
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+728
	mov       eax,offset _MapperInfo+88
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+747
	mov       eax,offset _MapperInfo+92
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+766
	mov       eax,offset _MapperInfo+96
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+778
	mov       eax,offset _MapperInfo+100
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+779
	mov       eax,offset _MapperInfo+104
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+780
	mov       eax,offset _MapperInfo+108
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+781
	mov       eax,offset _MapperInfo+112
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+782
	mov       eax,offset _MapperInfo+116
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+783
	mov       eax,offset _MapperInfo+120
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+784
	mov       eax,offset _MapperInfo+124
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+785
	mov       eax,offset _MapperInfo+128
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+796
	mov       eax,offset _MapperInfo+132
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+809
	mov       eax,offset _MapperInfo+136
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+816
	mov       eax,offset _MapperInfo+140
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+817
	mov       eax,offset _MapperInfo+144
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+818
	mov       eax,offset _MapperInfo+148
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+819
	mov       eax,offset _MapperInfo+152
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+820
	mov       eax,offset _MapperInfo+156
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+821
	mov       eax,offset _MapperInfo+160
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+822
	mov       eax,offset _MapperInfo+164
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+823
	mov       eax,offset _MapperInfo+168
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+824
	mov       eax,offset _MapperInfo+172
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+825
	mov       eax,offset _MapperInfo+176
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+826
	mov       eax,offset _MapperInfo+180
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+827
	mov       eax,offset _MapperInfo+184
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+828
	mov       eax,offset _MapperInfo+188
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+829
	mov       eax,offset _MapperInfo+192
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+830
	mov       eax,offset _MapperInfo+196
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+831
	mov       eax,offset _MapperInfo+200
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+832
	mov       eax,offset _MapperInfo+204
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+833
	mov       eax,offset _MapperInfo+208
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+834
	mov       eax,offset _MapperInfo+212
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+835
	mov       eax,offset _MapperInfo+216
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+836
	mov       eax,offset _MapperInfo+220
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+837
	mov       eax,offset _MapperInfo+224
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+838
	mov       eax,offset _MapperInfo+228
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+839
	mov       eax,offset _MapperInfo+232
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+840
	mov       eax,offset _MapperInfo+236
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+841
	mov       eax,offset _MapperInfo+240
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+842
	mov       eax,offset _MapperInfo+244
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+843
	mov       eax,offset _MapperInfo+248
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+844
	mov       eax,offset _MapperInfo+252
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+845
	mov       eax,offset _MapperInfo+256
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+860
	mov       eax,offset _MapperInfo+260
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+872
	mov       eax,offset _MapperInfo+264
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+878
	mov       eax,offset _MapperInfo+268
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+879
	mov       eax,offset _MapperInfo+272
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+897
	mov       eax,offset _MapperInfo+276
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+911
	mov       eax,offset _MapperInfo+280
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+912
	mov       eax,offset _MapperInfo+284
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+921
	mov       eax,offset _MapperInfo+288
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+922
	mov       eax,offset _MapperInfo+292
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+923
	mov       eax,offset _MapperInfo+296
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+924
	mov       eax,offset _MapperInfo+300
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+925
	mov       eax,offset _MapperInfo+304
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+926
	mov       eax,offset _MapperInfo+308
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+927
	mov       eax,offset _MapperInfo+312
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+943
	mov       eax,offset _MapperInfo+316
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+944
	mov       eax,offset _MapperInfo+320
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+945
	mov       eax,offset _MapperInfo+324
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+946
	mov       eax,offset _MapperInfo+328
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+947
	mov       eax,offset _MapperInfo+332
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+948
	mov       eax,offset _MapperInfo+336
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+949
	mov       eax,offset _MapperInfo+340
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+950
	mov       eax,offset _MapperInfo+344
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+951
	mov       eax,offset _MapperInfo+348
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+952
	mov       eax,offset _MapperInfo+352
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+953
	mov       eax,offset _MapperInfo+356
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+954
	mov       eax,offset _MapperInfo+360
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+973
	mov       eax,offset _MapperInfo+364
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+980
	mov       eax,offset _MapperInfo+368
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+981
	mov       eax,offset _MapperInfo+372
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+982
	mov       eax,offset _MapperInfo+376
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+983
	mov       eax,offset _MapperInfo+380
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+984
	mov       eax,offset _MapperInfo+384
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+985
	mov       eax,offset _MapperInfo+388
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+986
	mov       eax,offset _MapperInfo+392
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+987
	mov       eax,offset _MapperInfo+396
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+998
	mov       eax,offset _MapperInfo+400
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+999
	mov       eax,offset _MapperInfo+404
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1000
	mov       eax,offset _MapperInfo+408
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1001
	mov       eax,offset _MapperInfo+412
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1002
	mov       eax,offset _MapperInfo+416
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1003
	mov       eax,offset _MapperInfo+420
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1004
	mov       eax,offset _MapperInfo+424
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1005
	mov       eax,offset _MapperInfo+428
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1006
	mov       eax,offset _MapperInfo+432
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1007
	mov       eax,offset _MapperInfo+436
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1008
	mov       eax,offset _MapperInfo+440
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1009
	mov       eax,offset _MapperInfo+444
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1010
	mov       eax,offset _MapperInfo+448
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1011
	mov       eax,offset _MapperInfo+452
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1012
	mov       eax,offset _MapperInfo+456
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1013
	mov       eax,offset _MapperInfo+460
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1014
	mov       eax,offset _MapperInfo+464
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1015
	mov       eax,offset _MapperInfo+468
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1016
	mov       eax,offset _MapperInfo+472
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1017
	mov       eax,offset _MapperInfo+476
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1018
	mov       eax,offset _MapperInfo+480
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1019
	mov       eax,offset _MapperInfo+484
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1020
	mov       eax,offset _MapperInfo+488
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1021
	mov       eax,offset _MapperInfo+492
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1022
	mov       eax,offset _MapperInfo+496
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1023
	mov       eax,offset _MapperInfo+500
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1024
	mov       eax,offset _MapperInfo+504
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1025
	mov       eax,offset _MapperInfo+508
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1026
	mov       eax,offset _MapperInfo+512
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1027
	mov       eax,offset _MapperInfo+516
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1028
	mov       eax,offset _MapperInfo+520
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1029
	mov       eax,offset _MapperInfo+524
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1030
	mov       eax,offset _MapperInfo+528
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1031
	mov       eax,offset _MapperInfo+532
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1032
	mov       eax,offset _MapperInfo+536
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1033
	mov       eax,offset _MapperInfo+540
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1034
	mov       eax,offset _MapperInfo+544
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1035
	mov       eax,offset _MapperInfo+548
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1036
	mov       eax,offset _MapperInfo+552
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1037
	mov       eax,offset _MapperInfo+556
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1038
	mov       eax,offset _MapperInfo+560
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1039
	mov       eax,offset _MapperInfo+564
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1040
	mov       eax,offset _MapperInfo+568
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1041
	mov       eax,offset _MapperInfo+572
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1042
	mov       eax,offset _MapperInfo+576
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1043
	mov       eax,offset _MapperInfo+580
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1044
	mov       eax,offset _MapperInfo+584
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1045
	mov       eax,offset _MapperInfo+588
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1046
	mov       eax,offset _MapperInfo+592
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1047
	mov       eax,offset _MapperInfo+596
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1048
	mov       eax,offset _MapperInfo+600
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1049
	mov       eax,offset _MapperInfo+604
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1050
	mov       eax,offset _MapperInfo+608
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1051
	mov       eax,offset _MapperInfo+612
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1052
	mov       eax,offset _MapperInfo+616
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1053
	mov       eax,offset _MapperInfo+620
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1054
	mov       eax,offset _MapperInfo+624
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1055
	mov       eax,offset _MapperInfo+628
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1056
	mov       eax,offset _MapperInfo+632
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1057
	mov       eax,offset _MapperInfo+636
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1058
	mov       eax,offset _MapperInfo+640
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1059
	mov       eax,offset _MapperInfo+644
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1060
	mov       eax,offset _MapperInfo+648
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1061
	mov       eax,offset _MapperInfo+652
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1062
	mov       eax,offset _MapperInfo+656
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1063
	mov       eax,offset _MapperInfo+660
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1064
	mov       eax,offset _MapperInfo+664
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1065
	mov       eax,offset _MapperInfo+668
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1066
	mov       eax,offset _MapperInfo+672
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1067
	mov       eax,offset _MapperInfo+676
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1068
	mov       eax,offset _MapperInfo+680
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1069
	mov       eax,offset _MapperInfo+684
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1070
	mov       eax,offset _MapperInfo+688
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1071
	mov       eax,offset _MapperInfo+692
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1072
	mov       eax,offset _MapperInfo+696
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1073
	mov       eax,offset _MapperInfo+700
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1074
	mov       eax,offset _MapperInfo+704
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1075
	mov       eax,offset _MapperInfo+708
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1076
	mov       eax,offset _MapperInfo+712
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1077
	mov       eax,offset _MapperInfo+716
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1078
	mov       eax,offset _MapperInfo+720
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1079
	mov       eax,offset _MapperInfo+724
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1080
	mov       eax,offset _MapperInfo+728
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1081
	mov       eax,offset _MapperInfo+732
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1082
	mov       eax,offset _MapperInfo+736
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1083
	mov       eax,offset _MapperInfo+740
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1084
	mov       eax,offset _MapperInfo+744
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1085
	mov       eax,offset _MapperInfo+748
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1086
	mov       eax,offset _MapperInfo+752
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1087
	mov       eax,offset _MapperInfo+756
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1088
	mov       eax,offset _MapperInfo+760
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1089
	mov       eax,offset _MapperInfo+764
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1090
	mov       eax,offset _MapperInfo+768
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1091
	mov       eax,offset _MapperInfo+772
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1092
	mov       eax,offset _MapperInfo+776
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1093
	mov       eax,offset _MapperInfo+780
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1094
	mov       eax,offset _MapperInfo+784
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1095
	mov       eax,offset _MapperInfo+788
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1096
	mov       eax,offset _MapperInfo+792
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1097
	mov       eax,offset _MapperInfo+796
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1098
	mov       eax,offset _MapperInfo+800
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1099
	mov       eax,offset _MapperInfo+804
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1100
	mov       eax,offset _MapperInfo+808
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1101
	mov       eax,offset _MapperInfo+812
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1102
	mov       eax,offset _MapperInfo+816
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1103
	mov       eax,offset _MapperInfo+820
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1104
	mov       eax,offset _MapperInfo+824
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1105
	mov       eax,offset _MapperInfo+828
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1106
	mov       eax,offset _MapperInfo+832
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1107
	mov       eax,offset _MapperInfo+836
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1108
	mov       eax,offset _MapperInfo+840
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1109
	mov       eax,offset _MapperInfo+844
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1110
	mov       eax,offset _MapperInfo+848
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1111
	mov       eax,offset _MapperInfo+852
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1112
	mov       eax,offset _MapperInfo+856
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1113
	mov       eax,offset _MapperInfo+860
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1114
	mov       eax,offset _MapperInfo+864
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1115
	mov       eax,offset _MapperInfo+868
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1116
	mov       eax,offset _MapperInfo+872
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1117
	mov       eax,offset _MapperInfo+876
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1118
	mov       eax,offset _MapperInfo+880
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1119
	mov       eax,offset _MapperInfo+884
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1120
	mov       eax,offset _MapperInfo+888
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1121
	mov       eax,offset _MapperInfo+892
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1122
	mov       eax,offset _MapperInfo+896
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1123
	mov       eax,offset _MapperInfo+900
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1124
	mov       eax,offset _MapperInfo+904
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1132
	mov       eax,offset _MapperInfo+908
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1142
	mov       eax,offset _MapperInfo+912
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1152
	mov       eax,offset _MapperInfo+916
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1153
	mov       eax,offset _MapperInfo+920
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1161
	mov       eax,offset _MapperInfo+924
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1162
	mov       eax,offset _MapperInfo+928
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1163
	mov       eax,offset _MapperInfo+932
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1164
	mov       eax,offset _MapperInfo+936
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1165
	mov       eax,offset _MapperInfo+940
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1166
	mov       eax,offset _MapperInfo+944
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1167
	mov       eax,offset _MapperInfo+948
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1168
	mov       eax,offset _MapperInfo+952
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1169
	mov       eax,offset _MapperInfo+956
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1170
	mov       eax,offset _MapperInfo+960
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1171
	mov       eax,offset _MapperInfo+964
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1172
	mov       eax,offset _MapperInfo+968
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1173
	mov       eax,offset _MapperInfo+972
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1174
	mov       eax,offset _MapperInfo+976
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1175
	mov       eax,offset _MapperInfo+980
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1176
	mov       eax,offset _MapperInfo+984
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1177
	mov       eax,offset _MapperInfo+988
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1178
	mov       eax,offset _MapperInfo+992
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1179
	mov       eax,offset _MapperInfo+996
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1180
	mov       eax,offset _MapperInfo+1000
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1181
	mov       eax,offset _MapperInfo+1004
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1182
	mov       eax,offset _MapperInfo+1008
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1183
	mov       eax,offset _MapperInfo+1012
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1184
	mov       eax,offset _MapperInfo+1016
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,offset s@+1185
	mov       eax,offset _MapperInfo+1020
	call      @System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-8]
	mov       edx,dword ptr [ebp-36]
	mov       dword ptr fs:[0],edx
@2245:
	mov       esp,ebp
	pop       ebp
	ret 
_EXIT_	segment word public use32 'EXITDATA'
_EXIT_	ends
@_STCON0_$qv	endp
_TEXT	ends
_EXIT_	segment word public use32 'EXITDATA'
	db	0
	db	32
	dd	@_STDES0_$qv
_EXIT_	ends
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
_DATA	segment dword public use32 'DATA'
	align	4
@_$ECTSB$@_STDES0_$qv	label	dword
	dd	0
	dd	-36
_DATA	ends
_TEXT	segment dword public use32 'CODE'
	align	4
@_STDES0_$qv	proc	near
?live1@28192:
@2246:
	push      ebp
	mov       ebp,esp
	add       esp,-36
	mov       eax,offset @_$ECTSB$@_STDES0_$qv
	call      @__InitExceptBlockLDTC
	push      offset @System@AnsiString@$bdtr$qqrv
	push      3
	push      256
	push      4
	push      offset _MapperInfo
	call      @_vector_delete_ldtc_$qpvuiuiuit1
	add       esp,20
	push      offset @System@AnsiString@$bdtr$qqrv
	push      3
	push      24
	push      4
	push      offset _RegInfoHigh
	call      @_vector_delete_ldtc_$qpvuiuiuit1
	add       esp,20
	push      offset @System@AnsiString@$bdtr$qqrv
	push      3
	push      8
	push      4
	push      offset _RegInfoLow
	call      @_vector_delete_ldtc_$qpvuiuiuit1
	add       esp,20
	push      offset @System@AnsiString@$bdtr$qqrv
	push      3
	push      61
	push      4
	push      offset _Mn
	call      @_vector_delete_ldtc_$qpvuiuiuit1
	add       esp,20
	mov       edx,dword ptr [ebp-36]
	mov       dword ptr fs:[0],edx
@2247:
	mov       esp,ebp
	pop       ebp
	ret 
@_STDES0_$qv	endp
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$a256$17System@AnsiString	segment virtual
	align	2
@@$xt$a256$17System@AnsiString	label	byte
	dd	1024
	dw	1024
	dw	16
	dd	@@$xt$17System@AnsiString
	dd	256
	db	83
	db	121
	db	115
	db	116
	db	101
	db	109
	db	58
	db	58
	db	65
	db	110
	db	115
	db	105
	db	83
	db	116
	db	114
	db	105
	db	110
	db	103
	db	91
	db	50
	db	53
	db	54
	db	93
	db	0
@$xt$a256$17System@AnsiString	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$a24$17System@AnsiString	segment virtual
	align	2
@@$xt$a24$17System@AnsiString	label	byte
	dd	96
	dw	1024
	dw	16
	dd	@@$xt$17System@AnsiString
	dd	24
	db	83
	db	121
	db	115
	db	116
	db	101
	db	109
	db	58
	db	58
	db	65
	db	110
	db	115
	db	105
	db	83
	db	116
	db	114
	db	105
	db	110
	db	103
	db	91
	db	50
	db	52
	db	93
	db	0
@$xt$a24$17System@AnsiString	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$a8$17System@AnsiString	segment virtual
	align	2
@@$xt$a8$17System@AnsiString	label	byte
	dd	32
	dw	1024
	dw	16
	dd	@@$xt$17System@AnsiString
	dd	8
	db	83
	db	121
	db	115
	db	116
	db	101
	db	109
	db	58
	db	58
	db	65
	db	110
	db	115
	db	105
	db	83
	db	116
	db	114
	db	105
	db	110
	db	103
	db	91
	db	56
	db	93
	db	0
@$xt$a8$17System@AnsiString	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$a61$17System@AnsiString	segment virtual
	align	2
@@$xt$a61$17System@AnsiString	label	byte
	dd	244
	dw	1024
	dw	16
	dd	@@$xt$17System@AnsiString
	dd	61
	db	83
	db	121
	db	115
	db	116
	db	101
	db	109
	db	58
	db	58
	db	65
	db	110
	db	115
	db	105
	db	83
	db	116
	db	114
	db	105
	db	110
	db	103
	db	91
	db	54
	db	49
	db	93
	db	0
@$xt$a61$17System@AnsiString	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$p17System@AnsiString	segment virtual
	align	2
@@$xt$p17System@AnsiString	label	dword
	dd	4
	dw	16
	dw	12
	dd	@@$xt$17System@AnsiString
	db	83
	db	121
	db	115
	db	116
	db	101
	db	109
	db	58
	db	58
	db	65
	db	110
	db	115
	db	105
	db	83
	db	116
	db	114
	db	105
	db	110
	db	103
	db	32
	db	42
	db	0
@$xt$p17System@AnsiString	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$17System@AnsiString	segment virtual
	align	2
@@$xt$17System@AnsiString	label	byte
	dd	4
	dw	3
	dw	48
	dd	-1
	dd	3
	dw	68
	dw	72
	dd	0
	dw	0
	dw	0
	dd	0
	dd	1
	dd	1
	dd	@System@AnsiString@$bdtr$qqrv
	dw	3
	dw	76
	db	83
	db	121
	db	115
	db	116
	db	101
	db	109
	db	58
	db	58
	db	65
	db	110
	db	115
	db	105
	db	83
	db	116
	db	114
	db	105
	db	110
	db	103
	db	0
	db	0
	dd	0
	dd	0
	dd	0
@$xt$17System@AnsiString	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
@System@TObject@	segment virtual
	align	2
@@System@TObject@	label	byte
	dd	0
	dd	0
	dd	@@$xp$14System@TObject
	dd	0
	dd	0
	dd	0
	dd	@@System@TObject@+64
	dd	4
	dd	0
	dd	@System@TObject@AfterConstruction$qqrv
	dd	@System@TObject@BeforeDestruction$qqrv
	dd	@System@TObject@Dispatch$qqrpv
	dd	@System@TObject@DefaultHandler$qqrpv
	dd	@System@TObject@NewInstance$qqrp17System@TMetaClass
	dd	@System@TObject@FreeInstance$qqrv
	dd	@@System@TObject@$bdtr$qqrv
	db	7
	db        84,79,98,106,101,99,116
@System@TObject@	ends
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@$xp$14System@TObject	segment virtual
	align	2
@@$xp$14System@TObject	label	byte
	db	7
	db	7
	db        84,79,98,106,101,99,116
	dd	@@System@TObject@+64
	dd	0
	dw	0
	db	4
	db        54,53,48,50
	dw	0
@$xp$14System@TObject	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@System@TObject@$bdtr$qqrv	segment virtual
	align	2
@@System@TObject@$bdtr$qqrv	proc	near
?live16404@0:
@2248:
	call      __BeforeDestruction
	test      dl,dl
@2251:
	test      dl,dl
	jle       short @2252
	call      __ClassDestroy
@2252:
	ret 
@@System@TObject@$bdtr$qqrv	endp
@System@TObject@$bdtr$qqrv	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
s@	label	byte
	;	s@+0:
	db	"ADC ",0
	;	s@+5:
	db	"AND ",0
	;	s@+10:
	db	"ASL ",0
	;	s@+15:
	db	"BCC ",0
	;	s@+20:
	db	"BCS ",0
	;	s@+25:
	db	"BEQ ",0
	;	s@+30:
	db	"BIT ",0
	;	s@+35:
	db	"BMI ",0
	;	s@+40:
	db	"BNE ",0
	;	s@+45:
	db	"BPL ",0
	;	s@+50:
	db	"BRK ",0
	;	s@+55:
	db	"BVC ",0
	;	s@+60:
	db	"BVS ",0
	;	s@+65:
	db	"CLC ",0
	;	s@+70:
	db	"CLD ",0
	;	s@+75:
	db	"CLI ",0
	;	s@+80:
	db	"CLV ",0
	;	s@+85:
	db	"CMP ",0
	;	s@+90:
	db	"CPX ",0
	;	s@+95:
	db	"CPY ",0
	;	s@+100:
	db	"DEC ",0
	;	s@+105:
	db	"DEX ",0
	;	s@+110:
	db	"DEY ",0
	;	s@+115:
	db	"EOR ",0
	;	s@+120:
	db	"INC ",0
	;	s@+125:
	db	"INX ",0
	;	s@+130:
	db	"INY ",0
	;	s@+135:
	db	"JMP ",0
	;	s@+140:
	db	"JSR ",0
	;	s@+145:
	db	"LDA ",0
	;	s@+150:
	db	"LDX ",0
	;	s@+155:
	db	"LDY ",0
	;	s@+160:
	db	"LSR ",0
	;	s@+165:
	db	"NOP ",0
	;	s@+170:
	db	"ORA ",0
	;	s@+175:
	db	"PHA ",0
	;	s@+180:
	db	"PHP ",0
	;	s@+185:
	db	"PLA ",0
	;	s@+190:
	db	"PLP ",0
	;	s@+195:
	db	"ROL ",0
	;	s@+200:
	db	"ROR ",0
	;	s@+205:
	db	"RTI ",0
	;	s@+210:
	db	"RTS ",0
	;	s@+215:
	db	"SBC ",0
	;	s@+220:
	db	"SEC ",0
	;	s@+225:
	db	"SED ",0
	;	s@+230:
	db	"SEI ",0
	;	s@+235:
	db	"STA ",0
	;	s@+240:
	db	"STX ",0
	;	s@+245:
	db	"STY ",0
	;	s@+250:
	db	"TAX ",0
	;	s@+255:
	db	"TAY ",0
	;	s@+260:
	db	"TSX ",0
	;	s@+265:
	db	"TXA ",0
	;	s@+270:
	db	"TXS ",0
	;	s@+275:
	db	"TYA ",0
	;	s@+280:
	db	"ASLA",0
	;	s@+285:
	db	"LSRA",0
	;	s@+290:
	db	"ROLA",0
	;	s@+295:
	db	"RORA",0
	;	s@+300:
	db	"????",0
	;	s@+305:
	db	"PPUCtrl1",0
	;	s@+314:
	db	"PPUCtrl2",0
	;	s@+323:
	db	"PPUStat",0
	;	s@+331:
	db	"SPRAddr",0
	;	s@+339:
	db	"SPRIO",0
	;	s@+345:
	db	"BgScroll",0
	;	s@+354:
	db	"VRAMAddr",0
	;	s@+363:
	db	"VRAMIO",0
	;	s@+370:
	db	"pAPUP1C1",0
	;	s@+379:
	db	"pAPUP1C2",0
	;	s@+388:
	db	"pAPUP1F1",0
	;	s@+397:
	db	"pAPUP1F2",0
	;	s@+406:
	db	"pAPUP2C1",0
	;	s@+415:
	db	"pAPUP2C2",0
	;	s@+424:
	db	"pAPUP2F1",0
	;	s@+433:
	db	"pAPUP2F2",0
	;	s@+442:
	db	"pAPUTC1",0
	;	s@+450:
	db	"pAPUTC2",0
	;	s@+458:
	db	"pAPUTF1",0
	;	s@+466:
	db	"pAPUTF2",0
	;	s@+474:
	db	"pAPUNC1",0
	;	s@+482:
	db	"pAPUNC2",0
	;	s@+490:
	db	"pAPUNF1",0
	;	s@+498:
	db	"pAPUNF2",0
	;	s@+506:
	db	"pAPUDMCC",0
	;	s@+515:
	db	"pAPUDMCV",0
	;	s@+524:
	db	"pAPUDMCA",0
	;	s@+533:
	db	"pAPUDMCDL",0
	;	s@+543:
	db	"SPRDMA",0
	;	s@+550:
	db	"pAPUStCh",0
	;	s@+559:
	db	"Joypad1",0
	;	s@+567:
	db	"Joypad2",0
	;	s@+575:
	db	"No Mapper",0
	;	s@+585:
	db	"MMC1",0
	;	s@+590:
	db	"UNROM",0
	;	s@+596:
	db	"CNROM",0
	;	s@+602:
	db	"MMC3",0
	;	s@+607:
	db	"MMC5",0
	;	s@+612:
	db	"FFE F4xxx",0
	;	s@+622:
	db	"AOROM",0
	;	s@+628:
	db	"FFE F3xxx",0
	;	s@+638:
	db	"MMC2",0
	;	s@+643:
	db	"MMC4",0
	;	s@+648:
	db	"Color Dreams",0,0,0,0
	;	s@+664:
	db	"100-in-1",0
	;	s@+673:
	db	"Bandai",0
	;	s@+680:
	db	"FFE F8xxx",0
	;	s@+690:
	db	"Jaleco SS8806",0
	;	s@+704:
	db	"Namcot 106",0,0
	;	s@+716:
	db	"Konami VRC4",0
	;	s@+728:
	db	"Konami VRC2 type A",0
	;	s@+747:
	db	"Konami VRC2 type B",0
	;	s@+766:
	db	"Konami VRC6",0,0,0,0,0,0,0,0
	;	s@+785:
	db	"Irem G-101",0
	;	s@+796:
	db	"Taito TC0190",0
	;	s@+809:
	db	"Nina-1",0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0
	;	s@+845:
	db	"Tengen RAMBO-1",0
	;	s@+860:
	db	"Irem H-3001",0
	;	s@+872:
	db	"GNROM",0,0
	;	s@+879:
	db	"Sunsoft Mapper #4",0
	;	s@+897:
	db	"Sunsoft FME-7",0,0
	;	s@+912:
	db	"Camerica",0,0,0,0,0,0,0
	;	s@+927:
	db	"Irem 74HC161/32",0,0,0,0,0,0,0,0,0,0,0
	db	0
	;	s@+954:
	db	"Tekken 2/MK4 Hacks",0
	;	s@+973:
	db	"HK-SF3",0,0,0,0,0,0,0,0
	;	s@+987:
	db	"VS. System",0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	;	s@+1124:
	db	"76-in-1",0
	;	s@+1132:
	db	"1200-in-1",0
	;	s@+1142:
	db	"Action 52",0,0
	;	s@+1153:
	db	"22-in-1",0,0,0,0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0,0,0,0
	;	s@+1186:
	db	"NES4PC - FPS: ",0
	;	s@+1201:
	db	", Skip: ",0
	;	s@+1210:
	db	"Debug",0,0
	;	s@+1217:
	db	"    ",0
	;	s@+1222:
	db	" -$",0
	;	s@+1226:
	db	" $",0
	;	s@+1229:
	db	"00000000",0
	;	s@+1238:
	db	"1",0
	;	s@+1240:
	db	"0",0
	align	4
_DATA	ends
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
	?debug	C FB04175175657279506572666F726D616E6365436F756E74657202000000
	public	_Mem
	public	_DebuggingTrace
	extrn	_frameskip:dword
	public	_YMax
	public	_NTabAdr
	public	_BkPTA
	public	_CPURunning
	extrn	_StartFrm:dword
	public	_addressmode
	public	_instruc
	public	_ticks
	public	_bytes
	public	_Mn
	public	_RegInfoLow
	public	_RegInfoHigh
	public	_MapperInfo
	extrn	_LengthInfo:byte
	extrn	_PlayDataRate:word
	public	_tmp
	public	_tmpBYTE
	public	_tmpLBYTE
	public	_tmpshortint
	public	_tmpbool
	public	_DebuggingRegs
	public	_HaltOnNMI
	public	_HaltOnBadOp
	public	_tmpframes
	extrn	_Autoframeskip:byte
	extrn	_FPSnum:dword
	extrn	_Autoframeskipmax:dword
	extrn	_bitnumsp:byte
	public	_GGCodeNum
	public	_GGCode
	public	_A
	public	_X
	public	_Y
	public	_SP
	public	_PC
	public	_TU
	public	_ClockticksSm
	public	_TU2
	public	_NMIonVBlank
	public	_NMIonSprHit
	public	_SSize
	public	_SpPTA
	public	_PPUAdrI
	public	_SprVis
	public	_BGVis
	public	_SprClip
	public	_BGClip
	public	_DispType
	public	_VBlankOcc
	public	_Spr0Occ
	public	_ScLnSprCnt
	public	_VRAMWrFlg
	public	_VFirstRead
	public	_SFirstRead
	public	_TUMode
	public	_SpecialAccessR
	public	_SpecialAccessW
	public	_P
	public	_PALMode
	public	_LineRate
	public	_LineTotal
	public	_ScanLine
	public	_VBScanLine
	public	_MaxScanLine
	public	_MHBValue
	public	_ScanLineFake
	public	_LineTicksInt
	public	_CPUSpeed
	public	_VBlanking
	public	_FakeSLUsing
	public	_VBSec
	public	_Joy
	public	_PulseChan
	public	_TriChan
	public	_NoiseChan
	public	_DCMChan
	extrn	_SNDChannels:byte
	public	_SRAMFileWr
	public	_SRAMFileRd
	public	_ROMTrainer
	public	_MMC1
	public	_MMC3
	public	_M22in1
	public	_M16
	public	_M17
	public	_M90
	public	_M24
	extrn	_SavingState:byte
	extrn	_ClockFreq:byte
	extrn	_ClockFreqVblank:dword
	public	_LastClockVal
	public	@NewCPUMode$qs
	extrn	__ftol:near
	extrn	__lldiv:near
	public	@Setup$qp11Forms@TForm7tagRECTp14Stdctrls@TMemot3
	extrn	@VideoSetup$qp11Forms@TForm7tagRECTp14Stdctrls@TMemot3:near
	extrn	@AudioSetup$qqrp11Forms@TForm:near
	public	@Shutdown$qqrv
	extrn	_fseek:near
	extrn	_fwrite:near
	extrn	_fclose:near
	extrn	@VideoShutdown$qqrv:near
	extrn	@AudioShutdown$qqrv:near
	public	@exec6502$qqrv
	public	@HBlank$qv
	public	@run6502$qqrv
	public	@Addrmode$qqruc
	public	@ExecOp$qqruc
	public	@irq6502$qqrv
	extrn	@SaveState$qv:near
	extrn	@PrepTileline$qv:near
	extrn	@DrawScanline$qv:near
	extrn	@Forms@TApplication@ProcessMessages$qqrv:near
	extrn	@Forms@Application:dword
	extrn	QueryPerformanceCounter:near
	extrn	@Comctrls@TCustomUpDown@SetPosition$qqrs:near
	extrn	@Controls@TControl@SetText$qqrx17System@AnsiString:near
	extrn	@System@AnsiString@$badd$xqqrrx17System@AnsiString:near
	extrn	@System@AnsiString@$bctr$qqrpxc:near
	extrn	@System@AnsiString@$bctr$qqri:near
	extrn	@System@AnsiString@$bdtr$qqrv:near
	extrn	@FinishTileline$qv:near
	public	@nmi6502$qqrv
	extrn	__Exception_list:dword
	extrn	@__InitExceptBlockLDTC:near
	public	@HardBoot$qv
	extrn	_memset:near
	public	@reset6502$qqrv
	public	@UpdateGGCodes$qqrv
	extrn	_memcpy:near
	public	@MemoryTUGet$qqrv
	public	@MemoryTUEquals$qqruc
	extrn	@Forms@TApplication@MessageBoxA$qqrpct1us:near
	extrn	@Sysutils@IntToHex$qqrii:near
	extrn	@System@AnsiString@$bctr$qqrrx17System@AnsiString:near
	public	@ToBin$qqruc
	public	@ToBinC$qucucuc
	extrn	@System@AnsiString@$brplu$qqrrx17System@AnsiString:near
	extrn	@System@AnsiString@$basg$qqrrx17System@AnsiString:near
	extrn	@System@AnsiString@$bctr$qqrpxcuc:near
	extrn	@_vector_delete_ldtc_$qpvuiuiuit1:near
	extrn	@System@TObject@AfterConstruction$qqrv:near
	extrn	@System@TObject@BeforeDestruction$qqrv:near
	extrn	@System@TObject@Dispatch$qqrpv:near
	extrn	@System@TObject@DefaultHandler$qqrpv:near
	extrn	@System@TObject@NewInstance$qqrp17System@TMetaClass:near
	extrn	@System@TObject@FreeInstance$qqrv:near
	extrn	__BeforeDestruction:near
	extrn	__ClassDestroy:near
	?debug	D "States.h" 9871 19723
	?debug	D "mappers.h" 10054 17594
	?debug	D "audio.h" 9629 48533
	?debug	D "OptionsWindowForm.h" 9607 2528
	?debug	D "AboutWindowForm.h" 9818 40018
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\Richedit.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\oleidl.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\oleidl.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\oaidl.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\oleauto.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\cguid.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\cguid.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\objidl.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\objidl.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\unknwn.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\unknwn.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\wtypes.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\rpcnsip.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\rpcnsip.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\rpcndr.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\rpcndr.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\objbase.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\ole2.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\ole2.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winspool.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winspool.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winsock.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winperf.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winperf.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\shellapi.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\shellapi.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\rpcnterr.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\rpcnterr.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\rpcnsi.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\rpcnsi.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\rpcdcep.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\rpcdcep.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\rpcdce.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\rpcdce.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\rpc.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\rpc.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\nb30.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\nb30.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\mmsystem.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\lzexpand.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\lzexpand.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\dlgs.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\dlgs.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\ddeml.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\ddeml.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\dde.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\dde.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\cderr.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\cderr.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\RichEdit.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\vcl\ComCtrls.hpp" 8781 2048
	?debug	D "main.h" 9840 36723
	?debug	D "video.h" 10122 37040
	?debug	D "Defines.h" 10058 47406
	?debug	D "6502.h" 9854 28426
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\memory.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\mem.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\Bde.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\DB.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\DBTables.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\Mask.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\StdCtrls.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\ExtCtrls.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\Buttons.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\dbctrls.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\commdlg.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\Commdlg.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\CommDlg.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\dialogs.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\forms.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\ctl3d.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\Menus.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\pshpack8.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\prsht.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\Commctrl.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\CommCtrl.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\Imm.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\Imm.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\controls.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\graphics.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\classes.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\sysutils.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\messages.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\iostream.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\dstring.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\_nfile.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\stdio.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\stdlib.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\sysdefs.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\System.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\imm.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\mcx.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winsvc.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winsvc.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winnetwk.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winnetwk.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winreg.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winreg.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winver.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winver.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\wincon.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\wincon.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winnls.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winnls.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winuser.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winuser.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\pshpack1.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\wingdi.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\wingdi.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winerror.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winbase.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winbase.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\stddef.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\string.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\pshpack2.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\poppack.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\pshpack4.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\ctype.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\winnt.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\winnt.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\windef.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\_defs.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\stdarg.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\excpt.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\win32\windows.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\windows.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\windows.hpp" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\vcldb.h" 8781 2048
	?debug	D "C:\PROGRA~1\BORLAND\CBUILDER\INCLUDE\VCL\VCL.H" 8781 2048
	?debug	D "6502.cpp" 10596 38212
	end
