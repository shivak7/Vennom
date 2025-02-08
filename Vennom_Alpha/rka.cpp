
// rk4_adaptive.cpp

/*
  Function to advance set of coupled first-order o.d.e.s by single step
  using adaptive fourth-order Runge-Kutta scheme

     x       ... independent variable
     y       ... array of dependent variables
     h       ... step-length
     t_err   ... actual truncation error per step
     acc     ... desired truncation error per step
     S       ... step-length cannot change by more than this factor from
                  step to step
     rept    ... number of step recalculations
     maxrept ... maximum allowable number of step recalculations
     h_min   ... minimum allowable step-length
     h_max   ... maximum allowable step-length
     flag    ... controls manner in which truncation error is calculated

  Requires right-hand side routine

        void rhs_eval (double x, Array<double,1> y, Array<double,1>& dydx)

  which evaluates derivatives of y (w.r.t. x) in array dydx.

  Function advances equations by single step whilst attempting to maintain
  constant truncation error per step of acc:

    flag = 0 ... error is absolute
    flag = 1 ... error is relative
    flag = 2 ... error is mixed

  If step-length falls below h_min then routine aborts
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <blitz/array.h>

using namespace blitz;

void rk4_fixed (double&, Array<double,1>&,
                void (*)(double, Array<double,1>, Array<double,1>&),
                double);

void rk4_adaptive (double& x, Array<double,1>& y,
                   void (*rhs_eval)(double, Array<double,1>, Array<double,1>&),
                   double& h, double& t_err, double acc,
                   double S, int& rept, int maxrept,
                   double h_min, double h_max, int flag)
{
  // Array y assumed to be of extent n,  where n is no. of coupled
  // equations
  int n = y.extent(0);

  // Declare local arrays
  Array<double,1> y0(n), y1(n);

  // Declare repetition counter
  static int count = 0;

  // Save initial data
  double x0 = x;
  y0 = y;

  // Take full step
  rk4_fixed (x, y, rhs_eval, h);

  // Save data
  y1 = y;

  // Restore initial data
  x = x0;
  y = y0;

  // Take two half-steps
  rk4_fixed (x, y, rhs_eval, h/2.);
  rk4_fixed (x, y, rhs_eval, h/2.);

  // Calculate truncation error
  t_err = 0.;
  double err, err1, err2;
  if (flag == 0)
    {
      // Use absolute truncation error
      for (int i = 0; i < n; i++)
        {
          err = fabs (y(i) - y1(i));
          t_err = (err > t_err) ? err : t_err;
        }
    }
  else if (flag == 1)
    {
      // Use relative truncation error
      for (int i = 0; i < n; i++)
        {
          err = fabs ((y(i) - y1(i)) / y(i));
          t_err = (err > t_err) ? err : t_err;
        }
    }
  else
    {
      // Use mixed truncation error
      for (int i = 0; i < n; i++)
        {
          err1 = fabs ((y(i) - y1(i)) / y(i));
          err2 = fabs (y(i) - y1(i));
          err = (err1 < err2) ? err1 : err2;
          t_err = (err > t_err) ? err : t_err;
        }
    }

  // Prevent small truncation error from rounding to zero
  if (t_err == 0.) t_err = 1.e-15;

  // Calculate new step-length
  double h_est = h * pow (fabs (acc / t_err), 0.2);

  // Prevent step-length from changing by more than factor S
  if (h_est / h > S)
    h *= S;
  else if (h_est / h < 1. / S)
    h /= S;
  else
    h = h_est;

  // Prevent step-length from exceeding h_max
  h = (fabs(h) > h_max) ? h_max * h / fabs(h) : h;

  // Abort if step-length falls below h_min
  if (fabs(h) < h_min)
    {
      printf ("Error - |h| < hmin\n");
      exit (1);
    }

  // If truncation error acceptable take step
  if ((t_err <= acc) || (count >= maxrept))
    {
      rept = count;
      count = 0;
    }
  // If truncation error unacceptable repeat step
  else
    {
      count++;
      x = x0;
      y = y0;
      rk4_adaptive (x, y, rhs_eval, h, t_err, acc,
                    S, rept, maxrept, h_min, h_max, flag);
    }

  return;
}
