function
eval_not(p1)
{
	var t = expanding;
	expanding = 1;
	push(cadr(p1));
	evalp();
	p1 = pop();
	if (iszero(p1))
		push_integer(1);
	else
		push_integer(0);
	expanding = t;
}
