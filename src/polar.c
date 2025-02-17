#include "defs.h"

void
eval_polar(void)
{
	int t = expanding;
	expanding = 1;
	push(cadr(p1));
	eval();
	polar();
	expanding = t;
}

void
polar(void)
{
	save();
	polar_nib();
	restore();
}

void
polar_nib(void)
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
			polar();
			p1->u.tensor->elem[i] = pop();
		}
		push(p1);
		return;
	}

	push(p1);
	mag();
	push(imaginaryunit);
	push(p1);
	arg();
	p2 = pop();
	if (isdouble(p2)) {
		push_double(p2->u.d / M_PI);
		push_symbol(PI);
		multiply_factors(3);
	} else {
		push(p2);
		multiply_factors(2);
	}
	expfunc();
	multiply();
}
