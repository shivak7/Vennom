clc;
clear all;
 
 S = load('VNNM_out.dat');
 T = S(:,1); 
 V = S(:,2);

Vnd = downsample(V,4);
Td = downsample(T,4);

% addpath('../../DBS_programming/Opto_code');
% tic
% RunXPP('MorrisLecar.ode',[],[],'../../DBS_programming/Opto_code/xppall/xppaut');
% toc
% X = load('./output.dat');
% X1 = X(:,2);
% Tx = X(:,1);

figure;
 %load DBSBiphasic_nostim_Iapp_5_gSyn_0.5.mat
 %imac(Td,[1:10],Vd');
  plot(T,V(:,1),'r');
%  hold on
 %plot(Tx,X1);
