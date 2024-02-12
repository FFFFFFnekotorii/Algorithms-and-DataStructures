uint32_t* resize(uint32_t *a, int n, int m) {
  uint32_t* c = new uint32_t[m];
  fill(c, c + m, 0);
  
  for (int i = 0; i < n; i++) {
    c[i] = a[i];
  }
  
  return c;
}

uint32_t* add(uint32_t *a, int n, uint32_t *b, int m) {
  if (n < m) a = resize(a, n, m);
  if (m < n) b = resize(b, m, n);  
  n = max(n, m);
  
  uint32_t* c = new uint32_t[n + 1];
  fill(c, c + n + 1, 0);
  
  uint32_t carry = 0;
  for (int i = 0; i < n; i++) {
    if (carry + a[i] + b[i] >= 4294967295) {
      c[i] = carry + a[i] + b[i] - 4294967295;
      carry = 1;
    } else {
      c[i] = carry + a[i] + b[i];
      carry = 0;
    }
    
  }
  if (carry > 0) {
    c[n] = 1;
  }
  
  return c;
}

uint32_t* sub(uint32_t *a, int n, uint32_t *b, int m) {
  if (n < m) a = resize(a, n, m);
  if (m < n) b = resize(b, m, n);  
  n = max(n, m);
  
  uint32_t* c = new uint32_t[n];
  fill(c, c + n, 0);
  
  uint32_t carry = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] < b[i] + carry) {
      c[i] = a[i] + 4294967295 - b[i] - carry;
      carry = 1;
    } else {
      c[i] = a[i] - b[i] - carry;
      carry = 0;
    }
    
  }
  
  return c;
}

uint32_t* shift(uint32_t *a, int n, int k) {
  uint32_t* c = new uint32_t[n + k];
  fill(c, c + k, 0);
  
  for (int i = 0; i < n; i++) {
    c[i + k] = a[i];
  }
  
  return c;
}

uint32_t* karatsuba(uint32_t *a, uint32_t *b, int n) {
  if (n <= 4) {
    uint32_t *c = new uint32_t[2 * n];
    uint64_t *c1 = new uint64_t[2 * n];
    
    fill(c1, c1 + 2 * n, 0);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        c1[i + j] += a[i] * b[j];
      }
    }
    
    for (int i = 0; i < 2 * n - 1; i++) {
      c1[i + 1] += (c1[i] / 4294967295);
      c1[i] %= 4294967295;
    }
    
    for (int i = 0; i < 2 * n; i++) {
      c[i] = (uint32_t)c1[i];
    }
    
    return c;
  }
  int h = (n + 1) / 2;
  
  uint32_t* a1 = new uint32_t[h];
  uint32_t* a2 = new uint32_t[h];
  uint32_t* b1 = new uint32_t[h];
  uint32_t* b2 = new uint32_t[h];
  
  fill(a1, a1 + h, 0);
  fill(a2, a2 + h, 0);
  fill(b1, b1 + h, 0);
  fill(b2, b2 + h, 0);
  
  for (int i = 0; i < n / 2; i++) {
    a1[i] = a[i];
    b1[i] = b[i];
  }
  for (int i = n / 2; i < n; i++) {
    a2[i - n / 2] = a[i];
    b2[i - n / 2] = b[i];
  }
  
  uint32_t* v = karatsuba(a1, b1, h);
  uint32_t* u = karatsuba(a2, b2, h);
  
  a1 = add(a2, h, a1, h);
  b1 = add(b2, h, b1, h);
  
  uint32_t* w = karatsuba(a1, b1, h + 1);
  
  w = sub(w, 2 * h + 2, u, 2 * h);
  w = sub(w, 2 * h + 2, v, 2 * h);
  u = shift(u, 2 * h, (n / 2) * 2);
  w = shift(w, 2 * h + 2, n / 2);
  
  u = add(u, 2 * n, w, 2 * h + 2 + n / 2);
  u = add(u, 2 * n, v, 2 * h);
  
  return u;
  
}
