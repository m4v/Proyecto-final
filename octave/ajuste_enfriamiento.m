% Script de Octave para ajustar las mediciones hechas con una
% respuesta a un escalón

global tmed vmed y;

% la curva de enfriamiento es una exponencial decreciente

y = @(A, a, t0, t) A*exp(-a*(t-t0));

% siendo 
% a  - polo del sistema
% A  - valor inicial
% t0 - retraso

% leo los datos de la medición
D = csvread("../mediciones/captura_continua_04-Oct-2016_18:50:57.csv");
tmed = D(:,1);
vmed = D(:,2);

% la función a minimizar será el error cuadrático medio entre el modelo y las 
% mediciones

function E = error(M)
global tmed vmed y;
% M es un vector de los parámetros a estimar
A = M(1);
a = M(2);
t0 = M(3);

vmodelo = y(A, a, t0, tmed);
E = mean((vmed-vmodelo).^2);
end

% valores iniciales 
M0 = [3, 1/4500, 0];

% fue necesario jugar mucho con las tolerancia de convergencia para tener algo bueno
OPT = optimset("Display", "none", "TolX", 1e-18, "MaxFunEvals", 1000, "MaxIter", 1000);
resultado = fminsearch(@error, M0, OPT);

A = resultado(1);
a = resultado(2);
t0 = resultado(3);

t2 = 0:(1/a)*6;

printf("Resultado A:%.4f a:%.8f Tau:%.4f t0:%.2f\n", A, a, 1/a, t0);
plot(tmed/3600, vmed, 'x', t2/3600, y(A, a, t0, t2), '-r')
grid on
