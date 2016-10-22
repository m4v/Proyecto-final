% Script de Octave para leer y graficar datos desde el puerto serial.

serial_init

srl_write(fd, "m"); % el comando m inicia la captura de 1000 puntos

N = 1000;
v = zeros(N,1);
t = zeros(N,1);

for i=1:N
  % el número de muestra son 10 caracteres
  n = a_numero(srl_read(fd, 10));
  t(i) = n;
  srl_read(fd, 2); % descartar ', '
  % valor del AD 4 caracteres
  n = a_numero(srl_read(fd, 4)); 
  v(i) = n;
  srl_read(fd, 2); % descartar '\r\n'
end

fclose(fd);

% escalar los valores
t *= Tm;  
v *= LSB;

plot(t, v, '.-');
drawnow;
