function [model] = irad(R,x0,dt,dx,p0,dp,res,nr,nc)
% David Graham
% UTD, 4/26/18
%function irad is designed to take the inverse Radon transform of
%parabolicly transformed data (R) in the tau-p domaind back to the
%space-time domain as a 2d array (model).
% 
% [R] is a 2d array the contains amplitudes assocated with each point in
% the array where y axis is time and x axis is slowness (s/m or s/km)
% [x0] is the inital offset from the seimic source
% [dt] is a scalar (in seconds) representing the sampling rate
% [dx] is a scalar (m or km)  distance between each reaciever
% [nr] is a scalar with the number of rows of the inverse transformed data.
% this is will be equal to the sampled time window of the siesmic 
% [p0] is a scalar denoting the lowest (neg) slowness (s/m)
% [dp] is the scalar change in p depending on resoltuion
% [res] is scalar denoting how many samples, higher res more parabolas
% 

model=zeros(nr,nc);
for i= 1:nr
 t0=i*dt;
 for n=1:res
   p=p0+(n-1)*dp;
   amp=R(i,n);
   for j=1:nc
    x=x0+(j-1)*dx;
    para=t0+p*x^2;
    if (para>0)&&(para<(nr*dt))
      m=1+floor(para/dt);
      model(m,j)=model(m,j)+amp;
    end
    end
 end
end


        

end

