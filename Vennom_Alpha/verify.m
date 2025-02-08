clc;
clear all

dt = 0.05;
fs = 1000/dt;

addpath('../../DBS_programming/Opto_code');
tic
RunXPP('llr_stn.ode',[],[],'../../DBS_programming/Opto_code/xppall/xppaut');
toc
X = load('./output.dat');
X1 = X(:,2);
Tx = X(:,1);
%S2 = S(:,3);

system('./test');
V = load('VNNM_out.dat');
V1= V(:,2);
Tv = V(:,1);

 plot(Tv,V1); hold on
 plot(Tx,X1,'r--');

%[S2 V]
