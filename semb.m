function [vscan,svvec,stvec] = semb(data,nc,twin0,twine,v0,ve,x0,dvs,dx,dts,dt,sres)
% David Graham
% UTD, 4/27/18
% Function semb computes but does not display the semblance of a cmp or
% shot gather array and returns 'vscan' which is a 2d array that can be
% used to create a velocity function with time that can later be used to
% NMO correct the cmp or shot gather.
%  
% [vscan] is the 2d array with the Semblance
% [svvec] resized velocity vector for plotting
% [stvec] resized t0 vector for plotting
% 
% [data] is the cmp in 2d array form
% [nr] is the number of rows or the time window/sampling rate
% [nc] is the number of columns or recievers in the CMP
% [v0] is the lowest velocity desired to scan over. 
% [dv] is the change in velocity between sampling points, this is directly
% tied to the image resolution or 'res' so dv=(vo-vend)/res;
% [x0] is the initial offset in the CMP, or the first trace offset
% [dx] change in offset or reciever spacing
% [dt] change in time or sampling rate
% [sres] is the resolution of semb, higher resolution -> costly  
% 
vscan=zeros(sres,sres);

for i = 1:sres;
  v=v0+(i-1)*dvs;
  for n=1:sres;
    t0=n*dts;
    sum1=0;
    sum2=0;
      for m=1:size(data,2);
        x=x0+(m-1)*dx;
      trc=data(:,m);
      hyp=sqrt(t0^2+(x^2/v^2));
      amp=interp1(trc,(hyp/dt));
      sum1=amp+sum1;
      sum2=amp^2+sum2;
      end
    semb=sum1^2/(nc*sum2);
    vscan(n,i)=semb;
  end
end

vscan=interpn(vscan,2); 
svvec = linspace(v0,ve,size(vscan,2)); 
stvec=linspace(twin0,twine,size(vscan,1)); 
end

