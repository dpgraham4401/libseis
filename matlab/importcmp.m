function [cmp] = importcmp( file,nr,nc,ncmp)
% David Graham
% UTD, 4/27/18
%
% function 'importcmp' is designed to import a number of cmp binary files
% into a cell array. the number of samples per trace (nr) and number of
% traces per cmp is required. it can only handle binary files where every
% CMP has the same fold (number of traces/columns)
% 
% [cmp] is a vector cell array where each cell is a CMP file. 
% [file] is a string with the desired file name to be imported, you need to
% know how many CMP gathers are in this file. 
% [nr] number of rows for each CMP gather = time window/sampling rate
% [nc] number of columns per CMP gather or the fold or number of traces
% [ncmp] the number of CMP gathers in 'file' to be imported. 

fid=fopen(file);
data=fread(fid, inf, 'single');
fclose(fid);

 cmp=cell(1,ncmp);
for k=1:ncmp;
array=zeros(nr,nc);
skip=numel(array)*(k-1);
  for i=1:nc;
    j=nr*i+skip;
    n=1+skip+(nr*(i-1));
    if k<1;
      if i>1;
        n=(((i-1)*nc)+skip)+1;
      end
    end
    array(1:nr,i)=data(n:j);
  end
cmp{k}=array;
end

return

