clc;
clear all;

Nstn = 10;
Ngpe = 10;

Tsize = Nstn + Ngpe;

M = zeros(Tsize,Tsize);

g_sg = 1;
g_gs = 5;


%First set STN connectivity
for i = 1:Nstn
  M(i,Nstn+i) = g_sg; % 1:1 connection
end

%Next set GPe connectivity
for i = 1:Ngpe

  if(i-1<1)
  	M(Ngpe+i,Nstn) = g_gs;
  else
  	M(Ngpe+i,i-1) = g_gs;
  end
  
  M(Ngpe+i,i) = g_gs;
  
  if(i+1>Nstn)
  	M(Ngpe+i,1) = g_gs;
  else
  	M(Ngpe+i,i+1) = g_gs;
  end
  
end 	

save SGC.dat -ASCII M