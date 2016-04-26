int f(int x) {
  while (x > 0)
    x = x - 1;

  return 0;
}

int main() {
  int x;
  
  x = 0;

  x = x + 1;

  if (x == 1)
    x = 1 + 1;
  else
    x = 1 - 1;

  return f(0);
}
