% Script de Octave para leer y graficar datos desde el puerto serial.

serial_init

% creamos una figura
clf
clear t v
t(1) = 0; v(1) = 0;
h = plot(t, v, '.');
grid on

log = fopen("registro.log", "a");
fwrite(log, sprintf("-Inicio del registro de captura %s %s\r\n", date, 
    strftime("%H:%M", localtime(time))));

srl_write(fd, "c"); % iniciar captura
i = 1;
unwind_protect
  while(1)
    % leemos una línea, que son 18 bytes en total
    str = char(srl_read(fd, 18));
    n = base2dec(str(1:10), 10);
    m = base2dec(str(13:16), 10);
    if (isnan(n) || isnan(m))
      printf("error en la lectura de datos\n");
      continue
    end
    t(i) = n * Tm;
    v(i) = m * LSB;
    if (mod(i, 100) == 0)
      % actualizar gráfico
      set(h, 'XData', t, 'YData', v);
      drawnow;
    end
    %guardamos un registro
    fwrite(log, str);
    i++;
  end
unwind_protect_cleanup
  % Ctrl-C, detener y cerrar la conección
  srl_write(fd, "c");
  fclose(fd);
  fwrite(log, "-Fin de la captura\r\n");
  fclose(log);
  % guardar los datos capturados
  if (length(t) != length(v))
    % antes de guardar las longitudes tienen que ser iguales
    N = min([length(t), length(v)]);
    t = t(1:N);
    v = v(1:N);
  end
  csvwrite(sprintf("captura_continua_%s-%s.csv", date, strftime("%H:%M", localtime(time))), [t' v']);
end
