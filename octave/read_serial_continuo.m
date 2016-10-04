% Script de Octave para leer y graficar datos desde el puerto serial.

serial_init

% creamos una figura
clf
clear t v w
t(1) = 0; v(1) = 0;
h1 = plot(t, v, 'xb');
hold on
h2 = plot(t, v, '+r');
grid on

log = fopen("registro.log", "a");
fwrite(log, sprintf("-Inicio del registro de captura %s\r\n", fecha()));

srl_write(fd, "c"); % iniciar captura
Tm = 1; % en este modo el muestreo es cada seg
i = 1;
unwind_protect
  while(1)
    % leemos una línea, que son 24 bytes en total
    str = char(srl_read(fd, 24));
    n = base2dec(str(1:10), 10);    % num. de muestra
    d1 = base2dec(str(13:16), 10);  % termocupla
    d2 = base2dec(str(19:22), 10);  % lm35
    if (isnan(n) || isnan(d1) || isnan(d2))
      printf("error en la lectura de datos\n");
      break;
    end
    t(i) = n * Tm;
    v(i) = d1 * LSB;
    w(i) = d2 * LSB;
    % actualizar gráfico
    set(h1, 'XData', t, 'YData', v);
    set(h2, 'XData', t, 'YData', w);
    drawnow;
    %guardamos un registro
    fwrite(log, str);
    i++;
    % hacemos una pausa proporcional al muestreo así no estamos esperando mucho 
    % en srl_read que dificulta terminar el script con ctrl-c
    pause(Tm*0.8);
  end
unwind_protect_cleanup
  % Ctrl-C, detener y cerrar la conección
  srl_write(fd, "c");
  fclose(fd);
  fwrite(log, sprintf("-Fin de la captura %s\r\n", fecha()));
  fclose(log);
  % guardar los datos capturados
  % antes de guardar las longitudes tienen que ser iguales
  N = min([length(t), length(v), length(w)]);
  t = t(1:N);
  v = v(1:N);
  w = w(1:N);
  csvwrite(sprintf("captura_continua_%s.csv", fecha()), [t' v' w']);
  printf("captura guardada\n")
end
