#include "defs.h"

void
eval_imag(void)
{
	int t = expanding;
	expanding = 1;
	push(cadr(p1));
	eval();
	imag();
	expanding = t;
}

void
imag(void)
{
	save();
	imag_nib();
	restore();
}

void
imag_nib(void)
{
	int i, n;

	p1 = pop();

	if (istensor(p1)) {
		push(p1);
		copy_tensor();
		p1 = pop();
		n = p1->u.tensor->nelem;
		for (i = 0; i < n; i++) {
			push(p1->u.tensor->elem[i]);
			imag();
			p1->u.tensor->elem[i] = pop();
		}
		push(p1);
		return;
	}

	push(p1);
	rect();
	p1 = pop();
	push_rational(-1, 2);
	push(imaginaryunit);
	push(p1);
	push(p1);
	conjfunc();
	subtract();
	multiply_factors(3);
}
