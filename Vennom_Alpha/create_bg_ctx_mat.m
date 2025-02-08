clc;
clear all;

N(1) = 40;  %Cortical neurons
N(2) = 20;  %Striatum neurons
N(3) = 10;  %STN
N(4) = 10;  %GPe
N(5) = 10;  %GPi
N(6) = 20;   %Thalmo-cortical neurons

g_ctx_str = 1;
gs_ctx_str = [0.3 0.3 1 1].*g_ctx_str;

g_ctx_stn = 1;
gs_ctx_stn = [0.3 0.3 0.3 0.3 1 1 1 1].*g_ctx_stn;

g_str_gpi = 1;
gs_str_gpi = [0.3 0.3 1 1].*g_str_gpi;

g_str_gpe = 1;
gs_str_gpe = [0.3 0.3 1 1].*g_str_gpe;

g_gpi_tc = 1;
gs_gpi_tc = [0.3 0.3 1 1].*g_gpi_tc;

g_tc_ctx = 1;
gs_tc_ctx = [0.3 0.3 1 1].*g_tc_ctx;

g_sg = 0.4; %stn to gpe or gpi
g_gs = 0.5;% gpe to stn

for i = 1:length(N)
    if(i==1)
        Ts(i) = 1;
        Te(i) = N(1);
    else
        Ts(i) = sum(N(1:i-1)) + 1;
        Te(i) = sum(N(1:i));
    end
end
 
Tsize = sum(N);

M = zeros(Tsize,Tsize);


%% Cortex to Striatum
k = 1; %Cortex
g_ctx_str = 0.7;
g_ctx_str_weak = 0.3;    %Synaptic strength
g_ctx_str_strong = 1;
gs = gs_ctx_str;
to = 2;
k = 1;
step = 0;
j = Ts(to);

step = 0;   %Weak synaptic connections from Ctx to Str
jmp_size = N(k)/N(to);
for i = Ts(k)-1:jmp_size:Te(k)-1
    
    if(i==Ts(k)-1)
        i3 = mod(i+3,N(k));
        M(Te(k),Ts(to)) = gs(1);
        M(Ts(k)-1+i3,Ts(to)) = gs(2);
    else
        i2 = mod(i,N(k));
        i3 = mod(i+3,N(k));
        %if((i>1)&&(i+3<N(k)))
            M(i2,j+1+step) = gs(1);
            M(i3,j+1+step) = gs(2);
            step = step + 1;
    end
       M(i+1,j+step) = gs(3);
       M(i+2,j+step) = gs(4);
end

%% Cortex to STN
k = 1; %Cortex
g_ctx_stn_weak = 0.3;    %Synaptic strength
g_ctx_stn_strong = 1;
gs = gs_ctx_stn;
to = 3;     %STN

step = 0;
j = Ts(to);
step = 0;   %Weak synaptic connections from Ctx to Str
jmp_size = N(k)/N(to);
for i = Ts(k)-1:jmp_size:Te(k)-1
    
     if(i==0)
         i5 = mod(i+5,N(k));
         i6 = mod(i+6,N(k));
         M(N(k),Ts(to)) = gs(1);
         M(N(k)-1,Ts(to)) = gs(2);
         M(i5,Ts(to)) = gs(3);
         M(i6,Ts(to)) = gs(4);
     else
         
        i2 = mod(i-1,40);
        i3 = mod(i,40);
        i4 = mod(i+5,40);
        i5 = mod(i+6,40);
        M(i2,j+1+step) = gs(1);
        M(i3,j+1+step) = gs(2);
        M(i4,j+1+step) = gs(3);
        M(i5,j+1+step) = gs(4);
        step = step + 1;
    end
    
    for strong = 1:4
       M(i+strong,j+step) = gs(4+strong);
    end
end

%% STN to GPe and vice versa
from = 3;
to = 4;

step = 0;
j = Ts(to);
for i = Ts(from):Te(from)
  M(i,j + step) = g_sg; % 1:1 connection
  step = step + 1;
end

from = 4;
to = 3;
step = 0;
j = Ts(to);
for i = Ts(from):Te(from)
  
  if(j+step-1<Ts(to))
  	M(i,Te(to)) = g_gs;
  else
  	M(i,j+step-1) = g_gs;
  end
  
  M(i,j+step) = g_gs;
  
  if(j+step+1>Te(to))
  	M(i, Ts(to)) = g_gs;
  else
  	M(i,j+step+1) = g_gs;
  end
  
  step = step + 1;
end 
%% STN to GPi

from = 3;
to = 5;

step = 0;
j = Ts(to);
for i = Ts(from):Te(from)
  M(i,j + step) = g_sg; % 1:1 connection
  step = step + 1;
