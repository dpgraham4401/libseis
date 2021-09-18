function [R] = frad(data,x0,dt,dx,p0,dp,res)
% 
% David Graham
% UTD, 4/26/18
% 
% This function is design to forward parabolic radon transform a
%  seismic image in time and offset d(x,t) space to time intercept and
%  slope (tau-p) domain. 
% 
% [data] is a 2d array that contains the CMP pre-processed data
% [x0] is inital offset form source
% [dt] is a scalar (in seconds) representing the sampling rate
% [dx] is a scalar (m or km)  distance between each reaciever
% [p0] is a scalar denoting the lowest (neg) slowness (s/m)
% [dp] is the scalar change in p depending on resoltuion
% [res] is scalar denoting how many samples, higher res more parabolas
% 
[nr,nc]=size(data);

R=zeros((size(data,1)),res);
for i=1:nr;
 t0=i*dt;
 for n=1:res;
   p=p0+(n-1)*dp;
   sum=0;
   for j=1:nc;
     x=x0+(j-1)*dx;
     para=t0+p*x^2;
       itt=1+(round(para/dt));
       if (itt<=size(data,1)) && (itt>0);
         sum=sum+data(itt,j);
       end
    end
%       loc=1+(abs(p0)/dp)+round(p/dp);
      R(i,n)=sum;
  end
end

end

