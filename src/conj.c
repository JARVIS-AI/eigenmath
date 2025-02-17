#include "defs.h"

void
eval_conj(void)
{
	int t = expanding;
	expanding = 1;
	push(cadr(p1));
	eval();
	conjfunc();
	expanding = t;
}

void
conjfunc(void)
{
	conjfunc_subst();
	eval();
}

void
conjfunc_subst(void)
{
	save();
	conjfunc_subst_nib();
	restore();
}

void
conjfunc_subst_nib(void)
{
	int h, i, n;

	p1 = pop();

	if (istensor(p1)) {
		push(p1);
		copy_tensor();
		p1 = pop();
		n = p1->u.tensor->nelem;
		for (i = 0; i < n; i++) {
			push(p1->u.tensor->elem[i]);
			conjfunc_subst();
			p1->u.tensor->elem[i] = pop();
		}
		push(p1);
		return;
	}

	// (-1) ^ expr

	if (car(p1) == symbol(POWER) && isminusone(cadr(p1))) {
		push_symbol(POWER);
		push_integer(-1);
		push(caddr(p1));
		negate();
		list(3);
		return;
	}

	if (iscons(p1)) {
		h = tos;
		push(car(p1));
		p1 = cdr(p1);
		while (iscons(p1)) {
			push(car(p1));
			conjfunc_subst();
			p1 = cdr(p1);
		}
		list(tos - h);
		return;
	}

	push(p1);
}
