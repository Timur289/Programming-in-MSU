splot i*sin(sqrt(x**2+y**2))/sqrt(x**2+y**2) w l lt 1 lw 1.5 title sprintf("t=%i",i)
i=i+1
if(i<n) reread
