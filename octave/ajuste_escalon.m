% Script de Octave para ajustar las mediciones hechas con una
% respuesta a un escalón

global tmed vmed y;

% la respuesta al escalón está dada por

y = @(G, a, t0, t) G*(1 - exp(-a*(t-t0)));

% siendo 
% a  - polo del sistema
% t0 - retraso del sistema
% G - valor máximo de la respuesta que es igual a A*K/a, siendo A la altura del 
% escalón y K la ganancia del sistema, es decir:
% T(s) = K * exp(-t0*s) / (s + a)
% X(s) = A / s

% leo los datos de la medición
D = csvread("../mediciones/captura_continua_30-Sep-2016_19:32:35.csv");
%D = csvread("../mediciones/captura_continua_29-Sep-2016_20:00:26.csv");
%D = csvread("../mediciones/captura_continua_28-Sep-2016.csv");
tmed = D(:,1);
vmed = D(:,2);

% la función a minimizar será el error cuadrático medio entre el modelo y las 
% mediciones

function E = error(M)
global tmed vmed y;
% M es un vector de los parámetros a estimar
G = M(1);
a = M(2);
t0 = M(3);

vmodelo = y(G, a, t0, tmed);
E = mean((vmed-vmodelo).^2);
end

% valores iniciales 
M0 = [3, 1/3500, 70];

% fue necesario jugar mucho con las tolerancia de convergencia para tener algo bueno
OPT = optimset("Display", "none", "TolX", 1e-18, "MaxFunEvals", 1000, "MaxIter", 1000);
resultado = fminsearch(@error, M0, OPT);

t2 = 0:3600*3;
G = resultado(1);
a = resultado(2);
t0 = resultado(3);

printf("Resultado G:%.4f a:%.8f Tau:%.4f t0:%.4f\n", G, a, 1/a, t0);
plot(tmed/3600, vmed, 'x', t2/3600, y(G, a, t0, t2), '-r')

