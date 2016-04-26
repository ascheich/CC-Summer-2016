int main() {
  int x;
  int y;
  int z;
  
  x = 0;
  y = 1;
  z = 2;

  x = y + 1;
  y = z + z;

  if (x == 1)
    x = z + 1;
  else
    x = z - 1;

  return 0;
}
