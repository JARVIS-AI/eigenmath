#include "defs.h"

void
eval_clock(void)
{
	int t = expanding;
	expanding = 1;
	push(cadr(p1));
	eval();
	clockfunc();
	expanding = t;
}

void
clockfunc(void)
{
	save();
	clockfunc_nib();
	restore();
}

void
clockfunc_nib(void)
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
			clockfunc();
			p1->u.tensor->elem[i] = pop();
		}
		push(p1);
		return;
	}

	push(p1);
	mag();
	push_integer(-1);
	push(p1);
	arg();
	push_symbol(PI);
	divide();
	power();
	multiply();
}
