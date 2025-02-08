#include <iostream>
#include <vector>

void SplineDeriv(std::vector<double> &Out, std::vector<double> &Derivs, int columns);
void Spline(std::vector<double> &Out, std::vector<double> &Derivs, std::vector<int> &reg_idx, std::vector<double> &Out_sampled, int columns, double dt);
