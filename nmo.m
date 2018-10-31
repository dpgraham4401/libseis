function [output] = nmo(input,nr,nc,x0,dt,dx,vcurv)
% This function is designed to NMO correct a CMP or shot gather based on a
% velocity curve with increasing time ('vcurv')
% 
% [input] is a 2d array that contains the CMP pre-processed data (gain+mute)
% [nr] number of rows for each CMP gather = time window/sampling rate
% [nc] number of columns per CMP gather or the fold or number of traces
% [x0] is inital geo/hydrophone offset form source
% [dt] is a scalar (in seconds) representing the sampling rate
% [dx] is a scalar (m or km)  distance between each reaciever
% [vurcv] is a vector that denotes velocity (m/s or km/s) with time 
% i.e. length of vcurv = nr

output=zeros(size(input)); 
  for i = 1:nr
   t = i*dt;
     for j = 1:nc
       x = x0+(j-1)*dx;
       val = round(sqrt(t^2+x^2/vcurv(i)^2)/dt);
       if(val>=1 && val<=nr)
         output(i,j) = input(val,j);
       end
     end
  end

end

