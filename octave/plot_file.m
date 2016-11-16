% script para graficar las capturas y ver rápidamente que es que

name = file
D = csvread(name);
t = D(:,1) - D(1,1);
T = D(:,2);
ref = D(:,9);
piy = D(:,7);
dc = D(:,8);

figure(1);
plot(t, T, 'b', t, ref, 'r');
title(name)
figure(2);
plot(t, piy, 'r', t, dc, 'b');
title(name)
