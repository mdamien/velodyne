%Topark par Gautier et Di
clear all
close all
data1 = fopen('data1.txt', 'w'); fclose(data1);
data2 = fopen('data2.txt', 'w'); fclose(data2);
data3 = fopen('data3.txt', 'w'); fclose(data3);
%------------------------------------------------------------------------
%les paramètres de la voiture et la position
a=4.9;
b=1.7;
s=1.2;
c=2.75;
d1=7;
d2=1;
d3=0.2;
d4=8.0;
d5=0.2;
d6=0.2;
rmin=4.15;

%------------------------------------------------------------------------
%Calcul du sum et theta
f = @(t)[(d4-d3-s)*(1-t)-(d2+b-d6)*sqrt(1-t*t)];
t=fzero(f,0);
theta=acos(t);
sum=(d4-d3-s)/sin(theta);

%------------------------------------------------------------------------
%Calcul du r1min et r1max, amin et amax, aconsigne
R=zeros(10*(sum-2*rmin),2);
t=1;
for r1=rmin:.05:sum-rmin
    toucher=0;
% le premier procuss    
    for theta0=0:.1:theta
        x0=d4-r1*sin(theta0);
        y0=b/2+d2+1.7-r1*(1-cos(theta0));
        for x=x0+b/2*sin(theta0)-s*cos(theta0):.01:x0+b/2*sin(theta0)+(a-s)*cos(theta0)
            y=tan(theta0)*x+y0-b/2*cos(theta0)-tan(theta0)*x0-b/2*tan(theta0)*sin(theta0);
            if y<=1.7+d5 & x>=d1-d5
                toucher=1;
            end
        end
    end
% le deuxieme procuss    
    for theta0=theta:.1:0
        x0=d3+s+(sum-r1)*sin(theta0);
        y0=b/2+d6+(sum-r1)*(1-cos(theta0));
        for x=x0+b/2*sin(theta0)-s*cos(theta0):.01:x0+b/2*sin(theta0)+(a-s)*cos(theta0)
            y=tan(theta0)*x+y0-b/2*cos(theta0)-tan(theta0)*x0-b/2*tan(theta0)*sin(theta0);
            if y<=1.7+d5 & x>=d1-d5
                toucher=1;
            end
        end
    end
    R(t,1)=r1;
    R(t,2)=toucher;
    t=t+1;
end
% cherche le r1min et r1max dans la matrice R
t=1;
[m1,m2]=size(R);
r1min=R(m1,1);
r1max=R(t,1);
for t=1:m1
    if R(t,2)==0 
        if R(t,1)<=r1min
            r1min=R(t,1);
        end
        if R(t,1)>=r1max;
            r1max=R(t,1);
        end
    end
end
amin=atan(c/r1max)*180/pi;
amax=atan(c/r1min)*180/pi;
aconsigne=(amin+amax)/2;

%------------------------------------------------------------------------
%écrire a1 consigne dans le fichier date1.txt
data1 = fopen('data1.txt', 'w');
fprintf(data1, '%3.3f \n %3.3f \n %3.3f', aconsigne,amin,amax);
fclose(data1);

%------------------------------------------------------------------------
%lire a1 réel dans le fichier date2.txt
while(1)
data2 = fopen('data2.txt', 'r');
a1 = fscanf(data2,'%f');
    if isfloat(a1) & ~isempty(a1)
        break;
    end
fclose(data2);
pause(1);
end

%------------------------------------------------------------------------
%calcule d1,a2,d2
r1=c/tan(abs(a1/180*pi));
r2=sum-r1;
d1=theta*r1;
a2=-atan(c/r2)*180/pi;
d2=theta*r2;

%------------------------------------------------------------------------
%écrire d1,a2,d2 dans le fichier date3.txt
data3 = fopen('data3.txt', 'w');
fprintf(data3, '%3.3f \n %3.3f \n %3.3f', d1,a2,d2);
fclose(data3);
