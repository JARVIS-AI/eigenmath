#include "defs.h"

void
eval_leading(void)
{
	push(cadr(p1));
	eval();
	push(caddr(p1));
	eval();
	p1 = pop();
	if (p1 == symbol(NIL))
		push_symbol(X_LOWER);
	else
		push(p1);
	leading();
}

#undef P
#undef X
#undef N

#define P p1
#define X p2
#define N p3

void
leading(void)
{
	save();

	X = pop();
	P = pop();

	push(P);	// N = degree of P
	push(X);
	degree();
	N = pop();

	push(P);	// divide through by X ^ N
	push(X);
	push(N);
	power();
	divide();

	push(X);	// remove terms that depend on X
	filter();

	restore();
}
