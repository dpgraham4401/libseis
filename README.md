# DPG_2DSeis_proc
# seismic data processing
MATLAB functions for 2D seismic data processing
These are relatively simple scripts I made for a school project and,
do not include much functionality such as interactive picking.

functions included

importcmp.m - import seismic data from binary file  
gain.m      - apply t^pow to 2D seismic data  
nmo.m       - apply NMO to seismic data with supplied velocity function   
frad.m      - forward radon transform  
irad.m      - Radon transform adjoint   
semb.m      - velocity analysis, display semblance for velocity picking  

All functions start with a complete description of the inputs
