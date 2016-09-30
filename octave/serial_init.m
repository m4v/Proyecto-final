% inicialización del serial y cosas comunes que necesito en otros scripts

% comando para cargar las funciones del puerto serial de Octave
pkg load instrument-control

% función para convertir los datos del serial a un número
function n = a_numero(a)
  n = base2dec(char(a), 10);
end

function s = fecha()
  s = sprintf("%s_%s", date, strftime("%H:%M:%S", localtime(time)));
end

Tm = 100e-3;          % periodo de muestreo
LSB = 3.3/(2^12 - 1); % resolucion del ADC

try
  fd = serial("/dev/ttyUSB0", 115200);
catch
  fd = serial("/dev/ttyUSB1", 115200);
end
