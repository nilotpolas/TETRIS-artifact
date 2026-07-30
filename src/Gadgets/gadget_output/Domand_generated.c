/* DOMAND Function Definition */
void Domand(_Bool a0, _Bool a1, _Bool b0, _Bool b1, _Bool * c0, _Bool * c1, _Bool r01){
		_Bool t0, t1, t2, t3;
		_Bool i0, i1;

		t0 = a0 & b0;
		t1 = a0 & b1;
		i0 = t1 ^ r01;

		t2 = a1 & b0;
		i1 = t2 ^ r01;
		t3 = a1 & b1;

		*c0 = reg(i0) ^ t3;
		*c1 = reg(i1) ^ t3;
}