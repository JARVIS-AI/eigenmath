function
find_denominator(p)
{
	var q;
	while (iscons(p)) {
		q = car(p);
		if (car(q) == symbol(POWER) && isnegativenumber(caddr(q)))
			return 1;
		p = cdr(p);
	}
	return 0;
}
