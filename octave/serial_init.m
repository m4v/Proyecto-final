% inicialización del serial y cosas comunes que necesito en otros scripts

% comando para cargar las funciones del puerto serial de Octave
pkg load instrument-control

% función para convertir los datos del serial a un número
function n = a_numero(a)
  n = base2dec(char(a), 10);
end

Tm = 10e-3;           % periodo de muestreo
LSB = 3.3/(2^12 - 1); % resolucion del ADC

try
  fd = serial("/dev/ttyUSB0", 115200);
catch
  fd = serial("/dev/ttyUSB1", 115200);
end

