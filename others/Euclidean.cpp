/*
return the greatest common divisor (gcd) of a and b
*/
int gcd_basic(int a, int b) {
  if (!(a % b)) {
    return b;
  }
  return gcd_basic(b, a % b);
}

/*
return the greatest common divisor (gcd) of a and b
find s and t, such that sa + tb = gcd(a, b)
*/
int gcd_extended(int a, int b, int &s, int &t) {
  // base case
  if (!(a % b)) {
    s = 0;
    t = 1;
    return b;
  }
  // s1 and t1 record last equation's s and t
  int s1, t1;
  int gcd = gcd_extended(b, a % b, s1, t1);
  // s and t record current equation's coefficients.
  // We use s and t from last equation to calculate current equation's s and t
  s = t1;
  t = s1 - a / b * t1;
  return gcd;
}