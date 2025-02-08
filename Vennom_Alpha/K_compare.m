
Params = [-32  8  1  100  -80  -26];
%Params = [-32  -8  1  100  80  26];

V = 0;
k = 0;
dt = 0.05;
x_inf = 1/(1 + exp(-(V-Params(1))/Params(2)));
%x_inf = 1/(1 + exp((V-Params(1))/Params(2)));

x_tau = Params(3) + Params(4)/(1 + exp(-(V-Params(5))/Params(6)));
%x_tau = Params(3) + Params(4)/(1 + exp((V+Params(5))/Params(6)));

dx_dt = (x_inf - k)/x_tau;

k_1 = k + dx_dt*dt;


thetan=-32,sn=-8
taun0=1,taun1=100,thn=80,sigman=26

ninf=1./(1.+exp((V-thetan)/sn));
taun=taun0+taun1/(1+exp((V+thn)/sigman));

n = phi*( ninf-k)/taun(v[0])

