function [output] = gain(input,nr,nc,dt,pow)
% David Graham
% UTD, 4/28/18
% 
% The function gain is designed to gain a CMP gather as a function of t,
% currently only gaining by t^pow, but further releases could have
% alternative options for gaining. 
% 
% [cmp] is a 2d array with it's y-axis in time and x-axis is space
% [nr] number of rows for each CMP gather = time window/sampling rate
% [nc] number of columns per CMP gather or the fold or number of traces
% [dt] is a scalar (in seconds) representing the sampling rate
% [dx] is a scalar (m or km)  distance between each reaciever
% [pow] is a scalar (unitless) denoting the desired power to be applied
% with increaseing t, greater pow --> greater gain.

output=zeros(size(input));
for y = 1:nr;
    t=y*dt;
    for x = 1:nc;
      output(y,x) = (t^pow)*input(y,x); 
    end
end

end

