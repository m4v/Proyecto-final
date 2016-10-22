s = tf('s');

% parametros
td = 50; % retraso
tau = 51*60; % constante de tiempo
a = 1/tau; % polo
TMAX = 1500;
PMAX = 2200;
Ap = TMAX/PMAX; % factor de escala temp/potencia
Ch = Ap * a; % constante de escala del horno

% planta
G = Ch * (1 - td*s) / (s + a);

% controlador PI
Kp = tau/td * 0.9;
Ti = td / 0.3;
Cpi = Kp * (1 + 1/(Ti*s));
%Cpi = Kp;

% controlador PID
%Kp = tau/td * 1.2;
%Ti = td *2;
%Td = 0.5*td;
%Cpid = Kp * (1 + 1/(Ti*s) + Td*s)/(s + 1000)^2;

figure(1)
step(G*PMAX, 5*tau)
axis([0 5*tau 0 TMAX])

% entrada
Tsec = 200; Tcoc = 1000;
pc = 100/60; % pendiente maxima de coccion, 100C por min
ta = (Tcoc - Tsec) / pc; % tiempo de calentamiento
tc = 3600; % tiempo de coccion
ts = 1800; % tiempo de secado
t2 = ts + ta; % fin de calentamiento
tmax = t2 + tc;
t = 0:tmax;
X = zeros(1, tmax + 1);
X(1:ts) = Tsec; % secado
b = Tsec - pc*ts;
X(ts+1:t2) = pc*(ts+1:t2)' + b;
X(t2+1:tmax+1) = 1000; % coccion

C = Cpi;
Y = C*G/(1+C*G);
P = C/(1+C*G);

figure(2);
[y _t _x] = lsim(Y, X, t);
plot(t, y, t, X, '-r'); grid;
axis([0 tmax 0 (Tcoc + 200)])

figure(3);
[u _t _x] = lsim(P, X, t);
plot(t, u); grid;
axis([0 tmax min(u) max(u(ts:tmax))])

