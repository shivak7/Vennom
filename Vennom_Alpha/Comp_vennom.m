clc;
clear all;

S1 = load('../src/volt.txt');
S2 = load('volt.txt');

plot(-S1); hold on
plot(-S2,'r--');

S1(1:10)'
S2(1:10)'