// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
  TStack<char> st1;
  std::string hyp = "";
  TStack<std::string> st2;
  TStack<int> dst2;
  int t[1000];
  t['*'] = 2;
  t['/'] = 2;
  t['-'] = 1;
  t['+'] = 1;
  std::string a;
  int coef = 0;
  a = inf;
  for (int i = 0; i < a.length(); i++) {
    if (a[i] == '(') {
      coef += 2;
    } else if (a[i] == ')') {
      coef -= 2;
    } else if ((a[i] >= '0') && (a[i] <= '9')) {
      std::string z = "";
      do {
        z += a[i];
        i++;
      } while ((i < a.length()) && ((a[i] >= '0') && (a[i] <= '9')));
      i--;
      st2.push(z);
    } else if (st1.isEmpty()) {
      st1.push(a[i]);
      dst2.push(t[a[i]] + coef);
    } else if (t[a[i]] + coef > dst2.get()) {
      st1.push(a[i]);
      dst2.push(t[a[i]] + coef);
    } else {
      bool er = true;
      while ((!st1.isEmpty()) && (er == true)) {
        if (dst2.get() >= t[a[i]] + coef) {
          std::string b = "";
          b += st1.get();
          st2.push(b);
          st1.pop();
          dst2.pop();
        } else {
          er = false;
        }
      }
      st1.push(a[i]);
      dst2.push(t[a[i]] + coef);
    }
  }
  while (!st1.isEmpty()) {
    std::string b = "";
    b += st1.get();
    st2.push(b);
    st1.pop();
    dst2.pop();
  }
  while (!st2.isEmpty()) {
    p += (st2.get()+' ');
    st2.pop();
  }
  std::string s = "";
  for (int i = 0; i < hyp.length(); i++)
    if (!((i == 0) && (hyp[hyp.length() - 1] == ' ')))
      s += hyp[hyp.length() - 1 - i];
  return s;
}

int eval(std::string pst) {
    TStack<int> x;
  for (int i = 0; i < pst.length(); i++) {
    if ((pst[i] >= '0') && (pst[i] <= '9')) {
      std::string z = "";
      do {
        z += pst[i];
        i++;
      } while ((i < pst.length()) && ((pst[i] >= '0') && (pst[i] <= '9')));
      i--;
      x.push(stoi(z));
    } else if (pst[i] == '+') {
      int s = 0;
      s += x.get();
      x.pop();
      s += x.get();
      x.pop();
      x.push(s);
    } else if (pst[i] == '-') {
      int s = -1 * x.get();
      x.pop();
      s += x.get();
      x.pop();
      x.push(s);
    } else if (pst[i] == '*') {
      int s = x.get();
      x.pop();
      s *= x.get();
      x.pop();
      x.push(s);
    } else if (pst[i] == '/') {
      int s = x.get();
      x.pop();
      int c = x.get();
      x.pop();
      x.push(c/s);
    }
  }
  return x.get();
  return 0;
}
