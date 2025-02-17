#include "defs.h"

void
eval_abs(void)
{
	int t = expanding;
	expanding = 1;
	push(cadr(p1));
	eval();
	absfunc();
	expanding = t;
}

void
absfunc(void)
{
	save();
	absfunc_nib();
	restore();
}

void
absfunc_nib(void)
{
	int h;

	p1 = pop();

	if (istensor(p1)) {
		if (p1->u.tensor->ndim > 1) {
			push_symbol(ABS);
			push(p1);
			list(2);
			return;
		}
		push(p1);
		push(p1);
		conjfunc();
		inner();
		push_rational(1, 2);
		power();
		return;
	}

	push(p1);
	push(p1);
	conjfunc();
	multiply();
	push_rational(1, 2);
	power();

	p2 = pop();
	push(p2);
	floatfunc();
	p3 = pop();
	if (isdouble(p3)) {
		push(p2);
		if (isnegativenumber(p3))
			negate();
		return;
	}

	// abs(1/a) evaluates to 1/abs(a)

	if (car(p1) == symbol(POWER) && isnegativeterm(caddr(p1))) {
		push(p1);
		reciprocate();
		absfunc();
		reciprocate();
		return;
	}

	// abs(a*b) evaluates to abs(a)*abs(b)

	if (car(p1) == symbol(MULTIPLY)) {
		h = tos;
		p1 = cdr(p1);
		while (iscons(p1)) {
			push(car(p1));
			absfunc();
			p1 = cdr(p1);
		}
		multiply_factors(tos - h);
		return;
	}

	if (isnegativeterm(p1) || (car(p1) == symbol(ADD) && isnegativeterm(cadr(p1)))) {
		push(p1);
		negate();
		p1 = pop();
	}

	push_symbol(ABS);
	push(p1);
	list(2);
}
