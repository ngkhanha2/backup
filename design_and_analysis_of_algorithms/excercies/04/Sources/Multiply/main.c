/*
 * main.c
 *
 *  Created on: Nov 24, 2014
 *      Author: Khanh
 */

#include <stdio.h>
#include <stdlib.h>

#define FILE_IN "INPUT.txt"
#define FILE_OUT "1212171.txt"

typedef struct {
	int length;
	char sign;
	char *value;
} LARGE_INTEGER;

int isZero(LARGE_INTEGER *u) {
	int i;
	for (i = 0; i < u->length; ++i) {
		if (u->value[i] != 0) {
			return 0;
		}
	}
	return 1;
}

LARGE_INTEGER *createLargeInteger(int length) {
	LARGE_INTEGER *result = (LARGE_INTEGER*) malloc(sizeof(LARGE_INTEGER));
	result->length = length;
	result->sign = 1;
	result->value = (char*) calloc(length, sizeof(char));
	return result;
}

LARGE_INTEGER* cloneLargeInteger(LARGE_INTEGER *n, int length) {
	LARGE_INTEGER *result = createLargeInteger(length);
	int i;
	for (i = 0; i < length; ++i) {
		result->value[i] = n->value[i];
	}
	result->sign = n->sign;
	return result;
}

void dividePowerOf10(LARGE_INTEGER *n, int m, LARGE_INTEGER **quotient,
		LARGE_INTEGER **remain) {
	int i;
	if (m >= n->length) {
		*quotient = createLargeInteger(1);
		(*quotient)->value[0] = 0;
		*remain = cloneLargeInteger(n, n->length);
		return;
	}
	*quotient = createLargeInteger(n->length - m);
	for (i = m; i < n->length; ++i) {
		(*quotient)->value[i - m] = n->value[i];
	}
	(*quotient)->sign = n->sign;
	if (m == 0) {
		*remain = createLargeInteger(1);
		(*remain)->value[0] = 0;
	} else {
		*remain = cloneLargeInteger(n, m);
	}
}

LARGE_INTEGER* multiplyPowerOf10(LARGE_INTEGER *n, int m) {
	LARGE_INTEGER *result;
	int i;
	if (isZero(n)) {
		result = createLargeInteger(1);
		result->value[0] = 0;
	} else {
		if (m == 0) {
			result = cloneLargeInteger(n, n->length);
		} else {
			result = createLargeInteger(m + n->length);
			for (i = 0; i < m; ++i) {
				result->value[i] = 0;
			}
			for (i = 0; i < n->length; ++i) {
				result->value[i + m] = n->value[i];
			}
			result->sign = n->sign;
		}
	}
	return result;
}

LARGE_INTEGER* addu(LARGE_INTEGER *u, LARGE_INTEGER *v) {
	int n = u->length > v->length ? u->length : v->length;
	LARGE_INTEGER *result = createLargeInteger(n + 1);
	n = u->length > v->length ? v->length : u->length;
	int i, c;
	char t, r = 0;
	c = 0;
	for (i = 0; i < n; ++i) {
		t = r + u->value[i] + v->value[i];
		result->value[c] = t % 10;
		r = t / 10;
		++c;
	}
	if (u->length > v->length) {
		for (i = n; i < u->length; ++i) {
			t = r + u->value[i];
			result->value[c] = t % 10;
			r = t / 10;
			++c;
		}
	}
	if (r != 0) {
		result->value[c] = r;
		++c;
	}
	result->length = c;
	return result;
}

void deleteLargeInterger(LARGE_INTEGER *n) {
	free(n->value);
	free(n);
}

LARGE_INTEGER* subu(LARGE_INTEGER *u, LARGE_INTEGER *v) {
	int n = u->length > v->length ? u->length : v->length;
	LARGE_INTEGER *result = createLargeInteger(n + 1);
	n = u->length > v->length ? v->length : u->length;
	int i, c;
	char t, r = 0;
	c = 0;
	for (i = 0; i < n; ++i) {
		t = -r;
		r = 0;
		t += u->value[i] - v->value[i];
		if (t < 0) {
			t += 10;
			r = 1;
		}
		result->value[c] = t % 10;
		++c;
	}
	if (u->length > v->length) {
		for (i = n; i < u->length; ++i) {
			t = -r;
			r = 0;
			t += u->value[i];
			if (t < 0) {
				t += 10;
				r = 1;
			}
			result->value[c] = t % 10;
			++c;
		}
	}
	while (result->value[c - 1] == 0) {
		--c;
	}
	result->length = c;
	return result;
}

int compareUnsigned(LARGE_INTEGER *u, LARGE_INTEGER *v) {
	if (u->length > v->length) {
		return 1;
	}
	if (u->length < v->length) {
		return -1;
	}
	int i;
	for (i = u->length - 1; i >= 0; --i) {
		if (u->value[i] > v->value[i]) {
			return 1;
		} else {
			if (u->value[i] < v->value[i]) {
				return -1;
			}
		}
	}
	return 0;
}