end

%% Striatum to Gpe

k = 2; % Striatum
g_str_gpe_weak = 0.3;    %Synaptic strength
g_str_gpe_strong = 1;
to = 4; %GPe
step = 0;
j = Ts(to);
gs = gs_str_gpe;
step = 0;   %Weak synaptic connections from Ctx to Str
jmp_size = N(k)/N(to);
for i = Ts(k)-1:jmp_size:Te(k)-1
    
    if(i==Ts(k)-1)
        i3 = mod(i+3,N(k));
        M(Te(k),Ts(to)) = gs(1);
        M(Ts(k)-1+i3,Ts(to)) = gs(2);
        %keyboard
    else
        i2 = mod(i,N(k));
        i3 = mod(i+3,N(k));
        %if((i>1)&&(i+3<N(k)))
            M(Ts(k)-1+i2,j+1+step) = gs(1);
            M(Ts(k)-1+i3,j+1+step) = gs(2);
            step = step + 1;
    end
       M(i+1,j+step) = gs(3);
       M(i+2,j+step) = gs(4);
end


%% Striatum to Gpi

k = 2; % Striatum
g_str_gpi_weak = 0.3;    %Synaptic strength
g_str_gpi_strong = 1;
gs = gs_str_gpi;
to = 5; %GPi
step = 0;
j = Ts(to);

step = 0;   %Weak synaptic connections from Ctx to Str
jmp_size = N(k)/N(to);
for i = Ts(k)-1:jmp_size:Te(k)-1
    
    if(i==Ts(k)-1)
        i3 = mod(i+3,N(k));
        M(Te(k),Ts(to)) = gs(1);
        M(Ts(k)-1+i3,Ts(to)) = gs(2);
        %keyboard
    else
        i2 = mod(i,N(k));
        i3 = mod(i+3,N(k));
        %if((i>1)&&(i+3<N(k)))
            M(Ts(k)-1+i2,j+1+step) = gs(1);
            M(Ts(k)-1+i3,j+1+step) = gs(2);
            step = step + 1;
    end
       M(i+1,j+step) = gs(3);
       M(i+2,j+step) = gs(4);
end

%% GPi to Thalamus using inverese loop
k = 6; % Thalmus
g_gpi_tc_weak = 0.3;    %Synaptic strength
g_gpi_tc_strong = 1;
gs = gs_gpi_tc;
to = 5;     % Gpi
step = 0;
j = Ts(to);
step = 0;   
jmp_size = N(k)/N(to);

for i = Ts(k)-1:jmp_size:Te(k)-1
    
    if(i==Ts(k)-1)
        i3 = mod(i+3-Ts(k)+1,N(k));
        M(Ts(to),Te(k)) = gs(1);
        M(Ts(to),Ts(k)-1+i3) = gs(2);
    else
        i2 = mod(i-Ts(k)+1,N(k));
        i3 = mod(i-Ts(k)+1+3,N(k));
        %if((i>1)&&(i+3<N(k)))
            M(j+1+step,Ts(k)-1+i2) = gs(1);
            M(j+1+step,Ts(k)-1+i3) = gs(2);
            step = step + 1;
    end
       M(j+step, i+1) = gs(3);
       M(j+step, i+2) = gs(4);
end

%% Thalamus to Cortex using inverese loop
k = 1; % Cortex
g_tc_ctx_weak = 0.3;    %Synaptic strength
g_tc_ctx_strong = 1;
gs = gs_tc_ctx;
to = 6;     % Thalamus
step = 0;
j = Ts(to);
step = 0;   
jmp_size = N(k)/N(to);

for i = Ts(k)-1:jmp_size:Te(k)-1
    
    if(i==Ts(k)-1)
        i3 = mod(i+3-Ts(k)+1,N(k));
        M(Ts(to),Te(k)) = gs(1);
        M(Ts(to),Ts(k)-1+i3) = gs(2);
    else
        i2 = mod(i-Ts(k)+1,N(k));
        i3 = mod(i-Ts(k)+1+3,N(k));
        %if((i>1)&&(i+3<N(k)))
            M(j+1+step,Ts(k)-1+i2) = gs(1);
            M(j+1+step,Ts(k)-1+i3) = gs(2);
            step = step + 1;
    end
       M(j+step, i+1) = gs(3);
       M(j+step, i+2) = gs(4);
end

imagesc(M);
save BG_CTX_MAT.dat -ASCII M

k = 0;
for i = 1:size(M,1)
    for j = 1:size(M,2)
      if(M(i,j)>0)
          k = k+1;
      end
    end
end
k