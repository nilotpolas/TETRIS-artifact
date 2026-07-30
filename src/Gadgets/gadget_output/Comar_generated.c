/* COMAR Function Definition */
void Comar(_Bool a0, _Bool a1, _Bool b0, _Bool b1, _Bool* c0, _Bool* c1, _Bool r0, _Bool r1, _Bool r_0, _Bool r_1, _Bool r_2, _Bool r_3){
	_Bool a_0;
	a_0= reg(a0 ^ r0);
	_Bool a_1;
	a_1= reg(a1 ^ r0);
	_Bool b_0;
	b_0= reg(b0 ^ r1);
	_Bool b_1;
	b_1= reg(b1 ^ r1);

	_Bool t0, t1, t2, t3;

	_Bool c_0, c_1, c_2, c_3;
	t0 = a_0 & b_0;
	c_0 = reg(t0 ^ r_0);
	t1 = a_1 & b_0;
	c_1 = reg(t1 ^ r_1);
	t2 = a_0 & b_1;
	c_2 = reg(t2 ^ r_2);
	t3 = a_1 & b_1;
	c_3 = reg(t3 ^ r_3);
	_Bool t4, t5;
	t4 = c_0 ^ c_1;
	t5 = t4 ^ c_2;
	*c0 = t5 ^ c_3;

	_Bool t6, t7;

	t6 = r_0 ^ r_1;
	t7 = t6 ^ r_2;
	*c1 = reg(t7 ^ r_3);
}