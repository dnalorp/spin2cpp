pub main
  coginit(0, @entry, 0)
dat
	org	0
entry

_sum1
	rdbyte	_var01, arg01
	add	arg01, #1
	add	arg01, _var01
	mov	result1, arg01
_sum1_ret
	ret

result1
	long	0
COG_BSS_START
	fit	496
	org	COG_BSS_START
_var01
	res	1
arg01
	res	1
	fit	496