LARGE_INTEGER* add(LARGE_INTEGER *u, LARGE_INTEGER *v) {
	LARGE_INTEGER *result = NULL;
	int t;
	if (u->sign == v->sign) {
		if (u->length < v->length) {
			result = addu(v, u);
		} else {
			result = addu(u, v);
		}
		result->sign = u->sign;
	} else {
		t = compareUnsigned(u, v);
		switch (t) {
		case 1:
			result = subu(u, v);
			result->sign = u->sign;
			break;
		case 0:
			result = createLargeInteger(1);
			result->value[0] = 0;
			break;
		case -1:
			result = subu(v, u);
			result->sign = v->sign;
			break;
		}
	}
	return result;
}

LARGE_INTEGER* sub(LARGE_INTEGER *u, LARGE_INTEGER *v) {
	LARGE_INTEGER *result = NULL;
	int t;
	if (u->sign == v->sign) {
		t = compareUnsigned(u, v);
		switch (t) {
		case 1:
			result = subu(u, v);
			result->sign = u->sign;
			break;
		case 0:
			result = createLargeInteger(1);
			result->value[0] = 0;
			break;
		case -1:
			result = subu(v, u);
			result->sign = -1 * u->sign;
			break;
		}
	} else {
		if (u->length < v->length) {
			result = addu(v, u);
		} else {
			result = addu(u, v);
		}
		result->sign = u->sign;
	}
	return result;
}

void printLargeInterger(LARGE_INTEGER *u) {
	int i;
	for (i = u->length - 1; i >= 0; --i) {
		printf("%d", u->value[i]);
	}
	printf("\n");
}

LARGE_INTEGER* multiply(LARGE_INTEGER *u, LARGE_INTEGER *v) {
	int n = u->length > v->length ? u->length : v->length;
	if (isZero(u) || isZero(v)) {
		LARGE_INTEGER *result = createLargeInteger(1);
		result->value[0] = 0;
		return result;
	}
	if (n == 1) {
		char s = u->value[0] * v->value[0];
		LARGE_INTEGER *result;
		if (s < 10) {
			result = createLargeInteger(1);
			result->value[0] = s;
		} else {
			result = createLargeInteger(2);
			result->value[0] = s % 10;
			result->value[1] = s / 10;
		}
		return result;
	}
	int m = n / 2;

	LARGE_INTEGER *x, *y, *w, *z;
	dividePowerOf10(u, m, &x, &y);
	dividePowerOf10(v, m, &w, &z);

	LARGE_INTEGER *xAy = add(x, y);
	LARGE_INTEGER *wAz = add(w, z);
	LARGE_INTEGER *r = multiply(xAy, wAz);
	LARGE_INTEGER *p = multiply(x, w);
	LARGE_INTEGER *q = multiply(y, z);

	LARGE_INTEGER *pM10P2m = multiplyPowerOf10(p, 2 * m);
	LARGE_INTEGER *rSp = sub(r, p);
	LARGE_INTEGER *rSpSq = sub(rSp, q);
	LARGE_INTEGER *rSpSqM10Pm = multiplyPowerOf10(rSpSq, m);
	LARGE_INTEGER *rSpSqM10PmAq = add(rSpSqM10Pm, q);
	LARGE_INTEGER *result = add(pM10P2m, rSpSqM10PmAq);

	deleteLargeInterger(x);
	deleteLargeInterger(y);
	deleteLargeInterger(z);
	deleteLargeInterger(w);
	deleteLargeInterger(xAy);
	deleteLargeInterger(wAz);
	deleteLargeInterger(r);
	deleteLargeInterger(p);
	deleteLargeInterger(q);
	deleteLargeInterger(pM10P2m);
	deleteLargeInterger(rSp);
	deleteLargeInterger(rSpSq);
	deleteLargeInterger(rSpSqM10Pm);
	deleteLargeInterger(rSpSqM10PmAq);
	return result;
}

LARGE_INTEGER* inputLargeInterger(FILE *f, int count, char sign) {
	char c;
	fscanf(f, "%c", &c);
	if (c == '-') {
		return inputLargeInterger(f, count, -1);
	}
	if (c >= '0' && c <= '9') {
		LARGE_INTEGER *result = inputLargeInterger(f, count + 1, sign);
		result->value[result->length - count - 1] = c - '0';
		return result;
	}
	LARGE_INTEGER *result = createLargeInteger(count);
	result->sign = sign;
	return result;
}

void input(LARGE_INTEGER **u, LARGE_INTEGER **v) {
	FILE *fi = fopen(FILE_IN, "rt");
	*u = inputLargeInterger(fi, 0, 1);
	*v = inputLargeInterger(fi, 0, 1);
	fclose(fi);
}

int main() {
	LARGE_INTEGER *u, *v;
	input(&u, &v);
	LARGE_INTEGER *result = multiply(u, v);
	FILE *fo = fopen(FILE_OUT, "wt");
	int i;
	for (i = result->length - 1; i >= 0; --i) {
		fprintf(fo, "%d", result->value[i]);
	}
	fclose(fo);
	return 0;
}
