
inline static double fastexp(double y) 
{
    double d;
     *((int*)(&d) + 0) = 0;
     *((int*)(&d) + 1) = (int)(1512775 * y + 1072632447);
     return d;
}

inline static double fastpow(double a, double b) {
  union {
    double d;
    int x[2];
  } u = { a };
  u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
  u.x[0] = 0;
  return u.d;
}



