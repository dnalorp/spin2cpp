PUB main
  coginit(0, @entry, 0)
DAT
	org	0
entry

_test
L__0001
	mov	_test_x, INA
	sar	_test_x, #1
	and	_test_x, #1 wz
 if_ne	jmp	#L__0002
	mov	_tmp001_, INA
	sar	_tmp001_, #2
	test	_tmp001_, #1 wz
 if_ne	jmp	#L__0001
	xor	OUTA, #1
	jmp	#L__0001
L__0002
_test_ret
	ret

_test_x
	long	0
_tmp001_
	long	0
arg1
	long	0
arg2
	long	0
arg3
	long	0
arg4
	long	0
result1
	long	0
	fit	496
