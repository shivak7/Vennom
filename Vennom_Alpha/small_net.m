%clc;
clear all;

% So = load('VNNM_small_0.dat');
% To = So(:,1);
% Vo = So(:,2);

addpath('../../DBS_programming/Opto_code');
tic
RunXPP('ten_cortex_noise_sine_input_original.ode',[],[],'../../DBS_programming/Opto_code/xppall/xppaut');
toc
X = load('./output.dat');
X1 = X(:,2);
Tx = X(:,1);

system('./test');
V = load('VNNM_small_1.dat');
V1= V(:,2);
Tv = V(:,1);

figure
plot(Tx,X1);
hold on
plot(Tv,V1,'r');

[X1(1:10) V1(1:10)]